#include "print.h"

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
  int char_index = 0;
  if (source < 0) {
    dest[0] = '-';
    source = -source;
    char_index++;
  }

  int highest_power = 0;
  int tmp = source;
  do {
    tmp = div(tmp, 10);
    highest_power++;
  } while (source > 0);

  do {
    highest_power--;
    int current_power = power(10, highest_power);
    int digit = div(source, current_power);
    dest[char_index++] = digit + 0x30;
    tmp = div(tmp, 10);
  } while (source > 0);
  dest[char_index++] = '\0';
}

void c_entry() {
  char buffer[20];
  print_uart0("Beginning\0");
  for (int i = 0; i < 100; i++) {
    if (i % 15 == 0)
      string_copy("fizzbuzz", buffer, 8);
    else if (i % 5 == 0)
      string_copy("buzz", buffer, 4);
    else if (i % 3 == 0)
      string_copy("fizz", buffer, 4);
    else
      write_int(i, buffer);

    print_uart0(buffer);
  }
}
