#pragma once

#include <Firebase_ESP_Client.h>

#include "../secrets.hpp"
#include "misc.hpp"
#include "student.hpp"


namespace fbase {
    FirebaseConfig config;
    FirebaseAuth auth;
    FirebaseData fdata;

    void init() {
        config.database_url = FIREBASE_URL;
        config.api_key = FIREBASE_API_KEY;
        config.timeout.serverResponse = 10000;

        auth.user.email = FIREBASE_AUTH_EMAIL;
        auth.user.password = FIREBASE_AUTH_PASSWORD;

        fdata.setBSSLBufferSize(2048, 2048);
        fdata.setResponseSize(2048);

        Firebase.begin(&config, &auth);
        Firebase.reconnectWiFi(true);

        misc::beat();
    }

    Student fetchStudent(uint32_t card_uid) {
        Student student = {.card_uid = card_uid,
                           .name = "<Unavailable>",
                           .classroom = "<Unavailable>",
                           .school_id = 0,
                           .class_id = 0};

        // Fetches the personal info of the card holder in "/students/{card_uid}"
        String path = "/students/" + String(student.card_uid, HEX);
        if (!Firebase.RTDB.get(&fdata, path)) {
            Serial.printf("[fbase::fetchStudent] Unable to fetch '%s'. Error: %s\n", path.c_str(),
                          fdata.errorReason().c_str());
            return student;
        }
        misc::beat();

        FirebaseJson json = fdata.to<FirebaseJson>();
        path = fdata.dataPath();
        misc::beat();

        if (json.errorPosition() != -1) {
            Serial.printf("[fbase::fetchStudent] Fetched '%s' is not valid JSON.", path.c_str());
            return student;
        }
        else {
            String json_repr;
            json.toString(json_repr, true);
            Serial.printf("[fbase::fetchStudent] JSON from '%s' fetched. Dumping JSON content...\n%s\n",
                          path.c_str(), json_repr.c_str());
        }

        // From here on, fetches the necessary JSON members
        FirebaseJsonData json_data;

        if (json.get(json_data, "name")) {
            student.name = json_data.stringValue;
        }
        else {
            Serial.printf("[fbase::fetchStudent] Failed to get 'name' from %s\n", path.c_str());
        }

        if (json.get(json_data, "classroom")) {
            student.classroom = json_data.stringValue;
        }
        else {
            Serial.printf("[fbase::fetchStudent] Failed to get 'classroom' from %s\n", path.c_str());
        }

        if (json.get(json_data, "school_id")) {
            student.school_id = json_data.intValue;
        }
        else {
            Serial.printf("[fbase::fetchStudent] Failed to get 'school_id' from %s\n", path.c_str());
        }

        if (json.get(json_data, "class_id")) {
            student.class_id = json_data.intValue;
        }
        else {
            Serial.printf("[fbase::fetchStudent] Failed to get 'class_id' from %s\n", path.c_str());
        }

        misc::beat();
        return student;
    }
}
