void setup() {
  Serial.begin(9600);
  char KarakterSplit[] = "kata0,kata1";
  String kata0 = pecah(KarakterSplit, ',', 0); //pembatas koma
  String kata1 = pecah(KarakterSplit, ',', 1); //pembatas koma
  Serial.println(kata0);
  Serial.println(kata1);
}

void loop() {

}


String pecah(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
