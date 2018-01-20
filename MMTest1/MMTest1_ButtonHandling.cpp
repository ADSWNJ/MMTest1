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

inline MATRIX4 _M4(double m11, double m12, double m13, double m14,
  double m21, double m22, double m23, double m24,
  double m31, double m32, double m33, double m34, 
  double m41, double m42, double m43, double m44 )
{
  MATRIX4 mat = { m11,m12,m13,m14,  m21,m22,m23,m24,  m31,m32,m33,m34,  m41,m41,m43,m44 };
  return mat;
}

// GIR = Get Integer Remote
void MMTest1::Button_GIR() {
  int i;

	if (VC->mm.Get("MMTest2","I", &i)) {
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
	if (VC->mm.Get("MMTest2","D", &d)) {
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
	if (VC->mma.Get("MMTest2","V", &vec, VC->v)) {
		VC->TestVecR = vec;
		VC->goodVar[2] = 1;
	} else {
		VC->TestVecR = _V(0.0,0.0,0.0);
		VC->goodVar[2] = -1;
	}
  return;
};

// TST = Test Data Types
void MMTest1::Button_TST() {
  bool ret;
  int i;

  VECTOR3 v, v_ref;
  MATRIX3 m3 = _M(1, 2, 3, 4, 5, 6, 7, 8, 9);
  MATRIX4 m4 = _M4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

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

  ret = VC->mm.Put("S", "1");
  ret = VC->mm.Get("MMTest1", "S", &s);
  ret = VC->mma.Put("S", "123");
  ret = VC->mma.Get("MMTest1", "S", &s);
  ret = VC->mm.Put("S", "1234");
  ret = VC->mm.Get("MMTest1", "S", &s);
  ret = VC->mma.Put("S", "12345");
  ret = VC->mma.Get("MMTest1", "S", &s);
  ret = VC->mm.Put("S", "1234567890");
  ret = VC->mm.Get("MMTest1", "S", &s);

  OBJHANDLE oh = oapiGetVesselByName("ISS");
  OBJHANDLE roh;
  int ot;
  string iss_nickname = "$100B_Lab";

  ret = VC->mma.Put(iss_nickname, oh);
  ret = VC->mma.Get("MMTest1", iss_nickname, &roh);
  ot = VC->mma.ObjType(roh);

  oh = oapiGetGbodyByName("Sun");
  ret = VC->mma.Put("Warm'n'Shiny", oh);
  ret = VC->mma.Get("MMTest1", "Warm'n'Shiny", &roh);
  ot = VC->mma.ObjType(roh);

  oh = oapiGetGbodyByName("Earth");
  ret = VC->mma.Put("Marble", oh);
  ret = VC->mma.Get("MMTest1", "Marble", &roh);
  ot = VC->mma.ObjType(roh);

  oh = oapiGetGbodyByName("Moon");
  ret = VC->mma.Put("Cheese", oh);
  ret = VC->mma.Get("MMTest1", "Cheese", &roh);
  ot = VC->mma.ObjType(roh);

  oh = oapiGetBaseByName(roh, "Brighton Beach");
  ret = VC->mma.Put("RockyBeach", oh);
  ret = VC->mma.Get("MMTest1", "RockyBeach", &roh);
  ot = VC->mma.ObjType(roh);


  ot = VC->mm.ObjType((OBJHANDLE)((unsigned long)roh + 1));
  ot = VC->mm.ObjType(0);


  char TextVes[32];
  sprintf(TextVes, "%p", oh);

  sscanf(TextVes, "%p", &roh);



  MyStruct ss1;
  strcpy(ss1.MyMsg, "Hello world!");
  const MyStruct* ssRet;


  ret = VC->mma.PutMMStruct("SS1", &ss1);
  ret = VC->mma.GetMMStruct("MMTest1", "SS1", &ssRet, 1, sizeof(MyStruct));


  bool b;
  double d;
  strcpy(ss1.MyMsg, "Changed??");

  ret = VC->mm.Put("I", 37);
  ret = VC->mm.Put("B", true);
  ret = VC->mm.Put("D", 37.3737);
  ret = VC->mm.Put("V", v_ref);
  ret = VC->mm.Put("S", "12345");
  ret = VC->mm.Put("S", s);
  ret = VC->mm.Put("M3", m3);
  ret = VC->mm.Put("M4", m4);


  ret = VC->mm.Get("MMTest1", "I", &i);
  ret = VC->mm.Get("MMTest1", "B", &b);
  ret = VC->mm.Get("MMTest1", "D", &d);
  ret = VC->mm.Get("MMTest1", "V", &v);
  ret = VC->mm.Get("MMTest1", "S", &s);
  ret = VC->mm.Get("MMTest1", "M3", &m3);
  ret = VC->mm.Get("MMTest1", "M4", &m4);

  int ix = 0;
  string mod;
  string var;
  OBJHANDLE ovh;
  char typ;
  string lookup;
  bool skipSelf = false;
  char *vesName;
  while (VC->mma.Find(&typ, &mod, &var, &ovh, &ix, "*", "*", NULL, skipSelf)) {
    vesName = oapiGetVesselInterface(ovh)->GetName();
    lookup = string() + "Vessel: " + vesName + "  Module: " + mod + "  Var: " + var + "  Type: " + typ;
  }

  ix = 0;
  string rcli, rmod, rvar, rves, act;
  char rfunc;
  bool rsucc;
  while (VC->mma.GetLog(&rfunc, &rcli, &rmod, &rvar, &rves, &rsucc, &ix, false)) {
    act = rcli + " " + rfunc + " " + rves + ":" + rmod + ":" + rvar + "=" + (rsucc ? "S" : "F");
  }
  i = 0;
  b = true;
  d = 1.1;
  v = _V(1, 2, 3);
  ret = VC->mma.Put("I", i);
  ret = VC->mma.Put("I", 95);
  ret = VC->mma.Get("MMTest1", "I", &i);
  ret = VC->mma.Delete("I");
  ret = VC->mma.Get("MMTest1", "I", &i);

  ret = VC->mma.Put("B", b);
  ret = VC->mma.Put("B", false);
  ret = VC->mma.Get("MMTest1", "B", &b);
  ret = VC->mma.Delete("B");
  ret = VC->mma.Get("MMTest1", "B", &b);

  ret = VC->mma.Put("D", d);
  ret = VC->mma.Put("D", 987.6);
  ret = VC->mma.Get("MMTest1", "D", &d);
  ret = VC->mma.Delete("D");
  ret = VC->mma.Get("MMTest1", "D", &d);

  ret = VC->mma.Put("V", v);
  ret = VC->mma.Put("V", _V(9, 8, 7));
  ret = VC->mma.Get("MMTest1", "V", &v);
  ret = VC->mma.Delete("V");
  ret = VC->mma.Get("MMTest1", "V", &v);

  ret = VC->mma.Put("S", s);
  ret = VC->mma.Put("S", "Hello");
  ret = VC->mma.Get("MMTest1", "S", &s);
  ret = VC->mma.Delete("S");
  ret = VC->mma.Get("MMTest1", "S", &s);

  ret = VC->mma.Put("M3", m3);
  ret = VC->mma.Put("M3", _M(1, 1, 1, 1, 1, 1, 1, 1, 1));
  ret = VC->mma.Get("MMTest1", "M3", &m3);
  ret = VC->mma.Delete("M3");
  ret = VC->mma.Get("MMTest1", "M3", &m3);

  ret = VC->mma.Put("M4", m4);
  ret = VC->mma.Put("M4", _M4(8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8));
  ret = VC->mma.Get("MMTest1", "M4", &m4);
  ret = VC->mma.Delete("M4");
  ret = VC->mma.Get("MMTest1", "M4", &m4);

  return;
};


// SSN = Set Struct Name
void MMTest1::Button_SSN() {
	sprintf_s(VC->TargetText,128,"%s",VC->sc->name.c_str());
	oapiOpenInputBox( "Enter Struct Name",MMTest1_DialogFunc::clbkSSN, VC->TargetText, 32, LC);
  return;
};


