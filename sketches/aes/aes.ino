#include "tinyAES.h"
#include "plaintexts.h"

#define OUTPIN 7
uint8_t key[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
uint8_t buf[16];
uint8_t buf2[16];
char buffer[255];
int i;

void setup() {
  // put your setup code here, to run once:
  pinMode(OUTPIN, OUTPUT);
  Serial.setTimeout(100000);
  Serial.begin(115200);
  srand(micros());
}

void loop() {
  const uint8_t* plaintext = (uint8_t*)plaintexts[i];
  digitalWrite(OUTPIN, HIGH);
  AES128_ECB_encrypt(plaintext, key, buf);
  digitalWrite(OUTPIN, LOW);
}
