#ifndef LED_ANIMATIONS_H_
#define LED_ANIMATIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "led/Led.hpp"

#define ANIMATION_FPS   50

/**
 * @brief Set a rainbow style sequence
 *
 * Creates a rainbow slice. Internally this function calls dled_pixel_get_color_by_index.
 *
 * @param[in,out] led        Led strip object.
 * @param[in]     step       Index of rainbow seqence.
 *
 * @code{c}
 * pixel_t *pixels;
 * ... // create the pixels
 * uint16_t step = 0;
 * while (true) {
 *     moveRainbowPixel(led, step++);
 *     led.show(); // send the pixels to LEDs
 *     delay_ms(50); // wait a little between sequences
 * }
 * @endcode
 */
void rainbow(LED *led, uint16_t step);

/**
 * @brief Moves a pixel back and forth
 *
 * Moves a pixel back and forth changing its color through red, green and blue.
 * There are (6 * length) steps.
 *
 * @param[in,out] led        Led strip object.
 * @param[in]     step       The step of the moving sequence.
 *
 * @code{c}
 * uint16_t step = 0;
 * while (true) {
 *     moveRainbowPixel(led, step++);
 *     led.show(); // send the pixels to LEDs
 *     delay_ms(50); // wait a little between sequences
 * }
 * @endcode
 */
void moveRainbowPixel(LED *led, uint16_t step);

void movePixel(LED *led, CRGB color, uint16_t step);

/**
 * @brief Fade in into the color
 *
 * Animation step 20ms, i.e. 50 steps/s
 *
 * @param[in,out] led        Led strip object.
 * @param[in]     color      Led strip color.
 * @param[in]     ms         Animation time in ms.
 */
void hsvFadeIn(LED *led, CHSV color, uint32_t ms);
void rgbFadeIn(LED *led, CRGB color, uint32_t ms);

void colorFadeOut(LED *led, uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif