#ifndef UV_SENSOR_H
#define UV_SENSOR_H
#include <Arduino.h>

struct UVReading {
  int adc;
  float voltage;
  float uvIndex;
};

class UVSensor {
public:
  explicit UVSensor(uint8_t analogPin);
  void begin();
  UVReading read();
  void setCalibration(float voltsPerUVI, float zeroOffsetVolts);
private:
  uint8_t pin;
  float voltsPerUVI;
  float zeroOffsetVolts;
};
#endif
