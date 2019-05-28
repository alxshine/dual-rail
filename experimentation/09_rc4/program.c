#include "print.h"
#include "definitions.h"

void swap(uint8_t *p1, uint8_t *p2) {
  uint8_t t = *p1;
  *p1 = *p2;
  *p2 = t;
}

void rc4_init(uint8_t *s, uint8_t *key, uint8_t key_len) {
  uint8_t i, j = 0;
  // Initial values of both vectors
  for (i = 0; i < 255; i++) {
    s[i] = i;
  }
  s[255] = 255;

  // Initial permutation
  for (i = 0; i < 255; i++) {
    j = (j + s[i] + key[i % key_len]) % 256;
    swap(s + i, s + j);
  }
  j = (j + s[255] + key[255 % key_len]) % 256;
  swap(s + 255, s + j);
}

void generate_stream(uint8_t *s, uint8_t *buffer,
                     uint8_t len) {
  uint8_t i = 0, j = 0;
  for (uint8_t c = 0; c < len; ++c) {
    i = (i + 1) % 256;
    j = (j + s[i]) % 256;
    swap(&s[i], &s[j]);
    buffer[c] = s[(s[i] + s[j]) % 256];
  }
}

void rc4(uint8_t *s, uint8_t *key, uint8_t key_len,
         char *buff, uint8_t len) {
  // process one byte at a time
  uint8_t val;
  uint8_t out;
  uint8_t i = 0;
  uint8_t j = 0;
  for (uint8_t c = 0; c < len; ++c) {
    i = (i + 1) % 256;
    j = (j + s[i]) % 256;
    swap(s + i, s + j);
    val = (s[i] + s[j]) % 256;
    buff[c] ^= val;
  }
}

int main() {
  char buffer[32];

  uint8_t s[256];

  const uint8_t message_len = 9;
  uint8_t message[9];
  message[0] = 'P';
  message[1] = 'l';
  message[2] = 'a';
  message[3] = 'i';
  message[4] = 'n';
  message[5] = 't';
  message[6] = 'e';
  message[7] = 'x';
  message[8] = 't';
  uint8_t ciphertext[9];
  uint8_t decrypted[9 + 1];
  uint8_t keystream[9];

  const uint8_t key_len = 3;
  char key[3];
  key[0] = 'K';
  key[1] = 'e';
  key[2] = 'y';

  printn_uart0(key, key_len);
  printn_uart0((char *)message, message_len);

  rc4_init(s, (uint8_t *)key, key_len);
  generate_stream(s, keystream, message_len);

   for (uint8_t i = 0; i < message_len; ++i) {
    write_int(keystream[i], buffer);
    print_uart0(buffer);
  }

   for (uint8_t i = 0; i < message_len; ++i) {
    ciphertext[i] = message[i] ^ keystream[i];
    write_int(ciphertext[i], buffer);
    print_uart0(buffer);
  }

  rc4_init(s, (uint8_t *)key, key_len);
  generate_stream(s, keystream, message_len);

   for (uint8_t i = 0; i < message_len; ++i) {
    decrypted[i] = ciphertext[i] ^ keystream[i];
    write_int(decrypted[i], buffer);
    print_uart0(buffer);
  }

  decrypted[message_len] = 0;
  printn_uart0((char *)decrypted, message_len);

  return 0;
}

void c_entry(){
  main();
}
