#pragma once

#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>

#include "../secrets.h"
#include "student.hpp"


FirebaseConfig fbase_config;
FirebaseAuth fbase_auth;
FirebaseData fbase_data;


void checkWiFi() {
    // No need to do anything if it's already connected
    if (WiFi.status() == WL_CONNECTED) {
        return;
    }

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    // Waits upon connection
    while (WiFi.status() != WL_CONNECTED) {
        if (WiFi.status() == WL_WRONG_PASSWORD) {
            Serial.printf("[checkWiFi] Password for '" WIFI_SSID "' was incorrect.\n");
            delay(30000);
            WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        }
        else {
            Serial.print("[checkWiFi] Awaiting WiFi connection...\n");
            delay(2500);
        }
    }

    Serial.printf("[checkWiFi] Connected to '" WIFI_SSID "' with local IP: %s\n",
                  WiFi.localIP().toString().c_str());
}

void initFirebase() {
    fbase_config.database_url = FIREBASE_URL;
    fbase_config.api_key = FIREBASE_API_KEY;
    fbase_config.timeout.serverResponse = 10000;

    fbase_auth.user.email = FIREBASE_AUTH_EMAIL;
    fbase_auth.user.password = FIREBASE_AUTH_PASSWORD;

    fbase_data.setBSSLBufferSize(2048, 2048);
    fbase_data.setResponseSize(2048);

    Firebase.begin(&fbase_config, &fbase_auth);
    Firebase.reconnectWiFi(true);
}

Student fetchStudent(uint32_t card_uid) {
    Student student = {.card_uid = card_uid,
                       .name = "<Unavailable>",
                       .classroom = "<Unavailable>",
                       .school_id = 0,
                       .class_id = 0};

    // Fetches the personal info of the card holder in "/students/{card_uid}"
    String path = "/students/" + String(student.card_uid, HEX);
    if (!Firebase.RTDB.get(&fbase_data, path)) {
        Serial.printf("[fetchStudent] Unable to fetch '%s'. Error: %s\n", path.c_str(),
                      fbase_data.errorReason().c_str());
        return student;
    }

    FirebaseJson json = fbase_data.to<FirebaseJson>();
    path = fbase_data.dataPath();

    if (json.errorPosition() != -1) {
        Serial.printf("[fetchStudent] Fetched '%s' is not valid JSON.", path.c_str());
        return student;
    }
    else {
        String json_repr;
        json.toString(json_repr, true);
        Serial.printf("[fetchStudent] JSON from '%s' fetched. Dumping JSON content...\n%s\n",
                      path.c_str(), json_repr.c_str());
    }

    // From here on, fetches the necessary JSON members
    FirebaseJsonData json_data;

    if (json.get(json_data, "name")) {
        student.name = json_data.stringValue;
    }
    else {
        Serial.printf("[fetchStudent] Failed to get 'name' from %s\n", path.c_str());
    }

    if (json.get(json_data, "classroom")) {
        student.classroom = json_data.stringValue;
    }
    else {
        Serial.printf("[fetchStudent] Failed to get 'classroom' from %s\n", path.c_str());
    }

    if (json.get(json_data, "school_id")) {
        student.school_id = json_data.intValue;
    }
    else {
        Serial.printf("[fetchStudent] Failed to get 'school_id' from %s\n", path.c_str());
    }

    if (json.get(json_data, "class_id")) {
        student.class_id = json_data.intValue;
    }
    else {
        Serial.printf("[fetchStudent] Failed to get 'class_id' from %s\n", path.c_str());
    }

    return student;
}
