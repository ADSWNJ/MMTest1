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



#ifndef _MMTest1_BUTTON_CLASS
#define _MMTest1_BUTTON_CLASS
#include "MFDButtonPage.hpp"

class MMTest1;

class MMTest1_Buttons : public MFDButtonPage<MMTest1>
{
  public:
    MMTest1_Buttons();
  protected:
    bool SearchForKeysInOtherPages() const;
  private:
};
#endif // _MMTest1_BUTTON_CLASS

