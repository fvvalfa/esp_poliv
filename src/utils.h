
#include <Arduino.h>
#include <variables.h>
uint8_t crc8( ) {
  uint8_t count=0;
  uint8_t crc = 0;
  uint8_t inbyte=0;
  for (int k=0;k<countklapan;k++)
   {
     for (int d = 0;d<countday;d++)
      {
        for (int t = 0;t<countperiods;t++)
          {
            switch (count)
            {
            case 0:
               inbyte = klapan[k].sheduler_day[d].timework[t].starthour;
              break;
            case 1:
               inbyte = klapan[k].sheduler_day[d].timework[t].startmin;
              break;
            case 2:
               inbyte = klapan[k].sheduler_day[d].timework[t].duration;
              break;
            
            default:
              break;
            }
            for (uint8_t i = 8; i; i--) {
              uint8_t mix = (crc ^ inbyte) & 0x01;
              crc >>= 1;
              if (mix) crc ^= 0x8C;
              inbyte >>= 1;
            }
            count++;
            if (count==3) count=0;
          }
      }
    }
  return crc;

}



void dataToSerial()
{
   
  
     for (int k=0;k<countklapan;k++)
  {
   for (int d = 0;d<countday;d++)
    {
     for (int t = 0;t<countperiods;t++)
      {
         Serial.printf("Start hour - %d \n",klapan[k].sheduler_day[d].timework[t].starthour);
         Serial.printf("Start min - %d \n",klapan[k].sheduler_day[d].timework[t].startmin);
         Serial.printf("Start duration - %d \n",klapan[k].sheduler_day[d].timework[t].duration);
      }
   
    } 
  }

}
