/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.3
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


using System;
using System.Runtime.InteropServices;

public class BitcoinAcct : Acct {
  private HandleRef swigCPtr;

  internal BitcoinAcct(IntPtr cPtr, bool cMemoryOwn) : base(otapiPINVOKE.BitcoinAcct_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(BitcoinAcct obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~BitcoinAcct() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          otapiPINVOKE.delete_BitcoinAcct(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public string bitcoin_acct_name {
    set {
      otapiPINVOKE.BitcoinAcct_bitcoin_acct_name_set(swigCPtr, value);
      if (otapiPINVOKE.SWIGPendingException.Pending) throw otapiPINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      string ret = otapiPINVOKE.BitcoinAcct_bitcoin_acct_name_get(swigCPtr);
      if (otapiPINVOKE.SWIGPendingException.Pending) throw otapiPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

  public static BitcoinAcct dynamic_cast(Storable pObject) {
    IntPtr cPtr = otapiPINVOKE.BitcoinAcct_dynamic_cast(Storable.getCPtr(pObject));
    BitcoinAcct ret = (cPtr == IntPtr.Zero) ? null : new BitcoinAcct(cPtr, false);
    if (otapiPINVOKE.SWIGPendingException.Pending) throw otapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}
