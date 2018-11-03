#include "tinyAES.h"


#define OUTPIN 7
uint8_t key[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
uint8_t buf[16];
uint8_t buf2[16];
uint8_t plaintext[17];

void setup() {
  // put your setup code here, to run once:
  pinMode(OUTPIN, OUTPUT);
  Serial.setTimeout(100000);
  Serial.begin(115200);
  srand(micros());
}

void loop() {
  if (Serial.available() > 0) {
    for (int i = 0; i < 17; i++) {
      plaintext[i] = 0;
    }
    Serial.readBytesUntil('\n', plaintext, 17);

    Serial.println((char*)plaintext);

    digitalWrite(OUTPIN, HIGH);
    AES128_ECB_encrypt(plaintext, key, buf);
    digitalWrite(OUTPIN, LOW);
  }
}
