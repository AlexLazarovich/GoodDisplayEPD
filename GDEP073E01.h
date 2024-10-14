#ifndef _GDEP073E01_H_
#define _GDEP073E01_H_

#include "GDEPD.h"

class GDEP073E01 : public GDEPD {
public:
    GDEP073E01();
    void init() override;
    void clear() override;
    void display(const unsigned char* encodedImage, int length) override;
    inline void sleep() override;
    void init_fast() override;
    inline void startWrite();
    inline void endWrite();
    void displayBlue();
    void displayYellow();

private:
    inline void checkStatus();

    // Command definitions
    static const unsigned char PSR = 0x00;
    static const unsigned char PWRR = 0x01;
    static const unsigned char POF = 0x02;
    static const unsigned char POFS = 0x03;
    static const unsigned char PON = 0x04;
    static const unsigned char BTST1 = 0x05;
    static const unsigned char BTST2 = 0x06;
    static const unsigned char DSLP = 0x07;
    static const unsigned char BTST3 = 0x08;
    static const unsigned char DTM = 0x10;
    static const unsigned char DRF = 0x12;
    static const unsigned char PLL = 0x30;
    static const unsigned char CDI = 0x50;
    static const unsigned char TCON = 0x60;
    static const unsigned char TRES = 0x61;
    static const unsigned char REV = 0x70;
    static const unsigned char VDCS = 0x82;
    static const unsigned char T_VDCS = 0x84;
    static const unsigned char PWS = 0xE3;
};

#endif
