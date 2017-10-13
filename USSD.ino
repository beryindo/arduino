#include <AltSoftSerial.h>
#define ERROR(x)
AltSoftSerial Sim800LSerial; // 8,9
const byte numChars = 160;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

// variables to hold the parsed data
char messageFromPC[numChars] = {0};
boolean newData = false;

void setup() {
  Sim800LSerial.begin(9600);
  Serial.begin(9600);
  Serial.println("test");
  if (0 != sendCmdAndWaitForResp("AT+CUSD=1,\"*888#\"\r\n", "OK", 5000)) {
    ERROR("ERROR:CUSD");
    return;
  }
}

void loop() {
  recvWithStartEndMarkers();
  if (newData == true) {
    strcpy(tempChars, receivedChars);
    parseData();
    showParsedData();
    newData = false;
  }
}

void sendCmd(const char* cmd)
{
  Sim800LSerial.write(cmd);
}

int waitForResp(const char *resp, unsigned int timeout)
{
  int len = strlen(resp);
  int sum = 0;
  unsigned long timerStart, timerEnd;
  timerStart = millis();

  while (1) {
    if (Sim800LSerial.available()) {
      char c = Sim800LSerial.read();
      sum = (c == resp[sum]) ? sum + 1 : 0;
      if (sum == len)break;
    }
    timerEnd = millis();
    if (timerEnd - timerStart > 1000 * timeout) {
      return -1;
    }
  }

  while (Sim800LSerial.available()) {
    Sim800LSerial.read();
  }

  return 0;
}

int sendCmdAndWaitForResp(const char* cmd, const char *resp, unsigned timeout)
{
  sendCmd(cmd);
  return waitForResp(resp, timeout);
}

void Sim800LFlush() {
  if (Sim800LSerial.available())              // if date is comming from softwareserial port ==> data is comming from gprs shield
    Serial.write(Sim800LSerial.read());
  if (Serial.available())                // if data is available on hardwareserial port ==> data is comming from PC or notebook
    Sim800LSerial.write(Serial.read());
}

void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '"';
  char endMarker = '"';
  char rc;

  while (Sim800LSerial.available() > 0 && newData == false) {
    rc = Sim800LSerial.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}

//============

void parseData() {      // split the data into its parts

  char * strtokIndx; // this is used by strtok() as an index

  strtokIndx = strtok(tempChars, '"');     // get the first part - the string
  strcpy(messageFromPC, strtokIndx); // copy it to messageFromPC

}

//============

void showParsedData() {
  Serial.println(messageFromPC);
}
