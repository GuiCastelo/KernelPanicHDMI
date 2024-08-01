#include "uart.h"

void uart_init() {
	//gpio14 : alt0
	//gpio15 : alt0
    uint32_t sel = GPIO_REG(gpfsel[1]);
    sel = (sel & (~(7 << 12))) | (4 << 12);
    sel = (sel & (~(7 << 12))) | (4 << 12);
	GPIO_REG(gpfsel[1]) = sel;
	delay(150);
    UART_REG(cr) = 0x00000000;
    GPIO_REG(gppud) = 0x00000001;
	delay(150);
    
    uint32_t clk_en = GPIO_REG(gppudclk[0]);
    clk_en = clk_en | (1 << 14) | (1 << 15);
    GPIO_REG(gppudclk[0]) = clk_en;
	delay(150);
    GPIO_REG(gppudclk[0]) = 0x00000000;
    
	//PUT32(UART0_ICR,  0x7FF);
	UART_REG(ibrd) = 1; //PUT32(UART0_IBRD, 1);
	UART_REG(fbrd) = 40; //PUT32(UART0_FBRD, 40);
	UART_REG(lcrh) = 0x00000070;//(UART0_LCRH, 0x00000070);
	//PUT32(UART0_IMSC,
	//		(1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
	//		(1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));
	UART_REG(cr) = 0x00000301;// PUT32(UART0_CR, 0x00000301);
}

void uart_putc(uint8_t c) {
    while (UART_REG(fr) & (1 << 5) )
	    delay(1);
	UART_REG(dr) = c;
}