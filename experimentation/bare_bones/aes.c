#include "print.h"

#include "plaintexts.h"
#include "tinyAES.h"

#define OUTPIN 6
uint8_t key[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
uint8_t buf[16];

void c_entry() {
  for (int i = 0; i < 5; ++i) {
    const char *plaintext = plaintexts[i++];
    printn_uart0(plaintext, 16);
    AES128_ECB_encrypt((uint8_t *)plaintext, key, buf);
    printn_uart0((char*)buf, 16);
  }
}
