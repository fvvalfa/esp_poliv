#include <Arduino.h>
#include <WiFiUdp.h>
#include <WiFiManager.h>

#ifndef Variable_h

#define Variable_h
#define debug 1
#define LOGSERIAL(x) Serial.println(x);

;
#define  countday 7 //
#define  countperiods  4 //
#define  countklapan  4 //
#define offsetData 128 //смещение для хранения структуры данных с настройками 
bool klapanstate[countklapan]; //Состояния клапанов
int klapanpins[]={12,11,10,9};
long prevtime;
#pragma pack(push,1)
  struct Tsheduler
{
  uint8_t starthour=-1;
  uint8_t startmin=-1;
  uint8_t duration=0;
};
struct Tsheduler_day 
{
  Tsheduler timework[countperiods]; 
};

struct Tklapan
{

  Tsheduler_day sheduler_day [countday];
};

Tklapan klapan[countklapan]; //массив для хранения настроек клапанов
#pragma pack(pop)

// ============= НАСТРОЙКИ =============
// -------- КНОПКА -------
#define USE_BUTTON 1    // 1 - использовать кнопку, 0 - нет
#define BTN_PIN 2

// --------- ESP --------
#define ESP_MODE 1
// 0 - точка доступа
// 1 - локальный
// ----- AP (точка доступа) -------
#define AP_SSID "test2"
#define AP_PASS "0908070605"
#define AP_PORT 8888

// -------- Менеджер WiFi ---------
#define AC_SSID "AutoConnectAP"
#define AC_PASS "12345678"

byte IP_AP[] = {192, 168, 4, 66};   // статический IP точки доступа (менять только последнюю цифру
const char AP_NameChar[] = AP_SSID;
const char WiFiPassword[] = AP_PASS;
const char* autoConnectSSID = AC_SSID;
const char* autoConnectPass = AC_PASS;
unsigned int localPort = AP_PORT;

#define  UDP_TX_PACKET_MAX_SIZE  1460

WiFiServer server(80);
WiFiUDP Udp;

String inputbuffer;

char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1];
#endif