#include <stdio.h>

#include "tinyAES.h"

int main() {
  unsigned char plaintext[16] = "hello world!123";
  unsigned char key[17] = "supersecretkey11";
  unsigned char ciphertext[16];
  unsigned char decrypted[16];

  AES128_ECB_encrypt(plaintext, key, ciphertext);
  AES128_ECB_decrypt(ciphertext, key, decrypted);
  printf("decrypted: %s\n", decrypted);
  return 0;
}
