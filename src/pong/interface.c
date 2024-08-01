#include "interface.h"

fb_info_t *fb;
states_t states = {0};

unsigned long long int seed = 1;  // Semente inicial (pode ser qualquer número)
#define A 1664525                 // Constante multiplicativa
#define C 1013904223              // Constante de incremento
#define M 4294967296              // Modulo (2^32)

unsigned long long int simple_rand() {
    // LCG: Novo valor de seed é (A * seed + C) % M
    seed = (A * seed + C) % M;
    return seed;
}

int rand_range(int lower, int upper) {
    return (simple_rand() % (upper - lower + 1)) + lower;
}

void draw_delimiters() {
    uint32_t white_color = pack_color(255, 255, 255, 255);
    for(int i = 0; i < HEIGHT; i++) {
        fbPutPixel(fb, 0, i, white_color);
        fbPutPixel(fb, WIDTH-1, i, white_color);
    }
    for(int j = 0; j < WIDTH; j ++) {
        fbPutPixel(fb, j, 0, white_color);
        fbPutPixel(fb, j, HEIGHT-1, white_color);
    }
}

void create_ball() {
    uint32_t white_color = pack_color(255, 255, 255, 255);
    for(int i = 0; i < BALL_SIDE; i++) {
        for(int j = 0; j < BALL_SIDE; j++) {
            fbPutPixel(fb, states.ball_state.x_position + j, states.ball_state.y_position + i, white_color);
        }
    }
}

void delete_ball() {
    uint32_t black_color = pack_color(0, 0, 0, 0);
    for(int i = 0; i < BALL_SIDE; i++) {
        for(int j = 0; j < BALL_SIDE; j++) {
            fbPutPixel(fb, states.ball_state.x_position + j, states.ball_state.y_position + i, black_color);
        }
    }
}

void init_ball(void) {
    states.ball_state.x_position = WIDTH/2 - BALL_SIDE/2;
    states.ball_state.y_position = HEIGHT/2 - BALL_SIDE/2;
    int x_value = 0;
    do {
        x_value = rand_range(-5,5);
    } while (x_value == 0); 
    states.ball_state.delta_x = x_value;
    states.ball_state.delta_y = rand_range(-5,5);
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
    uint32_t black_color = pack_color(0, 0, 0, 0);
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
    uint32_t black_color = pack_color(0, 0, 0, 0);
    for(int i = 0; i < BAR_HEIGHT; i++) {
        for(int j = 0; j < BAR_WIDTH; j ++) {
            fbPutPixel(fb, WIDTH - j, HEIGHT/2 - BAR_HEIGHT/2 + i, black_color);
        }
    }
}

void init_left_bar() {
    create_left_bar();
    states.left_bar_state.y_position = HEIGHT/2 - BAR_HEIGHT/2;
    states.left_bar_state.delta_y = 0;
};

void init_right_bar() {
    create_right_bar();
    states.right_bar_state.y_position = HEIGHT/2 - BAR_HEIGHT/2;
    states.right_bar_state.delta_y = 0;
}

void interface_init(fb_info_t *fbInfo) {
    fb = fbInfo;
    draw_delimiters();
    init_ball();
    init_left_bar();
    init_right_bar();
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

void update_ball(ball_state_t* ball_state) {
    delete_ball();
    ball_state->x_position += ball_state->delta_x;
    ball_state->y_position += ball_state->delta_y;
    create_ball();
}

void check_colision(ball_state_t *ball_state, bar_state_t *left_bar_state, bar_state_t *right_bar_state) {
    if (ball_state->x_position<BAR_WIDTH/2 || ball_state->x_position>(WIDTH-BAR_WIDTH/2-BALL_SIDE)) { // Colisao nos delimitadores laterais
        restart_interface();
    }
    else if (ball_state->y_position<4 || ball_state->y_position>(HEIGHT-BALL_SIDE-4)) { // Colisao no delimitador superior ou inferior
        ball_state->delta_y = -ball_state->delta_y;
    }
    else if (ball_state->x_position<(BAR_WIDTH+4) && (ball_state->y_position >= left_bar_state->y_position && ball_state->y_position <= (left_bar_state->y_position + BAR_HEIGHT))) { // Colisao na barra esquerda
        ball_state->delta_x = -ball_state->delta_x;
    }
    else if (ball_state->x_position>(WIDTH - BAR_WIDTH - 4 - BALL_SIDE) && (ball_state->y_position >= right_bar_state->y_position && ball_state->y_position <= (right_bar_state->y_position + BAR_HEIGHT))) { // Colisao na barra direita
        ball_state->delta_x = -ball_state->delta_x;
    }
}

void update_interface(void) {
    check_colision(&states.ball_state, &states.left_bar_state, &states.right_bar_state);
    update_ball(&states.ball_state);
}

void update_bar(char action) {
    
}