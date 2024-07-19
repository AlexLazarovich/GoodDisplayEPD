#include "GDEPD.h"

GDEPD::GDEPD(int busyPin, int rstPin, int dcPin, int csPin)
    : busyPin(busyPin), rstPin(rstPin), dcPin(dcPin), csPin(csPin) {
    pinMode(busyPin, INPUT);
    pinMode(rstPin, OUTPUT);
    pinMode(dcPin, OUTPUT);
    pinMode(csPin, OUTPUT);
}

void GDEPD::init(){
    resetDisplay();  // Module reset
    delay(10);
    resetRelease();
    delay(10);
}

inline void GDEPD::SPI_Write(unsigned char value) {
    SPI.transfer(value);
}

void GDEPD::writeCommand(unsigned char command) {
    commsOn();
    commandMode();
    SPI_Write(command);
    commsOff();
}

void GDEPD::writeData(unsigned char data) {
    commsOn();
    dataMode();
    SPI_Write(data);
    commsOff();
}

inline bool GDEPD::isBusy() {
    return digitalRead(busyPin);
}

inline void GDEPD::resetDisplay() {
    digitalWrite(rstPin, LOW);
}

inline void GDEPD::resetRelease() {
    digitalWrite(rstPin, HIGH);
}

inline void GDEPD::commandMode() {
    digitalWrite(dcPin, LOW);
}

inline void GDEPD::dataMode() {
    digitalWrite(dcPin, HIGH);
}

inline void GDEPD::commsOn() {
    digitalWrite(csPin, LOW);
}

inline void GDEPD::commsOff() {
    digitalWrite(csPin, HIGH);
}
