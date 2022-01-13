
void setup() {

  // Serial monitor output
  Serial.begin(9600);

  // Beeper alarm
  
  // All done here
  Serial.println("Setup completed");
}

void loop() {
  // Use a C++ unsigned int to read water levle
  uint16_t waterLevel = analogRead(A12);
  Serial.println(waterLevel);

 
  // Slow things down or the serial monitor will go mad
  delay(250);
}
