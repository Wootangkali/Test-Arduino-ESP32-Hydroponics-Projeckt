
#define RELAY 17   

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS_1 40
#define ONE_WIRE_BUS_2 41

OneWire oneWire_in(ONE_WIRE_BUS_1);
OneWire oneWire_out(ONE_WIRE_BUS_2);

DallasTemperature sensor_room(&oneWire_in);
DallasTemperature sensor_water(&oneWire_out);

void setup() {

 Serial.begin(9600);
    Serial.println("Dallas Temperature Control Library Demo - TwoPin_DS18B20");

    sensor_room.begin();
    sensor_water.begin();
pinMode(RELAY, OUTPUT); 
}
void loop() {
  int Wc = sensor_water.getTempCByIndex(0);
  Serial.print("Requesting temperatures...");
    sensor_room.requestTemperatures();
    sensor_water.requestTemperatures();
    Serial.println(" done");

    Serial.print("room: ");
    Serial.println(sensor_room.getTempCByIndex(0));

    Serial.print("Water: ");
    Serial.println(sensor_water.getTempCByIndex(0));
if (Wc > 30) digitalWrite(RELAY, HIGH),Serial.print("Water ON ");
else if (Wc < 30) digitalWrite(RELAY, LOW),Serial.print("Water OFF");   
         
}
