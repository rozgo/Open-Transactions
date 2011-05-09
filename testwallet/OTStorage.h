
#ifndef __OT_STORAGE_H__
#define __OT_STORAGE_H__

#include <typeinfo>

#include <string>


// Which storage mechanism are we building?
// (Option is for both...)
//
#define OTDB_MESSAGE_PACK   1
//#define OTDB_PROTOCOL_BUFFERS 1




#if defined (OTDB_MESSAGE_PACK)
#include <msgpack.hpp>
#endif


#if defined(OTDB_PROTOCOL_BUFFERS)
#include "BitcoinAcct.pb.h"
#endif

#if defined (OTDB_JSON_PACKING)
//#include "JSON - LIBRARY . h"
#endif


#define OTDB_DEFAULT_PACKER		PACK_MESSAGE_PACK


// ----------------------------------------------------
// I'm doing some crazy stuff in this file.
// What you see below is a set of preprocessor definitions that
// allow me to use "Java-Style Interfaces" here in C++.
//
// Elsewhere in OTStorage, I am also using "template polymorphism".
// It turns out that Storable needed a normal class hierarchy, AND Java-
// style interfaces, AND template polymorphism, to do everything I wanted
// it to do!
//
// I will probably create a more general-purpose header file for OT
// and these sorts of #defines will probably end up there long-term.
// Much of OT might be separable out into a more general-purpose utility
// lib, which I will get to whenever it is more important than anything else.
//
#define Interface class

#define DeclareInterface(name) Interface name { \
public: \
virtual ~name() {}

#define DeclareBasedInterface(name, base) class name : public base { \
public: \
virtual ~name() {}

#define EndInterface };

#define implements public

// ----------------------------------------------------


/* 
// Then you can declare a class that implements this interface with something like:
 
 // Foo.h
 // 
 
 #include "BasicFoo.h"
 
 #include "IBar.h"
 
 
 class Foo : public BasicFoo, implements IBar
 {
	// Construction & Destruction
 
 public:
	Foo(int x) : BasicFoo(x)
	{
	}
 
	~Foo();
 
	// IBar implementation
 
 public:
	virtual int GetBarData() const
	{
	// stuff...
 
	}
 
	virtual void SetBarData(int nData)
	{
		// stuff...
 
	}
 };
 
 */

// ----------------------------------------------------

namespace OTDB
{
public:
	class InitOTDBDetails // Constructor for the namespace.
	{
	public:
		InitOTDBDetails(); 
		~InitOTDBDetails();
	};

	// ---------------------------------------------------
	// Currently supporting MsgPack and Protocol Buffers.  
	// 
	enum PackType
	{
		PACK_MESSAGE_PACK = 0,	// Using MessagePack as packer.
		PACK_PROTOCOL_BUFFERS,	// Using Google Protocol Buffers as packer.
		PACK_TYPE_ERROR			// (Should never be.)
	};

	// Currently supporting filesystem, with subclasses possible via API.
	enum StorageType
	{
		STORE_FILESYSTEM = 0,	// Filesystem
//		STORE_COUCH_DB,			// Couch DB (not yet supported)
		STORE_TYPE_SUBCLASS		// (Subclass provided by API client via SWIG.)
	};
	
	// -------------------------------------
	
	// Only specific OT objects are allowed... 
	// 
	enum StoredObjectType
	{
		STORED_OBJ_BITCOIN_ACCT = 0,	// The GUI wallet's stored data about a Bitcoin acct
		STORED_OBJ_BITCOIN_SERVER,		// The GUI wallet's stored data about a Bitcoin RPC port.
		STORED_OBJ_ERROR				// (Should never be.)
	};
	
	// ********************************************************************
	
	
	// abstract base classes.
	//
	class Storable;
	class Packer;
	class Storage;		

	class PackedBuffer;

	// Namespace types and members
	
	typedef Storable * (InstantiateFunc)(); // Each storable has one of these as a static method.
	typedef std::pair<PackType, StoredObjectType> InstantiateFuncKey; // Those methods are stored as function pointers here,
																	// indexed by Pack Type and Stored Object Type.
	typedef std::map<InstantiateFuncKey, InstantiateFunc*> mapOfFunctions; //...basically implementing my own vtable, eh?
	
	mapOfFunctions * pFunctionMap;
	
	
	// ********************************************************************
	
	// abstract base class for OT object types being serialized.
	
	class Storable
	{
		friend class Storage; // for instantiation of storable objects.
		
	protected:
		Storable() {}
		
	public:
		virtual ~Storable() {}

		// %ignore spam(unsigned short); API users don't need this function, it's for internal purposes.
		static Storable * Create(StoredObjectType eType, Packer & thePacker);
		
	}
	
	/*
	 #if defined(OTDB_PROTOCOL_BUFFERS)
	 class BitcoinAcctPB : public BitcoinAcct, implements IStorablePB
	 {
		BitcoinAcct_InternalPB __pb_obj; // <========== Using Google's "Protocol Buffers"
	 
	 protected:
		BitcoinAcctPB() : BitcoinAcct() { }
	 public:
		static Storable * Instantiate() { return new BitcoinAcctPB(); }
		virtual ~BitcoinAcctPB() { }
	 };
	 #endif	 
	 */
	
	 
	// ----------------------------------------------------

	// IStorable INTERFACE
	//
	// 
	//
	DeclareInterface(IStorable)
		virtual bool onPack(PackedBuffer& theBuffer) = NULL; // buffer is output, *this is input.
		virtual bool onUnpack(PackedBuffer& theBuffer, Storable& outObj) = NULL; // buffer is input, outObj is output.
		// ------------------------------------------
		virtual void hookBeforePack() {} // This is called just before packing. (Opportunity to copy values...)
		virtual void hookAfterUnpack() {} // This is called just after unpacking. (Opportunity to copy values...)
	EndInterface
	
	
	
// ----------------------------------------------------
#if defined (OTDB_MESSAGE_PACK)
	DeclareBasedInterface(IStorableMsgpack, IStorable)
		virtual bool onPack(PackedBuffer& theBuffer);
		virtual bool onUnpack(PackedBuffer& theBuffer, Storable& outObj);
	EndInterface	
#endif
// ----------------------------------------------------

	
	
	
// ----------------------------------------------------
#if defined (OTDB_PROTOCOL_BUFFERS)
	template <class T>	
	class TStorablePB	
	{					
		T const & t;	
	public:				
		TStorablePB(T const & obj) : t(obj) { }
		
		::google::protobuf::Message & getPBMessage()
		{ return t.__pb_obj; }			
	};
	
	// -------------------
	
	template <class T> 
	TStorablePB<T> makeTStorablePB( T& obj )
	{
		return TStorablePB<T>( obj ); 
	}

	// *********************
	
	DeclareBasedInterface(IStorablePB, IStorable)
		template<class T> friend class TStorablePB; 
		::google::protobuf::Message & getPBMessage()=NULL;
		// ------------------------------------------
		virtual bool onPack(PackedBuffer& theBuffer);
		virtual bool onUnpack(PackedBuffer& theBuffer, Storable& outObj);
	EndInterface
	
#endif
// ----------------------------------------------------
	
	
	
	// ********************************************************************
	
	
	// %ignore these classes
	
	class PackedBuffer 
	{
	protected:
		PackedBuffer();
	public:
		virtual ~PackedBuffer();
	};
	
	// ---------------------------------
#if defined (OTDB_MESSAGE_PACK)
	class BufferMsgpack : public PackedBuffer
	{
		friend class PackerMsgpack;
		friend class IStorableMsgpack;

		msgpack::sbuffer m_buffer;
		
	public:
		BufferMsgpack() : PackedBuffer() {}
		virtual ~BufferMsgpack(); 
	};
#endif
	
#if defined (OTDB_PROTOCOL_BUFFERS)
	class BufferPB : public PackedBuffer
	{
		friend class PackerPB;
		friend class IStorablePB;
		
		// Google's protocol buffers serializes to std::strings and streams. How conveeeeeenient. 
		std::string m_strBuffer; 
		
	public:
		BufferPB() : PackedBuffer() {}
		virtual ~BufferPB(); 
	};
#endif
	// ---------------------------------

	
#if defined (OTDB_MESSAGE_PACK)
	class PackerMsgpack;
#endif
#if defined (OTDB_PROTOCOL_BUFFERS)
	class PackerPB;
#endif
	
	// ---------------------------------

	// %ignore spam(unsigned short);
	// abstract base class for packer
	class Packer 
	{
	protected:
		Packer() { }

	public:
		virtual ~Packer() {}
		
		static Packer * Create(PackType ePackType); // Factory.
		
		PackType GetType() const;
		
		virtual PackedBuffer * CreateBuffer()=NULL;
		
		virtual PackedBuffer *	Pack(Storable& inObj);
		virtual bool			Unpack(PackedBuffer& inBuf, Storable& outObj);
	};
	
	// ---------------
	// Msgpack packer.
	
#if defined (OTDB_MESSAGE_PACK)
	// %ignore spam(unsigned short);
	class PackerMsgpack : public Packer 
	{
	public:
		PackerMsgpack() : Packer() {}
		virtual ~PackerMsgpack() {}
		//------------------------
		
		virtual PackedBuffer * CreateBuffer() { return new BufferMsgpack; }

		virtual PackedBuffer *	Pack(Storable& inObj);
		virtual bool			Unpack(PackedBuffer& inBuf, Storable& outObj);
	};
#endif
	
	// ---------------
	// Protocol Buffers packer.
	
#if defined (OTDB_PROTOCOL_BUFFERS)
	// %ignore spam(unsigned short);
	class PackerPB : public Packer 
	{
	public:
		PackerPB() : Packer() { }
		virtual ~PackerPB() {}
		//------------------------
		
		virtual PackedBuffer * CreateBuffer() { return new BufferPB; }
		
		virtual PackedBuffer *	Pack(Storable& inObj);
		virtual bool			Unpack(PackedBuffer& inBuf, Storable& outObj);
	};
#endif
	
	
	// ********************************************************************
	
	
	class StorageFS;	// storage is filesystem
						// More coming soon...
	
	// abstract base class
	class Storage
	{
	private:
		Packer * m_pPacker;
		
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
		Packer * GetPacker(PackType ePackType=OTDB_DEFAULT_PACKER);

		// This is called once, in the factory.
		void SetPacker(Packer & thePacker) { OT_ASSERT(NULL == m_pPacker); m_pPacker =  &thePacker; }
		
	public:
		virtual ~Storage() { if (NULL != m_pPacker) delete m_pPacker; }

		virtual bool Init(std::string oneStr="", std::string twoStr="", std::string threeStr="", 
						  std::string fourStr="", std::string fiveStr="", std::string sixStr="")=NULL;
		
		// -----------------------------------------
		// See if the file is there.
		virtual bool Exists(std::string strFolder, 
							std::string oneStr="", std::string twoStr="", std::string threeStr="")=NULL;

		// -----------------------------------------
		// Store/Retrieve a string.
		
		virtual bool StoreString(std::string strContents, std::string strFolder, 
								 std::string oneStr="", std::string twoStr="", std::string threeStr="")=NULL;
		
		virtual std::string QueryString(std::string strFolder, std::string oneStr="",
										std::string twoStr="", std::string threeStr="")=NULL;
				
		// -----------------------------------------
		// Store/Retrieve an object. (Storable.)
		
		virtual bool StoreObject(Storable & theContents, std::string strFolder, 
								 std::string oneStr="", std::string twoStr="", std::string threeStr="")=NULL;
		
		// Use %newobject OTDB::Storage::Query();
		virtual Storable * QueryObject(std::string strFolder, std::string oneStr="",
									   std::string twoStr="", std::string threeStr="")=NULL;
		
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
	
	// -----------------
	
	// Uses the filesystem for storage.
	class StorageFS : public Storage 
	{
	public:
		StorageFS();
		virtual ~StorageFS();
		
		virtual bool Init(std::string oneStr="", std::string twoStr="", std::string threeStr="", 
						  std::string fourStr="", std::string fiveStr="", std::string sixStr="");
		
		// -----------------------------------------
		// See if the file is there.
		virtual bool Exists(std::string strFolder, 
							std::string oneStr="", std::string twoStr="", std::string threeStr="");
		
		// -----------------------------------------
		// Store/Retrieve a string.
		
		virtual bool StoreString(std::string strContents, std::string strFolder, 
								 std::string oneStr="", std::string twoStr="", std::string threeStr="");
		
		virtual std::string QueryString(std::string strFolder, std::string oneStr="",
										std::string twoStr="", std::string threeStr="");
		
		// -----------------------------------------
		// Store/Retrieve an object. (Storable.)
		
		virtual bool StoreObject(Storable & theContents, std::string strFolder, 
								 std::string oneStr="", std::string twoStr="", std::string threeStr="");
		
		// Use %newobject OTDB::Storage::Query();
		virtual Storable * QueryObject(std::string strFolder, std::string oneStr="",
									   std::string twoStr="", std::string threeStr="");		
	};

	// Other subclasses may go here, for storing in SQL lite,
	// or couchDB, mongoDB, distributed DB, etc...
	
	// ********************************************************************
	
	// this details naming is a common C++ idiom for "private" in a namespace.
	namespace details 
	{
		Storage * s_pStorage;
	}
	
	
	bool InitDefaultStorage(StorageType eStoreType, PackType ePackType,
							std::string oneStr="", std::string twoStr="", std::string threeStr="", 
							std::string fourStr="", std::string fiveStr="", std::string sixStr="");
	
	// Default Storage instance:
	Storage * GetDefaultStorage() { return details::s_pStorage; }
	
	// %newobject Factory::createObj();
	Storage * CreateStorageContext(StorageType eStoreType, PackType ePackType);
	
	// bool bSuccess = OTDB::Store(strInbox, "inbox", "lkjsdf908w345ljkvd");
	// bool bSuccess = OTDB::Store(strMint,  "mints", SERVER_ID, ASSET_ID);
	// bool bSuccess = OTDB::Store(strPurse, "purse", SERVER_ID, USER_ID, ASSET_ID);
	
	// BELOW FUNCTIONS use the DEFAULT Storage context.
	
	// -----------------------------------------
	// See if the file is there.
	bool Exists(std::string strFolder, 
				std::string oneStr="", std::string twoStr="", std::string threeStr="");
	
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
	Storable * QueryObject(std::string strFolder, std::string oneStr="",
						   std::string twoStr="", std::string threeStr="");		
	
	// ********************************************************************
	
	// Serialized types...
		
	class BitcoinAcct : public Storable
	{
		// You never actually get an instance of this, only its subclasses.
		// Therefore, I don't allow you to access the constructor except through factory.
	protected:
		BitcoinAcct() : Storable() : bitcoin_address(""), bitcoin_name(""), gui_label("") { }
		
	public:
		virtual ~BitcoinAcct() { }
		
		std::string bitcoin_address;
		std::string bitcoin_name;
		std::string gui_label;
	};

	
// -----------------------------------------
#if defined (OTDB_MESSAGE_PACK)
	
	// Serialized objects are separate in implementation, based on how they are packed.
	
	// Don't use a semicolon after the first macro. (BEGIN.)
	// DO put a semicolon after the END macro.
#define OT_MSGPACK_BEGIN(theType, theParentType) \
class theType : public theParentType, implements IStorableMsgpack \
{		\
protected: \
	theType() : theParentType() { } \
public: \
	static Storable * Instantiate() { return dynamic_cast<Storable *>(new theType()); } \
	virtual ~ ## theType() { }
//	MSGPACK_DEFINE(bitcoin_address, bitcoin_name, gui_label);
#define OT_MSGPACK_END    }
//-----------------------------------------------
// Don't use a semicolon after the first macro. (BEGIN.)
// DO put a semicolon after the END macro.

OT_MSGPACK_BEGIN(BitcoinAcctMsgpack, BitcoinAcct)
	MSGPACK_DEFINE(bitcoin_address, bitcoin_name, gui_label);
OT_MSGPACK_END;

#endif
//-----------------------------------------------

	
	
// --------------------------------------------------------------
#if defined(OTDB_PROTOCOL_BUFFERS)
	/*
DeclareBasedInterface(IStorablePB, IStorable)
	 template<class T> friend class TStorablePB; 
	 ::google::protobuf::Message & getPBMessage()=NULL;
	 // ------------------------------------------
	 virtual bool onPack(PackedBuffer& theBuffer);
	 virtual bool onUnpack(PackedBuffer& theBuffer, Storable& outObj);
EndInterface
	 */
#define OT_PROTOBUF_DECLARE(theType, theParentType, theInternalType) \
class theType : public theParentType, implements IStorablePB \
{		\
private: \
	theInternalType __pb_obj; \
protected: \
	theType() : theParentType() { } \
public: \
	::google::protobuf::Message & getPBMessage() { return __pb_obj; } \
	static Storable * Instantiate() { return dynamic_cast<Storable *>(new theType()); } \
	virtual ~ ## theType() { } \
	virtual void hookBeforePack(); \
	virtual void hookAfterUnpack(); \
}
//------------------------
	
	OT_PROTOBUF_DECLARE(BitcoinAcctPB, BitcoinAcct, BitcoinAcct_InternalPB);
	
#endif
//-----------------------------------------------

}


#endif // __OT_STORAGE_H__


