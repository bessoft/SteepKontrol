#include "Arduino.h"
#include "FaDecimalView.h"


void FaDecimalView::SetMicros(unsigned long value)
{
  int _dakika = value / 60000000L;

  int _saniye = (value % 60000000L) / 1000000L;

  SetValue((_dakika*100) + _saniye );
 
  
  
}


void FaDecimalView::SetValue(int value)
{

  if (value != Value)
  {
    if (value > 9999)

      if (SaatModu == true)
        Value = 9959;
      else
        Value = 9999;


    else if (value < 0)
      Value = 0;
    else
      Value = value;


    birler = 0;
    onlar = 0;
    yuzler = 0;
    binler = 0;

    int sayi = Value;

    if (Value > 0)
    {
      birler = sayi - ((sayi / 10) * 10);
      if (Value >= 10)
      {
        sayi = sayi / 10;
        onlar = sayi - ((sayi / 10) * 10);
        if (Value >= 100)
        {
          sayi = sayi / 10;
          yuzler = sayi - ((sayi / 10) * 10);
          if (Value >= 1000)
          {
            sayi = sayi / 10;
            binler = sayi;
          }
        }
      }
    }



    TamKisim = (binler * 10) + yuzler;
    OndalikKisim = (onlar * 10) + birler;


    if (SaatModu)
    {
      ToplamSaniye=(TamKisim * 60) + OndalikKisim;
    }

    
    stringDeger = String(binler) + String(yuzler) + Sparator + String(onlar) + String(birler);

  }

}


void FaDecimalView::SaniyeDus()
{
  int Saniye=ToplamSaniye-1;
  int ModSaniye=(Saniye % 60);
  int Dakika=(Saniye / 60);
  SetValue((Dakika*100)+ModSaniye);
  
  
}

void FaDecimalView::UpDownDigit(int digit, int updownn)
{
  int add = 0;
  if (updownn > 0)
  {
    if ((digit == 4) && (birler < 9))
      add = 1;
    else if (digit == 3)
    {
      if ((SaatModu) && (onlar < 5))
        add = 10;
      else if ((!SaatModu) && (onlar < 9))
        add = 10;
    }
    else if ((digit == 2) && (yuzler < 9))
      add = 100;
    else if ((digit == 1) && (binler < 9))
      add = 1000;

  }
  else
  {
    if ((digit == 4) && (birler > 0))
      add = 1;
    else if ((digit == 3) && (onlar > 0))
      add = 10;
    else if ((digit == 2) && (yuzler > 0))
      add = 100;
    else if ((digit == 1) && (binler > 0))
      add = 1000;
  }

  SetValue(Value + (add * updownn));

}

String FaDecimalView::ToString()
{
  return stringDeger ;
}


int FaDecimalView::GetValue()
{
  return Value ;
}

int FaDecimalView::GetToplamSaniye()
{
  return ToplamSaniye;
}


