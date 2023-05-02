#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <MFRC522.h>

#include "utils/clcd.hpp"
#include "utils/diagnostics.hpp"
#include "utils/firebase.hpp"
#include "utils/rfid.hpp"
#include "utils/student.hpp"


void setup() {
    Serial.begin(115200);
    SPI.begin();

    initClcd();
    initMfrc();
}

void loop() {
    heartBeat();

    uint32_t rfid = readRfid();
    if (rfid == 0) {
        return;
    }

    Student student = fetchStudent(rfid);
    displayStudent(student);
}
