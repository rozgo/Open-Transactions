%module(directors="1") otapi
%{
#include "OTAPI_funcdef.h"
#include "../OTLib/OTAsymmetricKey.h"
%}
 
%include "std_string.i"

%typemap("javapackage") OTCallback, OTCallback *, OTCallback & "com.wrapper.core.jni";
%typemap("javapackage") OTCaller, OTCaller *, OTCaller & "com.wrapper.core.jni";

%feature("director") OTCallback;
%feature("director") OTCaller;

%ignore EVP_PKEY;
%ignore OTAsymmetricKey;
%ignore OT_OPENSSL_CALLBACK;
%ignore OTString;
%ignore OTASCIIArmor;
%ignore default_pass_cb;
%ignore souped_up_pass_cb;

/* Parse the header file to generate wrappers */
%include "OTAPI_funcdef.h"
%include "../OTLib/OTAsymmetricKey.h"






