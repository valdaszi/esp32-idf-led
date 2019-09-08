#ifdef __cplusplus
extern "C" {
#endif

#include "led_animations.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "led_anima";

/*
 * Maximum number of colors is: 6 * strand->brightLimit;
 * r max. g /   b 0
 * r \    g max
 * r 0    g max b /
 * r 0    g \   b max
 * r /    g 0   b max
 * r max  g 0   b \
 */
CRGB ani_pixel_get_color_by_index(uint8_t max_cc_val, uint16_t index)
{
    CRGB pixel(0, 0, 0);
    uint8_t seq;
    uint8_t idx;
    uint8_t maxVal;

    if (max_cc_val == 0) {
        return pixel;
    }
    maxVal = max_cc_val;

    seq = (index / maxVal) % 6;
    idx =  index % maxVal;

    switch (seq) {
    case 0: pixel = CRGB(maxVal,       idx,          0           ); break;
    case 1: pixel = CRGB(maxVal - idx, maxVal,       0           ); break;
    case 2: pixel = CRGB(0,            maxVal,       idx         ); break;
    case 3: pixel = CRGB(0,            maxVal - idx, maxVal      ); break;
    case 4: pixel = CRGB(idx,          0,            maxVal      ); break;
    case 5: pixel = CRGB(maxVal,       0,            maxVal - idx); break;
    }

    return pixel;
}

void rainbow(LED *led, uint16_t step)
{
    if (led == NULL) return;

    for (uint16_t idx = 0; idx < led->strip.length; idx++) {
        led->strip.pixels[idx] = ani_pixel_get_color_by_index(led->strip.max_cc_val, idx + step);
    }
}

void moveRainbowPixel(LED *led, uint16_t step)
{
    CRGB pixel;
    uint8_t seq;
    uint16_t idx;
    uint8_t maxVal;
    uint16_t length;

    if (led == NULL) return;

    length = led->strip.length;
    maxVal = led->strip.max_cc_val;

    seq = (step / length) % 6;
    idx =  step % length;

    switch (seq) {
    case 0: pixel = CRGB(maxVal, 0, 0); break;
    case 1: pixel = CRGB(0, maxVal, 0); idx = length - idx - 1; break;
    case 2: pixel = CRGB(0, 0, maxVal); break;
    case 3: pixel = CRGB(maxVal / 2, maxVal / 2, 0); idx = length - idx - 1; break;
    case 4: pixel = CRGB(0, maxVal / 2, maxVal / 2); break;
    case 5: pixel = CRGB(maxVal / 2, 0, maxVal / 2); idx = length - idx - 1; break;
    }

    for (uint16_t i = 0; i < length; i++) {
        if (i == idx) {
            led->strip.pixels[i] = pixel;
        } 
        else {
            led->strip.pixels[i].r /= 2;
            led->strip.pixels[i].g /= 2;
            led->strip.pixels[i].b /= 2;
        }
    }
}

void movePixel(LED *led, CRGB color, uint16_t step)
{
    if (led == NULL) return;

    uint16_t length = led->strip.length;
    uint16_t idx = step % length;

    if (step / length % 2 == 1) {
        idx = length - idx - 1;
    }

    for (uint16_t i = 0; i < length; i++) {
        if (i == idx) {
            led->strip.pixels[i] = color;
        } 
        else {
            led->strip.pixels[i].r /= 2;
            led->strip.pixels[i].g /= 2;
            led->strip.pixels[i].b /= 2;
        }
    }
}

void rgbFadeIn(LED *led, CRGB color, uint32_t ms)
{
    CHSV hsv = rgb2hsv_approximate(color);
    hsvFadeIn(led, hsv, ms);
}

void hsvFadeIn(LED *led, CHSV color, uint32_t ms)
{
    if (led == NULL) return;

    CHSV hsv = color;
    uint8_t value = hsv.value;

    // total frames per animation:
    uint16_t frames = ms * ANIMATION_FPS / 1000;

    if (frames == 0) {
        led->setStripColor(CRGB(color));
        led->show();
        return;
    }

    // ticks in 1 frame:
    TickType_t ticksPerFrame = 1000 / portTICK_PERIOD_MS / ANIMATION_FPS;

    CRGB rgb;
    for (uint16_t i = 0; i < frames; i++) {
        hsv.value = i * value / frames;
        led->setStripColor(CRGB(hsv));
        led->show();
        vTaskDelay(ticksPerFrame);
    }
}

void colorFadeOut(LED *led, uint32_t ms)
{
    uint16_t length = led->strip.length;

    if (ms == 0) {
        led->clear();
        led->show();
        return;
    }

    ESP_LOGD(TAG, "colorFadeOut - ms = %u", ms);
    ESP_LOGD(TAG, "colorFadeOut - total ticks = %u", ms / portTICK_PERIOD_MS);

    uint8_t maxVal = 0;
    for (uint16_t idx = 0; idx < length; idx++) {
        maxVal = maxVal < led->strip.pixels[idx].r ? led->strip.pixels[idx].r : maxVal;
        maxVal = maxVal < led->strip.pixels[idx].g ? led->strip.pixels[idx].g : maxVal;
        maxVal = maxVal < led->strip.pixels[idx].b ? led->strip.pixels[idx].b : maxVal;
    }
    if (maxVal == 0) {
        ESP_LOGD(TAG, "colorFadeOut - no maxVal");
        return;
    }
    ESP_LOGD(TAG, "colorFadeOut - maxVal = %u", maxVal);

    // total frames per animation:
    uint16_t frames = ms * ANIMATION_FPS / 1000;

    if (frames > maxVal) frames = maxVal;
    ESP_LOGD(TAG, "colorFadeOut - frames = %u", frames);

    // ticks in 1 frame:
    TickType_t ticksPerFrame = ms / portTICK_PERIOD_MS / frames;
    ESP_LOGD(TAG, "colorFadeOut - ticksPerFrame = %u", ticksPerFrame);

    // uint8_t delta = maxVal / frames + 1;
    // ESP_LOGI(TAG, "colorFadeOut - delta = %u", delta);

    // 256 -> / 256 = 1.0  -> 100%
    // 192 -> / 256 = 0.75 ->  75%
    // 128 -> / 256 = 0.5  ->  50%

    uint8_t scale = 256 / frames + 1;
    ESP_LOGD(TAG, "colorFadeOut - scale = %u", scale);

    uint16_t rest = frames;
    ESP_LOGD(TAG, "colorFadeOut - rgb = %u,%u,%u", led->strip.pixels[0].r, led->strip.pixels[0].g, led->strip.pixels[0].b);
    for (uint16_t i = 0; i < frames; i++) {
        maxVal = 0;
        for (uint16_t idx = 0; idx < length; idx++) {
            led->strip.pixels[idx].fadeToBlackBy(scale);
            maxVal = maxVal < led->strip.pixels[idx].r ? led->strip.pixels[idx].r : maxVal;
            maxVal = maxVal < led->strip.pixels[idx].g ? led->strip.pixels[idx].g : maxVal;
            maxVal = maxVal < led->strip.pixels[idx].b ? led->strip.pixels[idx].b : maxVal;
        }
        led->show();
        vTaskDelay(ticksPerFrame);
        ESP_LOGD(TAG, "colorFadeOut - rgb = %u,%u,%u", led->strip.pixels[0].r, led->strip.pixels[0].g, led->strip.pixels[0].b);

        if (maxVal != 0) {
            if (--rest > maxVal) rest = maxVal;
            scale = 256 / rest + 1;
        }
    }

    led->clear();
    led->show();
}

#ifdef __cplusplus
}
#endif