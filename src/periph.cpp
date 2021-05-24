#include "periph.h"

void Periph_Init(void) {
    pinMode(FILTER_PIN, OUTPUT);
    pinMode(VREF_PIN, OUTPUT);
    pinMode(LDO_PIN, OUTPUT);
}

void Periph_Switch(periph_t periph, uint32_t mode) {
    switch (periph) {
    case FILTER:
        digitalWrite(FILTER_PIN, mode);
        break;
    case LDO:
        digitalWrite(LDO_PIN, mode);
        break;
    case VREF:
        digitalWrite(VREF_PIN, mode);
        break;
    default:
        break;
    }
}