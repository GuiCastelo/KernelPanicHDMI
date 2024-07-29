#include "interface.h"
#include "common.h"

void create_ball(fb_info_t *fbInfo, uint32_t cor);
void create_left_bar(fb_info_t *fbInfo, uint32_t cor);
void create_right_bar(fb_info_t *fbInfo, uint32_t cor);


void interface_init(fb_info_t *fbInfo) {
    uint32_t cor = pack_color(255, 255, 255, 255);
    create_ball(fbInfo, cor);
    create_left_bar(fbInfo, cor);
    create_right_bar(fbInfo, cor);
}

void create_ball(fb_info_t *fbInfo, uint32_t cor) {
    for(int i = 0; i < BALL_SIDE; i++) {
        for(int j = 0; j < BALL_SIDE; j++) {
            fbPutPixel(fbInfo, WIDTH/2 - BALL_SIDE/2 + j, HEIGHT/2 - BALL_SIDE/2 + i, cor);
        }
    }
}

void start_ball() {
    
}

void create_left_bar(fb_info_t *fbInfo, uint32_t cor) {
    for(int i = 0; i < BAR_HEIGHT; i++) {
        for(int j = 0; j < BAR_WIDTH; j ++) {
            fbPutPixel(fbInfo, 0 + j, HEIGHT/2 - BAR_HEIGHT/2 + i, cor);
        }
    }
}

void create_right_bar(fb_info_t *fbInfo, uint32_t cor) {
    for(int i = 0; i < BAR_HEIGHT; i++) {
        for(int j = 0; j < BAR_WIDTH; j ++) {
            fbPutPixel(fbInfo, WIDTH - j, HEIGHT/2 - BAR_HEIGHT/2 + i, cor);
        }
    }
}

void update_bar(char action) {
    
}

void update_ball(void) {
    
}