
#include<stdio.h>

#define TRIGGER 2
#define TYPE char
#define REF 0xFF
#define LO 0x7F
#define HI 0x1

TYPE a = REF;
TYPE bs[] = {HI, LO};
TYPE cs[] = {LO, HI};
int j = 0;
int i = 0;

void setup() {
  pinMode(TRIGGER, OUTPUT);
  randomSeed(1337);
  Serial.begin(115200);
  //  digitalWrite(TRIGGER, HIGH);
  delay(5000);
  //  digitalWrite(TRIGGER, LOW);
}

TYPE doStuff(int i) {
  TYPE c = a ^ bs[1-i];
  return c;
}

void loop() {
  digitalWrite(TRIGGER, HIGH);
  TYPE c = doStuff(j);
  Serial.println(c);
  digitalWrite(TRIGGER, LOW);
  j = 1 - j;
  delay(100);
}
