#include <HardwareSerial.h>

HardwareSerial MySerial();

void setup() {
    HardwareSerial.begin(9600, SERIAL_8N1, 18, 19);
}

void loop() {
    while (HardwareSerial.available() > 0) {
        uint8_t byteFromSerial = HardwareSerial.read();
        // Do something
    }
    
    //Write something like that
    MySerial.write(random(0, 255));
}
