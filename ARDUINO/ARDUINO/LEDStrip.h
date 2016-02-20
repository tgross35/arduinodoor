#pragma once

#include <Color.h>
#include <assert.h>
#include <Arduino.h>

class LEDStrip {
public:

    int inREDPIN;
    int inGREENPIN;
    int inBLUEPIN;

    void setRGB(int redVal, int greenVal, int blueVal) {
        assert((redVal < 256) && (redVal >= 0));
        assert((greenVal < 256) && (greenVal >= 0));
        assert((blueVal < 256) && (blueVal >= 0));

        assert(inREDPIN != -1);
        assert(inGREENPIN != -1);
        assert(inBLUEPIN != -1);

        analogWrite(inREDPIN, redVal);
        analogWrite(inGREENPIN, greenVal);
        analogWrite(inBLUEPIN, blueVal);
    }

    void setColor(Color &color) {
        setRGB(color.redVal, color.greenVal, color.blueVal);
    }

    LEDStrip(int REDPIN, int GREENPIN, int BLUEPIN) : inREDPIN(REDPIN), inGREENPIN(GREENPIN), inBLUEPIN(BLUEPIN) {}
};
