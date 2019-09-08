#ifdef __cplusplus
extern "C" {
#endif

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_log.h"

#include "led/Led.hpp"
#include "app_cfg.h"
#include "helpers.h"
#include "led_animations.h"

static const char *TAG = "main";

void app_main(void)
{
    delay_ms(2000);     // laukome kol prisijungs konsole

    nvs_flash_init();

    LED led(DLED_WS2815, LEDS_COUNT, LED_BRIGHTNESS, GPIO);

    uint16_t step;

    TickType_t start = 0;

    for (;;)
    {
        // Red
        ESP_LOGI(TAG, "Red");
        led.setColor(CRGB(LED_BRIGHTNESS, 0, 0));
        led.show();
        delay_ms(3000);

        // Green
        ESP_LOGI(TAG, "Green");
        led.setColor(CRGB(0, LED_BRIGHTNESS, 0));
        led.show();
        delay_ms(3000);

        // Blue
        ESP_LOGI(TAG, "Blue");
        led.setColor(CRGB(0, 0, LED_BRIGHTNESS));
        led.show();
        delay_ms(3000);

        // White
        ESP_LOGI(TAG, "White");
        led.setColor(CRGB(LED_BRIGHTNESS, LED_BRIGHTNESS, LED_BRIGHTNESS));
        led.show();
        delay_ms(3000);

        ESP_LOGI(TAG, "Ping-pong");
        start = xTaskGetTickCount();
        step = 0;
        while (interval_ms(start, xTaskGetTickCount()) < 10000) {
            ani_pixel_move_pixel(led.strip.pixels, led.strip.length, led.strip.max_cc_val, step);
            led.show();
            step++;
            delay_ms(20);
        }

        ESP_LOGI(TAG, "Rainbow");
        start = xTaskGetTickCount();
        step = 0;
        while (interval_ms(start, xTaskGetTickCount()) < 20000) {
            ani_pixel_rainbow_step(led.strip.pixels, led.strip.length, led.strip.max_cc_val, step);
            led.show();
            step++;
            delay_ms(50);
        }
    }

    vTaskDelete(NULL);
}

#ifdef __cplusplus
}
#endif