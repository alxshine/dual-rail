volatile unsigned int *const UART0DR = (unsigned int *)0x101f1000;

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
