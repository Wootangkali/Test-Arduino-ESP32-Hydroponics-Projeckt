void pompa(void) {
 if (PompState == 1) digitalWrite(PolivPomp_Pin, LOW);
 if (PompStart == 1) digitalWrite(PolivPomp_Pin, LOW);
 if (PompState + PompStart == 0) digitalWrite(PolivPomp_Pin, HIGH);
 }
 //, myTimer3 = millis();
//  if ( millis() - polivtimer > 60000ul ) PompStart = 0, digitalWrite(PolivPomp_Pin, HIGH);
   
// else digitalWrite(PolivPomp_Pin, HIGH);


//  if (PompStart == 1 && (millis() - myTimer3) >= 15000) {
//  //  myTimer3 = millis(); // сбросить таймер
//     PompStart = 0;
//     digitalWrite(PolivPomp_Pin, HIGH);
//    //   mylcd.Fill_Screen(BLACK);
//    //show_Serial();
//  };
//  if (PompState + PompStart == 0) digitalWrite(PolivPomp_Pin, HIGH);
//  }
////#define relay 34 // реле
////#define btn   19 //кнопка
////
//uint32_t timer = 0;
//
//void setup() {
//  pinMode(relay, OUTPUT); // реле
//  pinMode(btn,   INPUT_PULLUP); // кнопка
//  digitalWrite(relay, LOW);
//}
//
//void loop() {
//  if ( !digitalRead(btn) )
//    digitalWrite( relay, !digitalRead(relay) ), timer = millis();
//  if ( millis() - timer > 60000ul ) digitalWrite(relay, LOW);
//} 
//buttonpoliv.tick();  // обязательная функция отработки. Должна постоянно опрашиваться
//
//  if (buttonpoliv.isSingle()) digitalWrite(PolivPomp_Pin, LOW);    // проверка на один клик
////  if (buttonpoliv.isDouble()) Serial.println("Double");     // проверка на двойной клик
//  if (buttonpoliv.isTriple()) digitalWrite(PolivPomp_Pin, LOW), polivtimer = millis();
//
//  if ( millis() - polivtimer > 60000ul ) digitalWrite(PolivPomp_Pin, HIGH);     // проверка на тройной клик
