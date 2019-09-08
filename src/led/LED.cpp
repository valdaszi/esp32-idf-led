#include "Led.hpp"
#include "dled/esp32_rmt_dled.h"
#include "dled/dled_strip.h"
#include "esp_log.h"

static const char *TAG = "LED";

LED::LED(dstrip_type_t strip_type, uint16_t length, uint8_t max_cc_val, gpio_num_t gpio_number)
{
    dled_strip_init(&strip);
    dled_strip_create(&strip, strip_type, length, max_cc_val);

    rmt_dled_init(&rps);

    esp_err_t err;

    err = rmt_dled_create(&rps, &strip);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "[0x%x] rmt_dled_init failed", err);
        while (true)
        {
        }
    }

    err = rmt_dled_config(&rps, gpio_number, RMT_CHANNEL_0);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "[0x%x] rmt_dled_config failed", err);
        while (true)
        {
        }
    }

    err = rmt_dled_send(&rps);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "[0x%x] rmt_dled_send failed", err);
    }
    else
    {
        ESP_LOGI(TAG, "LEDs initialized and turned off");
    }
}

void LED::show()
{
    dled_strip_fill_buffer(&strip);
    rmt_dled_send(&rps);
}

void LED::setPixel(uint16_t idx, CRGB color)
{
    if (idx >= strip.length)
    {
        return;
    }
    strip.pixels[idx] = color;
}

void LED::setColor(CRGB color)
{
    for (uint16_t i = 0; i < strip.length; i++)
    {
        strip.pixels[i] = color;
    }
}