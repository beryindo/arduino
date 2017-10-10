#define ON LOW
#define OFF HIGH
const int vibrationSensorPin = A0; // Vibration Sensor di hubungkan ke Pin 2
int vibrationSensorState = 0; // Status saat pertama mulai = 0
unsigned long interval = 900000; // the time we need to wait
unsigned long previousMillis = 0; // millis() returns an unsigned long.
const int Relay1 = 2;
int StatRelay1;

void setup() {
  pinMode(vibrationSensorPin, INPUT); // Jadikan Vibration sensor sebagai input
  pinMode (Relay1, OUTPUT);
  digitalWrite (Relay1, HIGH);
  //    StatRelay1 = OFF;
  Serial.begin(9600);
}

void loop() {
  digitalWrite(Relay1, StatRelay1);
  unsigned long currentMillis = millis();
  vibrationSensorState = digitalRead(vibrationSensorPin);

  if ((unsigned long)(currentMillis - previousMillis) >= interval) {
    if (vibrationSensorState == HIGH) {
      StatRelay1 = OFF;
      digitalWrite(Relay1, StatRelay1);
//      Serial.println("RELAY mati setelah standby 15menit tidak ada getaran...");
    }
    previousMillis = millis();
  }
  if (vibrationSensorState == LOW) {
    StatRelay1 = ON;
    digitalWrite(Relay1, StatRelay1);
//    Serial.println("RELAY hidup...");
  }
//  delay(600);
//  Serial.println(vibrationSensorState, DEC);
}
