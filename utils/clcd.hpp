#pragma once

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "student.hpp"


// Initializes LCD object
LiquidCrystal_I2C clcd(0x27, 20, 4);


void initClcd() {
    // Initializes the character LCD
    clcd.init();
    clcd.backlight();
    clcd.clear();
}

void displayStudent(const Student& student) {
    // Clears the LCD
    clcd.clear();

    // Displays the name
    clcd.setCursor(0, 0);
    clcd.print("Hello, ");
    clcd.print(student.name);
    clcd.print(".");

    // Displays school ID and class information
    clcd.setCursor(0, 1);
    clcd.print(student.school_id);

    String class_n_number = String(student.class_id) + " / " + student.classroom;
    clcd.setCursor(20 - class_n_number.length(), 1);
    clcd.print(class_n_number);

    // Displays card UID
    clcd.setCursor(0, 2);
    clcd.print("Card ID: ");
    clcd.print(String(student.card_uid, HEX));
}
