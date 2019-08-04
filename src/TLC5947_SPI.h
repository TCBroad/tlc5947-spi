/***************************************************
  This is an example for our Adafruit 24-channel PWM/LED driver
  Pick one up today in the adafruit shop!

  ------> http://www.adafruit.com/products/1429

  These drivers uses SPI to communicate, 3 pins are required to
  interface: Data, Clock and Latch. The boards are chainable

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution

  Modified to use hardware SPI by Tom Broad (tcbroad@gmail.com)
 ****************************************************/
//
// Created by tombr on 24/07/2019.
//

#ifndef BLINK_GDB_TLC5947_SPI_H
#define BLINK_GDB_TLC5947_SPI_H

#include <Arduino.h>

enum LedMode {
    RGB,
    BGR
};

class TLC5947_SPI {
public:
    TLC5947_SPI(uint16_t num, uint8_t pin, LedMode mode = RGB);

    void begin();

    void setPWM(uint16_t chan, uint16_t pwm);
    void setLED(uint16_t lednum, uint16_t r, uint16_t g, uint16_t b);
    void write();
private:
    uint16_t *pwmbuffer;

    uint16_t numdrivers;
    uint8_t pin;

    LedMode mode;
};


#endif //BLINK_GDB_TLC5947_SPI_H
