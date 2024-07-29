#include "interface.h"

void interface_init(fb_info_t *fbInfo) {
    // Um pixel vermelho no centro da tela
    uint32_t cor = pack_color(255, 0, 0, 255);
    fbPutPixel(fbInfo, 400, 300, cor);
}

void update_bar(char action) {
    
}

void update_ball(void) {

}