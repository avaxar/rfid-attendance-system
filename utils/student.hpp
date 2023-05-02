#pragma once

#include <Arduino.h>
#include <stdint.h>


struct Student {
    uint32_t card_uid;
    String name;
    String classroom;
    uint32_t school_id; // Student ID
    uint32_t class_id;  // Class number
};
