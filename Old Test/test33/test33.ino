#include "Adafruit_GFX.h"
#include "MCUFRIEND_kbv.h"
MCUFRIEND_kbv tft;
#include "Fonts/FreeSans9pt7b.h"
#include "Fonts/FreeSans12pt7b.h"
#include "Fonts/FreeSerif12pt7b.h"
#include "FreeDefaultFonts.h"
#define PI 3.1415926535897932384626433832795
#define BLACK   0x0000
#define RED     0xF800
#define GREEN   0x07E0
#define WHITE   0xFFFF
#define GREY    0x8410
int col[8];
uint32_t myTimer1, myTimer2, myTimer3;
#define RELAY 17   

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS_1 40
#define ONE_WIRE_BUS_2 41

OneWire oneWire_in(ONE_WIRE_BUS_1);
OneWire oneWire_out(ONE_WIRE_BUS_2);

DallasTemperature sensor_room(&oneWire_in);
DallasTemperature sensor_water(&oneWire_out);

#define TdsSensorPin A6
#define VREF 5.0 // analog reference voltage(Volt) of the ADC
#define SCOUNT 30 // sum of sample point
int analogBuffer[SCOUNT]; // store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0,copyIndex = 0;
float averageVoltage = 0,tdsValue = 0,temperature = 25;
float Wt;

#include <microDS3231.h>
MicroDS3231 rtc;


void showmsgXY(int x, int y, int sz, const GFXfont *f, const char *msg)
{
int16_t x1, y1;
uint16_t wid, ht;
tft.setFont(f);
tft.setCursor(x, y);
tft.setTextColor(0x0000);
tft.setTextSize(sz);
tft.print(msg);
}
void setup() {
Serial.begin(9600);
//tft.reset();
uint16_t ID = tft.readID();
tft.begin(ID);
tft.setRotation(1);
tft.invertDisplay(true);
tft.fillScreen(0xffff);

sensor_room.begin();
    sensor_water.begin();
pinMode(RELAY, OUTPUT); 
pinMode(TdsSensorPin,INPUT);

  // проверка наличия модуля на линии i2c
  if (!rtc.begin()) {
    Serial.println("DS3231 not found");
    for(;;);
  }
  
  // АВТОМАТИЧЕСКАЯ УСТАНОВКА ВРЕМЕНИ  
  if (rtc.lostPower()) {            // при потере питания
    //rtc.setTime(COMPILE_TIME);    // установить время компиляции ("тяжёлый" способ!!!)
    
    // визуально громоздкий, но более "лёгкий" с точки зрения памяти способ установить время компиляции
    rtc.setTime(BUILD_SEC, BUILD_MIN, BUILD_HOUR, BUILD_DAY, BUILD_MONTH, BUILD_YEAR);
  }

  //rtc.setTime(SEC, MIN, HOUR, DAY, MONTH, YEAR);      // установка времени вручную, числами или переменными  
  //rtc.setHMSDMY(HOUR, MIN, SEC, DAY, MONTH, YEAR);    // установка времени вручную, более привычный порядок


showmsgXY(170, 250, 2, &FreeSans9pt7b, "Loading...");
col[0] = tft.color565(155, 0, 50);
col[1] = tft.color565(170, 30, 80);
col[2] = tft.color565(195, 60, 110);
col[3] = tft.color565(215, 90, 140);
col[4] = tft.color565(230, 120, 170);
col[5] = tft.color565(250, 150, 200);
col[6] = tft.color565(255, 180, 220);
col[7] = tft.color565(255, 210, 240);



for (int i = 8; i > 0; i--) {
tft.fillCircle(240 + 40 * (cos(-i * PI / 4)), 120 + 40 * (sin(-i * PI / 4)), 10, col[0]); delay(15);
tft.fillCircle(240 + 40 * (cos(-(i + 1)*PI / 4)), 120 + 40 * (sin(-(i + 1)*PI / 4)), 10, col[1]); delay(15);
tft.fillCircle(240 + 40 * (cos(-(i + 2)*PI / 4)), 120 + 40 * (sin(-(i + 2)*PI / 4)), 10, col[2]); delay(15);
tft.fillCircle(240 + 40 * (cos(-(i + 3)*PI / 4)), 120 + 40 * (sin(-(i + 3)*PI / 4)), 10, col[3]); delay(15);
tft.fillCircle(240 + 40 * (cos(-(i + 4)*PI / 4)), 120 + 40 * (sin(-(i + 4)*PI / 4)), 10, col[4]); delay(15);
tft.fillCircle(240 + 40 * (cos(-(i + 5)*PI / 4)), 120 + 40 * (sin(-(i + 5)*PI / 4)), 10, col[5]); delay(15);
tft.fillCircle(240 + 40 * (cos(-(i + 6)*PI / 4)), 120 + 40 * (sin(-(i + 6)*PI / 4)), 10, col[6]); delay(15);
tft.fillCircle(240 + 40 * (cos(-(i + 7)*PI / 4)), 120 + 40 * (sin(-(i + 7)*PI / 4)), 10, col[7]); delay(15);
};
//tft.reset();
delay(2000); 
tft.invertDisplay(false);
tft.fillScreen(BLACK);
}
void loop() {
//  uint16_t ID = tft.readID();
//tft.begin(ID);
//tft.setRotation(1);
//  tft.invertDisplay(false);
   Wt = sensor_water.getTempCByIndex(0);
  Serial.print("Temp:");
    sensor_room.requestTemperatures();
    sensor_water.requestTemperatures();
   

    Serial.print("room: ");
    Serial.println(sensor_room.getTempCByIndex(0));

    Serial.print("Water: ");
    Serial.println(sensor_water.getTempCByIndex(0));
//       

// tft.setBackColor(0, 0, 20 );
 tft.setTextColor(GREEN);
  tft.setFont(&FreeSevenSegNumFont);                           
  tft.printNumber(Wt, 1, 330, 5); 
//      tft.setCursor(5, 5);
//      tft.setTextSize(2);    
//      tft.setFont(&FreeSevenSegNumFont); 
// //tft.setTextColor(WHITE,BLACK);
// tft.print(sensor_water.getTempCByIndex(0));
//showmsgXY(5, 5, 1, &FreeSevenSegNumFont,sensor_water.getTempCByIndex(0));

if (Wt > 30) digitalWrite(RELAY, HIGH),Serial.println("Water heat ON ");
else if (Wt < 30) digitalWrite(RELAY, LOW),Serial.println("Water heat OFF");   

static unsigned long analogSampleTimepoint = millis();
if(millis()-analogSampleTimepoint > 40U) //every 40 milliseconds,read the analog value from the ADC
{
analogSampleTimepoint = millis();
analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin); //read the analog value and store into the buffer
analogBufferIndex++;
if(analogBufferIndex == SCOUNT)
analogBufferIndex = 0;
}
static unsigned long printTimepoint = millis();
if(millis()-printTimepoint > 800U)
{
printTimepoint = millis();
for(copyIndex=0;copyIndex<SCOUNT;copyIndex++)
analogBufferTemp[copyIndex]= analogBuffer[copyIndex];
averageVoltage = getMedianNum(analogBufferTemp,SCOUNT) * (float)VREF/ 1024.0; // read the analog value more stable by the median filtering algorithm, and convert to voltage value
float compensationCoefficient=1.0+0.02*(temperature-25.0); //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
float compensationVolatge=averageVoltage/compensationCoefficient; //temperature compensation
tdsValue=(133.42*compensationVolatge*compensationVolatge*compensationVolatge - 255.86*compensationVolatge*compensationVolatge + 857.39*compensationVolatge)*0.5; //convert voltage value to tds value
//Serial.print("voltage:");
//Serial.print(averageVoltage,2);
//Serial.print("V ");
Serial.println("TDS Value:");
Serial.print(tdsValue,0);
Serial.println("ppm");
//  if (millis() - myTimer3 >= 1000) {
//    myTimer3 = millis(); // сбросить таймер
//  Serial.print(rtc.getHours());
//  Serial.print(":");
//  Serial.print(rtc.getMinutes());
//  Serial.print(":");
//  Serial.print(rtc.getSeconds());
//  Serial.print(" ");
//  Serial.print(rtc.getDay());
//  Serial.print(" ");
//  Serial.print(rtc.getDate());
//  Serial.print("/");
//  Serial.print(rtc.getMonth());
//  Serial.print("/");
//  Serial.println(rtc.getYear());
//  
//  Serial.println(rtc.getTemperatureFloat());  
//  //Serial.println(rtc.getTemperature());
//  Serial.println(rtc.getTimeString());
//  Serial.println(rtc.getDateString());

  // работа с char
  char time[8];
  rtc.getTimeChar(time);  // записать в массив time
  Serial.println(time);
  
  char date[10];
  rtc.getDateChar(date);
  Serial.println(date);
//  }


}
}
int getMedianNum(int bArray[], int iFilterLen)
{
int bTab[iFilterLen];
for (byte i = 0; i<iFilterLen; i++)
bTab[i] = bArray[i];
int i, j, bTemp;
for (j = 0; j < iFilterLen - 1; j++)
{
for (i = 0; i < iFilterLen - j - 1; i++)
{
if (bTab[i] > bTab[i + 1])
{
bTemp = bTab[i];
bTab[i] = bTab[i + 1];
bTab[i + 1] = bTemp;
}
}
}
if ((iFilterLen & 1) > 0)
bTemp = bTab[(iFilterLen - 1) / 2];
else
bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
return bTemp;

}


}
