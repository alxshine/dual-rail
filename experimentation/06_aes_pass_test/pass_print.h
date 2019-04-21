#ifndef _PASS_PRINT_H
#define _PASS_PRINT_H

volatile unsigned int *const pass_UART0DR = (unsigned int *)0x101f1000;

void pass_printn_uart0(const char *s, int n) {
  for (int i = 0; i < n; ++i) {
    *pass_UART0DR = (unsigned int)(*s++);
  }
  *pass_UART0DR = (unsigned int)('\n');
}

void pass_print_uart0(const char *s) {
  while (*s != '\0') {             /* Loop until end of string */
    *pass_UART0DR = (unsigned int)(*s); /* Transmit char */
    s++;                           /* Next char */
  }
  *pass_UART0DR = (unsigned int)('\n');
}

#endif
