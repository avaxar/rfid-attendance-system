#include <Arduino.h>

#include "include/clcd.hpp"
#include "include/diagnostics.hpp"
#include "include/firebase.hpp"
#include "include/rfid.hpp"
#include "include/student.hpp"


void setup() {
    // Hardware initializations
    Serial.begin(115200);
    SPI.begin();
    initClcd();
    initMfrc();

    // IoT initializations
    checkWiFi();
    initFirebase();
}

void loop() {
    heartBeat();
    checkWiFi();

    uint32_t rfid = readRfid();
    if (rfid == 0) {
        return;
    }

    Student student = fetchStudent(rfid);
    displayStudent(student);
}
