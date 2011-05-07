/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.3
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


using System;
using System.Runtime.InteropServices;

public class OTAsymmetricKey : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal OTAsymmetricKey(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(OTAsymmetricKey obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~OTAsymmetricKey() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          otapiPINVOKE.delete_OTAsymmetricKey(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public static void SetPasswordCallback(SWIGTYPE_p_f_p_char_int_int_p_void__int pCallback) {
    otapiPINVOKE.OTAsymmetricKey_SetPasswordCallback(SWIGTYPE_p_f_p_char_int_int_p_void__int.getCPtr(pCallback));
  }

  public static SWIGTYPE_p_f_p_char_int_int_p_void__int GetPasswordCallback() {
    IntPtr cPtr = otapiPINVOKE.OTAsymmetricKey_GetPasswordCallback();
    SWIGTYPE_p_f_p_char_int_int_p_void__int ret = (cPtr == IntPtr.Zero) ? null : new SWIGTYPE_p_f_p_char_int_int_p_void__int(cPtr, false);
    return ret;
  }

  public static bool IsPasswordCallbackSet() {
    bool ret = otapiPINVOKE.OTAsymmetricKey_IsPasswordCallbackSet();
    return ret;
  }

  public OTAsymmetricKey() : this(otapiPINVOKE.new_OTAsymmetricKey(), true) {
  }

  public void Release() {
    otapiPINVOKE.OTAsymmetricKey_Release(swigCPtr);
  }

  public SWIGTYPE_p_EVP_PKEY GetKey() {
    IntPtr cPtr = otapiPINVOKE.OTAsymmetricKey_GetKey(swigCPtr);
    SWIGTYPE_p_EVP_PKEY ret = (cPtr == IntPtr.Zero) ? null : new SWIGTYPE_p_EVP_PKEY(cPtr, false);
    return ret;
  }

  public void SetKey(SWIGTYPE_p_EVP_PKEY pKey) {
    otapiPINVOKE.OTAsymmetricKey_SetKey(swigCPtr, SWIGTYPE_p_EVP_PKEY.getCPtr(pKey));
  }

  public bool LoadPrivateKey(SWIGTYPE_p_OTString strFilename) {
    bool ret = otapiPINVOKE.OTAsymmetricKey_LoadPrivateKey(swigCPtr, SWIGTYPE_p_OTString.getCPtr(strFilename));
    if (otapiPINVOKE.SWIGPendingException.Pending) throw otapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool LoadPublicKey(SWIGTYPE_p_OTString strFilename) {
    bool ret = otapiPINVOKE.OTAsymmetricKey_LoadPublicKey(swigCPtr, SWIGTYPE_p_OTString.getCPtr(strFilename));
    if (otapiPINVOKE.SWIGPendingException.Pending) throw otapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool LoadPublicKeyFromPGPKey(SWIGTYPE_p_OTASCIIArmor strKey) {
    bool ret = otapiPINVOKE.OTAsymmetricKey_LoadPublicKeyFromPGPKey(swigCPtr, SWIGTYPE_p_OTASCIIArmor.getCPtr(strKey));
    if (otapiPINVOKE.SWIGPendingException.Pending) throw otapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool LoadPublicKeyFromCertFile(SWIGTYPE_p_OTString strFilename) {
    bool ret = otapiPINVOKE.OTAsymmetricKey_LoadPublicKeyFromCertFile(swigCPtr, SWIGTYPE_p_OTString.getCPtr(strFilename));
    if (otapiPINVOKE.SWIGPendingException.Pending) throw otapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool LoadPublicKeyFromCertString(SWIGTYPE_p_OTString strCert, bool bEscaped) {
    bool ret = otapiPINVOKE.OTAsymmetricKey_LoadPublicKeyFromCertString__SWIG_0(swigCPtr, SWIGTYPE_p_OTString.getCPtr(strCert), bEscaped);
    if (otapiPINVOKE.SWIGPendingException.Pending) throw otapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool LoadPublicKeyFromCertString(SWIGTYPE_p_OTString strCert) {
    bool ret = otapiPINVOKE.OTAsymmetricKey_LoadPublicKeyFromCertString__SWIG_1(swigCPtr, SWIGTYPE_p_OTString.getCPtr(strCert));
    if (otapiPINVOKE.SWIGPendingException.Pending) throw otapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool GetPublicKey(SWIGTYPE_p_OTString strKey, bool bEscaped) {
    bool ret = otapiPINVOKE.OTAsymmetricKey_GetPublicKey__SWIG_0(swigCPtr, SWIGTYPE_p_OTString.getCPtr(strKey), bEscaped);
    if (otapiPINVOKE.SWIGPendingException.Pending) throw otapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool GetPublicKey(SWIGTYPE_p_OTString strKey) {
    bool ret = otapiPINVOKE.OTAsymmetricKey_GetPublicKey__SWIG_1(swigCPtr, SWIGTYPE_p_OTString.getCPtr(strKey));
    if (otapiPINVOKE.SWIGPendingException.Pending) throw otapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool GetPublicKey(SWIGTYPE_p_OTASCIIArmor strKey) {
    bool ret = otapiPINVOKE.OTAsymmetricKey_GetPublicKey__SWIG_2(swigCPtr, SWIGTYPE_p_OTASCIIArmor.getCPtr(strKey));
    if (otapiPINVOKE.SWIGPendingException.Pending) throw otapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool SetPublicKey(SWIGTYPE_p_OTString strKey, bool bEscaped) {
    bool ret = otapiPINVOKE.OTAsymmetricKey_SetPublicKey__SWIG_0(swigCPtr, SWIGTYPE_p_OTString.getCPtr(strKey), bEscaped);
    if (otapiPINVOKE.SWIGPendingException.Pending) throw otapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool SetPublicKey(SWIGTYPE_p_OTString strKey) {
    bool ret = otapiPINVOKE.OTAsymmetricKey_SetPublicKey__SWIG_1(swigCPtr, SWIGTYPE_p_OTString.getCPtr(strKey));
    if (otapiPINVOKE.SWIGPendingException.Pending) throw otapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool SetPublicKey(SWIGTYPE_p_OTASCIIArmor strKey) {
    bool ret = otapiPINVOKE.OTAsymmetricKey_SetPublicKey__SWIG_2(swigCPtr, SWIGTYPE_p_OTASCIIArmor.getCPtr(strKey));
    if (otapiPINVOKE.SWIGPendingException.Pending) throw otapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}