#pragma once

#include <Arduino.h>


void heartBeat() {
    const unsigned long BEAT_DELAY = 1000;
    static unsigned long last_beat = 0;

    if (last_beat + BEAT_DELAY <= millis()) {
        last_beat = millis();

        Serial.printf("[heartBeat] Still alive. %ums since boot.\n", millis());
    }
}
