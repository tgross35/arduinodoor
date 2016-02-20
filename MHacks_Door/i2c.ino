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
