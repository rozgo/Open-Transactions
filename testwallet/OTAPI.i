%module(directors="1") otapi
%{
#include <string>
#include <map>
#include "../OTLib/OTAsymmetricKey.h"
#include "OTAPI_funcdef.h"
#include "../OTLib/OTStorage.h"
%}
 
%include "std_string.i";
%include "typemaps.i"

// ---------------------------------------------------------------
#ifdef SWIGJAVA

%include "java/enumtypeunsafe.swg";

%typemap("javapackage") OTCallback, OTCallback *, OTCallback & "com.wrapper.core.jni";
%typemap("javapackage") OTCaller, OTCaller *, OTCaller & "com.wrapper.core.jni";

%typemap("javapackage") Storage, Storage *, Storage & "com.wrapper.core.jni";
%typemap("javapackage") Storable, Storable *, Storable & "com.wrapper.core.jni";

%typemap("javapackage") StringMap, StringMap *, StringMap & "com.wrapper.core.jni";
%typemap("javapackage") BitcoinAcct, BitcoinAcct *, BitcoinAcct & "com.wrapper.core.jni";
%typemap("javapackage") BitcoinServer, BitcoinServer *, BitcoinServer & "com.wrapper.core.jni";
%typemap("javapackage") ServerInfo, ServerInfo *, ServerInfo & "com.wrapper.core.jni";
%typemap("javapackage") ContactNym, ContactNym *, ContactNym & "com.wrapper.core.jni";
%typemap("javapackage") ContactAcct, ContactAcct *, ContactAcct & "com.wrapper.core.jni";
%typemap("javapackage") Contact, Contact *, Contact & "com.wrapper.core.jni";
%typemap("javapackage") AddressBook, AddressBook *, AddressBook & "com.wrapper.core.jni";
%typemap("javapackage") WalletData, WalletData *, WalletData & "com.wrapper.core.jni";

%typemap("javapackage") InitDefaultStorage "com.wrapper.core.jni";
%typemap("javapackage") GetDefaultStorage "com.wrapper.core.jni";
%typemap("javapackage") CreateStorageContext "com.wrapper.core.jni";
%typemap("javapackage") CreateObject "com.wrapper.core.jni";
%typemap("javapackage") Exists "com.wrapper.core.jni";
%typemap("javapackage") StoreString "com.wrapper.core.jni";
%typemap("javapackage") QueryString "com.wrapper.core.jni";
%typemap("javapackage") StorePlainString "com.wrapper.core.jni";
%typemap("javapackage") QueryPlainString "com.wrapper.core.jni";
%typemap("javapackage") StoreObject "com.wrapper.core.jni";
%typemap("javapackage") QueryObject "com.wrapper.core.jni";

%typemap("javapackage") PackType "com.wrapper.core.jni";
%typemap("javapackage") StorageType "com.wrapper.core.jni";
%typemap("javapackage") StoredObjectType "com.wrapper.core.jni";

#endif
// ---------------------------------------------------------------


%feature("director") OTCallback;




class OTCallback 
{
public:
	OTCallback() {}
	virtual ~OTCallback();
	virtual std::string runOne();
	virtual std::string runTwo();
};


class OTCaller 
{
protected:
	std::string m_strPW;
	OTCallback *_callback;
	
public:
	OTCaller() : _callback(NULL) { }
	~OTCaller();
	
	const char * GetPassword();
	
	void delCallback();
	void setCallback(OTCallback *cb);
	bool isCallbackSet();
	
	void callOne();
	void callTwo();
};

bool OT_API_Set_PasswordCallback(OTCaller & theCaller);



//%apply int *INPUT {int *x, int *y};
//%apply SWIGTYPE *INPUT {int *x, int *y};


%ignore Storable::Create(StoredObjectType eType, PackType thePackType);

%ignore PackedBuffer;

%ignore OTPacker;

%ignore PackerSubclass;

%ignore Storage::Create(StorageType eStorageType, PackType ePackType);

%ignore stat;

%ignore std::istream;

%ignore std::ostream;

%ignore msgpack::sbuffer;

%ignore std::map<std::string, std::string>;

%ignore stlplus::simple_ptr_clone;

// -------------------------------------------

// So there aren't memory leaks from passing the objects back and forth.

//%apply SWIGTYPE & DISOWN { SWIGTYPE & disownObject };

// //
//%apply SWIGTYPE * DISOWN {wxCaret* caret};

//DEFAULT REFERENCE HANDLING
//%typemap(in) SWIGTYPE & { ... default reference handling ...};

//%typemap(in) SWIGTYPE & DISOWN { SWIGTYPE & disownObject };
//
//%typemap(in) SWIGTYPE *DISOWN { BitcoinAcct & disownObject };
//
//%typemap(in) SWIGTYPE *DISOWN { BitcoinServer & disownObject };
//
//%typemap(in) SWIGTYPE *DISOWN { ServerInfo & disownObject };
//
//%typemap(in) SWIGTYPE *DISOWN { ContactNym & disownObject };
//
//%typemap(in) SWIGTYPE *DISOWN { ContactAcct & disownObject };
//
//%typemap(in) SWIGTYPE *DISOWN { Contact & disownObject };


%newobject CreateObject(StoredObjectType eType);

%newobject QueryObject(StoredObjectType theObjectType, std::string strFolder, std::string oneStr="", std::string twoStr="", std::string threeStr="");

%newobject Storage::QueryObject(StoredObjectType theObjectType, std::string strFolder, std::string oneStr="", std::string twoStr="", std::string threeStr="");

%newobject Storage::CreateObject(StoredObjectType eType);

%newobject CreateStorageContext(StorageType eStoreType, PackType ePackType=OTDB_DEFAULT_PACKER);



// -------------------------------------------
//
%define OT_STORABLE_TYPE(STORABLE_TYPE, CONTAINER_TYPE)
#ifdef SWIGJAVA
// These two blocks enable the object to dynamic cast back
// to its true type, after factory construction.
%exception STORABLE_TYPE::dynamic_cast(Storable * pObject) {
	$action
	if (!result) {
		jclass excep = jenv->FindClass("java/lang/ClassCastException");
		if (excep) {
			jenv->ThrowNew(excep, "dynamic_cast exception");
		}
	}
}
%extend STORABLE_TYPE {
	static STORABLE_TYPE * dynamic_cast(Storable * pObject) {
		return dynamic_cast<STORABLE_TYPE *>(pObject);
	}
};
// ----------------
// The STORABLE_TYPE (BitcoinAcct, say) keeps a reference to its OT_CONTAINER (WalletData).
// USE THIS TYPEMAP *INSIDE* MOST DATA TYPES. (They ALL potentially could be inside a container.)
//
%typemap(javacode) STORABLE_TYPE %{
	// Ensure that the GC doesn't collect any OT_CONTAINER instance set from Java
	private CONTAINER_TYPE containerReference;
	
	protected void addReference(CONTAINER_TYPE theContainer) {
		containerReference = theContainer;
	}
// ----------------
// ----------------
	private List elementList = new ArrayList();
	// This list is used by OT_CONTAINER_HELPER. (below.)
%}
#endif
%enddef

// -------------------------------------------------------------------------------


// The CONTAINER_TYPE (WalletData) uses this for EACH Get/Add/Remove item within.
// So this macro appears multiple times, if there are multiple deques.
//
%define OT_CONTAINER_HELPER(STORABLE_TYPE, CONTAINER_TYPE)
#ifdef SWIGJAVA
%typemap(javain) STORABLE_TYPE & disownObject "getCPtrAndAddReference($javainput)"

// When the CONTAINER_TYPE's "getOT_Element" function is called, 
// Add a Java reference to prevent premature garbage collection and resulting use
// of dangling C++ pointer. Intended for methods that return pointers or
// references to a member variable.
%typemap(javaout) STORABLE_TYPE * Get##STORABLE_TYPE {
    long cPtr = $jnicall;
    $javaclassname ret = null;
    if (cPtr != 0) {
		ret = new $javaclassname(cPtr, $owner);
		ret.addReference(this);
    }
    return ret;
}

// This changes the CONTAINER_TYPE class to keep an internal reference to the STORABLE_TYPE.
//
%typemap(javacode) CONTAINER_TYPE %{
	// Ensure that the GC doesn't collect any STORABLE_TYPE set from Java
	// as the underlying C++ class stores a shallow copy
	
	private STORABLE_TYPE the##STORABLE_TYPE##Reference;
	
	// Altered the SWIG example so that we store a list of these references, instead
	// of only the latest one. None of them should go out of scope until this object does.
	
	private long getCPtrAndAddReference(STORABLE_TYPE element) {
		the##STORABLE_TYPE##Reference = element;
		elementList.add(the##STORABLE_TYPE##Reference);
		return STORABLE_TYPE.getCPtr(element);
	}	// Hope I get away with overloading this for every type. Otherwise,
		// hope I can just change the function name to customize it to type.
protected:
		std::deque< stlplus::simple_ptr_clone<STORABLE_TYPE> > list_##STORABLE_TYPE##s;
	public:
		size_t Get##STORABLE_TYPE##Count();
		STORABLE_TYPE * Get##STORABLE_TYPE(size_t nIndex);
		bool Remove##STORABLE_TYPE(size_t nIndex);
		bool Add##STORABLE_TYPE(STORABLE_TYPE & disownObject)	
	
%}		
#endif
%enddef


// ------------------------------------------------





/* Parse the header file to generate wrappers */
%include "OTAPI_funcdef.h"



namespace OTDB { 


enum PackType // PACKING TYPE
{
	PACK_MESSAGE_PACK = 0,	// Using MessagePack as packer.
	PACK_PROTOCOL_BUFFERS,	// Using Google Protocol Buffers as packer.
	PACK_TYPE_ERROR		// (Should never be.)
};
	
enum StorageType  // STORAGE TYPE
{
	STORE_FILESYSTEM = 0,	// Filesystem
//	STORE_COUCH_DB,			// Couch DB (not yet supported)
	STORE_TYPE_SUBCLASS		// (Subclass provided by API client via SWIG.)
};
	
enum StoredObjectType
{
	STORED_OBJ_STRING=0,		// Just a string.
	STORED_OBJ_STRING_MAP,		// A StringMap is a list of Key/Value pairs, useful for storing nearly anything.
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



class Storage
{
private:
	OTPacker * m_pPacker;
	
protected:
	Storage() : m_pPacker(NULL) {}
	
	Storage(const Storage & rhs) : m_pPacker(NULL) { } // We don't want to copy the pointer. Let it create its own.
	
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
	
	// Use %newobject Storage::Query();
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

// bool bSuccess = StoreString(strInbox, "inbox", "lkjsdf908w345ljkvd");
// bool bSuccess = StoreString(strMint,  "mints", SERVER_ID, ASSET_ID);
// bool bSuccess = StoreString(strPurse, "purse", SERVER_ID, USER_ID, ASSET_ID);

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

// Use %newobject Storage::Query();
Storable * QueryObject(StoredObjectType theObjectType,
					   std::string strFolder, std::string oneStr="",
					   std::string twoStr="", std::string threeStr="");		


// ------------------------------------------------

	
	
	
	
class String : public Storable
{
	// You never actually get an instance of this, only its subclasses.
	// Therefore, I don't allow you to access the constructor except through the factory.
protected:
	String() : Storable() { }
	String(const std::string& rhs) : Storable(), m_string(rhs) { }
	
public:
	virtual ~String() { }
	
	std::string m_string;

	OT_STORABLE_TYPE(String, Storable)
};
	
// ------------------------------------------------
	
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

	OT_STORABLE_TYPE(StringMap, Storable)
};

	
// ------------------------------------------------

class Displayable : public Storable
{
	// You never actually get an instance of this, only its subclasses.
	// Therefore, I don't allow you to access the constructor except through factory.
protected:
	Displayable() : Storable() { }
	
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
	Acct() : Displayable() { }
	
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
	BitcoinAcct() : Acct() { }
	
public:
	virtual ~BitcoinAcct() { }
	
	//		std::string gui_label;  // The label that appears in the GUI
	
	//		std::string acct_id;
	//		std::string server_id;
	
	std::string bitcoin_acct_name;

	OT_STORABLE_TYPE(BitcoinAcct, WalletData)
};

// **************************************************

// SERVER (GUI local storage about servers.)

class ServerInfo : public Displayable
{
	// You never actually get an instance of this, only its subclasses.
	// Therefore, I don't allow you to access the constructor except through factory.
protected:
	ServerInfo() : Displayable() { }
	
public:
	virtual ~ServerInfo() { }
	
//	std::string gui_label;  // The label that appears in the GUI
	
	std::string server_id;
	std::string server_type;

	OT_STORABLE_TYPE(ServerInfo, ContactNym)
};

// ----------------------------
	
class Server : public ServerInfo
{
	// You never actually get an instance of this, only its subclasses.
	// Therefore, I don't allow you to access the constructor except through factory.
protected:
	Server() : ServerInfo() { }
	
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
	BitcoinServer() : Server() { }
	
public:
	virtual ~BitcoinServer() { }
	
	//		std::string gui_label;  // The label that appears in the GUI
	
	//		std::string server_id;   // in base class
	//		std::string server_type; // in base class
	
	//		std::string server_host;
	//		std::string server_port;
	
	std::string bitcoin_username;
	std::string bitcoin_password;

	OT_STORABLE_TYPE(BitcoinServer, WalletData)
};

// ----------------------------	
	
		
// ----------------------------	

class ContactNym : public Displayable
{
	// You never actually get an instance of this, only its subclasses.
	// Therefore, I don't allow you to access the constructor except through factory.
protected:
	ContactNym() : Displayable() { }
	
public:
	virtual ~ContactNym();
	
	//		std::string gui_label;  // The label that appears in the GUI
	
	std::string nym_type;
	std::string nym_id;
	std::string public_key;
	std::string memo;
	
	OT_STORABLE_TYPE(ContactNym, Contact)
	
	OT_CONTAINER_HELPER(ServerInfo, ContactNym)
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
	
	OT_STORABLE_TYPE(WalletData, Storable)

	OT_CONTAINER_HELPER(BitcoinServer, WalletData)
	OT_CONTAINER_HELPER(BitcoinAcct, WalletData)
};
	
class ContactAcct : public Displayable {
	// You never actually get an instance of this, only its subclasses.
	// Therefore, I don't allow you to access the constructor except through factory.
protected:
	ContactAcct() : Displayable() { }
	
public:
	virtual ~ContactAcct() { }
	
//	std::string gui_label;  // The label that appears in the GUI
	
	std::string server_type;
	std::string server_id;
	std::string asset_type_id;
	std::string acct_id;
	std::string nym_id;
	std::string memo;
	std::string public_key;

	OT_STORABLE_TYPE(ContactAcct, Contact)
};

// ----------------------------
	
	
class Contact : public Displayable {
	// You never actually get an instance of this, only its subclasses.
	// Therefore, I don't allow you to access the constructor except through factory.
protected:
	Contact() : Displayable() { }
	
public:
	virtual ~Contact();
	
//		std::string gui_label;  // The label that appears in the GUI
	
	std::string contact_id;
	std::string email;
	std::string memo;
	std::string public_key;

	OT_STORABLE_TYPE(Contact, AddressBook)
	
	OT_CONTAINER_HELPER(ContactNym, Contact)
	OT_CONTAINER_HELPER(ContactAcct, Contact)
};
	
// ----------------------------

class AddressBook : public Storable {
	// You never actually get an instance of this, only its subclasses.
	// Therefore, I don't allow you to access the constructor except through factory.
protected:
	AddressBook() : Storable() { }
	
public:
	virtual ~AddressBook();
	
	OT_STORABLE_TYPE(AddressBook, Storable)

	OT_CONTAINER_HELPER(Contact, AddressBook)
};

// ----------------------------
	
	
	

	
	
} // namespace OTDB 




%inline %{
	using namespace OTDB;
	%}




%feature("director") Storage;








