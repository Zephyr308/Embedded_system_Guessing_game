# Embedded_system_Guessing_game

This was created as part of an assignment for the 'CE223 - C Programming and Embedded Systems' module at University of Essex. It's been a great exercise to practice different concepts of both C/C++ Programming and embedded systems development, using the ARM Mbed Cortex M3 (LPC1786).

## The Guessing Game

The task was to develop a guessing game on the ARM Mbed, using the ARM Mbed development board that was provided.










## ARM Mbed Development Board

The Mbed Development board contains the following:
- 4x4 Number pad
- LEDs which can display green or red, which is controlled via Serial Peripheral Interface (SPI).
- Switches which are controlled by the latch pin of TLC59281 IC.
- An Ethernet port (unused for this project)
- An ARM Mbed (LPC1786)


## Libraries used

- The RS232 C library by Teunis van Beelen was used for this project. A link to this library: [RS232 Library](https://www.teuniz.net/RS-232/)
- The 'TextLCD' library by Thomas Lunzer was used for the LCD screen. Link: [TextLCD Library](https://os.mbed.com/users/tlunzer/code/TextLCD/docs/tip/classTextLCD.html) 

