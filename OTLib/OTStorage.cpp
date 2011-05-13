/************************************************************
 -----BEGIN PGP SIGNED MESSAGE-----
 Hash: SHA256
 
 *                 OPEN TRANSACTIONS
 *
 *       Financial Cryptography and Digital Cash
 *       Library, Protocol, API, Server, and GUI 
 *    
 *    	 -- Anonymous Numbered Accounts.
 *    	 -- Untraceable Digital Cash.
 *    	 -- Triple-Signed Receipts.
 *    	 -- Cheques, Vouchers, Transfers, Inboxes.
 *    	 -- Basket Currencies, Markets, Payment Plans.
 *    	 -- Signed, XML, Ricardian-style Contracts.
 *    
 *  Copyright (C) 2010-2011 by "Fellow Traveler" (A pseudonym)
 *
 *  EMAIL:
 *  FellowTraveler@rayservers.net --- SEE PGP KEY BELOW.
 *  F3llowTraveler@gmail.com --- (not preferred.)
 *  
 *  BITCOIN:  1NtTPVVjDsUfDWybS4BwvHpG2pdS9RnYyQ
 *
 *  KEY FINGERPRINT:
 *  9DD5 90EB 9292 4B48 0484  7910 0308 00ED F951 BB8E
 *
 *  OFFICIAL PROJECT WIKI(s):
 *  http://wiki.github.com/FellowTraveler/Open-Transactions/wiki 
 *  http://wiki.github.com/FellowTraveler/Moneychanger/wiki 
 *
 *  WEBSITE:
 *  http://www.OpenTransactions.org/
 *    
 *  Components and licensing:
 *   -- Moneychanger..A Java client GUI.....LICENSE:.....GPLv3
 *   -- OTLib.........A class library.......LICENSE:...LAGPLv3 
 *   -- OT-API........A client API..........LICENSE:...LAGPLv3
 *   -- testwallet....Command-line client...LICENSE:...LAGPLv3
 *   -- OT-Server.....Server Application....LICENSE:....AGPLv3
 *  Github.com/FellowTraveler/Open-Transactions/wiki/Components
 *
 *  All of the above OT components were designed and written by
 *  Fellow Traveler, with the exception of Moneychanger, which
 *  was contracted out to Vicky C (livewire_3001@yahoo.com).
 *
 *  -----------------------------------------------------
 *
 *   LICENSE:
 *   This program is free software: you can redistribute it
 *   and/or modify it under the terms of the GNU Affero
 *   General Public License as published by the Free Software
 *   Foundation, either version 3 of the License, or (at your
 *   option) any later version.
 *    
 *   ADDITIONAL PERMISSION under the GNU Affero GPL version 3
 *   section 7: (This paragraph applies only to the LAGPLv3
 *   components listed above.) If you modify this Program, or
 *   any covered work, by linking or combining it with other
 *   code, such other code is not for that reason alone subject
 *   to any of the requirements of the GNU Affero GPL version 3.
 *   (==> This means if you are only using the OT-API, then you
 *   don't have to open-source your code--only your changes to
 *   Open Transactions itself must be open source. Similar to
 *   LGPLv3, except it applies to software-as-a-service, not
 *   just to distributing binaries.)
 *
 *   Extra WAIVER for OpenSSL, Lucre, and all other libraries
 *   used by Open Transactions: This program is released under
 *   the AGPL with the additional exemption that compiling,
 *   linking, and/or using OpenSSL is allowed. The same is true
 *   for any other open source libraries included in this
 *   project: complete waiver from the AGPL is hereby granted to
 *   compile, link, and/or use them with Open Transactions,
 *   according to their own terms, as long as the rest of the
 *   Open Transactions terms remain respected, with regard to
 *   the Open Transactions code itself.
 *    
 *   Lucre License:
 *   This code is also "dual-license", meaning that Ben Lau-
 *   rie's license must also be included and respected, since
 *   the code for Lucre is also included with Open Transactions.
 *   See Open-Transactions/OTLib/Lucre/LUCRE_LICENSE.txt
 *   The Laurie requirements are light, but if there is any
 *   problem with his license, simply remove the Lucre code.
 *   Although there are no other blind token algorithms in Open
 *   Transactions (yet. credlib is coming), the other functions
 *   will continue to operate.
 *   -----------------------------------------------------
 *   You should have received a copy of the GNU Affero General
 *   Public License along with this program.  If not, see:
 *   http://www.gnu.org/licenses/
 *
 *   If you would like to use this software outside of the free
 *   software license, please contact FellowTraveler.
 *   (Unfortunately many will run anonymously and untraceably,
 *   so who could really stop them?)
 *   
 *   DISCLAIMER:
 *   This program is distributed in the hope that it will be
 *   useful, but WITHOUT ANY WARRANTY; without even the implied
 *   warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *   PURPOSE.  See the GNU Affero General Public License for
 *   more details.
 
 -----BEGIN PGP SIGNATURE-----
 Version: GnuPG v1.4.10 (Darwin)
 
 iQIcBAEBCAAGBQJNsV9NAAoJEAMIAO35UbuOB3IP/12THBedTYrR2F2hkhYKK+0H
 YlVwRJyFnX3uKjDkYx2fpB2yNaMPPyiQRFpQBpiUxB2wSMHelM+m4YxVegx7h15s
 nD+jMLeVnlhgfKYsVZZiCKT58HXVsuGDc/iycXBBIQYBjCzbeCCG0vyEapR+sCwF
 eGR5l7yGbcMWaVqjPawqSMe/5Ie0wstWMrNAkLlWHRn/ISXb8vMusaxCe9kSeUX8
 7ZSZ0ojy3gLTZnUHFFZ2RaMepVB9jVoMSdVG89mEHX383foTuaxedjI2Wsw6J8YR
 D7PFp6PLGhm1eqArmotCj5NeV9lleULdnvR7T4QwzOZjI65kMwi/e1W6GyvzT3RZ
 RrLaZwiagcyKTXyEX5qSBQfSVNwC761rgNTG0fCBrBmDbQxet4A6Y+ZMxZmE0QXb
 Xch/g4g9Lki0TrSOx0zSAAcpLCIrqdvGX2jcmmJ/Ex4ZhzVhMvtkGfui9bUaY2bU
 bdu1GY0CfmElZ7+wXh2AutkMscRtnu62VSdGjrqry3KJMBWbtxNA9Q+U+NipWnYN
 yisBlQBADkXNtkL3EXEqX6OnjGfHNZ3G1bwuELcZjoOL+K0aQKCojRf8Ii5DW0A3
 niqzq/dwpt45VaQ+uYSG7Sg19FNvADg+WILdFcyszfS8Wks6BsKYzHUc5zbf3SFc
 JaOXLV9Ss58mj57JpNp8
 =VjLJ
 -----END PGP SIGNATURE-----
 **************************************************************/

#include <iostream>
#include <sstream>


#include "OTLog.h"
#include "OTStorage.h"



/*
 
 // We want to store EXISTING OT OBJECTS (Usually signed contracts)
 // These have an EXISTING OT path, such as "inbox/<acct_id>".
 // These are always in the form of a STRING.
 // The easiest way for me to store/retrieve those strings is:
 
 using namespace OTDB;
 
 bool bSuccessStore = StoreString(strContents, strFolder, strFilename);
 bool bSuccessQuery = QueryString(strRetrieved, strFolder, strFilename);
 
 // -------
 // Internal to the above functions, the default Packing/Buffer is
 // used, and the default Storage type is used. But what if I want to
 // CHOOSE the storage and packing? Perhaps the default (filesystem) is not
 // good enough for me, and I prefer a key/value DB.
 
 // Storage.
 // Before creating my OWN storage, let's try using the default storage object
 // itself, instead of asking the API to use it for me:
 
 OTDB::Storage * pStorage = OTDB::GetDefaultStorage();
 OT_ASSERT(NULL!=pStorage);
 
 bool bSuccessStore = pStorage->StoreString(strContents, strFolder, strFilename);
 bool bSuccessQuery = pStorage->QueryString(strRetrieved, strFolder, strFilename);
 
 // -------
 // So if I wanted to create my OWN instance of storage, instead of using the
 // default one, it would be similar:
 
 OTDB::Storage * pStorage = OTDB::CreateStorageContext(STORE_FILESYSTEM, PACK_MESSAGE_PACK);
 OT_ASSERT(NULL!=pStorage);
 
 bool bSuccessInit  = pStorage->Init("/path/to/data_folder", "wallet.xml");
 
 if (bSuccessInit)
 {
	bool bSuccessStore = pStorage->StoreString(strContents, strFolder, strFilename);
	bool bSuccessQuery = pStorage->QueryString(strRetrieved, strFolder, strFilename);
 }
 
 // Creating like above is also how the default storage context gets instantiated
 // (internally) when you first start storing and querying.
  
 // But Storage needs to be SET UP -- whether a database connection initiated,
 // or files loaded, or sub-directories created, or a Tor connection or whatever.
 // Therefore, there is an Init() call, which may have different parameters for
 // each storage type. That way, all subclasses might use it differently, and
 // the parameters are easily thrown into a config file later.
 
 // ------
 // What if it was a CouchDB database, instead of the filesystem? 
 // And using Google's Protocol Buffers for packing, isntead of MsgPack?
 // (Note: OT doesn't actually support CouchDB yet.) But it would look like:
 
 Storage * pStorage = 
 CreateStorageContext(STORE_COUCHDB, PACK_PROTOCOL_BUFFERS);
 OT_ASSERT(NULL!=pStorage);
 
 // This time, Init receives database connect info instead of filesystem info...
 bool bSuccessInit  = pStorage->Init("IP ADDRESS", "PORT", "USERNAME", "PASSWORD", "DATABASE NAME");
 
 etc.
 
 // --------------------
 // So what if I want to use the default, but I want that DEFAULT to be CouchDB and Google?
 // Just do this (near the beginning of the execution of the application):
 
 bool bInit = InitDefaultStorage(STORE_COUCHDB, PACK_PROTOCOL_BUFFERS, 
				"IP ADDRESS", "PORT", "USERNAME", "PASSWORD", "DB NAME");
 
 if (true == bInit)
 {
	// Then do this as normal:
 
	Storage * pStorage = GetDefaultStorage();
	OT_ASSERT(NULL!=pStorage);
 
	bool bSuccessStore = pStorage->StoreString(strContents, strFolder, strFilename);
	bool bSuccessQuery = pStorage->QueryString(strRetrieved, strFolder, strFilename);
 }
 
 // -----------------------------------------------------------
 
 // What if you want to store an OBJECT in that location instead of a string?
 // The object must be instantiated by the Storage Context...
 
 BitcoinAcct * pAcct = pStorage->CreateObject(STORED_OBJ_BITCOIN_ACCT);
 OT_ASSERT(NULL != pAcct);
 
 pAcct->acct_id			= "jkhsdf987345kjhf8lkjhwef987345";
 pAcct->bitcoin_acct_name	= "Read-Only Label (Bitcoin Internal acct)";
 pAcct->gui_label			= "Editable Label (Moneychanger)";
 
 // -----------------------------------------------------------
 // Perhaps you want to load up a Wallet and add this BitcoinAcct to it...
 
 WalletData * pWalletData = 
	pStorage->QueryObject(STORED_OBJ_WALLET_DATA, "moneychanger", "wallet.pak");
 
 if (NULL != pWalletData) // It loaded.
 {
	if (pWalletData->AddBitcoinAcct(*pAcct))
		bool bSuccessStore = pStorage->StoreObject(*pWalletData, "moneychanger", strFilename);
	else
		delete pAcct;
 
	delete pWalletData;
 }
 
 // Voila! The above code creates a BitcoinAcct (data object, not the real thing)
 // and then loads up the Moneychanger WalletData object, adds the BitcoinAcct to
 // it, and then stores it again.
 
 // --------------------------------------------------------------
  
 */

OTDB::Storage * OTDB::details::s_pStorage= NULL;

OTDB::mapOfFunctions * OTDB::details::pFunctionMap=NULL; // This is a pointer so I can control what order it is created in, on startup.

namespace OTDB
{
	

// ********************************************************************

// NAMESPACE CONSTRUCTOR / DESTRUCTOR

// s_pStorage is "private" to the namespace.
// Use GetDefaultStorage() to access this variable.
// Use InitDefaultStorage() to set up this variable.
//
//Storage * ::details::s_pStorage = NULL;
// These are actually defined in the namespace (.h file).

//mapOfFunctions * details::pFunctionMap;

InitOTDBDetails theOTDBConstructor; // Constructor for this instance (define all namespace variables above this line.)

InitOTDBDetails::InitOTDBDetails() // Constructor for namespace
{
	OT_ASSERT (NULL == details::pFunctionMap);

	details::pFunctionMap = new mapOfFunctions;
	
	OT_ASSERT (NULL != details::pFunctionMap);
	
	mapOfFunctions & theMap = *(details::pFunctionMap);
	
	// Set up theMap...
	
#if defined (OTDB_MESSAGE_PACK)
	theMap[std::make_pair(PACK_MESSAGE_PACK, STORED_OBJ_STRING_MAP)]	= &StringMapMsgpack::Instantiate;
	theMap[std::make_pair(PACK_MESSAGE_PACK, STORED_OBJ_WALLET_DATA)]	= &WalletDataMsgpack::Instantiate;
	theMap[std::make_pair(PACK_MESSAGE_PACK, STORED_OBJ_BITCOIN_ACCT)]	= &BitcoinAcctMsgpack::Instantiate;
	theMap[std::make_pair(PACK_MESSAGE_PACK, STORED_OBJ_BITCOIN_SERVER)]= &BitcoinServerMsgpack::Instantiate;
	theMap[std::make_pair(PACK_MESSAGE_PACK, STORED_OBJ_SERVER_INFO)]	= &ServerInfoMsgpack::Instantiate;
	theMap[std::make_pair(PACK_MESSAGE_PACK, STORED_OBJ_CONTACT_ACCT)]	= &ContactAcctMsgpack::Instantiate;
	theMap[std::make_pair(PACK_MESSAGE_PACK, STORED_OBJ_CONTACT_NYM)]	= &ContactNymMsgpack::Instantiate;
	theMap[std::make_pair(PACK_MESSAGE_PACK, STORED_OBJ_CONTACT)]		= &ContactMsgpack::Instantiate;
	theMap[std::make_pair(PACK_MESSAGE_PACK, STORED_OBJ_ADDRESS_BOOK)]	= &AddressBookMsgpack::Instantiate;
#endif
	
#if defined (OTDB_PROTOCOL_BUFFERS)
	GOOGLE_PROTOBUF_VERIFY_VERSION; 
	theMap[std::make_pair(PACK_PROTOCOL_BUFFERS, STORED_OBJ_STRING_MAP)]	= &StringMapPB::Instantiate;
	theMap[std::make_pair(PACK_PROTOCOL_BUFFERS, STORED_OBJ_WALLET_DATA)]	= &WalletDataPB::Instantiate;
	theMap[std::make_pair(PACK_PROTOCOL_BUFFERS, STORED_OBJ_BITCOIN_ACCT)]	= &BitcoinAcctPB::Instantiate;
	theMap[std::make_pair(PACK_PROTOCOL_BUFFERS, STORED_OBJ_BITCOIN_SERVER)]= &BitcoinServerPB::Instantiate; 
	theMap[std::make_pair(PACK_PROTOCOL_BUFFERS, STORED_OBJ_SERVER_INFO)]	= &ServerInfoPB::Instantiate; 
	theMap[std::make_pair(PACK_PROTOCOL_BUFFERS, STORED_OBJ_CONTACT_ACCT)]	= &ContactAcctPB::Instantiate; 
	theMap[std::make_pair(PACK_PROTOCOL_BUFFERS, STORED_OBJ_CONTACT_NYM)]	= &ContactNymPB::Instantiate; 
	theMap[std::make_pair(PACK_PROTOCOL_BUFFERS, STORED_OBJ_CONTACT)]		= &ContactPB::Instantiate; 
	theMap[std::make_pair(PACK_PROTOCOL_BUFFERS, STORED_OBJ_ADDRESS_BOOK)]	= &AddressBookPB::Instantiate; 
#endif
	
}

InitOTDBDetails::~InitOTDBDetails() // Destructor for namespace
{
	OT_ASSERT(NULL != details::pFunctionMap);
	
	delete details::pFunctionMap;
	
	details::pFunctionMap = NULL;
	
	// ------------------------------------------
	
#if defined (OTDB_PROTOCOL_BUFFERS)
	google::protobuf::ShutdownProtobufLibrary();
#endif
}

// ********************************************************************

// INTERFACE for the Namespace (for coders to use.)


	Storage * GetDefaultStorage() { return OTDB::details::s_pStorage; }

// You might normally create your own Storage object, choosing the storage type
// and the packing type, and then call Init() on that object in order to get it
// up and running.  This function is the equivalent of doing all that, but with the
// DEFAULT storage object (which OT uses when none is specified.)
//
bool InitDefaultStorage(StorageType eStoreType, PackType ePackType,
							  std::string oneStr/*=""*/,  std::string twoStr/*=""*/,  std::string threeStr/*=""*/, 
							  std::string fourStr/*=""*/, std::string fiveStr/*=""*/, std::string sixStr/*=""*/)
{
	// Allows you to call multiple times if you want to change the default storage.
	//
	if (NULL != details::s_pStorage)
	{
		delete details::s_pStorage;
		details::s_pStorage = NULL;
	}
	
	details::s_pStorage = Storage::Create(eStoreType, ePackType);
	
	if (NULL == details::s_pStorage)
		return false;
	
	return details::s_pStorage->Init(oneStr, twoStr, threeStr, fourStr, fiveStr, sixStr);
}


// %newobject Factory::createObj();
Storage * CreateStorageContext(StorageType eStoreType, PackType ePackType/*=OTDB_DEFAULT_PACKER*/)
{
	Storage * pStorage = Storage::Create(eStoreType, ePackType);
	
	return pStorage;	// caller responsible to delete
}



// %newobject Factory::createObj();
Storable * CreateObject(StoredObjectType eType)
{
	Storage * pStorage = details::s_pStorage;
	
	if (NULL == pStorage) 
	{
		return NULL;
	}
	
	return pStorage->CreateObject(eType);	
}


// bool bSuccess = Store(strInbox, "inbox", "lkjsdf908w345ljkvd");
// bool bSuccess = Store(strMint,  "mints", SERVER_ID, ASSET_ID);
// bool bSuccess = Store(strPurse, "purse", SERVER_ID, USER_ID, ASSET_ID);

// BELOW FUNCTIONS use the DEFAULT Storage context.

// -----------------------------------------
// See if the file is there.
bool Exists(std::string strFolder, std::string oneStr/*=""*/,  
				  std::string twoStr/*=""*/,  std::string threeStr/*=""*/)
{
	Storage * pStorage = details::s_pStorage;

	if (NULL == pStorage) 
	{
		return false;
	}
	
	return pStorage->Exists(strFolder, oneStr, twoStr, threeStr);
}

// -----------------------------------------
// Store/Retrieve a string.

bool StoreString(std::string strContents, std::string strFolder, std::string oneStr/*=""*/,  
					   std::string twoStr/*=""*/,  std::string threeStr/*=""*/)
{
	Storage * pStorage = details::s_pStorage;
	
	if (NULL == pStorage) 
	{
		return false;
	}
	
	return pStorage->StoreString(strContents, strFolder, oneStr, twoStr, threeStr);
}

std::string QueryString(std::string strFolder, std::string oneStr/*=""*/,  std::string twoStr/*=""*/,  
							  std::string threeStr/*=""*/)
{
	Storage * pStorage = details::s_pStorage;
	
	if (NULL == pStorage) 
	{
		return std::string("");
	}
	
	return pStorage->QueryString(strFolder, oneStr, twoStr, threeStr);
}

// -----------------------------------------
// Store/Retrieve an object. (Storable.)

bool StoreObject(Storable & theContents, std::string strFolder, std::string oneStr/*=""*/,  
					   std::string twoStr/*=""*/,  std::string threeStr/*=""*/)
{
	Storage * pStorage = details::s_pStorage;
	
	if (NULL == pStorage) 
	{
		return false;
	}
	
	return pStorage->StoreObject(theContents, strFolder, oneStr, twoStr, threeStr);
}

// Use %newobject Storage::Query();
Storable * QueryObject(StoredObjectType theObjectType,
							 std::string strFolder, std::string oneStr/*=""*/,  std::string twoStr/*=""*/,  
							 std::string threeStr/*=""*/)
{
	Storage * pStorage = details::s_pStorage;
	
	if (NULL == pStorage) 
	{
		return NULL;
	}
	
	return pStorage->QueryObject(theObjectType, strFolder, oneStr, twoStr, threeStr);
}
// ********************************************************************







// ********************************************************************

// Used internally. Creates the right subclass for any stored object type,
// based on which packer is needed.

Storable * Storable::Create(StoredObjectType eType, PackType thePackType)
{
	if (NULL == details::pFunctionMap)
		return NULL;
	
	Storable * pStorable = NULL;
	
	// The Pack type, plus the Stored Object type, is the Key to the map of function pointers.
	InstantiateFuncKey theKey(thePackType, eType);
	
	// If the key works, we get the function pointer to the static Create() method for
	// the appropriate object type.
	
	mapOfFunctions::iterator ii = details::pFunctionMap->find(theKey);
	
	if (details::pFunctionMap->end() == ii)
		return NULL;
	
	InstantiateFunc * pFunc = (*ii).second;
	
	if (NULL != pFunc)
	{
		pStorable = (*pFunc)(); // Now we instantiate the object...
	}
			
	return pStorable; // May return NULL...
}




// ********************************************************************

// static. OTPacker Factory.
//
OTPacker * OTPacker::Create(PackType ePackType)
{
	OTPacker * pPacker = NULL;
	
	switch (ePackType) 
	{
#if defined (OTDB_MESSAGE_PACK)
		case PACK_MESSAGE_PACK:
			pPacker = new PackerMsgpack; OT_ASSERT(NULL != pPacker); break;
#endif  
#if defined (OTDB_PROTOCOL_BUFFERS)
		case PACK_PROTOCOL_BUFFERS:
			pPacker = new PackerPB; OT_ASSERT(NULL != pPacker); break;
#endif
		case PACK_TYPE_ERROR:
		default:
			break;
	}
	
	return pPacker; // May return NULL...
}
	

PackType OTPacker::GetType() const
{
	if (0)
	{}
#if defined (OTDB_MESSAGE_PACK)
	else if (typeid(*this) == typeid(PackerMsgpack))
		return PACK_MESSAGE_PACK;
#endif
#if defined (OTDB_PROTOCOL_BUFFERS)
	else if (typeid(*this) == typeid(PackerPB))
		return PACK_PROTOCOL_BUFFERS;
#endif
	else
		return PACK_TYPE_ERROR; 
}


// Basically, ALL of the Storables have to implement the IStorable interface 
// (or one of its subclasses).  They can override hookBeforePack(), and they
// can override onPack(). Those two methods will be where all the action is,
// for each subclass of OTPacker.
//
PackedBuffer * OTPacker::Pack(Storable& inObj)
{
	IStorable * pStorable = dynamic_cast<IStorable *> (&inObj);
	
	if (NULL == pStorable)  // ALL Storables should implement SOME subinterface of IStorable
		return NULL;
	
	// --------------------------------
	
	// This is polymorphic, so we get the right kind of buffer for the packer.
	//
	PackedBuffer * pBuffer = CreateBuffer(); 
	OT_ASSERT(NULL != pBuffer);
	
	// Must delete pBuffer, or return it, below this point.
	// -------------------------------------
	
	pStorable->hookBeforePack(); // Give the subclass a chance to prepare its data for packing...
	
	// This line (commented out) shows how the line below it would have looked if I had ended
	// up using polymorphic templates:
	//	if (false == makeTStorable(*pStorable).pack(*pBuffer))
	
	if (false == pStorable->onPack(*pBuffer, inObj))
	{
		delete pBuffer;
		return NULL;
	}
	
	return pBuffer;
}

// Similar to Pack, above.
// Unpack takes the contents of the PackedBuffer and unpacks them into
// the Storable. ASSUMES that the PackedBuffer is the right type for
// the Packer, usually because the Packer is the one who instantiated
// it.  Also assumes that the Storable's actual object type is the
// appropriate one for the data that is sitting in that buffer.
//
bool OTPacker::Unpack(PackedBuffer& inBuf, Storable& outObj)
{
	IStorable * pStorable = dynamic_cast<IStorable *> (&outObj);
	
	if (NULL == pStorable)
		return false;
	
	// --------------------------------
	// outObj is the OUTPUT OBJECT.
	// If we're unable to unpack the contents of inBuf
	// into outObj, return false.
	//
	if (false == pStorable->onUnpack(inBuf, outObj))
	{
		return false;
	}
	
	// ---------------------------
	
	pStorable->hookAfterUnpack(); // Give the subclass a chance to settle its data after unpacking...
	
	return true;	
}


PackedBuffer * OTPacker::Pack(std::string& inObj)
{	
	// This is polymorphic, so we get the right kind of buffer for the packer.
	//
	PackedBuffer * pBuffer = CreateBuffer(); 
	OT_ASSERT(NULL != pBuffer);
	
	// Must delete pBuffer, or return it, below this point.
	// -------------------------------------

	if (false == pBuffer->PackString(inObj))
	{
		delete pBuffer;
		return NULL;
	}
	
	return pBuffer;
}

bool OTPacker::Unpack(PackedBuffer& inBuf, std::string& outObj)
{
	// --------------------------------
	// outObj is the OUTPUT OBJECT.
	// If we're unable to unpack the contents of inBuf
	// into outObj, return false.
	//
	if (false == inBuf.UnpackString(outObj))
		return false;
		
	return true;	
}

// ********************************************************************






// ---------------------------------------------

/*
#define CPPCAT3(X,Y) X##Y
#define CPPCAT2(X,Y)  CPPCAT3(X,Y)
#define CPPCAT(X,Y)  CPPCAT2(X,Y)

#define IMPLEMENT_GET_ADD_REMOVE(scope, name) \
int  scope CPPCAT2(CPPCAT3(Get,name),Count)() { return CPPCAT2(list_,CPPCAT3(name,s)).size() } \
name * scope CPPCAT2(Get,name)(int nIndex) \
{ if ((nIndex >= 0) && (nIndex < CPPCAT(list_,CPPCAT3(name,s)).size())) \
return dynamic_cast<name *>(CPPCAT(list_,CPPCAT3(name,s)).at(nIndex)); return NULL; } \
bool scope CPPCAT3(Remove,name)(int nIndex) \
{ if ((nIndex >= 0) && (nIndex < CPPCAT(list_,CPPCAT3(name,s)).size())) \
{ name * pData = CPPCAT(list_,CPPCAT3(name,s)).at(nIndex); delete pData; \
CPPCAT(list_,CPPCAT3(name,s)).erase(CPPCAT(list_,CPPCAT3(name,s)).begin() + nIndex); return true; } return false; } \
bool scope CPPCAT3(Add,name)(name & theDataObject) { CPPCAT(list_,CPPCAT3(name,s)).push_back(&theDataObject); return true; }
*/
	
#define IMPLEMENT_GET_ADD_REMOVE(scope, name) \
size_t  scope Get##name##Count() { return list_##name##s.size(); } \
name * scope Get##name(size_t nIndex) \
{ if ((nIndex >= 0) && (nIndex < list_##name##s.size())) \
return dynamic_cast<name *>(list_##name##s.at(nIndex)); return NULL; } \
bool scope Remove##name(size_t nIndex) \
{ if ((nIndex >= 0) && (nIndex < list_##name##s.size())) \
{ name * pData = list_##name##s.at(nIndex); delete pData; \
list_##name##s.erase(list_##name##s.begin() + nIndex); return true; } return false; } \
bool scope Add##name(name & disownObject) { list_##name##s.push_back(&disownObject); return true; }




IMPLEMENT_GET_ADD_REMOVE(WalletData::, BitcoinServer)   // No semicolon on this one!

IMPLEMENT_GET_ADD_REMOVE(WalletData::, BitcoinAcct)   // No semicolon on this one!
	
IMPLEMENT_GET_ADD_REMOVE(ContactNym::, ServerInfo)   // No semicolon on this one!

IMPLEMENT_GET_ADD_REMOVE(Contact::, ContactNym)   // No semicolon on this one!

IMPLEMENT_GET_ADD_REMOVE(Contact::, ContactAcct)   // No semicolon on this one!

IMPLEMENT_GET_ADD_REMOVE(AddressBook::, Contact)   // No semicolon on this one!
	


// Make sure SWIG "loses ownership" of any objects pushed onto these lists.
// (So I am safe to destruct them indiscriminately.)

WalletData::~WalletData()
{
	while (GetBitcoinServerCount() > 0)
		RemoveBitcoinServer(0);
	
	while (GetBitcoinAcctCount() > 0)
		RemoveBitcoinAcct(0);
}

// ----------------------------------------------



ContactNym::~ContactNym()
{
	while (GetServerInfoCount() > 0)
		RemoveServerInfo(0);
}

// ----------------------------------------------

Contact::~Contact()
{
	while (GetContactNymCount() > 0)
		RemoveContactNym(0);
	
	while (GetContactAcctCount() > 0)
		RemoveContactAcct(0);
}

// ----------------------------------------------



AddressBook::~AddressBook()
{
	while (GetContactCount() > 0)
		RemoveContact(0);
}

// ----------------------------------------------

	
	
	
	
	



// ********************************************************************
//
// Interface:  IStorableMsgpack
//
//
// Msgpack packer.
#if defined (OTDB_MESSAGE_PACK)

bool IStorableMsgpack::onPack(PackedBuffer& theBuffer, Storable& inObj)  // buffer is OUTPUT, Storable is INPUT.
{
	// check here to make sure theBuffer is the right TYPE.
	BufferMsgpack * pBuffer = dynamic_cast<BufferMsgpack *> (&theBuffer);
	
	if (NULL == pBuffer) // Buffer is wrong type!!
		return false;
	
	/*
	 TEST(pack, BitcoinAcct)
	 {
	 msgpack::sbuffer sbuf;
	 myclass m(1, "msgpack");
	 msgpack::pack(sbuf, m);
	 }
	 */
	bool bSuccess = PerformPack(*pBuffer);
	
//	msgpack::pack(pBuffer->m_buffer, *this);
//	msgpack::pack(pBuffer->m_buffer, inObj);

	return bSuccess;
}

bool IStorableMsgpack::onUnpack(PackedBuffer& theBuffer, Storable& outObj) // buffer is INPUT, Storable is OUTPUT.
{
	// check here to make sure theBuffer is the right TYPE.
	BufferMsgpack * pBuffer = dynamic_cast<BufferMsgpack *> (&theBuffer);
	
	if (NULL == pBuffer) // Buffer is wrong type!!
		return false;
	
	// --------------------
	/* 
	 TEST(unpack, BitcoinAcct)
	 {
	 msgpack::sbuffer sbuf;
	 myclass m1(1, "phraser");
	 msgpack::pack(sbuf, m1);
	 
	 msgpack::zone z;
	 msgpack::object obj;
	 
	 msgpack::unpack_return ret =
	 msgpack::unpack(sbuf.data(), sbuf.size(), NULL, &z, &obj);
	 
	 EXPECT_EQ(ret, msgpack::UNPACK_SUCCESS);
	 
	 myclass m2 = obj.as<myclass>();
	 EXPECT_EQ(m1.num, m2.num);
	 EXPECT_EQ(m1.str, m2.str);
	 }
	 */
	
	bool bSuccess = PerformUnpack(*pBuffer);

	/*
	msgpack::zone z;
	msgpack::object obj;
	
	msgpack::unpack_return ret = msgpack::unpack(pBuffer->m_buffer.data(), 
												 pBuffer->m_buffer.size(), NULL, &z, &obj);
	
	if (msgpack::UNPACK_SUCCESS == ret)
	{	
		obj.convert(this);
//		obj.convert(&outObj);
		
		return true;
	}
	*/
	
	return bSuccess;
}


bool BufferMsgpack::PackString(std::string& theString)
{
	MsgpackStringWrapper theWrapper(theString);
	
	msgpack::pack(m_buffer, theWrapper);
	
	return true;
}

bool BufferMsgpack::UnpackString(std::string& theString)
{
	msgpack::zone z;
	msgpack::object obj;
	
	msgpack::unpack_return ret = 
		msgpack::unpack(m_buffer.data(), m_buffer.size(), NULL, &z, &obj);
	
	if (msgpack::UNPACK_SUCCESS == ret)
	{	
		MsgpackStringWrapper theWrapper;
		
		obj.convert(&theWrapper);
		
		theString = theWrapper.s;
		
		return true;
	}
	
	return false;	
}

bool BufferMsgpack::ReadFromIStream(std::istream &inStream, long lFilesize)
{
	char * buf = new char[lFilesize];
	OT_ASSERT(NULL != buf);
	
	inStream.read(buf, lFilesize);
	
	if (inStream.good())
	{
		m_buffer.clear();
		m_buffer.write(buf, lFilesize);
		
		delete [] buf;
		return true;
	}
	
	delete [] buf;
	
	return false;
}

bool BufferMsgpack::WriteToOStream(std::ostream &outStream)
{
//	std::string strTemp;
//	strTemp.insert(0, m_buffer.data(), m_buffer.size());
//	
//	outStream << strTemp << std::flush;
	
	outStream.write(m_buffer.data(), m_buffer.size());
	
	bool bSuccess = outStream.good() ? true : false;
	
	return bSuccess;
}

	
	
	
void ContactNymMsgpack::hookBeforePack()
{
	// ----------------------------------------------------
	// ServerInfo
	//
	deque_ServerInfos.clear(); 
	
	// Loop through all the objects in the list, and add them to deque_ServerInfos.
	//
	for (std::deque<ServerInfo *>::iterator ii = list_ServerInfos.begin(); ii != list_ServerInfos.end(); ++ii)
	{
		ServerInfoMsgpack * pObject = dynamic_cast<ServerInfoMsgpack *>(*ii);
		
		if (NULL == pObject)
			continue;
		
		deque_ServerInfos.push_back(*pObject); // The deque acquires its own copy here, due to the default assignment operator.
	}
	// ----------------------------------------------------		
}

void ContactNymMsgpack::hookAfterUnpack() 
{ 
	while (GetServerInfoCount() > 0)
		RemoveServerInfo(0);
	
	// ---------------------------------
	for (std::deque<ServerInfoMsgpack>::iterator ii = deque_ServerInfos.begin(); ii != deque_ServerInfos.end(); ++ii)
	{		
		ServerInfoMsgpack * pNewWrapper = dynamic_cast<ServerInfoMsgpack *>(Storable::Create(STORED_OBJ_SERVER_INFO, PACK_MESSAGE_PACK));
		OT_ASSERT(NULL != pNewWrapper);
		
		(*pNewWrapper) = (*ii);  // COPYING THE DATA
		
		list_ServerInfos.push_back(dynamic_cast<ServerInfo*>(pNewWrapper));
	}
	// ---------------------------------
}

// ----------------------------------------------

void ContactMsgpack::hookBeforePack()
{
	// ----------------------------------------------------
	// ContactNym
	//
	deque_Nyms.clear(); 
	
	// Loop through all the objects in the list, and add them to deque_Nyms.
	//
	for (std::deque<ContactNym *>::iterator ii = list_ContactNyms.begin(); ii != list_ContactNyms.end(); ++ii)
	{
		ContactNymMsgpack * pObject = dynamic_cast<ContactNymMsgpack *>(*ii);
		
		if (NULL == pObject)
			continue;
		
		deque_Nyms.push_back(*pObject); // The deque acquires its own copy here, due to the default assignment operator.
	}
	// ----------------------------------------------------
	
	
	
	// ----------------------------------------------------
	// ContactAcct
	//
	deque_Accounts.clear(); 
	
	// Loop through all the objects in the deque, and add them to deque_Accounts.
	//
	for (std::deque<ContactAcct *>::iterator ii = list_ContactAccts.begin(); ii != list_ContactAccts.end(); ++ii)
	{
		ContactAcctMsgpack * pObject = dynamic_cast<ContactAcctMsgpack *>(*ii);
		
		if (NULL == pObject)
			continue;
		
		deque_Accounts.push_back(*pObject);
	}
	// ----------------------------------------------------
	
}


void ContactMsgpack::hookAfterUnpack()
{ 
	//	the_map = __pb_obj.the_map();
	
	while (GetContactNymCount() > 0)
		RemoveContactNym(0);
	
	while (GetContactAcctCount() > 0)
		RemoveContactAcct(0);
	
	// ---------------------------------
	for (std::deque<ContactNymMsgpack>::iterator ii = deque_Nyms.begin(); ii != deque_Nyms.end(); ++ii)
	{		
		ContactNymMsgpack * pNewWrapper = dynamic_cast<ContactNymMsgpack *>(Storable::Create(STORED_OBJ_CONTACT_NYM, PACK_MESSAGE_PACK));
		OT_ASSERT(NULL != pNewWrapper);
		
		(*pNewWrapper) = (*ii);  // COPYING THE DATA
		
		list_ContactNyms.push_back(dynamic_cast<ContactNym*>(pNewWrapper));
	}
	
	// ---------------------------------
	
	for (std::deque<ContactAcctMsgpack>::iterator ii = deque_Accounts.begin(); ii != deque_Accounts.end(); ++ii)
	{
		ContactAcctMsgpack * pNewWrapper = dynamic_cast<ContactAcctMsgpack *>(Storable::Create(STORED_OBJ_CONTACT_ACCT, PACK_MESSAGE_PACK));
		OT_ASSERT(NULL != pNewWrapper);
		
		(*pNewWrapper) = (*ii);  // COPYING THE DATA
		
		list_ContactAccts.push_back(dynamic_cast<ContactAcct*>(pNewWrapper));
	}
}

// ----------------------------------------------
	

	
void AddressBookMsgpack::hookBeforePack()
{
	// ----------------------------------------------------
	// Contact
	//
	deque_Contacts.clear(); 
	
	// Loop through all the objects in the list, and add them to deque_Contacts.
	//
	for (std::deque<Contact *>::iterator ii = list_Contacts.begin(); ii != list_Contacts.end(); ++ii)
	{
		ContactMsgpack * pObject = dynamic_cast<ContactMsgpack *>(*ii);
		
		if (NULL == pObject)
			continue;
		
		deque_Contacts.push_back(*pObject); // The deque acquires its own copy here, due to the default assignment operator.
	}
	// ----------------------------------------------------		
}

void AddressBookMsgpack::hookAfterUnpack() 
{ 
	while (GetContactCount() > 0)
		RemoveContact(0);
	
	// ---------------------------------
	for (std::deque<ContactMsgpack>::iterator ii = deque_Contacts.begin(); ii != deque_Contacts.end(); ++ii)
	{		
		ContactMsgpack * pNewWrapper = dynamic_cast<ContactMsgpack *>(Storable::Create(STORED_OBJ_CONTACT, PACK_MESSAGE_PACK));
		OT_ASSERT(NULL != pNewWrapper);
		
		(*pNewWrapper) = (*ii);  // COPYING THE DATA
		
		list_Contacts.push_back(dynamic_cast<Contact*>(pNewWrapper));
	}
	// ---------------------------------
}
	
	
void WalletDataMsgpack::hookBeforePack()
{
	// ----------------------------------------------------
	// BitcoinServer
	//
	deque_BitcoinServers.clear(); 
	
	// Loop through all the objects in the list, and add them to deque_BitcoinServers.
	//
	for (std::deque<BitcoinServer *>::iterator ii = list_BitcoinServers.begin(); ii != list_BitcoinServers.end(); ++ii)
	{
		BitcoinServerMsgpack * pObject = dynamic_cast<BitcoinServerMsgpack *>(*ii);
		
		if (NULL == pObject)
			continue;
		
		deque_BitcoinServers.push_back(*pObject); // The deque acquires its own copy here, due to the default assignment operator.
	}
	// ----------------------------------------------------
	
	
	
	// ----------------------------------------------------
	// BitcoinAcct
	//
	deque_BitcoinAccts.clear(); 
	
	// Loop through all the objects in the deque, and add them to deque_BitcoinAccts.
	//
	for (std::deque<BitcoinAcct *>::iterator ii = list_BitcoinAccts.begin(); ii != list_BitcoinAccts.end(); ++ii)
	{
		BitcoinAcctMsgpack * pObject = dynamic_cast<BitcoinAcctMsgpack *>(*ii);
		
		if (NULL == pObject)
			continue;
				
		deque_BitcoinAccts.push_back(*pObject);
	}
	// ----------------------------------------------------
	
}


void WalletDataMsgpack::hookAfterUnpack()
{ 
	//	the_map = __pb_obj.the_map();
	
	while (GetBitcoinServerCount() > 0)
		RemoveBitcoinServer(0);
	
	while (GetBitcoinAcctCount() > 0)
		RemoveBitcoinAcct(0);
	
	// ---------------------------------
	for (std::deque<BitcoinServerMsgpack>::iterator ii = deque_BitcoinServers.begin(); ii != deque_BitcoinServers.end(); ++ii)
	{		
		BitcoinServerMsgpack * pNewWrapper = dynamic_cast<BitcoinServerMsgpack *>(Storable::Create(STORED_OBJ_BITCOIN_SERVER, PACK_MESSAGE_PACK));
		OT_ASSERT(NULL != pNewWrapper);
				
		(*pNewWrapper) = (*ii);  // COPYING THE DATA
		
		list_BitcoinServers.push_back(dynamic_cast<BitcoinServer*>(pNewWrapper));
	}
	
	// ---------------------------------
	
	for (std::deque<BitcoinAcctMsgpack>::iterator ii = deque_BitcoinAccts.begin(); ii != deque_BitcoinAccts.end(); ++ii)
	{
		BitcoinAcctMsgpack * pNewWrapper = dynamic_cast<BitcoinAcctMsgpack *>(Storable::Create(STORED_OBJ_BITCOIN_ACCT, PACK_MESSAGE_PACK));
		OT_ASSERT(NULL != pNewWrapper);
				
		(*pNewWrapper) = (*ii);  // COPYING THE DATA
		
		list_BitcoinAccts.push_back(dynamic_cast<BitcoinAcct*>(pNewWrapper));
	}
}
	

#endif  // defined (OTDB_MESSAGE_PACK)
// ********************************************************************








// ---------------

/* Protocol Buffers notes.
 
 // optional string bitcoin_id = 1;
 inline bool has_bitcoin_id() const;
 inline void clear_bitcoin_id();
 static const int kBitcoinIdFieldNumber = 1;
 inline const ::std::string& bitcoin_id() const;
 inline void set_bitcoin_id(const ::std::string& value);
 inline void set_bitcoin_id(const char* value);
 inline void set_bitcoin_id(const char* value, size_t size);
 inline ::std::string* mutable_bitcoin_id();
 inline ::std::string* release_bitcoin_id();
 
 // optional string bitcoin_name = 2;
 inline bool has_bitcoin_name() const;
 inline void clear_bitcoin_name();
 static const int kBitcoinNameFieldNumber = 2;
 inline const ::std::string& bitcoin_name() const;
 inline void set_bitcoin_name(const ::std::string& value);
 inline void set_bitcoin_name(const char* value);
 inline void set_bitcoin_name(const char* value, size_t size);
 inline ::std::string* mutable_bitcoin_name();
 inline ::std::string* release_bitcoin_name();
 
 // optional string gui_label = 3;
 inline bool has_gui_label() const;
 inline void clear_gui_label();
 static const int kGuiLabelFieldNumber = 3;
 inline const ::std::string& gui_label() const;
 inline void set_gui_label(const ::std::string& value);
 inline void set_gui_label(const char* value);
 inline void set_gui_label(const char* value, size_t size);
 inline ::std::string* mutable_gui_label();
 inline ::std::string* release_gui_label(); 
 */
/*
 bool SerializeToString(string* output) const; serializes the message and stores the bytes in the given string. 
				(Note that the bytes are binary, not text; we only use the string class as a convenient container.)
 bool ParseFromString(const string& data); parses a message from the given string.
 
 bool SerializeToOstream(ostream* output) const; writes the message to the given C++ ostream.
 bool ParseFromIstream(istream* input); parses a message from the given C++ istream.
 */

// This is a case for template polymorphism.
// See this article:  http://accu.org/index.php/articles/471
//
/*
template <class T>	// TStorable...
class TStorable		// a "template subclass" of Storable. This is like a version of java
{					// interfaces, which C++ normally implements via pure virtual base classes
	T const & t;	// and multiple inheritance. But in this case, I need to have a consistent
public:				// interface across disparate classes (in various circumstances including
	TStorable(T const & obj) : t(obj) { }	// here with protocol buffers) and template interfaces
	bool pack(PackedBuffer& theBuffer)	// allow me to do that even with classes in a different hierarchy.
	{ return t.onPack(theBuffer); }			
};

template <class T> 
TStorable<T> makeTStorable( T& obj )
{
	return TStorable<T>( obj ); 
}
*/

/* // Specialization:
 template<>
 void TStorable<BigBenClock>::talk() 
 {
	t.playBongs(); 
 }
 
 // Passing and returning as parameter:
 
 template <class T> 
 void makeItTalk( TStorable<T> t )
 { 
	t.talk(); 
 }
 
 template <class T> 
 TStorable<T> makeTalkative( T& obj )
 {
	return TStorable<T>( obj ); 
 }
 */

// Why have IStorablePB::onPack? What is this all about?
//
// Because normally, packing is done by Packer. I have a packer subclass for
// the protocol buffers library, but notice that I don't have a packer for EVERY
// SINGLE STORABLE OT OBJECT, for the protocol buffers library. So when Packer::Pack() 
// is called, the subclass being activated is PackerPB, not PackerForBitcoinAccountOnPB.
// 
// With MsgPack, that would be the end of it, since the MsgPack Storables all derive from
// the same base class (due to the msgPack define) and a single call handles all of them.
// But with Protocol Buffers (and probably with custom objects, which are coming next), EACH
// PB-Storable has to wrap an instance of the PB-derived serializable object generated by
// protoc. Each instance thus has a PB member of a slightly different type, and there is no
// common base class between them that will give me a reference to that member, without
// overriding some virtual function IN ALL OF THE PB-SERIALIZABLE OBJECTS so that each can
// individually pass back the reference to its unique PB-derived member.
//
// Even if there were, LET US REMEMBER that all of the various Storables (instantiated for
// various specific packers), such as BitcoinAcctPB for example, are supposed to be derived
// from a data class such as BitcoinAcct. That way, BitcoinAcct can focus on the data itself,
// regardless of packer type, and OT can deal with its data in a pure way, meanwhile the
// actual object used can be one of 5 different subclasses of that, depending on which 
// packer was employed. All of those subclasses (for protocol buffers, for msgpack, for json,
// etc) must be derived from the data class, BitcoinAcct. 
// 
// Remember, if ALL of the protocol-buffers wrapper classes, such as BitcoinAcctPB,
// BitcoinServerPB, LoomAcctPB, LoomServerPB, etc, are all derived from some StorablePB object,
// so they can all share a virtual function and thereby return a reference to their internally-
// wrapped object, then how are all of those classes supposed to ALSO be derived from their
// DATA classes, such as BitcoinAcct, BitcoinServer, LoomAcct, LoomServer, etc??
//
// The answer is multiple inheritance. Or INTERFACES, to be more specific. I have implemented
// Java-style interfaces as well as polymorphism-by-template to resolve these issues.
//
// The Storable (parameter to Pack) is actually the object that somehow has to
// override--or implement--the actual packing. Only it really knows. Therefore I have decided
// to add an INTERFACE, which is OPTIONAL, which makes it possible to hook and override the
// packing/unpacking, but such that things are otherwise handled in a broad stroke, without
// having to override EVERY LITTLE THING to accomplish it.
//
// Storables, as I said, will all be derived from their respective data objects, no matter
// which packer is being employed. When packing one, the framework will check to see if IStorable
// is present. It it is, then the framework will use it instead of continuing with the normal
// Pack procedure. It will also call the hook (first) so values can be copied where appropriate,
// before the actual packing occurs, or after (for unpacking.)
//
// This means, first, that few of the storables will ever actually have to override Pack() or
// Unpack(), as long as they override onPack() as necessary. AND, when onPack() IS overridden,
// it will be able to handle many different objects (via the Interface, templates, etc), instead
// of each having to provide a separate Pack() implementation for EVERY SINGLE PB object. For
// example, the IStorablePB interface handles ALL of the PB objects, without ANY of them having
// to override some special pack function.
//
// It WOULD have been possible to add this interface to Storable itself. Functions such as 
// Pack(), Unpack(), hookBeforePack(), onPack(), etc could have been added there and then passed
// down to all the subclasses. But that is not as elegant, for these reasons:
// 1) Remember that BitcoinAcct is purely data-oriented, and is not a packing-related class.
//    (though its subclasses are.) So the members would be out of context, except for some lame
//    explanation that the subclasses use them for other purposes unrelated to this class.
// 2) EVERY SINGLE class would be forced to provide its own implementation of those functions,
//    since a common base class for groups of them is already discounted, since they are derived
//    from their data classes, not their packer classes.
//
//
//
//
//
//
// Interface:	IStorablePB
//
// --------------------------------------------
// Protocol Buffers packer.
#if defined (OTDB_PROTOCOL_BUFFERS)

	
	
::google::protobuf::Message * IStorablePB::getPBMessage() // This is really only here so it can be overridden. Only subclasses of IStorablePB will actually exist.
{ 
	return NULL; 
}

template<class theBaseType, class theInternalType>
::google::protobuf::Message * ProtobufSubclass<theBaseType, theInternalType>::getPBMessage() 
{ 
	return (&__pb_obj); 
}
	
	
//	if (false == makeTStorable(*pStorable).pack(*pBuffer))
//::google::protobuf::Message	&	IStorablePB::getPBMessage() 
//{
//	return makeTStorablePB(*this).getPBMessage();
//}

bool IStorablePB::onPack(PackedBuffer& theBuffer, Storable& inObj)  // buffer is OUTPUT.
{
	// check here to make sure theBuffer is the right TYPE.
	BufferPB * pBuffer = dynamic_cast<BufferPB *> (&theBuffer);
	
	if (NULL == pBuffer) // Buffer is wrong type!!
		return false;
	
	::google::protobuf::Message * pMessage = getPBMessage();
	
	if (NULL == pMessage)
		return false;
	
	if (false == pMessage->SerializeToString(&(pBuffer->m_buffer)))
		return false;
	
	return true;
}

bool IStorablePB::onUnpack(PackedBuffer& theBuffer, Storable& outObj) // buffer is INPUT.
{
	// check here to make sure theBuffer is the right TYPE.
	BufferPB * pBuffer = dynamic_cast<BufferPB *> (&theBuffer);
	
	if (NULL == pBuffer) // Buffer is wrong type!!
		return false;
	
	::google::protobuf::Message * pMessage = getPBMessage();
	
	if (NULL == pMessage)
		return false;

	if (false == pMessage->ParseFromString(pBuffer->m_buffer))
		return false;
	
	return true;
}



/*
 bool SerializeToString(string* output) const;: 
	Serializes the message and stores the bytes in the given string. Note that the bytes are binary, 
 not text; we only use the string class as a convenient container.
 
 bool ParseFromString(const string& data);: 
	parses a message from the given string.
 */
bool BufferPB::PackString(std::string& theString)
{
	StringPB theWrapper;
	
	::google::protobuf::Message * pMessage = theWrapper.getPBMessage();
	
	if (NULL == pMessage)
		return false;
	
	// ------------
	
	String_InternalPB * pBuffer = dynamic_cast<String_InternalPB *> (pMessage);
	
	if (NULL == pBuffer) // Buffer is wrong type!!
		return false;

	// ------------
	
	pBuffer->set_value(theString);
	
	if (false == pBuffer->SerializeToString(&m_buffer))
		return false;
	
	return true;
}

bool BufferPB::UnpackString(std::string& theString)
{
	StringPB theWrapper;
	
	::google::protobuf::Message * pMessage = theWrapper.getPBMessage();
	
	if (NULL == pMessage)
		return false;
		
	// ------------
	
	String_InternalPB * pBuffer = dynamic_cast<String_InternalPB *> (pMessage);
	
	if (NULL == pBuffer) // Buffer is wrong type!!
		return false;
	
	// ------------

	if (false == pBuffer->ParseFromString(m_buffer))
		return false;
	
	// ------------
	
	theString = pBuffer->value();
	
	return true;
}


bool BufferPB::ReadFromIStream(std::istream& inStream, long lFilesize)
{
	//bool	ParseFromIstream(istream * input)
	char * buf = new char[lFilesize];
	OT_ASSERT(NULL != buf);
	
	inStream.read(buf, lFilesize);
	
	if (inStream.good())
	{
		m_buffer.assign(buf, lFilesize);
		delete [] buf;
		return true;
	}
	 
	delete [] buf;

	return false;
	
	//m_buffer.ParseFromIstream(&inStream);
}

bool BufferPB::WriteToOStream(std::ostream &outStream)
{
	// bool	SerializeToOstream(ostream * output) const
	
	if (m_buffer.length() > 0)
	{
		outStream.write(m_buffer.data(), m_buffer.length());		
		return outStream.good() ? true : false;
	}
	
	return false;
	//m_buffer.SerializeToOstream(&outStream);
}

// !! All of these have to provide implementations for the hookBeforePack and hookAfterUnpack methods.
// In .cpp file:
/*
 void SUBCLASS_HERE::hookBeforePack()
 {
	__pb_obj.set_PROPERTY_NAME_GOES_HERE(PROPERTY_NAME_GOES_HERE); 
 }
 void SUBCLASS_HERE::hookAfterUnpack()
 { 
	PROPERTY_NAME_GOES_HERE	= __pb_obj.PROPERTY_NAME_GOES_HERE();
 }
 */
//
	


template<> 
void WalletDataPB::hookBeforePack()
{
	// ----------------------------------------------------
	// BitcoinServer
	//
	__pb_obj.clear_bitcoin_server(); // "bitcoin_server" is the repeated field of BitcoinServers. 
	
	// Loop through all the objects in the deque, and add them to __pb_obj.bitcoin_server.
	//
	for (std::deque<BitcoinServer *>::iterator ii = list_BitcoinServers.begin(); ii != list_BitcoinServers.end(); ++ii)
	{
		BitcoinServerPB * pObject = dynamic_cast<BitcoinServerPB *>(*ii);
		
		if (NULL == pObject)
			continue;

		::google::protobuf::Message * pMessage = pObject->getPBMessage();
				
		if (NULL == pMessage)
			continue;
		
		// Now theMessage contains the BitcoinServer_InternalPB from the list...
		// -----------------------
		
		BitcoinServer_InternalPB * pInternal = dynamic_cast<BitcoinServer_InternalPB *>(pMessage);
		
		if (NULL == pInternal)
			continue;
		
		// -----------------------
		
		BitcoinServer_InternalPB * pNewInternal = __pb_obj.add_bitcoin_server();
		
		(*pNewInternal) = (*pInternal);  // HERE IS THE COPY. Now the serialized object corresponds to the list object.
	}
	// ----------------------------------------------------
	
	
	
	// ----------------------------------------------------
	// BitcoinAcct
	//
	__pb_obj.clear_bitcoin_acct(); // "bitcoin_acct" is the repeated field of BitcoinAccts. 
	
	// Loop through all the objects in the deque, and add them to __pb_obj.bitcoin_acct.
	//
	for (std::deque<BitcoinAcct *>::iterator ii = list_BitcoinAccts.begin(); ii != list_BitcoinAccts.end(); ++ii)
	{
		BitcoinAcctPB * pObject = dynamic_cast<BitcoinAcctPB *>(*ii);
		
		if (NULL == pObject)
			continue;
		
		::google::protobuf::Message * pMessage = pObject->getPBMessage();
		
		if (NULL == pMessage)
			continue;
				
		// Now theMessage contains the BitcoinAcct_InternalPB from the list...
		// -----------------------
		
		BitcoinAcct_InternalPB * pInternal = dynamic_cast<BitcoinAcct_InternalPB *>(pMessage);
		
		if (NULL == pInternal)
			continue;		
		// -----------------------
		
		BitcoinAcct_InternalPB * pNewInternal = __pb_obj.add_bitcoin_acct();
		
		(*pNewInternal) = (*pInternal);  // HERE IS THE COPY. Now the serialized object corresponds to the list object.
	}
	// ----------------------------------------------------
	
	// Now when __pb_obj is serialized, it's up to date!	
}

template<> 
void WalletDataPB::hookAfterUnpack()
{ 
	//	the_map = __pb_obj.the_map();
	
	while (GetBitcoinServerCount() > 0)
		RemoveBitcoinServer(0);
	
	while (GetBitcoinAcctCount() > 0)
		RemoveBitcoinAcct(0);

	// ---------------------------------
	
	for (int i = 0; i < __pb_obj.bitcoin_server_size(); i++)
	{
		const BitcoinServer_InternalPB & theInternal = __pb_obj.bitcoin_server(i);
		// theInternal contains the internal data I want to copy to the list. (deque)
		
		BitcoinServerPB * pNewWrapper = dynamic_cast<BitcoinServerPB *>(Storable::Create(STORED_OBJ_BITCOIN_SERVER, PACK_PROTOCOL_BUFFERS));
		OT_ASSERT(NULL != pNewWrapper);
		
		::google::protobuf::Message * pMessage = pNewWrapper->getPBMessage();
		
		if (NULL == pMessage)
		{
			delete pNewWrapper;
			continue;	
		}
		
		// Now theMessage contains the BitcoinServer_InternalPB for the new object we just created.... (and wish to populate)
		// -----------------------
		
		BitcoinServer_InternalPB * pInternal = dynamic_cast<BitcoinServer_InternalPB *>(pMessage);
		
		if (NULL == pInternal)
		{
			delete pNewWrapper;
			continue;	
		}
		
		// now pInternal is the new object's BitcoinServer_InternalPB, and theInternal is 
		// the __pb_obj data I want... nothing to do now but copy it over...
		
		(*pInternal) = theInternal;  // COPYING THE DATA
		
		list_BitcoinServers.push_back(dynamic_cast<BitcoinServer*>(pNewWrapper));
	}
	
	// ---------------------------------
	
	for (int i = 0; i < __pb_obj.bitcoin_acct_size(); i++)
	{
		const BitcoinAcct_InternalPB & theInternal = __pb_obj.bitcoin_acct(i);
		// theInternal contains the internal data I want to copy to the list. (deque)
		
		BitcoinAcctPB * pNewWrapper = dynamic_cast<BitcoinAcctPB *>(Storable::Create(STORED_OBJ_BITCOIN_ACCT, PACK_PROTOCOL_BUFFERS));
		OT_ASSERT(NULL != pNewWrapper);
		
		::google::protobuf::Message * pMessage = pNewWrapper->getPBMessage();
		
		if (NULL == pMessage)
		{
			delete pNewWrapper;
			continue;	
		}
		
		// Now theMessage contains the BitcoinAcct_InternalPB for the new object we just created.... (and wish to populate)
		// -----------------------
		
		BitcoinAcct_InternalPB * pInternal = dynamic_cast<BitcoinAcct_InternalPB *>(pMessage);
		
		if (NULL == pInternal)
		{
			delete pNewWrapper;
			continue;	
		}
		
		// now pInternal is the new object's BitcoinAcct_InternalPB, and theInternal is 
		// the __pb_obj data I want... nothing to do now but copy it over...
		
		(*pInternal) = theInternal;  // COPYING THE DATA
		
		list_BitcoinAccts.push_back(dynamic_cast<BitcoinAcct*>(pNewWrapper));
	}
}
// ---------------------------------------------

template<> 
void StringMapPB::hookBeforePack()
{
	__pb_obj.clear_node(); // "node" is the repeated field of Key/Values. 
	
	// Loop through all the key/value pairs in the map, and add them to __pb_obj.node.
	//
	for (std::map<std::string, std::string>::iterator ii = the_map.begin(); ii != the_map.end(); ++ii)
	{
		KeyValue_InternalPB * pNode = __pb_obj.add_node();
		pNode->set_key((*ii).first);
		pNode->set_value((*ii).second);
	}
}

template<> 
void StringMapPB::hookAfterUnpack()
{ 
	//	the_map = __pb_obj.the_map();
	
	the_map.clear();
	
	for (int i = 0; i < __pb_obj.node_size(); i++)
	{
		const KeyValue_InternalPB & theNode = __pb_obj.node(i);
		
		the_map.insert ( std::pair<std::string,std::string>(theNode.key(), theNode.value()) );
	}
}
// ---------------------------------------------

	
template<> 
void StringPB::hookBeforePack()
{
	// The way StringPB is used, this function will never actually get called.
}
template<> 
void StringPB::hookAfterUnpack()
{ 
	// The way StringPB is used, this function will never actually get called.
}
// ---------------------------------------------
	
	
template<> 
void ContactPB::hookBeforePack()
{
	__pb_obj.set_gui_label(gui_label); 
	__pb_obj.set_email(email); 
	__pb_obj.set_public_key(public_key); 
	__pb_obj.set_memo(memo); 

	// ----------------------------------------------------
	// ContactNym
	//
	__pb_obj.clear_nyms(); // "nyms" is the repeated field of ContactNyms. 
	
	// Loop through all the objects in the deque, and add them to __pb_obj.nyms.
	//
	for (std::deque<ContactNym *>::iterator ii = list_ContactNyms.begin(); ii != list_ContactNyms.end(); ++ii)
	{
		ContactNymPB * pObject = dynamic_cast<ContactNymPB *>(*ii);
		
		if (NULL == pObject)
			continue;
		
		::google::protobuf::Message * pMessage = pObject->getPBMessage();
		
		if (NULL == pMessage)
			continue;
		
		// Now theMessage contains the ContactNym_InternalPB from the list...
		// -----------------------
		
		ContactNym_InternalPB * pInternal = dynamic_cast<ContactNym_InternalPB *>(pMessage);
		
		if (NULL == pInternal)
			continue;
		
		// -----------------------
		
		ContactNym_InternalPB * pNewInternal = __pb_obj.add_nyms();
		
		(*pNewInternal) = (*pInternal);  // HERE IS THE COPY. Now the serialized object corresponds to the list object.
	}
	// ----------------------------------------------------
	
	
	
	// ----------------------------------------------------
	// ContactAcct
	//
	__pb_obj.clear_accounts(); // "accounts" is the repeated field of ContactAccts. 
	
	// Loop through all the objects in the deque, and add them to __pb_obj.accounts.
	//
	for (std::deque<ContactAcct *>::iterator ii = list_ContactAccts.begin(); ii != list_ContactAccts.end(); ++ii)
	{
		ContactAcctPB * pObject = dynamic_cast<ContactAcctPB *>(*ii);
		
		if (NULL == pObject)
			continue;
		
		::google::protobuf::Message * pMessage = pObject->getPBMessage();
		
		if (NULL == pMessage)
			continue;
		
		// Now theMessage contains the ContactAcct_InternalPB from the list...
		// -----------------------
		
		ContactAcct_InternalPB * pInternal = dynamic_cast<ContactAcct_InternalPB *>(pMessage);
		
		if (NULL == pInternal)
			continue;		
		// -----------------------
		
		ContactAcct_InternalPB * pNewInternal = __pb_obj.add_accounts();
		
		(*pNewInternal) = (*pInternal);  // HERE IS THE COPY. Now the serialized object corresponds to the list object.
	}
	// ----------------------------------------------------
	
	// Now when __pb_obj is serialized, it's up to date!	
}

template<> 
void ContactPB::hookAfterUnpack()
{ 	
	gui_label = __pb_obj.gui_label();
	email = __pb_obj.email();
	public_key = __pb_obj.public_key();
	memo = __pb_obj.memo();

	// ---------------------------------

	while (GetContactNymCount() > 0)
		RemoveContactNym(0);
	
	while (GetContactAcctCount() > 0)
		RemoveContactAcct(0);
	
	// ---------------------------------
	
	for (int i = 0; i < __pb_obj.nyms_size(); i++)
	{
		const ContactNym_InternalPB & theInternal = __pb_obj.nyms(i);
		// theInternal contains the internal data I want to copy to the list. (deque)
		
		ContactNymPB * pNewWrapper = dynamic_cast<ContactNymPB *>(Storable::Create(STORED_OBJ_CONTACT_NYM, PACK_PROTOCOL_BUFFERS));
		OT_ASSERT(NULL != pNewWrapper);
		
		::google::protobuf::Message * pMessage = pNewWrapper->getPBMessage();
		
		if (NULL == pMessage)
		{
			delete pNewWrapper;
			continue;	
		}
		
		// Now theMessage contains the ContactNym_InternalPB for the new object we just created.... (and wish to populate)
		// -----------------------
		
		ContactNym_InternalPB * pInternal = dynamic_cast<ContactNym_InternalPB *>(pMessage);
		
		if (NULL == pInternal)
		{
			delete pNewWrapper;
			continue;	
		}
		
		// now pInternal is the new object's ContactNym_InternalPB, and theInternal is 
		// the __pb_obj data I want... nothing to do now but copy it over...
		
		(*pInternal) = theInternal;  // COPYING THE DATA
		
		list_ContactNyms.push_back(dynamic_cast<ContactNym*>(pNewWrapper));
	}
	
	// ---------------------------------
	
	for (int i = 0; i < __pb_obj.accounts_size(); i++)
	{
		const ContactAcct_InternalPB & theInternal = __pb_obj.accounts(i);
		// theInternal contains the internal data I want to copy to the list. (deque)
		
		ContactAcctPB * pNewWrapper = dynamic_cast<ContactAcctPB *>(Storable::Create(STORED_OBJ_CONTACT_ACCT, PACK_PROTOCOL_BUFFERS));
		OT_ASSERT(NULL != pNewWrapper);
		
		::google::protobuf::Message * pMessage = pNewWrapper->getPBMessage();
		
		if (NULL == pMessage)
		{
			delete pNewWrapper;
			continue;	
		}
		
		// Now theMessage contains the ContactAcct_InternalPB for the new object we just created.... (and wish to populate)
		// -----------------------
		
		ContactAcct_InternalPB * pInternal = dynamic_cast<ContactAcct_InternalPB *>(pMessage);
		
		if (NULL == pInternal)
		{
			delete pNewWrapper;
			continue;	
		}
		
		// now pInternal is the new object's ContactAcct_InternalPB, and theInternal is 
		// the __pb_obj data I want... nothing to do now but copy it over...
		
		(*pInternal) = theInternal;  // COPYING THE DATA
		
		list_ContactAccts.push_back(dynamic_cast<ContactAcct*>(pNewWrapper));
	}
}
// ---------------------------------------------


	
template<> 
void ContactNymPB::hookBeforePack()
{
	__pb_obj.set_gui_label(gui_label); 
	__pb_obj.set_nym_id(nym_id); 
	__pb_obj.set_nym_type(nym_type); 
	__pb_obj.set_public_key(public_key); 
	__pb_obj.set_memo(memo); 

	// ----------------------------------------------------
	// ServerInfo
	//
	__pb_obj.clear_servers(); // "servers" is the repeated field of ServerInfos. 
	
	// Loop through all the objects in the deque, and add them to __pb_obj.servers.
	//
	for (std::deque<ServerInfo *>::iterator ii = list_ServerInfos.begin(); ii != list_ServerInfos.end(); ++ii)
	{
		ServerInfoPB * pObject = dynamic_cast<ServerInfoPB *>(*ii);
		
		if (NULL == pObject)
			continue;
		
		::google::protobuf::Message * pMessage = pObject->getPBMessage();
		
		if (NULL == pMessage)
			continue;
		
		// Now theMessage contains the ServerInfo_InternalPB from the list...
		// -----------------------
		
		ServerInfo_InternalPB * pInternal = dynamic_cast<ServerInfo_InternalPB *>(pMessage);
		
		if (NULL == pInternal)
			continue;
		
		// -----------------------
		
		ServerInfo_InternalPB * pNewInternal = __pb_obj.add_servers();
		
		(*pNewInternal) = (*pInternal);  // HERE IS THE COPY. Now the serialized object corresponds to the list object.
	}
	// ----------------------------------------------------
		// Now when __pb_obj is serialized, it's up to date!	
}

template<> 
void ContactNymPB::hookAfterUnpack()
{ 
	gui_label = __pb_obj.gui_label();
	nym_id = __pb_obj.nym_id();
	nym_type = __pb_obj.nym_type();
	public_key = __pb_obj.public_key();
	memo = __pb_obj.memo();
	
	while (GetServerInfoCount() > 0)
		RemoveServerInfo(0);
	
	// ---------------------------------
	
	for (int i = 0; i < __pb_obj.servers_size(); i++)
	{
		const ServerInfo_InternalPB & theInternal = __pb_obj.servers(i);
		// theInternal contains the internal data I want to copy to the list. (deque)
		
		ServerInfoPB * pNewWrapper = dynamic_cast<ServerInfoPB *>(Storable::Create(STORED_OBJ_SERVER_INFO, PACK_PROTOCOL_BUFFERS));
		OT_ASSERT(NULL != pNewWrapper);
		
		::google::protobuf::Message * pMessage = pNewWrapper->getPBMessage();
		
		if (NULL == pMessage)
		{
			delete pNewWrapper;
			continue;	
		}
		
		// Now theMessage contains the ServerInfo_InternalPB for the new object we just created.... (and wish to populate)
		// -----------------------
		
		ServerInfo_InternalPB * pInternal = dynamic_cast<ServerInfo_InternalPB *>(pMessage);
		
		if (NULL == pInternal)
		{
			delete pNewWrapper;
			continue;	
		}
		
		// now pInternal is the new object's ServerInfo_InternalPB, and theInternal is 
		// the __pb_obj data I want... nothing to do now but copy it over...
		
		(*pInternal) = theInternal;  // COPYING THE DATA
		
		list_ServerInfos.push_back(dynamic_cast<ServerInfo*>(pNewWrapper));
	}
}
// ---------------------------------------------
	
	
	


template<> 
void AddressBookPB::hookBeforePack()
{
	// ----------------------------------------------------
	// Contact
	//
	__pb_obj.clear_contacts(); // "contacts" is the repeated field of Contacts. 
	
	// Loop through all the objects in the deque, and add them to __pb_obj.contacts.
	//
	for (std::deque<Contact *>::iterator ii = list_Contacts.begin(); ii != list_Contacts.end(); ++ii)
	{
		ContactPB * pObject = dynamic_cast<ContactPB *>(*ii);
		
		if (NULL == pObject)
			continue;
		
		::google::protobuf::Message * pMessage = pObject->getPBMessage();
		
		if (NULL == pMessage)
			continue;
		
		// Now theMessage contains the Contact_InternalPB from the list...
		// -----------------------
		
		Contact_InternalPB * pInternal = dynamic_cast<Contact_InternalPB *>(pMessage);
		
		if (NULL == pInternal)
			continue;
		
		// -----------------------
		
		Contact_InternalPB * pNewInternal = __pb_obj.add_contacts();
		
		(*pNewInternal) = (*pInternal);  // HERE IS THE COPY. Now the serialized object corresponds to the list object.
	}
	// ----------------------------------------------------
	// Now when __pb_obj is serialized, it's up to date!	
}

template<> 
void AddressBookPB::hookAfterUnpack()
{ 
	//	the_map = __pb_obj.the_map();
	
	while (GetContactCount() > 0)
		RemoveContact(0);
	
	// ---------------------------------
	
	for (int i = 0; i < __pb_obj.contacts_size(); i++)
	{
		const Contact_InternalPB & theInternal = __pb_obj.contacts(i);
		// theInternal contains the internal data I want to copy to the list. (deque)
		
		ContactPB * pNewWrapper = dynamic_cast<ContactPB *>(Storable::Create(STORED_OBJ_CONTACT, PACK_PROTOCOL_BUFFERS));
		OT_ASSERT(NULL != pNewWrapper);
		
		::google::protobuf::Message * pMessage = pNewWrapper->getPBMessage();
		
		if (NULL == pMessage)
		{
			delete pNewWrapper;
			continue;	
		}
		
		// Now theMessage contains the Contact_InternalPB for the new object we just created.... (and wish to populate)
		// -----------------------
		
		Contact_InternalPB * pInternal = dynamic_cast<Contact_InternalPB *>(pMessage);
		
		if (NULL == pInternal)
		{
			delete pNewWrapper;
			continue;	
		}
		
		// now pInternal is the new object's Contact_InternalPB, and theInternal is 
		// the __pb_obj data I want... nothing to do now but copy it over...
		
		(*pInternal) = theInternal;  // COPYING THE DATA
		
		list_Contacts.push_back(dynamic_cast<Contact*>(pNewWrapper));
	}
}
// ---------------------------------------------
	
template<> 
void ContactAcctPB::hookBeforePack()
{
	__pb_obj.set_gui_label(gui_label); 
	__pb_obj.set_server_id(server_id); 
	__pb_obj.set_server_type(server_type); 
	__pb_obj.set_asset_type_id(asset_type_id); 
	__pb_obj.set_acct_id(acct_id); 
	__pb_obj.set_nym_id(nym_id); 
	__pb_obj.set_memo(memo); 
	__pb_obj.set_public_key(public_key); 
}
template<> 
void ContactAcctPB::hookAfterUnpack()
{ 
	gui_label = __pb_obj.gui_label();
	server_id = __pb_obj.server_id();
	server_type = __pb_obj.server_type();
	asset_type_id = __pb_obj.asset_type_id();
	acct_id = __pb_obj.acct_id();
	nym_id = __pb_obj.nym_id();
	memo = __pb_obj.memo();
	public_key = __pb_obj.public_key();
}
// ---------------------------------------------

template<> 
void ServerInfoPB::hookBeforePack()
{
	__pb_obj.set_server_id(server_id); 
	__pb_obj.set_server_type(server_type); 
}
template<> 
void ServerInfoPB::hookAfterUnpack()
{ 
	server_id = __pb_obj.server_id();
	server_type = __pb_obj.server_type();
}
// ---------------------------------------------
	
template<> 
void BitcoinAcctPB::hookBeforePack()
{
	__pb_obj.set_gui_label(gui_label); 
	__pb_obj.set_acct_id(acct_id); 
	__pb_obj.set_server_id(server_id); 
	__pb_obj.set_bitcoin_acct_name(bitcoin_acct_name); 
}
template<> 
void BitcoinAcctPB::hookAfterUnpack()
{ 
	gui_label = __pb_obj.gui_label();
	acct_id = __pb_obj.acct_id();
	server_id = __pb_obj.server_id();
	bitcoin_acct_name = __pb_obj.bitcoin_acct_name();
}
// ---------------------------------------------
	
template<> 
void BitcoinServerPB::hookBeforePack()
{
	__pb_obj.set_gui_label(gui_label); 
	__pb_obj.set_server_id(server_id); 
	__pb_obj.set_server_type(server_type); 
	__pb_obj.set_server_host(server_host); 
	__pb_obj.set_server_port(server_port); 
	__pb_obj.set_bitcoin_username(bitcoin_username); 
	__pb_obj.set_bitcoin_password(bitcoin_password); 
}
template<> 
void BitcoinServerPB::hookAfterUnpack()
{ 
	gui_label = __pb_obj.gui_label();
	server_id = __pb_obj.server_id();
	server_type = __pb_obj.server_type();
	server_host = __pb_obj.server_host();
	server_port = __pb_obj.server_port();
	bitcoin_username = __pb_obj.bitcoin_username();
	bitcoin_password = __pb_obj.bitcoin_password();
}
// ---------------------------------------------

#endif // defined (OTDB_PROTOCOL_BUFFERS)
// ********************************************************************













// ********************************************************************
//
// STORAGE :: GetPacker
//
// Use this to access the OTPacker, throughout duration of this Storage object.
// If it doesn't exist yet, this function will create it on the first call. (The 
// parameter allows you the choose what type will be created, other than default.
// You probably won't use it. But if you do, you'll only call it once per instance
// of Storage.)
//
OTPacker * Storage::GetPacker(PackType ePackType/*=OTDB_DEFAULT_PACKER*/) 
{
	// Normally if you use Create(), the packer is created at that time.
	// However, in the future, coders using the API may create subclasses of
	// Storage through SWIG, which Create could not anticipate. This mechanism
	// makes sure that in those cases, the packer still gets set (on the first
	// Get() call), and the coder using the API still has the ability to choose
	// what type of packer will be used.
	//
	if (NULL == m_pPacker)
	{
		m_pPacker = OTPacker::Create(ePackType);
	}
	
	return m_pPacker; // May return NULL.
}
	
// (SetPacker(), from .h file) 
// This is called once, in the factory.
// void Storage::SetPacker(OTPacker & thePacker) { OT_ASSERT(NULL == m_pPacker); m_pPacker =  &thePacker; }
	

//
// Factory for Storable objects...
//
Storable * Storage::CreateObject(StoredObjectType eType) 
{
	OTPacker * pPacker = GetPacker();
	
	if (NULL == pPacker)
		return NULL;
	
	Storable * pStorable = Storable::Create(eType, pPacker->GetType());
	
	return pStorable; // May return NULL.
}
	
// Factory for the Storage context itself.
//
Storage * Storage::Create(StorageType eStorageType, PackType ePackType)
{ 
	Storage * pStore = NULL;
	
	switch (eStorageType) 
	{
		case STORE_FILESYSTEM:
			pStore = StorageFS::Instantiate(); OT_ASSERT(NULL != pStore); break;
//		case STORE_COUCH_DB:
//			pStore = new StorageCouchDB; OT_ASSERT(NULL != pStore); break;
		default:
			break;
	}
	
	// IF we successfully created the storage context, now let's 
	// try to create the packer that goes with it.
	// (They are created together and linked until death.)
	
	if (NULL != pStore)
	{
		OTPacker * pPacker = OTPacker::Create(ePackType);
		
		if (NULL == pPacker)
		{
			// For whatever reason, we failed. Memory issues or whatever.
			delete pStore;
			return NULL;
		}
		
		// Now they're married.
		pStore->SetPacker(*pPacker);
	}
	
	return pStore; // Possible to return NULL.
}
	

// ----------------------------------------------

StorageType Storage::GetType() const
{
	// If I find the type, then I return it. Otherwise I ASSUME
	// that the coder using the API has subclassed Storage, and
	// that this is a custom Storage type invented by the API user.
	
	if (typeid(*this) == typeid(StorageFS))
		return STORE_FILESYSTEM;
//	else if (typeid(*this) == typeid(StorageCouchDB))
//		return STORE_COUCH_DB;
//  Etc.
//
	else
		return STORE_TYPE_SUBCLASS; // The Java coder using API must have subclassed Storage himself.
}
	

// ----------------------------------------------------------------------

bool Storage::StoreString(std::string strContents, std::string strFolder, 
								std::string oneStr/*=""*/, std::string twoStr/*=""*/, std::string threeStr/*=""*/)
{
	OTPacker * pPacker = GetPacker();
	
	if (NULL == pPacker)
		return false;
	// ---------------------------
	
	PackedBuffer * pBuffer = pPacker->Pack(strContents);
	
	if (NULL == pBuffer)
		return false;
	// ---------------------------
	
	bool bSuccess = onStorePackedBuffer(*pBuffer, strFolder, oneStr, twoStr, threeStr);
	
	// Don't want any leaks here, do we?
	delete pBuffer;
	
	return bSuccess;
}

std::string Storage::QueryString(std::string strFolder, 
									   std::string oneStr/*=""*/, std::string twoStr/*=""*/, std::string threeStr/*=""*/)
{
	std::string theString("");

	// ------------------------------
	
	OTPacker * pPacker = GetPacker();
	
	if (NULL == pPacker)
		return theString;
	
	// ---------------------------
	
	PackedBuffer * pBuffer = pPacker->CreateBuffer();
	
	if (NULL == pBuffer)
		return theString;
	
	// Below this point, responsible for pBuffer.
	// ---------------------------
		
	bool bSuccess = onQueryPackedBuffer(*pBuffer, strFolder, oneStr, twoStr, threeStr);
	
	if (!bSuccess)
	{
		delete pBuffer;
		
		return theString;
	}
	
	// ---------------------------

	// We got the packed buffer back from the query!
	// Now let's unpack it and return the Storable object.
	
	bool bUnpacked = pPacker->Unpack(*pBuffer, theString);
	
	if (!bUnpacked)
	{
		delete pBuffer;
		theString = "";
		return theString;
	}
	
	// ---------------------------
	
	// Success :-)
	
	// Don't want any leaks here, do we?
	delete pBuffer;
	
	return theString; 	
}


bool Storage::StoreObject(Storable & theContents, std::string strFolder, 
								std::string oneStr/*=""*/, std::string twoStr/*=""*/, std::string threeStr/*=""*/)
{
	OTPacker * pPacker = GetPacker();
	
	if (NULL == pPacker)
		return false;
// ---------------------------
	PackedBuffer * pBuffer = pPacker->Pack(theContents);

	if (NULL == pBuffer)
		return false;
// ---------------------------
	bool bSuccess = onStorePackedBuffer(*pBuffer, strFolder, oneStr, twoStr, threeStr);
	
	// Don't want any leaks here, do we?
	delete pBuffer;
	
	return bSuccess;
}



// Use %newobject Storage::Query();
//
Storable * Storage::QueryObject(StoredObjectType theObjectType,
									  std::string strFolder, std::string oneStr/*=""*/,  
									  std::string twoStr/*=""*/, std::string threeStr/*=""*/)
{
	OTPacker * pPacker = GetPacker();
	
	if (NULL == pPacker)
		return NULL;
	
	// ---------------------------
	PackedBuffer * pBuffer = pPacker->CreateBuffer();
	
	if (NULL == pBuffer)
		return NULL;
	
	// Below this point, responsible for pBuffer.
	// ---------------------------
	Storable * pStorable = CreateObject(theObjectType);
	
	if (NULL == pStorable)
	{
		delete pBuffer;
		return NULL;
	}
	
	// Below this point, responsible for pBuffer AND pStorable.
	// ---------------------------
	bool bSuccess = onQueryPackedBuffer(*pBuffer, strFolder, oneStr, twoStr, threeStr);
	
	if (!bSuccess)
	{
		delete pBuffer;
		delete pStorable;
		
		return NULL;
	}
	// ---------------------------

	// We got the packed buffer back from the query!
	// Now let's unpack it and return the Storable object.
	
	bool bUnpacked = pPacker->Unpack(*pBuffer, *pStorable);
	
	if (!bUnpacked)
	{
		delete pBuffer;
		delete pStorable;
		
		return NULL;
	}

	// ---------------------------

	// Success :-)
	
	// Don't want any leaks here, do we?
	delete pBuffer;
	
	return pStorable; // caller is responsible to delete.
}



// *****************************************************************************



// Used for making sure that certain necessary folders actually exist. (Creates them otherwise.)
//
// If you pass in "spent", then this function will make sure that "<path>/spent" actually exists, 
// or create it. WARNING: If what you want to pass is "spent/sub-folder-to-spent" then make SURE
// you call it with "spent" FIRST, so you are sure THAT folder has been created, otherwise the
// folder creation will definitely fail on the sub-folder call (if the primary folder wasn't
// already there, that is.)
//
bool StorageFS::ConfirmOrCreateFolder(const char * szFolderName, struct stat * pst/*=NULL*/)
{
	OT_ASSERT(NULL != szFolderName);
	
	// DIRECTORY IS PRESENT?
	struct stat st;

	if (NULL == pst)
		pst = &st;
	
	OTString strPath;
	strPath.Format("%s%s%s", GetFullPath(), PathSeparator(), szFolderName);
	
	bool bDirIsPresent = (0 == stat(strPath.Get(), pst));
	
	// ----------------------------------------------------------------------------
	
	// IF NO, CREATE IT
	if (!bDirIsPresent)
	{
#ifdef _WIN32
		if (_mkdir(strPath.Get()) == -1) 
#else
			if (mkdir(strPath.Get(), 0700) == -1) 
#endif
			{
				OTLog::vError("StorageFS::ConfirmOrCreateFolder: Unable to create %s.\n",
							  strPath.Get());
				return false;
			}
		
		// Now we have created it, so let's check again...
		bDirIsPresent = (0 == stat(strPath.Get(), pst));
		
		if (bDirIsPresent)
			OTLog::vOutput(0, "Created folder: %s\n", strPath.Get());
	}
	
	// ----------------------------------------------------------------------------
	
	// At this point if the folder still doesn't exist, nothing we can do. We
	// already tried to create the folder, and SUCCEEDED, and then STILL failed 
	// to find it (if this is still false.)
	if (!bDirIsPresent)
	{
		OTLog::vError("StorageFS::ConfirmOrCreateFolder: Unable to find newly-created folder: %s\n", 
					  strPath.Get());
		return false;
	}
	
	return true;
}	

// Returns true or false whether a specific file exists.
// Adds the main path prior to checking.
bool StorageFS::ConfirmFile(const char * szFileName, struct stat * pst/*=NULL*/)
{
	OT_ASSERT(NULL != szFileName);
	
	
	struct stat st;

	// FILE IS PRESENT?
	if (NULL == pst)
		pst = &st;
	
	OTString strPath;
	strPath.Format("%s%s%s", GetFullPath(), PathSeparator(), szFileName);
	
	return (0 == stat(strPath.Get(), pst));
}

/*
 - Based on the input, constructs the full path and returns it in strOutput.
 - Also returns true/false based on whether the path actually exists.
 - If some failure occurs along the way, the path returned will not be the
   full path, but the path where the failure occurred.
 - This function will also try to create all the folders leading up to the
   file itself.
 
 New return values:
 
 -1 -- Error
  0 -- File not found
  1 -- File found.
 
 */
long StorageFS::ConstructAndConfirmPath(std::string & strOutput, 
											 const std::string& strFolder, const std::string& oneStr/*=""*/,  
											 const std::string& twoStr/*=""*/,  const std::string& threeStr/*=""*/)
{		
	struct stat st;

	if (strFolder.length() < 1)
	{
		// Must at least have a folder name and a file name.
		OTLog::Error("Folder has a zero length, unable to construct path.\n");
		
		return -1;
	}
	
	// -----------------------------------------------------------------

	bool bConfirmed = false;
	
	if (oneStr.length() < 1) // strFolder is the Filename.
	{
		strOutput = strFolder.c_str();
		bConfirmed = ConfirmFile(strFolder.c_str(), &st);	
	}
	else // There are more strings in the name after the folder...
	{
		strOutput = strFolder.c_str();
		bool bConfirmMAINFolder = ConfirmOrCreateFolder(strFolder.c_str());
		
		if (!bConfirmMAINFolder)
		{
			OTLog::vError("Unable to confirm or create folder: %s\n", strFolder.c_str());
			return -1;
		}
		
		// -----------------------------------------------------------------
			
		OTString strOnePath;
		strOnePath.Format("%s%s%s", strFolder.c_str(), PathSeparator(),
						  oneStr.c_str());
			
		// oneStr is the FILENAME. There are no other strings.
		//
		if (twoStr.length() < 1)
		{
			strOutput = strOnePath.Get();
			bConfirmed = ConfirmFile(strOnePath.Get(), &st);
		}
		else // There are more strings.
		{
			strOutput = strOnePath.Get();
			bool bConfirmFirstFolder = ConfirmOrCreateFolder(strOnePath.Get());
			
			if (!bConfirmFirstFolder)
			{
				OTLog::vError("Unable to confirm or create folder: %s\n", strOnePath.Get());
				return -1;
			}
			// -------------------
			
			OTString strTwoPath;
			strTwoPath.Format("%s%s%s", strOnePath.Get(), PathSeparator(),
							  twoStr.c_str());
			
			// twoStr is the FILENAME. There's no other strings.
			if (threeStr.length() < 1)
			{
				strOutput = strTwoPath.Get();
				bConfirmed = ConfirmFile(strTwoPath.Get(), &st);
			}
			else // There is one more string...
			{
				strOutput = strTwoPath.Get();
				bool bConfirmSecondFolder = ConfirmOrCreateFolder(strTwoPath.Get());
				
				if (!bConfirmSecondFolder)
				{
					OTLog::vError("Unable to confirm or create folder: %s\n", strTwoPath.Get());
					return -1;
				}
				// -------------------
				
				OTString strThreePath;
				strThreePath.Format("%s%s%s", strTwoPath.Get(), PathSeparator(),
									threeStr.c_str());
				
				strOutput = strThreePath.Get();
				bConfirmed = ConfirmFile(strThreePath.Get(), &st); // This may fail, that's okay.
			}
		}
	}
	// ------------------------
	
	OTString strFinalPath;
	strFinalPath.Format("%s%s%s", GetFullPath(), PathSeparator(), strOutput.c_str());
	
	strOutput = strFinalPath.Get();
	
	return bConfirmed ? static_cast<long>(st.st_size) : 0;
}



// -----------------------------------------
// Store/Retrieve an object. (Storable.)

bool StorageFS::onStorePackedBuffer(PackedBuffer & theBuffer, std::string strFolder, 
										  std::string oneStr/*=""*/, std::string twoStr/*=""*/, std::string threeStr/*=""*/)
{
	std::string strOutput;
	
	if (-1 == ConstructAndConfirmPath(strOutput, strFolder, oneStr, twoStr, threeStr))
	{
		OTLog::vError("StorageFS::onStorePackedBuffer: Error writing to %s.\n", strOutput.c_str());
		return false;
	}
	
	// TODO: Should check here to see if there is a .lock file for the target...
	
	// TODO: If not, next I should actually create a .lock file for myself right here..
	
	
	// SAVE to the file here
	std::ofstream ofs(strOutput.c_str(), std::ios::binary);
	
	if (ofs.fail())
	{
		OTLog::vError("Error opening file in StorageFS::onStorePackedBuffer: %s\n", 
					  strOutput.c_str());
		return false;
	}
	
	ofs.clear();
	
	bool bSuccess = theBuffer.WriteToOStream(ofs);	
	
	ofs.close();
	
	// TODO: Remove the .lock file.
	
	return bSuccess;
}


bool StorageFS::onQueryPackedBuffer(PackedBuffer & theBuffer, std::string strFolder, 
										  std::string oneStr/*=""*/, std::string twoStr/*=""*/, std::string threeStr/*=""*/)
{
	std::string strOutput;
	
	long lRet = ConstructAndConfirmPath(strOutput, strFolder, oneStr, twoStr, threeStr);
	
	if (-1 == lRet)
	{
		OTLog::vError("StorageFS::onQueryPackedBuffer: Error with %s.\n", strOutput.c_str());
		return false;
	}
	else if (0 == lRet)
	{
		OTLog::vError("StorageFS::onQueryPackedBuffer: Failure reading from %s: file does not exist.\n", strOutput.c_str());
		return false;
	}
	
	// -------------------------------
	
	// READ from the file here
	
	std::ifstream fin(strOutput.c_str(), std::ios::binary);
	
	if (!fin.is_open())
	{
		OTLog::vError("Error opening file in StorageFS::onQueryPackedBuffer: %s\n", strOutput.c_str());
		return false;
	}
	// -------------------------
	
	bool bSuccess = theBuffer.ReadFromIStream(fin, lRet);	
	
	fin.close();
	
	return bSuccess;
}




// ----------------------------------------------
// Constructor for Filesystem storage context. 
//
StorageFS::StorageFS() : Storage::Storage(), m_strFullPath(""), m_strWalletFile("")
{
	
}

StorageFS::~StorageFS()
{
	
}


// ----------------------------------------------
//
// oneStr == Full path to data_folder
// twoStr == Wallet.xml filename
//
// (The other strings are unused in StorageFS.)
//
bool StorageFS::Init(std::string oneStr/*=""*/,  std::string twoStr/*=""*/,  std::string threeStr/*=""*/, 
						   std::string fourStr/*=""*/, std::string fiveStr/*=""*/, std::string sixStr/*=""*/)
{
	// This is where I verify the directory path exists, and the wallet file within.
	
	if ((oneStr.length() < 1) || (twoStr.length() < 1))
	{
		OTLog::vError("Unable to locate data_folder/wallet: %s/%s\n", oneStr.c_str(), twoStr.c_str());
		return false;
	}
	// --------------------------------
	
	bool bMainFolder = OTLog::ConfirmExactPath(oneStr.c_str());
	
	if (!bMainFolder)
	{
		OTLog::vError("Unable to locate data_folder: %s\n", oneStr.c_str());
		return false;
	}
	// --------------------------------
	// By this point, data_folder was successfully located.
	
	OTString strWalletFile;
	strWalletFile.Format("%s%s%s", oneStr.c_str(), PathSeparator(), twoStr.c_str());
	
	bool bWalletFile = OTLog::ConfirmExactPath(strWalletFile.Get());
	
	if (!bWalletFile)
	{
		OTLog::vError("Unable to locate wallet: %s\n", strWalletFile.Get());
//		return false;  // Let the caller make this decision when he calls LoadWallet();
	}
	// -----------------------------------
	
	m_strFullPath	= oneStr;
	m_strWalletFile	= twoStr;
	
	return true;
}


// -----------------------------------------
// See if the file is there.
bool StorageFS::Exists(std::string strFolder, std::string oneStr/*=""*/,  
							 std::string twoStr/*=""*/,  std::string threeStr/*=""*/)
{
	std::string strOutput;
	
	return (ConstructAndConfirmPath(strOutput, strFolder, oneStr, twoStr, threeStr) > 0) ?
			true : false;
}


// ********************************************************************


} // namespace OTDB

