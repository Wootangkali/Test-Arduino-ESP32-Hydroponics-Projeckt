void show_Serial()
{
  Serial.print(rtc.getTimeString());
  Serial.println(rtc.getDateString());
  Serial.print("TDS Value:");
  Serial.println(tdsValue, 0);
  Serial.println("ppm");

  Serial.print("room: ");
  Serial.println(Rt);

  Serial.print("Water: ");
  Serial.println(Wt);
  //    Serial.println(F("Most Touch Screens use pins 6, 7, A1, A2"));
  //    Serial.println(F("But they can be in ANY order"));
  //    Serial.println(F("e.g. right to left or bottom to top"));
  //    Serial.println(F("or wrong direction"));
  //    Serial.println(F("Edit name and calibration statements\n"));
  //    Serial.println(name);
  //    Serial.print(F("ID=0x"));
  //    Serial.println(ID, HEX);
  //    Serial.println("Screen is " + String(tft.width()) + "x" + String(tft.height()));
  //    Serial.println("Calibration is: ");
  //    Serial.println("LEFT = " + String(TS_LEFT) + " RT  = " + String(TS_RT));
  //    Serial.println("TOP  = " + String(TS_TOP)  + " BOT = " + String(TS_BOT));
  //    Serial.println("Wiring is always PORTRAIT");
  //    Serial.println("YP=" + String(YP)  + " XM=" + String(XM));
  //    Serial.println("YM=" + String(YM)  + " XP=" + String(XP));
}
