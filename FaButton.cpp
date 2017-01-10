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



//FaButtonClass FaButton;

