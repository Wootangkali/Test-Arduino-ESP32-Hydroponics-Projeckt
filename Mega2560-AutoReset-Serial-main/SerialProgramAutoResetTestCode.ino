#define ResetPin A3

void setup() {
  // put your setup code here, to run once:
pinMode(ResetPin ,OUTPUT);
pinMode(13 ,OUTPUT);
Serial.begin(115200);
Serial.print("AutoSerialResetArduinoReady Baud 115200");
}
uint8_t NR_Bx = 0;
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
          digitalWrite(ResetPin, HIGH);

          // WYJSCIE_CYFROWE(ResetArduino, ON);
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
void loop() {
  // put your main code here, to run repeatedly:
  SerialMonitorReset();
}
