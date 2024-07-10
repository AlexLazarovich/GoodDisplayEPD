#include "GDEPD.h"
#include <SPI.h>

GDEPD::GDEPD(int busyPin, int rstPin, int dcPin, int csPin)
    : busyPin(busyPin), rstPin(rstPin), dcPin(dcPin), csPin(csPin) {
    pinMode(busyPin, INPUT);
    pinMode(rstPin, OUTPUT);
    pinMode(dcPin, OUTPUT);
    pinMode(csPin, OUTPUT);
}

void GDEPD::SPI_Write(unsigned char value) {
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

bool GDEPD::isBusy() {
    return digitalRead(busyPin);
}

void GDEPD::resetDisplay() {
    digitalWrite(rstPin, LOW);
}

void GDEPD::resetRelease() {
    digitalWrite(rstPin, HIGH);
}

void GDEPD::commandMode() {
    digitalWrite(dcPin, LOW);
}

void GDEPD::dataMode() {
    digitalWrite(dcPin, HIGH);
}

void GDEPD::commsOn() {
    digitalWrite(csPin, LOW);
}

void GDEPD::commsOff() {
    digitalWrite(csPin, HIGH);
}

cv::Mat GDEPD::processImage(const unsigned char* image, ImageDisplayMode mode) {
    cv::Mat img = cv::imdecode(cv::Mat(1, width * height, CV_8UC1, (void*)image), cv::IMREAD_GRAYSCALE);

    cv::Mat result;
    switch (mode) {
        case CROP:
            result = img(cv::Rect(0, 0, width, height));
            break;
        case FIT:
            cv::resize(img, result, cv::Size(width, height));
            break;
        case FIT_ASPECT_RATIO:
            int new_width, new_height;
            if (img.cols * height > img.rows * width) {
                new_width = width;
                new_height = img.rows * width / img.cols;
            } else {
                new_width = img.cols * height / img.rows;
                new_height = height;
            }
            cv::resize(img, result, cv::Size(new_width, new_height));
            cv::Mat canvas = cv::Mat::ones(height, width, CV_8UC1) * 255;  // Create a white canvas
            result.copyTo(canvas(cv::Rect((width - new_width) / 2, (height - new_height) / 2, new_width, new_height)));
            result = canvas;
            break;
    }

    return result;
}
