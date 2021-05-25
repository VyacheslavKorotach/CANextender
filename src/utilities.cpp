#include "utilities.h"

void EEPROM16_Write(uint8_t a, uint16_t b) {
  EEPROM.write(a, lowByte(b));
  EEPROM.write(a + 1, highByte(b));
}

uint16_t EEPROM16_Read(uint8_t a) {
  return word(EEPROM.read(a + 1), EEPROM.read(a));
}

/*--- Get and save params ---*/
void getAndSaveNewParams() {
  Serial.println("Start getting params");
  long paramGettingStart = millis();
  HTTPClient http;
  String paramPath = PARAMSJSONPATH;
  paramPath += DEVICE_NAME;
  paramPath += ".cfg";
  http.begin(paramPath.c_str());
  int httpResponseCode = http.GET();
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();  // get parameters
    Serial.println(payload);

    DynamicJsonDocument doc(1024);  // parse gotten parameters
    deserializeJson(doc, payload);
    unsigned long newTimeToSleep = doc["sleepTime"];

    Preferences preferences;
    preferences.begin("vibmet-prefs", false);
    preferences.putULong("timeToSleep", newTimeToSleep);  // set parameters
    preferences.end();

  } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
  }
  http.end();
  String getSetTime = String(millis() - paramGettingStart);
  Serial.println("Param get/set time: " + getSetTime);
}

void IRAM_ATTR resetModule() {
  ets_printf("watchdog reboot\n");
  esp_restart();
}