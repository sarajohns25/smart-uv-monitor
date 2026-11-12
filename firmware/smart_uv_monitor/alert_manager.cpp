
#include "alert_manager.h"

AlertManager::AlertManager(uint8_t buzzerPin) : pin(buzzerPin) {}

AlertLevel AlertManager::evaluate(float p) const {
  if (p >= 100.0f) return ALERT_LIMIT;
  if (p >= 80.0f) return ALERT_HIGH;
  if (p >= 50.0f) return ALERT_CAUTION;

  return ALERT_SAFE;
}

void AlertManager::apply(AlertLevel level) {
  if (level == ALERT_HIGH || level == ALERT_LIMIT) {
    // Generate a 1000 Hz warning tone.
    tone(pin, 1000);
  } else {
    // Keep buzzer silent for SAFE and CAUTION.
    noTone(pin);
  }
}

const __FlashStringHelper *AlertManager::label(AlertLevel level) const {
  switch (level) {
    case ALERT_CAUTION:
      return F("CAUTION");

    case ALERT_HIGH:
      return F("HIGH");

    case ALERT_LIMIT:
      return F("LIMIT");

    default:
      return F("SAFE");
  }
}
