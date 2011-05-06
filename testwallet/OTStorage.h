
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
	
	// -------------------------------------
	
	
	// abstract base classes.
	//
	class Storable;
	class Packer;
	class Storage;		

	
	// -------------------------------------
	
	// abstract base class for object types being serialized.
	class Storable
	{
		friend class Storage; // for instantiation of storable objects.
		
	protected:
		Storable() {}
		
	public:
		virtual ~Storable() {}

		static Storable * Create(StoredObjectType eType, Storage & theStorage)
		{
			Storable * pStorable = NULL;
			
			switch (eType) 
			{
				case STORED_OBJ_BITCOIN_ACCT:
					pStorable = new BitcoinAcct; OT_ASSERT(NULL != pStorable); break;
				case STORED_OBJ_BITCOIN_SERVER:
					pStorable = new BitcoinServer; OT_ASSERT(NULL != pStorable); break;
				default:
					break;
			}
			
			return pStorable; // May return NULL...
		}
	}
	
	// ----------------------------------------------------------
	
	
	class PackerMsgpack;
	class PackerPB;
	
	
	// abstract base class for packer
	class Packer 
	{
	protected:
		Packer() {}

	public:
		virtual ~Packer() {}
		
		static Packer * Create(PackType ePackType) // Factory.
		{
			Packer * pPacker = NULL;
			
			switch (ePackType) 
			{
				case PACK_MESSAGE_PACK:
					pPacker = new PackerMsgpack; OT_ASSERT(NULL != pPacker); break;
				case PACK_PROTOCOL_BUFFERS:
					pPacker = new PackerPB; OT_ASSERT(NULL != pPacker); break;
				default:
					break;
			}
			
			return pPacker; // May return NULL...
		}
		
		virtual Pack(const Storable& inObj)	= NULL;
		virtual Unpack(Storable& outObj)	= NULL;
	};
	
	// ---------------
	// Msgpack packer.
	
	class PackerMsgpack : public Packer 
	{
	public:
		PackerMsgpack() : Packer() {}
		virtual ~PackerMsgpack() {}
		//------------------------
		virtual Pack(const Storable& inObj);
		virtual Unpack(Storable& outObj);
	};
	
	// ---------------
	// Protocol Buffers packer.
	
	class PackerPB : public Packer 
	{
	public:
		PackerPB() : Packer() {}
		virtual ~PackerPB() {}
		//------------------------
		virtual Pack(const Storable& inObj);
		virtual Unpack(Storable& outObj);
	};
	
	// ----------------------------------------------------------
	
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
		// parameter allows you the choose what type will be created, other than default.
		// You probably won't use it. But if you do, you'll only call it once per instance
		// of OTDB::Storage.)
		Packer * GetPacker(PackType ePackType=OTDB_DEFAULT_PACKER) 
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
				m_pPacker = Packer::Create(ePackType);
			}
			
			return m_pPacker; // May return NULL.
		}

		// This is called once, in the factory.
		void SetPacker(Packer & thePacker) { OT_ASSERT(NULL == m_pPacker); m_pPacker =  &thePacker; }
		
	public:
		virtual ~Storage() { if (NULL != m_pPacker) delete m_pPacker; }

		virtual bool Init(std::string oneStr="", std::string twoStr="", std::string threeStr="", 
						  std::string fourStr="", std::string fiveStr="", std::string sixStr="")=NULL;
		
		virtual bool Store();
		virtual bool Query();
		
		Storable * Create(StoredObjectType eType) // Factory
		{
			
		}
		
		// --------------------------
		
		static Storage * Create(StorageType eStorageType, PackType ePackType) // FACTORY
		{ 
			Storage * pStore = NULL;
			
			switch (eStorageType) 
			{
				case STORE_FILESYSTEM:
					pStore = new StorageFS; OT_ASSERT(NULL != pStore); break;
//				case STORE_COUCH_DB:
//					pStore = new StorageCouchDB; OT_ASSERT(NULL != pStore); break;
				default:
					break;
			}
			
			if (NULL != pStore)
			{
				Packer * pPacker = Packer::Create(ePackType);
				
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
		
		StorageType GetType() const
		{
			if (typeid(*this) == typeid(StorageFS))
				return STORE_FILESYSTEM;
//			else if (typeid(*this) == typeid(StorageCouchDB))
//				return STORE_COUCH_DB;
			else
				return STORE_TYPE_SUBCLASS; // The Java coder using API must have subclassed Storage himself.
		}
		
	}
	
	// Uses the filesystem for storage.
	class StorageFS : public Storage 
	{
	public:
		StorageFS() : Storage() {}
		virtual ~StorageFS() {}
		//------------------------
		virtual bool Init(std::string oneStr="", std::string twoStr="", std::string threeStr="", 
						  std::string fourStr="", std::string fiveStr="", std::string sixStr="");
		
		virtual bool Store();
		virtual bool Query();
		
	};

	// Other subclasses may go here, for storing in SQL lite,
	// or couchDB, mongoDB, distributed DB, etc...
	
	// ---------------------------------------------------------------------------
	
	// this details naming is a common C++ idiom for "private" in a namespace.
	namespace details 
	{
		Storage * s_pStorage;
	}
	
	// Default Storage instance:
	Storage * GetDefaultStorage()
	{
		return details::s_pStorage;
	}
	
	bool Store();
	bool Query();
	
	bool InitDefaultStorage(StorageType eStoreType, PackType ePackType,
							std::string oneStr="", std::string twoStr="", std::string threeStr="", 
							std::string fourStr="", std::string fiveStr="", std::string sixStr="");

	// ---------------------------------------------------------------------------
	
	// Serialized types...
	
	class BitcoinAcctMsgpack;
	class BitcoinAcctPB;
	
	class BitcoinAcct : public Storable
	{
		// You never actually get an instance of this, only its subclasses.
		// Therefore, I don't allow you to access the constructor except through factory.
	protected:
		BitcoinAcct() : Storable() : bitcoin_address(""), bitcoin_name(""), gui_label("") { }
		
	public:
		static BitcoinAcct * Create() { return new BitcoinAcctMsgpack; }
#if defined(OTDB_PROTOCOL_BUFFERS)
		static BitcoinAcct * Create() { return new BitcoinAcctPB; }
#endif
		virtual ~BitcoinAcct() { }
		
		std::string bitcoin_address;
		std::string bitcoin_name;
		std::string gui_label;
	};

	
	// -----------------------------------------
	
	// Serialized objects are separate in implementation based on how they are packed.
	
#if defined (OTDB_MESSAGE_PACK)
	class BitcoinAcctMsgpack : public BitcoinAcct
	{
	public:
		BitcoinAcctMsgpack() : BitcoinAcct() { }
		virtual ~BitcoinAcctMsgpack() { }
		
		MSGPACK_DEFINE(bitcoin_address, bitcoin_name, gui_label); // <===== Using MessagePack
	};
#endif

#if defined(OTDB_PROTOCOL_BUFFERS)
	class BitcoinAcctPB : public BitcoinAcct 
	{
		BitcoinAcct_InternalPB pb_obj; // <========== Using Google's "Protocol Buffers"
		
	public:
		BitcoinAcctPB() : BitcoinAcct() { }
		virtual ~BitcoinAcctPB() { }
	};
#endif

}


#endif // __OT_STORAGE_H__


