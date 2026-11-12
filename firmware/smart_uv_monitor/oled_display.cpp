#include "oled_display.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
static Adafruit_SSD1306 oled(128, 64, &Wire, -1);
bool OLEDDisplay::begin() {
  available = oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  if (available) { oled.clearDisplay(); oled.setTextColor(SSD1306_WHITE); oled.display(); }
  return available;
}
void OLEDDisplay::showStatus(const char *a, const char *b) {
  if (!available) return;
  oled.clearDisplay(); oled.setTextSize(1); oled.setCursor(0, 8);
  oled.println(a); oled.println(b); oled.display();
}
void OLEDDisplay::showMeasurements(float uvi, float dose, float percent,
                                   AlertLevel level, bool moving) {
  if (!available) return;
  oled.clearDisplay();
  oled.setTextSize(1); oled.setCursor(0, 0);
  oled.print(F("UV Index: ")); oled.println(uvi, 1);
  oled.print(F("Dose: ")); oled.print(dose, 1); oled.println(F(" J/m2"));
  oled.print(F("Est. limit: ")); oled.print(percent, 0); oled.println(F("%"));
  oled.print(F("Status: "));
  if (level == ALERT_SAFE) oled.println(F("SAFE"));
  else if (level == ALERT_CAUTION) oled.println(F("CAUTION"));
  else if (level == ALERT_HIGH) oled.println(F("HIGH"));
  else oled.println(F("LIMIT"));
  oled.print(F("Motion: ")); oled.println(moving ? F("YES") : F("NO"));
  oled.display();
}
