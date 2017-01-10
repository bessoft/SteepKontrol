#ifndef FaGeriSayim_h
#define FaGeriSayim_h

class FaGeriSayim {
  public:
    void Basla();
    void Durdur();
    unsigned long GetKalanZaman();
    void SetToplamZaman(unsigned long);

  private:
    unsigned long durmaZamani=0; //micros
    unsigned long baslamaZamani=0; //micros
    unsigned long kalanZaman=0; //
    unsigned long toplamZaman=0; //
    unsigned long gecenZaman=0; //
    
    
    
 
 };

#endif

