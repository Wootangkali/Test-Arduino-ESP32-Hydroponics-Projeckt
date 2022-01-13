

/*
  Adapted from Example from ThingSpeak Library (Mathworks)
  
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-thingspeak-publish-arduino/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <WiFi.h>
#include "ThingSpeak.h"


const char* ssid = "TP-LINK";   // your network SSID (name) 
const char* password = "214365Qq";   // your network password

WiFiClient  client;

unsigned long myChannelNumber = 1628917;
const char * myWriteAPIKey = "R5VFO73Q37GESE3V";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

// Variable to hold temperature readings
float temperatureC;
float humidity;
float pressure;
//uncomment if you want to get temperature in Fahrenheit
//float temperatureF;


void setup() {
  Serial.begin(115200);  //Initialize serial
  
     
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    
    // Connect or reconnect to WiFi
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }
 }}
    // Ge
