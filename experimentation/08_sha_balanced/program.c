#include "print.h"
#include "keccak.h"

char *in_string = "abcdefghijklmnopqrstuvwxyz";

void c_entry() {
  uint8_t out[32];
  char buffer[16];
  print_uart0(in_string);
  sha3_256(out, 32, (uint8_t*) in_string, 26);

  /*for(char i = 0; i<32; ++i){*/
    /*write_int(out[i], buffer);*/
    /*print_uart0(buffer);*/
  /*}*/
}
