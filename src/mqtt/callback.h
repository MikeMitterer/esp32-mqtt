//
// Created by Mike Mitterer on 31.08.18.
//

#ifndef ESP32_CALLBACK_H
#define ESP32_CALLBACK_H

#include <Arduino.h>
#include <PubSubClient.h>

void mqtt_callback(char* topic, uint8_t* message, unsigned int length);

void mqtt_reconnect(PubSubClient& client);

#endif //ESP32_CALLBACK_H
