#ifndef MPU6050_HANDLER_H
#define MPU6050_HANDLER_H
#include <Arduino.h>
#include <Wire.h>
struct MotionReading {
  float ax, ay, az;
  bool moving;
  bool valid;
};
class MPU6050Handler {
public:
  bool begin();
  MotionReading read();
private:
  bool available;
  bool writeRegister(uint8_t reg, uint8_t value);
  bool readRegisters(uint8_t start, uint8_t *buffer, uint8_t count);
};
#endif
