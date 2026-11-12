#include "exposure_calculator.h"
ExposureCalculator::ExposureCalculator() : dose(0), previousUvi(0), hasPrevious(false), activeProfile(3) {}
float ExposureCalculator::thresholdFor(uint8_t p) const {
  // Demonstration-only dose thresholds; not validated MED values or medical advice.
  const float t[6] = {200, 250, 300, 450, 600, 1000};
  if (p < 1) p = 1; if (p > 6) p = 6;
  return t[p - 1];
}
void ExposureCalculator::update(float uvi, float dt, uint8_t profile) {
  if (profile < 1) profile = 1;
  if (profile > 6) profile = 6;
  activeProfile = profile;
  if (uvi < 0) uvi = 0;
  if (dt <= 0) return;
  // Approximate erythemally weighted irradiance: UVI = 40 * E (W/m^2).
  float irradiance = uvi / 40.0f;
  float previousIrradiance = hasPrevious ? previousUvi / 40.0f : irradiance;
  dose += 0.5f * (irradiance + previousIrradiance) * dt;
  previousUvi = uvi; hasPrevious = true;
}
float ExposureCalculator::getDose() const { return dose; }
float ExposureCalculator::getUpperDose() const { return dose * 1.15f; }
float ExposureCalculator::getUpperDosePercent() const {
  return (getUpperDose() / thresholdFor(activeProfile)) * 100.0f;
}
void ExposureCalculator::reset() { dose = 0; previousUvi = 0; hasPrevious = false; }
