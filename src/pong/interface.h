
#ifndef __INTERFACE_H_
#define __INTERFACE_H__

#include "framebuffer.h"

void interface_init(fb_info_t *fbInfo);
void update_bar(char action);
void update_ball(void);

#endif