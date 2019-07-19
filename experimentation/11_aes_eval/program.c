#include "print.h"
#include "tinyAES.h"

void c_entry() {
  unsigned char plaintext[16];
  plaintext[0] = C;
  plaintext[1] = C;
  plaintext[2] = C;
  plaintext[3] = C;
  plaintext[4] = C;
  plaintext[5] = C;
  plaintext[6] = C;
  plaintext[7] = C;
  plaintext[8] = C;
  plaintext[9] = C;
  plaintext[10] = C;
  plaintext[11] = C;
  plaintext[12] = C;
  plaintext[13] = C;
  plaintext[14] = C;
  plaintext[15] = C;

  unsigned char key[16];
  key[0] = 's';
  key[1] = 'u';
  key[2] = 'p';
  key[3] = 'e';
  key[4] = 'r';
  key[5] = 's';
  key[6] = 'e';
  key[7] = 'c';
  key[8] = 'r';
  key[9] = 'e';
  key[10] = 't';
  key[11] = 'k';
  key[12] = 'e';
  key[13] = 'y';
  key[14] = '1';
  key[15] = '1';

  unsigned char ciphertext[16];
  unsigned char decrypted[16];

  printn_uart0((char *)plaintext, 16);
  AES128_ECB_encrypt(plaintext, key, ciphertext);
  printn_uart0((char *)ciphertext, 16);
  AES128_ECB_decrypt(ciphertext, key, decrypted);
  printn_uart0((char *)decrypted, 16);
}
