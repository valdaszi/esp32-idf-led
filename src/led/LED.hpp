#ifndef LED_H_
#define LED_H_

#include "lib_FastLED/pixeltypes.h"
#include "lib_FastLED/hsv2rgb.h"
#include "dled/dled_types.h"
#include "driver/gpio.h"
#include "dled/esp32_rmt_dled.h"

class LED
{
public:
    pixel_strip_t strip;
    rmt_pixel_strip_t rps;

    LED(dstrip_type_t strip_type, uint16_t length, gpio_num_t gpio_number, uint8_t max_cc_val, rmt_channel_t rmt_channel);
    LED(dstrip_type_t strip_type, uint16_t length, gpio_num_t gpio_number, uint8_t max_cc_val);
    LED(dstrip_type_t strip_type, uint16_t length, gpio_num_t gpio_number);
    
    void show();
    void clear();
    void setStripColor(CRGB color);
};

#endif