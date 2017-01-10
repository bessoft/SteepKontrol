#include "Arduino.h"
#include "FaDegerSakla.h"


bool FaDegerSakla::Degisti1()
{
  return FDegisti1; 
}


bool FaDegerSakla::Degisti2()
{
  return FDegisti2; 
}

bool FaDegerSakla::Degisti3()
{
  return FDegisti3; 
}

bool FaDegerSakla::Degisti4()
{
  return FDegisti4; 
}


bool FaDegerSakla::Sakla(String pSatir1, String pSatir2,String pSatir3, String pSatir4)
{

    FDegisti1=false;
    FDegisti2=false;
    FDegisti3=false;
    FDegisti4=false;
 
  
  if (Satir1 != pSatir1)
  {
    FDegisti1=true;
  }
  if (Satir2 != pSatir2)
  {
    FDegisti2=true;
  }
  if (Satir3 != pSatir3)
  {
    FDegisti3=true;
  }
  if (Satir4 != pSatir4)
  {
    FDegisti4=true;
  }
  
  
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



