# RFID Attendance System

 An attendance registering device per RFID card with the ESP8266 IoT microcontroller.

 A school IT extracurricular project by:

- [Avaxar](https://github.com/avaxar)
- [DogeBonk](https://github.com/dozhbonk)

## Dependencies

 In order to compile the project in the Arduino IDE, you have to install these following libraries:

- [MFRC522](https://github.com/miguelbalboa/rfid)
- [LiquidCrystal I2C](https://github.com/johnrickman/LiquidCrystal_I2C)
- [Firebase Arduino Client Library for ESP8266 and ESP32](https://github.com/mobizt/Firebase-ESP-Client)

## Configuration

 In order to set this project up to your own use, create `secrets.hpp` in the root of the repository with defining these following macros:

```c
#pragma once

#define DEVICE_NAME "<Device name for hostname and Firebase records>"

#define WIFI_SSID "<Your WiFi's SSID>"
#define WIFI_PASSWORD "<Your WiFi's password>"

#define FIREBASE_URL "<URL to your Firebase>"
#define FIREBASE_API_KEY "<API key to your Firebase>"

#define FIREBASE_AUTH_EMAIL "<Firebase authentication email>"
#define FIREBASE_AUTH_PASSWORD "<Firebase authentication password>"
```

## Schematic

 This project requires a NodeMCU ESP8266 microcontroller, 20x4 character LCD screen with an I2C interface, and an MFRC522 RFID reader.

 ![Schematic](/schematic.png)

 (_Please don't mind the hand-drawn schematic on paper_)

## Firebase Layout

 The codebase fetches cardholder/student information by the JSON layout shown below. Adjust your Firebase database accordingly.

```json
{
    "students": {
        "{Card UID 4-byte hex for each student}": {
            "class_id": INTEGER,
            "classroom": STRING,
            "name": STRING,
            "school_id": INTEGER
        }
    }
}
```
