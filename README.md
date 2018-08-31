# ESP32 MQTTT

## Mosquito
> http://www.arduino-tutorial.de/arduino-und-mqtt/

    # Install
    brew install mosquitto
    
```bash
mosquitto has been installed with a default configuration file.
You can make changes to the configuration by editing:
    /usr/local/etc/mosquitto/mosquitto.conf

To have launchd start mosquitto now and restart at login:
  brew services start mosquitto
Or, if you don't want/need a background service you can just run:
  mosquitto -c /usr/local/etc/mosquitto/mosquitto.conf
```    

Mosquite wird nach `/usr/local/Cellar/mosquitto/1.5.1/sbin/mosquitto` installiert

    # Start
    /usr/local/Cellar/mosquitto/1.5.1/sbin/mosquitto -c /usr/local/etc/mosquitto/mosquitto.conf
    
### Testing

    # Turn on led
    mosquitto_pub -t "esp32/output" -m "on"
    
    # Turn off led
    mosquitto_pub -t "esp32/output" -m "off"    
    
## Links

   - [PlatformIO - PubSubClient for ESP32 / Arduino](https://platformio.org/lib/show/89/PubSubClient)
   - [Some samples](https://www.hivemq.com/blog/mqtt-client-library-encyclopedia-arduino-pubsubclient/)
   - [ESP32 MQTT – Publish and Subscribe with Arduino IDE](https://randomnerdtutorials.com/esp32-mqtt-publish-subscribe-arduino-ide/)
       