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
