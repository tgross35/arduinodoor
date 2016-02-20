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
