/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.3
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.wrapper.core.jni;

public class String extends Storable {
  private long swigCPtr;

  public String(long cPtr, boolean cMemoryOwn) {
    super(otapiJNI.String_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(String obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        otapiJNI.delete_String(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public void setM_string(String value) {
    otapiJNI.String_m_string_set(swigCPtr, this, value);
  }

  public String getM_string() {
    return otapiJNI.String_m_string_get(swigCPtr, this);
  }

}
