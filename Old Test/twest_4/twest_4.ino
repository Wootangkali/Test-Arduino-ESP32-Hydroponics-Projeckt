//#include <UTFT.h>  
const extern uint8_t SevenSegNumFontPlusPlus[];
const extern uint8_t SevenSeg_XXXL[];
//UTFT myGLCD(0,   A2,A1,A3,A4,A0);           // тип дисплея 3,95 UNO  (480x320 chip ILI9327)
#include <UTFTGLUE.h>              //use GLUE class and constructor
UTFTGLUE myGLCD(0,A2,A1,A3,A4,A0); //all dummy args
#define RELAY 17   
#include <microDS3231.h>
MicroDS3231 rtc;
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
void setup() {
   myGLCD.InitLCD();            //инициируем дисплей 
  myGLCD.clrScr(); 
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


pinMode(TdsSensorPin,INPUT);
 Serial.begin(9600);
    Serial.println("Dallas Temperature Control Library Demo - TwoPin_DS18B20");

    sensor_room.begin();
    sensor_water.begin();
pinMode(RELAY, OUTPUT); 
 myGLCD.fillScr(0, 0, 20  );    
}
void loop() {
  int Wt = sensor_water.getTempCByIndex(0);
 // Serial.print("Requesting temperatures...");
    sensor_room.requestTemperatures();
    sensor_water.requestTemperatures();
  //  Serial.println(" done");

    Serial.print("room: ");
    Serial.println(sensor_room.getTempCByIndex(0));

    Serial.print("Water: ");
    Serial.println(sensor_water.getTempCByIndex(0));
if (Wt > 30) digitalWrite(RELAY, HIGH),Serial.print("Water heatON ");
else if (Wt < 30) digitalWrite(RELAY, LOW),Serial.print("Water heat OFF");   
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

  // работа с char
  char time[8];
  rtc.getTimeChar(time);  // записать в массив time
  Serial.println(time);
  
  char date[10];
  rtc.getDateChar(date);
  Serial.println(date);

   myGLCD.setBackColor(0, 0, 20 );
  myGLCD.setColor(128, 0, 128);
  myGLCD.setFont(BigFont);
 // myGLCD.setFont(SevenSegNumFontPlusPlus);                           
  myGLCD.printNumF(Wt, 5, 5, 5); 
}
