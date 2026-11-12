# Firmware

Target board: Arduino Uno. Sensors: GUVA-S12SD analog UV module on A0,
MPU6050 on I2C (A4/A5), SSD1306 OLED at I2C address 0x3C, buzzer on D8.

Install these Arduino libraries: Adafruit GFX Library, Adafruit SSD1306.
The MPU6050 is accessed directly over I2C, so no MPU library is required.

**Calibration warning:** `uv_sensor.cpp` uses a provisional linear conversion
(0.10 V per UVI by default). Determine the actual slope and offset using a
traceable reference UV meter and the exact sensor/module. Do not treat this
default as calibrated. The dose thresholds in `exposure_calculator.cpp` are
demonstration constants, not clinically validated MED values.
