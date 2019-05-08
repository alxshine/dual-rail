#ifndef _PASS_PRINT_H
#define _PASS_PRINT_H

volatile unsigned int *const pass_UART0DR = (unsigned int *)0x101f1000;

char pass_hexChars[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
                          '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void pass_printn_uart0(const char *s, int n) {
  for (int i = 0; i < n; ++i) {
    *pass_UART0DR = (unsigned int)(*s++);
  }
  *pass_UART0DR = (unsigned int)('\n');
}

void pass_print_uart0(const char *s) {
  while (*s != '\0') {                  /* Loop until end of string */
    *pass_UART0DR = (unsigned int)(*s); /* Transmit char */
    s++;                                /* Next char */
  }
  *pass_UART0DR = (unsigned int)('\n');
}

void pass_write_int(int source, char *dest) {
  int index = 0;
  dest[index++] = '0';
  dest[index++] = 'x';
  for (int i = 28; i >= 0; i -= 4) {
    int bits = (((0xF) << i) & source) >> i;
    dest[index++] = pass_hexChars[bits];
  }
  dest[index] = '\0';
}

#endif
