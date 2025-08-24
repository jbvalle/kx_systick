#ifndef SYSTICK_H
#define SYSTICK_H
#include "cfg_systick.h"

void systick_init(const SysTick_ConfigType * config);

/* Register callback for a specific SysTick channel */
void SysTick_SetCallback(uint8_t channel, SysTick_CallbackType callback);

#endif
