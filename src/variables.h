#include <Arduino.h>

#ifndef Variable_h

#define Variable_h

String inputbuffer;
#define  countday 7 //
#define  countperiods  4 //
#define  countklapan  4 //
#define offsetData 128 //смещение для хранения структуры данных с настройками 
bool klapanstate[countklapan]; //Состояния клапанов
int klapanpins[]={12,11,10,9};
long prevtime;
//#pragma pack(push,1)
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

Tklapan klapan[countklapan];
//#pragma pack(pop)
#endif