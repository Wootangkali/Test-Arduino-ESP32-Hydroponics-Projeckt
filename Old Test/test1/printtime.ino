  void printtime() {
   Serial.println(time);
      Serial.println(date);



Serial.print("TDS Value:");
Serial.print(tdsValue,0);
Serial.println("ppm");


Serial.print("room: ");
    Serial.println(sensor_room.getTempCByIndex(0));

    Serial.print("Water: ");
    Serial.println(sensor_water.getTempCByIndex(0));

  }
  
