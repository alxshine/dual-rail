#include "print.h"

void string_copy(char *source, char *dest, int n) {
  for (int i = 0; i < n; i++)
    dest[i] = source[i];
  dest[n] = '\0';
}

void write_int(int source, char *dest) {
  char hexChars[16];
  hexChars[0] = '0';
  hexChars[1] = '1';
  hexChars[2] = '2';
  hexChars[3] = '3';
  hexChars[4] = '4';
  hexChars[5] = '5';
  hexChars[6] = '6';
  hexChars[7] = '7';
  hexChars[8] = '8';
  hexChars[9] = '9';
  hexChars[10] = 'A';
  hexChars[11] = 'B';
  hexChars[12] = 'C';
  hexChars[13] = 'D';
  hexChars[14] = 'E';
  hexChars[15] = 'F';

  int index = 0;
  dest[index++] = '0';
  dest[index++] = 'x';
  for (int i = 28; i >= 0; i -= 4) {
    int bits = (((0xF) << i) & source) >> i;
    dest[index++] = hexChars[bits];
  }
  dest[index] = '\0';
}

void test(char t){
  char buffer[20];
  write_int(t, buffer);
  print_uart0(buffer);
}

char t = 3;

void c_entry() {
  char buffer[20];
  for (char i = 0; i < 100; i++) {
    i = i*2;
    /*if (i % 15 == 0)*/
      /*string_copy("fizzbuzz", buffer, 8);*/
    /*else if (i % 5 == 0)*/
      /*string_copy("buzz", buffer, 4);*/
    /*else if (i % 3 == 0)*/
      /*string_copy("fizz", buffer, 4);*/
    /*else*/
      write_int(i, buffer);

    print_uart0(buffer);
  }
}
