// =======================================================================
//         ORBITER AUX LIBRARY: Module Messaging Extended v2
//                              DLL Interface Internal Header
//
// Copyright  (C) 2014-2017 Szymon "Enjo" Ender and Andrew "ADSWNJ" Stokes
//                         All rights reserved
//
// See MMExt2_Basic.hpp for license and usage information. 
// This is an internal implementation file. Do not include this directly
// in your code. 
// =======================================================================
#pragma once
#ifndef MMExt2_Internal_H
#define MMExt2_Internal_H
#include "windows.h"
#include "orbitersdk.h"
#include <string>

#include "__MMExt2_MMStruct.hpp"

namespace MMExt2
{
  typedef bool(*FUNC_MMEXT2_PUT_INT) (const char* mod,                   const char* var, const int& val,           const char* ves);
  typedef bool(*FUNC_MMEXT2_PUT_BOO) (const char* mod,                   const char* var, const bool& val,          const char* ves);
  typedef bool(*FUNC_MMEXT2_PUT_DBL) (const char* mod,                   const char* var, const double& val,        const char* ves);
  typedef bool(*FUNC_MMEXT2_PUT_VEC) (const char* mod,                   const char* var, const VECTOR3& val,       const char* ves);
  typedef bool(*FUNC_MMEXT2_PUT_MX3) (const char* mod,                   const char* var, const MATRIX3& val,       const char* ves);
  typedef bool(*FUNC_MMEXT2_PUT_MX4) (const char* mod,                   const char* var, const MATRIX4& val,       const char* ves);
  typedef bool(*FUNC_MMEXT2_PUT_CST) (const char* mod,                   const char* var, const char *val,          const char* ves);
  typedef bool(*FUNC_MMEXT2_PUT_MMS) (const char* mod,                   const char* var, const MMStruct* val,      const char* ves);
  typedef bool(*FUNC_MMEXT2_DEL_ANY) (const char* mod,  const char* var,                                            const char* ves);
  typedef bool(*FUNC_MMEXT2_GET_INT) (const char* gmod, const char* mod, const char* var, int* val,                 const char* ves);
  typedef bool(*FUNC_MMEXT2_GET_BOO) (const char* gmod, const char* mod, const char* var, bool* val,                const char* ves);
  typedef bool(*FUNC_MMEXT2_GET_DBL) (const char* gmod, const char* mod, const char* var, double* val,              const char* ves);
  typedef bool(*FUNC_MMEXT2_GET_VEC) (const char* gmod, const char* mod, const char* var, VECTOR3* val,             const char* ves);
  typedef bool(*FUNC_MMEXT2_GET_MX3) (const char* gmod, const char* mod, const char* var, MATRIX3* val,             const char* ves);
  typedef bool(*FUNC_MMEXT2_GET_MX4) (const char* gmod, const char* mod, const char* var, MATRIX4* val,             const char* ves);
  typedef bool(*FUNC_MMEXT2_GET_CST) (const char* gmod, const char* mod, const char* var, char *val, size_t *len,   const char* ves);
  typedef bool(*FUNC_MMEXT2_GET_MMS) (const char* gmod, const char* mod, const char* var, const MMStruct** val,     const char* ves);

  class Internal {
  public:
    Internal(const char *mod);
    ~Internal();
    bool IsInit() const {return m_initialized;};
    bool _Put(const char* var, const int &val,                          const VESSEL* ves = NULL) const   {return ((m_fPI) && ((*m_fPI)(m_mod, var, val,         (ves?ves->GetName():m_vn))));}
    bool _Put(const char* var, const bool &val,                         const VESSEL* ves = NULL) const   {return ((m_fPB) && ((*m_fPB)(m_mod, var, val,         (ves?ves->GetName():m_vn))));}
    bool _Put(const char* var, const double &val,                       const VESSEL* ves = NULL) const   {return ((m_fPD) && ((*m_fPD)(m_mod, var, val,         (ves?ves->GetName():m_vn))));}
    bool _Put(const char* var, const VECTOR3 &val,                      const VESSEL* ves = NULL) const   {return ((m_fPV) && ((*m_fPV)(m_mod, var, val,         (ves?ves->GetName():m_vn))));}
    bool _Put(const char* var, const MATRIX3 &val,                      const VESSEL* ves = NULL) const   {return ((m_fP3) && ((*m_fP3)(m_mod, var, val,         (ves?ves->GetName():m_vn))));}
    bool _Put(const char* var, const MATRIX4 &val,                      const VESSEL* ves = NULL) const   {return ((m_fP4) && ((*m_fP4)(m_mod, var, val,         (ves?ves->GetName():m_vn))));}
    bool _Put(const char* var, const MMStruct* val,                     const VESSEL* ves = NULL) const   {return ((m_fPX) && ((*m_fPX)(m_mod, var, val,         (ves?ves->GetName():m_vn))));}
    bool _Put(const char* var, const std::string &val,                  const VESSEL* ves = NULL) const   {return ((m_fPS) && ((*m_fPS)(m_mod, var, val.c_str(), (ves?ves->GetName():m_vn))));}
    bool _Del(const char* var,                                          const VESSEL* ves = NULL) const   {return ((m_fDA) && ((*m_fDA)(m_mod, var,              (ves?ves->GetName():m_vn))));}
    bool _Get(const char* mod, const char* var, int* val,               const VESSEL* ves = NULL) const   {return ((m_fGI) && ((*m_fGI)(m_mod, mod, var, val,    (ves?ves->GetName():m_vn))));}
    bool _Get(const char* mod, const char* var, bool* val,              const VESSEL* ves = NULL) const   {return ((m_fGB) && ((*m_fGB)(m_mod, mod, var, val,    (ves?ves->GetName():m_vn))));}
    bool _Get(const char* mod, const char* var, double* val,            const VESSEL* ves = NULL) const   {return ((m_fGD) && ((*m_fGD)(m_mod, mod, var, val,    (ves?ves->GetName():m_vn))));}
    bool _Get(const char* mod, const char* var, VECTOR3* val,           const VESSEL* ves = NULL) const   {return ((m_fGV) && ((*m_fGV)(m_mod, mod, var, val,    (ves?ves->GetName():m_vn))));}
    bool _Get(const char* mod, const char* var, MATRIX3* val,           const VESSEL* ves = NULL) const   {return ((m_fG3) && ((*m_fG3)(m_mod, mod, var, val,    (ves?ves->GetName():m_vn))));}
    bool _Get(const char* mod, const char* var, MATRIX4* val,           const VESSEL* ves = NULL) const   {return ((m_fG4) && ((*m_fG4)(m_mod, mod, var, val,    (ves?ves->GetName():m_vn))));}
    bool _Get(const char* mod, const char* var, const MMStruct** val,   const VESSEL* ves = NULL) const   {return ((m_fGX) && ((*m_fGX)(m_mod, mod, var, val,    (ves?ves->GetName():m_vn))));}
    bool _Get(const char* mod, const char* var, std::string* val,       const VESSEL* ves = NULL) const;
  private:
    FUNC_MMEXT2_PUT_INT m_fPI;
    FUNC_MMEXT2_PUT_BOO m_fPB;
    FUNC_MMEXT2_PUT_DBL m_fPD;
    FUNC_MMEXT2_PUT_VEC m_fPV;
    FUNC_MMEXT2_PUT_MX3 m_fP3;
    FUNC_MMEXT2_PUT_MX4 m_fP4;
    FUNC_MMEXT2_PUT_CST m_fPS;
    FUNC_MMEXT2_PUT_MMS m_fPX;
    FUNC_MMEXT2_GET_INT m_fGI;
    FUNC_MMEXT2_GET_BOO m_fGB;
    FUNC_MMEXT2_GET_DBL m_fGD;
    FUNC_MMEXT2_GET_VEC m_fGV;
    FUNC_MMEXT2_GET_MX3 m_fG3;
    FUNC_MMEXT2_GET_MX4 m_fG4;
    FUNC_MMEXT2_GET_CST m_fGS;
    FUNC_MMEXT2_GET_MMS m_fGX;
    FUNC_MMEXT2_DEL_ANY m_fDA;
    bool m_initialized; 
    HMODULE m_hDLL;
    char* m_vn;
    char* m_mod;
  };


  // Inline implementation allows this to be included in multiple compilation units 
  // Compiler and linker will determine best way to combine the compilation units
  inline bool Internal::_Get(const char* mod, const char* var, std::string* val, const VESSEL* ves) const {
    if (!m_fGS) return false;
    const size_t max_simple_len = 64;
    size_t csl = max_simple_len;
    char buf[max_simple_len];
    if (!(*m_fGS)(m_mod, mod, var, &buf[0], &csl, (ves ? ves->GetName() : m_vn))) return false;
    if (csl <= max_simple_len) {
      *val = buf;
      return true;
    }
    // long string support
    char *p1 = static_cast<char *>(malloc(csl));
    if (!(*m_fGS)(m_mod, mod, var, p1, &csl, (ves ? ves->GetName() : m_vn))) return false;
    *val = p1;
    free(p1);
    return true;
  };

  inline Internal::Internal(const char *mod) {
    if (m_initialized) return;
    m_mod = _strdup(mod);
    VESSEL* v = oapiGetFocusInterface();
    m_vn = _strdup(v->GetName());

    m_initialized = true;
    if (!(m_hDLL = LoadLibraryA(".\\Modules\\MMExt2.dll"))) return;
    m_fPI = (FUNC_MMEXT2_PUT_INT)GetProcAddress(m_hDLL, "ModMsgPut_int_v1");
    m_fPB = (FUNC_MMEXT2_PUT_BOO)GetProcAddress(m_hDLL, "ModMsgPut_bool_v1");
    m_fPD = (FUNC_MMEXT2_PUT_DBL)GetProcAddress(m_hDLL, "ModMsgPut_double_v1");
    m_fPV = (FUNC_MMEXT2_PUT_VEC)GetProcAddress(m_hDLL, "ModMsgPut_VECTOR3_v1");
    m_fP3 = (FUNC_MMEXT2_PUT_MX3)GetProcAddress(m_hDLL, "ModMsgPut_MATRIX3_v1");
    m_fP4 = (FUNC_MMEXT2_PUT_MX4)GetProcAddress(m_hDLL, "ModMsgPut_MATRIX4_v1");
    m_fPS = (FUNC_MMEXT2_PUT_CST)GetProcAddress(m_hDLL, "ModMsgPut_c_str_v1");
    m_fPX = (FUNC_MMEXT2_PUT_MMS)GetProcAddress(m_hDLL, "ModMsgPut_MMStruct_v1");
    m_fGI = (FUNC_MMEXT2_GET_INT)GetProcAddress(m_hDLL, "ModMsgGet_int_v1");
    m_fGB = (FUNC_MMEXT2_GET_BOO)GetProcAddress(m_hDLL, "ModMsgGet_bool_v1");
    m_fGD = (FUNC_MMEXT2_GET_DBL)GetProcAddress(m_hDLL, "ModMsgGet_double_v1");
    m_fGV = (FUNC_MMEXT2_GET_VEC)GetProcAddress(m_hDLL, "ModMsgGet_VECTOR3_v1");
    m_fG3 = (FUNC_MMEXT2_GET_MX3)GetProcAddress(m_hDLL, "ModMsgGet_MATRIX3_v1");
    m_fG4 = (FUNC_MMEXT2_GET_MX4)GetProcAddress(m_hDLL, "ModMsgGet_MATRIX4_v1");
    m_fGS = (FUNC_MMEXT2_GET_CST)GetProcAddress(m_hDLL, "ModMsgGet_c_str_v1");
    m_fGX = (FUNC_MMEXT2_GET_MMS)GetProcAddress(m_hDLL, "ModMsgGet_MMStruct_v1");
    m_fDA = (FUNC_MMEXT2_DEL_ANY)GetProcAddress(m_hDLL, "ModMsgDel_any_v1");
  };
  inline Internal::~Internal() {
    if (m_hDLL) FreeLibrary(m_hDLL);
    if (m_mod) free(m_mod);
    if (m_vn) free(m_vn);
  };
}


#endif // MMExt2_Internal_H
