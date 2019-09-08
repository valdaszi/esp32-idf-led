#ifdef __cplusplus
extern "C" {
#endif

#include "dled_pixel.h"

void dled_pixel_set(pixel_t* pixel, uint8_t r, uint8_t g, uint8_t b)
{
	if (pixel == NULL) return;
	pixel->r = r, pixel->g = g, pixel->b = b;
}

void dled_pixel_off(pixel_t* pixel)
{
	if (pixel == NULL) return;
	pixel->r = 0, pixel->g = 0, pixel->b = 0;
}

void dled_pixel_set_color(pixel_t *pixels, uint16_t length, uint8_t r, uint8_t g, uint8_t b)
{
    if (pixels == NULL) return;
    if (length == 0)    return;

    for (uint16_t idx = 0; idx < length; idx++) {
        dled_pixel_set(&pixels[idx], r, g, b);
    }
}

#ifdef __cplusplus
}
#endif