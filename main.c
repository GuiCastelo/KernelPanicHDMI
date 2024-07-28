
#include <stdio.h>
#include "fb.h"
#include "bcm.h"

void alerta_ok(void);
void alerta_erro(void);

void main(void) {
   bool ok = init_fb();
   // seria sábio tratar o valor retornado por init_fb()...
   if(ok) {
      alerta_ok();
   } else {
      alerta_erro();
   }

   // Um pixel vermelho no centro da tela
   unsigned cor = pack_color(255, 0, 0);
   fb_pixel(400, 300, cor);

   for(;;) {
   }
}

void alerta_ok(void) {
   // zera os bits 22 e 23 e seta o bit 21 de gpfsel[1] (saída)
   GPIO_REG(gpfsel[2]) = (GPIO_REG(gpfsel[2]) & (~(0x07)))|(0x01);

   // ativa led
   GPIO_REG(gpset[0]) = 0x01 << 20;
}

void alerta_erro(void) {
   // zera os bits 22 e 23 e seta o bit 21 de gpfsel[1] (saída)
   GPIO_REG(gpfsel[2]) = (GPIO_REG(gpfsel[2]) & (~(0x07<<3)))|(0x01<<3);

   // ativa led
   GPIO_REG(gpset[0]) = 0x01 << 21;
}


