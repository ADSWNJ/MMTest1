// ==============================================================
//
//	MMTest1 (Button Handling Code)
//	============================
//
//	Copyright (C) 2013	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See MMTest1.cpp
//
// ==============================================================

#include "MMTest1.hpp"
#include "MMTest1_DialogFunc.hpp"
#include <EnjoLib/ModuleMessagingExt.hpp>

// ==============================================================
// MFD button hooks to Button Page library
//
char* MMTest1::ButtonLabel (int bt)
{
	return LC->B.ButtonLabel(bt);
}

// Return button menus
int MMTest1::ButtonMenu (const MFDBUTTONMENU **menu) const
{
	return LC->B.ButtonMenu(menu);
}

// Return clicked button
bool MMTest1::ConsumeButton (int bt, int event) {
  return LC->B.ConsumeButton(this, bt, event);
}

// Return pressed keystroke
bool MMTest1::ConsumeKeyBuffered (DWORD key) {
  return LC->B.ConsumeKeyBuffered(this, key);
}



// ==============================================================
// MFD Button Handler Callbacks
//


// SIL = Set Integer Local
void MMTest1::Button_SIL() {
  sprintf_s(VC->TargetText,128,"%d",VC->TestIntL);
  oapiOpenInputBox( "Enter Test Int",MMTest1_DialogFunc::clbkSIL, VC->TargetText, 30, LC);
  return;
};

// SDL = Set Double Local
void MMTest1::Button_SDL() {
  sprintf_s(VC->TargetText,128,"%.3f",VC->TestDblL);
  oapiOpenInputBox( "Enter Test Dbl",MMTest1_DialogFunc::clbkSDL, VC->TargetText, 30, LC);
  return;
};

// SIL = Set Vector Local
void MMTest1::Button_SVL() {
	sprintf_s(VC->TargetText,128,"%.3f %.3f %.3f",VC->TestVecL.x,VC->TestVecL.y,VC->TestVecL.z);
	oapiOpenInputBox( "Enter Test Vec",MMTest1_DialogFunc::clbkSVL, VC->TargetText, 80, LC);
  return;
};


// GIR = Get Integer Remote
void MMTest1::Button_GIR() {
	int i;
	if (EnjoLib::ModuleMessagingExt().ModMsgGet("MMTest2","I", &i, VC->v)) {
		VC->TestIntR = i;
		VC->goodVar[0] = 1;
	} else {
		VC->TestIntR = 0;
		VC->goodVar[0] = -1;
	}
	return;
};

// GDR = Get Double Remote
void MMTest1::Button_GDR() {
	double d;
	if (EnjoLib::ModuleMessagingExt().ModMsgGet("MMTest2","D", &d, VC->v)) {
		VC->TestDblR = d;
		VC->goodVar[1] = 1;
	} else {
		VC->TestDblR = 0.0;
		VC->goodVar[1] = -1;
	}
  return;
};

// GVR = Get Vector Remote
void MMTest1::Button_GVR() {
	VECTOR3 vec;
	if (EnjoLib::ModuleMessagingExt().ModMsgGet("MMTest2","V", &vec, VC->v)) {
		VC->TestVecR = vec;
		VC->goodVar[2] = 1;
	} else {
		VC->TestVecR = _V(0.0,0.0,0.0);
		VC->goodVar[2] = -1;
	}
  return;
};


// SSN = Set Struct Name
void MMTest1::Button_SSN() {
	sprintf_s(VC->TargetText,128,"%s",VC->sc->name.c_str());
	oapiOpenInputBox( "Enter Struct Name",MMTest1_DialogFunc::clbkSSN, VC->TargetText, 32, LC);
  return;
};

