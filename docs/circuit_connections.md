# Circuit Connections

**Arduino Uno wiring (verify the exact breakout pin labels before powering):**

| Module pin | Arduino Uno |
|---|---|
| GUVA-S12SD analog OUT | A0 |
| GUVA module VCC/GND | Supply/GND per module datasheet |
| MPU6050 SDA | A4 (SDA) |
| MPU6050 SCL | A5 (SCL) |
| MPU6050 VCC/GND | Per breakout-board voltage specification |
| SSD1306 SDA | A4 (SDA) |
| SSD1306 SCL | A5 (SCL) |
| SSD1306 VCC/GND | Per OLED module specification |
| Buzzer + | D8 |
| Buzzer - | GND |

All modules need a common ground. The MPU6050 and OLED share the I2C bus;
check that their addresses do not conflict. Typical addresses are 0x68 and
0x3C respectively. Use a transistor driver if the buzzer current exceeds the
microcontroller pin rating. Add appropriate current limiting/protection.
