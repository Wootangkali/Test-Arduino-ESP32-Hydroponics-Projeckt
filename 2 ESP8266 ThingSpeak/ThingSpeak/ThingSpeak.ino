#include<ESP8266WiFi.h>
#include"ThingSpeak.h"
#include"DHT.h"

#define Ssid "TP-LINK"
#define PASS "214365Qq"
#define CH_ID 1551807
#define WRITE_APIKEY "VM6V62FL1A2N6OK6"

unsigned long myChannelNumber = CH_ID;
const char * myWriteAPIKey = WRITE_APIKEY;
const char * ssid = Ssid;
const char * pass = PASS;

WiFiClient client;

// DHT22 
#define DHTPIN 14 // номер ножки куда подключать датчик D5
#define DHTTYPE DHT22 //определяем тип датчика

float temperature=0;
float humidity=0;

// Инициализируем DHT сенсор.
DHT dht(DHTPIN, DHTTYPE, 5);

int n=0; // счетчик подключений

void setup() {
delay(1000);
Serial.begin(115200);
WiFi.mode(WIFI_STA);
dht.begin();
ThingSpeak.begin(client);
}

void loop() {
//Читаем температуру и давление
humidity = dht.readHumidity();
temperature = dht.readTemperature();

Serial.print("H=");Serial.println(humidity);
Serial.print("T=");Serial.println(temperature);

while (WiFi.status() != WL_CONNECTED) {
WiFi.begin(ssid, pass);// старт подключения
delay(1000);
n++;
if(n>=10)break;
}
n=0;

int httpCode1 = ThingSpeak.writeField(myChannelNumber, 1,humidity, myWriteAPIKey);
delay(21000);// Wait 30 seconds to update the channel again
int httpCode2 = ThingSpeak.writeField(myChannelNumber, 2,temperature, myWriteAPIKey);
delay(21000);
if((httpCode1 == 200)and (httpCode2 == 200)){
Serial.println("Channel write succeful");
}
else{
Serial.println("No write to channel");
}
}
