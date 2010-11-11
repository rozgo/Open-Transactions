/************************************************************************************
 *    
 *  OTAPI.cpp   -- Implementation for the C interface. (Written in C++)
 *	             
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


#include "OTIdentifier.h"
#include "OTString.h"

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

	
OT_BOOL OT_API_loadWallet(const char * szPath)
{
	OT_ASSERT(NULL != szPath);

	OTString strPath(szPath);
	
	bool bLoaded = g_OT_API.loadWallet(strPath);
	
	if (bLoaded)
		return OT_TRUE;
	
	return OT_FALSE;
}


// NOT necessary in XmlRpc->HTTP mode (the preferred way.)
// Only TCP/SSL mode maintains a connection to the server, and was for testing.
OT_BOOL OT_API_connectServer(const char * SERVER_ID,
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

	bool bConnected = g_OT_API.connectServer(theServerID, theUserID, strCA, strKeyFile, strKeyPassword);
	
	if (bConnected)
		return OT_TRUE;
	
	return OT_FALSE;
}

	
// Not necessary in HTTP mode. 
// (Request/Response; no need to check sockets periodically in that mode.)
// If you use TCP/SSL mode, you have to call this in order to check for
// server replies and process them.
OT_BOOL OT_API_processSockets(void) 
{
	bool bProcess = g_OT_API.processSockets();
	
	if (bProcess)
		return OT_TRUE;
	
	return OT_FALSE;
}



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

	

// Queries the wallet for an asset account.
OT_BOOL OT_API_GetAccountWallet(int iIndex, const char * THE_ID, const char * THE_NAME)
{
	OT_ASSERT(NULL != THE_ID);
	OT_ASSERT(NULL != THE_NAME);
	OT_ASSERT(iIndex > 0);
	
	OTIdentifier	theID(THE_ID);
	OTString		strName(THE_NAME);
	
	bool bGetAccount = g_OT_API.getAccount(iIndex, theID, strName);
	
	if (bGetAccount)
		return OT_TRUE;
	
	return OT_FALSE;
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

	
	
	// --------------------------------------------------
	
int OT_API_getNymCount(void)
{
	return g_OT_API.getNymCount();
}

int OT_API_getServerCount(void)
{
	return g_OT_API.getServerCount();
}

int OT_API_getAssetTypeCount(void)
{
	return g_OT_API.getAssetTypeCount();
}

int OT_API_getAccountCount(void)
{
	return g_OT_API.getAccountCount();
}

	
OT_BOOL OT_API_getNym(int iIndex, const char * NYM_ID, const char * NYM_NAME)
{
	OT_ASSERT(NULL != NYM_ID);
	OT_ASSERT(NULL != NYM_NAME);
	OT_ASSERT(iIndex > 0);
	
	OTIdentifier	theNymID(NYM_ID);
	OTString		strName(NYM_NAME);

	bool bGetNym = g_OT_API.getNym(iIndex, theNymID, strName);
	
	if (bGetNym)
		return OT_TRUE;
	
	return OT_FALSE;
}

OT_BOOL OT_API_getServer(int iIndex, const char * THE_ID, const char * THE_NAME)
{
	OT_ASSERT(NULL != THE_ID);
	OT_ASSERT(NULL != THE_NAME);
	OT_ASSERT(iIndex > 0);

	OTIdentifier	theID(THE_ID);
	OTString		strName(THE_NAME);
	
	bool bGetServer = g_OT_API.getServer(iIndex, theID, strName);
	
	if (bGetServer)
		return OT_TRUE;
	
	return OT_FALSE;
}

OT_BOOL OT_API_getAssetType(int iIndex, const char * THE_ID, const char * THE_NAME)
{
	OT_ASSERT(NULL != THE_ID);
	OT_ASSERT(NULL != THE_NAME);
	OT_ASSERT(iIndex > 0);

	OTIdentifier	theID(THE_ID);
	OTString		strName(THE_NAME);

	bool bGetAssetType = g_OT_API.getAssetType(iIndex, theID, strName);
	
	if (bGetAssetType)
		return OT_TRUE;
	
	return OT_FALSE;
}

		





















