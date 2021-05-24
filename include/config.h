#ifndef _CFG
#define _CFG

/*--- Network parameters ---*/

        /*---WiFi ---*/
#define WIFI_SSID       "raspi-salo"
#define WIFI_PASS       "salo54321///"

        /*--- MQTT ---*/
#define MQTT_HOST       "192.168.50.1"
#define MQTT_PORT       1883
#define MQTT_USER       "salo"
#define MQTT_PASS       "salo54321"
#define DEVICE_NAME     "canext00001"

        /*--- FTP ---*/
#define FTP_SERVER      "192.168.50.1"
#define FTP_USER        "salo"
#define FTP_PASS        "salo54321"

        /*--- OTA JSON ADDRESS ---*/
#define OTAJSONADDRESS "http://canexpender.korotach.com/CANextender/fota/canext00001/fota.json"

//         /*--- PARAMS JSON ADDRESS ---*/
#define PARAMSJSONPATH "http://canexpender.korotach.com/sensor/params/"

/*--- Firmware configuration ---*/
#define EEPROM_SIZE     2                             //EEPROM
#define uS_TO_mS_FACTOR  1000ULL                       // Conversion factor for micro seconds to seconds
#define TIME_TO_SLEEP   100                           // Time ESP32 will go to sleep (in milliseconds)

#endif
