#include "print.h"
#include "tinyAES.h"

#ifndef C0
#define C0 'a'
#endif
#ifndef C1
#define C1 'a'
#endif
#ifndef C2
#define C2 'a'
#endif
#ifndef C3
#define C3 'a'
#endif
#ifndef C4
#define C4 'a'
#endif
#ifndef C5
#define C5 'a'
#endif
#ifndef C6
#define C6 'a'
#endif
#ifndef C7
#define C7 'a'
#endif
#ifndef C8
#define C8 'a'
#endif
#ifndef C9
#define C9 'a'
#endif
#ifndef C10
#define C10 'a'
#endif
#ifndef C11
#define C11 'a'
#endif
#ifndef C12
#define C12 'a'
#endif
#ifndef C13
#define C13 'a'
#endif
#ifndef C14
#define C14 'a'
#endif
#ifndef C15
#define C15 'a'
#endif
void c_entry() {
  unsigned char plaintext[16];
  plaintext[0] = C0;
  plaintext[1] = C1;
  plaintext[2] = C2;
  plaintext[3] = C3;
  plaintext[4] = C4;
  plaintext[5] = C5;
  plaintext[6] = C6;
  plaintext[7] = C7;
  plaintext[8] = C8;
  plaintext[9] = C9;
  plaintext[10] = C10;
  plaintext[11] = C11;
  plaintext[12] = C12;
  plaintext[13] = C13;
  plaintext[14] = C14;
  plaintext[15] = C15;

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
