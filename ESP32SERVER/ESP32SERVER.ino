/*
   Copyright (c) 2019 Boot&Work Corp., S.L. All rights reserved

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

//ESP32 code

// Load Wi-Fi library
#include <WiFi.h>

// Replace with your network credentials
const char* ssid     = "ESPLINK";
const char* password = "398958Qq";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String outputQ0_0State = "on";
String outputQ0_1State = "on";

void setup() {
  Serial.begin(115200UL);
  Serial2.begin(9600L);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  server.begin();
}

void loop(){
  int var;
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /Q0_0/on") >= 0) {
              var=1;//1=Q0_0 on
              Serial.println("1");
              outputQ0_0State="on";
              Serial2.write(1);
            } 
            else if (header.indexOf("GET /Q0_0/off") >= 0) {
              var=0;//0=Q0_0 off
              Serial.println("0");
              outputQ0_0State="off";
              Serial2.write(0);
            } 
            else if (header.indexOf("GET /Q0_1/on") >= 0) {
              var=9;//9=Q0_1 on
              Serial.println("9");
              outputQ0_1State="on";
              Serial2.write(9);
            } 
            else if (header.indexOf("GET /Q0_1/off") >= 0) {
              var=8;//8=Q0_1 off
              Serial.println("8");              
              outputQ0_1State="off";
              Serial2.write(8);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO Q0_0  
            client.println("<p>GPIO Q0_0 - State " + outputQ0_0State + "</p>");
            // If the Q0_0 is off, it displays the ON button       
            if (outputQ0_0State=="off") {
              client.println("<p><a href=\"/Q0_0/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/Q0_0/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO Q0_1  
            client.println("<p>GPIO Q0_1 - State " + outputQ0_1State + "</p>");
            // If the Q0_1 is off, it displays the ON button       
            if (outputQ0_1State=="off") {
              client.println("<p><a href=\"/Q0_1/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/Q0_1/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
