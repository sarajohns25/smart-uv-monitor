#ifndef ALERT_MANAGER_H
#define ALERT_MANAGER_H
#include <Arduino.h>
enum AlertLevel { ALERT_SAFE, ALERT_CAUTION, ALERT_HIGH, ALERT_LIMIT };
class AlertManager {
public:
  explicit AlertManager(uint8_t buzzerPin);
  AlertLevel evaluate(float upperDosePercent) const;
  void apply(AlertLevel level);
  const __FlashStringHelper *label(AlertLevel level) const;
private:
  uint8_t pin;
};
#endif
