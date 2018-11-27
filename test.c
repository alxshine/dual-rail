volatile unsigned int * const UART0DR = (unsigned int *)0x101f1000;
 
void print_uart0(const char *s) {
 while(*s != '\0') { /* Loop until end of string */
 *UART0DR = (unsigned int)(*s); /* Transmit char */
 s++; /* Next char */
 }
}

void other_test(){
	for (int i = 0; i < 10; ++i) {
		print_uart0("Hello world!\n");
	}
}
 
void c_entry() {
	other_test();
}
