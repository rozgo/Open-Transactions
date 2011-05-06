
#include "OTStorage.h"

using namespace OTDB;



// "private" to the namespace.
// Use OTDB::GetDefaultStorage() to access this variable.
// Use OTDB::InitDefaultStorage() to set up this variable.
//
Storage * OTDB::details::s_pStorage = NULL;



Storable::Storable()




// You might normally create your own Storage object, choosing the storage type
// and the packing type, and then call Init() on that object in order to get it
// up and running.  This function is the equivalent of doing all that, but with the
// DEFAULT storage object (which OT uses when none is specified, which will probably
// be most or all of the time.)
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



bool OTDB::StorageFS::Init(std::string oneStr/*=""*/,  std::string twoStr/*=""*/,  std::string threeStr/*=""*/, 
						   std::string fourStr/*=""*/, std::string fiveStr/*=""*/, std::string sixStr/*=""*/)
{
	// This is where I verify the directory path exists, and the folders within.
	
}



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

	// This example 
	OTDB::Store(theAcct);
 
  
 */



/*
 
 TEST(pack, OTDB::BitcoinAcct)
 {
 msgpack::sbuffer sbuf;
 myclass m(1, "msgpack");
 msgpack::pack(sbuf, m);
 }
 
 
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