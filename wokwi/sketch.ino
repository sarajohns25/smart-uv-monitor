#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Wokwi validation build for the Smart UV Exposure Monitor.
// The potentiometer is ONLY a stand-in for the GUVA-S12SD analog output.
// Turn the knob to simulate changing UV input (0..12 UVI).

#define UV_INPUT A0
#define BUZZER_PIN 8
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const uint8_t SKIN_PROFILE = 3; // Demo profile; threshold is a software test constant.
const float PROFILE_THRESHOLDS[6] = {200.0, 250.0, 300.0, 450.0, 600.0, 1000.0};
const float UNCERTAINTY_FACTOR = 1.15;
const unsigned long SAMPLE_INTERVAL_MS = 1000;

unsigned long previousSampleMs = 0;
float cumulativeDose = 0.0;
float previousUvi = 0.0;
bool hasPreviousUvi = false;
bool mpuFound = false;

bool writeMpuRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(0x68);
  Wire.write(reg);
  Wire.write(value);
  return Wire.endTransmission() == 0;
}

bool readMpuBytes(uint8_t startReg, uint8_t *buffer, uint8_t count) {
  Wire.beginTransmission(0x68);
  Wire.write(startReg);
  if (Wire.endTransmission(false) != 0) return false;
  uint8_t received = Wire.requestFrom((uint8_t)0x68, count);
  if (received != count) return false;
  for (uint8_t i = 0; i < count; i++) buffer[i] = Wire.read();
  return true;
}

bool readMotion(bool &moving) {
  moving = false;
  if (!mpuFound) return false;
  uint8_t b[6];
  if (!readMpuBytes(0x3B, b, 6)) return false;
  int16_t rx = (int16_t)((b[0] << 8) | b[1]);
  int16_t ry = (int16_t)((b[2] << 8) | b[3]);
  int16_t rz = (int16_t)((b[4] << 8) | b[5]);
  float ax = rx / 16384.0;
  float ay = ry / 16384.0;
  float az = rz / 16384.0;
  float magnitude = sqrt(ax * ax + ay * ay + az * az);
  moving = fabs(magnitude - 1.0) > 0.12;
  return true;
}

const char *alertFor(float percent) {
  if (percent >= 100.0) return "LIMIT";
  if (percent >= 80.0) return "HIGH";
  if (percent >= 50.0) return "CAUTION";
  return "SAFE";
}

void showReadings(float uvi, float dose, float percent, const char *alert, bool moving) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("SMART UV MONITOR"));
  display.print(F("UV Index: ")); display.println(uvi, 1);
  display.print(F("Dose: ")); display.print(dose, 1); display.println(F(" J/m2"));
  display.print(F("Upper dose: ")); display.println(dose * UNCERTAINTY_FACTOR, 1);
  display.print(F("Exposure: ")); display.print(percent, 0); display.println(F("%"));
  display.print(F("Alert: ")); display.println(alert);
  display.print(F("Motion: ")); display.println(moving ? F("YES") : F("NO"));
  display.display();
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  pinMode(UV_INPUT, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  noTone(BUZZER_PIN);

  bool oledOK = display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
  mpuFound = writeMpuRegister(0x6B, 0x00); // wake MPU6050

  Serial.println(F("Smart UV Monitor - Wokwi validation build"));
  Serial.println(F("time_ms,adc,uv_index,dose_j_m2,upper_dose_j_m2,exposure_percent,alert,motion"));
  Serial.print(F("OLED,")); Serial.println(oledOK ? F("OK") : F("NOT_FOUND"));
  Serial.print(F("MPU6050,")); Serial.println(mpuFound ? F("OK") : F("NOT_FOUND"));

  if (oledOK) {
    display.clearDisplay(); display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1); display.setCursor(0, 12);
    display.println(F("UV Monitor"));
    display.println(F("Wokwi test starting"));
    display.display();
  }
  delay(700);
}

void loop() {
  unsigned long now = millis();
  if (now - previousSampleMs < SAMPLE_INTERVAL_MS) return;
  float dt = previousSampleMs == 0 ? 1.0 : (now - previousSampleMs) / 1000.0;
  previousSampleMs = now;

  int adc = analogRead(UV_INPUT);
  // Simulation-only mapping: potentiometer position 0..1023 -> UVI 0..12.
  float uvi = (adc / 1023.0) * 12.0;
  float irradiance = uvi / 40.0; // W/m2, erythemally weighted approximation
  float previousIrradiance = hasPreviousUvi ? previousUvi / 40.0 : irradiance;
  cumulativeDose += 0.5 * (irradiance + previousIrradiance) * dt;
  previousUvi = uvi;
  hasPreviousUvi = true;

  float threshold = PROFILE_THRESHOLDS[SKIN_PROFILE - 1];
  float upperDose = cumulativeDose * UNCERTAINTY_FACTOR;
  float exposurePercent = 100.0 * upperDose / threshold;
  const char *alert = alertFor(exposurePercent);

  bool moving = false;
  bool motionOK = readMotion(moving);

  if (exposurePercent >= 80.0) tone(BUZZER_PIN, 1800);
  else noTone(BUZZER_PIN);

  showReadings(uvi, cumulativeDose, exposurePercent, alert, moving);

  Serial.print(now); Serial.print(',');
  Serial.print(adc); Serial.print(',');
  Serial.print(uvi, 2); Serial.print(',');
  Serial.print(cumulativeDose, 3); Serial.print(',');
  Serial.print(upperDose, 3); Serial.print(',');
  Serial.print(exposurePercent, 2); Serial.print(',');
  Serial.print(alert); Serial.print(',');
  Serial.println(motionOK ? (moving ? F("MOVING") : F("STILL")) : F("MPU_NOT_FOUND"));
}
