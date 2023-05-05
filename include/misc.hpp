#pragma once

#include <Arduino.h>

#include "clcd.hpp"
#include "wifi.hpp"


namespace misc {
    void beat(bool no_wifi = false) {
        clcd::update();
        if (!no_wifi) {
            wifi::check();
        }

        const unsigned long BEAT_DELAY = 2000;
        static unsigned long last_beat = 0;

        if (last_beat + BEAT_DELAY <= millis()) {
            last_beat = millis();

            Serial.printf("[misc::beat] Still alive. %ums since boot.\n", millis());
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
