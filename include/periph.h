/*--- Peripherals driver ---*/

#ifndef _PERIPH
#define _PERIPH

#include <Arduino.h>
#include "config.h"

typedef enum periph {
    FILTER,
    LDO,
    VREF
}           periph_t;


void Periph_Init(void);
void Periph_Switch(periph_t periph, uint32_t mode);

#endif
