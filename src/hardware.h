//
// Created by Mike Mitterer on 31.08.18.
//

#ifndef ESP32_HARDWARE_H
#define ESP32_HARDWARE_H

#include <Arduino.h>

#ifdef BOARD_LOLIN32PRO
    const gpio_num_t internalLED = GPIO_NUM_5;
#else
    const gpio_num_t internalLED = GPIO_NUM_2;
#endif

const gpio_num_t testLED = GPIO_NUM_13;

#endif //ESP32_HARDWARE_H
