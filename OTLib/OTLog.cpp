/*******************************************************************
 *    
 *  OTLog.cpp
 *  
 */

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


// The long-awaited logging class.


#include <cstdarg>
#include <cstdio>
#include <cstring> // The C one 
#include <cstdlib>
#include <cctype>
#include <cassert>
#include <iostream>

#include <string> // The C++ one 



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


#ifdef ANDROID
#include <android/log.h>
#endif


#include "OTString.h"
#include "OTLog.h"



// If it MUST output, set the verbosity to 0. Less important logs are
// at higher and higher levels.
//
// All are sent to stdout, but the 0 are the most important ones.
// By default, only those are actually logged. If you want to see the other messages,
// then set this log level to a higher value sometime when you start execution.
// (Or right here.)

#if defined (DSP)					   
int OTLog::__CurrentLogLevel = -1;	// If you build with DSP=1, it assumes a special location for OpenSSL,
#else								// and it turns off all the output.
int OTLog::__CurrentLogLevel = 3;
#endif

OTString OTLog::__Version = "0.63";



// ---------------------------------------------------------------------------------
// This is the "global" path to the subdirectories. The wallet file is probably also there.
OTString OTLog::__OTPath("."); // it defaults to '.' but then it is set by the client and server.

// All my paths now use the global path above, and are constructed using
// the path separator below. So the filesystem aspect of Open Transactions
// should be a LOT more portable to Windows, though I haven't actually tried
// it on Windows.
#ifdef _WIN32
OTString OTLog::__OTPathSeparator = "\\";
#else
OTString OTLog::__OTPathSeparator = "/";
#endif

// ---------------------------------------------------------------------------------


// Just a default value, since this is configurable programmatically.


OTString OTLog::__OTCronFolder		= "cron";		
OTString OTLog::__OTNymFolder		= "nyms";		
OTString OTLog::__OTAccountFolder	= "accounts";	
OTString OTLog::__OTUserAcctFolder	= "useraccounts";	
OTString OTLog::__OTReceiptFolder	= "receipts";		
OTString OTLog::__OTNymboxFolder	= "nymbox";		
OTString OTLog::__OTInboxFolder		= "inbox";		
OTString OTLog::__OTOutboxFolder	= "outbox";		
OTString OTLog::__OTCertFolder		= "certs";		
OTString OTLog::__OTPubkeyFolder	= "pubkeys";
OTString OTLog::__OTContractFolder	= "contracts";
OTString OTLog::__OTMintFolder		= "mints";
OTString OTLog::__OTSpentFolder		= "spent";
OTString OTLog::__OTPurseFolder		= "purse";
OTString OTLog::__OTMarketFolder	= "markets";



// --------------------------------------------------

dequeOfStrings OTLog::__logDeque; // Stores the last 1024 logs in memory.


const char * OTLog::GetMemlogAtIndex(int nIndex)
{
	unsigned int uIndex = static_cast<unsigned int> (nIndex);
	
	if ((uIndex < 0) || (uIndex >= __logDeque.size()))
	{
		OTLog::vError("OTLog::GetMemlogAtIndex: index out of bounds: %d\n", nIndex);
		return NULL;
	}
	
	OTString * pStr = __logDeque.at(uIndex);
	
	if ((NULL != pStr) && (pStr->Exists()))
		return pStr->Get();
	
	return NULL;
}


// --------------------------------------------------
// We keep 1024 logs in memory, to make them available via the API.

int OTLog::GetMemlogSize() 
{
	return __logDeque.size();
}


const char * OTLog::PeekMemlogFront()
{
	if (__logDeque.size() <= 0)
		return NULL;
	
	OTString * pStr = __logDeque.front();
	
	if ((NULL != pStr) && (pStr->Exists()))
		return pStr->Get();
	
	return NULL;
}


const char * OTLog::PeekMemlogBack()
{
	if (__logDeque.size() <= 0)
		return NULL;
	
	OTString * pStr = __logDeque.back();
	
	if ((NULL != pStr) && (pStr->Exists()))
		return pStr->Get();
	
	return NULL;	
}


bool OTLog::PopMemlogFront()
{
	if (__logDeque.size() <= 0)
		return false;
	
	OTString * pStr = __logDeque.front();
	
	if (NULL != pStr)
	{
		delete pStr;
		pStr = NULL;
	}
	
	__logDeque.pop_front();
	
	return true;		
}


bool OTLog::PopMemlogBack()
{
	if (__logDeque.size() <= 0)
		return false;
	
	OTString * pStr = __logDeque.back();
	
	if (NULL != pStr)
	{
		delete pStr;
		pStr = NULL;
	}
	
	__logDeque.pop_back();
	
	return true;			
}


bool OTLog::PushMemlogFront(const char * szLog)
{
	OT_ASSERT(NULL != szLog);
	
	OTString * pStr = new OTString(szLog);
	
	OT_ASSERT(NULL != pStr);

	__logDeque.push_front(pStr);
	
	if (__logDeque.size() > 1024) // todo: stop hardcoding.
	{
		OTLog::PopMemlogBack(); // We start removing from the back when it reaches this size.
	}
	
	return true;
}

bool OTLog::PushMemlogBack(const char * szLog)
{
	OT_ASSERT(NULL != szLog);
	
	OTString * pStr = new OTString(szLog);
	
	OT_ASSERT(NULL != pStr);
	
	__logDeque.push_back(pStr);
	
	return true;	
}


// --------------------------------------------------


/*
 void sleep( unsigned int in_mseconds )
 {
 
 }
 
 
 void ssleep( unsigned int in_seconds )
 {
 }
 */



// ---------------------------------------------------------------------------------

void OTLog::SleepSeconds(long lSeconds)
{
#ifdef _WIN32
	Sleep(1000 * lSeconds);
#else
	sleep(lSeconds);
#endif	
}


void OTLog::SleepMilliseconds(long lMilliseconds)
{
#ifdef _WIN32
	Sleep( lMilliseconds );
#else
	usleep( lMilliseconds * 1000 );
#endif	
}


// ---------------------------------------------------------------------------------


// Private; never actually called.
OTLog::OTLog()
{
	
}

// Never actually called. Never instantiated.
OTLog::~OTLog()
{
	
}

// -------------------------------------------------------

// This function is for things that should NEVER happen.
// In fact you should never even call it -- use the OT_ASSERT() macro instead.

int OTLog::Assert(const char * szFilename, int nLinenumber, const char * szMessage)
{
	if (NULL != szMessage)
	{
#ifndef ANDROID // if NOT android
		std::cerr << szMessage << "\n";
#else // if Android
		__android_log_write(ANDROID_LOG_FATAL,"OT Assert", szMessage);
#endif		
	}
	
	return OTLog::Assert(szFilename, nLinenumber);
}

int OTLog::Assert(const char * szFilename, int nLinenumber)
{
	if ((NULL != szFilename))
	{
#ifndef ANDROID // if NOT android
		std::cerr << "OT_ASSERT in " << szFilename << " at line " << nLinenumber << "\n";
#else // if Android
		OTString strAndroidAssertMsg;
		strAndroidAssertMsg.Format("\nOT_ASSERT in %s at line %d\n", szFilename, nLinenumber);
		__android_log_write(ANDROID_LOG_FATAL,"OT Assert", (const char *)strAndroidAssertMsg.Get());
#endif
	}
	
	abort();
	return -1;
}


// -------------------------------------------------------

// For normal output. The higher the verbosity, the less important the message.
// (Verbose level 0 ALWAYS logs.) Currently goes to stdout.

void OTLog::Output(int nVerbosity, const char *szOutput)
{
	// If log level is 0, and verbosity of this message is 2, don't bother logging it.
//	if (nVerbosity > OTLog::__CurrentLogLevel || (NULL == szOutput))
	if ((nVerbosity > OTLog::__CurrentLogLevel) || (NULL == szOutput) || (OTLog::__CurrentLogLevel == (-1)))		
		return; 

	// We store the last 1024 logs so programmers can access them via the API.
	OTLog::PushMemlogFront(szOutput);
	
#ifndef ANDROID // if NOT android
	std::cout << szOutput;

	//	printf(szOutput); // Right now this goes to stdout, but could be changed to a file.
#else // if Android
	/*
	 typedef enum android_LogPriority {
	 ANDROID_LOG_UNKNOWN = 0,
	 ANDROID_LOG_DEFAULT,    // only for SetMinPriority()
	 ANDROID_LOG_VERBOSE,
	 ANDROID_LOG_DEBUG,
	 ANDROID_LOG_INFO,
	 ANDROID_LOG_WARN,
	 ANDROID_LOG_ERROR,
	 ANDROID_LOG_FATAL,
	 ANDROID_LOG_SILENT,     // only for SetMinPriority(); must be last
	 } android_LogPriority;
	 */
	switch (nVerbosity) {
		case 0:
		case 1:
			__android_log_write(ANDROID_LOG_INFO,"OT Output", szOutput);
			break;
		case 2:
		case 3:
			__android_log_write(ANDROID_LOG_DEBUG,"OT Debug", szOutput);
			break;
		case 4:
		case 5:
			__android_log_write(ANDROID_LOG_VERBOSE,"OT Verbose", szOutput);
			break;
		default:
			__android_log_write(ANDROID_LOG_UNKNOWN,"OT Unknown", szOutput);
			break;
	}
#endif
}

void OTLog::Output(int nVerbosity, OTString & strOutput)
{
	if (strOutput.Exists())
		OTLog::Output(nVerbosity, strOutput.Get());
}

// the vOutput is to avoid name conflicts.
void OTLog::vOutput(int nVerbosity, const char *szOutput, ...)
{
	// If log level is 0, and verbosity of this message is 2, don't bother logging it.
	if (nVerbosity > OTLog::__CurrentLogLevel || (NULL == szOutput))
		return; 
	
	va_list args;
	
   	// _WIN32
	static char * new_string = NULL;
	
	if (NULL == new_string)
	{
		new_string = new char[MAX_STRING_LENGTH]; // This only happens once -- static var.
		
		OT_ASSERT(NULL != new_string);
		
		memset(new_string, 0, MAX_STRING_LENGTH);
	}
	
	new_string[0] = '\0';
	// _end _WIN32
	
	va_start(args, szOutput);
	
#ifdef _WIN32
	vsprintf_s(new_string, MAX_STRING_LENGTH, szOutput, args);
#else
	vsnprintf(new_string, MAX_STRING_LENGTH, szOutput, args);
#endif
	
	va_end(args);
	
	OTLog::Output(nVerbosity, new_string);
}



// -----------------------------------------------------------------

// An error has occurred, that somehow doesn't match the Assert or Output functions.
// So use this one instead.  This ALWAYS logs and currently it all goes to stderr.

void OTLog::Error(const char *szError)
{
	if ((NULL == szError))
		return; 
	
	// We store the last 1024 logs so programmers can access them via the API.
	OTLog::PushMemlogFront(szError);

#ifndef ANDROID // if NOT android
	std::cerr << szError;
	//	fprintf(stderr, szError); // Right now this goes to stderr, but could be changed to a file.
#else // if Android
	__android_log_write(ANDROID_LOG_ERROR,"OT Error", szError);
#endif
}

void OTLog::Error(OTString & strError)
{
	if (strError.Exists())
		OTLog::Error(strError.Get());
}

// the vError name is to avoid name conflicts
void OTLog::vError(const char *szError, ...)
{
	if ((NULL == szError))
		return; 
	
	va_list args;
	
   	// _WIN32
	static char * new_string = NULL;
	
	if (NULL == new_string)
	{
		new_string = new char[MAX_STRING_LENGTH]; // This only happens once -- static var.
		
		OT_ASSERT(NULL != new_string);
		
		memset(new_string, 0, MAX_STRING_LENGTH);
	}
	
	new_string[0] = '\0';
	// _end _WIN32
	
	va_start(args, szError);
	
#ifdef _WIN32
	vsprintf_s(new_string, MAX_STRING_LENGTH, szError, args);
#else
	vsnprintf(new_string, MAX_STRING_LENGTH, szError, args);
#endif
	
	va_end(args);
	
	OTLog::Error(new_string);
}







// Used for making sure that certain necessary folders actually exist. (Creates them otherwise.)
//
// If you pass in "spent", then this function will make sure that "<path>/spent" actually exists, 
// or create it. WARNING: If what you want to pass is "spent/sub-folder-to-spent" then make SURE
// you call it with "spent" FIRST, so you are sure THAT folder has been created, otherwise the
// folder creation will definitely fail on the sub-folder call (if the primary folder wasn't
// already there, that is.)
//
bool OTLog::ConfirmOrCreateFolder(const char * szFolderName)
{
	OT_ASSERT(NULL != szFolderName);
	
	
	// DIRECTORY IS PRESENT?
	struct stat st;
	
	OTString strPath;
	strPath.Format("%s%s%s", OTLog::Path(), OTLog::PathSeparator(), szFolderName);
	
	bool bDirIsPresent = (0 == stat(strPath.Get(), &st));
	
	// ----------------------------------------------------------------------------
	
	// IF NO, CREATE IT
	if (!bDirIsPresent)
	{
#ifdef _WIN32
		if (_mkdir(strPath.Get()) == -1) 
#else
			if (mkdir(strPath.Get(), 0700) == -1) 
#endif
			{
				OTLog::vError("OTLog::ConfirmOrCreateFolder: Unable to create %s.\n",
							  strPath.Get());
				return false;
			}
		
		// Now we have created it, so let's check again...
		bDirIsPresent = (0 == stat(strPath.Get(), &st));
		
		if (bDirIsPresent)
			OTLog::vOutput(0, "Created folder: %s\n", strPath.Get());
	}
	
	// ----------------------------------------------------------------------------
	
	// At this point if the folder still doesn't exist, nothing we can do. We
	// already tried to create the folder, and SUCCEEDED, and then STILL failed 
	// to find it (if this is still false.)
	if (!bDirIsPresent)
	{
		OTLog::vError("OTLog::ConfirmOrCreateFolder: Unable to find newly-created folder: %s\n", 
					  strPath.Get());
		return false;
	}
	
	return true;
}	

// Returns true or false whether a specific file exists.
// Adds the main path prior to checking.
bool OTLog::ConfirmFile(const char * szFileName)
{
	OT_ASSERT(NULL != szFileName);
	
	
	// FILE IS PRESENT?
	struct stat st;
	
	OTString strPath;
	strPath.Format("%s%s%s", OTLog::Path(), OTLog::PathSeparator(), szFileName);
	
	return (0 == stat(strPath.Get(), &st));
}


// Returns true or false whether a specific file exists.
bool OTLog::ConfirmExactPath(const char * szFileName)
{
	OT_ASSERT(NULL != szFileName);
	
	// FILE IS PRESENT?
	struct stat st;
	
	OTString strPath;
	strPath.Format("%s", szFileName);
	
	return (0 == stat(strPath.Get(), &st));
}





















































