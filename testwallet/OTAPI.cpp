/************************************************************************************
 *    
 *  OTAPI.cpp   -- Implementation for the C interface. (Written in C++)
 *	               C Programmers can include OTAPI.h and call these functions
 *                 as if they were calling straight C functions. OTAPI.h is also
 *                 wrapped by SWIG, making this same interface available in many
 *                 other languages (Java, Python, Ruby, Perl, Php, etc)
 *
 *        Open Transactions:  Library, Protocol, Server, and Test Client
 *    
 *    			-- Anonymous Numbered Accounts
 *    			-- Untraceable Digital Cash
 *    			-- Triple-Signed Receipts
 *    			-- Basket Currencies
 *    			-- Signed XML Contracts
 *    
 *    Copyright (C) 2010 by "Fellow Traveler" (A pseudonym)
 *    
 *    EMAIL:
 *    F3llowTraveler@gmail.com --- SEE PGP PUBLIC KEY IN CREDITS FILE.
 *    
 *    KEY FINGERPRINT:
 *    9DD5 90EB 9292 4B48 0484  7910 0308 00ED F951 BB8E
 *    
 *    WEBSITE:
 *    http://www.OpenTransactions.org
 *    
 *    OFFICIAL PROJECT WIKI:
 *    http://wiki.github.com/FellowTraveler/Open-Transactions/
 *    
 *     ----------------------------------------------------------------
 *    
 *    Open Transactions was written including these libraries:
 *    
 *       Lucre          --- Copyright (C) 1999-2009 Ben Laurie.
 *                          http://anoncvs.aldigital.co.uk/lucre/
 *       irrXML         --- Copyright (C) 2002-2005 Nikolaus Gebhardt
 *                          http://irrlicht.sourceforge.net/author.html	
 *       easyzlib       --- Copyright (C) 2008 First Objective Software, Inc.
 *                          Used with permission. http://www.firstobject.com/
 *       PGP to OpenSSL --- Copyright (c) 2010 Mounir IDRASSI 
 *                          Used with permission. http://www.idrix.fr
 *       SFSocket       --- Copyright (C) 2009 Matteo Bertozzi
 *                          Used with permission. http://th30z.netsons.org/
 *    
 *     ----------------------------------------------------------------
 *
 *    Open Transactions links to these libraries:
 *    
 *       OpenSSL        --- (Version 1.0.0a at time of writing.) 
 *                          http://openssl.org/about/
 *       zlib           --- Copyright (C) 1995-2004 Jean-loup Gailly and Mark Adler
 *    
 *     ----------------------------------------------------------------
 *
 *    LICENSE:
 *        This program is free software: you can redistribute it and/or modify
 *        it under the terms of the GNU Affero General Public License as
 *        published by the Free Software Foundation, either version 3 of the
 *        License, or (at your option) any later version.
 *    
 *        You should have received a copy of the GNU Affero General Public License
 *        along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *    	
 *    	  If you would like to use this software outside of the free software
 *    	  license, please contact FellowTraveler.
 *   
 *        This library is also "dual-license", meaning that Ben Laurie's license
 *        must also be included and respected, since the code for Lucre is also
 *        included with Open Transactions.
 *        The Laurie requirements are light, but if there is any problem with his
 *        license, simply remove the Lucre code. Although there are no other blind
 *        token algorithms in Open Transactions (yet), the other functionality will
 *        continue to operate .
 *    
 *    OpenSSL WAIVER:
 *        This program is released under the AGPL with the additional exemption 
 *    	  that compiling, linking, and/or using OpenSSL is allowed.
 *    
 *    DISCLAIMER:
 *        This program is distributed in the hope that it will be useful,
 *        but WITHOUT ANY WARRANTY; without even the implied warranty of
 *        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *        GNU Affero General Public License for more details.
 *    	
 ************************************************************************************/


#include <cstring>


#include "OTIdentifier.h"
#include "OTString.h"
#include "OTPseudonym.h"
#include "OTAssetContract.h"
#include "OTServerContract.h"
#include "OTCheque.h"
#include "OTMint.h"
#include "OTLedger.h"
#include "OTAccount.h"
#include "OTWallet.h"
#include "OTPurse.h"


// A C++ class, high-level interface to OT. The class-based API.
#include "OpenTransactions.h"

// This is for an extern "C" (though written in C++) wrapper for a global instance of the above.
// (In order to be able to call Open Transactions from C, as well as use SWIG and call it from
// php, perl, ruby, python, tcl, java, lisp, etc.)
#include "OTAPI.h"

#include "OTLog.h"


// These functions are in C, so they can't return bool. But they can return BOOL!
// They appear as int in the header, for SWIG reasons.
//
#ifndef OT_BOOL
#define OT_BOOL int
#endif

#ifndef OT_FALSE
const int OT_FALSE = 0;
#endif

#ifndef OT_TRUE
const int OT_TRUE = 1;
#endif




// This global variable contains an OTWallet, an OTClient, etc. 
// It's the C++ high-level interace to OT. 
// Any client software will have an instance of this.
OT_API g_OT_API; 
// Note: Must call OT_API::Init() followed by g_OT_API.Init() in the main function, before using OT.


// To use this extern "C" API, you must call this function first.
// (Therefore the same is true for all scripting languages that use this file...
// Ruby, Python, Perl, PHP, etc.)
OT_BOOL OT_API_Init(const char * szClientPath)
{
	OT_ASSERT(NULL != szClientPath);
	
	static bool bAlreadyInitialized = false;
	
	if (!bAlreadyInitialized)
	{
		bAlreadyInitialized = true;
		
		if (OT_API::InitOTAPI())
		{
			OTString strClientPath(szClientPath);
			bool bInit = g_OT_API.Init(strClientPath);  // SSL gets initialized in here, before any keys are loaded.
			
			if (bInit)
				return OT_TRUE;
		}
	}
	
	return OT_FALSE;
}



OT_BOOL OT_API_LoadWallet(const char * szPath)
{
	OT_ASSERT(NULL != szPath);

	OTString strPath(szPath);
	
	bool bLoaded = g_OT_API.LoadWallet(strPath);
	
	if (bLoaded)
		return OT_TRUE;
	
	return OT_FALSE;
}



// --------------------------------------------------




int OT_API_GetNymCount(void)
{
	return g_OT_API.GetNymCount();
}

int OT_API_GetServerCount(void)
{
	return g_OT_API.GetServerCount();
}

int OT_API_GetAssetTypeCount(void)
{
	return g_OT_API.GetAssetTypeCount();
}

int OT_API_GetAccountCount(void)
{
	return g_OT_API.GetAccountCount();
}


static char g_tempBuf[MAX_STRING_LENGTH];


// based on Index (above 4 functions) this returns the Nym's ID
const char * OT_API_GetNym_ID(int nIndex)
{
	OT_ASSERT(nIndex >= 0);
	
	OTIdentifier	theNymID;
	OTString		strName;
	
	bool bGetNym = g_OT_API.GetNym(nIndex, theNymID, strName);
	
	if (bGetNym)
	{
		OTString strNymID(theNymID);
		
		const char * pBuf = strNymID.Get();

#ifdef _WIN32
		strcpy_s(g_tempBuf, MAX_STRING_LENGTH, pBuf);
#else
		strlcpy(g_tempBuf, pBuf, MAX_STRING_LENGTH);
#endif
	
		return g_tempBuf;
	}
	
	return NULL;
}

// Returns Nym Name (based on NymID)
const char * OT_API_GetNym_Name(const char * NYM_ID)
{
	OT_ASSERT(NULL != NYM_ID);
	
	OTIdentifier	theNymID(NYM_ID);
	
	OTPseudonym * pNym = g_OT_API.GetNym(theNymID);
	
	if (NULL != pNym)
	{
		OTString & strName = pNym->GetNymName();
		const char * pBuf = strName.Get();
		
#ifdef _WIN32
		strcpy_s(g_tempBuf, MAX_STRING_LENGTH, pBuf);
#else
		strlcpy(g_tempBuf, pBuf, MAX_STRING_LENGTH);
#endif
		
		return g_tempBuf;
	}
	
	return NULL;
}

// based on Index (above 4 functions) this returns the Server's ID
const char * OT_API_GetServer_ID(int nIndex)
{
	OT_ASSERT(nIndex >= 0);
	
	OTIdentifier	theID;
	OTString		strName;
	
	bool bGetServer = g_OT_API.GetServer(nIndex, theID, strName);
	
	if (bGetServer)
	{
		OTString strID(theID);
		
		const char * pBuf = strID.Get();
		
#ifdef _WIN32
		strcpy_s(g_tempBuf, MAX_STRING_LENGTH, pBuf);
#else
		strlcpy(g_tempBuf, pBuf, MAX_STRING_LENGTH);
#endif
		
		return g_tempBuf;		
	}
	return NULL;
}


// Return's Server's name (based on server ID)
const char * OT_API_GetServer_Name(const char * THE_ID)
{
	OT_ASSERT(NULL != THE_ID);
	
	OTIdentifier	theID(THE_ID);
	
	OTServerContract * pContract = g_OT_API.GetServer(theID);
	
	if (NULL != pContract)
	{
		OTString strName;
		pContract->GetName(strName);
		const char * pBuf = strName.Get();
		
#ifdef _WIN32
		strcpy_s(g_tempBuf, MAX_STRING_LENGTH, pBuf);
#else
		strlcpy(g_tempBuf, pBuf, MAX_STRING_LENGTH);
#endif
		
		return g_tempBuf;
	}
	
	return NULL;
}

// returns Asset Type ID (based on index from GetAssetTypeCount)
const char * OT_API_GetAssetType_ID(int nIndex)
{
	OT_ASSERT(nIndex >= 0);
	
	OTIdentifier	theID;
	OTString		strName;
	
	bool bGetServer = g_OT_API.GetAssetType(nIndex, theID, strName);
	
	if (bGetServer)
	{
		OTString strID(theID);
		
		const char * pBuf = strID.Get();
		
#ifdef _WIN32
		strcpy_s(g_tempBuf, MAX_STRING_LENGTH, pBuf);
#else
		strlcpy(g_tempBuf, pBuf, MAX_STRING_LENGTH);
#endif
		
		return g_tempBuf;		
	}
	return NULL;
}

// Returns asset type Name based on Asset Type ID
const char * OT_API_GetAssetType_Name(const char * THE_ID)
{
	OT_ASSERT(NULL != THE_ID);
	
	OTIdentifier	theID(THE_ID);
	
	OTAssetContract * pContract = g_OT_API.GetAssetType(theID);
	
	if (NULL != pContract)
	{
		OTString strName;
		pContract->GetName(strName);
		const char * pBuf = strName.Get();
		
#ifdef _WIN32
		strcpy_s(g_tempBuf, MAX_STRING_LENGTH, pBuf);
#else
		strlcpy(g_tempBuf, pBuf, MAX_STRING_LENGTH);
#endif
		
		return g_tempBuf;
	}
	
	return NULL;
}



// returns a string containing the account ID, based on index.
const char * OT_API_GetAccountWallet_ID(int nIndex)
{
	OT_ASSERT(nIndex >= 0);
	
	OTIdentifier	theID;
	OTString		strName;
	
	bool bGetServer = g_OT_API.GetAccount(nIndex, theID, strName);
	
	if (bGetServer)
	{
		OTString strID(theID);
		
		const char * pBuf = strID.Get();
		
#ifdef _WIN32
		strcpy_s(g_tempBuf, MAX_STRING_LENGTH, pBuf);
#else
		strlcpy(g_tempBuf, pBuf, MAX_STRING_LENGTH);
#endif
		
		return g_tempBuf;		
	}
	return NULL;
}


// returns the account name, based on account ID.
const char * OT_API_GetAccountWallet_Name(const char * THE_ID)
{
	OT_ASSERT(NULL != THE_ID);
	
	OTIdentifier	theID(THE_ID);
	
	OTAccount * pContract = g_OT_API.GetAccount(theID);
	
	if (NULL != pContract)
	{
		OTString strName;
		pContract->GetName(strName);
		const char * pBuf = strName.Get();
		
#ifdef _WIN32
		strcpy_s(g_tempBuf, MAX_STRING_LENGTH, pBuf);
#else
		strlcpy(g_tempBuf, pBuf, MAX_STRING_LENGTH);
#endif
		
		return g_tempBuf;
	}
	
	return NULL;
}


// returns the account balance, based on account ID.
const char * OT_API_GetAccountWallet_Balance(const char * THE_ID)
{
	OT_ASSERT(NULL != THE_ID);
	
	OTIdentifier	theID(THE_ID);
	
	OTAccount * pContract = g_OT_API.GetAccount(theID);
	
	if (NULL != pContract)
	{
		long lBalance = pContract->GetBalance();
		
		OTString strBalance;
		
		strBalance.Format("%ld", lBalance);
		
		const char * pBuf = strBalance.Get();
		
#ifdef _WIN32
		strcpy_s(g_tempBuf, MAX_STRING_LENGTH, pBuf);
#else
		strlcpy(g_tempBuf, pBuf, MAX_STRING_LENGTH);
#endif
		
		return g_tempBuf;
	}
	
	return NULL;	
}



// returns an account's "account type", (simple, issuer, etc.)
const char * OT_API_GetAccountWallet_Type(const char * THE_ID)
{
	OT_ASSERT(NULL != THE_ID);
	
	OTIdentifier	theID(THE_ID);
	
	OTAccount * pContract = g_OT_API.GetAccount(theID);
	
	if (NULL != pContract)
	{		
		const char * pBuf = pContract->GetTypeString();
		
#ifdef _WIN32
		strcpy_s(g_tempBuf, MAX_STRING_LENGTH, pBuf);
#else
		strlcpy(g_tempBuf, pBuf, MAX_STRING_LENGTH);
#endif
		
		return g_tempBuf;
	}
	
	return NULL;	
}



// Returns an account's asset type ID, based on account ID.
// (Which is a hash of the contract used to issue the asset type.)
const char * OT_API_GetAccountWallet_AssetTypeID(const char * THE_ID)
{
	OT_ASSERT(NULL != THE_ID);
	
	OTIdentifier	theID(THE_ID);
	
	OTAccount * pContract = g_OT_API.GetAccount(theID);
	
	if (NULL != pContract)
	{		
		OTString strAssetTypeID(pContract->GetAssetTypeID());
		
		const char * pBuf = strAssetTypeID.Get(); 
		
#ifdef _WIN32
		strcpy_s(g_tempBuf, MAX_STRING_LENGTH, pBuf);
#else
		strlcpy(g_tempBuf, pBuf, MAX_STRING_LENGTH);
#endif
		
		return g_tempBuf;
	}
	
	return NULL;	
}


// --------------------------------------------------




/*
// ----------------------------------------------------------------------
 
 WRITE A CHEQUE  --- (Returns the cheque in string form.)
 
 ==> OT_API_WriteCheque() internally constructs an OTCheque and issues it, like so:
 
 OTCheque theCheque( SERVER_ID, ASSET_TYPE_ID );
 
 theCheque.IssueCheque( AMOUNT // The amount of the cheque, in string form, which OTAPI
                               // will convert to a long integer. Negative amounts        
                               // allowed, since that is how OT implements invoices.
                               // (An invoice is just a cheque with a negative amount.)
 
 lTransactionNumber,   // The API will supply this automatically, as long as
                       // there are some transaction numbers in the wallet. (Call
                       // OT_API_getTransactionNumber() if your wallet needs more.)
 
 VALID_FROM, VALID_TO, // Valid date range (in seconds since Jan 1970...)
 
 ACCOUNT_ID, USER_ID,  // User ID and Acct ID for SENDER.
 
 CHEQUE_MEMO,  // The memo for the cheque.
 
 RECIPIENT_USER_ID); // Recipient User ID is optional. (You can use an
                     // empty string here, to write a blank cheque.)
 */
const char * OT_API_WriteCheque(const char * SERVER_ID,
								const char * CHEQUE_AMOUNT, 
								const char * VALID_FROM, 
								const char * VALID_TO,
								const char * SENDER_ACCT_ID,
								const char * SENDER_USER_ID,
								const char * CHEQUE_MEMO, 
								const char * RECIPIENT_USER_ID)
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != CHEQUE_AMOUNT);
	OT_ASSERT(NULL != VALID_FROM);
	OT_ASSERT(NULL != VALID_TO);
	OT_ASSERT(NULL != SENDER_ACCT_ID);
	OT_ASSERT(NULL != SENDER_USER_ID);
	
	const long lAmount = atol(CHEQUE_AMOUNT);
	
	const time_t time_From = (time_t)atoi(VALID_FROM), time_To = (time_t)atoi(VALID_TO);
	
	const OTString strMemo(CHEQUE_MEMO);
	
	const OTIdentifier theServerID(SERVER_ID);
	const OTIdentifier theSenderAcctID(SENDER_ACCT_ID);
	const OTIdentifier theSenderUserID(SENDER_USER_ID);

	OTIdentifier theRecipientUserID;
	
	if ((NULL != RECIPIENT_USER_ID) &&
		(strlen(RECIPIENT_USER_ID) > 2))
		theRecipientUserID.SetString(RECIPIENT_USER_ID);
	
	OTCheque * pCheque = g_OT_API.WriteCheque(theServerID,
								 lAmount, 
								 time_From, time_To,
								 theSenderAcctID,
								 theSenderUserID,
								 strMemo, 
								 (NULL != RECIPIENT_USER_ID) ? &(theRecipientUserID) : NULL);
	
	OTCleanup<OTCheque> theChequeAngel(pCheque); // Handles cleanup. (If necessary.)
	
	if (NULL == pCheque)
	{
		OTLog::Error("OT_API::WriteCheque failed in OT_API_WriteCheque.\n");
		return NULL;
	}
	
	// At this point, I know pCheque is good (and will be cleaned up automatically.)
	
	OTString strCheque(*pCheque); // Extract the cheque to string form.
	
	const char * pBuf = strCheque.Get(); 
	
#ifdef _WIN32
	strcpy_s(g_tempBuf, MAX_STRING_LENGTH, pBuf);
#else
	strlcpy(g_tempBuf, pBuf, MAX_STRING_LENGTH);
#endif
	
	return g_tempBuf;
}


// -----------------------------------------------------------------
// LOAD PUBLIC KEY  -- from local storage
//
// (return as STRING)
//
const char * OT_API_LoadUserPubkey(const char * USER_ID) // returns NULL, or a public key.
{
	OT_ASSERT(NULL != USER_ID);

	OTString strPubkey; // For the output

	OTIdentifier	NYM_ID(USER_ID);

	// There is an OT_ASSERT in here for memory failure,
	// but it still might return NULL if various verification fails.
	OTPseudonym *	pNym = g_OT_API.LoadPublicNym(NYM_ID); 
	
	// Make sure it gets cleaned up when this goes out of scope.
	OTCleanup<OTPseudonym>	theNymAngel(pNym); // I pass the pointer, in case it's NULL.
	
	if (NULL == pNym)
	{
		OTString strNymID(NYM_ID);
		OTLog::vOutput(0, "Failure calling OT_API::LoadPublicNym in OT_API_LoadUserPubkey: %s\n", 
					  strNymID.Get());
	}
	else if (false == pNym->GetPublicKey().GetPublicKey(strPubkey))
	{
		OTString strNymID(NYM_ID);
		OTLog::vOutput(0, "Failure retrieving pubkey from Nym in OT_API_LoadUserPubkey: %s\n", 
					  strNymID.Get());
	}
	else // success 
	{
		const char * pBuf = strPubkey.Get(); 
		
#ifdef _WIN32
		strcpy_s(g_tempBuf, MAX_STRING_LENGTH, pBuf);
#else
		strlcpy(g_tempBuf, pBuf, MAX_STRING_LENGTH);
#endif
		
		return g_tempBuf;
	}

	return NULL;
}


// ------------------------------------------------------------------------
//
// Verify that USER_ID (including its Private Key) is an 
// available and verified user in local storage.
//
// Loads the user's private key, verifies, then returns OT_TRUE or OT_FALSE.
//
OT_BOOL OT_API_VerifyUserPrivateKey(const char * USER_ID) // returns OT_BOOL
{
	OT_ASSERT(NULL != USER_ID);
	
	// Get the string into usable form.
	OTIdentifier	NYM_ID(USER_ID);
	
	// There is an OT_ASSERT in here for memory failure,
	// but it still might return NULL if various verification fails.
	OTPseudonym *	pNym = g_OT_API.LoadPrivateNym(NYM_ID); 
	
	// Make sure it gets cleaned up when this goes out of scope.
	OTCleanup<OTPseudonym>	theNymAngel(pNym); // I pass the pointer, in case it's NULL.
	
	if (NULL == pNym)
	{
		OTString strNymID(NYM_ID);
		OTLog::vOutput(0, "Failure calling OT_API::LoadPrivateNym in OT_API_VerifyUserPrivateKey:\n%s\n", 
					  strNymID.Get());
	}
	else
	{
		return OT_TRUE;
	}
	
	return OT_FALSE;
}



// --------------------------------------------------------------
// LOAD PURSE / MINT / ASSET CONTRACT -- (from local storage)
//
// Based on Asset Type ID: load a purse, a public mint, or an asset contract
// and return it as a string -- or return NULL if it wasn't found.
//
const char * OT_API_LoadPurse(const char * SERVER_ID,
							  const char * ASSET_TYPE_ID) // returns NULL, or a purse.
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != ASSET_TYPE_ID);
			
	const OTIdentifier theServerID(SERVER_ID);
	const OTIdentifier theAssetID(ASSET_TYPE_ID);
	
	// There is an OT_ASSERT in here for memory failure,
	// but it still might return NULL if various verification fails.
	OTPurse * pPurse = g_OT_API.LoadPurse(theServerID, theAssetID); 
	
	// Make sure it gets cleaned up when this goes out of scope.
	OTCleanup<OTPurse>	thePurseAngel(pPurse); // I pass the pointer, in case it's NULL.
	
	if (NULL == pPurse)
	{
		OTLog::vOutput(0, "Failure calling OT_API::LoadPurse in OT_API_LoadPurse.\n "
					   "Server: %s\n Asset Type: %s\n", SERVER_ID, ASSET_TYPE_ID);
	}
	else // success 
	{
		OTString strOutput(*pPurse); // For the output
		
		const char * pBuf = strOutput.Get(); 
		
#ifdef _WIN32
		strcpy_s(g_tempBuf, MAX_STRING_LENGTH, pBuf);
#else
		strlcpy(g_tempBuf, pBuf, MAX_STRING_LENGTH);
#endif
		
		return g_tempBuf;
	}
	
	return NULL;	
}


const char * OT_API_LoadMint(const char * SERVER_ID,
							 const char * ASSET_TYPE_ID) // returns NULL, or a mint
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != ASSET_TYPE_ID);
	
	const OTIdentifier theServerID(SERVER_ID);
	const OTIdentifier theAssetID(ASSET_TYPE_ID);
	
	// There is an OT_ASSERT in here for memory failure,
	// but it still might return NULL if various verification fails.
	OTMint * pMint = g_OT_API.LoadMint(theServerID, theAssetID); 
	
	// Make sure it gets cleaned up when this goes out of scope.
	OTCleanup<OTMint>	theMintAngel(pMint); // I pass the pointer, in case it's NULL.
	
	if (NULL == pMint)
	{
		OTLog::vOutput(0, "Failure calling OT_API::LoadMint in OT_API_LoadMint.\n "
					   "Server: %s\n Asset Type: %s\n", SERVER_ID, ASSET_TYPE_ID);
	}
	else // success 
	{
		OTString strOutput(*pMint); // For the output
		
		const char * pBuf = strOutput.Get(); 
		
#ifdef _WIN32
		strcpy_s(g_tempBuf, MAX_STRING_LENGTH, pBuf);
#else
		strlcpy(g_tempBuf, pBuf, MAX_STRING_LENGTH);
#endif
		
		return g_tempBuf;
	}
	
	return NULL;		
}


const char * OT_API_LoadAssetContract(const char * ASSET_TYPE_ID) // returns NULL, or an asset contract
{
	OT_ASSERT(NULL != ASSET_TYPE_ID);
	
	const OTIdentifier theAssetID(ASSET_TYPE_ID);
	
	// There is an OT_ASSERT in here for memory failure,
	// but it still might return NULL if various verification fails.
	OTAssetContract * pContract = g_OT_API.LoadAssetContract(theAssetID); 
	
	// Make sure it gets cleaned up when this goes out of scope.
	OTCleanup<OTAssetContract>	theAngel(pContract); // I pass the pointer, in case it's NULL.
	
	if (NULL == pContract)
	{
		OTLog::vOutput(0, "Failure calling OT_API::LoadAssetContract in OT_API_LoadAssetContract.\n "
					   "Asset Type: %s\n", ASSET_TYPE_ID);
	}
	else // success 
	{
		OTString strOutput(*pContract); // For the output
		
		const char * pBuf = strOutput.Get(); 
		
#ifdef _WIN32
		strcpy_s(g_tempBuf, MAX_STRING_LENGTH, pBuf);
#else
		strlcpy(g_tempBuf, pBuf, MAX_STRING_LENGTH);
#endif
		
		return g_tempBuf;
	}
	
	return NULL;			
}


// --------------------------------------------------------------
// LOAD ACCOUNT / INBOX / OUTBOX   --  (from local storage)
//
// Loads an acct, or inbox or outbox, based on account ID, (from local storage)
// and returns it as string (or returns NULL if it couldn't load it.)
//
const char * OT_API_LoadAssetAccount(const char * SERVER_ID,
									 const char * USER_ID,
									 const char * ACCOUNT_ID) // Returns NULL, or an account.
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	OT_ASSERT(NULL != ACCOUNT_ID);
	
	const OTIdentifier theServerID(SERVER_ID);
	const OTIdentifier theUserID(USER_ID);
	const OTIdentifier theAccountID(ACCOUNT_ID);
	
	// There is an OT_ASSERT in here for memory failure,
	// but it still might return NULL if various verification fails.
	OTAccount * pAccount = g_OT_API.LoadAssetAccount(theServerID, theUserID, theAccountID); 
	
	// Make sure it gets cleaned up when this goes out of scope.
	OTCleanup<OTAccount>	theAngel(pAccount); // I pass the pointer, in case it's NULL.
	
	if (NULL == pAccount)
	{
		OTLog::vOutput(0, "Failure calling OT_API::LoadAssetAccount in OT_API_LoadAssetAccount.\n "
					   "Account ID: %s\n", ACCOUNT_ID);
	}
	else // success 
	{
		OTString strOutput(*pAccount); // For the output
		
		const char * pBuf = strOutput.Get(); 
		
#ifdef _WIN32
		strcpy_s(g_tempBuf, MAX_STRING_LENGTH, pBuf);
#else
		strlcpy(g_tempBuf, pBuf, MAX_STRING_LENGTH);
#endif
		
		return g_tempBuf;
	}
	
	return NULL;				
}

const char * OT_API_LoadInbox(const char * SERVER_ID,
							  const char * USER_ID,
							  const char * ACCOUNT_ID) // Returns NULL, or an inbox.
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	OT_ASSERT(NULL != ACCOUNT_ID);
	
	const OTIdentifier theServerID(SERVER_ID);
	const OTIdentifier theUserID(USER_ID);
	const OTIdentifier theAccountID(ACCOUNT_ID);
	
	// There is an OT_ASSERT in here for memory failure,
	// but it still might return NULL if various verification fails.
	OTLedger * pLedger = g_OT_API.LoadInbox(theServerID, theUserID, theAccountID); 
	
	// Make sure it gets cleaned up when this goes out of scope.
	OTCleanup<OTLedger>	theAngel(pLedger); // I pass the pointer, in case it's NULL.
	
	if (NULL == pLedger)
	{
		OTLog::vOutput(0, "Failure calling OT_API::LoadInbox in OT_API_LoadInbox.\n "
					   "Account ID: %s\n", ACCOUNT_ID);
	}
	else // success 
	{
		OTString strOutput(*pLedger); // For the output
		
		const char * pBuf = strOutput.Get(); 
		
#ifdef _WIN32
		strcpy_s(g_tempBuf, MAX_STRING_LENGTH, pBuf);
#else
		strlcpy(g_tempBuf, pBuf, MAX_STRING_LENGTH);
#endif
		
		return g_tempBuf;
	}
	
	return NULL;				
}

const char * OT_API_LoadOutbox(const char * SERVER_ID,
							   const char * USER_ID,
							   const char * ACCOUNT_ID)
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	OT_ASSERT(NULL != ACCOUNT_ID);
	
	const OTIdentifier theServerID(SERVER_ID);
	const OTIdentifier theUserID(USER_ID);
	const OTIdentifier theAccountID(ACCOUNT_ID);
	
	// There is an OT_ASSERT in here for memory failure,
	// but it still might return NULL if various verification fails.
	OTLedger * pLedger = g_OT_API.LoadOutbox(theServerID, theUserID, theAccountID); 
	
	// Make sure it gets cleaned up when this goes out of scope.
	OTCleanup<OTLedger>	theAngel(pLedger); // I pass the pointer, in case it's NULL.
	
	if (NULL == pLedger)
	{
		OTLog::vOutput(0, "Failure calling OT_API::LoadOutbox in OT_API_LoadOutbox.\n "
					   "Account ID: %s\n", ACCOUNT_ID);
	}
	else // success 
	{
		OTString strOutput(*pLedger); // For the output
		
		const char * pBuf = strOutput.Get(); 
		
#ifdef _WIN32
		strcpy_s(g_tempBuf, MAX_STRING_LENGTH, pBuf);
#else
		strlcpy(g_tempBuf, pBuf, MAX_STRING_LENGTH);
#endif
		
		return g_tempBuf;
	}
	
	return NULL;				
}



// --------------------------------------------------------------

/*
 SO HOW WOULD YOU **USE** THIS?  To process your inbox...
 
 -- First you call OT_API_getInbox to grab the latest inbox from the server.
 
 -- Then you call OT_API_LoadInbox to load it from local storage.
 
 (At this time, your user has the opportunity to peruse the
 inbox, and to decide which transactions therein he wishes to 
 accept or reject.)
 
 -- Then call OT_API_Ledger_CreateResponse in order to create a
 'response' ledger for that inbox, (which will be send to the server.)
 
 -- Then call OT_API_Ledger_GetCount (pass it the inbox) to find out how many 
 transactions are inside of it.  Use that count to LOOP through them...
 
 -- Use OT_API_Ledger_GetTransactionByIndex to grab each transaction as
 you iterate through the inbox.
 
 -- Call OT_API_Transaction_CreateResponse to create a response for each
 transaction, accepting or rejecting it, and adding it to the response
 ledger.
 
 -- Finally, call OT_API_processInbox to send that response ledger to the
 server and process the various items.
 */


// Returns number of transactions within, or -1 for error.
int OT_API_Ledger_GetCount(const char * SERVER_ID,
						   const char * USER_ID,
						   const char * ACCOUNT_ID,
						   const char * THE_LEDGER) 
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	OT_ASSERT(NULL != ACCOUNT_ID);
	OT_ASSERT(NULL != THE_LEDGER);
	
	const OTIdentifier theServerID(SERVER_ID), theUserID(USER_ID), theAccountID(ACCOUNT_ID);

	OTString strLedger(THE_LEDGER);
	
	// -----------------------------------------------------

	OTLedger theLedger(theUserID, theAccountID, theServerID);

	if (false == theLedger.LoadContractFromString(strLedger))
	{
		OTString strAcctID(theAccountID);
		OTLog::vError("Error loading ledger from string in OT_API_Ledger_GetCount. Acct ID:\n%s\n",
					  strAcctID.Get());
		return -1;
	}
	
	return theLedger.GetTransactionCount();
	
	return -1;
}


// -----------------------------------------------------------------------
// Creates a new 'response' ledger, set up with the right Server ID, etc, so you
// can add the 'response' items to it, one by one. (Pass in the original ledger 
// that you are responding to, as it uses the data from it to set up the response.)
//
const char * OT_API_Ledger_CreateResponse(const char * SERVER_ID,
										  const char * USER_ID,
										  const char * ACCOUNT_ID,
										  const char * ORIGINAL_LEDGER)
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	OT_ASSERT(NULL != ACCOUNT_ID);
	OT_ASSERT(NULL != ORIGINAL_LEDGER);
	
	const OTIdentifier theServerID(SERVER_ID), theUserID(USER_ID), theAccountID(ACCOUNT_ID);

	// -----------------------------------------------------

	OTWallet * pWallet = g_OT_API.GetWallet();
	
	if (NULL == pWallet)
	{
		OTLog::Output(0, "The Wallet is not loaded.\n");
		return NULL;
	}
	
	// By this point, pWallet is a good pointer.  (No need to cleanup.)
	
	// -----------------------------------------------------
	
	OTPseudonym * pNym = pWallet->GetNymByID(theUserID);
	
	if (NULL == pNym) // Wasn't already in the wallet.
	{
		OTLog::Output(0, "There's no User already loaded with that ID. Loading...\n");
		
		pNym = g_OT_API.LoadPrivateNym(theUserID);
		
		if (NULL == pNym) // LoadPrivateNym has plenty of error logging already.	
		{
			return NULL;
		}
		
		pWallet->AddNym(*pNym);
	}
	
	// By this point, pNym is a good pointer, and is on the wallet.
	//  (No need to cleanup.)
	// -----------------------------------------------------

	// Let's load up the ledger (probably in inbox) that was passed in...
	OTString strOriginalLedger(ORIGINAL_LEDGER);
	
	OTLedger theOriginalLedger(theUserID, theAccountID, theServerID);
	
	if (false == theOriginalLedger.LoadContractFromString(strOriginalLedger))
	{
		OTString strAcctID(theAccountID);
		OTLog::vError("Error loading ledger from string in OT_API_Ledger_CreateResponse. Acct ID:\n%s\n",
					  strAcctID.Get());
		return NULL;
	}
	
	if (false == theOriginalLedger.VerifyAccount(*pNym))
	{
		OTString strAcctID(theAccountID);
		OTLog::vError("Error verifying original ledger in OT_API_Ledger_CreateResponse. Acct ID:\n%s\n",
					  strAcctID.Get());
		return NULL;
	}
	
	// -----------------------------------------------------

	// By this point, the ledger is loaded properly from the string,
	// Let's create the response to it.
	OTLedger * pResponseLedger = OTLedger::GenerateLedger(theUserID, theAccountID,
														  theServerID, OTLedger::message);// bCreateFile=false
	OTCleanup<OTLedger> theResponseAngel(pResponseLedger); // Angel will handle cleanup.
		
	if (NULL == pResponseLedger)
	{
		OTString strAcctID(theAccountID);
		OTLog::vError("Error generating response ledger in OT_API_Ledger_CreateResponse. Acct ID:\n%s\n",
					  strAcctID.Get());
		return NULL;
	}
	
	// -----------------------------------------------------

	pResponseLedger->SignContract(*pNym);
	pResponseLedger->SaveContract();

	OTString strOutput(*pResponseLedger); // For the output
	
	const char * pBuf = strOutput.Get(); 
	
#ifdef _WIN32
	strcpy_s(g_tempBuf, MAX_STRING_LENGTH, pBuf);
#else
	strlcpy(g_tempBuf, pBuf, MAX_STRING_LENGTH);
#endif
	
	return g_tempBuf;	
}



// -------------------------------------------------------------------------
// Lookup a transaction or its ID (from within a ledger) based on index or
// transaction number.
//
// The transaction number is returned as a string, because I return ALL long
// ints as a string (in the API.)  In C, you can just call atol to convert it back.
// This makes it easier for the guys who use scripting languages. (This file is 
// primarily for them. If you are lower-level, you should use OpenTransactions.h/.cpp
// and then use this one as a model for how to do it. Or use this one if you insist
// on straight C, since all these functions are extern "C".)
//
const char * OT_API_Ledger_GetTransactionByIndex(const char * SERVER_ID,
												 const char * USER_ID,
												 const char * ACCOUNT_ID,
												 const char * THE_LEDGER,
												 int nIndex) // returns transaction by index (from ledger)
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	OT_ASSERT(NULL != ACCOUNT_ID);
	OT_ASSERT(NULL != THE_LEDGER);
	OT_ASSERT(nIndex >= 0);
	
	const OTIdentifier theServerID(SERVER_ID), theUserID(USER_ID), theAccountID(ACCOUNT_ID);
	
	OTString strLedger(THE_LEDGER);
	
	// -----------------------------------------------------
	
	OTLedger theLedger(theUserID, theAccountID, theServerID);

	if (false == theLedger.LoadContractFromString(strLedger))
	{
		OTString strAcctID(theAccountID);
		OTLog::vError("Error loading ledger from string in OT_API_Ledger_GetTransactionByIndex. Acct ID:\n%s\n",
					  strAcctID.Get());
		return NULL;
	}
	
	// At this point, I know theLedger loaded successfully.
	
	if (nIndex >= theLedger.GetTransactionCount())
	{
		OTLog::vError("OT_API_Ledger_GetTransactionByIndex out of bounds: %d\n", nIndex);
		return NULL; // out of bounds. I'm saving from an OT_ASSERT() happening here. (Maybe I shouldn't.)
	}
	
	OTTransaction * pTransaction = theLedger.GetTransactionByIndex(nIndex);
//	OTCleanup<OTTransaction> theAngel(pTransaction); // THE LEDGER CLEANS THIS ALREADY.
	
	if (NULL == pTransaction)
	{
		OTLog::vError("OT_API_Ledger_GetTransactionByIndex good index but uncovered NULL pointer: %d\n", 
					  nIndex);
		return NULL; // Weird.
	}
	
	// At this point, I actually have the transaction pointer, so let's return it in string form...
	
	OTString strOutput(*pTransaction); // For the output
	
	const char * pBuf = strOutput.Get(); 
	
#ifdef _WIN32
	strcpy_s(g_tempBuf, MAX_STRING_LENGTH, pBuf);
#else
	strlcpy(g_tempBuf, pBuf, MAX_STRING_LENGTH);
#endif
	
	return g_tempBuf;	
}


// Returns transaction by ID (transaction numbers are long ints, and thus
// they are passed as strings in this OT high-level API.)
const char * OT_API_Ledger_GetTransactionByID(const char * SERVER_ID,
											  const char * USER_ID,
											  const char * ACCOUNT_ID,
											  const char * THE_LEDGER,
											  const char * TRANSACTION_NUMBER) 
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	OT_ASSERT(NULL != ACCOUNT_ID);
	OT_ASSERT(NULL != THE_LEDGER);
	OT_ASSERT(NULL != TRANSACTION_NUMBER);
	
	long lTransactionNumber = atol(TRANSACTION_NUMBER);
	OT_ASSERT(lTransactionNumber >= 0);
	
	const OTIdentifier theServerID(SERVER_ID), theUserID(USER_ID), theAccountID(ACCOUNT_ID);
	
	OTString strLedger(THE_LEDGER);
	
	// -----------------------------------------------------
	
	OTLedger theLedger(theUserID, theAccountID, theServerID);
		
	if (false == theLedger.LoadContractFromString(strLedger))
	{
		OTString strAcctID(theAccountID);
		OTLog::vError("Error loading ledger from string in OT_API_Ledger_GetTransactionByID. Acct ID:\n%s\n",
					  strAcctID.Get());
		return NULL;
	}
	
	// At this point, I know theLedger loaded successfully.
		
	OTTransaction * pTransaction = theLedger.GetTransaction(lTransactionNumber);
	// No need to cleanup this transaction, the ledger owns it already.
	
	if (NULL == pTransaction)
	{
		OTLog::vOutput(0, "OT_API_Ledger_GetTransactionByID: No transactions found "
					   "in ledger with that number: %ld.\n", lTransactionNumber);
		return NULL; // Maybe he was just looking; this isn't necessarily an error.
	}
	
	// At this point, I actually have the transaction pointer, so let's return it in string form...
	
	OTString strOutput(*pTransaction); // For the output
	
	const char * pBuf = strOutput.Get(); 
	
#ifdef _WIN32
	strcpy_s(g_tempBuf, MAX_STRING_LENGTH, pBuf);
#else
	strlcpy(g_tempBuf, pBuf, MAX_STRING_LENGTH);
#endif
	
	return g_tempBuf;	
}



// Returns a transaction number, or -1 for error.
const char * OT_API_Ledger_GetTransactionIDByIndex(const char * SERVER_ID,
												   const char * USER_ID,
												   const char * ACCOUNT_ID,
												   const char * THE_LEDGER,
												   int nIndex) // returns transaction number by index.
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	OT_ASSERT(NULL != ACCOUNT_ID);
	OT_ASSERT(NULL != THE_LEDGER);
	OT_ASSERT(nIndex >= 0);
	
	const OTIdentifier theServerID(SERVER_ID), theUserID(USER_ID), theAccountID(ACCOUNT_ID);
	
	OTString strLedger(THE_LEDGER);
	
	// -----------------------------------------------------
	
	OTString strOutput("-1"); // For the output

	long lTransactionNumber = 0;
	OTTransaction * pTransaction = NULL;
	
	OTLedger theLedger(theUserID, theAccountID, theServerID);
	
	if (false == theLedger.LoadContractFromString(strLedger))
	{
		OTString strAcctID(theAccountID);
		OTLog::vError("Error loading ledger from string in OT_API_Ledger_GetTransactionIDByIndex. Acct ID:\n%s\n",
					  strAcctID.Get());
	}
	
	// At this point, I know theLedger loaded successfully.
	
	else if (nIndex >= theLedger.GetTransactionCount())
	{
		OTLog::vError("OT_API_Ledger_GetTransactionIDByIndex out of bounds: %d\n", nIndex);
		// out of bounds. I'm saving from an OT_ASSERT() happening here. (Maybe I shouldn't.)
	}
	
	else if (NULL == (pTransaction = theLedger.GetTransactionByIndex(nIndex)))
	{
		OTLog::vError("OT_API_Ledger_GetTransactionIDByIndex good index but uncovered NULL pointer: %d\n", 
					  nIndex);
	} // NO NEED TO CLEANUP the transaction, since it is already "owned" by theLedger.
	
	// At this point, I actually have the transaction pointer, so let's get the ID...
	
	else if (0 > (lTransactionNumber = pTransaction->GetTransactionNum()))
	{
		OTLog::vError("OT_API_Ledger_GetTransactionIDByIndex negative transaction num: %ld\n", 
					  lTransactionNumber);
		// Bad value.
	}
	else // success
	{
		strOutput.Format("%ld", lTransactionNumber);
	}
	
	const char * pBuf = strOutput.Get(); 
	
#ifdef _WIN32
	strcpy_s(g_tempBuf, MAX_STRING_LENGTH, pBuf);
#else
	strlcpy(g_tempBuf, pBuf, MAX_STRING_LENGTH);
#endif
	
	return g_tempBuf;	
}


// --------------------------------------------------------------
// Add a transaction to a ledger.
// (Returns the updated ledger.)
//
const char * OT_API_Ledger_AddTransaction(const char * SERVER_ID,
										  const char * USER_ID,
										  const char * ACCOUNT_ID,
										  const char * THE_LEDGER,
										  const char * THE_TRANSACTION)
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	OT_ASSERT(NULL != ACCOUNT_ID);
	OT_ASSERT(NULL != THE_LEDGER);
	OT_ASSERT(NULL != THE_TRANSACTION);
	
	const OTIdentifier theServerID(SERVER_ID), theUserID(USER_ID), theAccountID(ACCOUNT_ID);
	
	OTString strLedger(THE_LEDGER);
	OTString strTransaction(THE_TRANSACTION);
	
	// -----------------------------------------------------
	
	OTWallet * pWallet = g_OT_API.GetWallet();
	
	if (NULL == pWallet)
	{
		OTLog::Output(0, "The Wallet is not loaded.\n");
		return NULL;
	}
	
	// By this point, pWallet is a good pointer.  (No need to cleanup.)
	
	// -----------------------------------------------------
	
	OTPseudonym * pNym = pWallet->GetNymByID(theUserID);
	
	if (NULL == pNym) // Wasn't already in the wallet.
	{
		OTLog::Output(0, "There's no User already loaded with that ID. Loading...\n");
		
		pNym = g_OT_API.LoadPrivateNym(theUserID);
		
		if (NULL == pNym) // LoadPrivateNym has plenty of error logging already.	
		{
			return NULL;
		}
		
		pWallet->AddNym(*pNym);
	}
	
	// By this point, pNym is a good pointer, and is on the wallet.
	//  (No need to cleanup.)
	// -----------------------------------------------------
	
	OTLedger theLedger(theUserID, theAccountID, theServerID);
	
	if (false == theLedger.LoadContractFromString(strLedger))
	{
		OTString strAcctID(theAccountID);
		OTLog::vError("Error loading ledger from string in OT_API_Ledger_AddTransaction. Acct ID:\n%s\n",
					  strAcctID.Get());
		return NULL;
	}
	else if (false == theLedger.VerifyAccount(*pNym))
	{
		OTString strAcctID(theAccountID);
		OTLog::vError("Error verifying ledger in OT_API_Ledger_AddTransaction. Acct ID:\n%s\n",
					  strAcctID.Get());
		return NULL;
	}
	
	// At this point, I know theLedger loaded and verified successfully.
	// -----------------------------------------------------
	
	OTTransaction * pTransaction = new OTTransaction(theUserID, theAccountID, theServerID);
		
	OT_ASSERT(NULL != pTransaction);
	
	if (false == pTransaction->LoadContractFromString(strTransaction))
	{
		OTString strAcctID(theAccountID);
		OTLog::vError("Error loading transaction from string in OT_API_Ledger_AddTransaction. Acct ID:\n%s\n",
					  strAcctID.Get());
		delete pTransaction; pTransaction = NULL;
		return NULL;
	}
	else if (false == pTransaction->VerifyAccount(*pNym))
	{
		OTString strAcctID(theAccountID);
		OTLog::vError("Error verifying transaction in OT_API_Ledger_AddTransaction. Acct ID:\n%s\n",
					  strAcctID.Get());
		delete pTransaction; pTransaction = NULL;
		return NULL;
	}

	// -----------------------------------------------------
		
	// At this point, I know pTransaction loaded and verified successfully.
	// So let's add it to the ledger, save, and return updated ledger in string form.
	
	theLedger.AddTransaction(*pTransaction); // Ledger now "owns" it and will handle cleanup.
	
	theLedger.ReleaseSignatures();
	theLedger.SignContract(*pNym);
	theLedger.SaveContract();
	
	OTString strOutput(theLedger); // For the output
	
	const char * pBuf = strOutput.Get(); 
	
#ifdef _WIN32
	strcpy_s(g_tempBuf, MAX_STRING_LENGTH, pBuf);
#else
	strlcpy(g_tempBuf, pBuf, MAX_STRING_LENGTH);
#endif
	
	return g_tempBuf;	
}



// --------------------------------------------------------------
// Create a 'response' transaction, that will be used to indicate my
// acceptance or rejection of another transaction. Usually an entire
// ledger full of these is sent to the server as I process the various
// transactions in my inbox.
//
// The original transaction is passed in, and I generate a response transaction based on it.
// Also, the response ledger is passed in, so I load it, add the response transaction, save
// it back to string, and return the string.
//
// This way, users can call this function multiple times, adding transactions until done.
//
const char * OT_API_Transaction_CreateResponse(const char * SERVER_ID,
											   const char * USER_ID,
											   const char * ACCOUNT_ID,
											   const char * THE_LEDGER, // 'Response' ledger be sent to the server...
											   const char * THE_TRANSACTION, // Responding to...?
											   OT_BOOL BOOL_DO_I_ACCEPT)   // 0 or 1  (OT_TRUE or OT_FALSE.)
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	OT_ASSERT(NULL != ACCOUNT_ID);
	OT_ASSERT(NULL != THE_LEDGER);
	OT_ASSERT(NULL != THE_TRANSACTION);
	
	const OTIdentifier theServerID(SERVER_ID), theUserID(USER_ID), theAccountID(ACCOUNT_ID);
	
	OTString strLedger(THE_LEDGER);
	OTString strTransaction(THE_TRANSACTION);
		
	// -----------------------------------------------------
	
	OTWallet * pWallet = g_OT_API.GetWallet();
	
	if (NULL == pWallet)
	{
		OTLog::Output(0, "The Wallet is not loaded.\n");
		return NULL;
	}
	
	// By this point, pWallet is a good pointer.  (No need to cleanup.)
	
	// -----------------------------------------------------------------
	
	OTServerContract * pServer = pWallet->GetServerContract(SERVER_ID);
	
	if (NULL == pServer)
	{
		OTLog::Output(0, "No Server Contract found with that Server ID.\n");
		return NULL;
	}
	
	// By this point, pServer is a good pointer.  (No need to cleanup.)

	const OTPseudonym * pServerNym = pServer->GetContractPublicNym();

	if (NULL == pServerNym)
	{
		OTLog::Output(0, "No Contract Nym found in that Server Contract.\n");
		return NULL;
	}
	
	// By this point, pServerNym is a good pointer.  (No need to cleanup.)
	
	// -----------------------------------------------------
	
	OTPseudonym * pNym = pWallet->GetNymByID(theUserID);
	
	if (NULL == pNym) // Wasn't already in the wallet.
	{
		OTLog::Output(0, "There's no User already loaded with that ID. Loading...\n");
		
		pNym = g_OT_API.LoadPrivateNym(theUserID);
		
		if (NULL == pNym) // LoadPrivateNym has plenty of error logging already.	
		{
			return NULL;
		}
		
		pWallet->AddNym(*pNym);
	}
	
	// By this point, pNym is a good pointer, and is on the wallet.
	//  (No need to cleanup.)
	// -----------------------------------------------------
	
	OTLedger theLedger(theUserID, theAccountID, theServerID);
	
	if (false == theLedger.LoadContractFromString(strLedger))
	{
		OTString strAcctID(theAccountID);
		OTLog::vError("Error loading ledger from string in OT_API_Transaction_CreateResponse. Acct ID:\n%s\n",
					  strAcctID.Get());
		return NULL;
	}
	else if (false == theLedger.VerifyAccount(*pNym))
	{
		OTString strAcctID(theAccountID);
		OTLog::vError("Error verifying ledger in OT_API_Transaction_CreateResponse. Acct ID:\n%s\n",
					  strAcctID.Get());
		return NULL;
	}
	
	// At this point, I know theLedger loaded and verified successfully.
	// (This is the 'response' ledger that the user previously generated,
	// and now he is loading it up with responses that this function will 
	// generate on his behalf.)
	// -----------------------------------------------------
	
	OTTransaction theTransaction(theUserID, theAccountID, theServerID);
		
	if (false == theTransaction.LoadContractFromString(strTransaction))
	{
		OTString strAcctID(theAccountID);
		OTLog::vError("Error loading transaction from string in OT_API_Transaction_CreateResponse. Acct ID:\n%s\n",
					  strAcctID.Get());
		return NULL;
	}
	// This transaction is presumably from the server, since we are in this
	// function in order to generate a response back to the server. So therefore
	// I want to verify that the server has actually signed the thing, before
	// I go off responding to it like a damned fool.
	//
	else if (false == theTransaction.VerifyAccount(*((OTPseudonym *)pServerNym)))
	{
		OTString strAcctID(theAccountID);
		OTLog::vError("Error verifying transaction in OT_API_Transaction_CreateResponse. Acct ID:\n%s\n",
					  strAcctID.Get());
		return NULL;
	}
	
	// -----------------------------------------------------
	
	// At this point, I know theTransaction loaded and verified successfully.
	// So let's generate a response item based on it, and add it to a processInbox
	// transaction to be added to that ledger (if one's not already there...)
	
	// First, check to see if there is a processInbox transaction already on
	// the ledger...
	OTTransaction * pTransaction = theLedger.GetTransaction(OTTransaction::processInbox);

	// If it's not already there, create it and add it.
	if (NULL == pTransaction)
	{
		OTString strServerID(theServerID);
		long lTransactionNumber=0;
		bool bGotTransNum = pNym->GetNextTransactionNum(*pNym, strServerID, lTransactionNumber);

		if (false == bGotTransNum)
		{
			OTString strNymID(theUserID);
			OTLog::vOutput(0, "User is all out of transaction numbers in OT_API_Transaction_CreateResponse:\n%s\n",
						  strNymID.Get());
			return NULL;
		}
		
		pTransaction = OTTransaction::GenerateTransaction(theUserID, theAccountID, theServerID, 
														  OTTransaction::processInbox, lTransactionNumber);
		if (NULL == pTransaction)
		{
			OTString strAcctID(theAccountID);
			OTLog::vError("Error generating processInbox transaction in \n"
						 "OT_API_Transaction_CreateResponse for AcctID:\n%s\n", strAcctID.Get());
			return NULL;
		}
		
		theLedger.AddTransaction(*pTransaction); // Ledger now "owns" it and will handle cleanup.
	}
	
	// At this point I know pTransaction is a processInbox transaction, ready to go,
	// and that theLedger will handle any cleanup issues related to it.
	
	// Next let's create a new item that response to theTransaction, and add that 
	// item to pTransaction. Then we'll return the updated ledger.
	
	OTItem * pAcceptItem = OTItem::CreateItemFromTransaction(theTransaction, 
															 (OT_TRUE == BOOL_DO_I_ACCEPT) ?
															 OTItem::accept : OTItem::reject);
	
	// Set up the "accept" transaction item to be sent to the server 
	// (this item references and accepts another item by its transaction number--
	//  one that is already there in my inbox)
	pAcceptItem->SetReferenceToNum(theTransaction.GetTransactionNum()); // This is critical. Server needs this to look up the original.
	// Don't need to set transaction num on item since the constructor already got it off the owner transaction.

	// the transaction will handle cleaning up the transaction item.
	pTransaction->AddItem(*pAcceptItem);
		
	// I don't attach the original item here because I already reference it by transaction num,
	// and because the server already has it and sent it to me. SO I just need to give the server
	// enough info to look it up again.
	
	// sign the item
	pAcceptItem->SignContract(*pNym);
	pAcceptItem->SaveContract();
	
	pTransaction->ReleaseSignatures();
	pTransaction->SignContract(*pNym);
	pTransaction->SaveContract();
	
	theLedger.ReleaseSignatures();
	theLedger.SignContract(*pNym);
	theLedger.SaveContract();
	
	OTString strOutput(theLedger); // For the output
	
	const char * pBuf = strOutput.Get(); 
	
#ifdef _WIN32
	strcpy_s(g_tempBuf, MAX_STRING_LENGTH, pBuf);
#else
	strlcpy(g_tempBuf, pBuf, MAX_STRING_LENGTH);
#endif
	
	return g_tempBuf;	
}


// --------------------------------------------------

// Get Transaction Type  (internally uses GetTransactionTypeString().)
const char * OT_API_Transaction_GetType(const char * SERVER_ID,
										const char * USER_ID,
										const char * ACCOUNT_ID,
										const char * THE_TRANSACTION)
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	OT_ASSERT(NULL != ACCOUNT_ID);
	OT_ASSERT(NULL != THE_TRANSACTION);
	
	const OTIdentifier theServerID(SERVER_ID), theUserID(USER_ID), theAccountID(ACCOUNT_ID);
	
	OTString strTransaction(THE_TRANSACTION);
	
	// -----------------------------------------------------
	
	OTWallet * pWallet = g_OT_API.GetWallet();
	
	if (NULL == pWallet)
	{
		OTLog::Output(0, "The Wallet is not loaded.\n");
		return NULL;
	}
	
	// By this point, pWallet is a good pointer.  (No need to cleanup.)
	
	// -----------------------------------------------------------------
		
	OTPseudonym * pNym = pWallet->GetNymByID(theUserID);
	
	if (NULL == pNym) // Wasn't already in the wallet.
	{
		OTLog::Output(0, "There's no User already loaded with that ID. Loading...\n");
		
		pNym = g_OT_API.LoadPrivateNym(theUserID);
		
		if (NULL == pNym) // LoadPrivateNym has plenty of error logging already.	
		{
			return NULL;
		}
		
		pWallet->AddNym(*pNym);
	}
	
	// By this point, pNym is a good pointer, and is on the wallet.
	//  (No need to cleanup.)
	// -----------------------------------------------------
	
	OTTransaction theTransaction(theUserID, theAccountID, theServerID);
	
	if (false == theTransaction.LoadContractFromString(strTransaction))
	{
		OTString strAcctID(theAccountID);
		OTLog::vError("Error loading transaction from string in OT_API_Transaction_GetType. Acct ID:\n%s\n",
					  strAcctID.Get());
		return NULL;
	}

	// -----------------------------------------------------

	
	const char * pBuf = theTransaction.GetTypeString(); 
	
#ifdef _WIN32
	strcpy_s(g_tempBuf, MAX_STRING_LENGTH, pBuf);
#else
	strlcpy(g_tempBuf, pBuf, MAX_STRING_LENGTH);
#endif
	
	return g_tempBuf;		
}





// --------------------------------------------------



// MESSAGES BEING SENT TO THE SERVER:




void OT_API_checkServerID(const char * SERVER_ID,
						  const char * USER_ID)
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	
	OTIdentifier theServerID(SERVER_ID), theUserID(USER_ID);

	g_OT_API.checkServerID(theServerID, theUserID);
}

	
void OT_API_createUserAccount(const char * SERVER_ID,
							  const char * USER_ID)
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	
	OTIdentifier theServerID(SERVER_ID), theUserID(USER_ID);

	g_OT_API.createUserAccount(theServerID, theUserID);
}

	
void OT_API_checkUser(const char * SERVER_ID,
					  const char * USER_ID,
					  const char * USER_ID_CHECK)
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	OT_ASSERT(NULL != USER_ID_CHECK);
	
	OTIdentifier theServerID(SERVER_ID), theUserID(USER_ID), theOtherUserID(USER_ID_CHECK);
	
	g_OT_API.checkUser(theServerID, theUserID, theOtherUserID);
}

	
void OT_API_getRequest(const char * SERVER_ID,
					   const char * USER_ID)
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	
	OTIdentifier theServerID(SERVER_ID), theUserID(USER_ID);

	g_OT_API.getRequest(theServerID, theUserID);
}

	
	
void OT_API_issueAssetType(const char *	SERVER_ID,
						   const char *	USER_ID,
						   const char *	THE_CONTRACT)
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	OT_ASSERT(NULL != THE_CONTRACT);
	
	OTIdentifier theServerID(SERVER_ID), theUserID(USER_ID);
	
	OTString strContract(THE_CONTRACT);

	g_OT_API.issueAssetType(theServerID, theUserID, strContract);
}

	
void OT_API_getContract(const char * SERVER_ID,
						const char * USER_ID,
						const char * ASSET_ID)
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	OT_ASSERT(NULL != ASSET_ID);

	OTIdentifier theServerID(SERVER_ID), theUserID(USER_ID), theAssetID(ASSET_ID);
	
	g_OT_API.getContract(theServerID, theUserID, theAssetID);
}

	
void OT_API_getMint(const char * SERVER_ID,
					const char * USER_ID,
					const char * ASSET_ID)
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	OT_ASSERT(NULL != ASSET_ID);

	OTIdentifier theServerID(SERVER_ID), theUserID(USER_ID), theAssetID(ASSET_ID);

	g_OT_API.getMint(theServerID, theUserID, theAssetID);
}

	
void OT_API_createAssetAccount(const char * SERVER_ID,
							   const char * USER_ID,
							   const char * ASSET_ID)
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	OT_ASSERT(NULL != ASSET_ID);

	OTIdentifier theServerID(SERVER_ID), theUserID(USER_ID), theAssetID(ASSET_ID);
	
	g_OT_API.createAssetAccount(theServerID, theUserID, theAssetID);
}

	

// Sends a message to the server to retrieve latest copy of an asset acct.
void OT_API_getAccount(const char * SERVER_ID,
					   const char * USER_ID,
					   const char * ACCT_ID)
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	OT_ASSERT(NULL != ACCT_ID);
	
	OTIdentifier theServerID(SERVER_ID), theUserID(USER_ID), theAcctID(ACCT_ID);

	g_OT_API.getAccount(theServerID, theUserID, theAcctID);
}

	
void OT_API_issueBasket(const char * SERVER_ID,
						const char * USER_ID,
						const char * BASKET_INFO)
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	OT_ASSERT(NULL != BASKET_INFO);
	
	OTIdentifier theServerID(SERVER_ID), theUserID(USER_ID);
	
	OTString strBasketInfo(BASKET_INFO);

	g_OT_API.issueBasket(theServerID, theUserID, strBasketInfo);
}

	
void OT_API_exchangeBasket(const char * SERVER_ID,
						   const char * USER_ID,
						   const char * BASKET_ASSET_ID,
						   const char * BASKET_INFO)
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	OT_ASSERT(NULL != BASKET_ASSET_ID);
	OT_ASSERT(NULL != BASKET_INFO);

	OTIdentifier theServerID(SERVER_ID), theUserID(USER_ID), theBasketAssetID(BASKET_ASSET_ID);

	OTString strBasketInfo(BASKET_INFO);

	g_OT_API.exchangeBasket(theServerID, theUserID, theBasketAssetID, strBasketInfo);
}

	
void OT_API_getTransactionNumber(const char * SERVER_ID,
								 const char * USER_ID)
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	
	OTIdentifier theServerID(SERVER_ID), theUserID(USER_ID);

	
	g_OT_API.getTransactionNumber(theServerID, theUserID);
}

	
void OT_API_notarizeWithdrawal(const char * SERVER_ID,
							   const char * USER_ID,
							   const char * ACCT_ID,
							   const char * AMOUNT)
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	OT_ASSERT(NULL != ACCT_ID);
	OT_ASSERT(NULL != AMOUNT);

	OTIdentifier theServerID(SERVER_ID), theUserID(USER_ID), theAcctID(ACCT_ID);

	OTString strAmount(AMOUNT);
	
	g_OT_API.notarizeWithdrawal(theServerID, theUserID, theAcctID, strAmount);
}

	
void OT_API_notarizeDeposit(const char * SERVER_ID,
							const char * USER_ID,
							const char * ACCT_ID,
							const char * THE_PURSE)
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	OT_ASSERT(NULL != ACCT_ID);
	OT_ASSERT(NULL != THE_PURSE);

	OTIdentifier theServerID(SERVER_ID), theUserID(USER_ID), theAcctID(ACCT_ID);
	OTString strPurse(THE_PURSE);

	g_OT_API.notarizeDeposit(theServerID, theUserID, theAcctID, strPurse);
}

	
void OT_API_notarizeTransfer(const char * SERVER_ID,
							 const char * USER_ID,
							 const char * ACCT_FROM,
							 const char * ACCT_TO,
							 const char * AMOUNT,
							 const char * NOTE)
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	OT_ASSERT(NULL != ACCT_FROM);
	OT_ASSERT(NULL != ACCT_TO);
	OT_ASSERT(NULL != AMOUNT);
	OT_ASSERT(NULL != NOTE);
	
	OTIdentifier theServerID(SERVER_ID), theUserID(USER_ID);
	OTIdentifier theFromAcct(ACCT_FROM), theToAcct(ACCT_TO);

	OTString strAmount(AMOUNT), strNote(NOTE);

	g_OT_API.notarizeTransfer(theServerID, theUserID, theFromAcct, theToAcct, strAmount, strNote);
}

	
void OT_API_getInbox(const char * SERVER_ID,
					 const char * USER_ID,
					 const char * ACCT_ID)
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	OT_ASSERT(NULL != ACCT_ID);
	
	OTIdentifier theServerID(SERVER_ID), theUserID(USER_ID), theAcctID(ACCT_ID);

	g_OT_API.getInbox(theServerID, theUserID, theAcctID);
}

	
void OT_API_processInbox(const char * SERVER_ID,
						 const char * USER_ID,
						 const char * ACCT_ID,
						 const char * ACCT_LEDGER)
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	OT_ASSERT(NULL != ACCT_ID);
	OT_ASSERT(NULL != ACCT_LEDGER);

	OTIdentifier theServerID(SERVER_ID), theUserID(USER_ID), theAcctID(ACCT_ID);
	OTString strLedger(ACCT_LEDGER);

	g_OT_API.processInbox(theServerID, theUserID, theAcctID, strLedger);
}

	
void OT_API_withdrawVoucher(const char * SERVER_ID,
							const char * USER_ID,
							const char * ACCT_ID,
							const char * RECIPIENT_USER_ID,
							const char * CHEQUE_MEMO,
							const char * AMOUNT)
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	OT_ASSERT(NULL != ACCT_ID);
	OT_ASSERT(NULL != RECIPIENT_USER_ID);
	OT_ASSERT(NULL != CHEQUE_MEMO);
	OT_ASSERT(NULL != AMOUNT);
	
	OTIdentifier	theServerID(SERVER_ID),	theUserID(USER_ID), 
						theAcctID(ACCT_ID),		theRecipientUserID(RECIPIENT_USER_ID);

	OTString strMemo(CHEQUE_MEMO), strAmount(AMOUNT);

	g_OT_API.withdrawVoucher(theServerID, theUserID, theAcctID, theRecipientUserID, strMemo, strAmount);
}



void OT_API_depositCheque(const char * SERVER_ID,
						  const char * USER_ID,
						  const char * ACCT_ID,
						  const char * THE_CHEQUE)
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	OT_ASSERT(NULL != ACCT_ID);
	OT_ASSERT(NULL != THE_CHEQUE);
	
	OTIdentifier theServerID(SERVER_ID), theUserID(USER_ID), theAcctID(ACCT_ID);
	OTString strCheque(THE_CHEQUE);
	
	g_OT_API.depositCheque(theServerID, theUserID, theAcctID, strCheque);
}

	





// NOT necessary in XmlRpc->HTTP mode (the preferred way.)
// Only TCP/SSL mode maintains a connection to the server, and was for testing.
OT_BOOL OT_API_ConnectServer(const char * SERVER_ID,
							 const char * USER_ID,
							 const char * szCA_FILE, 
							 const char * szKEY_FILE, 
							 const char * szKEY_PASSWORD)
{
	OT_ASSERT(NULL != SERVER_ID);
	OT_ASSERT(NULL != USER_ID);
	OT_ASSERT(NULL != szCA_FILE);
	OT_ASSERT(NULL != szKEY_FILE);
	OT_ASSERT(NULL != szKEY_PASSWORD);
	
	OTIdentifier theServerID(SERVER_ID), theUserID(USER_ID);
	
	OTString strCA(szCA_FILE), strKeyFile(szKEY_FILE), strKeyPassword(szKEY_PASSWORD);
	
	bool bConnected = g_OT_API.ConnectServer(theServerID, theUserID, strCA, strKeyFile, strKeyPassword);
	
	if (bConnected)
		return OT_TRUE;
	
	return OT_FALSE;
}


// Not necessary in HTTP mode. 
// (Request/Response; no need to check sockets periodically in that mode.)
// If you use TCP/SSL mode, you have to call this in order to check for
// server replies and process them.
OT_BOOL OT_API_ProcessSockets(void) 
{
	bool bProcess = g_OT_API.ProcessSockets();
	
	if (bProcess)
		return OT_TRUE;
	
	return OT_FALSE;
}


















