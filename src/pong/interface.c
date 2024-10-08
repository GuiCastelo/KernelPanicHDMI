#include "interface.h"

fb_info_t *fb;
states_t states = {0};

unsigned long long int seed = 1;  // Semente inicial (pode ser qualquer número)
#define A 1664525                 // Constante multiplicativa
#define C 1013904223              // Constante de incremento
#define M 4294967296              // Modulo (2^32)

void debug_states(void);
void debug_ball_state(void);

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
        x_value = rand_range(-MAX_BALL_SPEED, MAX_BALL_SPEED);
    } while (x_value == 0); 
    states.ball_state.delta_x = x_value;
    states.ball_state.delta_y = rand_range(-MAX_BALL_SPEED, MAX_BALL_SPEED);
    create_ball();
}

void create_left_bar(void) {
    uint32_t white_color = pack_color(255, 255, 255, 255);
    for(int i = 0; i < BAR_HEIGHT; i++) {
        for(int j = 0; j < BAR_WIDTH; j ++) {
            fbPutPixel(fb, j, states.left_bar_state.y_position + i, white_color);
        }
    }
}

void delete_left_bar(void) {
    uint32_t black_color = pack_color(0, 0, 0, 0);
    for(int i = 0; i < BAR_HEIGHT; i++) {
        for(int j = 0; j < BAR_WIDTH; j ++) {
            fbPutPixel(fb, j, states.left_bar_state.y_position + i, black_color);
        }
    }
}

void create_right_bar(void) {
    uint32_t white_color = pack_color(255, 255, 255, 255);
    for(int i = 0; i < BAR_HEIGHT; i++) {
        for(int j = 0; j < BAR_WIDTH; j ++) {
            fbPutPixel(fb, WIDTH - j, states.right_bar_state.y_position + i, white_color);
        }
    }
}

void delete_right_bar(void) {
    uint32_t black_color = pack_color(0, 0, 0, 0);
    for(int i = 0; i < BAR_HEIGHT; i++) {
        for(int j = 0; j < BAR_WIDTH; j ++) {
            fbPutPixel(fb, WIDTH - j, states.right_bar_state.y_position + i, black_color);
        }
    }
}

void init_left_bar() {
    states.left_bar_state.y_position = HEIGHT/2 - BAR_HEIGHT/2;
    states.left_bar_state.delta_y = 0;
    create_left_bar();
};

void init_right_bar() {
    states.right_bar_state.y_position = HEIGHT/2 - BAR_HEIGHT/2;
    states.right_bar_state.delta_y = 0;
    create_right_bar();
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
    init_left_bar();
    init_right_bar();
};

void update_ball(ball_state_t* ball_state) {
    delete_ball();
    ball_state->x_position += ball_state->delta_x;
    ball_state->y_position += ball_state->delta_y;
    create_ball();
}

void update_bar(bar_state_t* left_bar_state, bar_state_t* right_bar_state) {

    // if ((left_bar_state->delta_y != 0) &&
    //     !(left_bar_state->y_position < (BAR_MOVEMENT_SPEED + 1) && left_bar_state->delta_y < 0) &&
    //     !(left_bar_state->y_position > HEIGHT - BAR_HEIGHT - (BAR_MOVEMENT_SPEED + 1) && left_bar_state->delta_y > 0)) {
    //         delete_left_bar();
    //         left_bar_state->y_position += left_bar_state->delta_y;
    //         create_left_bar();
    //         //debug_states();
    //         left_bar_state->delta_y = 0;
    // }

    if (left_bar_state->delta_y != 0) {
        if (left_bar_state->delta_y < 0) {
            if (left_bar_state->y_position < (BAR_MOVEMENT_SPEED + 1)) {
                delete_left_bar();
                left_bar_state->y_position = 0;
                create_left_bar();
                //debug_states();
                left_bar_state->delta_y = 0;
            } else {
                delete_left_bar();
                left_bar_state->y_position += left_bar_state->delta_y;
                create_left_bar();
                //debug_states();
                left_bar_state->delta_y = 0;
            }
        }

        if (left_bar_state ->delta_y > 0) {
            if (left_bar_state->y_position > HEIGHT - BAR_HEIGHT - (BAR_MOVEMENT_SPEED + 1)) {
                delete_left_bar();
                left_bar_state->y_position = HEIGHT - BAR_HEIGHT;
                create_left_bar();
                //debug_states();
                left_bar_state->delta_y = 0;
            } else {
                delete_left_bar();
                left_bar_state->y_position += left_bar_state->delta_y;
                create_left_bar();
                //debug_states();
                left_bar_state->delta_y = 0;
            }
        }
    }

    // if ((right_bar_state->delta_y != 0) &&
    //     !(right_bar_state->y_position < (BAR_MOVEMENT_SPEED + 1) && right_bar_state->delta_y < 0) &&
    //     !(right_bar_state->y_position > HEIGHT - BAR_HEIGHT - (BAR_MOVEMENT_SPEED + 1) && right_bar_state->delta_y > 0)) {
    //         delete_right_bar();
    //         right_bar_state->y_position += right_bar_state->delta_y;
    //         create_right_bar();
    //         //debug_states();
    //         right_bar_state->delta_y = 0;
    // }

    if (right_bar_state->delta_y != 0) {
        if (right_bar_state->delta_y < 0) {
            if (right_bar_state->y_position < (BAR_MOVEMENT_SPEED + 1)) {
                delete_right_bar();
                right_bar_state->y_position = 0;
                create_right_bar();
                //debug_states();
                right_bar_state->delta_y = 0;
            } else {
                delete_right_bar();
                right_bar_state->y_position += right_bar_state->delta_y;
                create_right_bar();
                //debug_states();
                right_bar_state->delta_y = 0;
            }
        }

        if (right_bar_state ->delta_y > 0) {
            if (right_bar_state->y_position > HEIGHT - BAR_HEIGHT - (BAR_MOVEMENT_SPEED + 1)) {
                delete_right_bar();
                right_bar_state->y_position = HEIGHT - BAR_HEIGHT;
                create_right_bar();
                //debug_states();
                right_bar_state->delta_y = 0;
            } else {
                delete_right_bar();
                right_bar_state->y_position += right_bar_state->delta_y;
                create_right_bar();
                //debug_states();
                right_bar_state->delta_y = 0;
            }
        }
    }

    draw_delimiters();
}

void check_colision(ball_state_t *ball_state, bar_state_t *left_bar_state, bar_state_t *right_bar_state) {
    if (ball_state->x_position<BAR_WIDTH/2 || ball_state->x_position>(WIDTH-BAR_WIDTH/2-BALL_SIDE)) { // Colisao nos delimitadores laterais
        restart_interface();
    }
    else if (ball_state->y_position<(MAX_BALL_SPEED + 1) || ball_state->y_position>(HEIGHT-BALL_SIDE-(MAX_BALL_SPEED + 1))) { // Colisao no delimitador superior ou inferior
        ball_state->delta_y = -ball_state->delta_y;
    }
    else if (ball_state->x_position<(BAR_WIDTH+(MAX_BALL_SPEED + 1)) && (ball_state->y_position >= left_bar_state->y_position && ball_state->y_position <= (left_bar_state->y_position + BAR_HEIGHT))) { // Colisao na barra esquerda
        mini_uart_puts("Colisão na barra da esquerda:\n");
        debug_ball_state();
        int colision_height_normalized = ((ball_state->y_position - left_bar_state->y_position) / (BAR_HEIGHT/(2*MAX_BALL_SPEED))) - MAX_BALL_SPEED;
        ball_state->delta_y = colision_height_normalized;
        if(colision_height_normalized < 0) colision_height_normalized = -colision_height_normalized;
        ball_state->delta_x = (MAX_BALL_SPEED + 1) - colision_height_normalized;
        debug_ball_state();
    }
    else if (ball_state->x_position>(WIDTH - BAR_WIDTH - (MAX_BALL_SPEED + 1) - BALL_SIDE) && (ball_state->y_position >= right_bar_state->y_position && ball_state->y_position <= (right_bar_state->y_position + BAR_HEIGHT))) { // Colisao na barra direita
        mini_uart_puts("Colisão na barra da direita:\n");
        debug_ball_state();
        int colision_height_normalized = ((ball_state->y_position - right_bar_state->y_position) / (BAR_HEIGHT/(2*MAX_BALL_SPEED))) - MAX_BALL_SPEED;
        ball_state->delta_y = colision_height_normalized;
        if(colision_height_normalized < 0) colision_height_normalized = -colision_height_normalized;
        ball_state->delta_x = -((MAX_BALL_SPEED + 1) - colision_height_normalized);
        debug_ball_state();
    }
}

void update_interface(void) {
    check_colision(&states.ball_state, &states.left_bar_state, &states.right_bar_state);
    update_ball(&states.ball_state);
    update_bar(&states.left_bar_state, &states.right_bar_state);
}

void debug_bar_states(void) {
    mini_uart_debug_puts("Left bar y position: ", states.left_bar_state.y_position);
    mini_uart_debug_puts("Left bar delta y: ", states.left_bar_state.delta_y);
    mini_uart_debug_puts("Right bar state y position: ", states.right_bar_state.y_position);
    mini_uart_debug_puts("Right bar state delta y: ", states.right_bar_state.delta_y);
    mini_uart_puts("\n");
}

void debug_ball_state(void) {
    mini_uart_debug_puts("Ball y position: ", states.ball_state.y_position);
    mini_uart_debug_puts("Ball delta y: ", states.ball_state.delta_y);
    mini_uart_debug_puts("Ball x position: ", states.ball_state.x_position);
    mini_uart_debug_puts("Ball delta x: ", states.ball_state.delta_x);
    mini_uart_puts("\n");
}

void check_action(char action) {
    if (action == 'w') {
        states.left_bar_state.delta_y = -BAR_MOVEMENT_SPEED;
    }
    else if (action == 's') {
        states.left_bar_state.delta_y = BAR_MOVEMENT_SPEED;
    }
    else if (action == 'o') {
        states.right_bar_state.delta_y = -BAR_MOVEMENT_SPEED;
    }
    else if (action == 'l') {
        states.right_bar_state.delta_y = BAR_MOVEMENT_SPEED;
    }
}