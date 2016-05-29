#ifndef FaZamanlayici_h
#define FaZamanlayici_h

class FaZamanlayici {
  public:

    bool MicrosaniyedeBir(unsigned long);
    //bool MilisaniyedeBir(unsigned long);
    //bool SaniyedeBir(unsigned long);

    //bool DakikadaXDefaStepGonder(int, unsigned long);
    

  private:
    volatile unsigned long SonOkunanMicrosaniye=0;
    //volatile unsigned long DakikaIcinSonOkunanMicrosaniye=0;
 
 };

#endif

