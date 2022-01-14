//Header declearation Start
#include <LiquidCrystal_I2C.h> //Library for I2C lcd
#include <OneWire.h> //One wire library
#include <DallasTemperature.h> //Library for DS18B20 Sensor
#include <math.h>// Library for math function 
//Header Declearation End

//Pin Assignment and declearation Start
#define ONE_WIRE_BUS 4 //data pin  DQ pin of DS18B20 connected to digital pin D5
LiquidCrystal_I2C lcd(0x27,16,2);  //set the LCD address to 0x27 for a 20 chars and 4 line display
const int analogPhPin = 35; //PH module pin P0 connected to analog pin A0
const int analogTemPin = 33; //PH module pin T1 connected to analog pin A1

OneWire oneWire(ONE_WIRE_BUS); //Ste up one wire instance
DallasTemperature sensors(&oneWire); //pass one wire reference to DS18B20 library

long phTot, temTot;
float phAvg, temAvg;
int x;
const float C = 21.34; //Constant of straight line (Y = mx + C)
const float m = -5.70; // Slope of straight line (Y = mx + C)
//Pin Assignment and declearation end

// start for generate custom character
byte customChar[] = {
  B00100,
  B00100,
  B11111,
  B00100,
  B00100,
  B00000,
  B11111,
  B00000
};
//End for generate custom character
int phValue;
int phVoltage;
//Setup Function Start 
void setup() {
  Serial.begin(9600);
  dht.begin();
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
//Setup Function End

//Main function Start
void loop() {

  
  phTot = 0;
  temTot = 0;
  phAvg = 0;
  temAvg = 0;

  //taking 10 sample and adding with 10 milli second delay
  for(x=0; x<10 ; x++)
    {
        phTot += analogRead(35);
        temTot += analogRead(33);
        delay(10);
    }
    float temAvg = temTot/10;
    float phAvg = phTot/10;
    float temVoltage = temAvg * (5000.0 / 1023.0); //convert sensor reading into milli volt
    float phVoltage =  phAvg * (5.0 / 1023.0); //convert sensor reading into milli volt

    sensors.requestTemperatures(); // Send the command to get temperatures
    float Etemp = temVoltage*0.1; //convert milli volt to temperature degree Celsius
    float pHValue = phVoltage*m+C;
    float Wtemp = sensors.getTempCByIndex(0);
    float TempDif = fabs(Etemp-Wtemp); //calculating the absolute value of floating
   // lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Env.Tmp.");
    lcd.setCursor(12,0);
    lcd.print("Sol.Tmp.");
    lcd.setCursor(1,1);
    lcd.print(Etemp);
    lcd.setCursor(6,1);
    lcd.write(B11011111);
    lcd.setCursor(7,1);
    lcd.print("C");
    lcd.setCursor(13,1);
    lcd.print(Wtemp);
    lcd.setCursor(18,1);
    lcd.write(B11011111);
    lcd.setCursor(19,1);
    lcd.print("C");
    lcd.setCursor(0,2);
    lcd.print("PH Value of Solution");
    lcd.setCursor(3,3);
    lcd.print(pHValue);
    lcd.setCursor(9,3);
    lcd.print("PH");
     Serial.println(Etemp);
 Serial.println(Wtemp);
 Serial.println(phValue, 2);
 Serial.println(phVoltage, 2);
    if (TempDif<= 5)
    {
      lcd.setCursor(11,3);
     // lcd.write(customChar);
      lcd.setCursor(14,3);
      lcd.print("0.1PH");
      }

    if (TempDif> 5)
    {
      lcd.setCursor(11,3);
//      lcd.write(customChar);
      lcd.setCursor(14,3);
      lcd.print("0.2PH");
      }
      delay(1000);
     // Serial.print("sensor = ");


}
