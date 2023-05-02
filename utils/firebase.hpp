#pragma once

#include "student.hpp"


Student fetchStudent(uint32_t card_uid) {
    Student student = {.card_uid = card_uid};

    switch (student.card_uid) {
        case 0xCC74EE6F:
            student.name = "Avaxar";
            break;
        case 0x50CD49CF:
            student.name = "Lyn";
            break;
        case 0x638CD1CF:
            student.name = "SpookyOcean";
            break;
        case 0x5B3E024F:
            student.name = "DogeBonk";
            break;
        case 0xBD5691EF:
            student.name = "Yu";
            break;
        default:
            student.name = "Unknown";
            break;
    }

    return student;
}
