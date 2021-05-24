#ifndef _CFG
#define _CFG

#define ON      1
#define OFF     0

/*--- Network parameters ---*/

        /*---WiFi ---*/
#define WIFI_SSID       "raspi-salo"
#define WIFI_PASS       "salo54321///"
//#define WIFI_SSID       "HakunaMatata"
//#define WIFI_PASS       "pechersk293"
//#define WIFI_SSID       "PECI.COM.UA"
//#define WIFI_PASS       "salo54321///"

        /*--- MQTT ---*/
#define MQTT_HOST       "192.168.50.1"
#define MQTT_PORT       1883
#define MQTT_USER       "salo"
#define MQTT_PASS       "salo54321"
#define DEVICE_NAME     "vibmet00023"

        /*--- FTP ---*/
#define FTP_SERVER      "192.168.50.1"
#define FTP_USER        "salo"
#define FTP_PASS        "salo54321"

        /*--- OTA JSON ADDRESS ---*/
#define OTAJSONADDRESS "http://korotach.com/iBoart/fota/vibmet00018/fota.json"

//         /*--- PARAMS JSON ADDRESS ---*/
#define PARAMSJSONPATH "http://iboart.korotach.com/sensor/params/"

/*--- Firmware configuration ---*/
#define EEPROM_SIZE     2                             //EEPROM
#define uS_TO_mS_FACTOR  1000ULL                       // Conversion factor for micro seconds to seconds
#define TIME_TO_SLEEP   100                           // Time ESP32 will go to sleep (in milliseconds)
#define UPL_TO_SLEEP    1                             // Total files should be uploaded before stop
#define SAMPLES_IN_RAM  16384                         // Must be a power of 2 128 512 2048 4096, 16384, 32768 - max
#define LOOP_FREQ       0.5                           // Hz, how often data will be collected and sent in one loop
#define SAMP_FREQ       20000                         // Hz, must be less than 10000 due to ADC
#define MIC_SAMP_FREQ   16000
#define SPI_CLK         5000000                       //SPI clock (MHz)

/*--- ADC Pins on PCB ---*/
#define ADC_RESET       4
#define ADC_CONVST      21
//#define ADC_ALERT     25      //for 4 and 8 ch versions
#define ADC_CS          5

/*--- Peripherals pins on PCB ---*/
#define FILTER_PIN      2
#define VREF_PIN        15
#define LDO_PIN         26

/*--- LEDs pins on PCB ---*/
#define SLEEP_PIN       12
#define CONN_PIN        14
#define DATA_ACQ_PIN    27
#define DATA_TX_PIN     13

/*--- Digital Mic pins on PCB ---*/
#define I2S_SCK_PIN     26
#define I2S_WS_PIN      25
#define I2S_SD_PIN      33

/*--- Operation mode config ---*/
#define ADC_DBG         0
#define WIFI_DBG        1

/*--- Digital mic config ---*/
#define BUF_SAMPLES     128
#define MIC_SAMP_FREQ   16000

#endif
