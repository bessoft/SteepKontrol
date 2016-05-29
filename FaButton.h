#ifndef FaButton_h
#define FaButton_h

#include <inttypes.h>


class FaButton
{

  private:
    unsigned long Bekle2 = 0;
    int GetButton(int, int);
    int JoistikOku(int, int, int);
    
    

  public:
    int GenelButton = 0;

    int JoyX = 0;
    int JoyY = 0;
    int JoyKey = 0;
    
    int ButtonSakla = 0;


    
    void BeklemeliButonOku(unsigned long);

};

//extern FaButtonClass FaButton;

#endif

