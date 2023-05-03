#include <Arduino.h>

#include "utils/clcd.hpp"
#include "utils/diagnostics.hpp"
#include "utils/firebase.hpp"
#include "utils/rfid.hpp"
#include "utils/student.hpp"


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
