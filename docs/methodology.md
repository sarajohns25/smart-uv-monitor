# Methodology

1. Acquire the analog output of the GUVA-S12SD module.
2. Average repeated ADC samples and convert ADC counts to voltage.
3. Apply a calibration slope and offset determined against a reference UV meter.
4. Convert calibrated UVI to approximate erythemally weighted irradiance:
   E = UVI / 40 W/m².
5. Integrate dose over time using the trapezoidal rule.
6. Apply a configurable uncertainty margin to the estimated dose.
7. Compare the upper estimate with a configurable profile threshold and show
   SAFE, CAUTION, HIGH or LIMIT.
8. Log timestamp, ADC, voltage, UVI, dose, alert and motion state over Serial.
9. Validate the calculations using the supplied synthetic data and tests,
   then compare hardware readings against a reference instrument outdoors.
