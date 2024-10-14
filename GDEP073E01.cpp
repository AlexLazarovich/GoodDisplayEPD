#include "GDEP073E01.h"

GDEP073E01::GDEP073E01(): GDEPD(A14, A15, A16, A17) {
    width = 800;
    height = 480;
}

void GDEP073E01::init() {
    GDEPD::init();
    
    writeCommand(0xAA);    // CMDH
    writeData(0x49);
    writeData(0x55);
    writeData(0x20);
    writeData(0x08);
    writeData(0x09);
    writeData(0x18);

    writeCommand(PWRR);//
    writeData(0x3F);
    
    writeCommand(PSR);  
    writeData(0x5F);
    writeData(0x69);
    
    writeCommand(POFS);
    writeData(0x00);
    writeData(0x54);
    writeData(0x00);
    writeData(0x44); 

    writeCommand(BTST1);
    writeData(0x40);
    writeData(0x1F);
    writeData(0x1F);
    writeData(0x2C);
    
    writeCommand(BTST2);
    writeData(0x6F);
    writeData(0x1F);
    writeData(0x17);
    writeData(0x49);

    writeCommand(BTST3);
    writeData(0x6F);
    writeData(0x1F);
    writeData(0x1F);
    writeData(0x22);
    writeCommand(PLL);
    writeData(0x08);
    writeCommand(CDI);
    writeData(0x3F);
    
    writeCommand(TCON);
    writeData(0x02);
    writeData(0x00);
    
    writeCommand(TRES);
    writeData(0x03);
    writeData(0x20);
    writeData(0x01); 
    writeData(0xE0);

    writeCommand(T_VDCS);
    writeData(0x01);
    
    writeCommand(PWS);
    writeData(0x2F);

    writeCommand(0x04);     //PWR on  
    checkStatus();          //waiting for the electronic paper IC to release the idle signal
}

void GDEP073E01::init_fast() {
    GDEPD::init();
    writeCommand(0xAA);    // CMDH
    writeData(0x49);
    writeData(0x55);
    writeData(0x20);
    writeData(0x08);
    writeData(0x09);
    writeData(0x18);

    writeCommand(PWRR);
    writeData(0x3F);
    writeData(0x00);
    writeData(0x32);
    writeData(0x2A);
    writeData(0x0E);
    writeData(0x2A);
    
    writeCommand(PSR);  
    writeData(0x5F);
    writeData(0x69);
    
    writeCommand(POFS);
    writeData(0x00);
    writeData(0x54);
    writeData(0x00);
    writeData(0x44); 

    writeCommand(BTST1);
    writeData(0x40);
    writeData(0x1F);
    writeData(0x1F);
    writeData(0x2C);
    
    writeCommand(BTST2);
    writeData(0x6F);
    writeData(0x1F);
    writeData(0x16);
    writeData(0x25);

    writeCommand(BTST3);
    writeData(0x6F);
    writeData(0x1F);
    writeData(0x1F);
    writeData(0x22);
 
    writeCommand(0x13);    // IPC
    writeData(0x00);
    writeData(0x04);
    
    writeCommand(PLL);
    writeData(0x02);
    
    writeCommand(0x41);     // TSE
    writeData(0x00);
    
    writeCommand(CDI);
    writeData(0x3F);
    
    writeCommand(TCON);
    writeData(0x02);
    writeData(0x00);
    
    writeCommand(TRES);
    writeData(0x03);
    writeData(0x20);
    writeData(0x01); 
    writeData(0xE0);
    
    writeCommand(VDCS);
    writeData(0x1E); 

    writeCommand(T_VDCS);
    writeData(0x01);

    writeCommand(0x86);    // AGID
    writeData(0x00);
    
    writeCommand(PWS);
    writeData(0x2F);
 
    writeCommand(0xE0);   // CCSET
    writeData(0x00); 
  
    writeCommand(0xE6);   // TSSET
    writeData(0x00);  

    writeCommand(0x04);     //PWR on  
    checkStatus();          //waiting for the electronic paper IC to release the idle signal
}

void GDEP073E01::clear() {
    startWrite();
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width / 2; j++) {
            writeData(GDEPD::White);
        }
    }
    endWrite();
}

void GDEP073E01::displayBlue() {
    startWrite();
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width / 2; j++) {
            writeData(GDEPD::Blue);
        }
    }
    endWrite();
}

void GDEP073E01::displayYellow() {
    startWrite();
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width / 2; j++) {
            writeData(GDEPD::Yellow);
        }
    }
    endWrite();
}

void GDEP073E01::display(const unsigned char* encodedImage, int length) {
    // Start the data transmission command
    unsigned char count = 0;
    unsigned char color = 0;
    unsigned char oldCount = 0;
    unsigned char oldColor = 0;
    int total = 0;

    startWrite();

    for (int i = 0; i < length; i++) {
        oldColor = color;
        oldCount = count;

        count = (encodedImage[i] >> 3) & 0x1F;
        color = encodedImage[i] & 0x07;
        total += count;

        // If oldCount is odd, combine the last pixel of the previous color with the first of the current color
        if (oldCount % 2 != 0) {
            writeData(oldColor << 4 | color);
            count--;
        }

        // Write remaining pairs of the current color
        while (count > 1) {
            writeData(color << 4 | color);
            count -= 2;
        }
    }

    // Refresh the display to show the new image
    endWrite();
}



inline void GDEP073E01::startWrite() {
    writeCommand(DTM);  // Start data transmission command
}

inline void GDEP073E01::endWrite() {
    writeCommand(DRF);  // DISPLAY REFRESH
    writeData(PSR);
    delay(1);  // The delay here is necessary, 200uS at least
    checkStatus();  // Wait for the electronic paper IC to release the idle signal
}

inline void GDEP073E01::sleep() {
    writeCommand(POF);  // Power off
    writeData(PSR);
    checkStatus();
}

inline void GDEP073E01::checkStatus() {
    while (!digitalRead(busyPin));
}