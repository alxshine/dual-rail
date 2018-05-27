
#include<stdio.h>

#include "dual-rail.h"
#include "s_box.h"

#define TRIGGER 2
#define TYPE char
#define REF 0b10101010 // 0xF encoded
#define LO 0b01101010 // 0x7 encoded
#define HI 0b01010110 // 0x1 encoded

TYPE key_xor = 5, key_add = 7, key_mult = 1;
TYPE d_key_xor, d_key_add, d_key_mult;
TYPE a, b, c, d, e, f;
TYPE ptxt = 0;
TYPE d_ptxt;

void setup() {
  pinMode(TRIGGER, OUTPUT);
  Serial.begin(115200);
  d_key_xor = encode(key_xor);
  d_key_add = encode(key_add);
  d_key_mult = encode(key_mult);
  d_ptxt = encode(ptxt);
  delay(5000);
}

void loop() {

  digitalWrite(TRIGGER, HIGH);
  a = s[ptxt ^ key_xor];
  b = s[ptxt + key_add];
  c = s[ptxt * key_mult];

  d = d_s[dual_xor(d_ptxt, d_key_xor)];
  e = d_s[dual_add(d_ptxt, d_key_add)];
  f = d_s[dual_mult(d_ptxt, d_key_mult)];
  digitalWrite(TRIGGER, LOW);
  delay(50);
  Serial.println(short(a));
  Serial.println(short(b));
  Serial.println(short(c));
  Serial.println(short(d));
  Serial.println(short(e));
  Serial.println(short(f));
  d_ptxt = encode(++ptxt);
  delay(50);
}
