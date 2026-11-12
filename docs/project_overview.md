# Project Overview

The Smart Wearable UV Exposure Monitoring System is a prototype intended to
measure ambient UV level, estimate accumulated erythemally weighted exposure,
and provide simple visual and audible warnings. The prototype uses an Arduino
Uno, GUVA-S12SD analog UV module, MPU6050 motion sensor, SSD1306 OLED and buzzer.

The device estimates UVI from an analog sensor signal using a calibration
equation. It converts UVI to approximate irradiance using E = UVI / 40 W/m²
and integrates irradiance over time to estimate dose in J/m².

This is an educational engineering prototype, not a certified UV dosimeter,
medical device, or substitute for public-health sun-protection guidance.
