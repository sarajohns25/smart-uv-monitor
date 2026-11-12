# Calibration Method

1. Warm up the reference UV meter and prototype sensor as specified by their
   manufacturers.
2. Place both sensors side by side, with the same orientation and unobstructed
   sky view. Avoid shading one sensor with the other.
3. Collect paired readings across multiple UV levels and repeat on more than
   one occasion if possible.
4. Fit a calibration relationship between module output voltage and reference
   UVI. Start with linear regression only if residuals support linearity.
5. Record slope, intercept, fit quality, range, date, weather and geometry.
6. Validate using separate readings not used to fit the calibration.
7. Recalibrate if the sensor, optical cover, enclosure or geometry changes.

The default firmware conversion is a placeholder. The GUVA-S12SD photodiode
module output depends on its amplifier circuit and implementation; do not use
the placeholder as a measurement specification.
