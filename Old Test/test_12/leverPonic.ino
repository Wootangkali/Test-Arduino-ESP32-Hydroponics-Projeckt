void levelponic (void)
{
  // Устанавливаем текущее время
  CurrentTime3 = millis();
  // считываем сенсор
  boolean CurrentStatePonic = digitalRead(levelponicSENS_PIN);
  // если текущее состояние сенсора отличается считанного
  if (CurrentStatePonic != Sensorponic) {
    // если отсчет таймера смены состояния не начат, начинаем
    if (SensorStartChange2 == 0) SensorStartChange2 = CurrentTime3;
    // если новое состояние приняло свое значение за время большее чем время таймаута
    if (CurrentTime3 - SensorStartChange2 > TIMEOUT2) {
      // меняем состояние сенсора
      Sensorponic = !Sensorponic;
      // сбрасываем время начала смены состояния
      SensorStartChange2 = 0;
      // если текущее состояние сенсора 1, то включаем светодиод

      if (Sensorponic == 1) {
        digitalWrite(dolivPonic_Pin, HIGH);
        // если текущее состояние сенсора 0, то выключаем светодиод
      } else {
        digitalWrite(dolivPonic_Pin, LOW);
      }

      //        if(SensorState){
      //          digitalWrite(LED_PIN, HIGH);
      //        // если текущее состояние сенсора 0, то выключаем светодиод
      //        }else{
      //          digitalWrite(LED_PIN, LOW);
      //        }
    }
    // смена состояния не состоялась, сбрасываем таймер
  } else {
    SensorStartChange2 = 0;
  }

}
