#pragma once

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "student.hpp"


LiquidCrystal_I2C clcd(0x27, 20, 4);


void initClcd() {
    clcd.init();
    clcd.backlight();
    clcd.clear();
}

void displayStudent(const Student& student) {
    clcd.clear();

    // Displays the name
    clcd.setCursor(0, 0);
    clcd.printf("Hello, %s.", student.name.c_str());

    // Displays school ID and class information
    clcd.setCursor(0, 1);
    clcd.print(student.school_id);

    String class_n_number = String(student.class_id) + " / " + student.classroom;
    clcd.setCursor(20 - class_n_number.length(), 1);
    clcd.print(class_n_number);

    // Displays card UID
    clcd.setCursor(0, 2);
    clcd.printf("Card ID: %s", String(student.card_uid, HEX).c_str());
}
