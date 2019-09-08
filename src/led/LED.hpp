#ifndef LED_H_
#define LED_H_

#include "dled/dled_types.h"
#include "driver/gpio.h"
#include "dled/esp32_rmt_dled.h"

class LED
{
    public:
    pixel_strip_t strip;
    rmt_pixel_strip_t rps;

    LED(dstrip_type_t strip_type, uint16_t length, uint8_t max_cc_val, gpio_num_t gpio_number);
    void show();
    void setPixel(uint16_t index, CRGB color);
    void setColor(CRGB color);
};

#endif