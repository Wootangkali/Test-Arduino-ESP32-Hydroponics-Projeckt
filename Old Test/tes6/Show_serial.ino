void show_Serial(void)
{
  Serial.print(rtc.getTimeString());
  Serial.println(rtc.getDateString());
  Serial.print("TDS Value:");
  Serial.println(tdsValue, 0);
  //Serial.println("ppm");

  Serial.print("room: ");
  Serial.println(Rt);

  Serial.print("Water: ");
  Serial.println(Wt);

  Serial.print("Heater water");
  Serial.println(ioheat);
  Serial.print("Water up");
  Serial.println(SensorState);
  Serial.print("Distance in CM: ");
  Serial.println(distance);

Serial.print(value);
Serial.println(value2);
Serial.println(value3);

}
