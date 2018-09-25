
#include<stdio.h>

#include "s_box.h"

#define TRIGGER 9
#define TYPE char

TYPE key_xor = 7;
TYPE a;
TYPE ptxt = 0;

void setup() {
  pinMode(TRIGGER, OUTPUT);
  Serial.begin(115200);
  delay(5000);
}

void loop() {
  digitalWrite(TRIGGER, HIGH);
  delay(10);
  a = s[ptxt ^ key_xor];

  digitalWrite(TRIGGER, LOW);
  Serial.println(short(a));
  //keep it within the 4bit range
  ptxt = (ptxt + 1) % (1 << 4);
  delay(100);
}
