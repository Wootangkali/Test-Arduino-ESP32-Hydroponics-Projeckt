void setup() {
  pinMode(11,OUTPUT);//установка контакта 11 в качестве выходного контакта
}
void loop() {
  int wilg = analogRead(A0);//переменная для влажности
  int wil = map(wilg,310,570, 100, 0);//пересчитать значение в проценты

  if(wil < 60)//если влажность менее 60%
  {
    pinMode(11,HIGH);//насос включается 
    delay(5000);//на 5 секунд
    pinMode(11,LOW);//насос выключается
  }
  else// если нет
  {
    pinMode(11,LOW);//насос отключен
  }
  delay(1800000);//ждем 30 минут для следующего измерения
}
