#pragma once
#include <Arduino.h>

const uint8_t ERASE_FLASH = 0;
const uint8_t RELOAD_TIME = 10;  // sec
extern bool erase_flag;

void setGpios();
void IRAM_ATTR onTimer();
void IRAM_ATTR buttonInterrupt();
void IRAM_ATTR eraseInterrupt();
