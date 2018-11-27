#include <stdio.h>
#include <string.h>

#include "plaintexts.h"
#include "tinyAES.h"


#define OUTPIN 6
uint8_t key[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
uint8_t buf[16];

int main() {
  for (int i = 0; i < 5; ++i) {
    const uint8_t *plaintext = (uint8_t *)plaintexts[i++];
  	char printText[17];
  	memcpy(printText, plaintext, 16);
  	printText[16] = 0;
  	printf("Plaintext %d: %s\n", i, printText);
    AES128_ECB_encrypt(plaintext, key, buf);
    memcpy(printText, buf, 16);
    printf("Ciphertext: %s\n\n", printText);
  }

  return 0;
}
