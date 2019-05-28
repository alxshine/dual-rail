#include "print.h"
#include "tinyAES.h"

void c_entry() {
  unsigned char plaintext[16];
  plaintext[0] = 'H';
  plaintext[1] = 'e';
  plaintext[2] = 'l';
  plaintext[3] = 'l';
  plaintext[4] = 'o';
  plaintext[5] = ',';
  plaintext[6] = ' ';
  plaintext[7] = 'W';
  plaintext[8] = 'o';
  plaintext[9] = 'r';
  plaintext[10] = 'l';
  plaintext[11] = 'd';
  plaintext[12] = '!';
  plaintext[13] = '1';
  plaintext[14] = '2';
  plaintext[15] = '3';

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
