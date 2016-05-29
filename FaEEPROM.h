
#ifndef FaEEPROM_h
#define FaEEPROM_h

#include <inttypes.h>


class FaEEPROMClass
{

  private:
    int restartAddres = 0; //0,1 bayt
    int stepHiziAdres = 2; //2,3 bayt
    int zamanSayaciAdres = 4; //4,5,6,7 bayt

    int ReadInt(int);
    void WriteInt(int, int);

    void Writelong(int, long);
    long Readlong(long);

  public:

    unsigned int RestartSayisi = 0;


    int GetStepHizi();
    void SetStepHizi(unsigned int);

    unsigned long GetZamanSayaci();
    void SetZamanSayaci(unsigned long);

    void RestartSay();
};

extern FaEEPROMClass FaEEPROM;

#endif


