
#include "bouffalo_sdk.h"

extern void (*__preinit_array_start[])(void) __attribute__((weak));
extern void (*__preinit_array_end[])(void) __attribute__((weak));
extern void (*__init_array_start[])(void) __attribute__((weak));
extern void (*__init_array_end[])(void) __attribute__((weak));

void call_constructors() {
    for (void (**p)() = __preinit_array_start; p != __preinit_array_end; ++p) {
        (*p)(); // call preinit constructor
    }

    for (void (**p)() = __init_array_start; p != __init_array_end; ++p) {
        (*p)(); // call init constructor
    }
}

void init(void)
{
    call_constructors();
    board_init();
}

unsigned long millis()
{
  return bflb_mtimer_get_time_ms();
}

unsigned long micros() {
  return bflb_mtimer_get_time_us();
}

void delay(unsigned long ms)
{
#ifndef CONFIG_FREERTOS
    bflb_mtimer_delay_us(ms * 1000);
#else
    vTaskDelay(ms);
#endif
}

void delayMicroseconds(unsigned int us)
{
    bflb_mtimer_delay_us(us);
}

