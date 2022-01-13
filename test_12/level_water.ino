void level_water(void) {

  // Устанавливаем текущее время
  CurrentTime2 = millis();
  // считываем сенсор
  boolean CurrentState = digitalRead(DOLIVSENS_PIN);
  // если текущее состояние сенсора отличается считанного
  if (CurrentState != SensorState) {
    // если отсчет таймера смены состояния не начат, начинаем
    if (SensorStartChange == 0) SensorStartChange = CurrentTime2;
    // если новое состояние приняло свое значение за время большее чем время таймаута
    if (CurrentTime2 - SensorStartChange > TIMEOUT) {
      // меняем состояние сенсора
      SensorState = !SensorState;
      // сбрасываем время начала смены состояния
      SensorStartChange = 0;
      // если текущее состояние сенсора 1, то включаем светодиод

      if (SensorState == 1) {
        digitalWrite(doliv_Pin, HIGH);
        // если текущее состояние сенсора 0, то выключаем светодиод
      } else {
        digitalWrite(doliv_Pin, LOW);
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
    SensorStartChange = 0;
  }

}
