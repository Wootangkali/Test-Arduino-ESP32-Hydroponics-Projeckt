#include <ManagedSerialDevice.h>
#include <Regexp.h>

ManagedSerialDevice handler = ManagedSerialDevice();

void setup() {
    handler.begin(&Serial);

    ManagedSerialDevice::Command commands[] = {
        ManagedSerialDevice::Command(
            "AT+CIPSTART=\"TCP\",\"mywebsite.com\",\"80\"", // Command
            "OK\r\n",  // Expectation regex
            [](MatchState ms){
                Serial.println("Connected");
            }
        },
        ManagedSerialDevice::Command(
            "AT+CIPSEND",
            ">",
            NULL,
            NULL,
            COMMAND_TIMEOUT,
            1000  // Wait for 1s before running this command 
        ),
        ManagedSerialDevice::Command(
            "abc\r\n\x1a"
            "SEND OK\r\n"
        )
    }
    handler.executeChain(commands, 3);
}


void loop() {
    handler.loop();
}
