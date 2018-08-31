//
// Created by Mike Mitterer on 31.08.18.
//

#include <PubSubClient.h>
#include "callback.h"
#include "hardware.h"

void mqtt_callback(char* topic, uint8_t* message, unsigned int length) {
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.print(". Message: ");
    String messageTemp;

    for (int i = 0; i < length; i++) {
        Serial.print((char) message[i]);
        messageTemp += (char) message[i];
    }
    Serial.println();

    // Feel free to add more if statements to control more GPIOs with MQTT

    // If a message is received on the topic esp32/output, you check if the message is either "on" or "off".
    // Changes the output state according to the message
    if (String(topic) == "esp32/output") {
        Serial.print("Changing output to ");
        if (messageTemp == "on") {
            Serial.println("on");
            digitalWrite(testLED, HIGH);
        } else if (messageTemp == "off") {
            Serial.println("off");
            digitalWrite(testLED, LOW);
        }
    }
}

void mqtt_reconnect(PubSubClient& client) {
    // Loop until we're reconnected
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect("esp32client")) {
            Serial.println("connected");
            // Subscribe
            client.subscribe("esp32/output");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

