#ifndef MAIN_DLED_PIXEL_H_
#define MAIN_DLED_PIXEL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>
#include "dled_types.h"

/**
 * @brief Set the pixel_t from RGB.
 * @param[in,out] pixel   Pointer to the pixel_t object to be changed.
 * @param[in]     r, g, b The RGB color components.
 */
void dled_pixel_set(pixel_t* pixel, uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief Set the pixel_t to off (all zero).
 * @param[in,out] pixel Pointer to the pixel_t object to be changed.
 */
void dled_pixel_off(pixel_t* pixel);

/**
 * @brief Set all strip color to RGB.
 * @param[in,out] pixels    The pixels to be set.
 * @param[in]     length    Number of pixels.
 * @param[in]     r, g, b   The RGB color components.
 */ 
void dled_pixel_set_color(pixel_t *pixels, uint16_t length, uint8_t r, uint8_t g, uint8_t b);


#ifdef __cplusplus
}
#endif

#endif