# Embedded_system_Guessing_game

This was created as part of an assignment for the 'CE223 - C Programming and Embedded Systems' module at University of Essex. It's been a great exercise to practice different concepts of both C/C++ Programming and embedded systems development, using the ARM Mbed Cortex M3 (LPC1786).

## The Guessing Game

The task was to develop a guessing game on the ARM Mbed, using the ARM Mbed development board that was provided.

<img src="Mbed board.jpg" width="350">

The Mbed will interact with the host PC using serial communication via the RS232 protocol. And thus, a host terminal application is also developed (essentially a client-server model).  More details about the game are shown below

- Once PC connection with Mbed started, the secret number is generated randomly for the player to guess.
- The PC host application receives a message via serial communication , prompting the user to start the game with 'y'or 'n'
- The secret number is entered by keypad on the board, and the Mbed receives this number via inputs and processes it.
- Keypad is also used for player to enter any guessing number to interact with the game.
- the answers is monitored, to ensure the player whether they are close to the secret number.
- The results of the guess is shown on the PC application.
- Mechanisms for rejecting invalid inputs from both PC and Mbed is implemented.
- If the player loses, the game continue until forcely stopped. the scoring function will keep note of failed attempt.
- If the player wins, Present the secret number and final score on the LCD screen











## ARM Mbed Development Board

The Mbed Development board contains the following:
- 4x4 Number pad
- LEDs which can display green or red, which is controlled via Serial Peripheral Interface (SPI).
- Switches which are controlled by the latch pin of TLC59281 IC.
- An Ethernet port
- An ARM Mbed (LPC1786)


## Source files

Program code is stored in 'Program_code' branch of this repository

## Libraries used

- The RS232 C library by Teunis van Beelen was used for this project. A link to this library: [RS232 Library](https://www.teuniz.net/RS-232/)
- The 'TextLCD' library by Thomas Lunzer was used for the LCD screen. Link: [TextLCD Library](https://os.mbed.com/users/tlunzer/code/TextLCD/docs/tip/classTextLCD.html) 

