# RfidAttendanceSystem

 An attendance registering device per RFID card with the ESP8266 IoT microcontroller. In order to set this project up to your own use, create `secrets.h` in the root of the repository with defining these following macros:

```c
#pragma once

#define WIFI_SSID "<Your WiFi's SSID>"
#define WIFI_PASSWORD "<Your WiFi's password>"

#define FIREBASE_URL "<URL to your Firebase>"
#define FIREBASE_API_KEY "<API key to your Firebase>"

#define FIREBASE_AUTH_EMAIL "<Firebase authentication email>"
#define FIREBASE_AUTH_PASSWORD "<Firebase authentication password>"
```

 A school IT extracurricular project by:

- [Avaxar](https://github.com/avaxar)
- [DogeBonk](https://github.com/dozhbonk)

## Dependencies

 In order to compile the project in the Arduino IDE, you have to install these following libraries:

- [MFRC522](https://github.com/miguelbalboa/rfid)
- [LiquidCrystal I2C](https://github.com/johnrickman/LiquidCrystal_I2C)
- [Firebase Arduino Client Library for ESP8266 and ESP32](https://github.com/mobizt/Firebase-ESP-Client)
