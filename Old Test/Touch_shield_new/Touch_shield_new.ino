// the regular Adafruit "TouchScreen.h" library only works on AVRs

// different mcufriend shields have Touchscreen on different pins
// and rotation.
// Run the TouchScreen_Calibr_native sketch for calibration of your shield
#define RELAY 17   
#include <microDS3231.h>
MicroDS3231 rtc;
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS_1 40
#define ONE_WIRE_BUS_2 41

OneWire oneWire_in(ONE_WIRE_BUS_1);
OneWire oneWire_out(ONE_WIRE_BUS_2);

DallasTemperature sensor_room(&oneWire_in);
DallasTemperature sensor_water(&oneWire_out);

#define TdsSensorPin A6
#define VREF 5.0 // analog reference voltage(Volt) of the ADC
#define SCOUNT 30 // sum of sample point
int analogBuffer[SCOUNT]; // store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0,copyIndex = 0;
float averageVoltage = 0,tdsValue = 0,temperature = 25;
float Wt;



#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;       // hard-wired for UNO shields anyway.
#include <TouchScreen.h>

char *name = "Please Calibrate.";  //edit name of shield
const int XP=6,XM=A2,YP=A1,YM=7; //ID=0x9341
 const int TS_LEFT=901,TS_RT=604,TS_TOP=751,TS_BOT=209;


TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;

#define MINPRESSURE 200
#define MAXPRESSURE 1000
//
//int16_t BOXSIZE;
//int16_t PENRADIUS = 1;
//uint16_t ID, oldcolor, currentcolor;
uint8_t Orientation = 0;    //PORTRAIT

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

void show_Serial(void)
{
  
}

void show_tft(void)
{
    tft.setCursor(0, 0);
    tft.setTextSize(1);
  tft.print(F("ID=0x"));
   tft.println(ID, HEX);
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
//        tp = ts.getPoint();
//        pinMode(XM, OUTPUT);
//        pinMode(YP, OUTPUT);
//        if (tp.z < MINPRESSURE || tp.z > MAXPRESSURE) continue;
//        if (tp.x > 450 && tp.x < 570  && tp.y > 450 && tp.y < 570) break;
//        tft.setCursor(0, (tft.height() * 3) / 4);
//        tft.print("tp.x=" + String(tp.x) + " tp.y=" + String(tp.y) + "   ");
//    }
}


void setup(void)
{
//    uint16_t tmp;
 // ???????????????? ?????????????? ???????????? ???? ?????????? i2c
  if (!rtc.begin()) {
    Serial.println("DS3231 not found");
    for(;;);
  }
  
  // ???????????????????????????? ?????????????????? ??????????????  
  if (rtc.lostPower()) {            // ?????? ???????????? ??????????????
    //rtc.setTime(COMPILE_TIME);    // ???????????????????? ?????????? ???????????????????? ("??????????????" ????????????!!!)
    
    // ?????????????????? ????????????????????, ???? ?????????? "????????????" ?? ?????????? ???????????? ???????????? ???????????? ???????????????????? ?????????? ????????????????????
    rtc.setTime(BUILD_SEC, BUILD_MIN, BUILD_HOUR, BUILD_DAY, BUILD_MONTH, BUILD_YEAR);
  }

  //rtc.setTime(SEC, MIN, HOUR, DAY, MONTH, YEAR);      // ?????????????????? ?????????????? ??????????????, ?????????????? ?????? ??????????????????????  
  //rtc.setHMSDMY(HOUR, MIN, SEC, DAY, MONTH, YEAR);    // ?????????????????? ?????????????? ??????????????, ?????????? ?????????????????? ??????????????


pinMode(TdsSensorPin,INPUT);

    Serial.println("Dallas Temperature Control Library Demo - TwoPin_DS18B20");

    sensor_room.begin();
    sensor_water.begin();
pinMode(RELAY, OUTPUT); 
    tft.reset();
    ID = tft.readID();
    tft.begin(ID);
    Serial.begin(9600);
    show_Serial();
    tft.setRotation(Orientation);
    tft.fillScreen(BLACK);
    show_tft();

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
}

void loop()
{
int Wt = sensor_water.getTempCByIndex(0);
 // Serial.print("Requesting temperatures...");
    sensor_room.requestTemperatures();
    sensor_water.requestTemperatures();
  //  Serial.println(" done");

    Serial.print("room: ");
    Serial.println(sensor_room.getTempCByIndex(0));

    Serial.print("Water: ");
    Serial.println(sensor_water.getTempCByIndex(0));
if (Wt > 30) digitalWrite(RELAY, HIGH),Serial.print("Water heatON ");
else if (Wt < 30) digitalWrite(RELAY, LOW),Serial.print("Water heat OFF");   
        static unsigned long analogSampleTimepoint = millis();
if(millis()-analogSampleTimepoint > 40U) //every 40 milliseconds,read the analog value from the ADC
{
analogSampleTimepoint = millis();
analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin); //read the analog value and store into the buffer
analogBufferIndex++;
if(analogBufferIndex == SCOUNT)
analogBufferIndex = 0;
}
static unsigned long printTimepoint = millis();
if(millis()-printTimepoint > 800U)
{
printTimepoint = millis();
for(copyIndex=0;copyIndex<SCOUNT;copyIndex++)
analogBufferTemp[copyIndex]= analogBuffer[copyIndex];
averageVoltage = getMedianNum(analogBufferTemp,SCOUNT) * (float)VREF/ 1024.0; // read the analog value more stable by the median filtering algorithm, and convert to voltage value
float compensationCoefficient=1.0+0.02*(temperature-25.0); //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
float compensationVolatge=averageVoltage/compensationCoefficient; //temperature compensation
tdsValue=(133.42*compensationVolatge*compensationVolatge*compensationVolatge - 255.86*compensationVolatge*compensationVolatge + 857.39*compensationVolatge)*0.5; //convert voltage value to tds value
//Serial.print("voltage:");
//Serial.print(averageVoltage,2);
//Serial.print("V ");
Serial.println("TDS Value:");
Serial.print(tdsValue,0);
Serial.println("ppm");
}
}
int getMedianNum(int bArray[], int iFilterLen)
{
int bTab[iFilterLen];
for (byte i = 0; i<iFilterLen; i++)
bTab[i] = bArray[i];
int i, j, bTemp;
for (j = 0; j < iFilterLen - 1; j++)
{
for (i = 0; i < iFilterLen - j - 1; i++)
{
if (bTab[i] > bTab[i + 1])
{
bTemp = bTab[i];
bTab[i] = bTab[i + 1];
bTab[i + 1] = bTemp;
}
}
}
if ((iFilterLen & 1) > 0)
bTemp = bTab[(iFilterLen - 1) / 2];
else
bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
return bTemp;

  // ???????????? ?? char
  char time[8];
  rtc.getTimeChar(time);  // ???????????????? ?? ???????????? time
  Serial.println(time);
  
  char date[10];
  rtc.getDateChar(date);
  Serial.println(date);
  
//    uint16_t xpos, ypos;  //screen coordinates
//    tp = ts.getPoint();   //tp.x, tp.y are ADC values
//
//    // if sharing pins, you'll need to fix the directions of the touchscreen pins
//    pinMode(XM, OUTPUT);
//    pinMode(YP, OUTPUT);
//    // we have some minimum pressure we consider 'valid'
//    // pressure of 0 means no pressing!
//
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
//    }
}
