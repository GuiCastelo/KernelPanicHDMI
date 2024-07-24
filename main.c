
#include <stdio.h>
#include "fb.h"

void main(void) {
   bool ok = init_fb();
   // seria sábio tratar o valor retornado por init_fb()...

   // Um pixel vermelho no centro da tela
   unsigned cor = pack_color(255, 0, 0);
   fb_pixel(400, 300, cor);

   for(;;) {
   }
}


