//
// Created by tombr on 24/07/2019.
//

#include <SPI.h>
#include "TLC5947_SPI.h"

TLC5947_SPI::TLC5947_SPI(uint16_t num, uint8_t pin) {
    this->numdrivers = num;
    this->pin = pin;

    this->pwmbuffer = (uint16_t *) malloc(2 * 24 * num);
    memset(this->pwmbuffer, 0, 2 * 24 * num);
}

void TLC5947_SPI::begin(void) {
    pinMode(MOSI, OUTPUT);
    pinMode(SCK, OUTPUT);

    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
    SPI.begin(pin);

    digitalWrite(pin, LOW);
}

void TLC5947_SPI::setPWM(uint16_t chan, uint16_t pwm) {
    if (pwm > 4095) {
        pwm = 4095;
    }

    if (chan > 24 * this->numdrivers) {
        return;
    }

    this->pwmbuffer[chan] = pwm;
}

void TLC5947_SPI::setLED(uint16_t lednum, uint16_t r, uint16_t g, uint16_t b) {
    this->setPWM(lednum * 3, r);
    this->setPWM(lednum * 3 + 1, g);
    this->setPWM(lednum * 3 + 2, b);
}

void TLC5947_SPI::write() {
    SPI.beginTransaction(SPISettings(30000000, MSBFIRST, SPI_MODE0));
    digitalWrite(pin, LOW);
    // 24 channels per TLC5974
    for (int16_t c = 24 * numdrivers - 1; c >= 0; c -= 2) {
        // 12 bits per channel, send MSB first
        // have to split a pair of channels into groups of 3 bytes
        uint8_t data1 = (pwmbuffer[c] >> 4) & 0x00FF;
        uint8_t data2 = ((pwmbuffer[c] << 4) & 0x00F0) | ((pwmbuffer[c - 1] >> 4) & 0x000F);
        uint8_t data3 = (pwmbuffer[c - 1] & 0x00FFu);

        SPI.transfer(this->pin, data1, SPI_CONTINUE);
        SPI.transfer(this->pin, data2, SPI_CONTINUE);
        SPI.transfer(this->pin, data3, c > 0 ? SPI_CONTINUE : SPI_LAST);
    }

    digitalWrite(pin, HIGH);
    SPI.endTransaction();
}
