#ifndef _GDEPD_H_
#define _GDEPD_H_

#include "Arduino.h"
#include <SPI.h>

class GDEPD {
public:
    GDEPD(int busyPin, int rstPin, int dcPin, int csPin);
    virtual void init() = 0;
    virtual void clear() = 0;
    virtual void display(const unsigned char* encodedImage, int length) = 0;
    virtual void sleep() = 0;
    virtual void init_fast() = 0;

protected:
    unsigned int width;
    unsigned int height;
    int busyPin;
    int rstPin;
    int dcPin;
    int csPin;

    // SPI communication methods
    inline void SPI_Write(unsigned char value);
    void writeCommand(unsigned char command);
    void writeData(unsigned char data);

    // Pin control methods
    inline bool isBusy();
    inline void resetDisplay();
    inline void resetRelease();
    inline void commandMode();
    inline void dataMode();
    inline void commsOn();
    inline void commsOff();

    // Color definitions
    static const unsigned char Black = 0x00;  
    static const unsigned char White = 0x11;  
    static const unsigned char Green = 0x66;  
    static const unsigned char Blue = 0x55;  
    static const unsigned char Red = 0x33;  
    static const unsigned char Yellow = 0x22; 
    static const unsigned char Clean = 0x77;
};

#endif
