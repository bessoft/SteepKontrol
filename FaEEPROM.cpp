#include <Arduino.h>
#include <EEPROM.h>
#include "FaEEPROM.h"

#include <inttypes.h>




int FaEEPROMClass::ReadInt(int p_address)
{
  byte lowByte = EEPROM.read(p_address);
  byte highByte = EEPROM.read(p_address + 1);

  return ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
}

void FaEEPROMClass::WriteInt(int p_address, int p_value)
{
  byte lowByte = ((p_value >> 0) & 0xFF);
  byte highByte = ((p_value >> 8) & 0xFF);

  EEPROM.write(p_address, lowByte);
  EEPROM.write(p_address + 1, highByte);

  //EEPROM.write(p_address, 0);
  //EEPROM.write(p_address+1, 0);

}

void FaEEPROMClass::Writelong(int address, long value)
{
  //Decomposition from a long to 4 bytes by using bitshift.
  //One = Most significant -> Four = Least significant byte
  byte four = (value & 0xFF);
  byte three = ((value >> 8) & 0xFF);
  byte two = ((value >> 16) & 0xFF);
  byte one = ((value >> 24) & 0xFF);

  //Write the 4 bytes into the eeprom memory.
  EEPROM.write(address, four);
  EEPROM.write(address + 1, three);
  EEPROM.write(address + 2, two);
  EEPROM.write(address + 3, one);
}


long FaEEPROMClass::Readlong(long address)
{
  //Read the 4 bytes from the eeprom memory.
  long four = EEPROM.read(address);
  long three = EEPROM.read(address + 1);
  long two = EEPROM.read(address + 2);
  long one = EEPROM.read(address + 3);

  //Return the recomposed long by using bitshift.
  return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}



void FaEEPROMClass::RestartSay()
{
  unsigned int value = FaEEPROM.ReadInt(restartAddres);
  value += 1;
  FaEEPROM.WriteInt(restartAddres, value);
  FaEEPROM.RestartSayisi = value;

}


int FaEEPROMClass::GetStepHizi()
{
  return FaEEPROM.ReadInt(stepHiziAdres);
}
void FaEEPROMClass::SetStepHizi(unsigned int value)
{
  FaEEPROM.WriteInt(stepHiziAdres, value);
}


unsigned long FaEEPROMClass::GetZamanSayaci()
{

  unsigned long deger = FaEEPROM.Readlong(zamanSayaciAdres);

  if (deger == 0)
    deger = 100000;

  return deger;

}
void FaEEPROMClass::SetZamanSayaci(unsigned long value)
{
  FaEEPROM.Writelong(zamanSayaciAdres, value);
}





FaEEPROMClass FaEEPROM;

