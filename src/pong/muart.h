#ifndef _MUART_H_
#define _MUART_H_

#include "bcm.h"
#include <stdint.h>

extern void delay(unsigned);

void mini_uart_init(void);
void mini_uart_putc(uint8_t c);
uint8_t mini_uart_getc(void);
void mini_uart_puts(char *s);

#endif