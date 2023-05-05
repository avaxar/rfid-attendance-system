#pragma once

#include <Arduino.h>
#include <MFRC522.h>
#include <SPI.h>

#include "misc.hpp"


namespace mfrc {
    MFRC522 mfrc(D3, D4);

    void init() {
        mfrc.PCD_Init();
        mfrc.PCD_DumpVersionToSerial();

        misc::beat();
    }

    uint32_t read() {
        *(uint32_t*)mfrc.uid.uidByte = 0;

        // Checks whether a card is present near the sensor
        if (!mfrc.PICC_IsNewCardPresent()) {
            return 0;
        }
        misc::beat();

        // Attempts to read the card
        if (!mfrc.PICC_ReadCardSerial()) {
            Serial.printf("[mfrc::read] A card is present. Not able to read.\n");
            return 0;
        }
        misc::beat();

        // Dumps debug info about the card
        Serial.printf("[mfrc::read] A card has been read. Dumping card info to serial...\n");
        mfrc.PICC_DumpToSerial(&mfrc.uid);
        misc::beat();

        return *(uint32_t*)mfrc.uid.uidByte;
    }
}
