#include "tinyAES.h"


#define OUTPIN 7
uint8_t key[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
uint8_t buf[16];
uint8_t buf2[16];
uint8_t plaintext[16];
char buffer[255];

void setup() {
  // put your setup code here, to run once:
  pinMode(OUTPIN, OUTPUT);
  Serial.setTimeout(100000);
  Serial.begin(115200);
  srand(micros());
}

void loop() {
  if (Serial.available() > 0) {
    for (int i = 0; i < 16; i++) {
      plaintext[i] = 0;
    }
    Serial.readBytesUntil('\n', buffer, 255);
    sscanf(buffer, "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n", plaintext, plaintext + 1,
           plaintext + 2, plaintext + 3, plaintext + 4, plaintext + 5, plaintext + 6, plaintext + 7,
           plaintext + 8, plaintext + 9, plaintext + 10, plaintext + 11, plaintext + 12, plaintext + 13, plaintext + 14, plaintext + 15);

    delay(200);
    digitalWrite(OUTPIN, HIGH);
    AES128_ECB_encrypt(plaintext, key, buf);
    digitalWrite(OUTPIN, LOW);
  }
}
