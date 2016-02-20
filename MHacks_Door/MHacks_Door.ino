#include <Wire.h>

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
