#include "fb.h"

void interface_init(void) {
    // Um pixel vermelho no centro da tela
    unsigned cor = pack_color(255, 0, 0);
    fb_pixel(400, 300, cor);
}

void update_bar(char action) {
    
}

void update_ball(void) {

}