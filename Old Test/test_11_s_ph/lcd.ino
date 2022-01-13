//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1

void Show_lcd(void)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(pHValue, 2);
  //  lcd.setCursor(0,0);
  //  lcd.print("PH");
  lcd.setCursor(5, 0);
  lcd.print(voltage, 3);
  lcd.setCursor(0, 1);
  lcd.print("Wt");
  lcd.setCursor(2, 1);
  lcd.println(Wt, 2);

  lcd.setCursor(10, 1);
  lcd.print("R");
  lcd.setCursor(11, 1);
  lcd.print(Rt);


  lcd.setCursor(13, 0);
  lcd.print("D");
  lcd.setCursor(14, 0);
  lcd.print(distance);
}
