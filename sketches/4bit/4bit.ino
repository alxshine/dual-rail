
#include<stdio.h>

#define TRIGGER 2
#define TYPE char
#define REF 0xF
#define LO 0x7
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

void loop() {
  TYPE b;
  digitalWrite(TRIGGER, HIGH);
  b = a ^ bs[j];
  digitalWrite(TRIGGER, LOW);
  delay(50);
  Serial.println(b);
  j = 1 - j;
  delay(50);
}
