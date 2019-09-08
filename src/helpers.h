#ifndef HELPER_H_
#define HELPER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "freertos/FreeRTOS.h"

void delay_ms(uint32_t ms);

uint32_t interval_ms(TickType_t from, TickType_t to);


#ifdef __cplusplus
}
#endif

#endif