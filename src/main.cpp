/**
 * Hello-World ESP32.
 * Blinkt eine LED und ermöglicht ein OAT update
 *
 * Wenn das OAT funktioniere soll muss im platformio.ini der Upload-Port gesetzt sein!
 *
 * Mehr:
 *      https://diyprojects.io/arduinoota-esp32-wi-fi-ota-wireless-update-arduino-ide/
 *
 * OTA mit platformio:
 *      http://docs.platformio.org/en/latest/platforms/espressif8266.html#over-the-air-ota-update
 *
 * Debug:
 * > https://www.esp32.com/viewtopic.php?t=263
 * > http://esp-idf.readthedocs.io/en/latest/get-started/idf-monitor.html#launch-gdb-for-gdbstub
 * 
 *      /Users/mikemitterer/.platformio/packages/toolchain-xtensa32/bin/xtensa-esp32-elf-gdb ./.pioenvs/nodemcu-32s/firmware.elf -b 115200 -ex 'target remote /dev/cu.SLAB_USBtoUART'
 *      /Users/mikemitterer/.platformio/packages/toolchain-xtensa32/bin/xtensa-esp32-elf-gdb ./.pioenvs/nodemcu-32s/firmware.elf
 *      /Users/mikemitterer/.platformio/packages/toolchain-xtensa32/bin/xtensa-esp32-elf-addr2line -pfiaC -e ./.pioenvs/nodemcu-32s/firmware.elf
 */
#include "stdafx.h"
#include "config.h"
#include "hardware.h"
#include "ota/ota.h"
#include "socket/SocketHandler.h"
#include "mqtt/callback.h"

#include <functional>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include "SSD1306.h"
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <OneButton.h>

using namespace std::placeholders;

const std::string ssid{ PROJECT_SSID };            // NOLINT(cert-err58-cpp)
const std::string password{ PROJECT_PASSWORD };    // NOLINT(cert-err58-cpp)

static const uint8_t MAX_RETRIES = 80;

SSD1306 display(OLED_ADDRESS, SDA_PIN, SCL_PIN);                         // NOLINT(cert-err58-cpp)

const char* mqtt_server = "192.168.0.42";

WiFiClient wiFiClient;                                                     // NOLINT(cert-err58-cpp)
PubSubClient mqttClient(wiFiClient);                                       // NOLINT(cert-err58-cpp)

// Buttons
OneButton mainSwitch(pinMainSwitch, false);                                // NOLINT(cert-err58-cpp)

void setup() {
    Serial.begin(115200);
    Log.begin(LOG_LEVEL_NOTICE, &Serial);

    // OLED setup
    display.init();
    display.setFont(ArialMT_Plain_10);
    display.clear();

    // initialize digital pin LED_BUILTIN as an output.
    pinMode(pinInternalLED, OUTPUT);

    pinMode(pinTestLED, OUTPUT);

    pinMode(pinMainSwitch, INPUT_PULLDOWN);

    WiFi.begin(ssid.c_str(), password.c_str());
    Serial.print("\nBooting ");

    display.drawString(0, 0, "Booting...");
    display.display();

    int retry = 0;
    WiFiClass::mode(WIFI_STA);
    while (WiFiClass::status() != WL_CONNECTED && retry < MAX_RETRIES) {
        digitalWrite(pinInternalLED, HIGH);
        delay(100);
        digitalWrite(pinInternalLED, LOW);
        Serial.print(".");
        retry++;
    }

    Serial.println("");
    if (retry >= MAX_RETRIES) {
        Serial.println("Connection Failed! Rebooting...");

        display.clear();
        display.drawString(0, 0, "Connection Failed!");
        display.drawString(0, 11, "Rebooting...");
        display.display();

        delay(5000);
        ESP.restart();
    }

    digitalWrite(pinInternalLED, HIGH);
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    display.clear();
    delay(10);
    display.drawString(0, 0,  String("App: ") +
                              String(PROJECT_NAME.c_str()) + " / " +
                              String(PROJECT_VERSION.c_str()));
    display.drawString(0, 11, String("IP:  ") + WiFi.localIP().toString());
    display.drawString(0, 22, String("MAC: ") + WiFi.macAddress());
    display.display();

    mqttClient.setServer(mqtt_server, 1883);
    mqttClient.setCallback(mqtt_callback);

    // Buttons
    mainSwitch.setPressTicks(50);
    mainSwitch.attachDuringLongPress([]() {
        Serial.println("Button pressed");
        mqttClient.publish("esp32/push","on");
    });

    mainSwitch.attachLongPressStop([](){
        Serial.println("Button released");
        mqttClient.publish("esp32/push","off");
    });

    initOTA();
    ArduinoOTA.begin();

    Serial.println("Ready!");
}

void loop() {
    ArduinoOTA.handle();

    if (!mqttClient.connected()) {
        mqtt_reconnect(mqttClient);
    }
    mqttClient.loop();
    mainSwitch.tick();

    // Wird z.B. von digitalWrite benötigt - sonst geht die LED nicht an???
    delay(1);
}