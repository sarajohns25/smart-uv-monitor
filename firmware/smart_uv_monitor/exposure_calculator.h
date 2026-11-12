#ifndef EXPOSURE_CALCULATOR_H
#define EXPOSURE_CALCULATOR_H
#include <Arduino.h>
class ExposureCalculator {
public:
  ExposureCalculator();
  void update(float uvIndex, float dtSeconds, uint8_t skinProfile);
  float getDose() const;
  float getUpperDose() const;
  float getUpperDosePercent() const;
  void reset();
private:
  float dose;
  float previousUvi;
  bool hasPrevious;
  uint8_t activeProfile;
  float thresholdFor(uint8_t profile) const;
};
#endif
