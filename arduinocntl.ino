#include <stdio.h>
#include <stdlib.h>
#include <SoftwareSerial.h>
// #include <WString.h>
#define maxLength 30


String inString = String(maxLength);
byte val=0;

// GPS Setup
#define rxGPS 13
#define txGPS 11
SoftwareSerial serialGPS = SoftwareSerial(rxGPS, txGPS);
String stringGPS = "";

//motor A
int dir1PinA = 2;
int dir2PinA = 3;
//motor B
int dir1PinB = 4;
int dir2PinB = 5;
unsigned long time;
int dir;

void setup() {
  pinMode(rxGPS, INPUT);
  pinMode(txGPS, OUTPUT);

  // raspi serial
  Serial.begin(9600);
  Serial.println("Started");

  // GPS Setup
  serialGPS.begin(4800);
  digitalWrite(txGPS,HIGH);

  // Cut first gibberish
  while(serialGPS.available())
    if (serialGPS.read() == '\r')
      break;

  // mortor setup
  pinMode(dir1PinA,OUTPUT);
  pinMode(dir2PinA,OUTPUT);
  pinMode(dir1PinB,OUTPUT);
  pinMode(dir2PinB,OUTPUT);
  time = millis();
  dir = 0;
  
  move_stop();
}

void move_stop()
{
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, LOW);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, LOW);
}

void move_front(unsigned long ms)
{
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);
  delay(ms);
  move_stop();
}

void move_back(unsigned long ms)
{
  digitalWrite(dir1PinA, HIGH);
  digitalWrite(dir2PinA, LOW);
  digitalWrite(dir1PinB, HIGH);
  digitalWrite(dir2PinB, LOW);
  delay(ms);
  move_stop();
}

void rotate_right(unsigned long ms)
{
  digitalWrite(dir1PinA, HIGH);
  digitalWrite(dir2PinA, LOW);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);
  delay(ms);
  move_stop();
}

void rotate_left(unsigned long ms)
{
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);
  digitalWrite(dir1PinB, HIGH);
  digitalWrite(dir2PinB, LOW);
  delay(ms);
  move_stop();
}  

// Check GPS and returns string if full line recorded, else false
String checkGPS()
{
  if (serialGPS.available())
  {
    char c = serialGPS.read();
    if (c != '\n' && c != '\r')
    {
      stringGPS = String(stringGPS + c);
    }
    else
    {
      if (stringGPS != "")
      {
        String tmp = stringGPS;
        stringGPS = "";
        return tmp;
      }
    }
  } else {
      Serial.println("GPS not available...");
  }
  return false;
}

void recvStr(char *buf)
{
  int i = 0;
  char c;
  while (1) {
    if (Serial.available()) {
      c = Serial.read();
      buf[i] = c;
      if (c == '\r' || c == '\n') break;
      i++;
    }
  }
  buf[i] = '\n';
}

int parseTime(String cmdStr) {
  char timecnv[32];
  String timeStr = cmdStr.substring(cmdStr.indexOf(':') + 1);
  timeStr.toCharArray(timecnv, 31);
  return atoi(timecnv);
}

void loop(){
    int time = 0;
    if(Serial.available() > 0){
       char c = Serial.read();
       Serial.print(c); //for debug
//       if (c != '\r' && c != '\n') {
       if (c != '|') {
         inString = String(inString + c);
         
       } else {
         Serial.println(""); //for debug
         Serial.println("accepted:"+ inString); //for debug

          if(inString.startsWith("front:")){
              move_front(parseTime(inString));
          } else if(inString.startsWith("back:")){
              move_back(parseTime(inString));
          } else if(inString.startsWith("stop")){
              move_stop();
          } else if(inString.startsWith("left:")){
              rotate_left(parseTime(inString));
          } else if(inString.startsWith("right:")){
              rotate_right(parseTime(inString));
          } else if(inString.startsWith("gps")){
            int gpsloop = 1;
            while(gpsloop == 1) {
              String s = checkGPS();
              if(s && s.substring(0, 6) == "$GPGGA")
              {
                Serial.println(s);
                gpsloop = 0;
              }
            }
              
          }


          inString = "";
       }
       
    }
}
