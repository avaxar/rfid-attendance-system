#pragma once

#include <ESP8266WiFi.h>

#include "../secrets.hpp"


namespace misc {
    void beat(bool no_wifi);
    void delay(unsigned long ms, bool no_wifi);
}

namespace wifi {
    void check();
    void init() {
        WiFi.setHostname(DEVICE_NAME);
        check();
    }

    void check() {
        // No need to do anything if it's already connected
        if (WiFi.status() == WL_CONNECTED) {
            return;
        }

        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

        // Waits upon connection
        while (WiFi.status() != WL_CONNECTED) {
            if (WiFi.status() == WL_WRONG_PASSWORD) {
                Serial.printf("[wifi::check] Password for '" WIFI_SSID "' was incorrect.\n");
                misc::delay(30000, true);
                WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
            }
            else {
                Serial.print("[wifi::check] Awaiting WiFi connection...\n");
                misc::delay(2500, true);
            }
        }

        Serial.printf("[wifi::check] Connected to '" WIFI_SSID "' with local IP: %s\n",
                      WiFi.localIP().toString().c_str());
    }
}