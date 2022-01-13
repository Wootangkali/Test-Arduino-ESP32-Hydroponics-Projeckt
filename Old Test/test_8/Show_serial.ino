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
  Serial.print("Water doliv");
  Serial.println(SensorState);
  Serial.print("Distance in CM: ");
  Serial.println(distance);
  
Serial.print("CO2    ");  
Serial.println(valco2,DEC);//Print the value to serial port

Serial.print("1EL'");
Serial.println(value);
Serial.print("2EL'");
Serial.println(value2);
Serial.print("3EL'");
Serial.println(value3);

Serial.print("Doliv Ponic  ");
Serial.println(Sensorponic);

                                             // Выполняем код в теле оператора if через каждые printInterval мс
    Serial.println("Voltage:");                                                             // Выводим надпись "Voltage:"
    Serial.println(voltage, 4);                                                             // Выводим среднее напряжение
    Serial.println("    pH value: ");                                                       // Выводим надпись "    pH value: "
    Serial.println(pHValue, 4);                                                           // Выводим значение pH
    // digitalWrite(LED,digitalRead(LED)^1);                                                 // Меняем состояние светодиода
   


}
