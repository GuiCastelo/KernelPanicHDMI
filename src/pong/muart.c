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
  AUX_REG(enables) = 1;
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
  while((MU_REG(stat) & 0x01) == 0) ; // não há dados a ler
  return MU_REG(io);
}