#ifndef __FB_H__
#define __FB_H__

#include <stdbool.h>
#include <stdint.h>

bool init_fb(void);
void fb_pixel(unsigned x, unsigned y, unsigned c);
uint32_t pack_color(uint8_t r, uint8_t g, uint8_t b);

#endif
