//TouchScreen.h GFX Calibration
//Making all control and bus pins INPUT_PULLUP
//Typical 30k Analog pullup with corresponding pin
//would read low when digital is written LOW
//e.g. reads ~25 for 300R X direction
//e.g. reads ~30 for 500R Y direction
//
//Testing : (A1, D7) = 32
//Testing : (A2, D6) = 23
//ID = 0x9486
//
//cx=897 cy=922 cz=480  X, Y, Pressure
//cx=895 cy=554 cz=581  X, Y, Pressure
//cx=900 cy=186 cz=683  X, Y, Pressure
//cx=534 cy=923 cz=362  X, Y, Pressure
//cx=546 cy=187 cz=618  X, Y, Pressure
//cx=203 cy=712 cz=477  X, Y, Pressure
//cx=193 cy=549 cz=454  X, Y, Pressure
//cx=195 cy=185 cz=595  X, Y, Pressure
//
//*** COPY-PASTE from Serial Terminal:
//const int XP=6,XM=A2,YP=A1,YM=7; //320x480 ID=0x9486
//const int TS_LEFT=920,TS_RT=173,TS_TOP=866,TS_BOT=171;
//
//PORTRAIT  CALIBRATION     320 x 480
//x = map(p.x, LEFT=920, RT=173, 0, 320)
//y = map(p.y, TOP=866, BOT=171, 0, 480)
//
//LANDSCAPE CALIBRATION     480 x 320
//x = map(p.y, LEFT=866, RT=171, 0, 480)
//y = map(p.x, TOP=173, BOT=920, 0, 320)
//

// the regular Adafruit "TouchScreen.h" library only works on AVRs

// different mcufriend shields have Touchscreen on different pins
// and rotation.
// Run the TouchScreen_Calibr_native sketch for calibration of your shield





//

//    BOXSIZE = tft.width() / 6;
//    tft.fillScreen(BLACK);
//
//    tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
//    tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
//    tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, GREEN);
//    tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, CYAN);
//    tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, BLUE);
//    tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, MAGENTA);
//
//    tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
//    currentcolor = RED;
//    delay(1000);





//if (Wt > 24) digitalWrite(RELAY, HIGH),Serial.print("Water heatON ");
//else if (Wt < 24) digitalWrite(RELAY, LOW),Serial.print("Water heat OFF");


//  static unsigned long analogSampleTimepoint = millis();
//  if (millis() - analogSampleTimepoint > 40U) //every 40 milliseconds,read the analog value from the ADC
//  {
//    analogSampleTimepoint = millis();
//    analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin); //read the analog value and store into the buffer
//    analogBufferIndex++;
//    if (analogBufferIndex == SCOUNT)
//      analogBufferIndex = 0;
//  }
//  static unsigned long printTimepoint = millis();
//  if (millis() - printTimepoint > 800U)
//  {
//    printTimepoint = millis();
//    for (copyIndex = 0; copyIndex < SCOUNT; copyIndex++)
//      analogBufferTemp[copyIndex] = analogBuffer[copyIndex];
//    averageVoltage = getMedianNum(analogBufferTemp, SCOUNT) * (float)VREF / 1024.0; // read the analog value more stable by the median filtering algorithm, and convert to voltage value
//    float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0); //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
//    float compensationVolatge = averageVoltage / compensationCoefficient; //temperature compensation
//    tdsValue = (133.42 * compensationVolatge * compensationVolatge * compensationVolatge - 255.86 * compensationVolatge * compensationVolatge + 857.39 * compensationVolatge) * 0.5; //convert voltage value to tds value
//    //Serial.print("voltage:");
//    //Serial.print(averageVoltage,2);
//    //Serial.print("V ");
//
//
//  }
//}
//int getMedianNum(int bArray[], int iFilterLen)
//{
//  int bTab[iFilterLen];
//  for (byte i = 0; i < iFilterLen; i++)
//    bTab[i] = bArray[i];
//  int i, j, bTemp;
//  for (j = 0; j < iFilterLen - 1; j++)
//  {
//    for (i = 0; i < iFilterLen - j - 1; i++)
//    {
//      if (bTab[i] > bTab[i + 1])
//      {
//        bTemp = bTab[i];
//        bTab[i] = bTab[i + 1];
//        bTab[i + 1] = bTemp;
//      }
//    }
//  }
//  if ((iFilterLen & 1) > 0)
//    bTemp = bTab[(iFilterLen - 1) / 2];
//  else
//    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
//  return bTemp;
//
//
//}
//    uint16_t xpos, ypos;  //screen coordinates
//    tp = ts.getPoint();   //tp.x, tp.y are ADC values
//
//    // if sharing pins, you'll need to fix the directions of the touchscreen pins
//    pinMode(XM, OUTPUT);
//    pinMode(YP, OUTPUT);
// we have some minimum pressure we consider 'valid'
// pressure of 0 means no pressing!

//    if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE) {
//        // most mcufriend have touch (with icons) that extends below the TFT
//        // screens without icons need to reserve a space for "erase"
//        // scale the ADC values from ts.getPoint() to screen values e.g. 0-239
//        //
//        // Calibration is true for PORTRAIT. tp.y is always long dimension
//        // map to your current pixel orientation
//        switch (Orientation) {
//            case 0:
//                xpos = map(tp.x, TS_LEFT, TS_RT, 0, tft.width());
//                ypos = map(tp.y, TS_TOP, TS_BOT, 0, tft.height());
//                break;
//            case 1:
//                xpos = map(tp.y, TS_TOP, TS_BOT, 0, tft.width());
//                ypos = map(tp.x, TS_RT, TS_LEFT, 0, tft.height());
//                break;
//            case 2:
//                xpos = map(tp.x, TS_RT, TS_LEFT, 0, tft.width());
//                ypos = map(tp.y, TS_BOT, TS_TOP, 0, tft.height());
//                break;
//            case 3:
//                xpos = map(tp.y, TS_BOT, TS_TOP, 0, tft.width());
//                ypos = map(tp.x, TS_LEFT, TS_RT, 0, tft.height());
//                break;
//        }
//
//        // are we in top color box area ?
//        if (ypos < BOXSIZE) {               //draw white border on selected color box
//            oldcolor = currentcolor;
//
//            if (xpos < BOXSIZE) {
//                currentcolor = RED;
//                tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
//            } else if (xpos < BOXSIZE * 2) {
//                currentcolor = YELLOW;
//                tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, WHITE);
//            } else if (xpos < BOXSIZE * 3) {
//                currentcolor = GREEN;
//                tft.drawRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, WHITE);
//            } else if (xpos < BOXSIZE * 4) {
//                currentcolor = CYAN;
//                tft.drawRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, WHITE);
//            } else if (xpos < BOXSIZE * 5) {
//                currentcolor = BLUE;
//                tft.drawRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, WHITE);
//            } else if (xpos < BOXSIZE * 6) {
//                currentcolor = MAGENTA;
//                tft.drawRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, WHITE);
//            }
//
//            if (oldcolor != currentcolor) { //rub out the previous white border
//                if (oldcolor == RED) tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
//                if (oldcolor == YELLOW) tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
//                if (oldcolor == GREEN) tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, GREEN);
//                if (oldcolor == CYAN) tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, CYAN);
//                if (oldcolor == BLUE) tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, BLUE);
//                if (oldcolor == MAGENTA) tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, MAGENTA);
//            }
//        }
//        // are we in drawing area ?
//        if (((ypos - PENRADIUS) > BOXSIZE) && ((ypos + PENRADIUS) < tft.height())) {
//            tft.fillCircle(xpos, ypos, PENRADIUS, currentcolor);
//        }
//        // are we in erase area ?
//        // Plain Touch panels use bottom 10 pixels e.g. > h - 10
//        // Touch panels with icon area e.g. > h - 0
//        if (ypos > tft.height() - 10) {
//            // press the bottom of the screen to erase
//            tft.fillRect(0, BOXSIZE, tft.width(), tft.height() - BOXSIZE, BLACK);
//        }
//void showmsgXY(int x, int y, int sz, const GFXfont *f, const char *msg)
//{
//    int16_t x1, y1;
//    uint16_t wid, ht;
//    tft.drawFastHLine(0, y, tft.width(), WHITE);
//    //tft.setFont(f);
//    tft.setCursor(x, y);
//    tft.setTextColor(RED);
//    tft.setTextSize(sz);
//    tft.print(msg);
//    delay(1000);
//}







//if
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
