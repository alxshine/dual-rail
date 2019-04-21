#include "print.h"
#include "tinyAES.h"

unsigned char plaintext[16] = "hello world!123";
unsigned char key[17] = "supersecretkey11";

void c_entry() {
  unsigned char ciphertext[16];
  unsigned char decrypted[16];

  AES128_ECB_encrypt(plaintext, key, ciphertext);
  AES128_ECB_decrypt(ciphertext, key, decrypted);
  print_uart0((char *)decrypted);
}
