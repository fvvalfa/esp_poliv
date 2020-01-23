#include <Arduino.h>
#include <variables.h>
#include <Time.h>
  time_t t;

void parseCommand()
{
    t = now();
  if (inputbuffer.startsWith("GETTIME"))
  {
    Serial.println(inputbuffer);
    Serial.println("gettime");
    inputbuffer="OK-CURTIME:";
    inputbuffer+=String(hour(t))+":";
    inputbuffer+=String(minute(t))+":";
    inputbuffer+=String(second(t))+":";
    inputbuffer+=String(day(t))+":";
    inputbuffer+=String(month(t))+":";
    inputbuffer+=String(year(t))+":";
  
    Serial.println(inputbuffer);
   
  } else if(inputbuffer.startsWith("SETTIME")){
     Serial.println(inputbuffer);
     uint8_t end=0;
     tmElements_t temp_t;
     uint8_t start=0;
     for (size_t i = 0; i < 7; i++)
     {
      start = end;
      end  = inputbuffer.indexOf(":",start+1);
      String temp_s = inputbuffer.substring(start+1,end);
      switch (i)
      {
      case 1:
        temp_t.Hour=(byte)temp_s.toInt();
        break;
      case 2:
        temp_t.Minute = (byte)temp_s.toInt();
        break;
      case 3:
        temp_t.Second = (byte)temp_s.toInt();
        break;
      case 4:
        temp_t.Day = (byte)temp_s.toInt();
        break;
      case 5:
        temp_t.Month = (byte)temp_s.toInt();
        break;
      case 6:
        temp_t.Year = (byte)temp_s.toInt()-1970;
        break;
      default:
        break;
      }
     };
    inputbuffer="OK-SETTIME:";
    inputbuffer+=String(temp_t.Hour)+":";
    inputbuffer+=String(temp_t.Minute)+":";
    inputbuffer+=String(temp_t.Second)+":";
    inputbuffer+=String(temp_t.Day)+":";
    inputbuffer+=String(temp_t.Month)+":";
    inputbuffer+=String(temp_t.Year+1970);
    setTime(makeTime(temp_t));
    }
    else if (inputbuffer.startsWith("GETDATA")){
    Serial.println(inputbuffer);
     inputbuffer="OK-GETDATA:";
     for (int k=0;k<countklapan;k++)
      {
       for (int d = 0;d<countday;d++)
        {
         for (int t = 0;t<countperiods;t++)
         {
           inputbuffer+=String(klapan[k].sheduler_day[d].timework[t].starthour)+":";
           inputbuffer+=String(klapan[k].sheduler_day[d].timework[t].startmin)+":";
           inputbuffer+=String(klapan[k].sheduler_day[d].timework[t].duration)+":";
          }
       }
    }
    Serial.println(inputbuffer);
  }
   else if(inputbuffer.startsWith("SETDATA")){
    uint16_t start=0;
    uint16_t end=0;
    start = end;
    end  = inputbuffer.indexOf(":",start+1);
    String temp_s = inputbuffer.substring(start+1,end);
     for (int k=0;k<countklapan;k++)
      {
       for (int d = 0;d<countday;d++)
        {
         for (int t = 0;t<countperiods;t++)
         {
          for (size_t i = 0; i < 3; i++)
          {
            start = end;
            end  = inputbuffer.indexOf(":",start+1);
            String temp_s = inputbuffer.substring(start+1,end);
           
            switch (i)
            {
            case 0:
              klapan[k].sheduler_day[d].timework[t].starthour=(byte)temp_s.toInt();
              break;
            case 1:
              klapan[k].sheduler_day[d].timework[t].startmin=(byte)temp_s.toInt();
              break;
            case 2:
              klapan[k].sheduler_day[d].timework[t].duration=(byte)temp_s.toInt();
              break;
            default:
              break;
            }
          }
          
        }
       }
    }

  }

 
}