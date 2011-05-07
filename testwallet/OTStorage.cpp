
#include "OTStorage.h"

using namespace OTDB;


/*
 
 // We want to store EXISTING OT OBJECTS (Usually signed contracts)
 // These have an EXISTING OT path, such as "inbox/<acct_id>".
 // These are always in the form of a STRING.
 // The easiest way for me to store/retrieve those is:
 
 bool bSuccessStore = OTDB::Store(strPath, strContents);
 bool bSuccessQuery = OTDB::Query(strPath, strRetrieved);
 
 // -------
 // Internal to the above functions, the default Packing/Buffer is
 // used, and the default Storage is used. But what if I want to
 // CHOOSE the storage and packing?
 
 // Storage.
 // Before creating my own storage, let's try using the default storage
 // itself, instead of asking the API to use it for me:
 
 OTDB::Storage * pStorage = OTDB::GetDefaultStorage();
 OT_ASSERT(NULL!=pStorage);
 
 bool bSuccessStore = pStorage->Store(strPath, strContents);
 bool bSuccessQuery = pStorage->Query(strPath, strRetrieved);
 
 // -------
 // So if I wanted to create my own storage, it would be similar (below).
 
 OTDB::Storage * pStorage = OTDB::Storage::Create(OTDB::STORE_FILESYSTEM);
 OT_ASSERT(NULL!=pStorage);
 
 bool bSuccessStore = pStorage->Store(strPath, strContents);
 bool bSuccessQuery = pStorage->Query(strPath, strRetrieved);
 
 // Creating like above is also how the default gets instantiated (internally)
 // when you first start storing and querying without specifying yourself.
 
 // -------
 // In the above example, the default packing is still being used.
 // But what if I want to choose my packing?
 // It's actually a default parameter on the Create call:
 
 OTDB::Storage * pStorage = 
 OTDB::Storage::Create(OTDB::STORE_FILESYSTEM, OTDB::PACK_MESSAGE_PACK);
 OT_ASSERT(NULL!=pStorage);
 
 bool bSuccessInit  = pStorage->Init("/path/to/data_folder", "wallet.xml");
 
 if (bSuccessInit)
 {
 bool bSuccessStore = pStorage->Store(strPath, strContents);
 bool bSuccessQuery = pStorage->Query(strPath, strRetrieved);
 }
 
 // Storage needs to be set up -- whether a database connection initiated,
 // or files loaded, or sub-directories created, or a Tor connection or whatever.
 // Therefore, there is an Init() call which may have different parameters for
 // each storage type. That way, all subclasses might use it differently, and
 // the parameters are easily thrown into a config file later.
 
 // ------
 // What if it was a CouchDB database, instead of the filesystem? 
 // And using Google's Protocol Buffers for packing, isntead of MsgPack?
 
 OTDB::Storage * pStorage = 
 OTDB::Storage::Create(OTDB::STORE_COUCHDB, OTDB::PACK_PROTOCOL_BUFFERS);
 OT_ASSERT(NULL!=pStorage);
 
 // This time, Init receives database connect info instead of filesystem info...
 bool bSuccessInit  = pStorage->Init("IP ADDRESS", "PORT", "USERNAME", "PASSWORD", "DB NAME");
 
 etc.
 
 // --------------------
 // So what if I want to use the default, but I want that default to be CouchDB and Google?
 // Just do this (near the beginning of the execution of the application):
 
 bool bInit = OTDB::InitDefaultStorage(OTDB::STORE_COUCHDB, OTDB::PACK_PROTOCOL_BUFFERS,
 "IP ADDRESS", "PORT", "USERNAME", "PASSWORD", "DB NAME");
 
 if (true == bInit)
 {
 // Then do this as normal:
 
 OTDB::Storage * pStorage = OTDB::GetDefaultStorage();
 OT_ASSERT(NULL!=pStorage);
 
 bool bSuccessStore = pStorage->Store(strPath, strContents);
 bool bSuccessQuery = pStorage->Query(strPath, strRetrieved);
 }
 
 // -----------------------------------------------------------
 
 // What if you want to store an object in that location instead of a string?
 // The object must be derived from OTDB::Storable...
 
 OTDB::BitcoinAcct theAcct;
 
 theAcct.bitcoin_address	= "jkhsdf987345kjhf8lkjhwef987345";
 theAcct.bitcoin_name		= "Read-Only Label (Bitcoin Internal cacti)";
 theAcct.gui_label			= "Editable Label (Moneychanger)";
 
 OTDB::Store(theAcct);
 
 
 */



// ********************************************************************

// NAMESPACE CONSTRUCTOR / DESTRUCTOR

// "private" to the namespace.
// Use OTDB::GetDefaultStorage() to access this variable.
// Use OTDB::InitDefaultStorage() to set up this variable.
//
Storage * OTDB::details::s_pStorage = NULL;

mapOfFunctions * OTDB::pFunctionMap;

OTDB::InitOTDBDetails theOTDBConstructor; // Constructor for this instance (define all namespace variables above this line.)

OTDB::InitOTDBDetails::InitOTDBDetails() // Constructor for namespace
{
	OT_ASSERT (NULL == OTDB::pFunctionMap);

	OTDB::pFunctionMap = new mapOfFunctions;
	
	OT_ASSERT (NULL != OTDB::pFunctionMap);
	
	mapOfFunctions & theMap = *(OTDB::pFunctionMap);
	
	//This will go in C++ file in an Init section:
#if defined (OTDB_MESSAGE_PACK)
	OTDB::theMap[std::make_pair(PACK_MESSAGE_PACK, STORED_OBJ_BITCOIN_ACCT)]	= &BitcoinAcctMsgpack::Instantiate;
	OTDB::theMap[std::make_pair(PACK_MESSAGE_PACK, STORED_OBJ_BITCOIN_SERVER)]	= &BitcoinAcctMsgpack::Instantiate; // FIX THIS LINE! (should create server but none exists yet)
#endif
	
#if defined (OTDB_PROTOCOL_BUFFERS)
	OTDB::theMap[std::make_pair(PACK_PROTOCOL_BUFFERS, STORED_OBJ_BITCOIN_ACCT)]	= &BitcoinAcctPB::Instantiate;
	OTDB::theMap[std::make_pair(PACK_PROTOCOL_BUFFERS, STORED_OBJ_BITCOIN_SERVER)]	= &BitcoinAcctPB::Instantiate; // FIX THIS LINE! (should create server but none exists yet)
#endif
	
}

OTDB::InitOTDBDetails::~InitOTDBDetails() // Destructor for namespace
{
	OT_ASSERT(NULL != OTDB::pFunctionMap);
	
	delete OTDB::pFunctionMap;
	
	OTDB::pFunctionMap = NULL;
}

// ********************************************************************

// INTERFACE for the Namespace (for coders to use.)


// You might normally create your own Storage object, choosing the storage type
// and the packing type, and then call Init() on that object in order to get it
// up and running.  This function is the equivalent of doing all that, but with the
// DEFAULT storage object (which OT uses when none is specified.)
//
bool OTDB::InitDefaultStorage(OTDB::StorageType eStoreType, OTDB::PackType ePackType,
							  std::string oneStr/*=""*/,  std::string twoStr/*=""*/,  std::string threeStr/*=""*/, 
							  std::string fourStr/*=""*/, std::string fiveStr/*=""*/, std::string sixStr/*=""*/)
{
	// Allows you to call multiple times if you want to change the default storage.
	//
	if (NULL != OTDB::details::s_pStorage)
	{
		delete OTDB::details::s_pStorage;
		OTDB::details::s_pStorage = NULL;
	}
	
	OTDB::details::s_pStorage = OTDB::Storage::Create(eStoreType, ePackType);
	
	if (NULL == OTDB::details::s_pStorage)
		return false;
	
	return OTDB::details::s_pStorage->Init(oneStr, twoStr, threeStr, fourStr, fiveStr, sixStr);
}


// %newobject Factory::createObj();
Storage * OTDB::CreateStorageContext(StorageType eStoreType, PackType ePackType,
									 std::string oneStr/*=""*/,  std::string twoStr/*=""*/,  std::string threeStr/*=""*/, 
									 std::string fourStr/*=""*/, std::string fiveStr/*=""*/, std::string sixStr/*=""*/)
{
	
}

// bool bSuccess = OTDB::Store(strInbox, "inbox", "lkjsdf908w345ljkvd");
// bool bSuccess = OTDB::Store(strMint,  "mints", SERVER_ID, ASSET_ID);
// bool bSuccess = OTDB::Store(strPurse, "purse", SERVER_ID, USER_ID, ASSET_ID);

// BELOW FUNCTIONS use the DEFAULT Storage context.

// -----------------------------------------
// See if the file is there.
bool OTDB::Exists(std::string strFolder, std::string oneStr/*=""*/,  
				  std::string twoStr/*=""*/,  std::string threeStr/*=""*/)
{
	
}

// -----------------------------------------
// Store/Retrieve a string.

bool OTDB::Store(std::string strContents, std::string strFolder, std::string oneStr/*=""*/,  
				 std::string twoStr/*=""*/,  std::string threeStr/*=""*/)
{
	
}

std::string OTDB::Query(std::string strFolder, std::string oneStr/*=""*/,  std::string twoStr/*=""*/,  
						std::string threeStr/*=""*/)
{
	
}

// -----------------------------------------
// Store/Retrieve an object. (Storable.)

bool OTDB::Store(Storable & theContents, std::string strFolder, std::string oneStr/*=""*/,  
				 std::string twoStr/*=""*/,  std::string threeStr/*=""*/)
{
	
}

// Use %newobject OTDB::Storage::Query();
Storable * OTDB::Query(std::string strFolder, std::string oneStr/*=""*/,  std::string twoStr/*=""*/,  
					   std::string threeStr/*=""*/)
{
	
}


// ********************************************************************



/*
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
//	STORE_COUCH_DB,			// Couch DB (not yet supported)
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
*/



// ********************************************************************


Storable * OTDB::Storable:Create(StoredObjectType eType, Packer & thePacker)
{
	if (NULL == OTDB::pFunctionMap)
		return NULL;
	
	Storable * pStorable = NULL;
	
	// The Pack type, plus the Stored Object type, is the Key to the map of function pointers.
	InstantiateFuncKey theKey(thePacker.GetType(), eType);
	
	// If the key works, we get the function pointer to the static Create() method for
	// the appropriate object type.
	
	mapOfFunctions::iterator ii = OTDB::pFunctionMap->find(theKey);
	
	if (OTDB::pFunctionMap->end() == ii)
		return NULL;
	
	InstantiateFunc * pFunc = *ii;
	
	if (NULL != pFunc)
	{
		pStorable = (*pFunc)(); // Now we instantiate the object...
	}
			
	return pStorable; // May return NULL...
}




// ********************************************************************



Packer * OTDB::Packer::Create(PackType ePackType) // Factory.
{
	Packer * pPacker = NULL;
	
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
		default:
			break;
	}
	
	return pPacker; // May return NULL...
}
	

PackType OTDB::Packer::GetType() const
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
	




// ---------------
// Msgpack packer.
#if defined (OTDB_MESSAGE_PACK)

// caller is responsible to delete.
PackedBuffer * OTDB::PackerMsgpack::Pack(Storable& inObj)
{
	/*
	 TEST(pack, OTDB::BitcoinAcct)
	 {
		msgpack::sbuffer sbuf;
		myclass m(1, "msgpack");
		msgpack::pack(sbuf, m);
	 }
	 */
	
	BufferMsgpack * pBuffer = CreateBuffer();
	OT_ASSERT(NULL != pBuffer);
	
	// Must delete pBuffer, or return it, below this point.
	
	msgpack::pack(pBuffer->m_buffer, inObj);

	return pBuffer;
}

bool OTDB::PackerMsgpack::Unpack(PackedBuffer& inBuf, Storable& outObj)
{
	/* 
	 TEST(unpack, OTDB::BitcoinAcct)
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
	
	BufferMsgpack * pBuffer = dynamic_cast<BufferMsgpack*> (&inBuf); 
	
	if (NULL == pBuffer) // Wrong buffer type... should never happen.
		return false;
	
	// --------------------
	
	msgpack::zone z;
	msgpack::object obj;
	
	msgpack::unpack_return ret = msgpack::unpack(pBuffer->m_buffer.data(), 
												 pBuffer->m_buffer.size(), NULL, &z, &obj);
	
	if (msgpack::UNPACK_SUCCESS == ret)
	{	
		obj.convert(&outObj);
		
		return true;
	}
	
	return false;
}

#endif
// ---------------


// ---------------------------
// Protocol Buffers packer.
#if defined (OTDB_PROTOCOL_BUFFERS)

PackedBuffer * OTDB::PackerPB::Pack(Storable& inObj)
{
	
}

bool OTDB::PackerPB::Unpack(PackedBuffer& inBuf, Storable& outObj)
{
	
}

#endif
// ----------------------------------------



// ********************************************************************

// OTDB::STORAGE

// Use this to access the Packer, throughout duration of this Storage object.
// If it doesn't exist yet, this function will create it on the first call. (The 
// parameter allows you the choose what type will be created, other than default.
// You probably won't use it. But if you do, you'll only call it once per instance
// of OTDB::Storage.)
//
Packer * OTDB::Storage::GetPacker(PackType ePackType/*=OTDB_DEFAULT_PACKER*/) 
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
	
// (in .h file) 
// This is called once, in the factory.
// void OTDB::Storage::SetPacker(Packer & thePacker) { OT_ASSERT(NULL == m_pPacker); m_pPacker =  &thePacker; }
	


// Factory for Storable objects.
//
Storable * OTDB::Storage::CreateObject(StoredObjectType eType) 
{
	Packer * pPacker = GetPacker();
	
	if (NULL == pPacker)
		return NULL;
	
	Storable * pStorable = Storable::Create(eType, *pPacker);
	
	return pStorable; // May return NULL.
}
	
// Factory for Storage itself.
//
Storage * OTDB::Storage::Create(StorageType eStorageType, PackType ePackType)
{ 
	Storage * pStore = NULL;
	
	switch (eStorageType) 
	{
		case STORE_FILESYSTEM:
			pStore = new StorageFS; OT_ASSERT(NULL != pStore); break;
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
	
StorageType OTDB::Storage::GetType() const
{
	if (typeid(*this) == typeid(StorageFS))
		return STORE_FILESYSTEM;
//	else if (typeid(*this) == typeid(StorageCouchDB))
//		return STORE_COUCH_DB;
	else
		return STORE_TYPE_SUBCLASS; // The Java coder using API must have subclassed Storage himself.
}
	


// ----------------------------------------------

OTDB::StorageFS::StorageFS() : OTDB::Storage::Storage() 
{
	
}

OTDB::StorageFS::~StorageFS()
{
	
}

bool OTDB::StorageFS::Init(std::string oneStr/*=""*/,  std::string twoStr/*=""*/,  std::string threeStr/*=""*/, 
						   std::string fourStr/*=""*/, std::string fiveStr/*=""*/, std::string sixStr/*=""*/)
{
	// This is where I verify the directory path exists, and the folders within.
	
}


// -----------------------------------------
// See if the file is there.
bool OTDB::StorageFS::Exists(std::string strFolder, std::string oneStr/*=""*/,  
							 std::string twoStr/*=""*/,  std::string threeStr/*=""*/)
{
	
}

// -----------------------------------------
// Store/Retrieve a string.

bool OTDB::StorageFS::Store(std::string strContents, std::string strFolder, std::string oneStr/*=""*/,  
							std::string twoStr/*=""*/,  std::string threeStr/*=""*/)
{
	
}

std::string OTDB::StorageFS::Query(std::string strFolder, std::string oneStr/*=""*/,  
								   std::string twoStr/*=""*/,  std::string threeStr/*=""*/)
{
	
}

// -----------------------------------------
// Store/Retrieve an object. (Storable.)

bool OTDB::StorageFS::Store(Storable & theContents, std::string strFolder, std::string oneStr/*=""*/,  
							std::string twoStr/*=""*/,  std::string threeStr/*=""*/)
{
	
}

// Use %newobject OTDB::Storage::Query();
Storable * OTDB::StorageFS::Query(std::string strFolder, std::string oneStr/*=""*/,  
								  std::string twoStr/*=""*/, std::string threeStr/*=""*/)
{
	
}




// ********************************************************************




