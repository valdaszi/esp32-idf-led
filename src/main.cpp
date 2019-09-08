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

extern "C" void app_main(void)
{
    delay_ms(2000);     // laukome kol prisijungs konsole

    nvs_flash_init();

    LED led(DLED_WS2815, LEDS_COUNT, GPIO);

    uint16_t step;

    TickType_t start = 0;

    for (;;)
    {
        // ESP_LOGI(TAG, "Red");
        // led.setStripColor(CRGB(LED_BRIGHTNESS, 0, 0));
        // led.show();
        // delay_ms(3000);

        // ESP_LOGI(TAG, "Green");
        // led.setStripColor(CRGB(0, LED_BRIGHTNESS, 0));
        // led.show();
        // delay_ms(3000);

        // ESP_LOGI(TAG, "Blue");
        // led.setStripColor(CRGB(0, 0, LED_BRIGHTNESS));
        // led.show();
        // delay_ms(3000);

        // ESP_LOGI(TAG, "Yellow");
        // led.setStripColor(CRGB(LED_BRIGHTNESS, LED_BRIGHTNESS, 0));
        // led.show();
        // delay_ms(3000);

        ESP_LOGI(TAG, "Cyan");
        led.setStripColor(CRGB(0, LED_BRIGHTNESS, LED_BRIGHTNESS));
        led.show();
        delay_ms(3000);
 
        // ESP_LOGI(TAG, "Magenta");
        // led.setStripColor(CRGB(LED_BRIGHTNESS, 0, LED_BRIGHTNESS));
        // led.show();
        // delay_ms(3000);
 
        // ESP_LOGI(TAG, "White");
        // led.setStripColor(CRGB(LED_BRIGHTNESS, LED_BRIGHTNESS, LED_BRIGHTNESS));
        // led.show();
        // delay_ms(3000);

 
        // Fade in / out

        // ESP_LOGI(TAG, "Fade-in Hue Yellow, 1s");
        // hsvFadeIn(&led, CHSV(HUE_YELLOW, 255, 255), 1000);
        // ESP_LOGI(TAG, "Fade-out, 3s");
        // colorFadeOut(&led, 5000);

        // ESP_LOGI(TAG, "Fade-in RGB Yellow, 3s");
        // rgbFadeIn(&led, CRGB::Yellow, 1000);
        // ESP_LOGI(TAG, "Fade-out, 1s");
        // colorFadeOut(&led, 1000);

        // ESP_LOGI(TAG, "Fade-in RGB Magenta, 2s");
        // rgbFadeIn(&led, CRGB::Magenta, 2000);
        // ESP_LOGI(TAG, "Fade-out, 2s");
        // colorFadeOut(&led, 1000);

        ESP_LOGI(TAG, "Fade-in Hue Cyan/Aqua, 2s");
        hsvFadeIn(&led, CHSV(HUE_AQUA, 255, 255), 2000);
        ESP_LOGI(TAG, "Fade-out Hue, 1s");
        colorFadeOut(&led, 1000);

        ESP_LOGI(TAG, "Fade-in RGB Cyan, 2s");
        rgbFadeIn(&led, CRGB(0, 167, 167), 2000);
        ESP_LOGI(TAG, "Fade-out RGB, 3s");
        colorFadeOut(&led, 3000);

        // // move pixel

        // ESP_LOGI(TAG, "Move Red pixel");
        // start = xTaskGetTickCount();
        // step = 0;
        // while (interval_ms(start, xTaskGetTickCount()) < 10000) {
        //     movePixel(&led, CRGB::Red, step);
        //     led.show();
        //     step++;
        //     delay_ms(50);
        // }

        // ESP_LOGI(TAG, "Move Green pixel");
        // start = xTaskGetTickCount();
        // step = 0;
        // while (interval_ms(start, xTaskGetTickCount()) < 10000) {
        //     movePixel(&led, CRGB::Green, step);
        //     led.show();
        //     step++;
        //     delay_ms(50);
        // }

        // ESP_LOGI(TAG, "Move Blue pixel");
        // start = xTaskGetTickCount();
        // step = 0;
        // while (interval_ms(start, xTaskGetTickCount()) < 10000) {
        //     movePixel(&led, CRGB::Blue, step);
        //     led.show();
        //     step++;
        //     delay_ms(50);
        // }

        // ESP_LOGI(TAG, "Move Rainbow pixel");
        // start = xTaskGetTickCount();
        // step = 0;
        // while (interval_ms(start, xTaskGetTickCount()) < 10000) {
        //     moveRainbowPixel(&led, step);
        //     led.show();
        //     step++;
        //     delay_ms(50);
        // }
        
        // ESP_LOGI(TAG, "Rainbow");
        // start = xTaskGetTickCount();
        // step = 0;
        // while (interval_ms(start, xTaskGetTickCount()) < 20000) {
        //     rainbow(&led, step);
        //     led.show();
        //     step++;
        //     delay_ms(50);
        // }
    }

    vTaskDelete(NULL);
}