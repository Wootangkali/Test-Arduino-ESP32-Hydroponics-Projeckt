#include <SoftwareSerial.h>

SoftwareSerial Serial1(18, 19); // RX, TX
#define WIFI_SERIAL    Serial1
 #include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros
#define SECRET_MAC {0x90, 0xA2, 0xDA, 0x10, 0x40, 0x4F}

#define SECRET_CH_ID 155180      // replace 0000000 with your channel number
#define SECRET_WRITE_APIKEY "EZVNSKEUD4RWXAAD"   // replace XYZ with your channel write API Key
int keyIndex = 2;            // your network key Index number (needed only for WEP)
unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

// Initialize our values
int number1 = 0;
int number2 = random(0,100);
int number3 = random(0,100);
int number4 = random(0,100);
String myStatus = "";

void setup()
{
  // открываем последовательный порт для мониторинга действий в программе
  // и передаём скорость 9600 бод
  Serial.begin(9600);
  while (!Serial) {
  // ждём, пока не откроется монитор последовательного порта
  // для того, чтобы отследить все события в программе
  }
  Serial.print("Serial init OK\r\n");
  // открываем Serial-соединение с Wi-Fi модулем на скорости 115200 бод
  WIFI_SERIAL.begin(115200);
  ThingSpeak.begin(Serial1);  // Initialize ThingSpeak
}
 
void loop()
{
  // если приходят данные из Wi-Fi модуля - отправим их в порт компьютера
  if (WIFI_SERIAL.available()) {
    Serial.write(WIFI_SERIAL.read());
  }
  // если приходят данные из компьютера - отправим их в Wi-Fi модуль
  if (Serial.available()) {
    WIFI_SERIAL.write(Serial.read());
  }
   // set the fields with the values
  ThingSpeak.setField(1, number1);
  ThingSpeak.setField(2, number2);
  ThingSpeak.setField(3, number3);
  ThingSpeak.setField(4, number4);

  // figure out the status message
  if(number1 > number2){
    myStatus = String("field1 is greater than field2"); 
  }
  else if(number1 < number2){
    myStatus = String("field1 is less than field2");
  }
  else{
    myStatus = String("field1 equals field2");
  }
  
  // set the status
  ThingSpeak.setStatus(myStatus);
  
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  
  // change the values
  number1++;
  if(number1 > 99){
    number1 = 0;
  }
  number2 = random(0,100);
  number3 = random(0,100);
  number4 = random(0,100);
}
