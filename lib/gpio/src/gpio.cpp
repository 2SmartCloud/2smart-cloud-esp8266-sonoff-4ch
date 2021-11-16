#include "gpio.h"

#include <Ticker.h>

Ticker erase_flash_timer;

void onTimer() {
    if (!digitalRead(ERASE_FLASH)) {
        erase_flag = true;
    } else {
        erase_flash_timer.detach();
    }
}

void IRAM_ATTR eraseInterrupt() { erase_flash_timer.attach(10, onTimer); }

void setGpios() {
    pinMode(ERASE_FLASH, INPUT_PULLUP);
    attachInterrupt(ERASE_FLASH, eraseInterrupt, FALLING);
}
