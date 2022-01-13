int minv = 630;//малая влажность
int maxv = 330;//полный полив
int normv = 500;//чуть влажная
int value = 0;//полученное значение
int last_value = 0;//последнее значимое изменение
int value_sdvig =50;//значимое изменение 
int ralay = 6; //пин реле
int time_work = 10;//время работы помпы в сек
int analogPin = A8;//пин датчика

//Переменные таймаута
int second = 0; // секунды
int time_off = 0; // счетчик оставшегося времени
int pause_time = 15; // время отдыха после полива в минутах

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  pinMode(ralay,HIGH);//настройка реле
  digitalWrite(ralay, HIGH);
}

void poliv()
{
  int time_tmp;
  time_tmp=time_work;
  digitalWrite(ralay, LOW);
 while(time_tmp>0 && value>normv){// ждем истечения времени time_work или нормальной влажности почвы
  delay(1000);
   value=analogRead(analogPin);//обновляем значение влажности
 time_tmp--;
 }
  digitalWrite(ralay, HIGH);
  second=0; // сбрасываем секунды на ноль
  time_off=pause_time;// устанавливаем задержку между поливами
}

void loop() {
  // put your main code here, to run repeatedly:
value=analogRead(analogPin);
if (value>(last_value+value_sdvig)||value<(last_value-value_sdvig)){// если last_value отклонился на value_sdvig выводим value в uart
  Serial.println(value);
  last_value=value;
}
if ((value>(minv-value_sdvig)) && time_off<1) poliv();//если значение влажности > критическая влажность - 50 и не было недавних поливов
// временные функции что бы не играться с таймерами
if (second>59)
{
  second=0;
  if (time_off>0) time_off--;
}
delay(1000);//пауза 1 сек 
second++;
}
