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


#ifndef __MMTest1_H
#define __MMTest1_H

#include "MMTest1_Cores.hpp"   

class MMTest1: public MFD2
{
public:
	MMTest1 (DWORD w, DWORD h, VESSEL *vessel, UINT mfd);
	~MMTest1 ();
	
  char *ButtonLabel (int bt);
	int ButtonMenu (const MFDBUTTONMENU **menu) const;
  bool ConsumeKeyBuffered (DWORD key);
  bool ConsumeButton (int bt, int event);
  
  bool Update (oapi::Sketchpad *skp);
  static int MsgProc (UINT msg, UINT mfd, WPARAM wparam, LPARAM lparam);

  // Button Press Handlers
  void Button_SIL();
  void Button_SDL();
  void Button_SVL();
  void Button_GIR();
  void Button_GDR();
  void Button_GVR();
  void Button_SSN();

  const char* GetModuleName() const;

  // Persistence functions
  void ReadStatus(FILEHANDLE scn);
  void WriteStatus(FILEHANDLE scn) const;

  // Unit conversions
  double id( double d ) const;
  double ed( double d ) const;

protected:
  MMTest1_GCore* GC;
  MMTest1_LCore* LC;
  MMTest1_VCore* VC;

  int Line( int row );
  int Col( int pos );
  int Col2( int pos );
  void ShowMessage(oapi::Sketchpad *skp);

  oapi::Font *font;


};

#endif // !__MMTest1_H