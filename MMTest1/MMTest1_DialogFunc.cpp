// ==============================================================
//
//	MMTest1 (Dialog Function Handlers)
//	===============================
//
//	Copyright (C) 2013	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See MMTest1.cpp
//
// ==============================================================

#include "MMTest1_DialogFunc.hpp"
#include "MMTest1_Cores.hpp"

bool MMTest1_DialogFunc::clbkSIL(void *id, char *str, void *usrdata) {
  int parami; 

  if (strlen(str) == 0) return true;      // Empty string - assume canceled dialog
  if (sscanf_s(str,"%d",&parami) != 1) return true; // 0 or 2+ values found - ignore
  
  MMTest1_LCore* LC = (MMTest1_LCore*) usrdata;
  MMTest1_VCore* VC = LC->VC;

  VC->TestIntL = parami;
	VC->mm.Put("I",VC->TestIntL);
  return true;
}

bool MMTest1_DialogFunc::clbkSDL(void *id, char *str, void *usrdata) {
  float paramf; 

  if (strlen(str) == 0) return true;      // Empty string - assume canceled dialog
  if (sscanf_s(str,"%f",&paramf) != 1) return true; // No double value found - ignore
  
  MMTest1_LCore* LC = (MMTest1_LCore*) usrdata;
  MMTest1_VCore* VC = LC->VC;

  VC->TestDblL = paramf;
	VC->mm.Put("D",VC->TestDblL);
  return true;
}

bool MMTest1_DialogFunc::clbkSVL(void *id, char *str, void *usrdata) {
  float paramf1, paramf2, paramf3; 

  if (strlen(str) == 0) return true;      // Empty string - assume canceled dialog
  if (sscanf_s(str,"%f %f %f",&paramf1,&paramf2,&paramf3) != 3) return true; // No 3x doubles found - ignore
  
  MMTest1_LCore* LC = (MMTest1_LCore*) usrdata;
  MMTest1_VCore* VC = LC->VC;

  VC->TestVecL = _V(paramf1,paramf2,paramf3);
	VC->mm.Put("V",VC->TestVecL);
  return true;
}

bool MMTest1_DialogFunc::clbkSSN(void *id, char *str, void *usrdata) {
  
	MMTest1_LCore* LC = (MMTest1_LCore*) usrdata;
	MMTest1_VCore* VC = LC->VC;

	VC->sc->name = str;
  strcpy_s(VC->TargetText, 32, str);
  VC->mm.Put("STR", VC->TargetText);
	return true;
}