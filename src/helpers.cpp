#include "helpers.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void delay_ms(uint32_t ms)
{
    if (ms == 0) return;
    vTaskDelay(ms / portTICK_PERIOD_MS);
}

uint32_t interval_ms(TickType_t from, TickType_t to) 
{
    return (to - from) * portTICK_PERIOD_MS;
}