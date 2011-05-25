/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.3
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.wrapper.core.jni;

public class WalletData extends Storable {
  private long swigCPtr;

  public WalletData(long cPtr, boolean cMemoryOwn) {
    super(otapiJNI.WalletData_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(WalletData obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        otapiJNI.delete_WalletData(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }
{
	// ------------------------
	/*@SWIG:OTAPI.i,329,OT_CONTAINER_TYPE_MEMBERS@*/
private List elementList = new ArrayList();
/*@SWIG@*/
	/*@SWIG:OTAPI.i,410,OT_ADD_ELEMENT@*/  // THIS BLOCK CONTAINS JAVA CODE.
// Ensure that the GC doesn't collect any BitcoinServer set from Java
// as the underlying C++ class stores a shallow copy

// Altered the SWIG example so that we store a list of these references, instead
// of only the latest one. None of them should go out of scope until this object does.

private long removeRefBitcoinServer(long lIndex) {
	// 
	// loop through the elements in the actual container, in order to find the one
	// at lIndex. Once it is found, then loop through the reference list and remove
	// the corresponding reference for that element.
	//
	BitcoinServer refActualElement = GetBitcoinServer(lIndex);

	if (refActualElement = null)
		return lIndex; // oh well.
	
	// Loop through the reference list and remove the corresponding reference
	// for the specified element.
	//
	for(int intIndex = 0; intIndex < elementList.size(); intIndex++)
	{
		BitcoinServer tempRef = elementList.get(intIndex);
		
		if ((tempRef instanceof BitcoinServer) &&
			(BitcoinServer.getCPtr(tempRef) == BitcoinServer.getCPtr(refActualElement)))
		{
			elementList.remove(tempRef);
			break;
		}
	}
	
	return lIndex;
}

private long getCPtrAddRefBitcoinServer(BitcoinServer element) {
	// Whenever adding a reference to the list, I remove it first (if already there.)
	// That way we never store more than one reference per actual contained object.
	//
	for(int intIndex = 0; intIndex < elementList.size(); intIndex++)
	{
		BitcoinServer tempRef = elementList.get(intIndex);
		
		if (tempRef == null) // just in case. Should never happen.
			continue;
		
		if ((tempRef instanceof BitcoinServer) &&
			(BitcoinServer.getCPtr(tempRef) == BitcoinServer.getCPtr(element)))
		{
			elementList.remove(tempRef); // It was already there, so let's remove it before adding (below.)
			break;
		}
	}
	// Now we add it...
	//
	BitcoinServer tempLocalRef = element;
	elementList.add(tempLocalRef);
	return BitcoinServer.getCPtr(element);
}	// Hope I get away with overloading this for every type. Otherwise,
// hope I can just change the function name to customize it to type.
/*@SWIG@*/
	/*@SWIG:OTAPI.i,410,OT_ADD_ELEMENT@*/  // THIS BLOCK CONTAINS JAVA CODE.
// Ensure that the GC doesn't collect any BitcoinAcct set from Java
// as the underlying C++ class stores a shallow copy

// Altered the SWIG example so that we store a list of these references, instead
// of only the latest one. None of them should go out of scope until this object does.

private long removeRefBitcoinAcct(long lIndex) {
	// 
	// loop through the elements in the actual container, in order to find the one
	// at lIndex. Once it is found, then loop through the reference list and remove
	// the corresponding reference for that element.
	//
	BitcoinAcct refActualElement = GetBitcoinAcct(lIndex);

	if (refActualElement = null)
		return lIndex; // oh well.
	
	// Loop through the reference list and remove the corresponding reference
	// for the specified element.
	//
	for(int intIndex = 0; intIndex < elementList.size(); intIndex++)
	{
		BitcoinAcct tempRef = elementList.get(intIndex);
		
		if ((tempRef instanceof BitcoinAcct) &&
			(BitcoinAcct.getCPtr(tempRef) == BitcoinAcct.getCPtr(refActualElement)))
		{
			elementList.remove(tempRef);
			break;
		}
	}
	
	return lIndex;
}

private long getCPtrAddRefBitcoinAcct(BitcoinAcct element) {
	// Whenever adding a reference to the list, I remove it first (if already there.)
	// That way we never store more than one reference per actual contained object.
	//
	for(int intIndex = 0; intIndex < elementList.size(); intIndex++)
	{
		BitcoinAcct tempRef = elementList.get(intIndex);
		
		if (tempRef == null) // just in case. Should never happen.
			continue;
		
		if ((tempRef instanceof BitcoinAcct) &&
			(BitcoinAcct.getCPtr(tempRef) == BitcoinAcct.getCPtr(element)))
		{
			elementList.remove(tempRef); // It was already there, so let's remove it before adding (below.)
			break;
		}
	}
	// Now we add it...
	//
	BitcoinAcct tempLocalRef = element;
	elementList.add(tempLocalRef);
	return BitcoinAcct.getCPtr(element);
}	// Hope I get away with overloading this for every type. Otherwise,
// hope I can just change the function name to customize it to type.
/*@SWIG@*/
}
  public long GetBitcoinServerCount() { return otapiJNI.WalletData_GetBitcoinServerCount(swigCPtr, this); }

  public BitcoinServer GetBitcoinServer(long nIndex) {
    long cPtr = otapiJNI.WalletData_GetBitcoinServer(swigCPtr, this, nIndex);
    return (cPtr == 0) ? null : new BitcoinServer(cPtr, false);
  }

  public boolean RemoveBitcoinServer(long nIndexToRemove) {
    return otapiJNI.WalletData_RemoveBitcoinServer(swigCPtr, this, { removeRefContact(nIndexToRemove) });
  }

  public boolean AddBitcoinServer(BitcoinServer disownObject) {
    return otapiJNI.WalletData_AddBitcoinServer(swigCPtr, this, BitcoinServer.getCPtr(disownObject), disownObject);
  }

  public long GetBitcoinAcctCount() { return otapiJNI.WalletData_GetBitcoinAcctCount(swigCPtr, this); }

  public BitcoinAcct GetBitcoinAcct(long nIndex) {
    long cPtr = otapiJNI.WalletData_GetBitcoinAcct(swigCPtr, this, nIndex);
    return (cPtr == 0) ? null : new BitcoinAcct(cPtr, false);
  }

  public boolean RemoveBitcoinAcct(long nIndexToRemove) {
    return otapiJNI.WalletData_RemoveBitcoinAcct(swigCPtr, this, { removeRefContact(nIndexToRemove) });
  }

  public boolean AddBitcoinAcct(BitcoinAcct disownObject) {
    return otapiJNI.WalletData_AddBitcoinAcct(swigCPtr, this, BitcoinAcct.getCPtr(disownObject), disownObject);
  }

  public static WalletData ot_dynamic_cast(Storable pObject) { 
    long cPtr = otapiJNI.WalletData_ot_dynamic_cast(Storable.getCPtr(pObject), pObject); 
    WalletData ret = null; 
    if (cPtr != 0) { 
		ret = new WalletData(cPtr, false);
		ret.addReference(this); 
    } 
    return ret; 
}

}
