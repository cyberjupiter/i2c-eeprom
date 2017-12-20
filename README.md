# i2c-eeprom

## Overview
This project is done as my programming practice. It is written in C, to allow portability. It must be used along with my own I2C library which is located in cyberjupiter/I2CinC.

The library is tested on Arduino UNO which is based on Atmega328P microcontroller. Future plans include to make it work on other similar AVR microcontrollers. However, any other 8-bit AVR should also be able to use this library.

The library is also intended to become an example for any other microcontrollers that supports I2C/TWI interface for connecting external eeprom.

## Compiling the library
Since it is made and tested on Arduino, you need to use the Arduino IDE or any other compiler that includes avr-gcc. 

