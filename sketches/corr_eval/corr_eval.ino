
#include<stdio.h>

#include "s_box.h"

#define TRIGGER 9
#define TYPE uint8_t

TYPE key_xor = 7;
TYPE a;
TYPE ptxt = 0;
TYPE sbox[256];

void setup() {
  pinMode(TRIGGER, OUTPUT);
  Serial.begin(115200);
  delay(5000);
  initialize_aes_sbox(sbox);
}

void loop() {
  digitalWrite(TRIGGER, HIGH);
  delay(10);
  a = sbox[ptxt ^ key_xor];

  digitalWrite(TRIGGER, LOW);
  Serial.println(short(a));
  a++;
  delay(100);
}
