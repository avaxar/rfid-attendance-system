#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "clcd.hpp"
#include "wifi.hpp"


namespace misc {
    const unsigned long initial_heap_size = ESP.getFreeHeap();

    void beat(bool no_wifi = false) {
        clcd::update();
        if (!no_wifi) {
            wifi::check();
        }

        const unsigned long BEAT_DELAY_MS = 2500;
        static unsigned long last_beat = 0;

        if (last_beat + BEAT_DELAY_MS <= millis()) {
            last_beat = millis();

            Serial.printf(
                "[misc::beat] Still alive. %lums since boot. %lu out of %lu bytes used in heap.\n",
                millis(), initial_heap_size - ESP.getFreeHeap(), initial_heap_size);
        }
    }

    void delay(unsigned long ms, bool no_wifi = false) {
        unsigned long end = millis() + ms;
        while (millis() < end) {
            beat(no_wifi);
            ::delay(25);
        }
    }
}
