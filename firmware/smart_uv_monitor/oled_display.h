#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H
#include <Arduino.h>
#include "alert_manager.h"
class OLEDDisplay {
public:
  bool begin();
  void showStatus(const char *line1, const char *line2);
  void showMeasurements(float uvi, float dose, float percent,
                        AlertLevel level, bool moving);
private:
  bool available;
};
#endif
