#include "print.h"

char hexChars[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
                     '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void string_copy(char *source, char *dest, int n) {
  for (int i = 0; i < n; i++)
    dest[i] = source[i];
  dest[n] = '\0';
}

void write_int(int source, char *dest) {
  int index = 0;
  dest[index++] = '0';
  dest[index++] = 'x';
  for (int i = 28; i >= 0; i -= 4) {
    int bits = (((0xF) << i) & source) >> i;
    dest[index++] = hexChars[bits];
  }
  dest[index] = '\0';
}

void c_entry() {
  char buffer[20];
  char b = 0xb;
  for(char i = 0; i<10; ++i){
    write_int(b, buffer);
    print_uart0(buffer);
    write_int(i, buffer);
    print_uart0(buffer);
    char test = b ^ i;
    write_int(test, buffer);
    print_uart0(buffer);
  }

  /*for (char i = 0; i < 100; i++) {*/
    /*if (i % 15 == 0)*/
      /*string_copy("fizzbuzz", buffer, 8);*/
    /*else if (i % 5 == 0)*/
      /*string_copy("buzz", buffer, 4);*/
    /*else if (i % 3 == 0)*/
      /*string_copy("fizz", buffer, 4);*/
    /*else*/
      /*write_int(i, buffer);*/

    /*print_uart0(buffer);*/
  /*}*/
}
