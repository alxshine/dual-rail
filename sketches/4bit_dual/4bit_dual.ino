
#include<stdio.h>

#include "dual-rail.h"

#define TRIGGER 2
#define TYPE char
#define REF 0b10101010 // 0xF encoded
#define LO 0b01101010 // 0x7 encoded
#define HI 0b01010110 // 0x1 encoded

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
  c = dual_xor(a, b);
  digitalWrite(TRIGGER, LOW);
  delay(50);
  Serial.println((short)c);
  j = 2 - j/2;
  delay(50);
}
