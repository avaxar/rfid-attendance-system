#include <Arduino.h>

#include "include/clcd.hpp"
#include "include/fbase.hpp"
#include "include/mfrc.hpp"
#include "include/misc.hpp"
#include "include/student.hpp"
#include "include/wifi.hpp"


void setup() {
    // Hardware initializations
    Serial.begin(115200);
    SPI.begin();
    clcd::init();
    mfrc::init();

    // IoT initializations
    clcd::broadcast("Awaiting WiFi", "Connecting...");
    wifi::init();
    clcd::broadcast("Awaiting Firebase", "Connecting...");
    fbase::init();
}

void loop() {
    misc::beat();

    clcd::broadcast("Attendance System", "Tap your student card to mark your attendance.");
    uint32_t rfid = mfrc::read();
    if (rfid == 0) {
        return;
    }

    clcd::broadcast("Please wait", "Fetching info...");
    Student student = fbase::fetchStudent(rfid);

    if (student.name == "<Unavailable>") {
        clcd::broadcast("Card ID not found", "Card ID: " + String(rfid, HEX));
        misc::delay(5000);
        return;
    }
    else {
        clcd::greetStudent(student, "You're late.");
        misc::delay(7500);
    }
}
