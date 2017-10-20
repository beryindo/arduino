void setup() {
  Serial.begin(9600);
  char KarakterSplit[] = "cek,*635*1#";
  char* kata0 = strtok(KarakterSplit,",");
  char* kata1 = strtok(NULL,",");
  Serial.println(kata0);
  Serial.println(kata1);
}

void loop() {

}
