#ifndef _CFG
#define _CFG

/*--- Network parameters ---*/

        /*---WiFi ---*/
#define WIFI_SSID       "raspi-salo"
#define WIFI_PASS       "salo54321///"

        /*--- MQTT ---*/
#define MQTT_HOST       "korotach.com"
#define MQTT_PORT       1883
#define MQTT_USER       "igor"
#define MQTT_PASS       "igor1315"
#define DEVICE_NAME     "ican00001"

#define MQTT_DATA_RECEIVED_TOPIC    "ican/data/received/" // MQTT RECEIVED DATA topic
#define MQTT_DATA_SENT_TOPIC        "ican/data/sent/"     // MQTT SENT DATA topic
#define MQTT_STATUS_TOPIC           "ican/status/"        // MQTT STATUS topic
#define MQTT_CONTROL_TOPIC          "ican/control/"       // MQTT CONTROL topic

        /*--- FTP ---*/
#define FTP_SERVER      "192.168.50.1"
#define FTP_USER        "salo"
#define FTP_PASS        "salo54321"

        /*--- OTA JSON ADDRESS ---*/
#define OTAJSONADDRESS "http://ican.korotach.com/CANextender/fota/canext00001/fota.json"

//         /*--- PARAMS JSON ADDRESS ---*/
#define PARAMSJSONPATH "http://ican.korotach.com/device/params/"

/*--- Firmware configuration ---*/
#define EEPROM_SIZE     2                             //EEPROM
#define uS_TO_mS_FACTOR  1000ULL                       // Conversion factor for micro seconds to seconds
#define TIME_TO_SLEEP   100                           // Time ESP32 will go to sleep (in milliseconds)
#define WATCH_DOG_TIMEOUT 8000                       //time in ms to trigger the watchdog
#define ICAN_BUF 1024

/*--- Operation mode config ---*/
#define WIFI_DBG        1

#endif
