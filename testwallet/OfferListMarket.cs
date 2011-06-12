/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


using System;
using System.Runtime.InteropServices;

public class OfferListMarket : Storable {
  private HandleRef swigCPtr;

  internal OfferListMarket(IntPtr cPtr, bool cMemoryOwn) : base(otapiPINVOKE.OfferListMarket_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(OfferListMarket obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~OfferListMarket() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          otapiPINVOKE.delete_OfferListMarket(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public uint GetBidDataCount() {
    uint ret = otapiPINVOKE.OfferListMarket_GetBidDataCount(swigCPtr);
    return ret;
  }

  public OfferDataMarket GetBidData(uint nIndex) {
    IntPtr cPtr = otapiPINVOKE.OfferListMarket_GetBidData(swigCPtr, nIndex);
    OfferDataMarket ret = (cPtr == IntPtr.Zero) ? null : new OfferDataMarket(cPtr, false);
    return ret;
  }

  public bool RemoveBidData(uint nIndexBidData) {
    bool ret = otapiPINVOKE.OfferListMarket_RemoveBidData(swigCPtr, nIndexBidData);
    return ret;
  }

  public bool AddBidData(OfferDataMarket disownObject) {
    bool ret = otapiPINVOKE.OfferListMarket_AddBidData(swigCPtr, OfferDataMarket.getCPtr(disownObject));
    if (otapiPINVOKE.SWIGPendingException.Pending) throw otapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint GetAskDataCount() {
    uint ret = otapiPINVOKE.OfferListMarket_GetAskDataCount(swigCPtr);
    return ret;
  }

  public OfferDataMarket GetAskData(uint nIndex) {
    IntPtr cPtr = otapiPINVOKE.OfferListMarket_GetAskData(swigCPtr, nIndex);
    OfferDataMarket ret = (cPtr == IntPtr.Zero) ? null : new OfferDataMarket(cPtr, false);
    return ret;
  }

  public bool RemoveAskData(uint nIndexAskData) {
    bool ret = otapiPINVOKE.OfferListMarket_RemoveAskData(swigCPtr, nIndexAskData);
    return ret;
  }

  public bool AddAskData(OfferDataMarket disownObject) {
    bool ret = otapiPINVOKE.OfferListMarket_AddAskData(swigCPtr, OfferDataMarket.getCPtr(disownObject));
    if (otapiPINVOKE.SWIGPendingException.Pending) throw otapiPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public new static OfferListMarket ot_dynamic_cast(Storable pObject) {
    IntPtr cPtr = otapiPINVOKE.OfferListMarket_ot_dynamic_cast(Storable.getCPtr(pObject));
    OfferListMarket ret = (cPtr == IntPtr.Zero) ? null : new OfferListMarket(cPtr, false);
    return ret;
  }

}