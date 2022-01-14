

//download libraries
//https://www.electroniclinic.com/arduino-libraries-download-and-projects-they-are-used-in-project-codes/

#include <Wire.h>

#include <BlynkSimpleEsp32.h>
#include <SimpleTimer.h>

#include <LCDIC2.h>

LCDIC2 lcd(0x27, 16, 2);
// You should get Auth Token in the Blynk App.
char auth[] = "gFGwWD54NIHyaVnN6CqS8tQzKEEmkJqW";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "TP-LINK";
char pass[] = "214365Qq";

SimpleTimer timer;

float calibration_value = 20.24 - 0.7; //21.34 - 0.7
int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10],temp;

float ph_act;
// for the OLED display


void setup() 
{
  Wire.begin();
 Serial.begin(9600);
 
  if (lcd.begin()) lcd.print("Hello, World!");

 Blynk.begin(auth, ssid, pass);
  

 
timer.setInterval(5000L, display_pHValue);
}
void loop() {
  Blynk.run();
 // timer.run(); // Initiates SimpleTimer
 for(int i=0;i<10;i++) 
 { 
 buffer_arr[i]=analogRead(35);
 delay(30);
 }
 for(int i=0;i<9;i++)
 {
 for(int j=i+1;j<10;j++)
 {
 if(buffer_arr[i]>buffer_arr[j])
 {
 temp=buffer_arr[i];
 buffer_arr[i]=buffer_arr[j];
 buffer_arr[j]=temp;
 }
 }
 }
 avgval=0;
 for(int i=2;i<8;i++)
 avgval+=buffer_arr[i];
 float volt=(float)avgval*3.3/4096.0/6;  
 //Serial.print("Voltage: ");
 //Serial.println(volt);
  ph_act = -5.70 * volt + calibration_value;

 Serial.print("pH Val: ");
 Serial.println(ph_act);
 Serial.println(temp);
  Blynk.virtualWrite(V2,ph_act);
 delay(1000);
 lcd.clear();
}

void display_pHValue()
{
lcd.setCursor(0, 0);
lcd.print(ph_act);
lcd.setCursor(0, 1);
lcd.print(temp);
     // display on Oled display

   // Oled display
 // display.clearDisplay();
 // display.setTextSize(2);
//  display.setCursor(0,0); // column row
//  display.print("pH:");

//  display.setTextSize(2);
 // display.setCursor(55, 0);
//display.print(ph_act);

/*
    display.setTextSize(2);
  display.setCursor(0,30);
  display.print("EC:");

  display.setTextSize(2);
  display.setCursor(60, 30);
  display.print(345);
  display.setCursor(95, 50);
*/
// display.display();
}
