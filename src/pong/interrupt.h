#pragma once

#include <stdint.h>
#include "bcm.h"
#include "interface.h"
#include "muart.h"

void trata_irq(void);
void irq_init(void);
extern void enable_irq(void);