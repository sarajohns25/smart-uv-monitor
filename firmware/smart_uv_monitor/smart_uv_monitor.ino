#include <Wire.h>
#include "uv_sensor.h"
#include "mpu6050_handler.h"
#include "oled_display.h"
#include "exposure_calculator.h"
#include "alert_manager.h"

// Hardware: Arduino Uno, GUVA-S12SD analog UV module, MPU6050,
// SSD1306 128x64 I2C OLED, passive/active buzzer.
const uint8_t UV_PIN = A0;
const uint8_t BUZZER_PIN = 8;

UVSensor uvSensor(UV_PIN);
MPU6050Handler motion;
OLEDDisplay display;
ExposureCalculator exposure;
AlertManager alerts(BUZZER_PIN);

unsigned long lastSampleMs = 0;
const unsigned long SAMPLE_INTERVAL_MS = 1000;
const uint8_t SKIN_PROFILE = 3; // 1..6; set to the user's chosen profile

void setup() {
  Serial.begin(115200);
  Wire.begin();
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  uvSensor.begin();
  bool oledOK = display.begin();
  bool mpuOK = motion.begin();

  Serial.println(F("Smart UV Exposure Monitor"));
  Serial.println(F("time_ms,adc,voltage_v,uv_index,dose_j_m2,upper_dose_j_m2,alert,motion"));
  Serial.print(F("OLED: ")); Serial.println(oledOK ? F("OK") : F("NOT FOUND"));
  Serial.print(F("MPU6050: ")); Serial.println(mpuOK ? F("OK") : F("NOT FOUND"));
  display.showStatus("UV Monitor", "Starting...");
  delay(800);
}

void loop() {
  const unsigned long now = millis();
  if (now - lastSampleMs < SAMPLE_INTERVAL_MS) return;
  const float dtSeconds = (now - lastSampleMs) / 1000.0f;
  lastSampleMs = now;

  UVReading reading = uvSensor.read();
  MotionReading movement = motion.read();
  exposure.update(reading.uvIndex, dtSeconds, SKIN_PROFILE);
  AlertLevel level = alerts.evaluate(exposure.getUpperDosePercent());

  alerts.apply(level);
  display.showMeasurements(reading.uvIndex, exposure.getDose(),
                           exposure.getUpperDosePercent(), level,
                           movement.valid && movement.moving);

  Serial.print(now); Serial.print(',');
  Serial.print(reading.adc); Serial.print(',');
  Serial.print(reading.voltage, 4); Serial.print(',');
  Serial.print(reading.uvIndex, 3); Serial.print(',');
  Serial.print(exposure.getDose(), 3); Serial.print(',');
  Serial.print(exposure.getUpperDose(), 3); Serial.print(',');
  Serial.print(alerts.label(level)); Serial.print(',');
  Serial.println(movement.valid && movement.moving ? F("MOVING") : F("STILL"));
}
