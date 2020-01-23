#include <Wire.h>
#include <Arduino.h>
#include <variables.h>
uint8_t error, address;
int nDevices;  //Кол-во найденных устройств


void scan() {
  Serial.println("Scanning...");
  nDevices = 0;
  for (address = 1; address < 127; address++ )  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0)    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");
      nDevices++;
    }
    else if (error == 4)    {
      Serial.print("Unknow error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
  delay(5000);  // Ждем 5 сек. до следующего сканирования
}



#define chip1 0x50 // device address for left-hand chip on our breadboard
// always have your values in variables



uint8_t writeData(int device, unsigned int add, byte data)
// writes a byte of data 'data' to the chip at I2C address 'device', in memory location 'add'
{
  Wire.beginTransmission(device);
  Wire.write((int)(add >> 8)); // left-part of pointer address
  Wire.write((int)(add & 0xFF)); // and the right
  Wire.write(data);
  uint8_t out = Wire.endTransmission();
  delay(5);
  return out;
}
 
byte readData(int device, unsigned int add)
// reads a byte of data from memory location 'add' in chip at I2C address 'device'
{
  byte result; // returned value
  Wire.beginTransmission(device); // these three lines set the pointer position in the EEPROM
  Wire.write((int)(add >> 8)); // left-part of pointer address
  Wire.write((int)(add & 0xFF)); // and the right
  Wire.endTransmission();
  Wire.requestFrom(device,1); // now get the byte of data...
  result = Wire.read();
  return result; // and return it as a result of the function readData
}
 
 template <class T> int saveToEEPROMData(uint16_t ee, const T& value)
{
    const byte* p = (const byte*)(const void*)&value;
    unsigned int i;
    int out;
    for (i = 0; i < sizeof(value); i++)
    {  out = writeData(chip1,ee++,*p++);
      if (out!=0) return out;
    }
     
    return i;
}
 
template <class T> int loadFromEEPROMData(uint16_t ee, T& value)
{
    byte* p = (byte*)(void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
      *p++ = readData(chip1,ee++);
    return i;
}
void testwrite()
{
 
byte d=0; // example variable to handle data going in and out of EERPROMS

  Serial.println("Writing data...");
  for (int a=0; a<32000; a++)
  {
    writeData(chip1,a,a);
  }
  Serial.println("Reading data...");
  for (int a=0; a<32000; a++)
  {
    Serial.print("chip1 pointer ");
    Serial.print(a);
    Serial.print(" holds ");
    d=readData(chip1,a);
    Serial.println(d, DEC);
  }
}
