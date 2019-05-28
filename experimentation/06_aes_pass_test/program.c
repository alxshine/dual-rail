#include "print.h"
#include "tinyAES.h"

void c_entry() {
  unsigned char plaintext[16] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o',
                                 'r', 'l', 'd', '!', '1', '2', '3'};
  unsigned char key[16] = {'s', 'u', 'p', 'e', 'r', 's', 'e', 'c',
                           'r', 'e', 't', 'k', 'e', 'y', '1', '1'};
  unsigned char ciphertext[16];
  unsigned char decrypted[16];

  printn_uart0((char *)plaintext, 16);
  AES128_ECB_encrypt(plaintext, key, ciphertext);
  printn_uart0((char *)ciphertext, 16);
  AES128_ECB_decrypt(ciphertext, key, decrypted);
  printn_uart0((char *)decrypted, 16);
}
