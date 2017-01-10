#ifndef FaDecimalView_h
#define FaDecimalView_h

class FaDecimalView {
  public:

    String ToString();
    void SetValue(int);
    void SetMicros(unsigned long);
    
    int GetValue();
    void UpDownDigit(int,int);

    String Sparator=".";
    bool SaatModu=false;

    int GetTamKisim();
    int GetOndalikKisim();

    int GetToplamSaniye();
    void SaniyeDus();


  private:
    volatile int Value=0;
    volatile int TamKisim=0;
    volatile int OndalikKisim=0;
    String stringDeger="00"+Sparator+"00";
    
    int birler = 0;
    int onlar = 0;
    int yuzler = 0;
    int binler = 0;
    int ToplamSaniye;

    
    
 };

#endif

