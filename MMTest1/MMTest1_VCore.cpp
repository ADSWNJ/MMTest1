// ==============================================================
//
//	MMTest1 (Vessel Core Persistence)
//	==============================
//
//	Copyright (C) 2013	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See MMTest1.cpp
//
// ==============================================================

#include "MMTest1_Cores.hpp"
#include "ParseFunctions.h"
#include <stdio.h>
#include <math.h>

MMTest1_VCore::MMTest1_VCore(VESSEL *vin, MMTest1_GCore* gcin) : mm("MMTest1"), mma("MMTest1") {
	GC = gcin;
	v = vin;
  
  TestIntL = 111;
	TestDblL = 111.111;
	TestVecL = _V(1.1,1.1,1.1);
  strcpy(TargetText, "Target text");

	sc = new MMTest_Common;
	sc->name = "TEST NAME X1";

	mm.Put("I", TestIntL);
	mm.Put("D", TestDblL);
	mm.Put("V", TestVecL);
  mm.Put("STR", TargetText);
  mm.Put("STRL", "Literal");

	TestIntR = 0;
	TestDblR = 0;
	TestVecR = _V(0,0,0);

	goodVar[0] = 0;
	goodVar[1] = 0;
	goodVar[2] = 0;


	return;
};

MMTest1_VCore::~MMTest1_VCore() {
}
