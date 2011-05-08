
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
	GOOGLE_PROTOBUF_VERIFY_VERSION; 
	OTDB::theMap[std::make_pair(PACK_PROTOCOL_BUFFERS, STORED_OBJ_BITCOIN_ACCT)]	= &BitcoinAcctPB::Instantiate;
	OTDB::theMap[std::make_pair(PACK_PROTOCOL_BUFFERS, STORED_OBJ_BITCOIN_SERVER)]	= &BitcoinAcctPB::Instantiate; // FIX THIS LINE! (should create server but none exists yet)
#endif
	
}

OTDB::InitOTDBDetails::~InitOTDBDetails() // Destructor for namespace
{
	OT_ASSERT(NULL != OTDB::pFunctionMap);
	
	delete OTDB::pFunctionMap;
	
	OTDB::pFunctionMap = NULL;
	
	// ------------------------------------------
	
#if defined (OTDB_PROTOCOL_BUFFERS)
	google::protobuf::ShutdownProtobufLibrary();
#endif
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
Storage * OTDB::CreateStorageContext(StorageType eStoreType, PackType ePackType)
{
	Storage * pStorage = OTDB::Storage::Create(eStoreType, ePackType);
	
	return pStorage;	// caller responsible to delete
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
	Storage * pStorage = OTDB::details::s_pStorage;

	if (NULL == pStorage) 
	{
		return false;
	}
	
	return pStorage->Exists(strFolder, oneStr, twoStr, threeStr);
}

// -----------------------------------------
// Store/Retrieve a string.

bool OTDB::StoreString(std::string strContents, std::string strFolder, std::string oneStr/*=""*/,  
					   std::string twoStr/*=""*/,  std::string threeStr/*=""*/)
{
	Storage * pStorage = OTDB::details::s_pStorage;
	
	if (NULL == pStorage) 
	{
		return false;
	}
	
	return pStorage->StoreString(strContents, strFolder, oneStr, twoStr, threeStr);
}

std::string OTDB::QueryString(std::string strFolder, std::string oneStr/*=""*/,  std::string twoStr/*=""*/,  
							  std::string threeStr/*=""*/)
{
	Storage * pStorage = OTDB::details::s_pStorage;
	
	if (NULL == pStorage) 
	{
		return std::string("");
	}
	
	return pStorage->QueryString(strFolder, oneStr, twoStr, threeStr);
}

// -----------------------------------------
// Store/Retrieve an object. (Storable.)

bool OTDB::StoreObject(Storable & theContents, std::string strFolder, std::string oneStr/*=""*/,  
					   std::string twoStr/*=""*/,  std::string threeStr/*=""*/)
{
	Storage * pStorage = OTDB::details::s_pStorage;
	
	if (NULL == pStorage) 
	{
		return false;
	}
	
	return pStorage->StoreObject(theContents, strFolder, oneStr, twoStr, threeStr);
}

// Use %newobject OTDB::Storage::Query();
Storable * OTDB::QueryObject(std::string strFolder, std::string oneStr/*=""*/,  std::string twoStr/*=""*/,  
							 std::string threeStr/*=""*/)
{
	Storage * pStorage = OTDB::details::s_pStorage;
	
	if (NULL == pStorage) 
	{
		return NULL;
	}
	
	return pStorage->QueryObject(strFolder, oneStr, twoStr, threeStr);
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


// static. Packer Factory.
Packer * OTDB::Packer::Create(PackType ePackType)
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
		case PACK_TYPE_ERROR:
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


// Basically, ALL of the Storables have to implement the IStorable interface 
// (or one of its subclasses).  They can override hookBeforePack(), and they
// can override onPack(). Those two methods will be where all the action is,
// for each subclass of Packer.
//
PackedBuffer * OTDB::Packer::Pack(Storable& inObj)
{
	IStorable * pStorable = dynamic_cast<IStorable *> (&inObj);
	
	if (NULL == pStorable)
		return NULL;
	
	// --------------------------------
	
	PackedBuffer * pBuffer = CreateBuffer();
	OT_ASSERT(NULL != pBuffer);
	
	// Must delete pBuffer, or return it, below this point.
	
	// -------------------------------------
	
	pStorable->hookBeforePack(); // Give the subclass a chance to prepare its data for packing...
	
	// I ended up using polymorphic templates, but not in this func. This line
	// (commented out) shows how the line below it would have looked otherwise.
	//	if (false == makeTStorable(*pStorable).pack(*pBuffer))
	
	if (false == pStorable->onPack(*pBuffer))
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
bool OTDB::Packer::Unpack(PackedBuffer& inBuf, Storable& outObj)
{
	IStorable * pStorable = dynamic_cast<IStorable *> (&outObj);
	
	if (NULL == pStorable)
		return false;
	
	// --------------------------------
	// pStorable is the OUTPUT OBJECT.
	// If we're unable to unpack the contents of inBuf
	// into pStorable, return false.
	//
	if (false == pStorable->onUnpack(inBuf))
	{
		return false;
	}
	
	// ---------------------------
	
	pStorable->hookAfterUnpack(); // Give the subclass a chance to settle its data after unpacking...
	
	return true;	
}

// --------------------------------------------------------------------------







// ---------------------------------------------
// Msgpack packer.
#if defined (OTDB_MESSAGE_PACK)

bool OTDB::IStorableMsgpack::onPack(PackedBuffer& theBuffer)  // buffer is OUTPUT.
{
	// check here to make sure theBuffer is the right TYPE.
	BufferMsgpack * pBuffer = dynamic_cast<BufferMsgpack *> (&theBuffer);
	
	if (NULL == pBuffer) // Buffer is wrong type!!
		return false;
	
	
	msgpack::pack(pBuffer->m_buffer, inObj);
	
	
	if (false == getPBMessage().SerializeToString(&(pBuffer->m_strBuffer)))
		return false;
	
	return true;
}

bool OTDB::IStorableMsgpack::onUnpack(PackedBuffer& theBuffer, Storable& outObj) // buffer is INPUT, Storable is OUTPUT.
{
	// check here to make sure theBuffer is the right TYPE.
	BufferMsgpack * pBuffer = dynamic_cast<BufferMsgpack *> (&theBuffer);
	
	if (NULL == pBuffer) // Buffer is wrong type!!
		return false;
	
	
	
	
	
	
	if (false == getPBMessage().ParseFromString(pBuffer->m_strBuffer))
		return false;
	
	return true;
}

// ---------------------------------------------

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

#endif  // defined (OTDB_MESSAGE_PACK)
// -------------------------------------------





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

// --------------------------------------------
// Protocol Buffers packer.
#if defined (OTDB_PROTOCOL_BUFFERS)

//	if (false == makeTStorable(*pStorable).pack(*pBuffer))
::google::protobuf::Message	&	OTDB::IStorablePB::getPBMessage() 
{
	return makeTStorablePB(*this).getPBMessage();
}

bool OTDB::IStorablePB::onPack(PackedBuffer& theBuffer)  // buffer is OUTPUT.
{
	// check here to make sure theBuffer is the right TYPE.
	BufferPB * pBuffer = dynamic_cast<BufferPB *> (&theBuffer);
	
	if (NULL == pBuffer) // Buffer is wrong type!!
		return false;
	
	if (false == getPBMessage().SerializeToString(&(pBuffer->m_strBuffer)))
		return false;
	
	return true;
}

bool OTDB::IStorablePB::onUnpack(PackedBuffer& theBuffer, Storable& outObj) // buffer is INPUT.
{
	// check here to make sure theBuffer is the right TYPE.
	BufferPB * pBuffer = dynamic_cast<BufferPB *> (&theBuffer);
	
	if (NULL == pBuffer) // Buffer is wrong type!!
		return false;
	
	// bool ParseFromString(const string& data); parses a message from the given string.

	if (false == getPBMessage().ParseFromString(pBuffer->m_strBuffer))
		return false;
	
	return true;
}


// ADD THE HOOK HERE FOR "AFTER UNPACK" <=====  TODO
// Actually... this might have to be in the individual subclasses...
// (For protocol buffers anyway, though I think I can come up with a #define for this...)
// At least that's now possible :-)
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

bool OTDB::StorageFS::StoreString(std::string strContents, std::string strFolder, std::string oneStr/*=""*/,  
								  std::string twoStr/*=""*/,  std::string threeStr/*=""*/)
{
	
}

std::string OTDB::StorageFS::QueryString(std::string strFolder, std::string oneStr/*=""*/,  
										 std::string twoStr/*=""*/,  std::string threeStr/*=""*/)
{
	
}

// -----------------------------------------
// Store/Retrieve an object. (Storable.)

bool OTDB::StorageFS::StoreObject(Storable & theContents, std::string strFolder, std::string oneStr/*=""*/,  
								  std::string twoStr/*=""*/,  std::string threeStr/*=""*/)
{
	
}

// Use %newobject OTDB::Storage::Query();
Storable * OTDB::StorageFS::QueryObject(std::string strFolder, std::string oneStr/*=""*/,  
										std::string twoStr/*=""*/, std::string threeStr/*=""*/)
{
	
}




// ********************************************************************




