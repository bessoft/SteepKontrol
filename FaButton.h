#ifndef FaButton_h
#define FaButton_h

#include <inttypes.h>


class FaButton
{
  private:
    int JoistikOku(int, int, int);
  public:
    int JoyX = 0;
    int JoyY = 0;
};

//extern FaButtonClass FaButton;

#endif

