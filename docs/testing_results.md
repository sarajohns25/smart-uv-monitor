# Testing Results and Status

The repository includes synthetic CSV data and automated tests for the
dose-integration, calibration-metric and simulation-output paths.

**Important status distinction:** the supplied CSVs are generated example
data, not field measurements. They do not establish sensor accuracy or
clinical validity. Before reporting experimental results, replace example
data with clearly documented measurements and record instrument model,
calibration certificate/status, sampling interval, location, weather and
measurement geometry.

Suggested acceptance tests:
- Verify analog readings are stable at fixed illumination.
- Compare UVI estimates with a reference meter at several levels.
- Check dose integration against an independent spreadsheet calculation.
- Verify OLED and buzzer states at each configured alert boundary.
- Confirm I2C devices are detected reliably.
- Measure current consumption and battery runtime.
