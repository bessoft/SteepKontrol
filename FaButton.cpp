#include <Arduino.h>
#include "FaButton.h"

#include <inttypes.h>



int FaButton::JoistikOku(int Port,int DefValue, int MaxValue){

   int outputValue = 0;  
   int sensorValue;

   sensorValue = analogRead(Port);
    if (sensorValue < (DefValue - 1))
    outputValue = map(sensorValue, 0, DefValue, MaxValue, 0);
  else if (sensorValue > (DefValue + 1))
    outputValue = map(sensorValue,DefValue, 1021, 0, (MaxValue * (-1)));
  else
    outputValue = 0;

  return outputValue;
  
}



int FaButton::GetButton(int ButtonSize,int AnalogPortNo)
{

  byte OrtaDeger;
  
  int sensorValue = analogRead(AnalogPortNo);
  
  int SafDeger = map(sensorValue, 0, 1023, 0, ButtonSize+3);
    
  OrtaDeger = (ButtonSize+2) / 2;
  
  if(SafDeger ==  OrtaDeger)
  {
    SafDeger=0;
  }
  else if(SafDeger > OrtaDeger)
  {
    SafDeger -= 1;
  }


 
  return SafDeger;
}

void FaButton::BeklemeliButonOku(unsigned long MiliSaniye)
{
 
  if (ButtonSakla == 0)
  {
    if (Bekle2 < millis() - MiliSaniye)
    { 
     Bekle2=millis();
     GenelButton = this->GetButton(4,A5);
     
    }
  }
  if (GenelButton != 0)
  {
   ButtonSakla=GenelButton;
  } 
}
  


//FaButtonClass FaButton;

