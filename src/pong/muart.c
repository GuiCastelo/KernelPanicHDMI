#include "muart.h"

void mini_uart_init(void) {
  // configura GPIO14 e GPIO15 como função ALT5 (mini UART)
  uint32_t sel = GPIO_REG(gpfsel[1]);
  sel = (sel & (~(7<<12))) | (2<<12);
  sel = (sel & (~(7<<15))) | (2<<15);
  GPIO_REG(gpfsel[1]) = sel;

  // habilita pull-ups em GPIO14 e GPIO15
  GPIO_REG(gppud) = 0;
  delay(150);
  GPIO_REG(gppudclk[0]) = (1 << 14) | (1 << 15);
  delay(150);
  GPIO_REG(gppudclk[0]) = 0;

  // habilita perifério e configura
  AUX_REG(enables) = 0x00000001; // habilita a mini UART
  MU_REG(cntl) = 0;
  MU_REG(ier) = 0;
  MU_REG(lcr) = 3; // 8 bits
  MU_REG(mcr) = 0;
  MU_REG(baud) = 270; // para 115200 bps em 250 MHz
  MU_REG(cntl) = 3; // habilita TX e RX
}

void mini_uart_putc(uint8_t c) {
  while((MU_REG(stat) & 0x02) == 0) ; // não há espaço
  MU_REG(io) = c;
}

void mini_uart_puts(char *s) {
	while(*s) {
		mini_uart_putc(*s);
		if(*s == '\n')
			mini_uart_putc('\r');
		s++;
	}
}

uint8_t mini_uart_getc(void) {
  while((MU_REG(stat) & 0x01) == 0); // não há dados a ler 
  return MU_REG(io);
}

static uint8_t char_table[16] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

void mini_uart_put_dword(uint32_t value) {
	mini_uart_putc( char_table[(value >> 28) & 0xF]);
	mini_uart_putc( char_table[(value >> 24) & 0xF]);
	mini_uart_putc( char_table[(value >> 20) & 0xF]);
	mini_uart_putc( char_table[(value >> 16) & 0xF]);
	mini_uart_putc( char_table[(value >> 12) & 0xF]);
	mini_uart_putc( char_table[(value >>  8) & 0xF]);
	mini_uart_putc( char_table[(value >>  4) & 0xF]);
	mini_uart_putc( char_table[(value >>  0) & 0xF]);
}

void mini_uart_putc_hex(uint8_t value) {
	mini_uart_putc( char_table[(value >>  4) & 0xF]);
	mini_uart_putc( char_table[(value >>  0) & 0xF]);
}

void mini_uart_debug_puts(char *s, uint32_t value) {
	mini_uart_puts(s);
	mini_uart_put_dword(value);
	mini_uart_puts("\n");
}