//
// Created by Mike Mitterer on 10.03.17.
//
// cmake-Template für config.h
//

#ifndef XCTEST_CONFIG_H_IN_H
#define XCTEST_CONFIG_H_IN_H

#include <string>

// the configured options and settings for HelloWorld
const std::string MQTT_VERSION_MAJOR = "0";
const std::string MQTT_VERSION_MINOR = "1";

// Password compiled into source
// Set in .config/passwords.cmake (or via ENV-VAR)
const char* MQTT_SSID = "<Your SSID>";
const char* MQTT_PASSWORD = "<your password>";

#endif //XCTEST_CONFIG_H_IN_H
