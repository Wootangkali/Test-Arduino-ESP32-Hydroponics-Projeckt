#define Serial_0_Baud 115200
#define ResetArduino_pin 12 // > ULN 2004 > reset_pin
uint8_t NR_Bx = 0;

// add to setup()
void SerialAktywuj() {  Serial.begin(Serial_0_Baud); }

// add SerialMonitorReset() to loop()
void SerialMonitorReset() {
  if (Serial.available()) {
    int inByte = Serial.read();
    //#ifdef SerialEcho
    Serial.write(inByte);
    //#endif
    if (inByte == 0x30 && (NR_Bx == 0 || NR_Bx == 2)) {
      NR_Bx++;
    }
    else {
      if (inByte == 0x20 && (NR_Bx == 1 || NR_Bx == 3)) {
        NR_Bx++;
        if (NR_Bx > 1) {
          digitalWrite(13, HIGH);
          digitalWrite(ResetArduino_pin, HIGH);
          NR_Bx = 0;
        }
      }
      else
      {
        NR_Bx = 0;
      }
    }
  }
}
