// ==============================================================
//
//	MMTest1 (MFD Button Management)
//	============================
//
//	Copyright (C) 2013	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See MMTest1.cpp
//
// ==============================================================

#include "MFDButtonPage.hpp"
#include "MMTest1_Buttons.hpp"
#include "MMTest1.hpp"


MMTest1_Buttons::MMTest1_Buttons() 
{
    // The menu descriptions of all buttons
    static const MFDBUTTONMENU mnu0[] =
    {
      {"Set Int", 0, 'I'},
      {"Set Double", 0, 'D'},
      {"Set Vec", 0, 'V'},
      {"Get Int", 0, '1'},
      {"Get Double", 0, '2'},
      {"Get Vec", 0, '3'},
      {"Set Str Name", 0, 'S'}
    };

    RegisterPage(mnu0, sizeof(mnu0) / sizeof(MFDBUTTONMENU));

    RegisterFunction("SIL", OAPI_KEY_I, &MMTest1::Button_SIL);
    RegisterFunction("SDL", OAPI_KEY_D, &MMTest1::Button_SDL);
    RegisterFunction("SVL", OAPI_KEY_V, &MMTest1::Button_SVL);
    RegisterFunction("GIR", OAPI_KEY_1, &MMTest1::Button_GIR);
    RegisterFunction("GDR", OAPI_KEY_2, &MMTest1::Button_GDR);
    RegisterFunction("GVR", OAPI_KEY_3, &MMTest1::Button_GVR);
    RegisterFunction("SSN", OAPI_KEY_3, &MMTest1::Button_SSN);

    return;
}

bool MMTest1_Buttons::SearchForKeysInOtherPages() const
{
    return false;
}



