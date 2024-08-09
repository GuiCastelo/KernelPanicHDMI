
#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include "framebuffer.h"
#include "muart.h"

void interface_init(fb_info_t *fbInfo);
void update_interface(void);
void check_action(char action);
void delete_ball();

#define WIDTH 1920
#define HEIGHT 1080

#define BALL_SIDE 20
#define MAX_BALL_SPEED 5

#define BAR_WIDTH 28
#define BAR_HEIGHT 216
#define BAR_MOVEMENT_SPEED 50

typedef struct {
    uint32_t x_position;
    uint32_t y_position;
    int      delta_x;
    int      delta_y;
} ball_state_t;

typedef struct {
    uint32_t y_position;
    int      delta_y;
} bar_state_t;

typedef struct {
    ball_state_t ball_state;
    bar_state_t left_bar_state;
    bar_state_t right_bar_state;
} states_t;

#endif