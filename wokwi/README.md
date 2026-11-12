# Wokwi simulation — Smart UV Monitor

## Files
- `sketch.ino`: single-file Wokwi test firmware
- `diagram.json`: Arduino Uno, potentiometer (UV input stand-in), MPU6050, SSD1306 OLED and buzzer
- `libraries.txt`: Arduino libraries required by the sketch

## Browser setup
1. Create a new **Arduino Uno** project at https://wokwi.com/projects/new/arduino-uno.
2. Replace the editor's `sketch.ino` with this folder's `sketch.ino`.
3. Open `diagram.json` in the project, replace its contents with this folder's `diagram.json`.
4. Add a `libraries.txt` project file and paste the two library names from this folder.
5. Start simulation and open Serial Monitor at 115200 baud.

Wokwi browser projects are not opened by uploading a local ZIP. The files must be copied into a new Wokwi project once.

## How to test
- Turn the potentiometer: this simulates the analog voltage from the UV sensor and changes the displayed UVI.
- Watch the OLED and Serial Monitor for UVI, cumulative dose, uncertainty-adjusted dose and alert state.
- Increase the potentiometer and let the simulation run; the buzzer should sound when the estimated exposure reaches 80% of the demo threshold.
- MPU6050 is read over I2C at address 0x68. Its simulated motion can be adjusted through the component controls if available.

## Pin map represented by this diagram
| Function | Arduino Uno | Wokwi component |
|---|---|---|
| UV analog input | A0 | Potentiometer SIG (stand-in for GUVA-S12SD OUT) |
| I2C SDA | A4 | MPU6050 SDA + OLED SDA |
| I2C SCL | A5 | MPU6050 SCL + OLED SCL |
| Buzzer + | D8 | Buzzer pin 2 |
| Common ground | GND | Pot, MPU6050, OLED, buzzer pin 1 |

## Important limitations
- Wokwi's potentiometer is a functional analog-input stand-in, not a GUVA-S12SD model. It cannot validate the GUVA module's real output voltage, sensitivity, spectral response or calibration.
- The OLED and MPU6050 are simulated components; this test checks code-level I2C communication and pin mapping, not the quality of physical modules.
- Demo dose thresholds and the 15% uncertainty factor are provisional software test values, not validated MED values or medical guidance.
- This diagram powers the simulated MPU6050 and OLED from 5V as Wokwi's modeled parts specify. For physical hardware, verify the exact breakout-board voltage limits and I2C logic-level requirements before wiring. Do not blindly copy supply voltages from a simulator to an unidentified module.
- The Wokwi build is a dedicated single-file test sketch. The modular hardware firmware remains in `firmware/smart_uv_monitor/`.
