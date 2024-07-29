#include "interface.h"

fb_info_t *fb;
states_t states = {0};

void create_ball() {
    uint32_t white_color = pack_color(255, 255, 255, 255);
    
    for(int i = 0; i < BALL_SIDE; i++) {
        for(int j = 0; j < BALL_SIDE; j++) {
            fbPutPixel(fb, states.ball_state.x_position + j, states.ball_state.y_position + i, white_color);
        }
    }
}

void delete_ball() {
    uint32_t black_color = pack_color(0, 0, 0, 255);
        
    for(int i = 0; i < BALL_SIDE; i++) {
        for(int j = 0; j < BALL_SIDE; j++) {
            fbPutPixel(fb, states.ball_state.x_position + j, states.ball_state.y_position + i, black_color);
        }
    }
}

void init_ball(void) {
    states.ball_state.x_position = WIDTH/2 - BALL_SIDE/2;
    states.ball_state.y_position = HEIGHT/2 - BALL_SIDE/2;
    states.ball_state.delta_x = 3;
    states.ball_state.delta_y = 1;
    create_ball();
}

void create_left_bar(void) {
    uint32_t white_color = pack_color(255, 255, 255, 255);

    for(int i = 0; i < BAR_HEIGHT; i++) {
        for(int j = 0; j < BAR_WIDTH; j ++) {
            fbPutPixel(fb, 0 + j, HEIGHT/2 - BAR_HEIGHT/2 + i, white_color);
        }
    }
}

void delete_left_bar(void) {
    uint32_t black_color = pack_color(0, 0, 0, 255);

    for(int i = 0; i < BAR_HEIGHT; i++) {
        for(int j = 0; j < BAR_WIDTH; j ++) {
            fbPutPixel(fb, 0 + j, HEIGHT/2 - BAR_HEIGHT/2 + i, black_color);
        }
    }
}

void create_right_bar(void) {
    uint32_t white_color = pack_color(255, 255, 255, 255);

    for(int i = 0; i < BAR_HEIGHT; i++) {
        for(int j = 0; j < BAR_WIDTH; j ++) {
            fbPutPixel(fb, WIDTH - j, HEIGHT/2 - BAR_HEIGHT/2 + i, white_color);
        }
    }
}

void delete_right_bar(void) {
    uint32_t black_color = pack_color(0, 0, 0, 255);

    for(int i = 0; i < BAR_HEIGHT; i++) {
        for(int j = 0; j < BAR_WIDTH; j ++) {
            fbPutPixel(fb, WIDTH - j, HEIGHT/2 - BAR_HEIGHT/2 + i, black_color);
        }
    }
}

void interface_init(fb_info_t *fbInfo) {
    fb = fbInfo;

    init_ball();
    create_left_bar();
    create_right_bar();
}

void update_ball(ball_state_t* ball_state) {
    delete_ball();
    ball_state->x_position += ball_state->delta_x;
    ball_state->y_position += ball_state->delta_y;
    create_ball();
}

void update_interface(void) {
    update_ball(&states.ball_state);
}

void update_bar(char action) {
    
}