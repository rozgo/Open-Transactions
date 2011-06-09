/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


using System;
using System.Runtime.InteropServices;

public class Acct : Displayable {
  private HandleRef swigCPtr;

  internal Acct(IntPtr cPtr, bool cMemoryOwn) : base(otapiPINVOKE.Acct_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(Acct obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~Acct() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          otapiPINVOKE.delete_Acct(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public string gui_label {
    set {
      otapiPINVOKE.Acct_gui_label_set(swigCPtr, value);
      if (otapiPINVOKE.SWIGPendingException.Pending) throw otapiPINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      string ret = otapiPINVOKE.Acct_gui_label_get(swigCPtr);
      if (otapiPINVOKE.SWIGPendingException.Pending) throw otapiPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

  public string acct_id {
    set {
      otapiPINVOKE.Acct_acct_id_set(swigCPtr, value);
      if (otapiPINVOKE.SWIGPendingException.Pending) throw otapiPINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      string ret = otapiPINVOKE.Acct_acct_id_get(swigCPtr);
      if (otapiPINVOKE.SWIGPendingException.Pending) throw otapiPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

  public string server_id {
    set {
      otapiPINVOKE.Acct_server_id_set(swigCPtr, value);
      if (otapiPINVOKE.SWIGPendingException.Pending) throw otapiPINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      string ret = otapiPINVOKE.Acct_server_id_get(swigCPtr);
      if (otapiPINVOKE.SWIGPendingException.Pending) throw otapiPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

  public new static Acct ot_dynamic_cast(Storable pObject) {
    IntPtr cPtr = otapiPINVOKE.Acct_ot_dynamic_cast(Storable.getCPtr(pObject));
    Acct ret = (cPtr == IntPtr.Zero) ? null : new Acct(cPtr, false);
    return ret;
  }

}
