#include <LiquidCrystal_I2C.h> //Download the library below 
LiquidCrystal_I2C lcd(0x27, 16, 2);




void setup() {
 // initialize serial communication at 9600 bits per second:
 Serial.begin(9600);
 lcd.begin(21, 22);
  //  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("ph woo");
  lcd.setCursor(0, 1);
  lcd.print(">Initializing...");
  delay(2000);
  lcd.clear();
}

// the loop routine runs over and over showing the voltage on A0
void loop() {
 // read the input on analog pin 0:
 int sensorValue = analogRead(35);
 // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
 float voltage = sensorValue * (3.3 / 3936.0);
 // print out the value you read:
 Serial.println(voltage);
 lcd.setCursor(0, 0);
 lcd.print(voltage);
    
 delay(300);
}
