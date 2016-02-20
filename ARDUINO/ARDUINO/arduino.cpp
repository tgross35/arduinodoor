#include "ArduinoNonsense.h"

#define relayPin 3
#define LEDR 5
#define LEDG 6
#define LEDB 9
#define SLAVE_ADDRESS 0x04

struct LEDcolors {
    float red;
    float green;
    float blue;
};

LEDcolors colors;
int anal = 0;
bool unlocked = false;
long receivedNumber = 0;
String receivedLong;
uint8_t receivedCount24 = 0;
long unlockedStart;

void decodeSignal(long recVal) {
    //Serial.print("Decoding ");
    //Serial.println(recVal, HEX);
    switch (recVal) {
        case 0x1: // Unlock
            unlocked = true;
            unlockedStart = millis();
            break;
        case 0x2:
            break;
        case 0xFF: // Beginning of IR-style code
            receivedCount24 = 1;
            receivedLong.concat(String(255, HEX));
            break;
    }
}

void decodeI2C (int bytecount) {
    while (Wire.available()) { // Loop while it's receiving data
        receivedNumber = Wire.read();
        if (receivedCount24 > 0 && receivedCount24 < 3) {
            if (receivedNumber < 10) {
                receivedLong.concat("0");
            }
            receivedLong.concat(String(receivedNumber, HEX));
            receivedCount24++;
            
        }
        else {
            //Serial.print("I2C received ");
            //Serial.println(receivedNumber, HEX);
            decodeSignal(receivedNumber);
        }
        
        if (receivedCount24 == 3) {
            receivedCount24 = 0;
            //Serial.print("received: ");
            //Serial.println(receivedLong);
            decodeSignal(strtoul(receivedLong.c_str(), NULL, 16));
            receivedLong = "";
        }
    }
}



void writeLEDs() {
    analogWrite(LEDR, colors.red);
    analogWrite(LEDG, colors.green);
    analogWrite(LEDB, colors.blue);
}

void checkLock() {
    if (unlocked && millis() - unlockedStart < 50) {
        digitalWrite(relayPin, HIGH);
        Serial.println("Unlocked");
    } else {
        unlocked = false;
        digitalWrite(relayPin, LOW);
    }
}

void setup() {
    // put your setup code here, to run once:
    pinMode(relayPin, OUTPUT);
    pinMode(LEDR, OUTPUT);
    pinMode(LEDG, OUTPUT);
    pinMode(LEDB, OUTPUT);
    //Serial.begin(9600);
    
    Wire.begin(SLAVE_ADDRESS);
    Wire.onReceive(decodeI2C);
}


void loop() {
    anal = analogRead(0);
    
    if (unlocked) {
        colors.red = 0;
        colors.green = 255;
        colors.blue = 0;
    }
    else {
        if (anal > 10) {
            //Serial.println(anal);
            colors.red = 255;
            colors.green = 50;
            colors.blue = 0;
        } else if (colors.green > 0) {
            colors.green-= 1;
        } else {
            colors.red = 255;
            colors.green = 0;
            colors.blue = 0;
        }
    }
    checkLock();
    writeLEDs();
    delay(10);
}