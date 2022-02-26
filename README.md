# Snake Game on 5110 LCD

![](/snake_game.png)

## How to Built It?

1. Built the circuit correctly

    > *<b>How to Connect the 5110 LCD to Arduino UNO:</b><br>Just add 10kΩ resistors between the CLK, DIN, D/C, and RST pins and a 1kΩ resistor between CE.<br>Finally, The backlight(BL) pin is connected to 3.3V via 330Ω current limiting resistor.![](/uno_to_5110.png)<br>https://lastminuteengineers.com/nokia-5110-lcd-arduino-tutorial/*

    Connect VRX to A0, VRY to A1, +5V to 5V, GND to GND.
    ![](/diagram.png "Diagram")

1. Connect the Arduino UNO to your computer via USB

1. Download Arduino IDE

1. Open "snake-game-on-5110-lcd.ino" in Arduino IDE

1. Select the Board and the Port

1. Click the upload button

1. Enjoy