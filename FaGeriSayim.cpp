#include "Arduino.h"
#include "FaGeriSayim.h"

void FaGeriSayim::Basla()
{
  baslamaZamani = micros();
  durmaZamani = 0;

}
void FaGeriSayim::Durdur()
{
  if (baslamaZamani > 0)
  {

    durmaZamani = micros();
    gecenZaman += (durmaZamani - baslamaZamani);
    baslamaZamani=0;

  }

}
unsigned long FaGeriSayim::GetKalanZaman()
{

  
 unsigned long R=toplamZaman;



  if (gecenZaman > toplamZaman)
    R=0;
 
    
  else if (baslamaZamani > 0)
  {
    unsigned long basladiktanItibarenGecenSure=(micros() - baslamaZamani) + gecenZaman ;

    if (basladiktanItibarenGecenSure > toplamZaman)
      R=0;
    else
      R = toplamZaman -  basladiktanItibarenGecenSure;
  
  }
  else if (durmaZamani == 0)
  {
      R = toplamZaman - gecenZaman;
  }
  
 


  return R;


}
void FaGeriSayim::SetToplamZaman(unsigned long ToplamZaman)
{
  toplamZaman = ToplamZaman;
  durmaZamani = 0;
  gecenZaman  = 0;
  baslamaZamani =0;
  

}

