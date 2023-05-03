#pragma once

#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>

#include "../secrets.h"
#include "student.hpp"


FirebaseConfig fbase_config;
FirebaseAuth fbase_auth;


void checkWiFi() {
    if (WiFi.status() == WL_CONNECTED) {
        return;
    }

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        if (WiFi.status() == WL_WRONG_PASSWORD) {
            Serial.println("[checkWiFi] Password for '" WIFI_SSID "' was incorrect.");
            delay(30000);
            WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        }
        else {
            Serial.println("[checkWiFi] Awaiting WiFi connection...");
            delay(2500);
        }
    }

    Serial.print("[checkWiFi] Connected to '" WIFI_SSID "' with local IP: ");
    Serial.println(WiFi.localIP());
}

void initFirebase() {
    fbase_config.host = FIREBASE_HOSTNAME;
    fbase_config.api_key = FIREBASE_API_KEY;

    fbase_auth.user.email = FIREBASE_AUTH_EMAIL;
    fbase_auth.user.password = FIREBASE_AUTH_PASSWORD;

    Firebase.begin(&fbase_config, &fbase_auth);
    Firebase.reconnectWiFi(true);
}

Student fetchStudent(uint32_t card_uid) {
    Student student = {
        .card_uid = card_uid, .name = "", .classroom = "", .school_id = 0, .class_id = 0};

    switch (student.card_uid) {
        case 0xCC74EE6F:
            student.name = "Avaxar";
            break;
        case 0x50CD49CF:
            student.name = "Lyn";
            break;
        case 0x638CD1CF:
            student.name = "SpookyOcean";
            break;
        case 0x5B3E024F:
            student.name = "DogeBonk";
            break;
        case 0xBD5691EF:
            student.name = "Yu";
            break;
        default:
            student.name = "Unknown";
            break;
    }

    return student;
}
