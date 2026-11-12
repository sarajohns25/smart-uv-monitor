# Smart UV Monitor

A modular Arduino Uno prototype and Python analysis/simulation workspace for
a wearable UV exposure monitor.

## Hardware
- Arduino Uno
- GUVA-S12SD analog UV module (A0)
- MPU6050 (I2C)
- SSD1306 128x64 OLED (I2C, address 0x3C)
- Buzzer (D8)

## Repository layout
- `firmware/smart_uv_monitor/` — modular Arduino sketch and source files
- `analysis/` — calibration, dose, sampling and plotting scripts
- `data/` — example raw, calibrated and exposure CSV files
- `simulation/` — synthetic UV data and dose simulation
- `docs/` — project, methodology, circuit and validation notes
- `images/` — generated diagrams and example plots
- `tests/` — pytest checks

## Setup
1. Install Arduino IDE and select Arduino Uno.
2. Install Arduino libraries: Adafruit GFX Library and Adafruit SSD1306.
3. Open `firmware/smart_uv_monitor/smart_uv_monitor.ino`.
4. Install Python dependencies: `pip install -r requirements.txt`.
5. From the repository root, run `pytest`.
6. Run simulation: `python simulation/exposure_simulation.py`.
7. Generate plots: `python analysis/generate_plots.py`.

## Important scientific limitations
The GUVA conversion constants and profile dose thresholds are provisional
software placeholders. Calibrate the exact sensor module against a suitable
reference UV meter. Do not interpret the profile thresholds as validated
minimal erythema doses, medical advice or a guarantee against sunburn.
The provided datasets are synthetic examples and must not be presented as
collected experimental data.


## Wokwi simulation
See `wokwi/` for the Wokwi-specific sketch, diagram, library list and setup instructions. The potentiometer stands in for the GUVA-S12SD analog output.
