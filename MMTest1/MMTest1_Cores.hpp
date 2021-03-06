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

#include "windows.h"
#include "orbitersdk.h"
#include "MMTest1_Buttons.hpp"
#include "MFDPersist.hpp"
#include <list>
#include <string>
#include <new>
#include "MMExt2_Basic.hpp"
#include "MMExt2_Advanced.hpp"
using namespace std;

#ifndef _MMTest1_CORE_CLASSES
#define _MMTest1_CORE_CLASSES

// Forward reference needed, as the cores all talk to each other. (This is also why the cores are kept together in this single hpp file)
class MMTest1_GCore;

class MMTest_Common {
public:

	std::string name;

};


//+++++
// Vessel Persistence core. One of these is instantiated per Vessel flown with RV Orientation up.
//+++++

class MMTest1_VCore {
  public:
    // Core references ... instantiation, vessel reference and GC.
    MMTest1_VCore(VESSEL *vin, MMTest1_GCore* gcin);
    ~MMTest1_VCore();
    MMTest1_GCore* GC;

    MMExt2::Basic mm;
    MMExt2::Advanced mma;

		// Add Vessel data here
    VESSEL *v;

	char TargetText[128];
	int TestIntL, TestIntR;
	double TestDblL, TestDblR;
	VECTOR3 TestVecL, TestVecR;
	int goodVar[3];

	struct INTERESTING_STRUCT {
		char name[32];
		int blah;
		double dd;
	} s;

	MMTest_Common *sc;

  private:
};


//+++++
// Local Persistence core. One of these is instantiated per Vessel AND MFD panel location. Local defaults for that combination.
//+++++

class MMTest1_LCore {
  public:
    // Local references ... instantiation, references for vesseland mfd position, and links to the appropriate VC, MC and GC
    MMTest1_LCore(VESSEL *vin, UINT mfdin, MMTest1_GCore* gcin);
    VESSEL *v;
    UINT m;
    MMTest1_GCore* GC;
    MMTest1_VCore* VC;

    // Add local vessel+panel data here

    MMTest1_Buttons B;
    bool showMessage;
    bool okMessagePage;
    string Message;
};

//+++++
// Global Persistence core. One of these is instantiated for the whole orbiter session, on the first launch of this MFD type
//+++++

class MMTest1_GCore {
  public:
    // Global references ... instantiation and a link to the persistence library (running the linked lists)
    MMTest1_GCore();
    MFDPersist P;

};


#endif // _MMTest1_CORE_CLASSES