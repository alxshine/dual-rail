
/*
  Cyrus.Sh
  ~cyn
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(unsigned char *p1, unsigned char *p2) {
  unsigned char t = *p1;
  *p1 = *p2;
  *p2 = t;
}

void rc4_init(unsigned char *s, unsigned char *key, unsigned char key_len) {
  unsigned char i, j = 0;
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

void generate_stream(unsigned char *s, unsigned char *buffer,
                     unsigned char len) {
  unsigned char i = 0, j = 0;
  for (unsigned char c = 0; c < len; ++c) {
    i = (i + 1) % 256;
    j = (j + s[i]) % 256;
    swap(&s[i], &s[j]);
    buffer[c] = s[(s[i] + s[j]) % 256];
  }
}

void rc4(unsigned char *s, unsigned char *key, unsigned char key_len,
         char *buff, unsigned char len) {
  // process one byte at a time
  unsigned char val;
  unsigned char out;
  unsigned char i = 0;
  unsigned char j = 0;
  for (unsigned char c = 0; c < len; ++c) {
    i = (i + 1) % 256;
    j = (j + s[i]) % 256;
    swap(s + i, s + j);
    val = (s[i] + s[j]) % 256;
    buff[c] ^= val;
  }
}

int main() {
  unsigned char s[256];

  const unsigned char message_len = 9;
  unsigned char message[message_len] = "Plaintext";
  unsigned char ciphertext[message_len];
  unsigned char decrypted[message_len + 1];
  unsigned char keystream[message_len];

  const unsigned char key_len = 3;
  char key[key_len] = "Key";

  printf("Key: %s\n", key);
  printf("Plaintext: %s\n", message);

  rc4_init(s, (unsigned char *)key, key_len);
  generate_stream(s, keystream, message_len);

  printf("keystream: ");
  for (unsigned char i = 0; i < message_len; ++i) {
    printf("%02x ", keystream[i]);
  }
  printf("\n");

  printf("ciphertext: ");
  for (unsigned char i = 0; i < message_len; ++i) {
    ciphertext[i] = message[i] ^ keystream[i];
    printf("%02x ", ciphertext[i]);
  }
  printf("\n");

  rc4_init(s, (unsigned char *)key, key_len);
  generate_stream(s, keystream, message_len);

  printf("decrypted: ");
  for (unsigned char i = 0; i < message_len; ++i) {
    decrypted[i] = ciphertext[i] ^ keystream[i];
    printf("%02x ", decrypted[i]);
  }
  printf("\n");
  decrypted[message_len] = 0;
  printf("%s\n", decrypted);
}
