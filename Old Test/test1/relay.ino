void relay() {

if (Wc > 30) digitalWrite(RELAY, HIGH),Serial.print("Hot ON ");
else if (Wc < 30) digitalWrite(RELAY, LOW),Serial.print("Hot OFF");   
}
