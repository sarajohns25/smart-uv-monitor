#include "mpu6050_handler.h"
static const uint8_t MPU_ADDR = 0x68;

bool MPU6050Handler::writeRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(reg); Wire.write(value);
  return Wire.endTransmission() == 0;
}
bool MPU6050Handler::readRegisters(uint8_t start, uint8_t *buffer, uint8_t count) {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(start);
  if (Wire.endTransmission(false) != 0) return false;
  uint8_t got = Wire.requestFrom(MPU_ADDR, count);
  if (got != count) return false;
  for (uint8_t i = 0; i < count; ++i) buffer[i] = Wire.read();
  return true;
}
bool MPU6050Handler::begin() {
  available = writeRegister(0x6B, 0x00); // wake device
  return available;
}
MotionReading MPU6050Handler::read() {
  MotionReading out = {0, 0, 0, false, false};
  if (!available) return out;
  uint8_t b[6];
  if (!readRegisters(0x3B, b, 6)) return out;
  int16_t rx = (int16_t)((b[0] << 8) | b[1]);
  int16_t ry = (int16_t)((b[2] << 8) | b[3]);
  int16_t rz = (int16_t)((b[4] << 8) | b[5]);
  out.ax = rx / 16384.0f; out.ay = ry / 16384.0f; out.az = rz / 16384.0f;
  // A simple movement flag from deviation of acceleration magnitude from 1 g.
  float mag = sqrt(out.ax*out.ax + out.ay*out.ay + out.az*out.az);
  out.moving = fabs(mag - 1.0f) > 0.12f;
  out.valid = true;
  return out;
}
