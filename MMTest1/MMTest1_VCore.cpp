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

#include "MMExt2_Client.hpp"

#include "MMTest1_Cores.hpp"
#include "ParseFunctions.h"
#include <stdio.h>
#include <math.h>

MMTest1_VCore::MMTest1_VCore(VESSEL *vin, MMTest1_GCore* gcin) {
	GC = gcin;
	v = vin;

  mm.Init("MMTest1");
  mma.Init("MMTest1");
  
  TestIntL = 111;
	TestDblL = 111.111;
	TestVecL = _V(1.1,1.1,1.1);
  strcpy(TargetText, "Target text");

	sc = new MMTest_Common;
	sc->name = "TEST NAME X1";
	strncpy(exps.safeName, sc->name.c_str(), 32);

	ModMsgPut("I", TestIntL, v);
	ModMsgPut("D", TestDblL, v);
	ModMsgPut("V", TestVecL, v);
	ModMsgPutByRef("SafePtr_V1", 13, exps, v);

  ModMsgPut("STR", TargetText, v);

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
