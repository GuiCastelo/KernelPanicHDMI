
#ifndef __INTERFACE_H_
#define __INTERFACE_H__

#include "framebuffer.h"

void interface_init(fb_info_t *fbInfo);
void update_bar(char action);
void update_ball(void);

#define WIDTH 1920
#define HEIGHT 1080

#define BALL_SIDE 20

#define BAR_WIDTH (0.015*WIDTH)
#define BAR_HEIGHT (0.2*HEIGHT)

typedef struct states
{
    /* data */
};


#endif