#ifndef FaDecimalView_h
#define FaDecimalView_h

class FaDecimalView {
  public:

    String ToString();
    void SetValue(float);
    void UpDownDigit(int,int);

  private:
    volatile float Value=0;
    
 };

#endif

