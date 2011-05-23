/**************************************************************
 *    
 *  OTASCIIArmor.cpp
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


#include <cstring>
#include <cstdlib>

extern "C"
{
#include <inttypes.h>  //uint8_t

#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
}

// I use ezcompress once and ezuncompress once.
// Basically I compress the strings before they
// are ascii-armored, to save space.
// If it turns out I can't use this lib, then I'll
// just do the same thing using zlib instead of easyzlib.
// I'm avoiding that since it won't be as easy. Ha.
#include "easyzlib.h"

#include "OTLog.h"
#include "OTStorage.h"


#include "OTString.h"
#include "OTASCIIArmor.h"
#include "OTEnvelope.h"






// initializes blank.
OTASCIIArmor::OTASCIIArmor() : OTString()
{
	
}

// encodes
OTASCIIArmor::OTASCIIArmor(const OTString & strValue) : OTString(/*Don't pass here, since we're encoding.*/)
{
	this->SetString(strValue);
}

// Copies (already encoded)
OTASCIIArmor::OTASCIIArmor(const OTASCIIArmor & strValue) : OTString(dynamic_cast<const OTString&>(strValue))
{
	
}


// assumes envelope contains encrypted data; 
// grabs that data in base64-form onto *this.
OTASCIIArmor::OTASCIIArmor(const OTEnvelope & theEnvelope) : OTString()
{
	theEnvelope.GetAsciiArmoredData(*this);
}


// copies (already encoded)
OTASCIIArmor::OTASCIIArmor(const char * szValue) : OTString(szValue)
{

}

// -------------------------------------------------------------

// copies, assumes already encoded.
OTASCIIArmor & OTASCIIArmor::operator=(const char * szValue)
{
	this->Set(szValue);
	return *this;
}

// encodes
OTASCIIArmor & OTASCIIArmor::operator=(const OTString & strValue)
{
	if ((&strValue) != (&(dynamic_cast<const OTString&>(*this))))
	{
		this->SetString(strValue);
	}
	return *this;	
}

// assumes is already encoded and just copies the encoded text
OTASCIIArmor & OTASCIIArmor::operator=(const OTASCIIArmor & strValue)
{
	if ((&strValue) != this) // prevent self-assignment
	{
		this->OTString::operator=(dynamic_cast<const OTString&>(strValue));
	}
	return *this;
}



extern "C" {
char *OT_base64_encode(const uint8_t* input, int in_len, int bLineBreaks)
{
    char *buf = NULL;
	
    BIO * bmem = NULL;
	BIO * b64  = NULL;
    BUF_MEM *bptr = NULL;
	
    b64 = BIO_new(BIO_f_base64());
    
	if (!b64) 
		return buf;
    
	if (!bLineBreaks) 
	{
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    }
	
    bmem = BIO_new(BIO_s_mem());
    
	if (bmem) 
	{
        b64 = BIO_push(b64, bmem);
		
        if (BIO_write(b64, input, in_len)==in_len) 
		{
            (void)BIO_flush(b64);
            BIO_get_mem_ptr(b64, &bptr);
			
//			OTLog::vOutput(5, "DEBUG base64_encode size: %ld,  in_len: %ld\n", bptr->length+1, in_len);
			
            buf = new char[bptr->length+1];
			
			OT_ASSERT(NULL != buf);
			
			memcpy(buf, bptr->data, bptr->length);  // Safe.
			buf[bptr->length] = '\0';
        }
    }
	else 
	{
		OT_ASSERT_MSG(false, "Failed creating new Bio in base64_encode.\n");
	}
	
    BIO_free_all(b64);
	
    return buf;
}

uint8_t* OT_base64_decode(const char *input, size_t* out_len, int bLineBreaks)
{
    BIO *bmem = NULL, *b64 = NULL;
	
	OT_ASSERT(NULL != input);
	
    int in_len = strlen(input);
    int out_max_len=(in_len*6+7)/8;
    unsigned char *buf = new unsigned char [out_max_len];
	
	OT_ASSERT(NULL != buf);
	
	memset(buf, 0, out_max_len);

	b64 = BIO_new(BIO_f_base64());
	
	if (b64) 
	{
		if (!bLineBreaks) 
		{
			BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
		}
		bmem = BIO_new_mem_buf((char*)input, in_len);
		b64 = BIO_push(b64, bmem);
		*out_len = BIO_read(b64, buf, out_max_len);
		BIO_free_all(b64);
	}
	else 
	{
		OT_ASSERT_MSG(false, "Failed creating new Bio in base64_decode.\n");
	}

    return buf;
}
} // extern "C"




/* More code for Base64 Decoding using OpenSSL:
 
 void base64Decode(unsigned char* pIn, int inLen, unsigned char* pOut,
 int& outLen)
 {
 // create a memory buffer containing base64 encoded data
 BIO* bmem = BIO_new_mem_buf((void*)pIn, inLen);
 
 // push a Base64 filter so that reading from buffer decodes it
 BIO *bioCmd = BIO_new(BIO_f_base64());
 // we don't want newlines
 BIO_set_flags(bioCmd, BIO_FLAGS_BASE64_NO_NL);
 bmem = BIO_push(bioCmd, bmem);
 
 int finalLen = BIO_read(bmem, (void*)pOut, outLen);
 BIO_free_all(bmem);
 outLen = finalLen;
 }
 
 Another example of similar code:
 
 char *unbase64(unsigned char *input, int length)
 {
 BIO *b64, *bmem;
 
 char *buffer = (char *)malloc(length);
 memset(buffer, 0, length);
 
 b64 = BIO_new(BIO_f_base64());
 bmem = BIO_new_mem_buf(input, length);
 bmem = BIO_push(b64, bmem);
 
 BIO_read(bmem, buffer, length);
 
 BIO_free_all(bmem);
 
 return buffer;
 }
 

 */


// easyzlib knows, if the result buffer isn't big enough to 
// store the results, 
#define DEFAULT_BUFFER_SIZE_EASYZLIB	16384

// This function will base64 DECODE the string contents
// and return them as a string in theData
// It also handles uncompression afterwards.

bool OTASCIIArmor::GetString(OTString & theData, bool bLineBreaks) const //bLineBreaks=true
{	
	size_t		outSize	= 0;
	uint8_t *	pData	= NULL;
	
	theData.Release();
	
	if (GetLength() < 1) {
		return true;
	}
	
	pData = OT_base64_decode(Get(), &outSize, (bLineBreaks ? 1 : 0));
	
	if (pData)
	{
		 long nDestLen = DEFAULT_BUFFER_SIZE_EASYZLIB; // todo stop hardcoding numbers (but this one is OK I think.)
		 unsigned char* pDest = new unsigned char [nDestLen+10]; // For safety.
		 
		OT_ASSERT(NULL != pDest);
		
		 int nErr = ezuncompress( pDest, &nDestLen, pData, outSize );
		 if ( nErr == EZ_BUF_ERROR )
		 {
			 delete [] pDest;
			 pDest = new unsigned char [nDestLen]; // enough room now
			 
			 OT_ASSERT(NULL != pDest);
			 
			 nErr = ezuncompress( pDest, &nDestLen, pData, outSize );
		 }
		 
		// Now we're done with this memory, let's free it.
		delete [] pData; pData=NULL;
		
		// ----------------------------------------
		
		if ( nErr == EZ_BUF_ERROR )
		{
			delete [] pDest;
			pDest = NULL;
			
			OT_ASSERT_MSG(false, "Buffer error in OTASCIIArmor::GetString\n");
			return false; // not really necessary but just making sure.
		}
		else if ( nErr == EZ_STREAM_ERROR )
		{
			delete [] pDest;
			pDest = NULL;
			
			OT_ASSERT_MSG(false, "pDest is NULL in OTASCIIArmor::GetString\n");
			return false; // not really necessary but just making sure.
		}
		else if ( nErr == EZ_DATA_ERROR )
		{
			delete [] pDest;
			pDest = NULL;
			
			OTLog::vError("corrupted pSrc passed to ezuncompress OTASCIIArmor::GetString, size: %d\n", outSize);
			
			OT_ASSERT(false);
			
			return false; // not really necessary but just making sure.
		}
		else if ( nErr == EZ_MEM_ERROR )
		{
			delete [] pDest;
			pDest = NULL;
			
			OT_ASSERT_MSG(false, "Out of memory in OTASCIIArmor::GetString\n");
			return false; // not really necessary but just making sure.
		}
		
		// This enforces the null termination. (using the extra parameter nDestLen as nEnforcedMaxLength)
		 theData.Set((const char*)pDest, nDestLen);
	
		delete [] pDest; pDest=NULL; 
		return true;
	}
	else 
	{
		OTLog::Error("NULL pData while base64_decodeing pData.\n");
		return false;
	}
}



/*
// This function will base64 DECODE the string contents
// and return them as a string in theData
// It does NOT handle Uncompression

bool OTASCIIArmor::GetString(OTString & theData, bool bLineBreaks) const //=true
{	
	size_t		outSize	= 0;
	uint8_t *	pData	= NULL;
	
	pData = base64_decode(Get(), &outSize, (bLineBreaks ? 1 : 0));
	
	if (pData)
	{
		theData.Set((const char*)pData, outSize);
		
		delete [] pData; pData=NULL;
		return true;
	}
	else {
		return false;
	}
}


// This function will base64 ENCODE string stored in theData,
// and then Set() that as the string contents for *this.
// It does NOT handle compression.

bool OTASCIIArmor::SetString(const OTString & theData, bool bLineBreaks) // =true
{
	char *	pString	= NULL;
	
	// Now let's base-64 encode it...										// +1 for the null terminator.
	pString = base64_encode((const uint8_t*)theData.Get(), theData.GetLength(), (bLineBreaks ? 1 : 0));
	//	pString = base64_encode((const uint8_t*)theData.Get(), theData.GetLength()+1, (bLineBreaks ? 1 : 0)); // this was before we used compression.
		
	if (pString)
	{
		Set(pString);
		delete [] pString; pString=NULL; // I'm using free here because I believe base64_encode is using malloc
		return true;
	}
	
	return false;
}
*/



// This version is fully functional, and performs compression in addition to base64-encoding.
// I have currently deactivated it in order to use a version that only supports encoding, but doesn't
// support compression.


 bool OTASCIIArmor::SetString(const OTString & theData, bool bLineBreaks) //=true
{
//	OTLog::vError("DEBUGGING OTASCIIARMOR::SETSTRING, INPUT:  --------->%s<---------", theData.Get());
	
	Release();
	
	if (theData.GetLength() < 1)
		return true;
	
	char *	pString	= NULL;
	
	// Set up source buffer and destination buffer
	long nDestLen	= DEFAULT_BUFFER_SIZE_EASYZLIB; // todo stop hardcoding numbers (but this one is OK I think.)
	const	long lSourcelen	= sizeof(unsigned char)*theData.GetLength()+1;// for null terminator
	
	unsigned char* pSource	= new unsigned char[lSourcelen+10]; // for safety
	unsigned char* pDest	= new unsigned char[nDestLen+10]; // for safety
	
	OT_ASSERT(NULL != pSource);
	OT_ASSERT(NULL != pDest);
	
	memcpy(pSource, (const unsigned char*)theData.Get(), lSourcelen );
	
	// Now we are compressing first before base64-encoding (for strings, anyway)	
	int nErr = ezcompress( pDest, &nDestLen, pSource, lSourcelen );
	
	// If the destination buffer wasn't the right size the first time around,
	// then we re-allocate it to the right size (which we now know) and try again...
	if ( nErr == EZ_BUF_ERROR )
	{
		delete [] pDest;
		pDest = new unsigned char [nDestLen]; // enough room now
		
		OT_ASSERT(NULL != pDest);
		
		nErr = ezcompress( pDest, &nDestLen, pSource, lSourcelen );
	}
	
	// Clean this up...
	delete [] pSource;
	pSource = NULL;

	// Still errors?
	if ( nErr == EZ_BUF_ERROR )
	{
		delete [] pDest;
		pDest = NULL;	
		
		OT_ASSERT_MSG(false, "Error allocating memory in OTASCIIArmor::SetString\n");
		return false; // not really necessary but just making sure.
	}
	else if ( nErr == EZ_STREAM_ERROR )
	{
		delete [] pDest;
		pDest = NULL;	

		OT_ASSERT_MSG(false, "pDest is NULL in OTASCIIArmor::SetString\n");
		return false; // not really necessary but just making sure.
	}
	else if ( nErr == EZ_DATA_ERROR )
	{
		delete [] pDest;
		pDest = NULL;	

		OT_ASSERT_MSG(false, "corrupted pSrc passed to ezuncompress OTASCIIArmor::SetString\n");
		return false; // not really necessary but just making sure.
	}
	else if ( nErr == EZ_MEM_ERROR )
	{
		delete [] pDest;	
		pDest = NULL;

		OT_ASSERT_MSG(false, "Out of memory in OTASCIIArmor::SetString\n");
		return false; // not really necessary but just making sure.
	}
	
	
	OT_ASSERT_MSG(pDest != NULL, "pDest NULL in OTASCIIArmor::SetString\n");
	
	// Success
	if (0 < nDestLen)
	{
		// Now let's base-64 encode it...
		pString = OT_base64_encode((const uint8_t*)pDest, nDestLen, (bLineBreaks ? 1 : 0));
	//	pString = OT_base64_encode((const uint8_t*)theData.Get(), theData.GetLength()+1, (bLineBreaks ? 1 : 0)); // this was before we used compression.
		
		delete [] pDest;
		pDest = NULL;
		
		if (pString)
		{
			Set(pString);
			delete [] pString; pString=NULL; 
			return true;
		}
		else 
		{
			OTLog::Error("pString NULL in OTASCIIArmor::SetString\n");
		}
	}
	else 
	{
		OTLog::Error("nDestLen 0 in OTASCIIArmor::SetString\n");
	}
	
	if (pDest)
		delete [] pDest;

	pDest = NULL;
	
	return false;
}



// This function will base64 DECODE the string contents
// and return them as binary in theData
bool OTASCIIArmor::GetData(OTData & theData, bool bLineBreaks) const //linebreaks=true
{	
	size_t		outSize	= 0;
	uint8_t *	pData	= NULL;
	
	theData.Release();
	
	if (GetLength() < 1)
		return true;
	
	pData = OT_base64_decode(Get(), &outSize, (bLineBreaks ? 1 : 0));
	
	if (pData)
	{
		theData.Assign(pData, outSize);
		delete [] pData; pData=NULL;
		return true;
	}
	else 
	{
		OTLog::Error("Error while base64_decoding in OTASCIIArmor::GetData.\n");
		return false;
	}
}

// This function will base64 ENCODE theData,
// and then Set() that as the string contents.
bool OTASCIIArmor::SetData(const OTData & theData, bool bLineBreaks/*=true*/)
{
	char *	pString	= NULL;
	
	Release();
	
	if (theData.GetSize() < 1)
		return true;
	
	pString = OT_base64_encode((const uint8_t*)theData.GetPointer(), theData.GetSize(), (bLineBreaks ? 1 : 0));
	
	if (pString)
	{
		Set(pString);
		delete [] pString; pString=NULL;
		return true;
	}
	else 
	{
		OTLog::Error("Error while base64_encoding in OTASCIIArmor::GetData.\n");
		return false;
	}
}


// This code reads up the file, discards the bookends, and saves only the gibberish itself.
bool OTASCIIArmor::LoadFromFile(const OTString & foldername, const OTString & filename)
{	
	/*
	std::ifstream fin(filename.Get(), std::ios::binary);
		
	if (!fin.is_open())
	{
		OTLog::vError("Error opening file in OTASCIIArmor::LoadFromFile: %s\n", filename.Get());
		return false;
	}

	return LoadFromifstream(fin);	
	 */
	
	OT_ASSERT(foldername.Exists());
	OT_ASSERT(filename.Exists());
	
	// --------------------------------------------------------------------
	
	OTLog::Error("DEBUG OTASCIIArmor 0 \n");
	
	if (false == OTDB::Exists(foldername.Get(), filename.Get()))
	{
		OTLog::vError("OTASCIIArmor::LoadFromFile: File does not exist: %s%s%s\n", 
					  foldername.Get(), OTLog::PathSeparator(), filename.Get());
		return false;
	}
	OTLog::Error("DEBUG OTASCIIArmor 1 \n");
	
	// --------------------------------------------------------------------
	//
	OTString strFileContents(OTDB::QueryPlainString(foldername.Get(), filename.Get())); // <=== LOADING FROM DATA STORE.
	
	if (strFileContents.GetLength() < 2)
	{
		OTLog::vError("OTASCIIArmor::LoadFromFile: Error reading file: %s%s%s\n", 
					  foldername.Get(), OTLog::PathSeparator(), filename.Get());
		return false;
	}
	OTLog::Error("DEBUG OTASCIIArmor 2 \n");

	// --------------------------------------------------------------------
	
	return LoadFromString(strFileContents);	
}

// This code reads up the file, discards the bookends, and saves only the gibberish itself.
bool OTASCIIArmor::LoadFromifstream(const std::ifstream & fin)
{
	std::stringstream buffer;
	buffer << fin.rdbuf();
	
	std::string contents(buffer.str());
	
	OTString theString;
	theString.Set(contents.c_str());
	
	return LoadFromString(theString);	
}


// This code reads up the file, discards the bookends, and saves only the gibberish itself.
// the bEscaped option allows you to load a normal ASCII-Armored file if off, and allows
// you to load an escaped ASCII-armored file (such as inside the contracts when the public keys
// are escaped with a "- " before the rest of the ------- starts.)
bool OTASCIIArmor::LoadFromString(OTString & theStr, bool bEscaped/*=false*/)
{
	char buffer1[2100];
	
	memset(buffer1, 0, 2100);
	
	bool bContentMode = false;				// "currently in content mode"
	bool bHaveEnteredContentMode = false;	// "have yet to enter content mode"
	
	// Clear out whatever string might have been in there before.
	Release();
	
	// Load up the string from theStr, 
	// (bookended by "-----BEGIN ... -----" and END messages)
	bool bIsEOF = false;
	theStr.reset(); // So we can call theStr.sgets(). Making sure position is at start of string.
	
	do
	{
		bIsEOF = !(theStr.sgets(buffer1, 2048));
		//		bIsEOF = fin.getline(buffer1, 2048).eof();
		
		std::string line		= buffer1;	
		const char * pConstBuf	= line.c_str();
		char * pBuf				= (char *)pConstBuf;
		
		// It's not a blank line.
		if (line.length() < 2)
		{
			continue;
		}
		
		// if we're on a dashed line...
		else if (line.at(0) == '-' && line.at(2) == '-' && line.at(3) == '-'
				 && (bEscaped ? (line.at(1) == ' ') : (line.at(1) == '-') ) )
		{			
			// If I just hit a dash, that means there are only two options:
			
			// a. I have not yet entered content mode, and potentially just now entering it for the first time.
			if (!bHaveEnteredContentMode)
			{
				if (line.find("BEGIN")!=std::string::npos && line.at(0) == '-' && line.at(2) == '-' && 
					line.at(3) == '-' && (bEscaped ? (line.at(1) == ' ') : (line.at(1) == '-')))
				{
//					OTLog::Error("Reading ascii-armored contents...");
					bHaveEnteredContentMode = true;
					bContentMode = true;
					continue;
				}
				else
				{
					continue;
				}				
				
			}
			
			// b. I am now LEAVING content mode!
			else if (bContentMode && line.find("END")!=std::string::npos)
			{
//				OTLog::Error("Finished reading ascii-armored contents.\n");
//				OTLog::vError("Finished reading ascii-armored contents:\n%s(END DATA)\n", Get());
				bContentMode   = false;
				continue;
			}
		}
		
		
		// Else we're on a normal line, not a dashed line.
		else
		{
			if (bHaveEnteredContentMode && bContentMode)
			{
				if (line.compare(0,8,"Version:") == 0)
				{
//					OTLog::Error("Skipping version line...\n");
					continue;
				}
			}
			
		}
		
		// Here we save the line to member variables, if appropriate
		if (bContentMode)
		{
			Concatenate("%s\n", pBuf);
		}
	}
	while(!bIsEOF && (bContentMode || !bHaveEnteredContentMode));
	
	
	// reset the string position back to 0
	theStr.reset();
	
	if (!bHaveEnteredContentMode)
	{
		OTLog::Error("Error in OTASCIIArmor::LoadFromString: EOF before ascii-armored content found.\n");
		return false;
	}
	else if (bContentMode)
	{
		OTLog::Error("Error in OTASCIIArmor::LoadFromString: EOF while still reading content.\n");
		return false;
	}
	else
		return true;
}


OTASCIIArmor::~OTASCIIArmor()
{
	// ~OTString called automatically, which calls Release().
}

