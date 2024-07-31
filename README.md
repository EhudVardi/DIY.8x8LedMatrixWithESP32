# Description

This is a DIY project utilizing a nice 8 by 8 led kit I've soldered together, controlled with an [ESP32DEVKITV1 board](https://www.circuitstate.com/pinouts/doit-esp32-devkit-v1-wifi-development-board-pinout-diagram-and-reference/), coded using [Arduino IDE](https://www.arduino.cc/en/software)

the DIY board offers external pins to be controlled from the outside, [bought from aliexpress](https://www.aliexpress.com/item/1005005671763020.html) and soldered manually.

The following is the Schema of the board, provided kindly by the seller:
![8x8 Led Matrix Board Schema](https://raw.githubusercontent.com/EhudVardi/DIY.8x8LedMatrixWithESP32/master/Resources/schema.webp)

A few notes on the board:
1. there are no permanent latching of the data, meaning that in order to see a constant pattern for a specific time, one must repeatedly send the pattern over and over again so it will create the illusion that the pattern is stable.
2. there are two 8 bit led drivers, one for 8 rows and one for 8 columns. the first byte we send enables specific rows and the second byte we send will light up the leds of the rows that were enabled 
   - for example, we send 10000001 which will enable the 1st and the last rows, and then we send 00011000 which will light up the 4th and 5th leds of the first and the last rows.
3. I could not identify the type of the single 8 pin chip, I'm not sure how does it plays in the mix.
4. Note of the J4 point, I believe it is connected to a carry bit of some sort and it might allow us to concatenate multiple boards together.

# Environment Installation
1. Download & install Arduino IDE
2. Install the ESP32 Board in Arduino IDE: Open Arduino IDE.
   1. Go to File > Preferences.
   2. In the Additional Board Manager URLs field, add: https://dl.espressif.com/dl/package_esp32_index.json.
   3. Go to Tools > Board > Board Manager, Search for "esp32" and install the "esp32" platform.
   4. Select the ESP32 Board: Go to Tools > Board > esp32 > and select "ESP32 Dev Module".

# Connecting the boards together

### DIY board 
The board runs a demo when provided with power only.
The board has the following pins: 
- OE: enable/disable pin
- IN: data-in pin. this data is shifted into the board bit by bit.
- STB: latch the data into the internal registers of the led drivers.
- CLK: clock pin used to time the data shifting from the IN pin.
- VCC, GND: power the board with either 3.3V or 5V.

### ESP32 board
The board is powered on its "Vin" & "GND" pins, and they can take input voltage from 4V to 12V.

When powered, the board provides a stable 3.3V on the its "3.3V" & "GND" pins that can power low current loads.

We select GPIO's 12,13,14 and 15 of the ESP32 board to the "OE", "IN", "STB", "CLK" of the led matrix.

### Connecting them together:
   1. Connect external 5V power source to the "Vin" & "GND" pins of the ESP32 board.
   2. Connect pins from ESP32 board to the led matrix board pins:
      1. "GPIO12" to "OE"
      2. "GPIO13" to "IN"
      3. "GPIO14" to "STB"
      4. "GPIO15" to "CLK"
      5. "3.3V" & "GND" to "VCC" & "GND"
         - ** it is possible to provide the matrix board with a separate 3.3V external voltage, to avoid the ESP32 board with the task to power it by itself. both ways will work

# Build & Flash firmware
1. Open the ".ino" code file in the IDE 
2. Disconnect the external power to the ESP32 board
3. connect the ESP32 board to your host PC via USB and select the COM port 
- Open windows Device manager and look under "ports" what is the port of the board. 
- Go to Tools > Port > and select that port.
- The IDE should tell you that the board is connected at the bottom right corner of the app
4. Hit the "Upload" button at the top left. the IDE will compile the program and if successful, it will attempt to upload the binaries to the ESP32 board. upon success it will show "100%" message at the log window.
5. (optional) To prevent the host PC to power the boards, disconnect the USB cable and re-connect the external 5V power source to the ESP32 board.


# Results
At this point, the led matrix board should display and swap between 3 patterns in a 1 second interval.

# Modifying the Code
- To add more patterns, simply add more data to the "patterns" variable.
- To make use of different GPIO's, make sure to change the definitions in the code, and it is recommended to select simple GPIO pins and not UART pins. do NOT use UART0 pins, you won't be able to flash new firmware if you do.


# Contributing

Pull requests are welcome. Make me smarted if you will ;)



# License

Me?
