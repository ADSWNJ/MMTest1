// ================================================================================================
//
//	MM Test 1
//	==========
//
//	Copyright (C) 2014-2016	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	Description:
//
//	Test MFD to showcase MFD Button Page (simple control of buttons), MFD Persist (simple persistence hierarchy), and MMExt2 (data tranfer between MFD's)
//
//	Copyright Notice:
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	For full licencing terms, pleaserefer to the GNU General Public License
//	(gpl-3_0.txt) distributed with this release, or see
//	http://www.gnu.org/licenses/.
//
//
//	Credits:
//	
//	Orbiter Simulator	(c) 2003-2016 Martin (Martins) Schweiger
// 	MFDButtonPage		(c) 2012-2016 Szymon (Enjo) Ender
// 	original ModuleMessaging (c) 2014-2016 Szymon (Enjo) Ender
//	
//
//	Release History:
//
//  V3.00 Updated to use MMExt2 dynamically (no more error 126 on launch!!)
//	V2.00	Updated to use ModuleMessagingExt
//  V1.00	Initial Release
// ================================================================================================

#define STRICT
#define ORBITER_MODULE

#include "windows.h"
#include "orbitersdk.h"
#include "MMTest1.hpp"
#include "MMTest1_Cores.hpp"
#include "MMTest1_DialogFunc.hpp"
#include "MFDPersist.hpp"


// =======================================================================
// Global variables

MMTest1_GCore *g_SC;    // points to the static core, root of all persistence
int g_MFDmode;			// holds the mode identifier for our MFD


// =======================================================================
// API interface

DLLCLBK void InitModule (HINSTANCE hDLL)
{
	static char *name = "MMTest1";
	MFDMODESPECEX spec;
	spec.name = name;
	spec.key = OAPI_KEY_T;
	spec.context = NULL;
	spec.msgproc = MMTest1::MsgProc;
	g_MFDmode = oapiRegisterMFDMode (spec);
}

DLLCLBK void ExitModule (HINSTANCE hDLL)
{
	oapiUnregisterMFDMode (g_MFDmode);
}

DLLCLBK void opcPreStep(double SimT,double SimDT,double mjd) {
  double thisSimT = oapiGetSimTime();

  if (!g_SC) return;		// Static core not yet initialized
  // g_SC->PreStep();		// Put any global pre-step work here
  // g_SC->VC->Update();    // Put any vessel pre-step work here...
  // g_SC->VC->Update();    // Put any local vessel+MFD pre-step in here...
}

// ==============================================================
// MFD class implementation
//
// ... derive also from EnjoLib::IDrawsHUD to hook to the HUD drawer interface


// Constructor
MMTest1::MMTest1 (DWORD w, DWORD h, VESSEL *vessel, UINT mfd)
: MFD2 (w, h, vessel)
{
  if (!g_SC) {										// Find the static global core 
    g_SC = new MMTest1_GCore;						//  ... if missing, then init the static core (only done once for this addon per run of Orbiter)
  }
  GC = g_SC;

  VC = (MMTest1_VCore*) GC->P.FindVC(vessel);		// Find the vessel core for our vessel
  if (!VC) {
    VC = new MMTest1_VCore(vessel,GC);				// ... if missing, then init the vessel core for our vessel (once for this vessel)
    GC->P.AddVC(vessel, VC);
  }

  LC = (MMTest1_LCore*) GC->P.FindLC(vessel, mfd);	// Find the local core doe this vessel + mfd combination
  if (!LC) {
    LC = new MMTest1_LCore(vessel,mfd,GC);			// ... if missing, init the local core once per vessel + mfd position
    GC->P.AddLC(vessel, mfd, LC);
  }

  //
  // Set up core components for this MFD instance
  //

  font = oapiCreateFont (h/25, true, "Fixed", FONT_NORMAL, 0);

}

// ===========================================================================
// Destructor (called any time our MFD goes out of scope ... e.g. on F8 press)
MMTest1::~MMTest1 ()
{
  return;
}


// ==============================================================
// MFD message parser
int MMTest1::MsgProc (UINT msg, UINT mfd, WPARAM wparam, LPARAM lparam)
{
	switch (msg) {
	case OAPI_MSG_MFD_OPENED:
		// Our new MFD mode has been selected, so we create the MFD and
		// return a pointer to it.
		return (int)(new MMTest1 (LOWORD(wparam), HIWORD(wparam), (VESSEL*)lparam, mfd));
	}
	return 0;
}



// ==============================================================
// Persistence functions
void MMTest1::ReadStatus(FILEHANDLE scn) {
  return;
}

void MMTest1::WriteStatus(FILEHANDLE scn) const {
  return;
}



