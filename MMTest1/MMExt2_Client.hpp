// ====================================================================
//                ORBITER AUX LIBRARY: ModuleMessagingExt v2 (MMExt2)
//             http://sf.net/projects/enjomitchsorbit
//
// Allows Orbiter modules to communicate with each other,
// using predefined module and variable names.
//
// Copyright  (C) 2014-2017 Szymon "Enjo" Ender and Andrew "ADSWNJ" Stokes
//
//                         All rights reserved
//
// ModuleMessagingExt v2 is free software: you can redistribute it
// and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either version
// 3 of the License, or (at your option) any later version.
//
// ModuleMessagingExt v2 is distributed in the hope that it will
// be useful, but WITHOUT ANY WARRANTY; without even the implied
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with ModuleMessagingExt. If not, see
// <http://www.gnu.org/licenses/>.
// ====================================================================

#pragma once
#ifndef MMExt2_Client_H
#define MMExt2_Client_H
#include "windows.h"
#include "orbitersdk.h"
#include <string>

namespace ModuleMessagingExt
{
  /*
  Purpose:

  Gets data from other MFD's using the common ModuleMessagingExt library. Data can be passed by value
  or by reference. For pass by reference, the ModuleMessagingExt library implements several further
  checks to ensure safety and to deal with potential version or definition mismatches.

  Developer Instructions:

  1. #include "EnjoLib/ModuleMessagingExt.hpp" where you need to get data from ModuleMessagingExt.

  2. For get by value ... call EnjoLib::ModuleMessagingExt().Get(MFDname, varName, &value, {vessel}),
  where:	MFDname is a string literal for the sending MFD or module (e.g. "BaseSyncMFD"),
  varName is a string literal for the variable you are looking for
  &value is the address of where you want the value to be received, and is one of the following
  types: bool, int, double, VECTOR3, MATRIX3, and MATRIX4.
  vessel is VESSEL* pointer to the vessel you want to get data from (defaults to your vessel).

  The return is a bool indicating success or failure. If successful, the value will have the new data.

  3. For get by reference (meaning you are addressing memory directly in the other DLL), the author
  of the module PUTting the data will give you a header file with a data structure like this:

  #pragma pack(push)
  #pragma pack(8)
  struct XYZ : public EnjoLib::ModuleMessagingExtBase {
  XYZ():EnjoLib::ModuleMessagingExtBase(13,sizeof(XYZ)) {};  // version 13
  ...
  ... your data structures (don't use STL's like std::string
  ... or std::map, etc as these tend not to be byte-compatible
  ... across compiler versions)
  ...
  };
  #pragma pack(pop)

  (Obviously with their structure name instead of XYZ). Include this header into your code to give you
  the latest definition of the structure and version you are accessing. Make a note of the version number
  on the ModuleMessagingExtBase constructor (i.e. 13 in this case), as you need it for your ModMsgGetByRef()
  call.

  In your code, define a pointer to a constant XYZ structure (replace XYZ, of course), such as:

  constant struct xyz *remoteData;

  This tells the compiler that you guarantee not to write data via the pointer. (If you wanted to do this,
  and the other module author wanted to cooperate, then have both sides ModMsgGetByRef the other side
  and write local / read remote.)

  Then, call EnjoLib::ModuleMessagingExt().ModMsgGetByRef(MFDname, structName, structVer, &structPtr,
  {vessel}), where the structName and structVer are given to you by the author of the PUTting module,
  and the other parameters are the same as the ModMsgGet(). In addition to looking up the data and returning
  it if found, the library will do additional checks to ensure the structure has a valid
  inheritance from the ModuleMessagigngBaseStruct, the structure version number is identical, and
  the structure size is also correct. (The PUT side should increment the version any time the structure
  is changed, which will prevent you accessing a wrong verion of the structure, and the sizeof()
  check is there as a further failsafe). So if you get a "true" back from ModMsgGetByRef(), you can be
  reasonably sure that everything is safe and you will not crash the Orbiter when you reference the data.

  4. To link your code, make sure your Linker, Input, AdditionalDependencies includes ModuleMessagingExt.lib.
  Have a look at http://orbiter-forum.com/showthread.php?t=34971 for advice on setting up Property Pages
  for Orbiter development (highly recommended, and it makes things much easier). If you do this, then
  you can edit the Linker Input Additional Directories in the orbiter_vs2005 proprty page and this will
  let you resolve any ModuleMessagigngExt for this and future projects.
  */
#define MM_FNC_TYPEDEF(__TY, __ty, __pt, __gt) __MMFNC_TYPEDEF(__TY, __ty, __pt, __gt)
#define __MMFNC_TYPEDEF(__TY, __ty, __pt, __gt) \
  typedef bool(*FUNC_MMEXT2_PUT_##__TY) (const char* moduleName, const char* varName, const __ty __pt value, const char* vesselName);\
  typedef bool(*FUNC_MMEXT2_GET_##__TY) (const char* moduleName, const char* varName, __ty __gt value, const char* vesselName)

  MM_FNC_TYPEDEF(INT, int, , *);
  MM_FNC_TYPEDEF(BOOL, bool, , *);
  MM_FNC_TYPEDEF(DBL, double, , *);
  MM_FNC_TYPEDEF(VEC, VECTOR3, &, *);
  MM_FNC_TYPEDEF(MX3, MATRIX3, &, *);
  MM_FNC_TYPEDEF(MX4, MATRIX4, &, *);

  typedef bool(*FUNC_MMEXT2_PUT_CST) (const char* moduleName, const char* varName, const char *value, const char* vesselName);
  typedef bool(*FUNC_MMEXT2_GET_CST) (const char* moduleName, const char* varName, char **value, const size_t maxValueLen, const char* vesselName);
  typedef bool(*FUNC_MMEXT2_DEL_ANY) (const char* moduleName, const char* varName, const char* vesselName);


  class Implementation {
  public:
    Implementation() {
      if (!(m_hDLL = LoadLibraryA(".\\Modules\\MMExt2.dll"))) return;
      m_fncPut_int = (FUNC_MMEXT2_PUT_INT)GetProcAddress(m_hDLL, "ModMsgPut_int_v1");
      m_fncGet_int = (FUNC_MMEXT2_GET_INT)GetProcAddress(m_hDLL, "ModMsgGet_int_v1");
      m_fncPut_bool = (FUNC_MMEXT2_PUT_BOOL)GetProcAddress(m_hDLL, "ModMsgPut_bool_v1");
      m_fncGet_bool = (FUNC_MMEXT2_GET_BOOL)GetProcAddress(m_hDLL, "ModMsgGet_bool_v1");
      m_fncPut_double = (FUNC_MMEXT2_PUT_DBL)GetProcAddress(m_hDLL, "ModMsgPut_double_v1");
      m_fncGet_double = (FUNC_MMEXT2_GET_DBL)GetProcAddress(m_hDLL, "ModMsgGet_double_v1");
      m_fncPut_VECTOR3 = (FUNC_MMEXT2_PUT_VEC)GetProcAddress(m_hDLL, "ModMsgPut_VECTOR3_v1");
      m_fncGet_VECTOR3 = (FUNC_MMEXT2_GET_VEC)GetProcAddress(m_hDLL, "ModMsgGet_VECTOR3_v1");
      m_fncPut_MATRIX3 = (FUNC_MMEXT2_PUT_MX3)GetProcAddress(m_hDLL, "ModMsgPut_MATRIX3_v1");
      m_fncGet_MATRIX3 = (FUNC_MMEXT2_GET_MX3)GetProcAddress(m_hDLL, "ModMsgGet_MATRIX3_v1");
      m_fncPut_MATRIX4 = (FUNC_MMEXT2_PUT_MX4)GetProcAddress(m_hDLL, "ModMsgPut_MATRIX4_v1");
      m_fncGet_MATRIX4 = (FUNC_MMEXT2_GET_MX4)GetProcAddress(m_hDLL, "ModMsgGet_MATRIX4_v1");
      m_fncPut_c_str = (FUNC_MMEXT2_PUT_CST)GetProcAddress(m_hDLL, "ModMsgPut_c_str_v1");
      m_fncGet_c_str = (FUNC_MMEXT2_GET_CST)GetProcAddress(m_hDLL, "ModMsgGet_c_str_v1");
      m_fncDel_any = (FUNC_MMEXT2_DEL_ANY)GetProcAddress(m_hDLL, "ModMsgDel_any_v1");
    };
    ~Implementation() {
      if (m_hDLL) FreeLibrary(m_hDLL);
      m_fncPut_int = NULL;
      m_fncGet_int = NULL;
    };
    bool Put(const char* moduleName, const char* varName, const int value, const VESSEL* myVessel = oapiGetFocusInterface()) const {
      return ((m_fncPut_int) && ((*m_fncPut_int)(moduleName, varName, value, myVessel->GetName())));
    };
    bool Get(const char* moduleName, const char* varName, int* value, const VESSEL* myVessel = oapiGetFocusInterface()) const {
      return ((m_fncGet_int) && ((*m_fncGet_int)(moduleName, varName, value, myVessel->GetName())));
    };
    
    bool Put(const char* moduleName, const char* varName, const bool value, const VESSEL* myVessel = oapiGetFocusInterface()) const {
      return ((m_fncPut_bool) && ((*m_fncPut_bool)(moduleName, varName, value, myVessel->GetName())));
    };
    bool Get(const char* moduleName, const char* varName, bool* value, const VESSEL* myVessel = oapiGetFocusInterface()) const {
      return ((m_fncGet_bool) && ((*m_fncGet_bool)(moduleName, varName, value, myVessel->GetName())));
    };

    bool Put(const char* moduleName, const char* varName, const double value, const VESSEL* myVessel = oapiGetFocusInterface()) const {
      return ((m_fncPut_double) && ((*m_fncPut_double)(moduleName, varName, value, myVessel->GetName())));
    };
    bool Get(const char* moduleName, const char* varName, double* value, const VESSEL* myVessel = oapiGetFocusInterface()) const {
      return ((m_fncGet_double) && ((*m_fncGet_double)(moduleName, varName, value, myVessel->GetName())));
    };

    bool Put(const char* moduleName, const char* varName, const VECTOR3 &value, const VESSEL* myVessel = oapiGetFocusInterface()) const {
      return ((m_fncPut_VECTOR3) && ((*m_fncPut_VECTOR3)(moduleName, varName, value, myVessel->GetName())));
    };
    bool Get(const char* moduleName, const char* varName, VECTOR3* value, const VESSEL* myVessel = oapiGetFocusInterface()) const {
      return ((m_fncGet_VECTOR3) && ((*m_fncGet_VECTOR3)(moduleName, varName, value, myVessel->GetName())));
    };

    bool Put(const char* moduleName, const char* varName, const MATRIX3 &value, const VESSEL* myVessel = oapiGetFocusInterface()) const {
      return ((m_fncPut_MATRIX3) && ((*m_fncPut_MATRIX3)(moduleName, varName, value, myVessel->GetName())));
    };
    bool Get(const char* moduleName, const char* varName, MATRIX3* value, const VESSEL* myVessel = oapiGetFocusInterface()) const {
      return ((m_fncGet_MATRIX3) && ((*m_fncGet_MATRIX3)(moduleName, varName, value, myVessel->GetName())));
    };

    bool Put(const char* moduleName, const char* varName, const MATRIX4 &value, const VESSEL* myVessel = oapiGetFocusInterface()) const {
      return ((m_fncPut_MATRIX4) && ((*m_fncPut_MATRIX4)(moduleName, varName, value, myVessel->GetName())));
    };
    bool Get(const char* moduleName, const char* varName, MATRIX4* value, const VESSEL* myVessel = oapiGetFocusInterface()) const {
      return ((m_fncGet_MATRIX4) && ((*m_fncGet_MATRIX4)(moduleName, varName, value, myVessel->GetName())));
    };

    bool Put(const char* moduleName, const char* varName, const char *value, const VESSEL* myVessel = oapiGetFocusInterface()) const {
      return ((m_fncPut_c_str) && ((*m_fncPut_c_str)(moduleName, varName, value, myVessel->GetName())));
    };
    bool Get(const char* moduleName, const char* varName, char** value, const size_t maxValueLen, const VESSEL* myVessel = oapiGetFocusInterface()) const {
      return ((m_fncGet_c_str) && ((*m_fncGet_c_str)(moduleName, varName, value, maxValueLen, myVessel->GetName())));
    };

    bool Delete(const char* moduleName, const char* varName, const VESSEL* myVessel = oapiGetFocusInterface()) const {
      return ((m_fncDel_any) && ((*m_fncDel_any)(moduleName, varName, myVessel->GetName())));
    };

  private:
    HMODULE m_hDLL = NULL;
#

#define MM_FNC(__TY, __ty) __MMFNC(__TY, __ty)
#define __MMFNC(__TY, __ty) \
    FUNC_MMEXT2_PUT_##__TY m_fncPut_##__ty = NULL;\
    FUNC_MMEXT2_GET_##__TY m_fncGet_##__ty = NULL

    MM_FNC(INT, int);
    MM_FNC(BOOL, bool);
    MM_FNC(DBL, double);
    MM_FNC(VEC, VECTOR3);
    MM_FNC(MX3, MATRIX3);
    MM_FNC(MX4, MATRIX4);
    FUNC_MMEXT2_PUT_CST m_fncPut_c_str;
    FUNC_MMEXT2_GET_CST m_fncGet_c_str;
    FUNC_MMEXT2_DEL_ANY m_fncDel_any = NULL;
  };

  class Advanced {
  public:
    template<typename T> bool Put(const char* moduleName, const char* varName, T  value, const VESSEL* myVessel = oapiGetFocusInterface()) const {
      return m_imp.Put(moduleName, varName, value, myVessel);
    };
    template<typename T> bool Get(const char* moduleName, const char* varName, T* value, const VESSEL* myVessel = oapiGetFocusInterface()) const {
      return m_imp.Get(moduleName, varName, value, myVessel);
    };
    bool Delete(const char* moduleName, const char* varName, const VESSEL* myVessel = oapiGetFocusInterface()) const {
      return m_imp.Delete(moduleName, varName, myVessel);
    };
  private:
    Implementation m_imp;
  };

  class Simple
  {
  public:
    bool Put(const char* moduleName, const char* varName, int value)     const { return m_imp.Put(moduleName, varName, value); };
    bool Put(const char* moduleName, const char* varName, bool value)    const { return m_imp.Put(moduleName, varName, value); };
    bool Put(const char* moduleName, const char* varName, double value)  const { return m_imp.Put(moduleName, varName, value); };
    bool Put(const char* moduleName, const char* varName, VECTOR3 &value)  const { return m_imp.Put(moduleName, varName, value); };
    bool Put(const char* moduleName, const char* varName, MATRIX3 &value)  const { return m_imp.Put(moduleName, varName, value); };
    bool Put(const char* moduleName, const char* varName, MATRIX4 &value)  const { return m_imp.Put(moduleName, varName, value); };
    bool Get(const char* moduleName, const char* varName, int* value)    const { return m_imp.Get(moduleName, varName, value); };
    bool Get(const char* moduleName, const char* varName, bool* value)   const { return m_imp.Get(moduleName, varName, value); };
    bool Get(const char* moduleName, const char* varName, double* value) const { return m_imp.Get(moduleName, varName, value); };
    bool Get(const char* moduleName, const char* varName, VECTOR3* value) const { return m_imp.Get(moduleName, varName, value); };
    bool Get(const char* moduleName, const char* varName, MATRIX3* value) const { return m_imp.Get(moduleName, varName, value); };
    bool Get(const char* moduleName, const char* varName, MATRIX4* value) const { return m_imp.Get(moduleName, varName, value); };
    bool Delete(const char* moduleName, const char* varName) const { return m_imp.Delete(moduleName, varName); };
  private:
    Implementation m_imp;
    const char *m_thisModuleName;
  };


}
#endif // MMExt2_Client_H
