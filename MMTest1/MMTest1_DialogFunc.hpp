// ==============================================================
//
//	Bare Bones Auto Pilot (MMTest1)
//	============================
//
//	Copyright (C) 2014	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See MMTest1.cpp
//
// ==============================================================


#ifndef __MMTest1_DIALOGFunc
#define __MMTest1_DIALOGFunc

class MMTest1_DialogFunc
{
    public:
      static bool clbkSIL(void *id, char *str, void *usrdata);
      static bool clbkSDL(void *id, char *str, void *usrdata);
      static bool clbkSVL(void *id, char *str, void *usrdata);
      static bool clbkSSN(void *id, char *str, void *usrdata);
    protected:
    private:

};

#endif // MMTest1_DIALOGFunc