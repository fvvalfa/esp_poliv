#include <Arduino.h>
#include <Wire.h>
#include <eeprom.h>
#include <variables.h>
#include <utils.h>
#include <Time.h>
#include <parse.h>
#include <WiFiUdp.h>
#include <WiFiManager.h>


int setting(int _setting, int ii) //Setting - 0 для заполнения нулями структуры klapan
 {
   if (_setting==0) return 255;
   return ii;
 }

void setKlapans(int set)
{
  int ii=0;
  for (int k=0;k<countklapan;k++)
  {
   for (int d = 0;d<countday;d++)
    {
     for (int t = 0;t<countperiods;t++)
      {
         if (ii<=-1) ii=0;
         klapan[k].sheduler_day[d].timework[t].starthour=setting(set,ii);
         //Serial.println(ii);
         ii++;
         if (ii<=-1) ii=0;
         klapan[k].sheduler_day[d].timework[t].startmin=setting(set,ii);
        // Serial.println(ii);
         ii++;
         if (ii<=-1) ii=0;
         klapan[k].sheduler_day[d].timework[t].duration=setting(set,ii);
        // Serial.println(ii);
         ii++;
      }
   
    }
}
  
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(21,22);
  uint8_t firstStart=0;
  loadFromEEPROMData(0,firstStart);
  if (firstStart!=0x50){
    //первый старт
    setKlapans(0);
    if (saveToEEPROMData(offsetData,klapan)!=0) Serial.println("Ошибка записи");
    saveToEEPROMData(0,0x50);
  }else
  {
    {
      Serial.println("Не первый запуск");
      loadFromEEPROMData(offsetData,klapan);
    }
  }
  for (int ii=0;ii<4;ii++)
  {
    pinMode(klapanpins[ii],OUTPUT);
    digitalWrite(klapanpins[ii],HIGH);
  }
  prevtime=millis();

  klapanstate[0]=true;
  klapanstate[1]=true;
  klapanstate[2]=true;
  klapanstate[3]=true;

  //инициальзация точки доступа 
   if (ESP_MODE == 0) {    // режим точки доступа
    WiFi.softAPConfig(IPAddress(IP_AP[0], IP_AP[1], IP_AP[2], IP_AP[3]),
                      IPAddress(192, 168, 4, 1),
                      IPAddress(255, 255, 255, 0));

    WiFi.softAP(AP_NameChar, WiFiPassword);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("Access point Mode");
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    server.begin();
  } else {                // подключаемся к роутеру
    Serial.print("WiFi manager");
    WiFiManager wifiManager;
    wifiManager.setDebugOutput(true);
    //wifiManager.se setDebugOutput(false);
    #if (USE_BUTTON == 1)
      if (digitalRead(BTN_PIN)) wifiManager.resetSettings();
    #endif
    wifiManager.autoConnect(autoConnectSSID, autoConnectPass);
}
  Udp.begin(localPort);
 // setKlapans(0);
}


void loop() {

 Serial.begin(115200);
  esp_int_wdt_init();
  esp_task_wdt_init(5000, true);
  enableLoopWDT();
  while (1!=2)
  {
    /* code */
     delay(10);
  }
  
 
  parseCommand();
 delay(10);
  
 
}