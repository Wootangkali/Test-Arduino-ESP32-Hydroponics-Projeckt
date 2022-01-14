#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
  
  LiquidCrystal_I2C lcd(0x27,16,2); // Check I2C address of LCD, normally 0x27 or 0x3F
 #include "OneWire.h"
#include "DallasTemperature.h"
 
// Data wire is connected to GPIO15
#define ONE_WIRE_BUS 4
// Setup a oneWire instance to communicate with a OneWire device
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);
 //28 63 FD 7 64 20 1 EC
DeviceAddress sensor1 = { 0x28, 0x63, 0xFD, 0x7, 0x64, 0x20, 0x1, 0xEC }; 


void setup() {
  // put your setup code here, to run once:
 lcd.begin(21,22);      // In ESP8266-01, SDA=0, SCL=2               
    lcd.backlight();
     Serial.begin(9600);
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures();

 Serial.print("Sensor 1(*C): ");
  Serial.print(sensors.getTempC(sensor1)); 
  
  // put your main code here, to run repeatedly:
lcd.setCursor(0, 0);
    lcd.print(sensors.getTempC(sensor1));
}
