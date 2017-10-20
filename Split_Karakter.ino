void setup() {
  Serial.begin(9600);
  char KarakterSplit[] = "kata0,kata1";
  char* kata0 = strtok(KarakterSplit,","); //pembatas koma
  char* kata1 = strtok(NULL,","); //pembatas koma
  Serial.println(kata0);
  Serial.println(kata1);
}

void loop() {

}
