//
// Created by Mike Mitterer on 31.08.18.
//

#ifndef ESP32_HARDWARE_H
#define ESP32_HARDWARE_H

#include <Arduino.h>

#ifdef BOARD_LOLIN32PRO
    const gpio_num_t pinInternalLED = GPIO_NUM_5;
#else
    const gpio_num_t pinInternalLED = GPIO_NUM_2;
#endif

const gpio_num_t pinTestLED = GPIO_NUM_32;

// OLED
const uint8_t SDA_PIN = 21;
const uint8_t SCL_PIN = 22;
const uint8_t OLED_ADDRESS = 0x3c;

// Switches
const gpio_num_t pinMainSwitch = GPIO_NUM_26;


#endif //ESP32_HARDWARE_H
