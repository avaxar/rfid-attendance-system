#pragma once

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "student.hpp"


namespace misc {
    void beat(bool no_wifi);
    void delay(unsigned long ms, bool no_wifi);
}

namespace clcd {
    LiquidCrystal_I2C clcd(0x27, 20, 4);
    String lines[4];
    int lines_mod_ms[4] = {1}; // Timestamp of the last line modification

    void init() {
        clcd.init();
        clcd.backlight();
        clcd.clear();
    }

    enum Placement { LEFT, MIDDLE, RIGHT };
    void setLine(const String& string, int line, Placement placement = LEFT) {
        if (string == lines[line]) {
            return;
        }

        if (string.length() > 20) {
            placement = LEFT;
        }

        switch (placement) {
            case LEFT:
                lines[line] = string;
                break;

            case MIDDLE:
                lines[line] = "";
                lines[line].reserve(10 - string.length() / 2 + string.length());
                for (int i = 0; i < 10 - string.length() / 2; i++) {
                    lines[line] += ' ';
                }
                lines[line] += string;
                break;

            case RIGHT:
                lines[line] = "";
                lines[line].reserve(20);
                for (int i = 0; i < 20 - string.length(); i++) {
                    lines[line] += ' ';
                }
                lines[line] += string;
                break;
        }

        lines_mod_ms[line] = millis();
    }

    void scrollLine(const String& string, int line, unsigned long delay_ms = 250, int spacing = 5) {
        char row[21] = {0};

        int starting_chr = (millis() - lines_mod_ms[line]) / delay_ms;
        for (int i = 0; i < 20; i++) {
            int chr = (starting_chr + i) % (string.length() + spacing);

            if (chr >= string.length()) {
                row[i] = ' ';
            }
            else {
                row[i] = string[chr];
            }
        }

        clcd.setCursor(0, line);
        clcd.print(row);
    }

    void update(bool override = false) {
        // Timestamp of the last line update to the CLCD
        static unsigned long last_update_ms[4] = {0};

        for (int line = 0; line < 4; line++) {
            // Discards already-updated static non-scrolling lines
            if (!override && lines[line].length() <= 20 && last_update_ms[line] > lines_mod_ms[line]) {
                continue;
            }

            // Rate-limits the number of changes to 300ms per line update
            if (!override && last_update_ms[line] + 300 > millis()) {
                continue;
            }

            if (lines[line].length() <= 20) {
                clcd.setCursor(0, line);
                clcd.print(lines[line]);

                for (int i = 0; i < 20 - lines[line].length(); i++) {
                    clcd.print(' ');
                }
            }
            else {
                scrollLine(lines[line], line);
            }

            last_update_ms[line] = millis();
        }
    }

    void clear() {
        for (int line = 0; line < 4; line++) {
            lines[line] = "";
            lines_mod_ms[line] = millis();
        }

        update(true);
    }

    void broadcast(const String& title, const String& description) {
        setLine("+==================+", 0);
        setLine(title, 1, MIDDLE);
        setLine(description, 2, MIDDLE);
        setLine("+==================+", 3);

        update(true);
    }

    void greetStudent(const Student& student, const String& note, unsigned long duration_ms = 5000) {
        setLine("Welcome, " + student.name + "!", 0);
        setLine(note, 1, MIDDLE);
        setLine(String(student.school_id) + " " + String(student.class_id) + "/" + student.classroom, 2,
                MIDDLE);
        setLine("Card ID: " + String(student.card_uid, HEX), 3);

        // The rest of the code below makes up for line 2 (3rd line, 1-indexed).
        String school_id = String(student.school_id);
        String class_id_and_classroom = String(student.class_id) + "/" + student.classroom;
        String line_2 = school_id;

        // Adds spacing in the middle, so that `school_id` is placed to the left of the CLCD, and
        // `class_id_and_classroom` is placed to the right
        if (school_id.length() + class_id_and_classroom.length() < 20) {
            line_2.reserve(20);
            for (int i = 0; i < 20 - school_id.length() - class_id_and_classroom.length(); i++) {
                line_2 += ' ';
            }
        }
        else {
            line_2.reserve(school_id.length() + 1 + class_id_and_classroom.length());
            line_2 += ' ';
        }

        line_2 += class_id_and_classroom;
        setLine(line_2, 2);

        misc::delay(duration_ms, false);
    }
}
