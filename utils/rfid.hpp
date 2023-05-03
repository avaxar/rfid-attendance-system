#pragma once

#include <Arduino.h>
#include <MFRC522.h>
#include <SPI.h>


MFRC522 mfrc(D3, D4);


void initMfrc() {
    mfrc.PCD_Init();
    mfrc.PCD_DumpVersionToSerial();
}

uint32_t readRfid() {
    *(uint32_t*)mfrc.uid.uidByte = 0;

    // Checks whether a card is present near the sensor
    if (!mfrc.PICC_IsNewCardPresent()) {
        return 0;
    }

    // Attempts to read the card
    if (!mfrc.PICC_ReadCardSerial()) {
        Serial.println("[readRfid] A card is present. Not able to read.");
        return 0;
    }

    // Dumps debug info about the card
    Serial.println("[readRfid] A card has been read. Dumping card to serial...");
    mfrc.PICC_DumpToSerial(&mfrc.uid);

    return *(uint32_t*)mfrc.uid.uidByte;
}
