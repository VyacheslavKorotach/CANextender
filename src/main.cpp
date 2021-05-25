#include "main.h"

CAN_device_t CAN_cfg;               // CAN Config
unsigned long previousMillis = 0;   // will store last time a CAN Message was send
const int interval = 1000;          // interval at which send CAN Messages (milliseconds)
const int rx_queue_size = 10;       // Receive Queue size

unsigned long microseconds;
 
uint16_t icanBuf[ICAN_BUF];
unsigned char* uchar_buf = (unsigned char*)(&icanBuf);

uint8_t address = 0;
const int wdtTimeout = WATCH_DOG_TIMEOUT;                         //time in ms to trigger the watchdog
int counter = 0;

/*--- PREFERENCES ---*/
Preferences preferences;
unsigned long timeToSleep;

/*--- GLOBALS ---*/
hw_timer_t *timer = NULL;

EspMQTTClient client(
  WIFI_SSID,
  WIFI_PASS,
  MQTT_HOST,
  MQTT_USER,
  MQTT_PASS,
  DEVICE_NAME,
  MQTT_PORT
);

ESP32_FTPClient ftp(
  FTP_SERVER,
  FTP_USER,
  FTP_PASS,
  5000,
  0
);

String device_name = DEVICE_NAME;
String status_topic = MQTT_STATUS_TOPIC + device_name;
String ctrl_topic = MQTT_CONTROL_TOPIC + device_name;
String status_str_template = "{\"dn\":\"" + device_name + "\"";
String last_status_str = status_str_template + ", \"status\":\"I am going offline\"}";
String template_msg = "{}";

esp32FOTA esp32FOTA("esp32-fota-http", 1);  // Firmware http update

void setup() {
  
  //Init preferences
  preferences.begin("vibmet-prefs", false);
  timeToSleep = preferences.getULong("timeToSleep", TIME_TO_SLEEP);

  //Init watchdog timer
  timer = timerBegin(0, 80, true);                      //timer 0, div 80
  timerAttachInterrupt(timer, &resetModule, true);      //attach callback
  timerAlarmWrite(timer, wdtTimeout * 1000, false);     //set time in us
  timerAlarmEnable(timer); 

  //init serial port communication
  Serial.begin(115200);

  if(WIFI_DBG) client.enableDebuggingMessages();
  
  client.enableLastWillMessage(status_topic.c_str(), last_status_str.c_str());
  // client.enableHTTPWebUpdater(); //Enable the OTA1

  //work with EEPROM
  previousMillis = millis();
  EEPROM.begin(EEPROM_SIZE);
  counter = EEPROM16_Read(address) + 1; 
  EEPROM16_Write(address, counter);
  EEPROM.commit();

  /*--- Firmware updator ---*/
  esp32FOTA.checkURL = OTAJSONADDRESS;

  getAndSaveNewParams();  // Get and save new ican params
  timeToSleep = preferences.getULong("timeToSleep", timeToSleep); // Set up new gotten params

  Serial.println("Basic Demo - ESP32-Arduino-CAN");
  CAN_cfg.speed = CAN_SPEED_125KBPS;
  CAN_cfg.tx_pin_id = GPIO_NUM_5;
  CAN_cfg.rx_pin_id = GPIO_NUM_4;
  CAN_cfg.rx_queue = xQueueCreate(rx_queue_size, sizeof(CAN_frame_t));
  // Init CAN Module
  ESP32Can.CANInit();
}

void loop() {

  client.loop();

  timerWrite(timer, 0);                           //reset timer (feed watchdog)

  template_msg = "{\"dn\":";
  template_msg += "\"" + device_name + "\"";
  template_msg += ", \"rn\":" + String(counter);           // MQTT message prepearing

  CAN_frame_t rx_frame;

  unsigned long currentMillis = millis();

  // Receive next CAN frame from queue
  if (xQueueReceive(CAN_cfg.rx_queue, &rx_frame, 3 * portTICK_PERIOD_MS) == pdTRUE) {

    if (rx_frame.FIR.B.FF == CAN_frame_std) {
      printf("New standard frame");
    }
    else {
      printf("New extended frame");
    }

    if (rx_frame.FIR.B.RTR == CAN_RTR) {
      printf(" RTR from 0x%08X, DLC %d\r\n", rx_frame.MsgID,  rx_frame.FIR.B.DLC);
    }
    else {
      printf(" from 0x%08X, DLC %d, Data ", rx_frame.MsgID,  rx_frame.FIR.B.DLC);
      for (int i = 0; i < rx_frame.FIR.B.DLC; i++) {
        printf("0x%02X ", rx_frame.data.u8[i]);
      }
      printf("\n");

    /*----- Publish received data to MQTT -----*/
    String can_data = "can_received_data_string";
    String mqtt_data_msg = template_msg;
    mqtt_data_msg += ", \"data\":\"" + can_data + "\"";
    mqtt_data_msg += "}";
    String can_received_data_topic = MQTT_DATA_RECEIVED_TOPIC;
    can_received_data_topic += device_name;
    client.publish(can_received_data_topic, mqtt_data_msg);
    Serial.println(mqtt_data_msg);

    timerWrite(timer, 0);                       //reset timer (feed watchdog)
    EEPROM16_Write(address, counter);
    EEPROM.commit();   
    counter += 1;
    }
  }

  // Send CAN Message
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    CAN_frame_t tx_frame;
    tx_frame.FIR.B.FF = CAN_frame_std;
    tx_frame.MsgID = 0x001;
    tx_frame.FIR.B.DLC = 8;
    tx_frame.data.u8[0] = 0x00;
    tx_frame.data.u8[1] = 0x01;
    tx_frame.data.u8[2] = 0x02;
    tx_frame.data.u8[3] = 0x03;
    tx_frame.data.u8[4] = 0x04;
    tx_frame.data.u8[5] = 0x05;
    tx_frame.data.u8[6] = 0x06;
    tx_frame.data.u8[7] = 0x07;
    // ESP32Can.CANWriteFrame(&tx_frame);

    /*----- Publish sent data to MQTT -----*/
    String can_data = "can_sent_data_string";
    String mqtt_data_msg = template_msg;
    mqtt_data_msg += ", \"data\":\"" + can_data + "\"";
    mqtt_data_msg += "}";
    String can_sent_data_topic = MQTT_DATA_SENT_TOPIC;
    can_sent_data_topic += device_name;
    client.publish(can_sent_data_topic, mqtt_data_msg);
    Serial.println(mqtt_data_msg);

    timerWrite(timer, 0);                       //reset timer (feed watchdog)
    EEPROM16_Write(address, counter);
    EEPROM.commit();   
    counter += 1;

    // /*--- Get new firmware if it needed ---*/
    // bool updatedNeeded = esp32FOTA.execHTTPcheck();
    // if (updatedNeeded)
    // {
    //   timerAlarmDisable(timer);
    //   esp32FOTA.execOTA();
    // }
  }
}

/*--- Definitions ---*/
void onConnectionEstablished() {
  timerWrite(timer, 0);                       //reset timer (feed watchdog)

  // ftp.OpenConnection();  

  client.subscribe(ctrl_topic, [](const String & payload) {
  Serial.println(payload);
   });  

  String status_msg = "{\"dn\":";
  status_msg += "\"" + device_name + "\"";
  status_msg += ", \"rn\":" + String(counter);
  status_msg += ", \"status\":\"waiting for a command\"";
  status_msg += "}";
  client.publish(status_topic, status_msg);
}