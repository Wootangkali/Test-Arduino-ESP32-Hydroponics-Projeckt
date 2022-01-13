#include <TasmotaSerial.h>
#include <core_version.h>
TasmotaSerial swSer(19, 18);

void setup() {
  Serial.begin(115200);
  swSer.begin();

  Serial.println("\nTasmota serial test started");

  for (char ch = ' '; ch <= 'z'; ch++) {
    swSer.write(ch);
  }
  swSer.println("");

}

void loop() {
  while (swSer.available() > 0) {
    Serial.write(swSer.read());
  }
  while (Serial.available() > 0) {
    swSer.write(Serial.read());
  }

}
