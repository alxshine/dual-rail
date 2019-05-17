#ifndef _PRINT_H
#define _PRINT_H

volatile unsigned int *const UART0DR = (unsigned int *)0x101f1000;

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

void printn_uart0(const char *s, int n) {
  for (int i = 0; i < n; ++i) {
    *UART0DR = (unsigned int)(*s++);
  }
  *UART0DR = (unsigned int)('\n');
}

void print_uart0(const char *s) {
  while (*s != '\0') {             /* Loop until end of string */
    *UART0DR = (unsigned int)(*s); /* Transmit char */
    s++;                           /* Next char */
  }
  *UART0DR = (unsigned int)('\n');
}

#endif
