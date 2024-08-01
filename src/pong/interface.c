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
    draw_delimiters();
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
    check_colision(&states.ball_state, &states.left_bar_state, &states.right_bar_state);
}

void restart_interface() {
    delete_ball();
    delete_left_bar();
    delete_right_bar();
    draw_delimiters();
    init_ball();
    create_left_bar();
    create_right_bar();
};

void check_colision(ball_state_t *ball_state, bar_state_t *left_bar_state, bar_state_t *right_bar_state) {
    if (ball_state->x_position==0 || ball_state->x_position==(WIDTH-BALL_SIDE)) { // Colisao nos delimitadores laterais
        restart_interface();
    }
    else if (ball_state->y_position==0 || ball_state->y_position==(HEIGHT-BALL_SIDE)) { // Colisao no delimitador superior ou inferior
        ball_state->delta_y = -ball_state->delta_y;
    }
    else if (ball_state->x_position==(BAR_WIDTH) && (ball_state->y_position > left_bar_state->y_position && ball_state->y_position < (left_bar_state->y_position + BAR_HEIGHT))) { // Colisao na barra esquerda
        ball_state->delta_x = -ball_state->delta_x;
    }
    else if (ball_state->x_position==(WIDTH - BAR_WIDTH) && (ball_state->y_position > right_bar_state->y_position && ball_state->y_position < (right_bar_state->y_position + BAR_HEIGHT))) { // Colisao na barra direita
        ball_state->delta_x = -ball_state->delta_x;
    }
}

void draw_delimiters() {
    uint32_t white_color = pack_color(255, 255, 255, 255);
    for(int i = 0; i < HEIGHT; i++) {
        fbPutPixel(fb, 0, i, white_color);
        fbPutPixel(fb, WIDTH, i, white_color);
    }
    for(int j = 0; j < WIDTH; j ++) {
        fbPutPixel(fb, j, 0, white_color);
        fbPutPixel(fb, j, HEIGHT, white_color);
    }
}

void update_bar(char action) {
    
}