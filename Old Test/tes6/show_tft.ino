void show_tft(void)
{
   tft.setFont(&FreeSerif9pt7b);
   // tft.fillScreen(BLACK);
  tft.setCursor(3, 15);
  tft.setTextSize(1);
  tft.setTextColor(YELLOW, BLACK);
  tft.println("R");
  tft.setCursor(23, 15);
  tft.print(Rt);

  tft.setTextColor(BLUE, BLACK);
  tft.setCursor(3, 35);
  tft.println("W");
  tft.setCursor(23, 35);
  tft.print(Wt);
  
 tft.setTextColor(CYAN, BLACK);
  tft.setCursor(3, 60);
  tft.print("PPM");
  tft.setCursor(43, 60);
 tft.print(tdsValue, 0);


 tft.setTextColor( MAGENTA, BLACK);
  tft.setCursor(3, 80);
  tft.print("Distance");
  tft.setCursor(85, 80);
 tft.print(distance);




 if (ioheat == 1) {tft.setTextColor(RED);show_heater(110, 40, 2, &FreeSerifItalic18pt7b, "Heater ON");}

 else{tft.setTextColor(GREEN); show_heater(110, 40, 2, &FreeSerifItalic18pt7b, "Heater OFF");};
// tft.setTextColor(GREEN); 


if (SensorState == 1) {tft.setTextColor(RED);show_heater(120, 95, 2, &FreeSerifItalic18pt7b, "Doliv ON");}

  else{tft.setTextColor(GREEN); show_heater(120, 95, 2, &FreeSerifItalic18pt7b, "Doliv OFF");};
// tft.setTextColor(GREEN); 

 tft.setFont(&FreeSerif9pt7b);
tft.setTextSize(2);
 tft.setTextColor( GREENYELLOW, BLACK);
  tft.setCursor(3, 125);
  tft.print("1");
  tft.setCursor(33, 125);
 tft.print(value);

  tft.setTextColor( WHITE, BLACK);
  tft.setCursor(3, 160);
  tft.print("2");
  tft.setCursor(33, 160);
 tft.print(value2);

  tft.setTextColor( ORANGE, BLACK);
  tft.setCursor(3, 190);
  tft.print("3");
  tft.setCursor(33, 190);
 tft.print(value3);
}
 
