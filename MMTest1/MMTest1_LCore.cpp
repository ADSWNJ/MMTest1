// ==========================================================================
//
//	MMTest1 (Local (Vessel+MFD Panel) Core Persistence)
//	================================================
//
//	Copyright (C) 2013	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See MMTest1.cpp
//
// ==========================================================================

#include "MMTest1_Cores.hpp"

MMTest1_LCore::MMTest1_LCore(VESSEL *vin, UINT mfdin, MMTest1_GCore* gcin) {
  GC = gcin;
  v = vin;
  m = mfdin;

  VC = (MMTest1_VCore*) GC->P.FindVC(v);

  showMessage = false;
  okMessagePage = true;
  return;
}
