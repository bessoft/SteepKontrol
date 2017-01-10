#include "Arduino.h"
#include "FaZamanlayici.h"


bool FaZamanlayici::MicrosaniyedeBir(unsigned long BeklemeSuresi)
{
  volatile bool R=false;
 
  volatile unsigned long fark = micros() - BeklemeSuresi;
  
  if (SonOkunanMicrosaniye < fark)
  {
    SonOkunanMicrosaniye=micros();
    R=true;
  }
  return R;
  
}

void FaZamanlayici::Reset()
{
    SonOkunanMicrosaniye=micros();
}

//bool FaZamanlayici::DakikadaXDefaStepGonder(int PortNo, unsigned long DakikadakiTekrarSayisi)
//{
//
//  volatile bool R=false;
//
//  volatile unsigned long Dakika = 60000000;//Microsaniye
//  volatile unsigned long MicroSaniyeBeklemeSuresi = (Dakika / DakikadakiTekrarSayisi);
// 
//  volatile unsigned long fark = micros() - MicroSaniyeBeklemeSuresi;
//  
//  if (DakikaIcinSonOkunanMicrosaniye < fark)
//  {
//    digitalWrite(PortNo, HIGH );
//    delayMicroseconds(10);
//    R=true;
//    digitalWrite( PortNo, LOW );
//    DakikaIcinSonOkunanMicrosaniye=micros();
//  }
//  return R;
//}



