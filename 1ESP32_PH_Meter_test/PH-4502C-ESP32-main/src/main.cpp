#include <Arduino.h>
#include "PHSensor.h"

#define println_(arg) Serial.println(arg);
#define print_(arg) Serial.print(arg);

uint8_t phSensorPin = A0;
PHSensor phSensor{phSensorPin};

void setup()
{
  Serial.begin(115200);
  EEPROM.begin(8);
  analogReadResolution(12); // 4095
  phSensor.init();
}

void loop()
{
  println_('{')

  while (Serial.available())
  {
    String input = Serial.readStringUntil('\n');
    println_(input)
    phSensor.calibrate(input[0]);
    if (input[0] == 'r') { phSensor.clear(); }
  }
  println_(phSensor.retEEPROMvalues())
  print_(phSensor.getReading())
  print_(" / 4095\t\t")
  println_(phSensor.readPH())

  println_('}')
  delay(5000);
}
