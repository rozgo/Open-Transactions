
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


#define OTDB_DEFAULT_PACKER		PACK_MESSAGE_PACK



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
		Packer() {}

	public:
		virtual ~Packer() {}
		
		static Packer * Create(PackType ePackType); // Factory.
		
		PackType GetType() const;
		
		virtual PackedBuffer * CreateBuffer()=NULL;
		
		virtual PackedBuffer *	Pack(Storable& inObj)=NULL;
		virtual bool			Unpack(PackedBuffer& inBuf, Storable& outObj)=NULL;
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
		PackerPB() : Packer() {}
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

		// Use this to access the Packer, throughout duration of this Storage object.
		// If it doesn't exist yet, this function will create it on the first call. (The 
		// parameter allows you the choose what type will be created, other than default.)
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
	
	// Serialized objects are separate in implementation, based on how they are packed.
	
#if defined (OTDB_MESSAGE_PACK)
	class BitcoinAcctMsgpack : public BitcoinAcct
	{
	protected:
		BitcoinAcctMsgpack() : BitcoinAcct() { }
	public:
		static Storable * Instantiate() { return new BitcoinAcctMsgpack(); }
		virtual ~BitcoinAcctMsgpack() { }
				
		MSGPACK_DEFINE(bitcoin_address, bitcoin_name, gui_label); // <===== Using MessagePack
	};
#endif

#if defined(OTDB_PROTOCOL_BUFFERS)
	class BitcoinAcctPB : public BitcoinAcct 
	{
		BitcoinAcct_InternalPB pb_obj; // <========== Using Google's "Protocol Buffers"

	protected:
		BitcoinAcctPB() : BitcoinAcct() { }
	public:
		static Storable * Instantiate() { return new BitcoinAcctPB(); }
		virtual ~BitcoinAcctPB() { }
	};
#endif

}


#endif // __OT_STORAGE_H__


