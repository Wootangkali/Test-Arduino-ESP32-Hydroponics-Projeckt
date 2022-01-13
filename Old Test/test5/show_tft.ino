void show_tft(void)
{
   tft.setFont(&FreeSerif9pt7b);
    tft.fillScreen(BLACK);
  tft.setCursor(3, 10);
  tft.setTextSize(1);
  tft.setTextColor(YELLOW, BLACK);
  tft.println("R");
  tft.setCursor(23, 10);
  tft.print(Rt);

  tft.setTextColor(BLUE, BLACK);
  tft.setCursor(3, 35);
  tft.println("W");
  tft.setCursor(23, 35);
  tft.print(Wt);

  tft.setCursor(3, 60);
  tft.print("PPM");
  tft.setCursor(43, 60);
  tft.setTextColor(CYAN, BLACK);
  tft.print(tdsValue, 0);
 
  
 // if (digitalWrite(17, HIGH)) showmsgXY(0, 160, 1, &FreeSevenSegNumFont, "Heater ON");
  //  if  digitalWrite(RELAY, HIGH), tft.setCursor(300, 0),tft.println("T+");
  // if  digitalWrite(RELAY, LOW),tft.setCursor(300, 0),tft.println("T-");
  //    tft.println(ID, HEX);
  //    tft.println("Screen is " + String(tft.width()) + "x" + String(tft.height()));
  //    tft.println("");
  //    tft.setTextSize(2);
  //    tft.println(name);
  //    tft.setTextSize(1);
  //    tft.println("PORTRAIT Values:");
  //    tft.println("LEFT = " + String(TS_LEFT) + " RT  = " + String(TS_RT));
  //    tft.println("TOP  = " + String(TS_TOP)  + " BOT = " + String(TS_BOT));
  //    tft.println("\nWiring is: ");
  //    tft.println("YP=" + String(YP)  + " XM=" + String(XM));
  //    tft.println("YM=" + String(YM)  + " XP=" + String(XP));
  //    tft.setTextSize(2);
  //    tft.setTextColor(RED);
  //    tft.setCursor((tft.width() - 48) / 2, (tft.height() * 2) / 4);
  //    tft.print("EXIT");
  //    tft.setTextColor(YELLOW, BLACK);
  //    tft.setCursor(0, (tft.height() * 6) / 8);
  //    tft.print("Touch screen for loc");
  //    while (1) {
  //       tp = ts.getPoint();
  //        pinMode(XM, OUTPUT);
  //       pinMode(YP, OUTPUT);
  //        if (tp.z < MINPRESSURE || tp.z > MAXPRESSURE) continue;
  //        if (tp.x > 450 && tp.x < 570  && tp.y > 450 && tp.y < 570) break;
  //        tft.setCursor(0, (tft.height() * 3) / 4);
  //        tft.print("tp.x=" + String(tp.x) + " tp.y=" + String(tp.y) + "   ");
  //    }
}
