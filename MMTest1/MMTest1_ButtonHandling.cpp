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
  bool ret;
  int i;
  bool b;
  double d;
  VECTOR3 v, v_ref;
  MATRIX3 m3 = _M(1, 2, 3, 4, 5, 6, 7, 8, 9);
  MATRIX4 m4 = _M(1, 2, 3, 4, 5, 6, 7, 8, 9,10,11, 12, 13, 14, 15, 16);

  string s = "ABCDE";

  v_ref = _V(9.9, 8.8, 7.7);
  v = v_ref;

#pragma pack(push)
#pragma pack(8)
  struct MyStruct : public MMExt2::MMStruct {
    MyStruct() : MMExt2::MMStruct(1, sizeof(MyStruct)) {};
    char MyMsg[20];
  };
#pragma pack(pop)


  MyStruct ss1;
  strcpy(ss1.MyMsg, "Hello world!");
  const MyStruct* ssRet;


  ret = VC->mma.PutMMStruct("SS1", &ss1);
  ret = VC->mma.GetMMStruct("SS1", &ssRet, 1, sizeof(MyStruct));

  strcpy(ss1.MyMsg, "Changed??");

  ret = VC->mm.Put("I", 37);
  ret = VC->mm.Put("B", true);
  ret = VC->mm.Put("D", 37.3737);
  ret = VC->mm.Put("V", v_ref);
  ret = VC->mm.Put("S", "12345");
  ret = VC->mm.Put("S", s);
  ret = VC->mm.Put("M3", m3);
  ret = VC->mm.Put("M4", m4);


  ret = VC->mm.Get("I", &i);
  ret = VC->mm.Get("B", &b);
  ret = VC->mm.Get("D", &d);
  ret = VC->mm.Get("V", &v);
  ret = VC->mm.Get("S", &s);
  ret = VC->mm.Get("M3", &m3);
  ret = VC->mm.Get("M4", &m4);


  i = 0;
  b = true;
  d = 1.1;
  v = _V(1, 2, 3);
  ret = VC->mma.Put("I", i);
  ret = VC->mma.Put("I", 95);
  ret = VC->mma.Get("I", &i);
  ret = VC->mma.Delete("I");
  ret = VC->mma.Get("I", &i);

  ret = VC->mma.Put("B", b);
  ret = VC->mma.Put("B", false);
  ret = VC->mma.Get("B", &b);
  ret = VC->mma.Delete("B");
  ret = VC->mma.Get("B", &b);

  ret = VC->mma.Put("D", d);
  ret = VC->mma.Put("D", 987.6);
  ret = VC->mma.Get("D", &d);
  ret = VC->mma.Delete("D");
  ret = VC->mma.Get("D", &d);

  ret = VC->mma.Put("V", v);
  ret = VC->mma.Put("V", _V(9, 8, 7));
  ret = VC->mma.Get("V", &v);
  ret = VC->mma.Delete("V");
  ret = VC->mma.Get("V", &v);

  ret = VC->mma.Put("S", s);
  ret = VC->mma.Put("S", "Hello");
  ret = VC->mma.Get("S", &s);
  ret = VC->mma.Delete("S");
  ret = VC->mma.Get("S", &s);

  ret = VC->mma.Put("M3", m3);
  ret = VC->mma.Put("M3", _M(1, 1, 1, 1, 1, 1, 1, 1, 1));
  ret = VC->mma.Get("M3", &m3);
  ret = VC->mma.Delete("M3");
  ret = VC->mma.Get("M3", &m3);

  ret = VC->mma.Put("M4", m4);
  ret = VC->mma.Put("M4", _M(8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8));
  ret = VC->mma.Get("M4", &m4);
  ret = VC->mma.Delete("M4");
  ret = VC->mma.Get("M4", &m4);


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




// GPA = Test Get Proc Address
void MMTest1::Button_GPA() {

  HMODULE hMMT2 = GetModuleHandleA(".\\Modules\\Plugin\\MMTest2.dll");
  if (hMMT2 == nullptr) return;

  FARPROC hMGE = GetProcAddress(hMMT2, "MyGlobalEntry");

  typedef bool(*RMTCALL)();

  RMTCALL rc = (RMTCALL)(hMGE);

  (*rc)();

  return;


};
