#include <stdint.h>
#include "systick.h"
#include "cortex_m4.h"

void systick_init(const SysTick_ConfigType * config){
    // Configure Interrupt Settings for Systick
    SYSTICK->STK_CTRL &= ~(1 << STK_CTRL_BIT_POS_TICKINT);
    SYSTICK->STK_CTRL |=  (config->int_en << STK_CTRL_BIT_POS_TICKINT);
    // Configure Clock Source for Systick
    SYSTICK->STK_CTRL &= ~(1 << STK_CTRL_BIT_POS_CLKSRC);
    SYSTICK->STK_CTRL |=  (config->clk_src << STK_CTRL_BIT_POS_CLKSRC);
    // Set Reload Value
    uint32_t systick_reload_val = (AHB_FRQ_Hz / config->freq_Hz) - 1;
    SYSTICK->STK_LOAD = systick_reload_val - 1;
    // Reset Counter Current Register
    SYSTICK->STK_VAL = 0;
    // Start Timer
    SYSTICK->STK_CTRL |= 1;
}
