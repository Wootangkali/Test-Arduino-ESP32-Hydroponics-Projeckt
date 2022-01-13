
uint32_t myTimer1, myTimer2, myTimer3;
#include "MCUFRIEND_kbv.h"
MCUFRIEND_kbv tft;
#include "TFT_eSPI.h" // Hardware-specific library
#include "SPI.h"// hard-wired for UNO shields anyway.
#include "TouchScreen.h"
#include "Free_Fonts.h"
float Wt = 23;
float Rt = 23;
int ioheat;

int valco2; //co2



//float tdsValue = 0;
int distance;
char *name = "Please Calibrate.";  //edit name of shield
const int XP = 6, XM = A2, YP = A1, YM = 7; //320x480 ID=0x9486
const int TS_LEFT = 920, TS_RT = 173, TS_TOP = 866, TS_BOT = 171;


TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;

#define MINPRESSURE 200
#define MAXPRESSURE 1000

int16_t BOXSIZE;
int16_t PENRADIUS = 1;
uint16_t ID, oldcolor, currentcolor;
uint8_t Orientation = 0;    //PORTRAIT

// Assign human-readable names to some common 16-bit color values:
#define BLACK 0x0000
#define NAVY 0x000F
#define DARKGREEN 0x03E0
#define DARKCYAN 0x03EF
#define MAROON 0x7800
#define PURPLE 0x780F
#define OLIVE 0x7BE0
#define LIGHTGREY 0xC618
#define DARKGREY 0x7BEF
#define BLUE 0x001F
#define GREEN 0x07E0
#define CYAN 0x07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define ORANGE 0xFD20
#define GREENYELLOW 0xAFE5
#define PINK 0xF81F

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>
#include <Fonts/FreeSerifBold12pt7b.h>
#include <Fonts/FreeMonoBoldOblique12pt7b.h>
#include <Fonts/FreeSerif9pt7b.h>
#include <Fonts/FreeSerifItalic18pt7b.h>
#include <Fonts/TomThumb.h>

#include "Adafruit_GFX.h"// hard-wired for UNO shields anyway.


//#define  sensor1      A8                    // Определяем номер аналогового входа, к которому подключен датчик влажности почвы.
//                                           // Датчик инверсный: больше влажность - меньше значение.
//#define  MIN        630                    // Определяем минимальное показание датчика (в воздухе),
//#define  MAX        330                    // определяем максимальное показание датчика (в воде),
//uint16_t sensor1;



#include <Ultrasonic.h>
Ultrasonic ultrasonic(10, 11);

const int PODOGREV_PIN = 13;
//#define RELAY 17
#define SonicPin 11
//Pащита от дребезга контактов, например при волнах, когда работает насос.

// Текущее состояние сенсора
//bool dolivwater = false0
#define DOLIVSENS_PIN 34
bool SensorState = HIGH;
// Время начала смены
unsigned long SensorStartChange = 100;
// Защитный интервал между сменами состояния
unsigned long TIMEOUT = 30;
// Текущее время
unsigned long CurrentTime2 = 0;
#define doliv_Pin 12

float CurrentState;



#define levelponicSENS_PIN 36
bool Sensorponic = HIGH;
// Время начала смены
unsigned long SensorStartChange2 = 0;
// Защитный интервал между сменами состояния
unsigned long TIMEOUT2 = 1000;
// Текущее время
unsigned long CurrentTime3 = 0;
float CurrentStatePonic;

#define dolivPonic_Pin 14


#include "microDS3231.h"
MicroDS3231 rtc;
#include "OneWire.h"
#include "DallasTemperature.h"
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
int analogBufferIndex = 0, copyIndex = 0;
float averageVoltage = 0, tdsValue = 0, temperature = 25;

int minv = 645;//малая влажность
int maxv = 240;//полный полив
int normv = 500;//чуть влажная
int value = 0;//полученное значение
int value2 = 0;//полученное значение
int value3 = 0;//полученное значение
int last_value = 0;//последнее значимое изменение
int value_sdvig = 50; //значимое изменение
//int ralay = 14; //пин реле
int time_work = 10;//время работы помпы в сек
int analogPin = A8;//пин датчика
int analogPin2 = A9;//пин датчика
int analogPin3 = A10;//пин датчика

int second = 0; // секунды
int time_off = 0; // счетчик оставшегося времени
int pause_time = 15; // время отдыха после полива в минутах




void setup(void)
{
  //  pinMode(ralay,HIGH);//настройка реле
  //  digitalWrite(ralay, HIGH);
  pinMode(DOLIVSENS_PIN, INPUT);
  pinMode(PODOGREV_PIN, OUTPUT);
  // Вначале не светим
  pinMode(doliv_Pin, OUTPUT);
  digitalWrite(doliv_Pin, HIGH);

  digitalWrite(PODOGREV_PIN, LOW);
  //  // Сенсор это вход

  pinMode(levelponicSENS_PIN, INPUT);
 
  pinMode(dolivPonic_Pin, OUTPUT);
  digitalWrite(dolivPonic_Pin, HIGH);



  if (!rtc.begin()) {
    Serial.println("DS3231 not found");
    for (;;);
  }
  uint16_t ID = tft.readID();
  // АВТОМАТИЧЕСКАЯ УСТАНОВКА ВРЕМЕНИ
  if (rtc.lostPower()) {            // при потере питания
    //rtc.setTime(COMPILE_TIME);    // установить время компиляции ("тяжёлый" способ!!!)

    // визуально громоздкий, но более "лёгкий" с точки зрения памяти способ установить время компиляции
    rtc.setTime(BUILD_SEC, BUILD_MIN, BUILD_HOUR, BUILD_DAY, BUILD_MONTH, BUILD_YEAR);
  }

  //rtc.setTime(SEC, MIN, HOUR, DAY, MONTH, YEAR);      // установка времени вручную, числами или переменными
  //rtc.setHMSDMY(HOUR, MIN, SEC, DAY, MONTH, YEAR);    // установка времени вручную, более привычный порядок


  pinMode(TdsSensorPin, INPUT);

  //  Serial.println("Dallas Temperature Control Library Demo - TwoPin_DS18B20");

  sensor_room.begin();
  sensor_water.begin();

  uint16_t tmp;
  if (ID == 0xD3D3) ID = 0x9481; //force ID if write-only display
  tft.reset();
  ID = tft.readID();
  tft.begin(ID);
  Serial.begin(9600);

  tft.setRotation(Orientation);
  tft.fillScreen(BLACK);

}

void loop()
{
  //poliv();
  // soil();
  value = analogRead(analogPin);
  value2 = analogRead(analogPin2);
  value3 = analogRead(analogPin3);
  //if (value>(last_value+value_sdvig)||value<(last_value-value_sdvig)){// если last_value отклонился на value_sdvig выводим value в uart
  //  Serial.println(value);
  //  last_value=value;
  //}
  //if ((value>(minv-value_sdvig)) && time_off<1) poliv();//если значение влажности > критическая влажность - 50 и не было недавних поливов
  //// временные функции что бы не играться с таймерами
  //if (second>59)
  //{
  //  second=0;
  //  if (time_off>0) time_off--;
  //}
  level_water();
co2();
 levelponic ();
  read_ppm();
  distance = ultrasonic.read();
  //tft.setFont(&FreeMonoBoldOblique12pt7b);
  //tft.setFont(&FreeSerif9pt7b);

  if (millis() - myTimer1 >= 5000) {
    myTimer1 = millis(); // сбросить таймер
    show_tft();
  };

  if (millis() - myTimer2 >= 5000) {
    myTimer2 = millis(); // сбросить таймер
    show_Serial();
    
    sensor_room.requestTemperatures();
    sensor_water.requestTemperatures();
    Wt = sensor_water.getTempCByIndex(0);
    Rt = sensor_room.getTempCByIndex(0);
     
  };
  if (millis() - myTimer3 >= 5000) {
    myTimer3 = millis(); // сбросить таймер
    tft.fillScreen(BLACK);
  };



  rtc.getTimeString();
  rtc.getDateString();



  if (Wt < 23) {
    digitalWrite(PODOGREV_PIN, LOW);
    ioheat = 1;
  }//showmsgXY(110, 40, 2, &FreeSerifItalic18pt7b, "Heater ON");}

  else  {
    (digitalWrite(PODOGREV_PIN, HIGH));
    ioheat = 0;
  }; //{ tft.setTextColor(GREEN); showmsgXY(110, 40, 2, &FreeSerifItalic18pt7b, "Heater OFF")};


}
