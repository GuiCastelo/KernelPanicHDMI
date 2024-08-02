#pragma once

#include <stdint.h>
#include "bcm.h"
#include "uart.h"
#include "interface.h"

void trata_irq(void);
void irq_init(void);
extern void enable_irq(void);