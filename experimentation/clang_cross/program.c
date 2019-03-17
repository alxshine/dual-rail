#include "print.h"

char hexChars[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
                     '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void string_copy(char *source, char *dest, int n) {
  for (int i = 0; i < n; i++)
    dest[i] = source[i];
}

int power(int base, int exp) {
  int ret = base;
  for (int i = 1; i < exp; i++)
    ret *= base;
  return ret;
}

int div(int a, int b) {
  int ret = 0;
  while (a > b) {
    ret++;
    a -= b;
  }
  return ret;
}

void write_int(int source, char *dest) {
  int index = 0;
  for (int i = 28; i >= 0; i -= 4) {
    int bits = (((0xF) << 28) & source) >> i;
    dest[index] = hexChars[bits];
  }
  dest[index] = '\0';
}

void c_entry() {
  char buffer[20];
  print_uart0("Beginning\0");
  for (int i = 0; i < 100; i++) {
    /* if (i % 15 == 0) */
    /*   string_copy("fizzbuzz", buffer, 8); */
    /* else if (i % 5 == 0) */
    /*   string_copy("buzz", buffer, 4); */
    /* else if (i % 3 == 0) */
    /*   string_copy("fizz", buffer, 4); */
    /* else */
    /*   write_int(i, buffer); */

    /* print_uart0(buffer); */
    write_int(i, buffer);
    /*print_uart0(buffer);*/
  }
}
