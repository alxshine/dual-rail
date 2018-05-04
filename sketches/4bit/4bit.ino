
#include<stdio.h>

#define TRIGGER 2
#define TYPE char
#define REF 0xF
#define LO 0x7
#define HI 0x1

TYPE a = REF;
TYPE bs[] = {HI, LO, HI};
TYPE cs[] = {LO, HI};
int j = 1;

void setup() {
  pinMode(TRIGGER, OUTPUT);
  randomSeed(1337);
  Serial.begin(115200);
  //  digitalWrite(TRIGGER, HIGH);
  delay(5000);
  //  digitalWrite(TRIGGER, LOW);
}

void loop() {
  TYPE b = bs[j];
  TYPE c;
  digitalWrite(TRIGGER, HIGH);
  delay(10);
  c = a ^ b;
  digitalWrite(TRIGGER, LOW);
  delay(50);
  Serial.println((short)c);
  j = 2 - j/2;
  delay(50);
}
