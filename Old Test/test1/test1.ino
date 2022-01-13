#include "Adafruit_GFX.h"
#include "MCUFRIEND_kbv.h"
MCUFRIEND_kbv tft;
#include "Fonts/FreeSans9pt7b.h"
#include "Fonts/FreeSans12pt7b.h"
#include "Fonts/FreeSerif12pt7b.h"
#include "FreeDefaultFonts.h"
#define PI 3.1415926535897932384626433832795
int col[8];

//ppm icl
#define TdsSensorPin A6
#define VREF 5.0 // analog reference voltage(Volt) of the ADC
#define SCOUNT 30 // sum of sample point
int analogBuffer[SCOUNT]; // store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0,copyIndex = 0;
float averageVoltage = 0,tdsValue = 0,temperature = 23;

//temp inc
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS_1 40
#define ONE_WIRE_BUS_2 41

OneWire oneWire_in(ONE_WIRE_BUS_1);
OneWire oneWire_out(ONE_WIRE_BUS_2);

DallasTemperature sensor_room(&oneWire_in);
DallasTemperature sensor_water(&oneWire_out);
float Wc = sensor_water.getTempCByIndex(0);

#define RELAY 17   


#include <microDS3231.h>
MicroDS3231 rtc;


byte time; date;


uint32_t myTimer1, myTimer2, myTimer3;











void setup() {
tft.reset();


rtc.setTime(BUILD_SEC, BUILD_MIN, BUILD_HOUR, BUILD_DAY, BUILD_MONTH, BUILD_YEAR);
 
pinMode(RELAY, OUTPUT); 
pinMode(TdsSensorPin,INPUT);

sensor_room.begin();
    sensor_water.begin();


Serial.begin(9600);
uint16_t ID = tft.readID();
tft.begin(ID);
tft.setRotation(1);
tft.invertDisplay(true);
tft.fillScreen(0xffff);
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
}
void loop() {
//void loop(void) {
 // каждую секунду
  if (millis() - myTimer3 >= 1000) {
    myTimer3 = millis(); // сбросить таймер
   ppm();
  }

  if (millis() - myTimer2 >= 200) {
    myTimer2 = millis(); // сбросить таймер
    temp();
  }

 if (millis() - myTimer3 >= 1000) {
    myTimer3 = millis(); // сбросить таймер
  relay();
  }
  
  // каждую секунду
  if (millis() - myTimer3 >= 1000) {
    myTimer3 = millis(); // сбросить таймер
    Time();
  } 
   if (millis() - myTimer3 >= 1000) {
    myTimer3 = millis(); // сбросить таймер
    printtime();
  } 
}
