#pragma once

#include <stdint.h>
#include "bcm.h"
#include "interface.h"
#include "muart.h"

void trata_irq(void);
void irq_init(void);
void enable_timer_irq(void);
void enable_mini_uart_irq(void);
extern void enable_irq(void);