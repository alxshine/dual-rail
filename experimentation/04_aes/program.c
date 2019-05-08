#include "print.h"
#include "tinyAES.h"

unsigned char plaintext[16] = "hello world!123";
unsigned char key[17] = "supersecretkey11";

void c_entry() {
  unsigned char ciphertext[16];
  unsigned char decrypted[16];

  char buffer[16];
  for (int i = 0; i < 256; ++i) {
    char test = getSBoxValue(i);
    write_int(test, buffer);
    print_uart0(buffer);
  }
  /* printn_uart0((char *)plaintext, 16); */
  /* AES128_ECB_encrypt(plaintext, key, ciphertext); */
  /* printn_uart0((char *)ciphertext, 16); */
  /* AES128_ECB_decrypt(ciphertext, key, decrypted); */
  /* printn_uart0((char *)decrypted, 16); */
}
