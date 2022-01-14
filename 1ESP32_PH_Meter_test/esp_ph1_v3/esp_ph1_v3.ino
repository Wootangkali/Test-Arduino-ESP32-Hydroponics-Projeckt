/*
 # This sample code is used to test the pH meter V1.0.
 # Editor : YouYou
 # Ver    : 1.0
 # Product: analog pH meter
 # SKU    : SEN0161
*/
#define SensorPin 35            //pH meter Analog output to Arduino Analog Input 0
#define Offset 18.31            //deviation compensate
#define LED 13
#define samplingInterval 5
#define printInterval 300
#define ArrayLenth  40    //times of collection
int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=5;


//Header declearation Start
#include <LiquidCrystal_I2C.h> //Library for I2C lcd
#include <OneWire.h> //One wire library
#include <DallasTemperature.h> //Library for DS18B20 Sensor
#include <math.h>// Library for math function 
//Header Declearation End


#include <Arduino.h>
#include <Ticker.h>

#include "DHTesp.h" // Click here to get the library: http://librarymanager/All#DHTesp

#ifndef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP32 ONLY!)
#error Select ESP32 board.
#endif
/** Initialize DHT sensor 1 */
DHTesp dhtSensor1;
/** Task handle for the light value read task */
TaskHandle_t tempTaskHandle = NULL;
/** Pin number for DHT11 1 data pin */
int dhtPin1 = 33;
/** Data from sensor 1 */
TempAndHumidity sensor1Data;

//Pin Assignment and declearation Start
#define ONE_WIRE_BUS 4 //data pin  DQ pin of DS18B20 connected to digital pin D5
LiquidCrystal_I2C lcd(0x27,16,2);  //set the LCD address to 0x27 for a 20 chars and 4 line display

OneWire oneWire(ONE_WIRE_BUS); //Ste up one wire instance
DallasTemperature sensors(&oneWire); //pass one wire reference to DS18B20 library




void setup(void)
{
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
  Serial.println("pH meter experiment!");    //Test the serial monitor
  // Initialize temperature sensor 1
  dhtSensor1.setup(dhtPin1, DHTesp::DHT11);
 lcd.begin(21, 22); //initialization the lcd
  lcd.backlight(); 
  sensors.begin(); //Start the DS18B20 Library
  lcd.setCursor(0,0);
  lcd.print("PH and Temperature");
  lcd.setCursor(0,1);
  lcd.print("Meter Using");
  lcd.setCursor(0, 2);
  lcd.print("Arduino");
  

  
  delay(3000);
  lcd.clear();

}
void loop() {
  
  sensor1Data = dhtSensor1.getTempAndHumidity();  // Read values from sensor 1
  sensors.requestTemperatures(); // Send the command to get temperatures
   float Wtemp = 1.006 * sensors.getTempCByIndex(0);
   
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue,voltage;
  if(millis()-samplingTime > samplingInterval)
  {
      pHArray[pHArrayIndex++]=analogRead(SensorPin);
      if(pHArrayIndex==ArrayLenth)pHArrayIndex=5;
      voltage = avergearray(pHArray, ArrayLenth)*3.85/4095;
      pHValue = -4.9*voltage+Offset;
      samplingTime=millis();
  }
  if(millis() - printTime > printInterval)   //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
  {
    Serial.print("Voltage:");
        Serial.print(voltage, 3);
        Serial.print("    pH value: ");
    Serial.println(pHValue);
   // Serial.println(analogRead(SensorPin));
        digitalWrite(LED,digitalRead(LED)^1);
        printTime=millis();
         // lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("R");
    lcd.setCursor(10,0);
    lcd.print("W");
//    lcd.setCursor(1,1);
//    lcd.print(Etemp);
//    lcd.setCursor(6,1);
//    lcd.write(B11011111);
    lcd.setCursor(1,0);
    lcd.print(sensor1Data.temperature,2);
    lcd.setCursor(11,0);
    lcd.print(Wtemp);
    lcd.setCursor(0,1);
//    lcd.write(B11011111);
//    lcd.setCursor(19,1);
    lcd.print(pHValue);
    lcd.setCursor(10,1);
    lcd.print(sensor1Data.humidity,1);
//    lcd.setCursor(3,3);
//    lcd.print(pHValue);
//    lcd.setCursor(9,3);
//    lcd.print("PH");
    // Serial.println(Etemp);
Serial.println("Temp: " + String(sensor1Data.temperature,2) + "'C Humidity: " + String(sensor1Data.humidity,1) + "%");
     
Serial.println(Wtemp);

  }
}
double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}
