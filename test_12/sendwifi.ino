void sendwifi(void) {
  
  // set the fields with the values
  ThingSpeak.setField(1, Wt);
  ThingSpeak.setField(2, pHValue);
  ThingSpeak.setField(3, voltage);
  ThingSpeak.setField(4, Rt);
   ThingSpeak.setField(5, distance);
  ThingSpeak.setField(6, value);
  ThingSpeak.setField(7, value2);
  ThingSpeak.setField(8, value3);

  
  // write to the ThingSpeak channel 
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  
 


}