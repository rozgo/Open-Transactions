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

#ifndef __OT_STORAGE_H__
#define __OT_STORAGE_H__

#include <typeinfo>

#include <string>
#include <deque>
#include <map>

// credit:stlplus library.
#include "containers/simple_ptr.hpp"

// Use Win or Posix
// IF I need this while porting, then uncomment it.
#ifdef _WIN32
#include <windows.h>
//#else
//#ifndef POSIX
//#warning POSIX will be used (but you did not define it)
//#endif
//#include <unistd.h>
#endif


extern "C" 
{
	
#ifdef _WIN32
#include <direct.h>
#include <sys/stat.h>	
#else
#include <sys/stat.h>	
#endif
}


#include "OTLog.h"



// Which storage mechanism are we building?
// (Option is for both...)
//
#define OTDB_MESSAGE_PACK   1
#define OTDB_PROTOCOL_BUFFERS 1
//#define OTDB_JSON_PACKING 1 // coming soon.



//#define OTDB_DEFAULT_PACKER		PACK_MESSAGE_PACK
#define OTDB_DEFAULT_PACKER		OTDB::PACK_PROTOCOL_BUFFERS

#define OTDB_DEFAULT_STORAGE	OTDB::STORE_FILESYSTEM


// ----------------------------------------------------
// JAVA-STYLE INTERFACES.
//
// I'm doing some crazy stuff in this file.
// What you see below is a set of preprocessor definitions that
// allow me to use "Java-Style Interfaces" here in C++.
//
// It turns out that Storable needed a normal class hierarchy, AND Java-
// style interfaces, to do everything I wanted it to do.
//
// I will probably create a more general-purpose header file for OT
// and these sorts of #defines will probably end up there long-term.
// Much of OT might be separable out into a more general-purpose utility
// lib, which I will get to whenever it is more important than anything else.
//
#define Interface class

#define DeclareInterface(name) Interface name { \
public: \
	virtual ~name() {}\
	name* clone(void) const {return NULL;}

#define DeclareBasedInterface(name, base) class name : public base { \
public: \
	virtual ~name() {} \
	base* clone(void) const {return NULL;}

#define EndInterface };

#define implements public
// ----------------------------------------------------





// ----------------------------------------------------

namespace OTDB
{		
	
	// ENUMS:	PackType, StorageType, and StoredObjectType.
	
	// ---------------------------------------------------
	// Currently supporting MsgPack and Protocol Buffers.  
	// 
	enum PackType // PACKING TYPE
	{
		PACK_MESSAGE_PACK = 0,	// Using MessagePack as packer.
		PACK_PROTOCOL_BUFFERS,	// Using Google Protocol Buffers as packer.
		PACK_TYPE_ERROR			// (Should never be.)
	};
	
	// ------------------------------
	// Currently supporting filesystem, with subclasses possible via API.
	//
	enum StorageType  // STORAGE TYPE
	{
		STORE_FILESYSTEM = 0,	// Filesystem
//		STORE_COUCH_DB,			// Couch DB (not yet supported)
		STORE_TYPE_SUBCLASS		// (Subclass provided by API client via SWIG.)
	};
	
	// -------------------------------------
	// 
	// STORED OBJECT TYPES...
	// 
	enum StoredObjectType
	{
		STORED_OBJ_STRING_MAP=0,	// A StringMap is a list of Key/Value pairs, useful for storing nearly anything.
		STORED_OBJ_WALLET_DATA,		// The GUI wallet's stored data
		STORED_OBJ_BITCOIN_ACCT,	// The GUI wallet's stored data about a Bitcoin acct
		STORED_OBJ_BITCOIN_SERVER,	// The GUI wallet's stored data about a Bitcoin RPC port.
		STORED_OBJ_SERVER_INFO,		// A Nym has a list of these.
		STORED_OBJ_CONTACT_NYM,		// This is a Nym record inside a contact of your address book.
		STORED_OBJ_CONTACT_ACCT,	// This is an account record inside a contact of your address book.
		STORED_OBJ_CONTACT,			// Your address book has a list of these.
		STORED_OBJ_ADDRESS_BOOK,	// Your address book.
		STORED_OBJ_ERROR			// (Should never be.)
	};
	
// ********************************************************************
	
	// OTDB NAMESPACE "CONSTRUCTOR"
	//
	class InitOTDBDetails 
	{
	public:
		InitOTDBDetails();  // See implementation of this in CPP file for namespace construction.
		~InitOTDBDetails(); // Ditto.
	};
	// -------------------------------
	
	
	
	// ABSTRACT BASE CLASSES
	//
	class Storable;		// A storable object
	class OTPacker;		// A packer (Could be MsgPack, or Google Protocol Buffers, or a json lib...)
	class Storage;		// A storage context (database, filesystem, cloud, etc. Swappable.)
	class PackedBuffer;	// A buffer for containing a PACKED STORABLE. (On its way to/from storage.)
	
	
	
	// ------------------------------------------------
	//
	// OTDB Namespace internal types
	//
	// In short:
	// - InstantiateFunc (function pointer type.)
	// - InstantiateFuncKey (based on Pack Type and Stored Object Type.)
	// - mapOfFunctions (type: map of InstantiateFuncs, indexed by InstantiateFuncKeys.)
	//
	// Resulting in: pFunctionMap (Instance of mapOfFunctions, created in the OTDB constructor.)
	//
	typedef Storable * (InstantiateFunc)(); // Each storable has one of these as a static method.
	typedef std::pair<PackType, StoredObjectType> InstantiateFuncKey; // Those methods are stored as function pointers here, and they are
															// indexed by Pack Type and Stored Object Type. So if you know "LoomAcct" and
															// "protocol buffers", those form the KEY for looking up the LoomAcctPB instantiator.
	typedef std::map<InstantiateFuncKey, InstantiateFunc*> mapOfFunctions; //...basically implementing my own vtable, eh?
			
	
	
// ********************************************************************
	
	// OTDB Namespace PRIVATE MEMBERS
	// this "details" naming is a common C++ idiom for "private" in a namespace.
	//
	namespace details 
	{
		extern OTDB::Storage * s_pStorage;

		extern OTDB::mapOfFunctions * pFunctionMap; // This is a pointer so I can control what order it is created in, on startup.
	}
	
	
	
	
	
// ********************************************************************
	
	//
	// STORABLE
	//
	// Abstract base class for OT serializable object types.
	//
	class Storable
	{
		friend class Storage; // for instantiation of storable objects by their storage context.
		
	protected:
		Storable() {}
		
	public:
		virtual ~Storable() {}
		
		// %ignore spam(unsigned short); API users don't need this function, it's for internal purposes.
		static Storable * Create(StoredObjectType eType, PackType thePackType);
		
	};

// ----------------------------------------------------
	
	// All of the class hierarchy under Storable is based on OT data design. (Not packing.)
	// So when we need to add custom behavior that's common to groups of the final subclasses,
	// we use Interfaces to do it. 
	
	// ===> That way, the Storable hierarchy can focus on DATA,
	// ===> while the IStorable hierarchy focuses on PACKING.
	// ===> Things are more elegant that way.
	
	//
	//
	// Interface:    IStorable
	//
	// Each Packer library (MsgPack, etc) must provide an interface derived from IStorable.
	// (They're all listed below this.)
	//
DeclareInterface(IStorable)
	virtual bool onPack(PackedBuffer& theBuffer, Storable& inObj) = 0; // buffer is output, inObj is input.
	virtual bool onUnpack(PackedBuffer& theBuffer, Storable& outObj) = 0; // buffer is input, outObj is output.
	// ------------------------------------------
	virtual void hookBeforePack() {} // This is called just before packing a storable. (Opportunity to copy values...)
	virtual void hookAfterUnpack() {} // This is called just after unpacking a storable. (Opportunity to copy values...)
EndInterface
	
	
	
	
	
// ********************************************************************
	
	// PACKED BUFFER (for storing PACKED DATA)
	//
	// %ignore these classes (I think)
	// 
	
	class PackedBuffer 
	{
	protected:
		PackedBuffer() {} // Only subclasses of this should be instantiated.
	public:
		virtual ~PackedBuffer() {}
		
		virtual bool PackString(std::string& theString)=0;
		virtual bool UnpackString(std::string& theString)=0;
		
		virtual bool ReadFromIStream(std::istream &inStream, long lFilesize)=0;
		virtual bool WriteToOStream(std::ostream &outStream)=0;
	};
	
	// --------------------------------
	//
	// SUBCLASSES (the actual declarations are at the bottom of this file.)
	//
//	typedef PackedBufferSubclass<PackerMsgpack, IStorableMsgpack,	msgpack::sbuffer>	BufferMsgpack;
//	typedef PackedBufferSubclass<PackerPB,		IStorablePB,		std::string>		BufferPB;

	// They're all based on this template:
	//
#define DECLARE_PACKED_BUFFER_SUBCLASS(theNewType, thePackerType, theInterfaceType, theInternalType) \
	class theNewType : public PackedBuffer \
	{ \
		friend class		thePackerType; \
		friend Interface	theInterfaceType; \
		theInternalType		m_buffer; \
	public: \
		theNewType() : PackedBuffer() {} \
		virtual ~theNewType() {} \
		virtual bool PackString(std::string& theString); \
		virtual bool UnpackString(std::string& theString); \
		virtual bool ReadFromIStream(std::istream &inStream, long lFilesize); \
		virtual bool WriteToOStream(std::ostream &outStream); \
		theInternalType & GetBuffer() { return m_buffer; } \
	}
	
// ********************************************************************

	
	
	
	
	
	
	
	
// ********************************************************************
	
	// PACKER (now OTPacker since MsgPack also has a "Packer" in a #define).
	//
	// abstract base class for a packer
	//
	
	// %ignore spam(unsigned short);  (probably for all packers.)
	class OTPacker 
	{
	protected:
		OTPacker() { }

	public:
		virtual ~OTPacker() {}
		
		static OTPacker * Create(PackType ePackType); // Factory.
		
		PackType GetType() const;

		PackedBuffer *	Pack(Storable& inObj);
		bool			Unpack(PackedBuffer& inBuf, Storable& outObj);
		
		PackedBuffer *	Pack(std::string& inObj);
		bool			Unpack(PackedBuffer& inBuf, std::string& outObj);
		
		virtual PackedBuffer * CreateBuffer()=0;
	};

	
	// ----------------------------------------------------
	// For declaring subclasses of OTPacker.
	
	template<class theBufferType>
	class PackerSubclass : public OTPacker
	{
	public:
		PackerSubclass() : OTPacker() {}
		virtual ~PackerSubclass() {}
		
		virtual PackedBuffer * CreateBuffer() { return new theBufferType; }
		
		// You don't see onPack and onUnpack here because they are on IStorable.
	};
	
	// To use:
	// typedef PackerSubclass<theBufferType> theType;
	//
	// ----------------------------------------------------
	
	// SUBCLASSES:
	//
	// (Actual declarations are at the bottom of the file.)
	//
//	typedef PackerSubclass<BufferMsgpack>	PackerMsgpack;
//	typedef PackerSubclass<BufferPB>		PackerPB;
	
// ********************************************************************
	
	
	
	
	
	
	
	
// ********************************************************************
	//
	// STORAGE  -- abstract base class
	//
	//
	class Storage
	{
	private:
		OTPacker * m_pPacker;
		
	protected:
		Storage() : m_pPacker(NULL) {}

		// Use GetPacker() to access the Packer, throughout duration of this Storage object.
		// If it doesn't exist yet, this function will create it on the first call. (The 
		// parameter allows you the choose what type will be created, other than default.)
		// This way, whenever using an OT Storage, you KNOW the packer is always the right
		// one, and that you don't have to fiddle with it at all. You can also therefore use
		// it for creating instances of various Storables and PackedBuffers, and knowing
		// that the right types will be instantiated, with the buffer being the appropriate
		// subclass for the packer.
		//
		OTPacker * GetPacker(PackType ePackType=OTDB_DEFAULT_PACKER);

		// This is called once, in the factory.
		void SetPacker(OTPacker & thePacker) { OT_ASSERT(NULL == m_pPacker); m_pPacker =  &thePacker; }
		
		// -------------------------------------
		// OVERRIDABLES
		//
		virtual bool onStorePackedBuffer(PackedBuffer & theBuffer, std::string strFolder, std::string oneStr="", 
										 std::string twoStr="", std::string threeStr="")=0;
		
		virtual bool onQueryPackedBuffer(PackedBuffer & theBuffer, std::string strFolder, std::string oneStr="",
										 std::string twoStr="", std::string threeStr="")=0;
		
		virtual bool onStorePlainString(std::string & theBuffer, std::string strFolder, std::string oneStr="", 
										std::string twoStr="", std::string threeStr="")=0;
		
		virtual bool onQueryPlainString(std::string & theBuffer, std::string strFolder, std::string oneStr="",
										std::string twoStr="", std::string threeStr="")=0;
		
		// -------------------------------------
		
	public:
		virtual ~Storage() { if (NULL != m_pPacker) delete m_pPacker; }

		virtual bool Init(std::string oneStr="", std::string twoStr="", std::string threeStr="", 
						  std::string fourStr="", std::string fiveStr="", std::string sixStr="")=0;
		
		// -----------------------------------------
		// See if the file is there.
		virtual bool Exists(std::string strFolder, 
							std::string oneStr="", std::string twoStr="", std::string threeStr="")=0;

		// -----------------------------------------
		// Store/Retrieve a string.
		
		bool StoreString(std::string strContents, std::string strFolder, 
						 std::string oneStr="", std::string twoStr="", std::string threeStr="");
		
		std::string QueryString(std::string strFolder, std::string oneStr="",
								std::string twoStr="", std::string threeStr="");
				
		bool StorePlainString(std::string strContents, std::string strFolder, 
							  std::string oneStr="", std::string twoStr="", std::string threeStr="");
		
		std::string QueryPlainString(std::string strFolder, std::string oneStr="",
									 std::string twoStr="", std::string threeStr="");
		
		// -----------------------------------------
		// Store/Retrieve an object. (Storable.)
		
		bool StoreObject(Storable & theContents, std::string strFolder, 
						 std::string oneStr="", std::string twoStr="", std::string threeStr="");
		
		// Use %newobject OTDB::Storage::Query();
		Storable * QueryObject(StoredObjectType theObjectType,
							   std::string strFolder, std::string oneStr="",
							   std::string twoStr="", std::string threeStr="");
		
		// --------------------------
		// Note:
		// Make sure to use: %newobject Factory::createObj();  IN OTAPI.i file!
		//
		// That way, Java garbage cleanup will handle object after this.
		// (Instead of leaking because it thinks C++ will clean it up.)
		//
		// Factory for Storable objects.   %newobject Factory::createObj();
		Storable * CreateObject(StoredObjectType eType);
		
		// --------------------------
		
		// Factory for Storage itself.  %ignore this in OTAPI.i  (It's accessed through 
		// a namespace-level function.)
		//
		static Storage * Create(StorageType eStorageType, PackType ePackType); // FACTORY
		
		StorageType GetType() const;
	};

	
// ********************************************************************
	//
	// OTDB Namespace PUBLIC INTERFACE
	//
	//
	
	bool InitDefaultStorage(StorageType eStoreType, PackType ePackType,
							std::string oneStr="", std::string twoStr="", std::string threeStr="", 
							std::string fourStr="", std::string fiveStr="", std::string sixStr="");
	
	// Default Storage instance:
	Storage * GetDefaultStorage();
	
	// %newobject Factory::createObj();
	Storage * CreateStorageContext(StorageType eStoreType, PackType ePackType=OTDB_DEFAULT_PACKER);
	
	Storable * CreateObject(StoredObjectType eType);

	// bool bSuccess = OTDB::StoreString(strInbox, "inbox", "lkjsdf908w345ljkvd");
	// bool bSuccess = OTDB::StoreString(strMint,  "mints", SERVER_ID, ASSET_ID);
	// bool bSuccess = OTDB::StoreString(strPurse, "purse", SERVER_ID, USER_ID, ASSET_ID);
	
	// BELOW FUNCTIONS use the DEFAULT Storage context for the OTDB Namespace
	
	// --------
	// See if the file is there.
	//
	bool Exists(std::string strFolder, 
				std::string oneStr="", std::string twoStr="", std::string threeStr="");
	
	// --------
	// Store/Retrieve a string.
	//
	bool StoreString(std::string strContents, std::string strFolder, 
					 std::string oneStr="", std::string twoStr="", std::string threeStr="");
	
	std::string QueryString(std::string strFolder, std::string oneStr="",
							std::string twoStr="", std::string threeStr="");
	
	bool StorePlainString(std::string strContents, std::string strFolder, 
						  std::string oneStr="", std::string twoStr="", std::string threeStr="");
	
	std::string QueryPlainString(std::string strFolder, std::string oneStr="",
								 std::string twoStr="", std::string threeStr="");
	
	// --------
	// Store/Retrieve an object. (Storable.)
	//
	bool StoreObject(Storable & theContents, std::string strFolder, 
					 std::string oneStr="", std::string twoStr="", std::string threeStr="");
	
	// Use %newobject OTDB::Storage::Query();
	Storable * QueryObject(StoredObjectType theObjectType,
						   std::string strFolder, std::string oneStr="",
						   std::string twoStr="", std::string threeStr="");		

// ********************************************************************
	
	// Serialized types...
	//
	// Here the entire hierarchy focuses on the OT data itself.
	// Later, subclasses are made providing the final implementation,
	// based on the packer type. (Same for buffers.)
		
	// The most useful generic data object... a map of strings, key/value pairs.
	//
	class StringMap : public Storable
	{
		// You never actually get an instance of this, only its subclasses.
		// Therefore, I don't allow you to access the constructor except through factory.
	protected:
		StringMap() : Storable() { }
		
	public:
		virtual ~StringMap() { }
		
		std::map<std::string, std::string> the_map;  // all strings, key/value pairs.
		
		void SetValue(const std::string& strKey, const std::string& strValue)
		{ the_map[strKey] = strValue; }
		
		std::string GetValue(const std::string& strKey)
		{ std::string ret_val(""); std::map<std::string, std::string>::iterator ii = the_map.find(strKey);
		  if (ii != the_map.end()) ret_val = (*ii).second; return ret_val; }
	};

	// ------------------------------------------------
	
	class Displayable : public Storable
	{
		// You never actually get an instance of this, only its subclasses.
		// Therefore, I don't allow you to access the constructor except through factory.
	protected:
		Displayable() : Storable(),  gui_label("") { }
		
	public:
		virtual ~Displayable() { }
		
		std::string gui_label;  // The label that appears in the GUI
	};
	
	// *************************************************
	
	// ACCOUNT (GUI local storage about my own accounts, in my wallet.)
	
	class Acct : public Displayable
	{
		// You never actually get an instance of this, only its subclasses.
		// Therefore, I don't allow you to access the constructor except through factory.
	protected:
		Acct() : Displayable(), acct_id(""), server_id("")  { }
		
	public:
		virtual ~Acct() { }

//		std::string gui_label;  // The label that appears in the GUI

		std::string acct_id;
		std::string server_id;
	};
	
	// ----------------------------
	
	class BitcoinAcct : public Acct
	{
		// You never actually get an instance of this, only its subclasses.
		// Therefore, I don't allow you to access the constructor except through factory.
	protected:
		BitcoinAcct() : Acct(), bitcoin_acct_name("") { }
		
	public:
		virtual ~BitcoinAcct() { }
		
//		std::string gui_label;  // The label that appears in the GUI
		
//		std::string acct_id;
//		std::string server_id;
		
		std::string bitcoin_acct_name;
	};
	
	// **************************************************
	
	// SERVER (GUI local storage about servers.)
	
	class ServerInfo : public Displayable
	{
		// You never actually get an instance of this, only its subclasses.
		// Therefore, I don't allow you to access the constructor except through factory.
	protected:
		ServerInfo() : Displayable(), server_id(""), server_type("") { }
		
	public:
		virtual ~ServerInfo() { }
		
//		std::string gui_label;  // The label that appears in the GUI

		std::string server_id;
		std::string server_type;
	};
	
	// ----------------------------
	
	class Server : public ServerInfo
	{
		// You never actually get an instance of this, only its subclasses.
		// Therefore, I don't allow you to access the constructor except through factory.
	protected:
		Server() : ServerInfo(), server_host(""), server_port("") { }
		
	public:
		virtual ~Server() { }
		
//		std::string gui_label;  // The label that appears in the GUI

//		std::string server_id;   // in base class
//		std::string server_type; // in base class
		
		std::string server_host;
		std::string server_port;
	};
	
	// ----------------------------
	
	class BitcoinServer : public Server
	{
		// You never actually get an instance of this, only its subclasses.
		// Therefore, I don't allow you to access the constructor except through factory.
	protected:
		BitcoinServer() : Server(), bitcoin_username(""), bitcoin_password("") { }
		
	public:
		virtual ~BitcoinServer() { }
		
//		std::string gui_label;  // The label that appears in the GUI
		
//		std::string server_id;   // in base class
//		std::string server_type; // in base class
		
//		std::string server_host;
//		std::string server_port;
		
		std::string bitcoin_username;
		std::string bitcoin_password;
	};
	
	// ----------------------------
	
#define DECLARE_GET_ADD_REMOVE(name) \
	protected: \
	std::deque< stlplus::simple_ptr_clone<name> > list_##name##s; \
	public: \
	size_t Get##name##Count(); \
	name * Get##name(size_t nIndex); \
	bool Remove##name(size_t nIndex); \
	bool Add##name(name & disownObject)
	
	
	class ContactNym : public Displayable
	{
		// You never actually get an instance of this, only its subclasses.
		// Therefore, I don't allow you to access the constructor except through factory.
	protected:
		ContactNym() : Displayable(), nym_type(""), nym_id(""), public_key(""), memo("") { }
		
	public:
		virtual ~ContactNym();
		
//		std::string gui_label;  // The label that appears in the GUI

		std::string nym_type;
		std::string nym_id;
		std::string public_key;
		std::string memo;
		
		DECLARE_GET_ADD_REMOVE(ServerInfo);
	};
	
	
	// ------------------------------------------------

	class WalletData : public Storable
	{
		// You never actually get an instance of this, only its subclasses.
		// Therefore, I don't allow you to access the constructor except through factory.
	protected:
		WalletData() : Storable() { }
		
	public:
		virtual ~WalletData();
		
		// List of Bitcoin servers
		// List of Bitcoin accounts
		// Loom, etc.
		
		DECLARE_GET_ADD_REMOVE(BitcoinServer);
		DECLARE_GET_ADD_REMOVE(BitcoinAcct);
	};
	
	// ----------------------------
	
	class ContactAcct : public Displayable {
		// You never actually get an instance of this, only its subclasses.
		// Therefore, I don't allow you to access the constructor except through factory.
	protected:
		ContactAcct() : Displayable(), server_type(""), server_id(""), asset_type_id(""), acct_id(""), nym_id(""), memo(""), public_key("")  { }
		
	public:
		virtual ~ContactAcct() { }
		
//		std::string gui_label;  // The label that appears in the GUI
		
		std::string server_type;
		std::string server_id;
		std::string asset_type_id;
		std::string acct_id;
		std::string nym_id;
		std::string memo;
		std::string public_key;
	};
	
	// ----------------------------
	
	
	class Contact : public Displayable {
		// You never actually get an instance of this, only its subclasses.
		// Therefore, I don't allow you to access the constructor except through factory.
	protected:
		Contact() : Displayable(), contact_id(""), email(""), memo(""), public_key("") { }
		
	public:
		virtual ~Contact();
		
//		std::string gui_label;  // The label that appears in the GUI
		
		std::string contact_id;
		std::string email;
		std::string memo;
		std::string public_key;
		
		DECLARE_GET_ADD_REMOVE(ContactNym);
		DECLARE_GET_ADD_REMOVE(ContactAcct);
	};
	
	// ----------------------------
	
	class AddressBook : public Storable {
		// You never actually get an instance of this, only its subclasses.
		// Therefore, I don't allow you to access the constructor except through factory.
	protected:
		AddressBook() : Storable() { }
		
	public:
		virtual ~AddressBook();
		
		DECLARE_GET_ADD_REMOVE(Contact);
	};
} // Namespace OTDB

// ********************************************************************









// *******************************************************************************************
//
// StorageFS -- FILE-SYSTEM Storage Context
//
//
namespace OTDB 
{
	// --------------------------------------------------------------------------
	//
	// StorageFS means "Storage on Filesystem."
	// 
	// This is the first subclass of OTDB::Storage -- but it won't be the last!
	//
	class StorageFS : public Storage 
	{
		std::string m_strFullPath;
		std::string m_strWalletFile;
		
	protected:
		StorageFS();	// You have to use the factory to instantiate (so it can create the Packer also.)
		// But from there, however you Init, Store, Query, etc is entirely up to you.

		// -----------------------------------------------------
		virtual bool onStorePackedBuffer(PackedBuffer & theBuffer, std::string strFolder, std::string oneStr="", 
										 std::string twoStr="", std::string threeStr="");
		
		virtual bool onQueryPackedBuffer(PackedBuffer & theBuffer, std::string strFolder, std::string oneStr="",
										 std::string twoStr="", std::string threeStr="");
		
		virtual bool onStorePlainString(std::string & theBuffer, std::string strFolder, std::string oneStr="", 
										std::string twoStr="", std::string threeStr="");
		
		virtual bool onQueryPlainString(std::string & theBuffer, std::string strFolder, std::string oneStr="",
										std::string twoStr="", std::string threeStr="");
		
		// -----------------------------------------------------
		
		long ConstructAndConfirmPath(std::string & strOutput,
									 const std::string& strFolder, const std::string& oneStr="",  
									 const std::string& twoStr="",  const std::string& threeStr="");
	public:
		static StorageFS * Instantiate() { return new StorageFS; }
		
		virtual ~StorageFS();
		
		virtual bool Init(std::string oneStr="", std::string twoStr="", std::string threeStr="", 
						  std::string fourStr="", std::string fiveStr="", std::string sixStr="");
		
		// -----------------------------------------
		// See if the file is there.
		virtual bool Exists(std::string strFolder, 
							std::string oneStr="", std::string twoStr="", std::string threeStr="");
		

		// -----------------------------------------
		// lower level calls.
		
		bool ConfirmOrCreateFolder(const char * szFolderName, struct stat *pst=NULL); // local to data_folder
		bool ConfirmFile(const char * szFileName, struct stat *pst=NULL); // local to data_folder

		const char * GetFullPath() { return m_strFullPath.c_str(); }  // path to data_folder
		const char * GetWalletFile() { return m_strWalletFile.c_str(); } // wallet filename
	
		const char * PathSeparator() { return OTLog::PathSeparator(); } // using OTLog for now.
		
		/*
		 IN BASE CLASS:
		 
		// -----------------------------------------
		// Store/Retrieve a string.
		
		bool StoreString(std::string strContents, std::string strFolder, 
						 std::string oneStr="", std::string twoStr="", std::string threeStr="");
		
		std::string QueryString(std::string strFolder, std::string oneStr="",
								std::string twoStr="", std::string threeStr="");
		
		// -----------------------------------------
		// Store/Retrieve an object. (Storable.)
		
		bool StoreObject(Storable & theContents, std::string strFolder, 
						 std::string oneStr="", std::string twoStr="", std::string threeStr="");
		
		// Use %newobject OTDB::Storage::Query();
		Storable * QueryObject(StoredObjectType theObjectType,
							   std::string strFolder, std::string oneStr="",
							   std::string twoStr="", std::string threeStr="");
		*/
	};
	
	// Other storage subclasses may go here, for storing in SQL lite,
	// or couchDB, mongoDB, distributed DB, etc...	
	
	// class StorageCouchDB
	// class CloudMagic
	// class SQL-LITE
	//
	// Etc.
	
	// Also, coders using the API should be able to subclass Storage in their own language via SWIG.
	
} // namespace OTDB
// *******************************************************************************************








// IStorable-derived types...
//
//
// BELOW are the SUBCLASSES of the storable objects that actually get INSTANTIATED,
// based on WHICH PACKER is being used.
	
// If you are adding a new DATA OBJECT, then you probably want to add lines below
// for EACH of the different packer types (MsgPack, Protocol Buffers, JSON, etc.)
//
	
#define OT_USING_ISTORABLE_HOOKS \
	using IStorable::hookBeforePack; \
	using IStorable::hookAfterUnpack









// *******************************************************************************************

// JSON will be the next packer that I add

#if defined (OTDB_JSON_PACKING)
//#include "JSON - LIBRARY . h"   // coming soon.
#endif // defined (OTDB_JSON_PACKING)
// *******************************************************************************************







// *******************************************************************************************
#if defined (OTDB_MESSAGE_PACK)
#include <msgpack.hpp>
//
// To declare MsgPack-packed OT objects (IStorableMsgpack):
/*
 OT_MSGPACK_BEGIN(BitcoinAcctMsgpack, BitcoinAcct)
	MSGPACK_DEFINE(acct_id, server_id, bitcoin_acct_name, gui_label);
 OT_MSGPACK_END;
 */
// Where BitcoinAcctMsgpack is the new class being declared (for that packer),
// BitcoinAcct is the OT Data object that it serializes, and where bitcoin_address,
// bitcoin_acct_name, and gui_label are being used as examples for the data members
// being serialized.
//
// DON'T use a semicolon after the first macro. (OT_MSGPACK_BEGIN.)
// But DO put semicolons after the MSGPACK_DEFINE and OT_MSGPACK_END macros.
//
// The idea is that the data members themselves (in the above example, 
// bitcoin_address, bitcoin_acct_name, and gui_label) are actually implemented
// by BitcoinAcct (the base), and any other packer library could similarly
// be subclassing that base as we are here with BitcoinAcctMsgPack.
//
// To cap it all off, MsgPack-specific functionality (which we may also need
// in 30 other MsgPack classes like BitcoinServerMsgpack, LoomAcctMsgpack,
// etc) can be added to all of the msgPack objects via the IStorableMsgpack
// interface, even though they all have different base classes (oriented around
// their data, and not their packing.)
//

// ----------------------------------------------
#define OT_MSGPACK_BEGIN(theType, theBaseType) \
class theType : public theBaseType, implements IStorableMsgpack \
{		\
public: \
	theType() : theBaseType() { } \
	IStorable * clone(void) const {return dynamic_cast<IStorable *>(new theType(*this));} \
	static Storable * Instantiate() { return dynamic_cast<Storable *>(new theType); } \
	virtual ~theType() { } \
	virtual bool PerformPack(BufferMsgpack& theBuffer) { msgpack::pack(theBuffer.GetBuffer(), *this); return true; } \
	virtual bool PerformUnpack(BufferMsgpack& theBuffer) { msgpack::zone z; msgpack::object obj; msgpack::unpack_return ret = \
		msgpack::unpack(theBuffer.GetBuffer().data(), theBuffer.GetBuffer().size(), NULL, &z, &obj); if (msgpack::UNPACK_SUCCESS == ret) \
		{ obj.convert(this); return true; } return false; }

// Next go these:
//	OT_USING_ISTORABLE_HOOKS;
//	MSGPACK_DEFINE(gui_label, server_id, server_type, asset_type_id, acct_id, nym_id, memo, public_key);

// Sometimes looks more like this:
//	virtual void hookBeforePack(); // This is called just before packing a storable. (Opportunity to copy values...)
//	virtual void hookAfterUnpack(); // This is called just after unpacking a storable. (Opportunity to copy values...)
//	std::deque<BitcoinServerMsgpack>	deque_BitcoinServers;
//	std::deque<BitcoinAcctMsgpack>		deque_BitcoinAccts;
//	MSGPACK_DEFINE(deque_BitcoinServers, deque_BitcoinAccts);

// This part is commented out. Why? Because I think it's unnecessary. Operator= is not inherited.
// That means when I copy these objects, only the WalletDataMsgpack data members are being copied,
// not the 

// !!!!! This bottom part MUST be directly before the OT_MSGPACK_END!!!!!!!!!
// Notice I declare an op=, so the compiler won't define a default one. Why?
// Because the default one will call the base class op= as well, and copy over the
// pointer lists that are in the data portion. (I don't want that.) I want to only copy
// the basic members and the deques, NOT the pointers. So I declare op= and do so.
// NO semicolon after this one...
/*
#define OT_MSGPACK_BEGIN_SWAP(theType) \
public: \
	theType & operator=(theType rhs) { \
		this->swap(rhs); \
		return *this; \
	} \
void swap (theType & rhs) {

// semicolon after this one.
#define OT_MSGPACK_SWAP_MEMBER(theMember) \
	std::swap(theMember, rhs.theMember)
 
*/
//
// You put the actual assignments in like this:
//		OT_MSGPACK_SWAP_MEMBER(theMember);
//		OT_MSGPACK_SWAP_MEMBER(theMember);
//		OT_MSGPACK_SWAP_MEMBER(theMember);


// Finishing with this, and semicolon after.
//#define OT_MSGPACK_END  } }
#define OT_MSGPACK_END  } 


// ----------------------------------------------


namespace OTDB 
{	
	class BufferMsgpack;
	
	// Interface:	IStorableMsgpack
	//
	DeclareBasedInterface(IStorableMsgpack, IStorable)
		virtual bool onPack(PackedBuffer& theBuffer, Storable& inObj);
		virtual bool onUnpack(PackedBuffer& theBuffer, Storable& outObj);
		virtual bool PerformPack(BufferMsgpack& theBuffer)=0;
		virtual bool PerformUnpack(BufferMsgpack& theBuffer)=0;
		OT_USING_ISTORABLE_HOOKS;
	EndInterface
	
	
	// ---------------------------------
	// BUFFER for MsgPack.
	//
	// typedef PackedBufferSubclass<PackerMsgpack, IStorableMsgpack, msgpack::sbuffer> BufferMsgpack;
	DECLARE_PACKED_BUFFER_SUBCLASS(BufferMsgpack, PackerSubclass<BufferMsgpack>, IStorableMsgpack, msgpack::sbuffer);

	// ---------------
	// Msgpack packer.
	//
	typedef PackerSubclass<BufferMsgpack> PackerMsgpack;
	
	
	// -------------------------------------------------------
	// For strings.
	//
	class MsgpackStringWrapper
	{
	public:
		MsgpackStringWrapper() : s("") {}
		MsgpackStringWrapper(const std::string& strInput) : s(strInput) {}
		~MsgpackStringWrapper() {}
		std::string s;
		MSGPACK_DEFINE(s);
	};
		
// -------------------------------------------------------
		
	
	// Do NOT use a semicolon after the first macro. (OT_MSGPACK_BEGIN.)
	// DO put a semicolon after the MSGPACK_DEFINE macro.
	// DO put a semicolon after the OT_MSGPACK_END macro.

	// -------------------------------------------------------
	OT_MSGPACK_BEGIN(StringMapMsgpack, StringMap)
		OT_USING_ISTORABLE_HOOKS;
		MSGPACK_DEFINE(the_map);
//		OT_MSGPACK_BEGIN_SWAP(StringMapMsgpack)
//		OT_MSGPACK_SWAP_MEMBER(the_map);
	OT_MSGPACK_END;	
	// -------------------------------------------------------
	OT_MSGPACK_BEGIN(ServerInfoMsgpack, ServerInfo)
		OT_USING_ISTORABLE_HOOKS;
		MSGPACK_DEFINE(gui_label, server_id, server_type);
//		OT_MSGPACK_BEGIN_SWAP(ServerInfoMsgpack)
//		OT_MSGPACK_SWAP_MEMBER(gui_label);
//		OT_MSGPACK_SWAP_MEMBER(server_id);
//		OT_MSGPACK_SWAP_MEMBER(server_type);
	OT_MSGPACK_END;	
	// -------------------------------------------------------
	OT_MSGPACK_BEGIN(BitcoinAcctMsgpack, BitcoinAcct)
		OT_USING_ISTORABLE_HOOKS;
		MSGPACK_DEFINE(gui_label, acct_id, server_id, bitcoin_acct_name);
//		OT_MSGPACK_BEGIN_SWAP(BitcoinAcctMsgpack)
//		OT_MSGPACK_SWAP_MEMBER(gui_label);
//		OT_MSGPACK_SWAP_MEMBER(acct_id);
//		OT_MSGPACK_SWAP_MEMBER(server_id);
//		OT_MSGPACK_SWAP_MEMBER(bitcoin_acct_name);
	OT_MSGPACK_END;
	// -------------------------------------------------------
	OT_MSGPACK_BEGIN(BitcoinServerMsgpack, BitcoinServer)
		OT_USING_ISTORABLE_HOOKS;
		MSGPACK_DEFINE(gui_label, server_id, server_type, server_host, server_port, bitcoin_username, bitcoin_password);
//		OT_MSGPACK_BEGIN_SWAP(BitcoinServerMsgpack)
//		OT_MSGPACK_SWAP_MEMBER(gui_label);
//		OT_MSGPACK_SWAP_MEMBER(server_id);
//		OT_MSGPACK_SWAP_MEMBER(server_type);
//		OT_MSGPACK_SWAP_MEMBER(server_host);
//		OT_MSGPACK_SWAP_MEMBER(server_port);
//		OT_MSGPACK_SWAP_MEMBER(bitcoin_username);
//		OT_MSGPACK_SWAP_MEMBER(bitcoin_password);
	OT_MSGPACK_END;
	// -------------------------------------------------------
	OT_MSGPACK_BEGIN(ContactAcctMsgpack, ContactAcct)
		OT_USING_ISTORABLE_HOOKS;
		MSGPACK_DEFINE(gui_label, server_id, server_type, asset_type_id, acct_id, nym_id, memo, public_key);
//		OT_MSGPACK_BEGIN_SWAP(ContactAcctMsgpack)
//		OT_MSGPACK_SWAP_MEMBER(gui_label);
//		OT_MSGPACK_SWAP_MEMBER(server_id);
//		OT_MSGPACK_SWAP_MEMBER(server_type);
//		OT_MSGPACK_SWAP_MEMBER(asset_type_id);
//		OT_MSGPACK_SWAP_MEMBER(acct_id);
//		OT_MSGPACK_SWAP_MEMBER(nym_id);
//		OT_MSGPACK_SWAP_MEMBER(memo);
//		OT_MSGPACK_SWAP_MEMBER(public_key);
	OT_MSGPACK_END;
	// -------------------------------------------------------
	OT_MSGPACK_BEGIN(ContactNymMsgpack, ContactNym)
		virtual void hookBeforePack(); // This is called just before packing a storable. (Opportunity to copy values...)
		virtual void hookAfterUnpack(); // This is called just after unpacking a storable. (Opportunity to copy values...)
		std::deque<ServerInfoMsgpack>	deque_ServerInfos;
		MSGPACK_DEFINE(gui_label, nym_id, nym_type, public_key, memo, deque_ServerInfos);
//		OT_MSGPACK_BEGIN_SWAP(ContactNymMsgpack)
//		OT_MSGPACK_SWAP_MEMBER(gui_label);
//		OT_MSGPACK_SWAP_MEMBER(nym_id);
//		OT_MSGPACK_SWAP_MEMBER(nym_type);
//		OT_MSGPACK_SWAP_MEMBER(public_key);
//		OT_MSGPACK_SWAP_MEMBER(memo);
//		OT_MSGPACK_SWAP_MEMBER(deque_ServerInfos);
	OT_MSGPACK_END;	
	// -------------------------------------------------------
	OT_MSGPACK_BEGIN(ContactMsgpack, Contact)
		virtual void hookBeforePack(); // This is called just before packing a storable. (Opportunity to copy values...)
		virtual void hookAfterUnpack(); // This is called just after unpacking a storable. (Opportunity to copy values...)
		std::deque<ContactNymMsgpack>	deque_Nyms;
		std::deque<ContactAcctMsgpack>	deque_Accounts;
		MSGPACK_DEFINE(gui_label, contact_id, email, public_key, memo, deque_Nyms, deque_Accounts);
//		OT_MSGPACK_BEGIN_SWAP(ContactMsgpack)
//		OT_MSGPACK_SWAP_MEMBER(gui_label);
//		OT_MSGPACK_SWAP_MEMBER(contact_id);
//		OT_MSGPACK_SWAP_MEMBER(email);
//		OT_MSGPACK_SWAP_MEMBER(public_key);
//		OT_MSGPACK_SWAP_MEMBER(memo);
//		OT_MSGPACK_SWAP_MEMBER(deque_Nyms);
//		OT_MSGPACK_SWAP_MEMBER(deque_Accounts);
	OT_MSGPACK_END;	
	// -------------------------------------------------------
	OT_MSGPACK_BEGIN(AddressBookMsgpack, AddressBook)
		virtual void hookBeforePack(); // This is called just before packing a storable. (Opportunity to copy values...)
		virtual void hookAfterUnpack(); // This is called just after unpacking a storable. (Opportunity to copy values...)
		std::deque<ContactMsgpack>	deque_Contacts;
		MSGPACK_DEFINE(deque_Contacts);
//		OT_MSGPACK_BEGIN_SWAP(AddressBookMsgpack)
//		OT_MSGPACK_SWAP_MEMBER(deque_Contacts);
	OT_MSGPACK_END;	
	// -------------------------------------------------------
	OT_MSGPACK_BEGIN(WalletDataMsgpack, WalletData)
		virtual void hookBeforePack(); // This is called just before packing a storable. (Opportunity to copy values...)
		virtual void hookAfterUnpack(); // This is called just after unpacking a storable. (Opportunity to copy values...)
		std::deque<BitcoinServerMsgpack>	deque_BitcoinServers;
		std::deque<BitcoinAcctMsgpack>		deque_BitcoinAccts;
		MSGPACK_DEFINE(deque_BitcoinServers, deque_BitcoinAccts);
//		OT_MSGPACK_BEGIN_SWAP(WalletDataMsgpack)
//		OT_MSGPACK_SWAP_MEMBER(deque_BitcoinServers);
//		OT_MSGPACK_SWAP_MEMBER(deque_BitcoinAccts);
	OT_MSGPACK_END;
	// -------------------------------------------------------
	
	// You might ask, why did I code the "copy and swap" idiom above, and then comment it out?
	// Because I'm now storing smart pointers instead of regular pointers, in the lists of the
	// objects above. Therefore I'm not so worried about the copy constructor, operator=, etc.
	// The deques will copy over exactly, and the lists will copy the smart pointers, so I don't
	// have to worry about the lists double-deleting anymore.
	
} // namespace OTDB

#endif // defined (OTDB_MESSAGE_PACK)
// *******************************************************************************************










// *******************************************************************************************

#if defined(OTDB_PROTOCOL_BUFFERS)
#include "Generics.pb.h"
#include "Bitcoin.pb.h"
#include "Moneychanger.pb.h"
// To make subclasses of the various data objects (for Protocol Buffers):
//
// typedef ProtobufSubclass<theBaseType, theInternalType> theType;
//
// Also, REMEMBER for each object type declared, to add the hooks to the CPP file.
// (Instructions are below.)
//
// ----------------------------------------------------
/* 
	 REPLACING OT_PROTOBUF_DECLARE() WITH A TEMPLATE FOR NOW...
	 
	 #define OT_PROTOBUF_DECLARE(theType, theBaseType, theInternalType) \
	 class theType : public theBaseType, implements IStorablePB \
	 {		\
	 private: \
		theInternalType __pb_obj; \
	 protected: \
		theType() : theBaseType() { } \
	 public: \
		::google::protobuf::Message & getPBMessage() { return dynamic_cast<::google::protobuf::Message>(__pb_obj); } \
		static Storable * Instantiate() { return dynamic_cast<Storable *>(new theType()); } \
		virtual ~theType() { } \
		virtual void hookBeforePack(); \
		virtual void hookAfterUnpack(); \
	 }
	 //	OT_PROTOBUF_DECLARE(BitcoinAcctPB, BitcoinAcct, BitcoinAcct_InternalPB);
	 //	OT_PROTOBUF_DECLARE(BitcoinServerPB, BitcoinServer, BitcoinServer_InternalPB);
 
 
 
 #define DECLARE_PACKED_BUFFER_SUBCLASS(theNewType, thePackerType, theInterfaceType, theInternalType) \
 class theNewType : public PackedBuffer \
 { \
	 friend class		thePackerType; \
	 friend Interface	theInterfaceType; \
	 theInternalType		m_buffer; \
 public: \
	 theNewType() : PackedBuffer() {} \
	 virtual ~theNewType(); \
	 virtual bool PackString(std::string& theString); \
	 virtual bool UnpackString(std::string& theString); \
	 virtual bool ReadFromIStream(std::istream &inStream, long lFilesize); \
	 virtual bool WriteToOStream(std::ostream &outStream); \
 }
*/




namespace OTDB 
{

	// Interface:    IStorablePB
	//
	DeclareBasedInterface(IStorablePB, IStorable)
		virtual ::google::protobuf::Message * getPBMessage();
		virtual bool onPack(PackedBuffer& theBuffer, Storable& inObj);
		virtual bool onUnpack(PackedBuffer& theBuffer, Storable& outObj);
		OT_USING_ISTORABLE_HOOKS;
	EndInterface
	
	// ----------------------------------------------------
	// BUFFER for Protocol Buffers.
	// Google's protocol buffers serializes to std::strings and streams. How conveeeeeenient. 
	//
	//typedef PackedBufferSubclass<PackerPB, IStorablePB, std::string> BufferPB;
	DECLARE_PACKED_BUFFER_SUBCLASS(BufferPB, PackerSubclass<BufferPB>, IStorablePB, std::string);

	// ---------------
	// Protocol Buffers packer.
	//
	typedef PackerSubclass<BufferPB> PackerPB;
	
	// ----------------------------------------------------
	// Used for subclassing IStorablePB:
	//
	template<class theBaseType, class theInternalType>
	class ProtobufSubclass : public theBaseType, implements IStorablePB 
	{
	private:
		theInternalType __pb_obj; 
	public: 
		ProtobufSubclass() : theBaseType() { } 
		virtual ::google::protobuf::Message * getPBMessage(); 
		IStorable * clone(void) const 
			{return dynamic_cast<IStorable *>(new ProtobufSubclass<theBaseType, theInternalType>(*this));} \
		static Storable * Instantiate() 
			{ return dynamic_cast<Storable *>(new ProtobufSubclass<theBaseType, theInternalType>); } 
		virtual ~ProtobufSubclass() { } 
		OT_USING_ISTORABLE_HOOKS;
		virtual void hookBeforePack();  // <=== Implement this if you subclass.
		virtual void hookAfterUnpack(); // <=== Implement this if you subclass.
	};
	
#define DECLARE_PROTOBUF_SUBCLASS(theBaseType, theInternalType, theNewType) \
	template<> void ProtobufSubclass<theBaseType, theInternalType>::hookBeforePack(); \
	template<> void ProtobufSubclass<theBaseType, theInternalType>::hookAfterUnpack(); \
	typedef ProtobufSubclass<theBaseType, theInternalType>	theNewType

	// ---------------------------------------------
	//
	// THE ACTUAL SUBCLASSES: 
	
	DECLARE_PROTOBUF_SUBCLASS(Storable,			String_InternalPB,			StringPB);
	DECLARE_PROTOBUF_SUBCLASS(StringMap,		StringMap_InternalPB,		StringMapPB);
	DECLARE_PROTOBUF_SUBCLASS(BitcoinAcct,		BitcoinAcct_InternalPB,		BitcoinAcctPB);
	DECLARE_PROTOBUF_SUBCLASS(BitcoinServer,	BitcoinServer_InternalPB,	BitcoinServerPB);
	DECLARE_PROTOBUF_SUBCLASS(ServerInfo,		ServerInfo_InternalPB,		ServerInfoPB);
	DECLARE_PROTOBUF_SUBCLASS(ContactAcct,		ContactAcct_InternalPB,		ContactAcctPB);
	DECLARE_PROTOBUF_SUBCLASS(ContactNym,		ContactNym_InternalPB,		ContactNymPB);
	DECLARE_PROTOBUF_SUBCLASS(Contact,			Contact_InternalPB,			ContactPB);
	DECLARE_PROTOBUF_SUBCLASS(AddressBook,		AddressBook_InternalPB,		AddressBookPB);
	DECLARE_PROTOBUF_SUBCLASS(WalletData,		WalletData_InternalPB,		WalletDataPB);
	
	/*
	typedef ProtobufSubclass<Storable, String_InternalPB>					StringPB;
	
	typedef ProtobufSubclass<StringMap, StringMap_InternalPB>::Type			StringMapPB;
	
	typedef ProtobufSubclass<BitcoinAcct, BitcoinAcct_InternalPB>::Type		BitcoinAcctPB;
	typedef ProtobufSubclass<BitcoinServer, BitcoinServer_InternalPB>::Type	BitcoinServerPB;
	
	
	typedef ProtobufSubclass<ServerInfo, ServerInfo_InternalPB>::Type		ServerInfoPB;
	
	typedef ProtobufSubclass<ContactAcct, ContactAcct_InternalPB>::Type		ContactAcctPB;
	typedef ProtobufSubclass<ContactNym, ContactNym_InternalPB>::Type		ContactNymPB;
	typedef ProtobufSubclass<Contact, Contact_InternalPB>::Type				ContactPB;
	
	typedef ProtobufSubclass<AddressBook, AddressBook_InternalPB>::Type		AddressBookPB;
	
	typedef ProtobufSubclass<WalletData, WalletData_InternalPB>::Type		WalletDataPB;
	*/
	
	
	// !! ALL OF THESE have to provide implementations for hookBeforePack() and hookAfterUnpack().
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
	
	
	
} // namespace OTDB

#endif // defined(OTDB_PROTOCOL_BUFFERS)
// *******************************************************************************************







#endif // __OT_STORAGE_H__











