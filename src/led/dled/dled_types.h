#ifndef DLED_TYPES_H_
#define DLED_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>
#include "../lib_FastLED/pixeltypes.h"

/**
 * @brief Structure to be used as a pixel.
 *
 */
// typedef struct {
// 	uint8_t r; /*!< Red color component */
//     uint8_t g; /*!< Green color component */
//     uint8_t b; /*!< Blue color component */
// } pixel_t;
typedef CRGB pixel_t;

/**
 * @brief The type of digital LEDs.
 *
 */
typedef enum {
    DLED_NULL,    /*!< This is used as NOT set value */
    DLED_WS2812,
    DLED_WS2812B,
    DLED_WS2812D,
    DLED_WS2813,
    DLED_WS2815,
    DLED_WS281x    /*!< This value should work for all WS281* and clones */
} dstrip_type_t;

/**
 * @brief Structure to be used as a LED strip
 *
 */
typedef struct {
	pixel_t* pixels;        /*!< these are the pixels, one for each LED */
	uint16_t length;        /*!< the number of pixels */

	uint8_t* buffer;        /*!< buffer to hold data to be sent to LEDs */
	uint16_t buffer_length; /*!< length, in bytes, of buffer */

	uint8_t max_cc_val;     /*!< maximum value allowed for a color component */

	dstrip_type_t type;          /*!< type of digital LEDs */
	uint8_t bytes_per_led;       /*!< number of bytes per LED */
    uint16_t T0H, T0L, T1H, T1L; /*!< timings of the communication protocol */
    uint32_t TRS;                /*!< reset timing of the communication protocol */
} pixel_strip_t;

#ifdef __cplusplus
}
#endif

#endif