#ifndef _UTILITIES
#define _UTILITIES

#include "config.h"
#include <EEPROM.h>

void EEPROM16_Write(uint8_t a, uint16_t b);
uint16_t EEPROM16_Read(uint8_t a);

#include <HTTPClient.h>
void getAndSaveNewParams();

#include <Preferences.h>
#include <ArduinoJson.h>

#endif
