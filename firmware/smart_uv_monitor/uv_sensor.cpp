#include "uv_sensor.h"

UVSensor::UVSensor(uint8_t analogPin)
  : pin(analogPin), voltsPerUVI(0.10f), zeroOffsetVolts(0.00f) {}

void UVSensor::begin() {
  pinMode(pin, INPUT);
  analogReference(DEFAULT);
}

void UVSensor::setCalibration(float slope, float offset) {
  if (slope > 0.0f) voltsPerUVI = slope;
  zeroOffsetVolts = offset;
}

UVReading UVSensor::read() {
  // Average several ADC samples to reduce short-term noise.
  long sum = 0;
  const uint8_t n = 8;
  for (uint8_t i = 0; i < n; ++i) {
    sum += analogRead(pin);
    delay(2);
  }
  const int adc = (int)(sum / n);
  const float voltage = adc * (5.0f / 1023.0f);
  // Provisional linear conversion only. Calibrate against a reference UV meter.
  float uvi = (voltage - zeroOffsetVolts) / voltsPerUVI;
  if (uvi < 0.0f) uvi = 0.0f;
  if (uvi > 15.0f) uvi = 15.0f;
  UVReading result = {adc, voltage, uvi};
  return result;
}
