/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.3
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


using System;
using System.Runtime.InteropServices;

public class OTCaller : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal OTCaller(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(OTCaller obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~OTCaller() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          otapiPINVOKE.delete_OTCaller(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public OTCaller() : this(otapiPINVOKE.new_OTCaller(), true) {
  }

  public string GetPassword() {
    string ret = otapiPINVOKE.OTCaller_GetPassword(swigCPtr);
    return ret;
  }

  public void delCallback() {
    otapiPINVOKE.OTCaller_delCallback(swigCPtr);
  }

  public void setCallback(OTCallback cb) {
    otapiPINVOKE.OTCaller_setCallback(swigCPtr, OTCallback.getCPtr(cb));
  }

  public bool isCallbackSet() {
    bool ret = otapiPINVOKE.OTCaller_isCallbackSet(swigCPtr);
    return ret;
  }

  public void callOne() {
    otapiPINVOKE.OTCaller_callOne(swigCPtr);
  }

  public void callTwo() {
    otapiPINVOKE.OTCaller_callTwo(swigCPtr);
  }

}
