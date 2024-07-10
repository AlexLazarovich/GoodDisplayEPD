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
    writeCommand(DTM);
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width / 2; j++) {
            writeData(GDEPD::White);
        }
    }
    writeCommand(DRF);  // Refresh
    delay(1);
    checkStatus();
}

void GDEP073E01::display(const unsigned char* image, ImageDisplayMode mode) {
    cv::Mat processedImage = processImage(image, mode);

    writeCommand(0x10);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width / 2; j++) {
            unsigned char temp1 = processedImage.at<unsigned char>(i, j * 2);
            unsigned char temp2 = processedImage.at<unsigned char>(i, j * 2 + 1);
            unsigned char data_H = colorToData(temp1) << 4;
            unsigned char data_L = colorToData(temp2);
            unsigned char data = data_H | data_L;
            writeData(data);
        }
    }

    writeCommand(0x12);  // DISPLAY REFRESH
    writeData(0x00);
    delay(1);  // The delay here is necessary, 200uS at least
    checkStatus();  // waiting for the electronic paper IC to release the idle signal
}

void GDEP073E01::sleep() {
    writeCommand(POF);  // Power off
    writeData(0x00);
    checkStatus();
}

void GDEP073E01::checkStatus() {
    while (!digitalRead(busyPin));
}

unsigned char GDEP073E01::colorToData(unsigned char color) {
    switch (color) {
        case GDEPD::Black: return 0x00;
        case GDEPD::White: return 0x01;
        case GDEPD::Yellow: return 0x02;
        case GDEPD::Red: return 0x03;
        case GDEPD::Blue: return 0x05;
        case GDEPD::Green: return 0x06;
        default: return 0x00;  // Default to black
    }
}
