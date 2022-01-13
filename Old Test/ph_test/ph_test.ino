int pH_Value; 
float Voltage;

void setup() 
{ 
  Serial.begin(9600);
  pinMode(pH_Value, INPUT); 
} 
 
void loop() 
{ 
  pH_Value = analogRead(A12); 
  Voltage = pH_Value * (5.07 / 1023.0); 
  Serial.println(Voltage); 
  delay(500); 
}
