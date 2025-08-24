#include <stdint.h>
#include "systick.h"
#include "cortex_m4.h"
#include "mcu.h"
#include "gpio.h"

static SysTick_CallbackType SysTick_Callbacks[SYSTICK_CHANNEL_COUNT] = {0};

void systick_init(const SysTick_ConfigType * config){
    // Set Reload Value
    uint32_t systick_reload_val = (MCU_SYSTEM_CLK / config->freq_Hz) - 1;
    SYSTICK->STK_LOAD = systick_reload_val - 1;
    // Reset Counter Current Register
    SYSTICK->STK_VAL = 0;

    // Configure Interrupt Settings for Systick
    SYSTICK->STK_CTRL &= ~(1 << STK_CTRL_BIT_POS_TICKINT);
    SYSTICK->STK_CTRL |=  (config->int_en << STK_CTRL_BIT_POS_TICKINT);
    if(config->int_en){
        global_disable_IRQ();

    }
    // Configure Clock Source for Systick
    SYSTICK->STK_CTRL &= ~(1 << STK_CTRL_BIT_POS_CLKSRC);
    SYSTICK->STK_CTRL |=  (config->clk_src << STK_CTRL_BIT_POS_CLKSRC);
    // Start Timer
    SYSTICK->STK_CTRL |= 1;
    if(config->int_en){
        global_enable_IRQ();
    }
}

void _wait_ms(int time){
    for(int i = 0; i < time; i++){
        for(int j = 0; j < 1600; j++);
    }
}


/* Example notification function (application logic here) */
void SysTick_Callback_Channel0(void){

    // Example: toggle LED, increment tick counter, etc.
    gpio_toggle(GPIO_PORT_D, 12);

}

void SysTick_Callback_Channel1(void){

    // Example: toggle LED, increment tick counter, etc.
    gpio_toggle(GPIO_PORT_D, 13);

}

void SysTick_Callback_Channel2(void){

    // Example: toggle LED, increment tick counter, etc.
    gpio_toggle(GPIO_PORT_D, 14);

}

void SysTick_Callback_Channel3(void){

    // Example: toggle LED, increment tick counter, etc.
    gpio_toggle(GPIO_PORT_D, 15);

}

void SysTick_SetCallback(uint8_t channel, SysTick_CallbackType callback){

    if(channel < SYSTICK_CHANNEL_COUNT){
        SysTick_Callbacks[channel] = callback;
    }
}

void Systick_handler(void){
    for(uint8_t i = 0; i < SYSTICK_CHANNEL_COUNT; i++){
        if(SysTick_Callbacks[i] != 0){
            SysTick_Callbacks[i]();
        }
    }
}

