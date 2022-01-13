#include <Ethernet.h>
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros
#include <Arduino.h>
byte mac[] = SECRET_MAC;

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 0, 177);
IPAddress myDns(192, 168, 0, 1);

EthernetClient client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;





#include <GyverTimer.h>
uint32_t myTimer1, myTimer2, myTimer3, myTimer4, myTimer5;
// Пример использования библиотеки GyverButton, все возможности в одном скетче.
// автоматический тик
        // кнопка подключена сюда (BTN_PIN --- КНОПКА --- GND)
#define buttonpolivPin 44   // кнопка подключена сюда (BTN_PIN --- КНОПКА --- GND)

#include "GyverButton.h"
GButton buttonpoliv(buttonpolivPin);

#define polivsamplingInterval   60000ul

#define PolivPomp_Pin 15
bool PompState = 0;
bool PompStart = 0;

#define SensorPin        A12                                                                   // pH meter Analog output to Arduino Analog Input 0
#define Offset           -8.445 ;                                                               // Компенсация смещения
//#define LED              13                                                                   // Номер вывода светодиода, который является индикатором нормальной работы скетча
#define samplingInterval 5                                                                   // Интервал в мс между измерениями
#define printInterval    80                                                                  // Интервал в мс между выводами показаний

#define ArrayLenth       10                                                                   // Количество выборок
int pHArray[ArrayLenth];                                                                      // Массив для определения среднего показания напряжения считанного с датчика
int pHArrayIndex = 5;                                                                         // Индекс элемента массива pHArray значения которого требуется изменить
float voltage;
float pHValue;


static unsigned long samplingTime = millis();                                             // Определяем переменную samplingTime для хранения времени прошедшего с момента старта (переменная создаётся при первом проходе цикла loop и не теряется по его завершении)
static unsigned long printTime    = millis();



#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display


// IMPORTANT: LCDWIKI_KBV LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.

//This program is a demo of clearing screen to display black,white,red,green,blue.

//Set the pins to the correct ones for your development shield or breakout board.
//when using the BREAKOUT BOARD only and using these 8 data lines to the LCD,
//pin usage as follow:
//             CS  CD  WR  RD  RST  D0  D1  D2  D3  D4  D5  D6  D7
//Arduino Uno  A3  A2  A1  A0  A4   8   9   2   3   4   5   6   7
//Arduino Mega A3  A2  A1  A0  A4   8   9   2   3   4   5   6   7

//the 16bit mode only use in Mega.you must modify the mode in the file of lcd_mode.h
//when using the BREAKOUT BOARD only and using these 16 data lines to the LCD,
//pin usage as follow:
//             CS  CD  WR  RD  RST  D0  D1  D2  D3  D4  D5  D6  D7  D8  D9  D10  D11  D12  D13  D14  D15
//Arduino Mega 40  38  39  44  41   37  36  35  34  33  32  31  30  22  23  24   25   26   27   28   29

//Remember to set the pins to suit your display module!

#include "LCDWIKI_GUI.h" //Core graphics library
#include "LCDWIKI_KBV.h" //Hardware-specific library
extern uint8_t BigFontRus[]; //Кирилица
extern uint8_t BigFont[];    //Латиница

//the definiens of 8bit mode as follow:
//if the IC model is known or the modules is unreadable,you can use this constructed function
//LCDWIKI_KBV mylcd(ILI9341,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV mylcd(ILI9325,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV mylcd(ILI9328,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV mylcd(HX8357D,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV mylcd(HX8347G,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV mylcd(HX8347I,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset
LCDWIKI_KBV mylcd(ILI9486, A3, A2, A1, A0, A4); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV mylcd(ST7735S,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset

//if the IC model is not known and the modules is readable,you can use this constructed function
//LCDWIKI_KBV mylcd(240,320,A3,A2,A1,A0,A4);//width,height,cs,cd,wr,rd,reset
//LCDWIKI_KBV mylcd(320,480,A3,A2,A1,A0,A4);//width,height,cs,cd,wr,rd,reset

//the definiens of 16bit mode as follow:
//if the IC model is known or the modules is unreadable,you can use this constructed function
//LCDWIKI_KBV mylcd(ILI9341,40,38,39,44,41); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV mylcd(ILI9325,40,38,39,44,41); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV mylcd(ILI9328,40,38,39,44,41); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV mylcd(HX8357D,40,38,39,44,41); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV mylcd(HX8347G,40,38,39,44,41); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV mylcd(HX8347I,40,38,39,44,41); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV mylcd(ILI9486,40,38,39,44,41); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV mylcd(ILI9488,40,38,39,44,41); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV mylcd(ILI9481,40,38,39,44,41); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV mylcd(ST7735S,40,38,39,44,41); //model,cs,cd,wr,rd,reset

//if the IC model is not known and the modules is readable,you can use this constructed function
//LCDWIKI_KBV mylcd(240,320,40,38,39,44,41);//width,height,cs,cd,wr,rd,reset
//LCDWIKI_KBV mylcd(320,480,40,38,39,44,41);//width,height,cs,cd,wr,rd,reset

#include "TouchScreen.h"

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

//#define LCD_CS A3 // Chip Select goes to Analog 3
//#define LCD_CD A2 // Command/Data goes to Analog 2
//#define LCD_WR A1 // LCD Write goes to Analog 1
//#define LCD_RD A0 // LCD Read goes to Analog 0
//#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin



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
float CurrentState;


#define doliv_Pin 12


float FILLScreen = 2;
float OLDScreen ;



#define levelponicSENS_PIN 36
bool Sensorponic = HIGH;
// Время начала смены
unsigned long SensorStartChange2 = 0;
// Защитный интервал между сменами состояния
unsigned long TIMEOUT2 = 20000;
// Текущее время
unsigned long CurrentTime3 = 0;
float CurrentStatePonic;

#define dolivPonic_Pin 14

#include "Wire.h"
#include "microDS3231.h"
MicroDS3231 rtc;
#include "OneWire.h"
#include "DallasTemperature.h"
#define ONE_WIRE_BUS_1 42
#define ONE_WIRE_BUS_2 43

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
   //Serial.begin(9600);
 buttonpoliv.setDebounce(150);        // настройка антидребезга (по умолчанию 80 мс)
  buttonpoliv.setTimeout(500);        // настройка таймаута на удержание (по умолчанию 500 мс)

  // HIGH_PULL - кнопка подключена к GND, пин подтянут к VCC (BTN_PIN --- КНОПКА --- GND)
  // LOW_PULL  - кнопка подключена к VCC, пин подтянут к GND
  // по умолчанию стоит HIGH_PULL
  buttonpoliv.setType(HIGH_PULL);

  // NORM_OPEN - нормально-разомкнутая кнопка
  // NORM_CLOSE - нормально-замкнутая кнопка
  // по умолчанию стоит NORM_OPEN
  buttonpoliv.setDirection(NORM_OPEN);

  // MANUAL - нужно вызывать функцию tick() вручную
  // AUTO - tick() входит во все остальные функции и опрашивается сама!
  buttonpoliv.setTickMode(AUTO);

  Ethernet.init(33);  // Most Arduino Ethernet hardware
  Serial.begin(115200);  //Initialize serial
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }


  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip, myDns);
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }

  
  ThingSpeak.begin(client);  // Initialize ThingSpeak



  
//  pinMode(Polivbottom_Pin, INPUT);
pinMode(PolivPomp_Pin, OUTPUT);
digitalWrite(PolivPomp_Pin, HIGH);


  
  lcd.init();                      // initialize the lcd
  // Print a message to the LCD.
  lcd.backlight();
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
  mylcd.Init_LCD(); //initialize lcd
  mylcd.Fill_Screen(BLACK);
 


}

void loop()
{
//  buttonpoliv.tick();  // обязательная функция отработки. Должна постоянно опрашиваться
////  if (buttonpoliv.pressed()) digitalWrite(PolivPomp_Pin, LOW);
////  else digitalWrite(PolivPomp_Pin, HIGH);
//     if (buttonpoliv.isSingle()) digitalWrite(PolivPomp_Pin, LOW);    // проверка на один клик
//     else digitalWrite(PolivPomp_Pin, HIGH);
////  if (buttonpoliv.isDouble()) Serial.println("Double");     // проверка на двойной клик
//  if (buttonpoliv.isTriple()) digitalWrite(PolivPomp_Pin, LOW), polivtimer = millis();
//
//  if ( millis() - polivtimer > 60000ul ) digitalWrite(PolivPomp_Pin, HIGH);     // проверка на тройной клик
    wi_fi();
  
  pompa();
  show_tft();
  Show_lcd();
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

  levelponic ();
  read_ppm();
  phRead();
  distance = ultrasonic.read();
  //tft.setFont(&FreeMonoBoldOblique12pt7b);
  //tft.setFont(&FreeSerif9pt7b);

  if (millis() - myTimer1 >= 5000) {
    myTimer1 = millis(); // сбросить таймер
    //  show_tft();
  show_Serial();
    co2();
  };

  if (millis() - myTimer2 >= 1000) {
    myTimer2 = millis(); // сбросить таймер






    sensor_room.requestTemperatures();
    sensor_water.requestTemperatures();
    Wt = sensor_water.getTempCByIndex(0);
    Rt = sensor_room.getTempCByIndex(0);

  };
  //  if (millis() - myTimer3 >= 5000) {
  //    myTimer3 = millis(); // сбросить таймер
  //    tft.fillScreen(BLACK);
  //  };





  if (Wt < 22.5) {
    digitalWrite(PODOGREV_PIN, LOW);
    ioheat = 1;
  }//showmsgXY(110, 40, 2, &FreeSerifItalic18pt7b, "Heater ON");}

  else  {
    (digitalWrite(PODOGREV_PIN, HIGH));
    ioheat = 0;
  }; //{ tft.setTextColor(GREEN); showmsgXY(110, 40, 2, &FreeSerifItalic18pt7b, "Heater OFF")};

//  if (millis() - myTimer3 >= 15000) {
//    myTimer3 = millis(); // сбросить таймер
//    //   mylcd.Fill_Screen(BLACK);
//    //show_Serial();
//  };

  if (millis() - myTimer4 >= 1000) {
    myTimer4 = millis(); // сбросить таймер


    rtc.getTimeString();
    rtc.getDateString();
  };
   if (buttonpoliv.isClick()) Serial.println("Click");         // проверка на один клик
  if (buttonpoliv.isSingle()) Serial.println("Single");       // проверка на один клик
  if (buttonpoliv.isDouble()) Serial.println("Double");       // проверка на двойной клик
  if (buttonpoliv.isTriple()) Serial.println("Triple");       // проверка на тройной клик

  if (buttonpoliv.hasClicks())                                // проверка на наличие нажатий
    Serial.println(buttonpoliv.getClicks());                  // получить (и вывести) число нажатий

  if (buttonpoliv.isPress()) Serial.println("Press");         // нажатие на кнопку (+ дебаунс)
  if (buttonpoliv.isRelease()) Serial.println("Release");     // отпускание кнопки (+ дебаунс)
  if (buttonpoliv.isHolded()) Serial.println("Holded");       // проверка на удержание
  if (buttonpoliv.isHold()) Serial.println("Holding");        // проверка на удержание
  //if (buttonpoliv.state()) Serial.println("Hold");  

}
void yield() {


   if (buttonpoliv.isHold()) PompState = 1; 
   else PompState = 0;
if (buttonpoliv.isSingle() || buttonpoliv.isClick() || buttonpoliv.isPress()) { PompStart = 1; 
myTimer3 = millis();}
 if (millis() - myTimer3 >= polivsamplingInterval)  {PompStart = 0;}


 
  // вращать мотор
}
