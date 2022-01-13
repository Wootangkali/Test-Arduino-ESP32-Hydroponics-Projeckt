void show_tft(void)
{
  //mylcd.Set_Text_Mode(BigFontRus);
  //if (ioheat != ioheat) { mylcd.Fill_Screen(BLACK);}
  //if (SensorState != SensorState) { mylcd.Fill_Screen(BLACK);}
  //if (Sensorponic != Sensorponic) { mylcd.Fill_Screen(BLACK);}




  mylcd.Set_Text_colour(GREEN);
  mylcd.Set_Text_Size(3);
  mylcd.Set_Text_Back_colour(BLACK);
  //         mylcd.Set_Text_Mode(1);
  //char time[8];
  // rtc.getTimeChar(time);
  // char date[10];
  // rtc.getDateChar(date);
  mylcd.Print_String(String(rtc.getDateString()), 175, 0);
  mylcd.Print_String(String(rtc.getTimeString()), 175, 35);
  // if (ioheat == 1) {tft.setTextColor(RED);show_heater(110, 40, 2, &FreeSerifItalic18pt7b, "Heater ON");}
  //
  // else{tft.setTextColor(GREEN); show_heater(110, 40, 2, &FreeSerifItalic18pt7b, "Heater OFF");};
  //// tft.setTextColor(GREEN);
  //
  //
  //if (SensorState == 0) {tft.setTextColor(RED);show_heater(120, 95, 2, &FreeSerifItalic18pt7b, "Doliv ON");}
  //
  //  else{tft.setTextColor(GREEN); show_heater(120, 95, 2, &FreeSerifItalic18pt7b, "Doliv OFF");};
  //// tft.setTextColor(GREEN);
  //
  //
  //if (Sensorponic == 0) {tft.setTextColor(RED);show_heater(120, 130, 1, &FreeSerif12pt7b, "PonDoliv ON");}
  //
  //  else{tft.setTextColor(GREEN); show_heater(120, 130, 1, &FreeSerif12pt7b, "PonDoliv OFF");};
  //// tft.setTextColor(GREEN);
  //
  //
  //   tft.setFont(&FreeSerif9pt7b);
  //   // tft.fillScreen(BLACK);
  //  tft.setCursor(3, 15);
  //  tft.setTextSize(1);
  //  tft.setTextColor(YELLOW, BLACK);
  //  tft.println("R");
  //  tft.setCursor(23, 15);
  //  tft.print(Rt);
  //
  //  tft.setTextColor(BLUE, BLACK);
  //  tft.setCursor(3, 35);
  //  tft.println("W");
  //  tft.setCursor(23, 35);
  //  tft.print(Wt);
  //
  // tft.setTextColor(CYAN, BLACK);
  //  tft.setCursor(3, 60);
  //  tft.print("PPM");
  //  tft.setCursor(43, 60);
  // tft.print(tdsValue, 0);
  //
  //
  // tft.setTextColor( MAGENTA, BLACK);
  //  tft.setCursor(3, 80);
  //  tft.print("Distance");
  //  tft.setCursor(85, 80);
  // tft.print(distance);
  //
  //
  //
  //
  //
  // tft.setFont(&FreeSerif9pt7b);
  //tft.setTextSize(2);
  // tft.setTextColor( GREENYELLOW, BLACK);
  //  tft.setCursor(3, 125);
  //  tft.print("1");
  //  tft.setCursor(33, 125);
  // tft.print(value);
  //
  //  tft.setTextColor( WHITE, BLACK);
  //  tft.setCursor(3, 160);
  //  tft.print("2");
  //  tft.setCursor(33, 160);
  // tft.print(value2);
  //
  //  tft.setTextColor( ORANGE, BLACK);
  //  tft.setCursor(3, 190);
  //  tft.print("3");
  //  tft.setCursor(33, 190);
  // tft.print(value3);

  //  mylcd.Set_Text_Size(2);;
  //  mylcd.Set_Text_colour(YELLOW);
  //  mylcd.setCursor();
  mylcd.Set_Text_Size(3);
  mylcd.Set_Text_colour(YELLOW);
  mylcd.Print_String("Rt  " + String(Rt), 0, 0);

  mylcd.Set_Text_colour(YELLOW);
  mylcd.Print_String("Wt  " + String(Wt), 0, 25);

  mylcd.Set_Text_colour(MAGENTA);
  mylcd.Print_String("PPM  " + String(tdsValue, 0), 0, 50);


  mylcd.Set_Text_colour(NAVY);
  mylcd.Print_String("Sonic" +    String(distance), 0, 75);

  mylcd.Set_Text_colour(ORANGE);
  mylcd.Print_String("1PON-" + String(value), 0, 100);

  mylcd.Set_Text_colour(GREENYELLOW);
  mylcd.Print_String("2PON-" + String(value2), 0, 125);

  mylcd.Set_Text_colour(GREEN);
  mylcd.Print_String("3PON-" + String(value3), 0, 150);


  mylcd.Set_Text_colour(MAROON);
  mylcd.Print_String("CO2--" + String(valco2), 0, 175);

  mylcd.Set_Text_colour(PURPLE);
  mylcd.Print_String("PHV-" + String(voltage, 4), 0, 200);


  mylcd.Set_Text_colour(CYAN);
  mylcd.Print_String("PH-" + String(pHValue, 3), 0, 225);
  //  mylcd.setCursor(53, 220);
  // mylcd.Print_String(valco2, 53, 220);


  if (ioheat == 1) {
    mylcd.Set_Text_colour(GREEN);
    mylcd.Print_String("HEAT 1", 160, 75);
  }

  if (ioheat == 0) {
    mylcd.Set_Text_colour(RED);
    mylcd.Print_String("HEAT 0", 160, 75);
  }

  if (SensorState == 0) {
    mylcd.Set_Text_colour(GREEN);
    mylcd.Print_String("DOLIV", 160, 100);
  }

  if (SensorState == 1) {
    mylcd.Set_Text_colour(RED);
    mylcd.Print_String("DOLIV", 160, 100);
  }

  if (Sensorponic == 0) {
    mylcd.Set_Text_colour(GREEN);
    mylcd.Print_String("PONIC_LEV", 160, 125);
  }

  if (Sensorponic == 1) {
    mylcd.Set_Text_colour(RED);
    mylcd.Print_String("PONIC", 160, 125);
  }
  //// tft.setTextColor(GREEN);
  //
 if (PompState + PompStart >= 1) {
    mylcd.Set_Text_colour(GREEN);
    mylcd.Print_String("POMPA", 160, 150);
    mylcd.Print_String(String((millis() - myTimer3)/1000), 290, 150);
  }

  if (PompState + PompStart == 0) {
    mylcd.Set_Text_colour(RED);
    mylcd.Print_String("POMPA", 160, 150);
  }

  

  FILLScreen =  ioheat + SensorState + Sensorponic;

  if (OLDScreen != FILLScreen){
    mylcd.Fill_Screen(BLACK);
    OLDScreen = FILLScreen;
  }



}
