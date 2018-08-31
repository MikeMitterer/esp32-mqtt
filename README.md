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
    
    