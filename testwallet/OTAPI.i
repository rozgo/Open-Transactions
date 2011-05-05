%module(directors="1") otapi
%{
#include <string>
#include "../OTLib/OTAsymmetricKey.h"
#include "OTAPI_funcdef.h"
%}
 
%include "std_string.i"

%typemap("javapackage") OTCallback, OTCallback *, OTCallback & "com.wrapper.core.jni";
%typemap("javapackage") OTCaller, OTCaller *, OTCaller & "com.wrapper.core.jni";

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


/* Parse the header file to generate wrappers */
%include "OTAPI_funcdef.h"






