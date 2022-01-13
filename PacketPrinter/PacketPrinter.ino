/**
 * Packet Printer - prints Ethernet and IPv6 packet headers received to Serial
 *
 * Uses a static MAC address, please update with your own.
 *
 * Get your own Random Locally Administered MAC Address here:
 * https://www.hellion.org.uk/cgi-bin/randmac.pl
 *
 * @file
 */
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros
#include <Ethernet.h>
#include <EtherSia.h>

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

// Initialize our values
int number1 = 0;
int number2 = random(0,100);
int number3 = random(0,100);
int number4 = random(0,100);


EthernetClient client;
/** Ethernet Interface with ENC28J60 (with Chip Select connected to Pin 10) */
EtherSia_ENC28J60 ether(10);

void setup() {
    MACAddress macAddress("e2:d7:66:39:6b:5e");

    // Setup serial port for debugging
    Serial.begin(38400);
    Serial.println("[EtherSia PacketPrinter]");

    Serial.print("Our MAC is: ");
    macAddress.println();

    if (ether.begin(macAddress) == false) {
        Serial.println("Failed to configure Ethernet");
    }
    ThingSpeak.begin(client);  // Initialize ThingSpeak
}


void loop() {
    
  
  // write to the ThingSpeak channel 
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
   ThingSpeak.setField(1, number1);
  ThingSpeak.setField(2, number2);
  ThingSpeak.setField(3, number3);
  ThingSpeak.setField(4, number4);

  // change the values
  number1++;
  if(number1 > 99){
    number1 = 0;
  }
  number2 = random(0,100);
  number3 = random(0,100);
  number4 = random(0,100);
  
    if (ether.receivePacket()) {
        IPv6Packet& packet = ether.packet();

        Serial.print("Source MAC: ");
        packet.etherSource().println();

        Serial.print("Destination MAC: ");
        packet.etherDestination().println();

        Serial.print("Source Address: ");
        packet.source().println();

        Serial.print("Destination Address: ");
        packet.destination().println();

        Serial.print("Protocol: ");
        Serial.println(packet.protocol(), DEC);

        Serial.print("Length: ");
        Serial.println(packet.payloadLength(), DEC);

        Serial.println();
    }
  
}
