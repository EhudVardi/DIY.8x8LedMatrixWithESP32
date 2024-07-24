# Description

This version of the project is built upon the original, and add a [rotary encoder](https://www.aliexpress.com/item/32913703856.html), in order to control the selection of the pattern that is displayed.

This new setup will allow to select the pattern and also enable/disable the auto switch pattern by clicking the encoder knob.


# Connecting it together

### Rotary encoder
This specific encoder works only with 5V, so it is required to reduce the signal voltages coming out of it to the 0-3.3V range, before feeding it to the ESP32 board.

The encoder has an endless rotation capability which works by having two digital output signals, which phase shift from each other according to the direction of the rotation. by measuring this shift we can tell the direction and amount of rotation.

The encoder has the following pins:
- S1: 1st signal
- S2: 2nd signal
- Key: button press signal
- VCC, GND: 5V power supply
 
Connect as following:
- GND and VCC to the same 5V power supply that powers the ESP32.
- use three pairs of 20K & 10K resistors, to divide 5V to 3.3V. 
   - connect each pair in series, connect the 10K resistor to 5V edge and the 20K edge to GND
   - connect the rotary S1, S2 and Key, each to a single pair, at the middle of each pair.
- from each divisor point (the middle) to ESP32 GPIO pin:
   - S1 to GPIO2
   - S2 to GPIO4
   - Key to GPIO5


# Build & Flash firmware
Use the new code file to flash the code in the same way as before.

!! be sure to disconnect power (out/in) on the ESP side before attempting to flash the firmware.

# Results
Rotating the encoder to either side will select the next/previous available pattern. Clicking the encode will start/stop the auto pattern switch.


# Modifying the Code
One can add new patterns same as before, and also can change the way the rotary encoder controls the ESP32

