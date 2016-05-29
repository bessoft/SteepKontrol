#include "Arduino.h"
#include "FaDegerSakla.h"


bool FaDegerSakla::Sakla(String pSatir1, String pSatir2,String pSatir3, String pSatir4)
{
  if ((Satir1 != pSatir1) || (Satir2 != pSatir2) || (Satir3 != pSatir3)|| (Satir4 != pSatir4))
  {
    Satir1=pSatir1;
    Satir2=pSatir2;
    Satir3=pSatir3;
    Satir4=pSatir4;
    
    
    return true;
  }
  else
  {
    Satir1=pSatir1;
    Satir2=pSatir2;
    Satir3=pSatir3;
    Satir4=pSatir4;
    
    return false;
  }
}



