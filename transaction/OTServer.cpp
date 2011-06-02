/************************************************************************************
 *    
 *  OTServer.cpp
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


#include <cstdio>
#include <cstring>
#include <ctime>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "irrxml/irrXML.h"

using namespace irr;
using namespace io;
using namespace std;


#include "OTStorage.h"

#include "OTData.h"

#include "OTString.h"
#include "OTStringXML.h"

#include "OTDataCheck.h"


#include "OTServer.h"


#include "OTMint.h"
#include "OTPseudonym.h"
#include "OTCheque.h"

#include "OTPayload.h"
#include "OTMessage.h"
#include "OTAccount.h"
#include "OTClientConnection.h"
#include "OTAssetContract.h"
#include "OTServerContract.h"

#include "OTItem.h"
#include "OTTransaction.h"
#include "OTLedger.h"
#include "OTToken.h"
#include "OTPurse.h"
#include "OTBasket.h"
#include "OTMarket.h"
#include "OTTrade.h"
#include "OTOffer.h"
#include "OTPaymentPlan.h"
#include "OTLog.h"

#include "OTCron.h"








// TODO:
//
// Code commands for checking your Cron Items and for canceling them.
// Code command for looking up specific markets from the server to see if they're supported.
// NOTE: For now, the server just creates any market you request, if it doesn't already exist.
//
// DONE Code the payment plan command code on client and server side handling.
// DONE OTServer needs to have a map of Markets, indexed by Market ID. The Offer "ID" matches this. (DONE)
// DONE Offer Minimum Increment MUST EXACTLY MATCH MARKET's .. can NOT simply "divide equally", although a second variable can be used for that...
// DONE Code the actual Cron processing for the Trades
// DONE ...and the Payment Plans.
//
//
// Get it all compiled.
// Get it all running again and debugged.


// --------------------------------------------------------------------------------------

void OTServer::ActivateCron()
{
	m_Cron.ActivateCron();
}


/// Currently the test server calls this 10 times per second.
/// It also processes all the input/output at the same rate.
/// It sleeps in between. (See testserver.cpp for the call 
/// and OTLog::Sleep() for the sleep code.)
///
void OTServer::ProcessCron()
{
	if (!m_Cron.IsActivated())
		return;
	
	bool bAddedNumbers = false;
	
	// Cron requires transaction numbers in order to process.
	// So every time before I call Cron.Process(), I make sure to replenish first.
	while (m_Cron.GetTransactionCount() < 20) 
	{
		long lTransNum = 0;
		bool bSuccess = IssueNextTransactionNumber(m_nymServer, lTransNum, false); // bStoreTheNumber = false
		
		if (bSuccess)
		{
			m_Cron.AddTransactionNumber(lTransNum);
			bAddedNumbers = true;
		}
		else
			break;
	}
	
	if (bAddedNumbers)
	{
		m_Cron.SaveCron();
	}
	
	m_Cron.ProcessCronItems(); // This needs to be called regularly for trades, markets, payment plans, etc to process.
	
	
	// NOTE:  TODO:  OTHER RE-OCCURRING SERVER FUNCTIONS CAN GO HERE AS WELL!! 
	//
	// Such as sweeping server accounts after expiration dates, etc.

}


// --------------------------------------------------------------------------------------


const OTPseudonym & OTServer::GetServerNym() const
{
	return m_nymServer;
}

// Server stores a map of BASKET_ID to BASKET_ACCOUNT_ID.
bool OTServer::AddBasketAccountID(const OTIdentifier & BASKET_ID, const OTIdentifier & BASKET_ACCOUNT_ID, 
								  const OTIdentifier & BASKET_CONTRACT_ID)
{
	OTIdentifier theBasketAcctID;
	
	if (LookupBasketAccountID(BASKET_ID, theBasketAcctID))
	{
		OTLog::Output(0, "User attempted to add Basket that already exists.\n");
		return false;
	}
	
	OTString strBasketID(BASKET_ID), strBasketAcctID(BASKET_ACCOUNT_ID), strBasketContractID(BASKET_CONTRACT_ID);
	
	m_mapBaskets[strBasketID.Get()]					= strBasketAcctID.Get();
	m_mapBasketContracts[strBasketContractID.Get()]	= strBasketAcctID.Get();

	return true;
}

/// Looks up a basket account ID and returns true or false.
/// (So you can confirm whether or not it's on the list.)
bool OTServer::VerifyBasketAccountID(const OTIdentifier & BASKET_ACCOUNT_ID)
{
	// Server stores a map of BASKET_ID to BASKET_ACCOUNT_ID. Let's iterate through that map...
	for (mapOfBaskets::iterator ii = m_mapBaskets.begin(); ii != m_mapBaskets.end(); ++ii)
	{
		OTString strBasketAcctID	= (*ii).second.c_str();
		
		OTIdentifier id_BASKET_ACCT(strBasketAcctID);
		
		if (BASKET_ACCOUNT_ID == id_BASKET_ACCT) // if the basket Acct ID passed in matches this one...
		{
			return true;
		}
	}
	return false;
}

/// Use this to find the basket account ID for this server (which is unique to this server)
/// using the contract ID to look it up. (The basket contract ID is unique to this server.)
bool OTServer::LookupBasketAccountIDByContractID(const OTIdentifier & BASKET_CONTRACT_ID, OTIdentifier & BASKET_ACCOUNT_ID)
{
	// Server stores a map of BASKET_ID to BASKET_ACCOUNT_ID. Let's iterate through that map...
	for (mapOfBaskets::iterator ii = m_mapBasketContracts.begin(); ii != m_mapBasketContracts.end(); ++ii)
	{
		OTString strBasketContractID	= (*ii).first.c_str();
		OTString strBasketAcctID		= (*ii).second.c_str();
		
		OTIdentifier id_BASKET_CONTRACT(strBasketContractID), id_BASKET_ACCT(strBasketAcctID);
		
		if (BASKET_CONTRACT_ID == id_BASKET_CONTRACT) // if the basket contract ID passed in matches this one...
		{
			BASKET_ACCOUNT_ID = id_BASKET_ACCT;
			return true;
		}
	}
	return false;
}


/// Use this to find the basket account ID for this server (which is unique to this server)
/// using the contract ID to look it up. (The basket contract ID is unique to this server.)
bool OTServer::LookupBasketContractIDByAccountID(const OTIdentifier & BASKET_ACCOUNT_ID, OTIdentifier & BASKET_CONTRACT_ID)
{
	// Server stores a map of BASKET_ID to BASKET_ACCOUNT_ID. Let's iterate through that map...
	for (mapOfBaskets::iterator ii = m_mapBasketContracts.begin(); ii != m_mapBasketContracts.end(); ++ii)
	{
		OTString strBasketContractID	= (*ii).first.c_str();
		OTString strBasketAcctID		= (*ii).second.c_str();
		
		OTIdentifier id_BASKET_CONTRACT(strBasketContractID), id_BASKET_ACCT(strBasketAcctID);
		
		if (BASKET_ACCOUNT_ID == id_BASKET_ACCT) // if the basket contract ID passed in matches this one...
		{
			BASKET_CONTRACT_ID = id_BASKET_CONTRACT;
			return true;
		}
	}
	return false;
}


/// Use this to find the basket account for this server (which is unique to this server)
/// using the basket ID to look it up (the Basket ID is the same for all servers)
bool OTServer::LookupBasketAccountID(const OTIdentifier & BASKET_ID, OTIdentifier & BASKET_ACCOUNT_ID)
{
	// Server stores a map of BASKET_ID to BASKET_ACCOUNT_ID. Let's iterate through that map...
	for (mapOfBaskets::iterator ii = m_mapBaskets.begin(); ii != m_mapBaskets.end(); ++ii)
	{
		OTString strBasketID		= (*ii).first.c_str();
		OTString strBasketAcctID	= (*ii).second.c_str();
		
		OTIdentifier id_BASKET(strBasketID), id_BASKET_ACCT(strBasketAcctID);
		
		if (BASKET_ID == id_BASKET) // if the basket ID passed in matches this one...
		{
			BASKET_ACCOUNT_ID = id_BASKET_ACCT;
			return true;
		}
	}
	return false;
}


/// Looked up the voucher account (where cashier's cheques are issued for any given asset type)
/// return a pointer to the account.  Since it's SUPPOSED to exist, and since it's being requested,
/// also will GENERATE it if it cannot be found, add it to the list, and return the pointer. Should
/// always succeed.
OTAccount * OTServer::GetVoucherAccount(const OTIdentifier & ASSET_TYPE_ID)
{
	OTAccount * pAccount = NULL;
	
	for (mapOfAccounts::iterator ii = m_mapVoucherAccounts.begin(); ii != m_mapVoucherAccounts.end(); ++ii)
	{
		pAccount = (*ii).second;
		
		OT_ASSERT_MSG(NULL != pAccount, "NULL account pointer in OTServer::GetVoucherAccount");
		
		if (ASSET_TYPE_ID == pAccount->GetAssetTypeID())
			return pAccount;
	}
	

	// If we made it down here, that means the voucher account wasn't on the list,
	// so we need to create it.
	
	const OTIdentifier SERVER_USER_ID(m_nymServer), SERVER_ID(m_strServerID);
	
	OTMessage theMessage;
	SERVER_USER_ID.GetString(theMessage.m_strNymID);
	ASSET_TYPE_ID.GetString(theMessage.m_strAssetID);
	SERVER_ID.GetString(theMessage.m_strServerID);
	
	pAccount = OTAccount::GenerateNewAccount(SERVER_USER_ID, SERVER_ID, m_nymServer, theMessage);
	
	if (NULL != pAccount)
	{
		OTString strAcctID;
		pAccount->GetIdentifier(strAcctID);

		OTLog::vOutput(0, "Successfully created voucher account ID:\n%s\nAsset Type ID:\n%s\n", 
				 strAcctID.Get(), theMessage.m_strAssetID.Get());
		

		if (false == SaveMainFile())
		{
			OTLog::Error("Error saving main server file containing new account ID!!\n");
			delete pAccount;
			pAccount = NULL;
		}
		else
		{
			// Add it to the server's list.
			m_mapVoucherAccounts[theMessage.m_strAssetID.Get()] = pAccount;
		}
		
		return pAccount;
	}
	else 
	{
		OTLog::vError("Failed trying to generate voucher account in OTServer::GetVoucherAccount with asset type ID: %s\n",
				theMessage.m_strAssetID.Get());
	}
	
	return NULL;
}
	

/// Lookup the current mint for any given asset type ID and series.
OTMint * OTServer::GetMint(const OTIdentifier & ASSET_TYPE_ID, int nSeries) // Each asset contract has its own Mint.
{
	OTMint * pMint = NULL;
	
	for (mapOfMints::iterator ii = m_mapMints.begin(); ii != m_mapMints.end(); ++ii)
	{
		pMint = (*ii).second;
		
		OT_ASSERT_MSG(NULL != pMint, "NULL mint pointer in OTServer::GetMint\n");
		
		OTIdentifier theID;
		pMint->GetIdentifier(theID);
		
		if (ASSET_TYPE_ID	== theID &&				// if the ID on the Mint matches the ID passed in
			nSeries			== pMint->GetSeries())	// and the series also matches...
			return pMint;							// return the pointer right here, we're done.
	}
	
	// --------------------------------------------------------------------
	
	// The mint isn't in memory for the series requested.
	const OTString ASSET_ID_STR(ASSET_TYPE_ID);
	
	OTString	strMintFilename; 
	strMintFilename.Format("%s%s%s%s%d", 
						   m_strServerID.Get(), OTLog::PathSeparator(), 
						   ASSET_ID_STR.Get(), ".", nSeries);
	
	const char * szFoldername	= OTLog::MintFolder();
	const char * szFilename		= strMintFilename.Get();
	
	// --------------------------------------------------------------------
		
	pMint = new OTMint(m_strServerID, m_strServerUserID, ASSET_ID_STR);

	// You cannot hash the Mint to get its ID. (The ID is a hash of the asset contract.)
	// Instead, you must READ the ID from the Mint file, and then compare it to the one expected
	// to see if they match (similar to how Account IDs are verified.)

	OT_ASSERT_MSG(NULL != pMint, "Error allocating memory for Mint in OTServer::GetMint");
	
	OTString strSeries; strSeries.Format("%s%d", ".", nSeries);
	//
	if (pMint->LoadMint(strSeries.Get()))
	{
		if (pMint->VerifyMint(m_nymServer)) // I don't verify the Mint's expiration date here, just its signature, ID, etc.
		{									// (Expiry dates are enforced on tokens during deposit--and checked against mint-- 
											// but expiry dates are only enforced on the Mint itself during a withdrawal.)
			// It's a multimap now...
			//m_mapMints[ASSET_ID_STR.Get()] = pMint;
			
			m_mapMints.insert ( pair<std::string, OTMint *>(ASSET_ID_STR.Get(), pMint) );
			
			return pMint;
		}
		else 
		{
			OTLog::vError("Error verifying Mint in OTServer::GetMint:\n%s%s%s\n", 
						  szFoldername, OTLog::PathSeparator(), szFilename);
			delete pMint;
			pMint = NULL;
		}
	}
	else 
	{
		OTLog::vError("Error loading Mint in OTServer::GetMint:\n%s%s%s\n", 
					  szFoldername, OTLog::PathSeparator(), szFilename);
		delete pMint;
		pMint = NULL;
	}

	return NULL;
}


/// Just as every request must be accompanied by a request number, so
/// every transaction request must be accompanied by a transaction number.
/// The request numbers can simply be incremented on both sides (per user.)
/// But the transaction numbers must be issued by the server and they do
/// not repeat from user to user. They are unique to transaction.
///
/// Users must ask the server to send them transaction numbers so that they
/// can be used in transaction requests. The server keeps an internal counter
/// and maintains a data file to store the latest one.
///
/// More specifically, the server file itself stores the latest transaction number
/// (So it knows what number to issue and increment when the next request comes in.)
///
/// But once it issues the next number, that number needs to be recorded in the nym file
/// for the user it was issued to, so that it can be verified later when he submits it
/// for a transaction--and so it can be removed once the transaction is complete (so it
/// won't work twice.)
/// 
/// The option to bSaveTheNumber defaults to true for this reason. But sometimes it
/// will be sent to false, in cases where the number doesn't need to be saved because
/// it's never going to be verified. For example, if the server creates a transaction
/// number so it can put a transaction into your inbox, it's never going to have to verify
/// that it actually put it into the inbox by checking it's own nymfile for that transaction
/// number. Instead it would just check its own server signature on the inbox. But I digress...
///
bool OTServer::IssueNextTransactionNumber(OTPseudonym & theNym, long &lTransactionNumber,
										  bool bStoreTheNumber/*=true*/)
{
	OTIdentifier NYM_ID(theNym), SERVER_NYM_ID(m_nymServer);
	
	// If theNym has the same ID as m_nymServer, then we'll use m_nymServer
	// instead of theNym.  (Since it's the same nym anyway, we'll stick to the
	// one we already loaded so any changes don't get overwritten later.)
	OTPseudonym * pNym = NULL;
	
	if (NYM_ID == SERVER_NYM_ID)
		pNym = &m_nymServer;
	else
		pNym = &theNym;
	
	// ----------------------------------------------------------------------------
	
	// m_lTransactionNumber stores the last VALID AND ISSUED transaction number.
	// So first, we increment that, since we don't want to issue the same number twice.
	m_lTransactionNumber++;
	
	// Next, we save it to file.
	if (false == SaveMainFile())
	{
		OTLog::Error("Error saving main server file.\n");
		m_lTransactionNumber--;
		return false;
	}
	
	// Each Nym stores the transaction numbers that have been issued to it.
	// (On client AND server side.)
	//
	// So whenever the server issues a new number, it's to a specific Nym, then
	// it is recorded in his Nym file before being sent to the client (where it
	// is also recorded in his Nym file.)  That way the server always knows which
	// numbers are valid for each Nym.
	
	else if ( bStoreTheNumber && 
			 (false == pNym->AddTransactionNum(m_nymServer, m_strServerID, m_lTransactionNumber, true))) // bSave = true
	{
		OTLog::Error("Error adding transaction number to Nym file.\n");
		m_lTransactionNumber--;
		SaveMainFile(); // Save it back how it was, since we're not issuing this number after all.
		return false;
	}
	
	// SUCCESS? 
	// Now the server main file has saved the latest transaction number,
	// and the number has been stored on the relevant nym file.
	// NOW we set it onto the parameter and return true.
	else 
	{  
		lTransactionNumber = m_lTransactionNumber;
		return true;		
	}
}



/// Transaction numbers are now stored in the nym file (on client and server side) for whichever nym
/// they were issued to. This function verifies whether or not the transaction number is present and valid
/// for any specific nym (i.e. for the nym passed in.)
bool OTServer::VerifyTransactionNumber(OTPseudonym & theNym, const long &lTransactionNumber) // passed by reference for speed, but not a return value.
{
	OTIdentifier NYM_ID(theNym), SERVER_NYM_ID(m_nymServer);
	
	// If theNym has the same ID as m_nymServer, then we'll use m_nymServer
	// instead of theNym.  (Since it's the same nym anyway, we'll stick to the
	// one we already loaded so any changes don't get overwritten later.)
	OTPseudonym * pNym = NULL;
	
	if (NYM_ID == SERVER_NYM_ID)
		pNym = &m_nymServer;
	else
		pNym = &theNym;

	
	if (pNym->VerifyTransactionNum(m_strServerID, lTransactionNumber))
		return true;
	else 
		OTLog::vError("Invalid transaction number: %ld.  (Current Trns# counter: %ld)\n", 
				lTransactionNumber, m_lTransactionNumber);
	
	return false;
}


/// Remove a transaction number from the Nym record once it's officially used/spent.
bool OTServer::RemoveTransactionNumber(OTPseudonym & theNym, const long &lTransactionNumber, bool bSave/*=false*/)
{
	OTIdentifier NYM_ID(theNym), SERVER_NYM_ID(m_nymServer);
	
	// If theNym has the same ID as m_nymServer, then we'll use m_nymServer
	// instead of theNym.  (Since it's the same nym anyway, we'll stick to the
	// one we already loaded so any changes don't get overwritten later.)
	OTPseudonym * pNym = NULL;
	
	if (NYM_ID == SERVER_NYM_ID)
		pNym = &m_nymServer;
	else
		pNym = &theNym;
	
	bool bRemoved = false;
	
	if (bSave)
		bRemoved = pNym->RemoveTransactionNum(m_nymServer, m_strServerID, lTransactionNumber); // the version that passes in a signer nym -- saves to local storage.
	else 
		bRemoved = pNym->RemoveTransactionNum(m_strServerID, lTransactionNumber); // the version that doesn't save.

	return bRemoved;
}


/// Remove an issued number from the Nym record once that nym accepts the receipt from his inbox.
bool OTServer::RemoveIssuedNumber(OTPseudonym & theNym, const long &lTransactionNumber, bool bSave/*=false*/)
{
	OTIdentifier NYM_ID(theNym), SERVER_NYM_ID(m_nymServer);
	
	// If theNym has the same ID as m_nymServer, then we'll use m_nymServer
	// instead of theNym.  (Since it's the same nym anyway, we'll stick to the
	// one we already loaded so any changes don't get overwritten later.)
	OTPseudonym * pNym = NULL;
	
	if (NYM_ID == SERVER_NYM_ID)
		pNym = &m_nymServer;
	else
		pNym = &theNym;
	
	bool bRemoved = pNym->RemoveIssuedNum(m_nymServer, m_strServerID, lTransactionNumber, bSave);
	
	return bRemoved;
}



/// The server supports various different asset types.
/// Any user may create a new asset type by uploading the asset contract to the server.
/// The server stores the contract in a directory and in its in-memory list of asset types.
/// You can call this function to look up any asset contract by ID. If it returns NULL,
/// you can add it yourself by uploading the contract.  But be sure that the public key
/// in the contract, used to sign the contract, is also the public key of the Nym of the
/// issuer.  They must match.  In the future I may create a special key category just for
/// this purpose. Right now I'm using the "contract" key which is already used to verify
/// any asset or server contract.
OTAssetContract * OTServer::GetAssetContract(const OTIdentifier & ASSET_TYPE_ID)
{
	OTAssetContract * pContract = NULL;
	
	for (mapOfContracts::iterator ii = m_mapContracts.begin(); ii != m_mapContracts.end(); ++ii)
	{
		if (pContract = (*ii).second) // if not null
		{
			OTIdentifier theContractID;
			pContract->GetIdentifier(theContractID);
			
			if (theContractID == ASSET_TYPE_ID)
				return pContract;
		}
		else 
		{
			OTLog::Error("NULL contract pointer in OTServer::GetAssetContract.\n");
		}
	}
	
	return NULL;
}



/// OTServer will take ownership of theContract from this point on,
/// and will be responsible for deleting it. MUST be allocated on the heap.
bool OTServer::AddAssetContract(OTAssetContract & theContract)
{
	OTAssetContract * pContract = NULL;
	
	OTString STR_CONTRACT_ID; OTIdentifier CONTRACT_ID;
	theContract.GetIdentifier(STR_CONTRACT_ID);
	theContract.GetIdentifier(CONTRACT_ID);
	
	// already exists
	if (pContract = GetAssetContract(CONTRACT_ID)) // if not null
		return false;
	
	m_mapContracts[STR_CONTRACT_ID.Get()] = &theContract;
	
	return true;
}


bool OTServer::SaveMainFileToString(OTString & strMainFile)
{
	// ---------------------------------------------------------------
	
	strMainFile.Format("<?xml version=\"1.0\"?>\n"
					   "<notaryServer version=\"%s\"\n"
					   " serverID=\"%s\"\n"
					   " serverUserID=\"%s\"\n"
					   " transactionNum=\"%ld\" >\n\n", m_strVersion.Get(), m_strServerID.Get(),
					   m_strServerUserID.Get(), m_lTransactionNumber);
	
	//mapOfContracts	m_mapContracts;   // If the server needs to store copies of the asset contracts, then here they are.
	//mapOfMints		m_mapMints;		  // Mints for each of those.
	
	// ---------------------------------------------------------------
	
	OTContract * pContract = NULL;
	
	for (mapOfContracts::iterator ii = m_mapContracts.begin(); ii != m_mapContracts.end(); ++ii)
	{
		pContract = (*ii).second;
		
		OT_ASSERT_MSG(NULL != pContract, "NULL contract pointer in OTServer::SaveMainFile.\n");
		
		// This is like the Server's wallet.
		pContract->SaveContractWallet(strMainFile);
		
		// ----------------------------------------
	}
	
	// Save the basket account information
	
	for (mapOfBaskets::iterator ii = m_mapBaskets.begin(); ii != m_mapBaskets.end(); ++ii)
	{
		OTString strBasketID		= (*ii).first.c_str();
		OTString strBasketAcctID	= (*ii).second.c_str();
		
		const	OTIdentifier BASKET_ACCOUNT_ID(strBasketAcctID);
				OTIdentifier BASKET_CONTRACT_ID;
		
		bool bContractID = LookupBasketContractIDByAccountID(BASKET_ACCOUNT_ID, BASKET_CONTRACT_ID);
		
		if (!bContractID)
		{
			OTLog::vError("Error in OTServer::SaveMainFile: Missing Contract ID for basket ID %s\n",
						  strBasketID.Get());
			break;
		}
		
		OTString strBasketContractID(BASKET_CONTRACT_ID);
		
		strMainFile.Concatenate("<basketInfo basketID=\"%s\"\n"
								" basketAcctID=\"%s\"\n"
								" basketContractID=\"%s\" />\n\n", 
								strBasketID.Get(), strBasketAcctID.Get(), strBasketContractID.Get());
	}
	
	/*
	 OTPseudonym * pNym = NULL;
	 
	 for (mapOfNyms::iterator ii = m_mapNyms.begin(); ii != m_mapNyms.end(); ++ii)
	 {		
	 pNym = (*ii).second;
	 
	 OT_ASSERT_MSG(NULL != pNym, "NULL pseudonym pointer in OTWallet::m_mapNyms, OTWallet::SaveWallet");
	 
	 pNym->SavePseudonymWallet(fl);
	 }
	 
	 
	 // ---------------------------------------------------------------
	 
	 OTContract * pServer = NULL;
	 
	 for (mapOfServers::iterator ii = m_mapServers.begin(); ii != m_mapServers.end(); ++ii)
	 {
	 pServer = (*ii).second;
	 
	 OT_ASSERT_MSG(NULL != pServer, "NULL server pointer in OTWallet::m_mapServers, OTWallet::SaveWallet");
	 
	 pServer->SaveContractWallet(fl);
	 }
	 
	 // ---------------------------------------------------------------
	 */
	
	strMainFile.Concatenate("</notaryServer>\n");
	
	return true;	
}

bool OTServer::SaveMainFile()
{
	static OTString strMainFilePath;
	
	if (!strMainFilePath.Exists())
	{
		strMainFilePath = "notaryServer.xml"; // todo fix hardcoding
	}

	// ---------------------------------------------------------------	
	
	OTString strMainFile;
	
	if (false == SaveMainFileToString(strMainFile))
	{
		OTLog::Error("Error saving to string in OTServer::SaveMainFile.\n");
		return false;
	}	
	
	// ---------------------------------------------------------------
	
	bool bSaved = OTDB::StorePlainString(strMainFile.Get(), ".", strMainFilePath.Get());
	
	if (!bSaved)
		OTLog::vError("Error saving main file: %s\n", strMainFilePath.Get());
	
	return bSaved;
}





void OTServer::Init()
{
	bool bSuccessInitDefault = 
	OTDB::InitDefaultStorage(OTDB_DEFAULT_STORAGE, 
							 OTDB_DEFAULT_PACKER, OTLog::Path(), 
							 "notaryServer.xml"); // todo stop hardcoding
	
	OTLog::ConfirmOrCreateFolder(OTLog::MarketFolder()); 
	OTLog::ConfirmOrCreateFolder(OTLog::CronFolder());
	OTLog::ConfirmOrCreateFolder(OTLog::NymFolder());
	OTLog::ConfirmOrCreateFolder(OTLog::AccountFolder());
	OTLog::ConfirmOrCreateFolder(OTLog::UserAcctFolder());
	OTLog::ConfirmOrCreateFolder(OTLog::ReceiptFolder());
	OTLog::ConfirmOrCreateFolder(OTLog::NymboxFolder());
	OTLog::ConfirmOrCreateFolder(OTLog::InboxFolder());
	OTLog::ConfirmOrCreateFolder(OTLog::OutboxFolder()); 
	OTLog::ConfirmOrCreateFolder(OTLog::CertFolder());
	OTLog::ConfirmOrCreateFolder(OTLog::PubkeyFolder()); 
	OTLog::ConfirmOrCreateFolder(OTLog::ContractFolder());
	OTLog::ConfirmOrCreateFolder(OTLog::MintFolder()); 
	OTLog::ConfirmOrCreateFolder(OTLog::SpentFolder());
	OTLog::ConfirmOrCreateFolder(OTLog::MarketFolder()); 	
	
	// Load up the transaction number.
	LoadMainFile();
	
	// We just want to call this function once in order to make sure that the
	// Nym is loaded up and ready for use decrypting messages that are sent to it.
	// If you comment this out, the server will be unable to decrypt and open envelopes.
	ValidateServerIDfromUser(m_strServerID);
		
	// With the Server's private key loaded, and the latest transaction number loaded,
	// the server is now ready for operation!
}



bool OTServer::LoadMainFile()
{
	const char * szFoldername = "."; // todo stop hardcoding.
	const char * szFilename = "notaryServer.xml"; // todo stop hardcoding.
	
	if (false == OTDB::Exists(szFoldername, szFilename))
	{
		OTLog::vError("OTServer::LoadMainFile: %s%s%s does not exist.\n", szFoldername, 
					  OTLog::PathSeparator(), szFilename);
		return false;
	}
	
	// --------------------------------------------------------------------
	//
	std::string strFileContents(OTDB::QueryPlainString(szFoldername, szFilename)); // <=== LOADING FROM DATA STORE.
	
	if (strFileContents.length() < 2)
	{
		OTLog::vError("OTServer::LoadMainFile: Error reading file: %s%s%s\n", 
					  szFoldername, OTLog::PathSeparator(), szFilename);
		return false;
	}
	// --------------------------------------------------------------------

	OTStringXML xmlFileContents(strFileContents.c_str());

	IrrXMLReader* xml = createIrrXMLReader(&xmlFileContents);
	
	OTCleanup<IrrXMLReader> theXMLGuardian(xml); // So I don't have to clean it up later.
	
	
	// parse the file until end reached
	while(xml && xml->read())
	{
		// strings for storing the data that we want to read out of the file
		
		OTString AssetName;
		OTString AssetContract;
		OTString AssetID;
		/*
		OTString NymName;
		OTString NymFile;
		OTString NymID;
		*/
		
//		OTString ServerName;
//		OTString ServerID;
		
		
		switch(xml->getNodeType())
		{
			case EXN_TEXT:
				// in this xml file, the only text which occurs is the messageText
				//messageText = xml->getNodeData();
				break;
			case EXN_ELEMENT:
			{
				if (!strcmp("notaryServer", xml->getNodeName()))
				{
					m_strVersion			= xml->getAttributeValue("version");					
					m_strServerID			= xml->getAttributeValue("serverID");
					m_strServerUserID		= xml->getAttributeValue("serverUserID");
					
					m_nymServer.SetIdentifier(m_strServerUserID);
					
					OTString strTransactionNumber;  // The server issues transaction numbers and stores the counter here for the latest one.
					strTransactionNumber	= xml->getAttributeValue("transactionNum");
					m_lTransactionNumber	= atol(strTransactionNumber.Get());
					
					OTLog::vOutput(0, "\nLoading Open Transactions server. File version: %s\nLast Issued Transaction Number: %ld\nServerID:\n%s\n", 
								   m_strVersion.Get(), m_lTransactionNumber, m_strServerID.Get());

					
					if (!m_nymServer.Loadx509CertAndPrivateKey())
					{
						OTLog::Output(0, "Error loading server certificate and keys.\n");
					}
					else if (!m_nymServer.VerifyPseudonym())
					{
						OTLog::Output(0, "Error verifying server nym.\n");
					}
					else 
					{
						// This file will be saved during the course of operation
						// Just making sure it is loaded up first.
						OT_ASSERT(m_nymServer.LoadSignedNymfile(m_nymServer));
				
						
//						m_nymServer.SaveSignedNymfile(m_nymServer); // Uncomment this if you want to create the file. NORMALLY LEAVE IT OUT!!!! DANGEROUS!!!
						
						OTLog::Output(0, "Loaded server certificate and keys. Next loading Cron...\n");
						
						// ----------------------------------------------------------------
						// Load Cron (now that we have the server Nym.
						// (I WAS loading this erroneously in Server.Init(), before
						// the Nym had actually been loaded from disk. That didn't work.)
						const OTIdentifier SERVER_ID(m_strServerID);
						
						// Make sure the Cron object has a pointer to the server's Nym.
						// (For signing stuff...)
						m_Cron.SetServerID(SERVER_ID);
						m_Cron.SetServerNym(&m_nymServer);
						
						if (!m_Cron.LoadCron())
							OTLog::Error("Failed loading Cron file in OTServer::Init.\n");
						
						// ----------------------------------------------------------------

						OTLog::Output(0, "Next loading the server contract...\n");
						
						// We have the serverID, so let's load  up the server Contract!
						OTString strContractPath(OTLog::ContractFolder());
						
						OTServerContract * pContract = new OTServerContract(m_strServerID, strContractPath, m_strServerID, m_strServerID);
						
						OT_ASSERT_MSG(NULL != pContract, "Error allocating memory for main Server Contract in OTServer::LoadMainFile\n");
						
						if (pContract->LoadContract()) 
						{
							if (pContract->VerifyContract())
							{
								OTLog::Output(0, "** Main Server Contract Verified **\n");
								
								m_pServerContract = pContract;
							}
							else
							{
								delete pContract; pContract = NULL;
								OTLog::Output(0, "Main Server Contract FAILED to verify.\n");
							}							
						}
						else 
						{
							delete pContract; pContract = NULL;
							OTLog::vOutput(0, "Failed reading Main Server Contract in OTServer::LoadMainFile:\n%s\n",
										  strContractPath.Get());
						}						
					}					
				}
				else if (!strcmp("basketInfo", xml->getNodeName()))
				{
					OTString strBasketID			= xml->getAttributeValue("basketID");					
					OTString strBasketAcctID		= xml->getAttributeValue("basketAcctID");
					OTString strBasketContractID	= xml->getAttributeValue("basketContractID");
					
					const OTIdentifier BASKET_ID(strBasketID), BASKET_ACCT_ID(strBasketAcctID), BASKET_CONTRACT_ID(strBasketContractID);
					
					if (AddBasketAccountID(BASKET_ID, BASKET_ACCT_ID, BASKET_CONTRACT_ID))						
						OTLog::vOutput(0, "Loading basket currency info...\n Basket ID:\n%s\n Basket Acct ID:\n%s\n Basket Contract ID:\n%s\n", 
								strBasketID.Get(), strBasketAcctID.Get(), strBasketContractID.Get());
					else						
						OTLog::vError("Error adding basket currency info...\n Basket ID:\n%s\n Basket Acct ID:\n%s\n", 
								strBasketID.Get(), strBasketAcctID.Get());
				}

				// Create an OTAssetContract and load them from file, (for each asset type),
				// and add them to the internal map.
				else if (!strcmp("assetType", xml->getNodeName()))
				{
					OTASCIIArmor ascAssetName = xml->getAttributeValue("name");	
					
					if (ascAssetName.Exists())
						ascAssetName.GetString(AssetName, false); // linebreaks == false
					
					AssetID			= xml->getAttributeValue("assetTypeID");	// hash of contract itself
					
					OTLog::vOutput(0, "\n\n****Asset Contract**** (server listing) Name: %s\nContract ID:\n%s\n",
								   AssetName.Get(), AssetID.Get());
					
					OTString strContractPath;
					strContractPath = OTLog::ContractFolder();

					OTAssetContract * pContract = new OTAssetContract(AssetName, strContractPath, AssetID, AssetID);
					
					OT_ASSERT_MSG(NULL != pContract, "Error allocating memory for Asset Contract in OTServer::LoadMainFile\n");
					
					if (pContract->LoadContract()) 
					{
						if (pContract->VerifyContract())
						{
							OTLog::Output(0, "** Asset Contract Verified **\n");
							
							pContract->SetName(AssetName);
							
							m_mapContracts[AssetID.Get()] = pContract;
						}
						else
						{
							delete pContract; pContract = NULL;
							OTLog::Output(0, "Asset Contract FAILED to verify.\n");
						}							
					}
					else 
					{
						delete pContract; pContract = NULL;
						OTLog::Output(0, "Failed reading file for Asset Contract in OTServer::LoadMainFile\n");
					}
				}

				// This is where the server finds out his own contract, which he hashes in order to verify his
				// serverID (which is either hardcoded or stored in the server xml file.)
				//
				// There should be only one of these per transaction server.
				//
				// Commented out because I don't need it right now. TODO. COMING SOON! So the server can load his
				// port information out of the contract BEFORE it starts listening on the port (right now port is
				// still hardcoded.)
				// Todo: Server should also then immediately connect to itself BASED ON THE INFO IN THE CONTRACT
				// in order to verify that whatever is running at that port IS, IN FACT, ITSELF!
				/*
				else if (!strcmp("notaryProvider", xml->getNodeName()))
				{
					ServerName		= xml->getAttributeValue("name");			
					ServerID		= xml->getAttributeValue("serverID");	// hash of contract itself
					
					OTLog::vOutput(0, "\n\n****Notary Server (contract)**** (server listing) Name: %s\nContract ID:\n%s\n",
								   ServerName.Get(), ServerID.Get());
					
					OTString strContractPath;
					strContractPath.Format("%s%s%s%s%s", OTLog::Path(), OTLog::PathSeparator(),
										   OTLog::ContractFolder(),
										   OTLog::PathSeparator(), ServerID.Get());
					OTServerContract * pContract = new OTServerContract(ServerName, strContractPath, ServerID);

					OT_ASSERT_MSG(NULL != pContract, "Error allocating memory for Server Contract in OTServer::LoadMainFile\n");
					
					if (pContract->LoadContract()) 
					{
						if (pContract->VerifyContract())
						{
							OTLog::Output(0, "** Server Contract Verified **\n");
							
							m_mapContracts[ServerID.Get()] = pContract;
						}
						else
						{
							delete pContract; pContract = NULL;
							OTLog::Output(0, "Server Contract FAILED to verify.\n");
						}							
					}
					else 
					{
						delete pContract; pContract = NULL;
						OTLog::Output(0, "Failed reading file for Server Contract in OTServer::LoadMainFile\n");
					}
				}
				 */
				
				
				
				/*
				 // commented out because, since I already have the serverID, then the server
				 // already knows which certfile to open in order to get at its private key.
				 // So I already have the private key loaded, so I don't need pseudonyms in
				 // the config file right now.
				 //
				 // In the future, I will load the server XML file (here) FIRST, and get the serverID and
				 // contract file from that. THEN I will hash the contract file and verify that it matches
				 // the serverID. THEN I will use that serverID to open the Certfile and get my private key.
				 //
				 // In the meantime I don't need this yet, serverID is setup in the config file (that I'm reading now.)
				else if (!strcmp("pseudonym", xml->getNodeName())) // The server has to sign things, too.
				{
					NymName = xml->getAttributeValue("name");// user-assigned name for GUI usage				
					NymID = xml->getAttributeValue("nymID"); // message digest from hash of x.509 cert, used to look up certfile.
					
					OTLog::vOutput(0, "\n\n** Pseudonym ** (server): %s\nID: %s\nfile: %s\n",
							NymName.Get(), NymID.Get(), NymFile.Get());
					
					OTPseudonym * pNym = new OTPseudonym(NymName, NymFile, NymID);
					
					if (pNym && pNym->LoadNymfile((char*)(NymFile.Get())))
					{
						if (pNym->Loadx509CertAndPrivateKey()) 
						{							
							if (pNym->VerifyPseudonym()) 
							{
								m_mapNyms[NymID.Get()] = pNym;
								g_pTemporaryNym = pNym; // TODO remove this temporary line used for testing only.
							}
							else {
								OTLog::Error("Error verifying public key from x509 against Nym ID in OTWallet::LoadWallet\n");
							}
						}
						else {
							OTLog::Error("Error loading x509 file for Pseudonym in OTWallet::LoadWallet\n");
						}
					}
					else {
						OTLog::Error("Error creating or loading Nym in OTWallet::LoadWallet\n");
					}
				}
				 				 
			
				*/
				
				
				else
				{
					// unknown element type
					OTLog::vError("unknown element type: %s\n", xml->getNodeName());
				}
			}
				break;
		}
	}
	
	return true;	
}







void OTServer::UserCmdCheckServerID(OTPseudonym & theNym, OTMessage & MsgIn, OTMessage & msgOut)
{
	// (1) set up member variables 
	msgOut.m_strCommand		= "@checkServerID";	// reply to checkServerID
	msgOut.m_strNymID		= MsgIn.m_strNymID;	// UserID
	msgOut.m_strServerID	= m_strServerID;	// ServerID, a hash of the server contract.
	
	if (MsgIn.m_strServerID == m_strServerID)	// ServerID, a hash of the server contract.
		msgOut.m_bSuccess		= true;
	else
		msgOut.m_bSuccess		= false;
	
	// (2) Sign the Message 
	msgOut.SignContract(m_nymServer);		
	
	// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
	//
	// FYI, SaveContract takes m_xmlUnsigned and wraps it with the signatures and ------- BEGIN  bookends
	// If you don't pass a string in, then SaveContract saves the new version to its member, m_strRawFile
	msgOut.SaveContract();
}



void OTServer::UserCmdGetTransactionNum(OTPseudonym & theNym, OTMessage & MsgIn, OTMessage & msgOut)
{
	long lTransNum = 0;
	
	// (1) set up member variables 
	msgOut.m_strCommand		= "@getTransactionNum";	// reply to getTransactionNum
	msgOut.m_strNymID		= MsgIn.m_strNymID;	// UserID
	msgOut.m_strServerID	= m_strServerID;	// ServerID, a hash of the server contract.
	
	// This call will save the new transaction number to the nym's file.
	bool bGotNextTransNum	= IssueNextTransactionNumber(theNym, lTransNum, false); // bool bStoreTheNumber = false
	
	OTIdentifier USER_ID;
	const OTIdentifier SERVER_ID(m_strServerID);
	theNym.GetIdentifier(USER_ID);
		
	OTLedger theLedger(USER_ID, USER_ID, SERVER_ID);
		
	if (!bGotNextTransNum)
	{
		lTransNum = 0;
		OTLog::Error("Error getting next transaction number in OTServer::UserCmdGetTransactionNum\n");
	}
	// Drop in the Nymbox 
	else if (msgOut.m_bSuccess = (theLedger.LoadNymbox() && theLedger.VerifyAccount(m_nymServer)) )
	{						
		OTTransaction * pTransaction = OTTransaction::GenerateTransaction(theLedger, OTTransaction::blank, lTransNum);
		
		if (NULL != pTransaction) // The above has an OT_ASSERT within, but I just like to check my pointers.
		{			
			pTransaction->	SignContract(m_nymServer);
			pTransaction->	SaveContract();

			theLedger.AddTransaction(*pTransaction);
			
			theLedger.ReleaseSignatures();
			theLedger.SignContract(m_nymServer);
			theLedger.SaveContract();
			theLedger.SaveNymbox();
		}
	}
	else
	{
		OTLog::Error("Error loading or verifying Nymbox in OTServer::UserCmdGetTransactionNum\n");
	}
	
	RemoveTransactionNumber(theNym, lTransNum, false); //bSave=false
	RemoveIssuedNumber(theNym, lTransNum, false); // I'll drop it in his Nymbox -- he can SIGN for it.
	// Then why was it added in the first place? Because we originally sent it back in the reply directly, 
	// so IssueNext was designed that way.

	// (2) Sign the Message 
	msgOut.SignContract(m_nymServer);		
	
	// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
	//
	// FYI, SaveContract takes m_xmlUnsigned and wraps it with the signatures and ------- BEGIN  bookends
	// If you don't pass a string in, then SaveContract saves the new version to its member, m_strRawFile
	msgOut.SaveContract();	
}

void OTServer::UserCmdGetRequest(OTPseudonym & theNym, OTMessage & MsgIn, OTMessage & msgOut)
{
	long lReqNum = 0;
	
	// (1) set up member variables 
	msgOut.m_strCommand		= "@getRequest";	// reply to getRequest
	msgOut.m_strNymID		= MsgIn.m_strNymID;	// UserID
	msgOut.m_strServerID	= m_strServerID;	// ServerID, a hash of the server contract.
	
	msgOut.m_bSuccess	= theNym.GetCurrentRequestNum(m_strServerID, lReqNum);
	
	// Server was unable to load ReqNum, which is unusual because the calling function
	// should have already insured its existence.
	if (!msgOut.m_bSuccess)
	{
		lReqNum = 0;
		OTLog::Error("Error loading request number in OTServer::UserCmdGetRequest\n");
	}
	
	msgOut.m_strRequestNum.Format("%ld", lReqNum);
	
	// (2) Sign the Message 
	msgOut.SignContract(m_nymServer);		
	
	// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
	//
	// FYI, SaveContract takes m_xmlUnsigned and wraps it with the signatures and ------- BEGIN  bookends
	// If you don't pass a string in, then SaveContract saves the new version to its member, m_strRawFile
	msgOut.SaveContract();
}



void OTServer::UserCmdSendUserMessage(OTPseudonym & theNym, OTMessage & MsgIn, OTMessage & msgOut)
{
	long lTransNum = 0;
	
	// (1) set up member variables 
	msgOut.m_strCommand		= "@sendUserMessage";	// reply to sendUserMessage
	msgOut.m_strNymID		= MsgIn.m_strNymID;	// UserID
	msgOut.m_strNymID2		= MsgIn.m_strNymID2;// UserID of recipient pubkey
	msgOut.m_strServerID	= m_strServerID;	// ServerID, a hash of the server contract.
		
	bool bGotNextTransNum	= IssueNextTransactionNumber(m_nymServer, lTransNum, false); // bool bStoreTheNumber = false

	OTPseudonym nym2;	
	nym2.SetIdentifier(MsgIn.m_strNymID2);
	
	OTIdentifier RECIPIENT_USER_ID(nym2), SERVER_ID(m_strServerID);
	
	OTLedger theLedger(RECIPIENT_USER_ID, RECIPIENT_USER_ID, SERVER_ID);

	OTString strInMessage(MsgIn);
	msgOut.m_ascInReferenceTo.SetString(strInMessage);

	if (!bGotNextTransNum)
	{
		lTransNum = 0;
		OTLog::Error("Error getting next transaction number in OTServer::UserCmdSendUserMessage\n");
	}
	// Drop in the Nymbox 
	else if (msgOut.m_bSuccess = (theLedger.LoadNymbox() && theLedger.VerifyAccount(m_nymServer)) )
	{						
		OTTransaction * pTransaction = OTTransaction::GenerateTransaction(theLedger, OTTransaction::message, lTransNum);
		
		if (NULL != pTransaction) // The above has an OT_ASSERT within, but I just like to check my pointers.
		{			
			pTransaction->	SetReferenceToNum(lTransNum);		// <====== Recipient RECEIVES entire incoming message as string here, which includes the sender user ID,
			pTransaction->	SetReferenceString(strInMessage);	// and has an OTEnvelope in the payload. Message is signed by sender, and envelope is encrypted to recipient.
			
			pTransaction->	SignContract(m_nymServer);
			pTransaction->	SaveContract();
			
			theLedger.AddTransaction(*pTransaction); // Add the message transaction to the nymbox.
			
			theLedger.ReleaseSignatures();
			theLedger.SignContract(m_nymServer);
			theLedger.SaveContract();
			theLedger.SaveNymbox();

			msgOut.m_bSuccess = true;
		}
		else 
		{
			msgOut.m_bSuccess = false;
		}
	}	
		
	// (2) Sign the Message 
	msgOut.SignContract(m_nymServer);		
	
	// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
	//
	// FYI, SaveContract takes m_xmlUnsigned and wraps it with the signatures and ------- BEGIN  bookends
	// If you don't pass a string in, then SaveContract saves the new version to its member, m_strRawFile
	msgOut.SaveContract();
}


void OTServer::UserCmdCheckUser(OTPseudonym & theNym, OTMessage & MsgIn, OTMessage & msgOut)
{
	// (1) set up member variables 
	msgOut.m_strCommand		= "@checkUser";	// reply to checkUser
	msgOut.m_strNymID		= MsgIn.m_strNymID;	// UserID
	msgOut.m_strNymID2		= MsgIn.m_strNymID2;// UserID of public key requested by user.
	msgOut.m_strServerID	= m_strServerID;	// ServerID, a hash of the server contract.
	
	OTPseudonym nym2;	
	nym2.SetIdentifier(MsgIn.m_strNymID2);
	
	// If success, we send the Nym2's public key back to the user.
	if (msgOut.m_bSuccess = nym2.LoadPublicKey())
	{
		nym2.GetPublicKey().GetPublicKey(msgOut.m_strNymPublicKey, true);
	}
	// if Failed, we send the user's message back to him, ascii-armored as part of response.
	else 
	{
		OTString tempInMessage(MsgIn);
		msgOut.m_ascInReferenceTo.SetString(tempInMessage);
	}
	
	// (2) Sign the Message 
	msgOut.SignContract(m_nymServer);		
	
	// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
	//
	// FYI, SaveContract takes m_xmlUnsigned and wraps it with the signatures and ------- BEGIN  bookends
	// If you don't pass a string in, then SaveContract saves the new version to its member, m_strRawFile
	msgOut.SaveContract();
}




/// An existing user is issuing a new currency.
void OTServer::UserCmdIssueAssetType(OTPseudonym & theNym, OTMessage & MsgIn, OTMessage & msgOut)
{
	// (1) set up member variables 
	msgOut.m_strCommand		= "@issueAssetType";// reply to issueAssetType
	msgOut.m_strNymID		= MsgIn.m_strNymID;	// UserID
	msgOut.m_strAssetID		= MsgIn.m_strAssetID;	// Asset Type ID, a hash of the asset contract.
	msgOut.m_strServerID	= m_strServerID;	// ServerID, a hash of the server contract.
	
	const OTIdentifier USER_ID(theNym), SERVER_ID(m_strServerID), ASSET_TYPE_ID(MsgIn.m_strAssetID);
	
	OTAssetContract * pAssetContract = NULL;

	// Make sure the contract isn't already available on this server.
	if (pAssetContract = GetAssetContract(ASSET_TYPE_ID))
	{
		OTLog::Error("Error: Attempt to issue asset type that already exists in OTServer::UserCmdIssueAssetType.\n");
	}
	else
	{		
		// Pull the contract out of the message and verify it.
		OTString strFoldername(OTLog::ContractFolder()), strFilename(MsgIn.m_strAssetID.Get());

		OTString strContract(MsgIn.m_ascPayload);
		pAssetContract = new OTAssetContract(MsgIn.m_strAssetID, strFoldername, strFilename, MsgIn.m_strAssetID);
		
		OTIdentifier	ASSET_USER_ID;
		bool			bSuccessLoadingContract	= false;
		bool			bSuccessCalculateDigest = false;
		OTPseudonym *	pNym					= NULL;

		if (pAssetContract)
		{
			bSuccessLoadingContract	= pAssetContract->LoadContractFromString(strContract);
			
			if (pNym = (OTPseudonym*)pAssetContract->GetContractPublicNym())
			{
//				pNym->GetIdentifier(ASSET_USER_ID);
				OTString strPublicKey;
				bool bGotPublicKey = pNym->GetPublicKey().GetPublicKey(strPublicKey);
				
				if (!bGotPublicKey)
				{
					OTLog::Error("Error getting public key in OTServer::UserCmdIssueAssetType.\n");
				}
				else 
				{
					bSuccessCalculateDigest = ASSET_USER_ID.CalculateDigest(strPublicKey);
					
					if (!bSuccessCalculateDigest)
					{
						OTLog::Error("Error calculating digest in OTServer::UserCmdIssueAssetType.\n");
					}
				}
			}
		}
				
		// Make sure the public key in the contract is the public key of the Nym.
		// If we successfully loaded the contract from the string, and the contract
		// internally verifies (the ID matches the hash of the contract, and the
		// signature verifies with the contract key that's inside the contract),
		// AND the Nym making this request has the same ID as the Nym in the
		// asset contract. (ONLY the issuer of that contract can connect to this
		// server and issue his currency.)
		// TODO make sure a receipt is issued that the issuer can post on his
		// website, to verify that he has indeed issued the currency at the specified
		// transaction processor.  That way, users can double-check.
		if (bSuccessCalculateDigest)
		{
			if ((ASSET_USER_ID == USER_ID))
										// The ID of the user who signed the contract must be the ID of the user
										// whose public key is associated with this user account. They are one.
			{
				if (pAssetContract->VerifyContract())
				{
					// Create an ISSUER account (like a normal account, except it can go negative)
					OTAccount * pNewAccount = NULL;
					OTCleanup<OTAccount> theAcctGuardian;
					
					// If we successfully create the account, then bundle it in the message XML payload
					if (pNewAccount = OTAccount::GenerateNewAccount(USER_ID, SERVER_ID, m_nymServer, MsgIn, 
																	OTAccount::issuer)) // This last parameter makes it an ISSUER account
					{																	// instead of the default SIMPLE.
						theAcctGuardian.SetCleanupTarget(*pNewAccount); // So I don't have to worry about cleaning it up.
						
						OTString tempPayload(*pNewAccount);
						msgOut.m_ascPayload.SetString(tempPayload);
				
						// Attach the new account number to the outgoing message.
						pNewAccount->GetIdentifier(msgOut.m_strAcctID);

						// Now that the account is actually created, let's add the new asset contract
						// to the server's list.
						AddAssetContract(*pAssetContract); // Do NOT clean this up unless failure! Server will clean it up.
						SaveMainFile(); // So the main xml file knows to load this asset type next time we run.
						
						// Make sure the contracts/%s file is created for next time.
						pAssetContract->SaveContract(OTLog::ContractFolder(), strFilename.Get());
						
						// ---------------------------------------------------

						OTIdentifier theNewAccountID;
						pNewAccount->GetIdentifier(theNewAccountID);
						
				//		OTLog::Error("DEBUG: GenerateNewAccount successfully returned account pointer. Contents:\n%s\n", tempPayload.Get());
						
						// -----------------------------------------------
						
						OTLog::Output(0, "Generating inbox/outbox for new issuer acct. IGNORE ANY \"FILE OPEN\" ERRORS HERE.\n");
						
						OTLedger	theOutbox	(USER_ID, theNewAccountID, SERVER_ID), 
									theInbox	(USER_ID, theNewAccountID, SERVER_ID);
						
						bool bSuccessLoadingInbox	= theInbox.LoadInbox();
						bool bSuccessLoadingOutbox	= theOutbox.LoadOutbox();
						
						// --------------------------------------------------------------------
						
						// ...or generate them otherwise...
						
						if (true == bSuccessLoadingInbox) // WEIRD IF THIS HAPPENED...
							bSuccessLoadingInbox	= theInbox.VerifyAccount(m_nymServer); // todo -- this should NEVER happen, the ID was just RANDOMLY generated, so HOW did the inbox already exist???
						else
						{
							bSuccessLoadingInbox	= theInbox.GenerateLedger(theNewAccountID, SERVER_ID, OTLedger::inbox, true); // bGenerateFile=true
							
							if (bSuccessLoadingInbox)
							{
								bSuccessLoadingInbox	= theInbox.SignContract(m_nymServer);
								
								if (bSuccessLoadingInbox)
								{
									bSuccessLoadingInbox = theInbox.SaveContract();
									
									if (bSuccessLoadingInbox)
										bSuccessLoadingInbox	= theInbox.SaveInbox();
								}
							}
						}
						
						// --------------------------------------------------------------------
						
						if (true == bSuccessLoadingOutbox) // WEIRD IF THIS HAPPENED....
							bSuccessLoadingOutbox	= theOutbox.VerifyAccount(m_nymServer);	// todo -- this should NEVER happen, the ID was just RANDOMLY generated, so HOW did the outbox already exist???
						else
						{
							bSuccessLoadingOutbox	= theOutbox.GenerateLedger(theNewAccountID, SERVER_ID, OTLedger::outbox, true); // bGenerateFile=true
							
							if (bSuccessLoadingOutbox)
							{
								bSuccessLoadingOutbox	= theOutbox.SignContract(m_nymServer);
								
								if (bSuccessLoadingOutbox)
								{
									bSuccessLoadingOutbox = theOutbox.SaveContract();
									
									if (bSuccessLoadingOutbox)
										bSuccessLoadingOutbox	= theOutbox.SaveOutbox();
								}
							}
						}
						
						// --------------------------------------------------------------------
						
						if (false == bSuccessLoadingInbox)
						{
							OTString strNewAcctID(theNewAccountID);
							
							OTLog::vError("ERROR generating inbox ledger in OTServer::UserCmdIssueAssetType:\n%s\n",
										  strNewAcctID.Get());
						}
						else if (false == bSuccessLoadingOutbox)
						{
							OTString strNewAcctID(theNewAccountID);
							
							OTLog::vError("ERROR generating outbox ledger in OTServer::UserCmdIssueAssetType:\n%s\n", 
										  strNewAcctID.Get());
						}
						else 
						{			
							msgOut.m_bSuccess = true; // <==== SUCCESS!!
							
							// TODO fire off a separate process here to create the mint.
							//
							// THE PROGRAM ALREADY EXISTS (CreateMint) and you can RUN IT BY HAND FOR NOW.
							// But in actual production environment, we'll trigger that executable here,
							// and within a few minutes, users will be able to getMint successfully (and
							// thus withdraw cash.)
						}
					}
					else 
					{
						OTLog::Error("Failure generating new issuer account in OTServer::UserCmdIssueAssetType.\n");
					}
				}
				else 
				{
					OTLog::Error("Failure verifying asset contract in OTServer::UserCmdIssueAssetType.\n");
				}
			}
			else 
			{
				OTString strAssetUserID(ASSET_USER_ID), strUserID;
				theNym.GetIdentifier(strUserID);
				OTLog::vError("User ID on this user account:\n%s\ndoes NOT match public key used in asset contract:\n%s\n",
						strUserID.Get(), strAssetUserID.Get());
			}
		}
		else
		{
			OTLog::Error("Failure loading asset contract from client in OTServer::UserCmdIssueAssetType\n");
		}
		
		
		if (pAssetContract && !msgOut.m_bSuccess) // We only clean it up here, if the Server didn't take ownership of it.
		{
			delete pAssetContract;
			pAssetContract = NULL;
		}
	}

	// Either way, we need to send the user's command back to him as well.
	{
		OTString tempInMessage(MsgIn);
		msgOut.m_ascInReferenceTo.SetString(tempInMessage);
	}

	// (2) Sign the Message 
	msgOut.SignContract(m_nymServer);		 
	
	// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
	//
	// FYI, SaveContract takes m_xmlUnsigned and wraps it with the signatures and ------- BEGIN  bookends
	// If you don't pass a string in, then SaveContract saves the new version to its member, m_strRawFile
	msgOut.SaveContract();
}



/// An existing user is creating an issuer account (that he will not control) based on a basket of currencies.
void OTServer::UserCmdIssueBasket(OTPseudonym & theNym, OTMessage & MsgIn, OTMessage & msgOut)
{
	// (1) set up member variables 
	msgOut.m_strCommand		= "@issueBasket";	// reply to issueBasket
	msgOut.m_strNymID		= MsgIn.m_strNymID;	// UserID
	msgOut.m_strServerID	= m_strServerID;	// ServerID, a hash of the server contract.
	
	// Either way, we need to send the user's command back to him as well.
	{
		OTString tempInMessage(MsgIn);
		msgOut.m_ascInReferenceTo.SetString(tempInMessage);
	}
	
	const OTIdentifier USER_ID(theNym), SERVER_ID(m_strServerID), SERVER_USER_ID(m_nymServer);
	
	OTString strBasket(MsgIn.m_ascPayload);
	OTBasket theBasket;
	
	if (theBasket.LoadContractFromString(strBasket) && theBasket.VerifySignature(theNym))
	{		
		// The contract ID of the basket is calculated based on the UNSIGNED portion of the contract
		// (so it is unique on every server) and for the same reason with the AccountID removed before calculating.
		OTIdentifier BASKET_ID, BASKET_ACCOUNT_ID, BASKET_CONTRACT_ID;
		theBasket.CalculateContractID(BASKET_ID);
		
		// Use BASKET_ID to look up the Basket account and see if it already exists (the server keeps a list.)
		bool bFoundBasket = LookupBasketAccountID(BASKET_ID, BASKET_ACCOUNT_ID);
		
		if (!bFoundBasket)
		{
			// Generate a new OTAssetContract -- the ID will be a hash of THAT contract, which includes theBasket as well as
			// the server's public key as part of its contents. Therefore, the actual Asset Type ID of the basket currency
			// will be different from server to server.
			//
			// BUT!! Because we can also generate a hash of theBasket.m_xmlUnsigned (which is what OTBasket::CalculateContractID
			// does) then we have a way of obtaining a number that will be the same from server to server, for cross-server
			// transfers of basket assets.
			//
			// The way it will work is, when the cross-server transfer request is generated, the server will check the asset contract
			// for the "from" account and see if it is for a basket currency. If it is, there will be a function on the contract
			// that returns the Basket ID, which can be included in the message to the target server, which uses the ID to look
			// for its own basket issuer account for the same basket asset type. This allows the target server to translate the 
			// Asset Type ID to its own corresponding ID for the same basket.
			
			
			// GenerateNewAccount also expects the NymID to be stored in m_strNymID.
			// Since we want the SERVER to be the user for basket accounts, I'm setting it that
			// way in MsgIn so that GenerateNewAccount will create the sub-account with the server
			// as the owner, instead of the user.
			SERVER_USER_ID.GetString(MsgIn.m_strNymID);
			
			// We need to actually create all the sub-accounts.
			// This loop also sets the Account ID onto the basket items (which formerly was blank, from the client.)
			// This loop also adds the BASKET_ID and the NEW ACCOUNT ID to a map on the server for later reference.
			for (int i = 0; i < theBasket.Count(); i++)
			{
				BasketItem * pItem = theBasket.At(i);
				
				
				/*
				 
				 // Just make sure theMessage has these members populated:
				 //
				 // theMessage.m_strNymID;
				 // theMessage.m_strAssetID; 
				 // theMessage.m_strServerID;
				 
				 // static method (call it without an instance, using notation: OTAccount::GenerateNewAccount)
				 OTAccount * OTAccount::GenerateNewAccount(	const OTIdentifier & theUserID,	const OTIdentifier & theServerID, 
															const OTPseudonym & theServerNym,	const OTMessage & theMessage,
															const OTAccount::AccountType eAcctType=OTAccount::simple)

				
				 // The above method uses this one internally...
				 bool OTAccount::GenerateNewAccount(const OTPseudonym & theServer, const OTMessage & theMessage,
													const OTAccount::AccountType eAcctType=OTAccount::simple)
				 
				 */
				
				OTAccount * pNewAccount = NULL;
				
				// GenerateNewAccount expects the Asset ID to be in MsgIn. So we'll just put it there to make things easy...
				pItem->SUB_CONTRACT_ID.GetString(MsgIn.m_strAssetID);
								
				// If we successfully create the account, then bundle it in the message XML payload
				if (pNewAccount = OTAccount::GenerateNewAccount(SERVER_USER_ID, SERVER_ID, m_nymServer, MsgIn))
				{
					msgOut.m_bSuccess = true;
					
					// Now the item finally has its account ID. Let's grab it.
					pNewAccount->GetIdentifier(pItem->SUB_ACCOUNT_ID);
					
					delete pNewAccount;
					pNewAccount = NULL;
				}
				else {
					msgOut.m_bSuccess = false;
					break;
				}
			} // for
			
			
			if (true == msgOut.m_bSuccess)
			{
				theBasket.ReleaseSignatures();
				theBasket.SignContract(m_nymServer);
				theBasket.SaveContract();
				
				// The basket does not yet exist on this server. Create a new Asset Contract to support it...
				OTAssetContract * pBasketContract = new OTAssetContract;
				
				// todo check for memory allocation failure here.
				
				// Put the Server's Public Key into the "contract" key field of the new Asset Contract...
				// This adds a "contract" key to the asset contract (the server's public key)
				// Asset Contracts are verified by a key found internal to the contract, so it's
				// necessary to put the key in there so it will verify later.
				// This also updates the m_xmlUnsigned contents, signs the contract, saves it,
				// and calculates the new ID.
				pBasketContract->CreateBasket(theBasket, m_nymServer);
				
				// Grab the new asset ID for the new basket currency
				pBasketContract->GetIdentifier(BASKET_CONTRACT_ID);
				OTString STR_BASKET_CONTRACT_ID(BASKET_CONTRACT_ID);
				
				// set the new Asset Type ID, aka ContractID, onto the outgoing message.
				msgOut.m_strAssetID = STR_BASKET_CONTRACT_ID;
				
				// Save the new Asset Contract to disk
				const OTString strFoldername(OTLog::ContractFolder()), strFilename(STR_BASKET_CONTRACT_ID.Get());

				// Save the new basket contract to the contracts folder 
				// (So the users can use it the same as they would use any other contract.)
				pBasketContract->SaveContract(strFoldername.Get(), strFilename.Get());
				
				AddAssetContract(*pBasketContract);
				// I don't save this here. Instead, I wait for AddBasketAccountID and then I call SaveMainFile after that. See below.
				// TODO need better code for reverting when something screws up halfway through a change.
				// If I add this contract, it's not enough to just "not save" the file. I actually need to re-load the file
				// in order to TRULY "make sure" this won't screw something up on down the line.
				
				// Once the new Asset Type is generated, from which the BasketID can be requested at will, next we need to create
				// the issuer account for that new Asset Type.  (We have the asset type ID and the contract file. Now let's create
				// the issuer account the same as we would for any normal issuer account.)
				//
				// The issuer account is special compared to a normal issuer account, because within its walls, it must store an
				// OTAccount for EACH sub-contract, in order to store the reserves. That's what makes the basket work.
				
				OTAccount * pBasketAccount = NULL;
				
				// GenerateNewAccount expects the Asset ID to be in MsgIn. So we'll just put it there to make things easy...
				MsgIn.m_strAssetID = STR_BASKET_CONTRACT_ID;
				
				if (pBasketAccount = OTAccount::GenerateNewAccount(SERVER_USER_ID, SERVER_ID, m_nymServer, MsgIn, OTAccount::basket))
				{			
					msgOut.m_bSuccess = true;
					
					pBasketAccount->GetIdentifier(msgOut.m_strAcctID); // string
					pBasketAccount->GetAssetTypeID().GetString(msgOut.m_strAssetID);
					
					pBasketAccount->GetIdentifier(BASKET_ACCOUNT_ID); // id
					
					// So the server can later use the BASKET_ID (which is universal)
					// to lookup the account ID on this server corresponding to that basket.
					// (The account ID will be different from server to server, thus the need
					// to be able to look it up via the basket ID.)
					AddBasketAccountID(BASKET_ID, BASKET_ACCOUNT_ID, BASKET_CONTRACT_ID);

					SaveMainFile(); // So the main xml file loads this basket info next time we run.
					
					delete pBasketAccount;
					pBasketAccount = NULL;
				}
				else {
					msgOut.m_bSuccess = false;
				}
				
			}// if true == msgOut.m_bSuccess
		}
	}
	
	// (2) Sign the Message 
	msgOut.SignContract(m_nymServer);		 
	
	// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
	//
	// FYI, SaveContract takes m_xmlUnsigned and wraps it with the signatures and ------- BEGIN  bookends
	// If you don't pass a string in, then SaveContract saves the new version to its member, m_strRawFile
	msgOut.SaveContract();
}




/// a user is exchanging in or out of a basket.  (Ex. He's trading 2 gold and 3 silver for 10 baskets, or vice-versa.)
void OTServer::UserCmdExchangeBasket(OTPseudonym & theNym, OTMessage & MsgIn, OTMessage & msgOut)
{
	// (1) set up member variables 
	msgOut.m_strCommand		= "@exchangeBasket";// reply to exchangeBasket
	msgOut.m_strNymID		= MsgIn.m_strNymID;	// UserID
	msgOut.m_strServerID	= m_strServerID;	// ServerID, a hash of the server contract.
	msgOut.m_strAssetID		= MsgIn.m_strAssetID;// basket asset type ID
	msgOut.m_bBool			= MsgIn.m_bBool;	// exchange in or out?
	
	const OTIdentifier	USER_ID(theNym), SERVER_ID(m_strServerID), 
						SERVER_USER_ID(m_nymServer), 
						BASKET_CONTRACT_ID(msgOut.m_strAssetID);
	
	OTIdentifier BASKET_ACCOUNT_ID;
	
	// Either way, we need to send the user's command back to him as well.
	{
		OTString tempInMessage(MsgIn);
		msgOut.m_ascInReferenceTo.SetString(tempInMessage);
	}
	
	// Set up some account pointer lists for later...
	listOfAccounts  listUserAccounts, listServerAccounts;
	
	// Here's the request from the user.
	OTString strBasket(MsgIn.m_ascPayload);
	OTBasket theBasket, theRequestBasket;
	
	long lTransferAmount = 0;

	// Now we have the Contract ID from the basket account, 
	// we can get a pointer to its asset contract...
	
	bool bLookup = LookupBasketAccountIDByContractID(BASKET_CONTRACT_ID, BASKET_ACCOUNT_ID);
	
	OTAccount * pBasketAcct = NULL;
	OTCleanup<OTAccount> theBasketAcctGuardian;
	
	// if the account we received IS INDEED a basket account, AND
	// we can load the request basket from a string, AND verify its signature...
	if (bLookup && theRequestBasket.LoadContractFromString(strBasket) && theRequestBasket.VerifySignature(theNym))
	{		
		// Load the basket account and make sure it exists.
		pBasketAcct = OTAccount::LoadExistingAccount(BASKET_ACCOUNT_ID, SERVER_ID);
		
		// If the pointer is NULL, that works too. Otherwise it cleans up the object at the end of this function.
		theBasketAcctGuardian.SetCleanupTargetPointer(pBasketAcct); 
		
		if (NULL == pBasketAcct)
		{
			OTLog::Error("ERROR loading the basket account in OTServer::UserCmdExchangeBasket\n");
			msgOut.m_bSuccess = false;
		}
		// Does it verify?
		// I call VerifySignature here since VerifyContractID was already called in LoadExistingAccount().
		else if (!pBasketAcct->VerifySignature(m_nymServer))
		{
			OTLog::Error("ERROR verifying signature on the basket account in OTServer::UserCmdExchangeBasket\n");
			msgOut.m_bSuccess = false;
		}		
		else 
		{
			// Now we get a pointer to its asset contract...
			OTAssetContract * pContract = GetAssetContract(BASKET_CONTRACT_ID);
			
			// Now let's load up the actual basket, from the actual asset contract.
			if (pContract && 
				theBasket.LoadContractFromString(pContract->GetBasketInfo()) && 
				theBasket.VerifySignature(m_nymServer) &&
				theBasket.Count() == theRequestBasket.Count() && 
				theBasket.GetMinimumTransfer() == theRequestBasket.GetMinimumTransfer())
			{
				// Loop through the request AND the actual basket TOGETHER...
				for (int i = 0; i < theBasket.Count(); i++)
				{
					BasketItem * pBasketItem	= theBasket.At(i);
					BasketItem * pRequestItem	= theRequestBasket.At(i); // we already know these are the same length
					
					// if not equal 
					if (!(pBasketItem->SUB_CONTRACT_ID == pRequestItem->SUB_CONTRACT_ID))
					{
						OTLog::Error("Error: expected asset type IDs to match in OTServer::UserCmdExchangeBasket\n");
						msgOut.m_bSuccess = false;
						break;
					}
					else // if equal
					{
						msgOut.m_bSuccess = true;
						
						// Load up the two accounts and perform the exchange...
						OTAccount * pUserAcct	= OTAccount::LoadExistingAccount(pRequestItem->SUB_ACCOUNT_ID, SERVER_ID);
						
						if (NULL == pUserAcct)
						{
							OTLog::Error("ERROR loading a user's asset account in OTServer::UserCmdExchangeBasket\n");
							msgOut.m_bSuccess = false;
							break;
						}

						OTAccount * pServerAcct	= OTAccount::LoadExistingAccount(pBasketItem->SUB_ACCOUNT_ID, SERVER_ID);

						if (NULL == pServerAcct)
						{
							OTLog::Error("ERROR loading a basket sub-account in OTServer::UserCmdExchangeBasket\n");
							msgOut.m_bSuccess = false;
							break;
						}
						
						// I'm preserving these points, to be deleted at the end.
						// They won't be saved until after ALL debits/credits were successful.
						// Once ALL exchanges are done, THEN it loops through and saves / deletes
						// all the accounts.
						listUserAccounts.push_back(pUserAcct);
						listServerAccounts.push_back(pServerAcct);

						
						// Do they verify?
						// I call VerifySignature here since VerifyContractID was already called in LoadExistingAccount().
						if (!(pUserAcct->GetAssetTypeID() == pBasketItem->SUB_CONTRACT_ID))
						{
							OTLog::Error("ERROR verifying asset type on a user's account in OTServer::UserCmdExchangeBasket\n");
							msgOut.m_bSuccess = false;
							break;
						}		
						else if (!pUserAcct->VerifySignature(m_nymServer))
						{
							OTLog::Error("ERROR verifying signature on a user's asset account in OTServer::UserCmdExchangeBasket\n");
							msgOut.m_bSuccess = false;
							break;
						}		
						else if (!pServerAcct->VerifySignature(m_nymServer))
						{
							OTLog::Error("ERROR verifying signature on a basket sub-account in OTServer::UserCmdExchangeBasket\n");
							msgOut.m_bSuccess = false;
							break;
						}		
						else 
						{
							// the amount being transferred between these two accounts is the minimum transfer amount
							// for the sub-account on the basket, multiplied by 
							lTransferAmount = (pBasketItem->lMinimumTransferAmount * theRequestBasket.GetTransferMultiple());

							// user is performing exchange IN
							if (msgOut.m_bBool)
							{
								if (pUserAcct->Debit(lTransferAmount) && pServerAcct->Credit(lTransferAmount))
								{
									msgOut.m_bSuccess = true;
								}
								else 
								{
									msgOut.m_bSuccess = false;
									OTLog::Output(0, "Unable to Debit user account, or Credit server account, in OTServer::UserCmdExchangeBasket\n");
									break;
								}
							}
							else // user is peforming exchange OUT 
							{
								if (pUserAcct->Credit(lTransferAmount) && pServerAcct->Debit(lTransferAmount))
								{
									msgOut.m_bSuccess = true;
								}
								else 
								{
									msgOut.m_bSuccess = false;
									OTLog::Output(0, "Unable to Credit user account, or Debit server account, in OTServer::UserCmdExchangeBasket\n");
									break;
								}								
							}
						}							
					}
				} // for
			}
			else 
			{
				OTLog::Error("Error finding asset contract for basket, or loading the basket from it, or verifying\n"
								"the signature on that basket, or the request basket didn't match actual basket.\n");
			}
		} // pBasket exists and signature verifies

		
		// Load up the two accounts and perform the exchange...
		OTAccount * pUserMainAcct	= NULL;
		OTCleanup<OTAccount> theUserAcctGuardian;
		
		// At this point, if we have successfully debited / credited the sub-accounts.
		// then we need to debit and credit the user's main basket account and the server's basket issuer account.
		if ((true == msgOut.m_bSuccess) && pBasketAcct &&
			(pUserMainAcct = OTAccount::LoadExistingAccount(theRequestBasket.GetRequestAccountID(), SERVER_ID)) &&
			theUserAcctGuardian.SetCleanupTargetPointer(pUserMainAcct) && // Make sure pUserMainAcct gets cleaned up
			 pUserMainAcct->VerifySignature(m_nymServer) && 
			(pUserMainAcct->GetAssetTypeID() == BASKET_CONTRACT_ID)) // Just make sure the two main basket accts have same currency type
		{
			lTransferAmount =  (theRequestBasket.GetMinimumTransfer() * theRequestBasket.GetTransferMultiple());
			
			// Load up the two accounts and perform the exchange...
			// user is performing exchange IN
			if (msgOut.m_bBool)
			{
				if (pUserMainAcct->Credit(lTransferAmount) && pBasketAcct->Debit(lTransferAmount))
				{
					msgOut.m_bSuccess = true;
				}
				else 
				{
					msgOut.m_bSuccess = false;
					OTLog::Output(0, "Unable to Credit user basket account, or Debit basket issuer account, "
							"in OTServer::UserCmdExchangeBasket\n");
				}
			}
			else // user is peforming exchange OUT 
			{
				if (pUserMainAcct->Debit(lTransferAmount) && pBasketAcct->Credit(lTransferAmount))
				{
					msgOut.m_bSuccess = true;
				}
				else 
				{
					msgOut.m_bSuccess = false;
					OTLog::Output(0, "Unable to Debit user basket account, or Credit basket issuer account, "
							"in OTServer::UserCmdExchangeBasket\n");
				}								
			}
		}
		else {
			OTLog::Error("Error loading or verifying user's main basket account in OTServer::UserCmdExchangeBasket\n");
			msgOut.m_bSuccess = false;
		}
		
		// At this point, we have hopefully credited/debited ALL the relevant accounts.
		// So now, let's Save them ALL to disk.. (and clean them up.)
		OTAccount * pAccount = NULL;

		// empty the list of user accounts (and save to disk, if everything was successful.)
		while (!listUserAccounts.empty())
		{
			pAccount = listUserAccounts.front();
			listUserAccounts.pop_front();
			
			if (true == msgOut.m_bSuccess)
			{
				pAccount->ReleaseSignatures();
				pAccount->SignContract(m_nymServer);
				pAccount->SaveContract();
				pAccount->SaveAccount();
			}
			
			delete pAccount; pAccount=NULL;
		}
		
		// empty the list of server accounts (and save to disk, if everything was successful.)
		while (!listServerAccounts.empty())
		{
			pAccount = listServerAccounts.front();
			listServerAccounts.pop_front();
			
			if (true == msgOut.m_bSuccess)
			{
				pAccount->ReleaseSignatures();
				pAccount->SignContract(m_nymServer);
				pAccount->SaveContract();
				pAccount->SaveAccount();
			}
			
			delete pAccount; pAccount=NULL;
		}
		
		
		if (true == msgOut.m_bSuccess)
		{
			pBasketAcct->ReleaseSignatures();
			pBasketAcct->SignContract(m_nymServer);
			pBasketAcct->SaveContract();
			pBasketAcct->SaveAccount();

			pUserMainAcct->ReleaseSignatures();
			pUserMainAcct->SignContract(m_nymServer);
			pUserMainAcct->SaveContract();
			pUserMainAcct->SaveAccount();
		}

		
		// NO need to cleanup pBasketAcct or pUserMainAcct here, since OTCleanup handles it now.
	}
	
	// (2) Sign the Message 
	msgOut.SignContract(m_nymServer);		 
	
	// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
	//
	// FYI, SaveContract takes m_xmlUnsigned and wraps it with the signatures and ------- BEGIN  bookends
	// If you don't pass a string in, then SaveContract saves the new version to its member, m_strRawFile
	msgOut.SaveContract();
}


/// An existing user is creating an asset account.
void OTServer::UserCmdCreateAccount(OTPseudonym & theNym, OTMessage & MsgIn, OTMessage & msgOut)
{
	// (1) set up member variables 
	msgOut.m_strCommand		= "@createAccount";	// reply to createAccount
	msgOut.m_strNymID		= MsgIn.m_strNymID;	// UserID
	msgOut.m_strServerID	= m_strServerID;	// ServerID, a hash of the server contract.
	
	const OTIdentifier USER_ID(theNym), SERVER_ID(m_strServerID);
	
	// ----------------------------------------------
	
	OTAccount * pNewAccount = NULL;
	
	// If we successfully create the account, then bundle it in the message XML payload
	if (pNewAccount = OTAccount::GenerateNewAccount(USER_ID, SERVER_ID, m_nymServer, MsgIn))
	{
		OTIdentifier theNewAccountID;
		pNewAccount->GetIdentifier(theNewAccountID);
		
//		OTLog::Error("DEBUG: GenerateNewAccount successfully returned account pointer. Contents:\n%s\n", tempPayload.Get());
			
		// -----------------------------------------------
		
		OTLedger	theOutbox(USER_ID, theNewAccountID, SERVER_ID), 
					theInbox(USER_ID, theNewAccountID, SERVER_ID);
		
		bool bSuccessLoadingInbox	= theInbox.LoadInbox();
		bool bSuccessLoadingOutbox	= theOutbox.LoadOutbox();
		
		// --------------------------------------------------------------------
		
		// ...or generate them otherwise...
		
		if (true == bSuccessLoadingInbox) // WEIRD IF THIS HAPPENED...
			bSuccessLoadingInbox	= theInbox.VerifyAccount(m_nymServer); // todo -- this should NEVER happen, the ID was just RANDOMLY generated, so HOW did the inbox already exist???
		else
		{
			bSuccessLoadingInbox	= theInbox.GenerateLedger(theNewAccountID, SERVER_ID, OTLedger::inbox, true); // bGenerateFile=true
			
			if (bSuccessLoadingInbox)
			{
				bSuccessLoadingInbox	= theInbox.SignContract(m_nymServer);
				
				if (bSuccessLoadingInbox)
				{
					bSuccessLoadingInbox = theInbox.SaveContract();
					
					if (bSuccessLoadingInbox)
						bSuccessLoadingInbox	= theInbox.SaveInbox();
				}
			}
		}
		
		// --------------------------------------------------------------------
		
		if (true == bSuccessLoadingOutbox) // WEIRD IF THIS HAPPENED....
			bSuccessLoadingOutbox	= theOutbox.VerifyAccount(m_nymServer);	// todo -- this should NEVER happen, the ID was just RANDOMLY generated, so HOW did the outbox already exist???
		else
		{
			bSuccessLoadingOutbox	= theOutbox.GenerateLedger(theNewAccountID, SERVER_ID, OTLedger::outbox, true); // bGenerateFile=true
			
			if (bSuccessLoadingOutbox)
			{
				bSuccessLoadingOutbox	= theOutbox.SignContract(m_nymServer);
				
				if (bSuccessLoadingOutbox)
				{
					bSuccessLoadingOutbox = theOutbox.SaveContract();
					
					if (bSuccessLoadingOutbox)
						bSuccessLoadingOutbox	= theOutbox.SaveOutbox();
				}
			}
		}
		
		// --------------------------------------------------------------------
		
		if (false == bSuccessLoadingInbox)
		{
			OTString strNewAcctID(theNewAccountID);
			
			OTLog::vError("ERROR generating inbox ledger in OTServer::UserCmdCreateAccount:\n%s\n",
						  strNewAcctID.Get());
		}
		else if (false == bSuccessLoadingOutbox)
		{
			OTString strNewAcctID(theNewAccountID);

			OTLog::vError("ERROR generating outbox ledger in OTServer::UserCmdCreateAccount:\n%s\n", 
						  strNewAcctID.Get());
		}
		else 
		{			
			msgOut.m_bSuccess = true; // <==== SUCCESS!!
			
			pNewAccount->GetIdentifier(msgOut.m_strAcctID);
			
			OTString tempPayload(*pNewAccount);
			msgOut.m_ascPayload.SetString(tempPayload);
		}
		
		// --------------------------------------------------------------------

		delete pNewAccount;
		pNewAccount = NULL;
	}
	
	// Either way, we need to send the user's command back to him as well.
	{
		OTString tempInMessage(MsgIn);
		msgOut.m_ascInReferenceTo.SetString(tempInMessage);
	}
	
	// (2) Sign the Message 
	msgOut.SignContract(m_nymServer);		 
	
	// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
	//
	// FYI, SaveContract takes m_xmlUnsigned and wraps it with the signatures and ------- BEGIN  bookends
	// If you don't pass a string in, then SaveContract saves the new version to its member, m_strRawFile
	msgOut.SaveContract();
}



void OTServer::NotarizeTransfer(OTPseudonym & theNym, OTAccount & theFromAccount, OTTransaction & tranIn, OTTransaction & tranOut)
{
	// The outgoing transaction is an "atTransfer", that is, "a reply to the transfer request"
	tranOut.SetType(OTTransaction::atTransfer);
		
	OTItem * pItem			= NULL;
	OTItem * pBalanceItem	= NULL;
	OTItem * pResponseItem	= NULL;
	OTItem * pResponseBalanceItem	= NULL;
	
	// The incoming transaction may be sent to inboxes and outboxes, and it
	// will probably be bundled in our reply to the user as well. Therefore,
	// let's grab it as a string.
	OTString strInReferenceTo;
	OTString strBalanceItem;

	// Grab the actual server ID from this object, and use it as the server ID here.
	const OTIdentifier	SERVER_ID(m_strServerID),		USER_ID(theNym),	ACCOUNT_ID(theFromAccount),
						SERVER_USER_ID(m_nymServer),	ASSET_TYPE_ID(theFromAccount.GetAssetTypeID());
	
	OTString strUserID(USER_ID), strAccountID(ACCOUNT_ID);

	// For now, there should only be one of these transfer items inside the transaction.
	// So we treat it that way... I either get it successfully or not.
	if ((pItem			= tranIn.GetItem(OTItem::transfer)) &&
		(pBalanceItem	= tranIn.GetItem(OTItem::balanceStatement)))  // must have included a balance statement for this transaction.
	{
		// The response item, as well as the inbox and outbox items, will contain a copy
		// of the request item. So I save it into a string here so they can all grab a copy of it
		// into their "in reference to" fields.
		pItem->SaveContract(strInReferenceTo);
		pBalanceItem->SaveContract(strBalanceItem);

		// IDFromAccount is the ID on the "from" Account that was passed in.
		// IDItemFromAccount is the "from" account ID on the transaction Item we are currently examining.
		// IDItemToAccount is the "to" account ID on the transaction item we are currently examining.
		OTIdentifier IDFromAccount(theFromAccount);

		// Server response item being added to server response transaction (tranOut)
		// They're getting SOME sort of response item.
		
		pResponseItem = OTItem::CreateItemFromTransaction(tranOut, OTItem::atTransfer);	 
		pResponseItem->SetStatus(OTItem::rejection); // the default.
		pResponseItem->SetReferenceString(strInReferenceTo); // the response item carries a copy of what it's responding to.
		pResponseItem->SetReferenceToNum(pItem->GetTransactionNum()); // This response item is IN RESPONSE to pItem and its Owner Transaction.
		tranOut.AddItem(*pResponseItem); // the Transaction's destructor will cleanup the item. It "owns" it now.		
				
		pResponseBalanceItem = OTItem::CreateItemFromTransaction(tranOut, OTItem::atBalanceStatement);	 
		pResponseBalanceItem->SetStatus(OTItem::rejection); // the default.
		pResponseBalanceItem->SetReferenceString(strBalanceItem); // the response item carries a copy of what it's responding to.
		pResponseBalanceItem->SetReferenceToNum(pItem->GetTransactionNum()); // This response item is IN RESPONSE to pItem and its Owner Transaction.
		tranOut.AddItem(*pResponseBalanceItem); // the Transaction's destructor will cleanup the item. It "owns" it now.		
		
//		OTString strTestInRefTo2;
//		pResponseItem->GetReferenceString(strTestInRefTo2);
//		OTLog::Error("DEBUG: Item in reference to: %s\n", strTestInRefTo2.Get());

		// Set the ID on the To Account based on what the transaction request said. (So we can load it up.)
		OTAccount * pDestinationAcct = OTAccount::LoadExistingAccount(pItem->GetDestinationAcctID(), SERVER_ID);
	
		OTCleanup<OTAccount> theDestAcctGuardian(pDestinationAcct); // This is safe in cases where NULL is returned. No more need to cleanup pDestAcct.
		
		// Only accept transfers with positive amounts.
		if (0 > pItem->GetAmount()) 
		{
			OTLog::Output(0, "Attempt to transfer negative balance.\n");
		}
	
		// I'm using the operator== because it exists.
		// If the ID on the "from" account that was passed in,
		// does not match the "Acct From" ID on this transaction item
		else if (!(IDFromAccount == pItem->GetPurportedAccountID()))
		{
			OTLog::Output(0, "Error: 'From' account ID on the transaction does not match 'from' account ID on the transaction item.\n");
		} 
		// ok so the IDs match. Does the destination account exist? 
		else if (NULL == pDestinationAcct)
		{
			OTLog::Output(0, "ERROR verifying existence of the 'to' account in OTServer::NotarizeTransfer\n");
		}
		// Are both of the accounts of the same Asset Type?
		else if (!(theFromAccount.GetAssetTypeID() == pDestinationAcct->GetAssetTypeID()))
		{
			OTString strFromAssetID(theFromAccount.GetAssetTypeID()), 
			strDestinationAssetID(pDestinationAcct->GetAssetTypeID());
			OTLog::vOutput(0, "ERROR - user attempted to transfer between accounts of 2 different "
					"asset types in OTServer::NotarizeTransfer:\n%s\n%s\n", strFromAssetID.Get(),
					strDestinationAssetID.Get());
		}
		// Does it verify?
		// I call VerifySignature here since VerifyContractID was already called in LoadExistingAccount().
		else if (!pDestinationAcct->VerifySignature(m_nymServer))
		{
			OTLog::Output(0, "ERROR verifying signature on, the 'to' account in OTServer::NotarizeTransfer\n");
		}
		
		// This entire function can be divided into the top and bottom halves.
		// The top half is oriented around finding the "transfer" item (in the "transfer" transaction)
		// and setting up the response item that will go into the response transaction.
		// The bottom half is oriented, in the case of success, around creating the necessary inbox
		// and outbox entries, and debiting the account, and basically performing the actual transfer.
		else 
		{			
			// Okay then, everything checks out. Let's add this to the sender's outbox and the recipient's inbox. 
			// IF they can be loaded up from file, or generated, that is. 

			// Load the inbox/outbox in case they already exist
			OTLedger	theFromOutbox(USER_ID, IDFromAccount, SERVER_ID), 
						theToInbox(pItem->GetDestinationAcctID(), SERVER_ID);
			
			bool bSuccessLoadingInbox	= theToInbox.LoadInbox();
			bool bSuccessLoadingOutbox	= theFromOutbox.LoadOutbox();
			
			// --------------------------------------------------------------------
			
			// ...or generate them otherwise...

			if (true == bSuccessLoadingInbox)
				bSuccessLoadingInbox	= theToInbox.VerifyAccount(m_nymServer);
			else
				bSuccessLoadingInbox	= theToInbox.GenerateLedger(pItem->GetDestinationAcctID(), SERVER_ID, OTLedger::inbox, true); // bGenerateFile=true
			
			
			// --------------------------------------------------------------------
			
			if (true == bSuccessLoadingOutbox)
				bSuccessLoadingOutbox	= theFromOutbox.VerifyAccount(m_nymServer);
			else
				bSuccessLoadingOutbox	= theFromOutbox.GenerateLedger(IDFromAccount, SERVER_ID, OTLedger::outbox, true); // bGenerateFile=true
			
			// --------------------------------------------------------------------
			
			OTLedger * pInbox	= theFromAccount.LoadInbox(m_nymServer); 
			OTLedger * pOutbox	= theFromAccount.LoadOutbox(m_nymServer); 
			
			OTCleanup<OTLedger> theInboxAngel(pInbox);
			OTCleanup<OTLedger> theOutboxAngel(pOutbox);
			
			if (NULL == pInbox || !pInbox->VerifyAccount(m_nymServer))
			{
				OTLog::Error("Error loading or verifying inbox.\n");
			}
			
			else if (NULL == pOutbox || !pOutbox->VerifyAccount(m_nymServer))
			{
				OTLog::Error("Error loading or verifying outbox.\n");
			}
			
			// --------------------------------------------------------------------
			
			else if (false == bSuccessLoadingInbox || false == bSuccessLoadingOutbox)
			{
				OTLog::Error("ERROR generating ledger in OTServer::NotarizeTransfer.\n");
			}
			else 
			{
				// Generate new transaction number for these new transactions
				// todo check this generation for failure (can it fail?)
				long lNewTransactionNumber = 0;
				
				IssueNextTransactionNumber(m_nymServer, lNewTransactionNumber, false); // bStoreTheNumber = false
				
				// ------------------------------------------
				// I create TWO Outbox transactions -- one for the real outbox, (theFromOutbox)
				// and one for pOutbox (used for verifying the balance statement.)
				// pTEMPOutboxTransaction (here below) is that last one, pOutbox.
				//
				OTTransaction * pTEMPOutboxTransaction	= OTTransaction::GenerateTransaction(*pOutbox, OTTransaction::pending,
																						 lNewTransactionNumber);
				// ------------------------------------------
				
				OTTransaction * pOutboxTransaction		= OTTransaction::GenerateTransaction(theFromOutbox, OTTransaction::pending,
																						 lNewTransactionNumber);
				
//				IssueNextTransactionNumber(m_nymServer, lNewTransactionNumber, false); // bStoreTheNumber = false
				OTTransaction * pInboxTransaction		= OTTransaction::GenerateTransaction(theToInbox, OTTransaction::pending,
																						 lNewTransactionNumber);
				// ------------------------------------------
							
				// UPDATE: I am now issuing one new transaction number above, instead of two. This is to make it easy
				// for the two to cross-reference each other. Later if I want to remove the transaction from the inbox
				// and need to know the corresponding transaction # for the outbox, it will be the same number.
				
				// I have to set this one up just like the one below.
				pTEMPOutboxTransaction->SetReferenceString(strInReferenceTo);
				pTEMPOutboxTransaction->SetReferenceToNum(pItem->GetTransactionNum());
				
				// -------------------------------------------
				
				// the new transactions store a record of the item they're referring to.
				pOutboxTransaction->SetReferenceString(strInReferenceTo);
				pOutboxTransaction->SetReferenceToNum(pItem->GetTransactionNum());
				
				//todo put these two together in a method.
				pInboxTransaction->	SetReferenceString(strInReferenceTo);
				pInboxTransaction->SetReferenceToNum(pItem->GetTransactionNum());
					  
				// Now we have created 2 new transactions from the server to the users' boxes
				// Let's sign them and add to their inbox / outbox.
				pOutboxTransaction->SignContract(m_nymServer);
				pInboxTransaction->	SignContract(m_nymServer);
				
				pOutboxTransaction->SaveContract();
				pInboxTransaction->	SaveContract();

				// -------------------------------------------

				// Meanwhile a copy of the outbox transaction is also added to 
				// pOutbox. (It's just another copy of the outbox, but used
				// purely for verifying the balance statement, while a different
				// copy of the outbox is used for actually adding the receipt
				// and saving to the outbox file.)
				//
				pTEMPOutboxTransaction->SignContract(m_nymServer);
				pTEMPOutboxTransaction->SaveContract();
				
				pOutbox->AddTransaction(*pTEMPOutboxTransaction); // pOutbox will clean this up
				
				// The balance item from the user, for the outbox transaction, will not have
				// the correct transaction number (because I just generated it above, so the user
				// could not possibly have known that when he sent his message.) Currently it is
				// set to "1" in the user request, but I just put the actual number in the pOutbox
				// above (since I now have the actual number.)
				//
				// So when the receipt is saved (the output transaction) it will show the user's
				// signed request with "1" in the outbox, included in the server's signed reply
				// with lNewTransactionNumber in the outbox to correspond to it. The user saves
				// a copy of the same receipt, thus he will be unable to produce a receipt signed
				// by the server, without producing the exact same thing.
				// ("1" in the request and lNewTransactionNumber in the signed response.)
				//
				// This all means that the below call to VerifyBalanceStatement() needs to verify
				// the number "1" on the user request, as lNewTransactionNumber in pOutbox, in order
				// to handle this special case, since otherwise the verification would fail.
				//
				if (!(pBalanceItem->VerifyBalanceStatement(pItem->GetAmount() * (-1), // My acct balance will be smaller as a result of this transfer. 
														   theNym,
														   *pInbox,
														   *pOutbox,
														   theFromAccount,
														   tranIn,
														   lNewTransactionNumber)))
				{
					OTLog::vOutput(0, "ERROR verifying balance statement while performing transfer. Acct ID:\n%s\n",
								   strAccountID.Get());
				}			

				else 
				{
					pResponseBalanceItem->SetStatus(OTItem::acknowledgement); // the balance agreement (just above) was successful.
					pResponseBalanceItem->SetNewOutboxTransNum(lNewTransactionNumber); // So the receipt will show that the client's "1" in the outbox is now actually "34" or whatever, issued by the server as part of successfully processing the transaction.
					
					// Deduct the amount from the account...
					// TODO an issuer account here, can go negative.
					// whereas a regular account should not be allowed to go negative.
					if (theFromAccount.Debit(pItem->GetAmount()))
					{//todo need to be able to "roll back" if anything inside this block fails.
						// Here the transactions we just created are actually added to the ledgers.
						theFromOutbox.	AddTransaction(*pOutboxTransaction);
						theToInbox.		AddTransaction(*pInboxTransaction);
						
						// Release any signatures that were there before (They won't
						// verify anymore anyway, since the content has changed.)
						theFromAccount.	ReleaseSignatures();
						theFromOutbox.	ReleaseSignatures();
						theToInbox.		ReleaseSignatures();
						
						// Sign all three of them.
						theFromAccount.	SignContract(m_nymServer);
						theFromOutbox.	SignContract(m_nymServer);
						theToInbox.		SignContract(m_nymServer);
						
						// Save all three of them internally
						theFromAccount.	SaveContract();
						theFromOutbox.	SaveContract();
						theToInbox.		SaveContract();
						
						// Save all three of their internals (signatures and all) to file.
						theFromAccount.	SaveAccount();
						theFromOutbox.	SaveOutbox();
						theToInbox.		SaveInbox();
						
						// Now we can set the response item as an acknowledgement instead of the default (rejection)
						// otherwise, if we never entered this block, then it would still be set to rejection, and the
						// new items would never have been added to the inbox/outboxes, and those files, along with
						// the account file, would never have had their signatures released, or been re-signed or 
						// re-saved back to file.  The debit failed, so all of those other actions would fail also.
						// BUT... if the message comes back with acknowledgement--then all of these actions must have
						// happened, and here is the server's signature to prove it.
						// Otherwise you get no items and no signature. Just a rejection item in the response transaction.
						pResponseItem->SetStatus(OTItem::acknowledgement);
					}
					else 
					{
						delete pOutboxTransaction; pOutboxTransaction = NULL; // I can't use OTCleanup here because sometimes we DON'T delete it. (above)
						delete pInboxTransaction; pInboxTransaction = NULL;
						OTLog::vOutput(0, "Unable to debit account in OTServer::NotarizeTransfer:  %ld\n", pItem->GetAmount());
					}					
				}
			} // both boxes were successfully loaded or generated.
		}

		// sign the response item before sending it back (it's already been added to the transaction above)
		// Now, whether it was rejection or acknowledgement, it is set properly and it is signed, and it
		// is owned by the transaction, who will take it from here.
		pResponseItem->SignContract(m_nymServer);
		pResponseItem->SaveContract(); // the signing was of no effect because I forgot to save.
		
		pResponseBalanceItem->SignContract(m_nymServer);
		pResponseBalanceItem->SaveContract();

//		OTString strTestInRefTo;
//		pResponseItem->GetReferenceString(strTestInRefTo);
//		OTLog::vError("DEBUG: Item in reference to: %s\n", strTestInRefTo.Get());
		
	} // if pItem = tranIn.GetItem(OTItem::transfer)
	else 
	{
		OTLog::Error("Error, expected OTItem::transfer in OTServer::NotarizeTransfer\n");
	}
}






/// NotarizeWithdrawal supports two withdrawal types:
///
/// OTItem::withdrawVoucher	This is a bank voucher, like a cashier's check. Funds are transferred to
///							the bank, who then issues a cheque drawn on an internal voucher account.
///
/// OTItem::withdrawal		This is a digital cash withdrawal, in the form of untraceable, blinded
///							tokens. Funds are transferred to the bank, who blind-signs the tokens.
///
void OTServer::NotarizeWithdrawal(OTPseudonym & theNym, OTAccount & theAccount, 
								  OTTransaction & tranIn, OTTransaction & tranOut)
{
	// The outgoing transaction is an "atWithdrawal", that is, "a reply to the withdrawal request"
	tranOut.SetType(OTTransaction::atWithdrawal);
	
	OTItem * pItem			= NULL;
	OTItem * pBalanceItem	= NULL;
	OTItem * pResponseItem	= NULL;
	OTItem * pResponseBalanceItem	= NULL;
	
	// The incoming transaction may be sent to inboxes and outboxes, and it
	// will probably be bundled in our reply to the user as well. Therefore,
	// let's grab it as a string.
	OTString strInReferenceTo;
	OTString strBalanceItem;

	// Grab the actual server ID from this object, and use it as the server ID here.
	const OTIdentifier	SERVER_ID(m_strServerID),		USER_ID(theNym), ACCOUNT_ID(theAccount),
						SERVER_USER_ID(m_nymServer),	ASSET_TYPE_ID(theAccount.GetAssetTypeID());
	
	const OTString strUserID(USER_ID), strAccountID(ACCOUNT_ID), strAssetTypeID(ASSET_TYPE_ID);
	
	// ------------------------------------------------------------------------
	//
	// WITHDRAW VOUCHER (like a cashier's cheque) is the top half of this function.
	//
	// For digital cash (blinded tokens), see the bottom half of this function.
	//
	
	
	if ((pItem			= tranIn.GetItem(OTItem::withdrawVoucher)) &&
		(pBalanceItem	= tranIn.GetItem(OTItem::balanceStatement))) // must have included a balance statement for this transaction.
	{
		// The response item will contain a copy of the request item. So I save it into a string 
		// here so they can all grab a copy of it into their "in reference to" fields.
		pItem->SaveContract(strInReferenceTo);
		pBalanceItem->SaveContract(strBalanceItem);

		// Server response item being added to server response transaction (tranOut)
		// (They're getting SOME sort of response item.)
		
		pResponseItem = OTItem::CreateItemFromTransaction(tranOut, OTItem::atWithdrawVoucher);	 
		pResponseItem->SetStatus(OTItem::rejection); // the default.
		pResponseItem->SetReferenceString(strInReferenceTo); // the response item carries a copy of what it's responding to.
		pResponseItem->SetReferenceToNum(pItem->GetTransactionNum()); // This response item is IN RESPONSE to pItem and its Owner Transaction.
		tranOut.AddItem(*pResponseItem); // the Transaction's destructor will cleanup the item. It "owns" it now.		
		
		pResponseBalanceItem = OTItem::CreateItemFromTransaction(tranOut, OTItem::atBalanceStatement);	 
		pResponseBalanceItem->SetStatus(OTItem::rejection); // the default.
		pResponseBalanceItem->SetReferenceString(strBalanceItem); // the response item carries a copy of what it's responding to.
		pResponseBalanceItem->SetReferenceToNum(pItem->GetTransactionNum()); // This response item is IN RESPONSE to pItem and its Owner Transaction.
		tranOut.AddItem(*pResponseBalanceItem); // the Transaction's destructor will cleanup the item. It "owns" it now.		
		
		OTAccount	* pVoucherReserveAcct	= NULL; // contains the server's funds to back vouchers of a specific asset type.
		
		// ----------------------------------------------------

		OTLedger * pInbox	= theAccount.LoadInbox(m_nymServer); 
		OTLedger * pOutbox	= theAccount.LoadOutbox(m_nymServer); 
		
		OTCleanup<OTLedger> theInboxAngel(pInbox);
		OTCleanup<OTLedger> theOutboxAngel(pOutbox);
		
		// ----------------------------------------------------
	
		// I'm using the operator== because it exists.
		// If the ID on the "from" account that was passed in,
		// does not match the "Acct From" ID on this transaction item
		if (!(ACCOUNT_ID == pItem->GetPurportedAccountID()))
		{  // TODO see if this is already verified by the caller function and if so, remove.
			OTLog::Output(0, "Error: Account ID does not match account ID on the withdrawal item.\n");
		}
		// --------------------------------------------------------------------
		
		else if (NULL == pInbox || !pInbox->VerifyAccount(m_nymServer))
		{
			OTLog::Error("Error loading or verifying inbox.\n");
		}
		
		else if (NULL == pOutbox || !pOutbox->VerifyAccount(m_nymServer))
		{
			OTLog::Error("Error loading or verifying outbox.\n");
		}
		
		// --------------------------------------------------------------------
		
		// The server will already have a special account for issuing vouchers. Actually, a list of them --
		// one for each asset type. Since this is the normal way of doing business, GetVoucherAccount() will
		// just create it if it doesn't already exist, and then return the pointer. Therefore, a failure here
		// is a catastrophic failure!  Should never fail.
		else if ((pVoucherReserveAcct = GetVoucherAccount(ASSET_TYPE_ID)) &&
				 pVoucherReserveAcct->VerifyAccount(m_nymServer))
		{					
			OTString strVoucherRequest, strItemNote;
			pItem->GetNote(strItemNote);
			pItem->GetAttachment(strVoucherRequest);
			
			OTIdentifier VOUCHER_ACCOUNT_ID(*pVoucherReserveAcct);
			
			OTCheque	theVoucher(SERVER_ID, ASSET_TYPE_ID),
						theVoucherRequest(SERVER_ID, ASSET_TYPE_ID);
			
			bool bLoadContractFromString = theVoucherRequest.LoadContractFromString(strVoucherRequest);
			
			if (!bLoadContractFromString)
			{
				OTLog::vError("ERROR loading voucher request from string in OTServer::NotarizeWithdrawal:\n%s\n",
						strVoucherRequest.Get());
			}
			else if (!(pBalanceItem->VerifyBalanceStatement(theVoucherRequest.GetAmount() * (-1), // My account's balance will go down by this much. 
															theNym,
															*pInbox,
															*pOutbox,
															theAccount,
															tranIn)))
			{
				OTLog::vOutput(0, "ERROR verifying balance statement while issuing voucher. Acct ID:\n%s\n",
							   strAccountID.Get());
			}
			else // successfully loaded the voucher request from the string...
			{
				pResponseBalanceItem->SetStatus(OTItem::acknowledgement); // the transaction agreement was successful.

				// -------------------------------------------
				
				OTString strChequeMemo;
				strChequeMemo.Format("%s\n%s", strItemNote.Get(), theVoucherRequest.GetMemo().Get());
				
				// 10 minutes ==    600 Seconds
				// 1 hour	==     3600 Seconds
				// 1 day	==    86400 Seconds
				// 30 days	==  2592000 Seconds
				// 3 months ==  7776000 Seconds
				// 6 months == 15552000 Seconds
				
				const time_t	VALID_FROM	= time(NULL);			// This time is set to TODAY NOW
				const time_t	VALID_TO	= VALID_FROM + 15552000;// This time occurs in 180 days (6 months)
				
				long lNewTransactionNumber = 0;
				
				IssueNextTransactionNumber(m_nymServer, lNewTransactionNumber); // bStoreTheNumber defaults to true. We save the transaction
																				// number on the server Nym (normally we'd discard it) because
				const long lAmount = theVoucherRequest.GetAmount();				// when the cheque is deposited, the server nym, as the owner of
				const OTIdentifier & RECIPIENT_ID = theVoucherRequest.GetRecipientUserID();	// the voucher account, needs to verify the transaction # on the
																				// cheque (to prevent double-spending of cheques.)
				bool bIssueVoucher = theVoucher.IssueCheque(
										lAmount,				// The amount of the cheque.
										lNewTransactionNumber,	// Requiring a transaction number prevents double-spending of cheques.
										VALID_FROM,				// The expiration date (valid from/to dates) of the cheque
										VALID_TO,				// Vouchers are automatically starting today and lasting 6 months.
										VOUCHER_ACCOUNT_ID,		// The asset account the cheque is drawn on.
										SERVER_USER_ID,			// User ID of the sender (in this case the server.)
										strChequeMemo.Get(),	// Optional memo field. Includes item note and request memo.
										theVoucherRequest.HasRecipient() ? (&RECIPIENT_ID) : NULL);

				// IF we successfully created the voucher, AND the voucher amount is greater than 0,
				// AND debited the user's account,
				// AND credited the server's voucher account,
				//
				// THEN save the accounts and return the voucher to the user.
				//
				if (bIssueVoucher					&& (lAmount > 0)				&&
					theAccount.				Debit(theVoucherRequest.GetAmount())	&&
					pVoucherReserveAcct->	Credit(theVoucherRequest.GetAmount()))
				{
					OTString strVoucher;
					theVoucher.SetAsVoucher();	// All this does is set the voucher's internal contract 
												// string to "VOUCHER" instead of "CHEQUE". 
					theVoucher.SignContract(m_nymServer);
					theVoucher.SaveContract();
					theVoucher.SaveContract(strVoucher);
					
					pResponseItem->SetAttachment(strVoucher);
					pResponseItem->SetStatus(OTItem::acknowledgement);
					
					
					// Release any signatures that were there before (They won't
					// verify anymore anyway, since the content has changed.)
					theAccount.	ReleaseSignatures();
					theAccount.	SignContract(m_nymServer);	// Sign 
					theAccount.	SaveContract();				// Save 
					theAccount.	SaveAccount();				// Save to file
					
					// We also need to save the Voucher cash reserve account.
					// (Any issued voucher cheque is automatically backed by this reserve account.
					// If a cheque is deposited, the funds come back out of this account. If the
					// cheque expires, then after the expiry period, if it remains in the account,
					// it is now the property of the transaction server.)
					pVoucherReserveAcct->ReleaseSignatures();
					pVoucherReserveAcct->SignContract(m_nymServer);
					pVoucherReserveAcct->SaveContract();
					pVoucherReserveAcct->SaveAccount();					
				}	
				//else{} // TODO log that there was a problem with the amount
				
			} // voucher request loaded successfully from string
		} // GetVoucherAccount()
		else 
		{
			OTLog::vError("GetVoucherAccount() failed in NotarizeWithdrawal. Asset Type:\n%s\n",
					strAssetTypeID.Get());
		}
		
		// sign the response item before sending it back (it's already been added to the transaction above)
		// Now, whether it was rejection or acknowledgement, it is set properly and it is signed, and it
		// is owned by the transaction, who will take it from here.
		pResponseItem->SignContract(m_nymServer);
		pResponseItem->SaveContract(); // the signing was of no effect because I forgot to save.
		
		pResponseBalanceItem->SignContract(m_nymServer);
		pResponseBalanceItem->SaveContract();
	}
	
	// --------------------------------------------------------------------------------------
	
	// WITHDRAW DIGITAL CASH (BLINDED TOKENS)
	//
	// For now, there should only be one of these withdrawal items inside the transaction.
	// So we treat it that way... I either get it successfully or not.
	else if ((pItem			= tranIn.GetItem(OTItem::withdrawal)) &&
			 (pBalanceItem	= tranIn.GetItem(OTItem::balanceStatement)))  // must have included a balance statement for this transaction.
	{
		// The response item will contain a copy of the request item. So I save it into a string 
		// here so they can all grab a copy of it into their "in reference to" fields.
		pItem->SaveContract(strInReferenceTo);
		pBalanceItem->SaveContract(strBalanceItem);

		// Server response item being added to server response transaction (tranOut)
		// They're getting SOME sort of response item.
		
		pResponseItem = OTItem::CreateItemFromTransaction(tranOut, OTItem::atWithdrawal);	 
		pResponseItem->SetStatus(OTItem::rejection); // the default.
		pResponseItem->SetReferenceString(strInReferenceTo); // the response item carries a copy of what it's responding to.
		pResponseItem->SetReferenceToNum(pItem->GetTransactionNum()); // This response item is IN RESPONSE to pItem and its Owner Transaction.
		tranOut.AddItem(*pResponseItem); // the Transaction's destructor will cleanup the item. It "owns" it now.		
		
		pResponseBalanceItem = OTItem::CreateItemFromTransaction(tranOut, OTItem::atBalanceStatement);	 
		pResponseBalanceItem->SetStatus(OTItem::rejection); // the default.
		pResponseBalanceItem->SetReferenceString(strBalanceItem); // the response item carries a copy of what it's responding to.
		pResponseBalanceItem->SetReferenceToNum(pItem->GetTransactionNum()); // This response item is IN RESPONSE to pItem and its Owner Transaction.
		tranOut.AddItem(*pResponseBalanceItem); // the Transaction's destructor will cleanup the item. It "owns" it now.		
						
		// --------------------------------------------------------------------
		
		OTLedger * pInbox	= theAccount.LoadInbox(m_nymServer); 
		OTLedger * pOutbox	= theAccount.LoadOutbox(m_nymServer); 
		
		OTCleanup<OTLedger> theInboxAngel(pInbox);
		OTCleanup<OTLedger> theOutboxAngel(pOutbox);
				
		// --------------------------------------------------------------------

		OTMint		* pMint = NULL;
		OTAccount	* pMintCashReserveAcct = NULL;
	
		if (0 > pItem->GetAmount())
		{
			OTLog::Output(0, "Attempt to withdraw a negative amount.\n");
		}
	
		// I'm using the operator== because it exists.
		// If the ID on the "from" account that was passed in,
		// does not match the "Acct From" ID on this transaction item
		else if (!(ACCOUNT_ID == pItem->GetPurportedAccountID()))
		{
			OTLog::Output(0, "Error: 'From' account ID on the transaction does not match 'from' account ID on the withdrawal item.\n");
		} 
				
		else if (NULL == pInbox || !pInbox->VerifyAccount(m_nymServer))
		{
			OTLog::Error("Error loading or verifying inbox.\n");
		}
		
		else if (NULL == pOutbox || !pOutbox->VerifyAccount(m_nymServer))
		{
			OTLog::Error("Error loading or verifying outbox.\n");
		}

		else
		{						
			
			// --------------------------------------------------------------------
			// The COIN REQUEST (including the prototokens) comes from the client side.
			// so we assume the OTToken is in the payload. Now we need to randomly choose one for
			// signing, and reply to the client with that number so that the client can reply back
			// to us with the unblinding factors for all the other prototokens (but that one.)
			//
			// In the meantime, I have to store this request somewhere -- presumably in the outbox or purse.
			// 
			// UPDATE!!! Looks like Lucre protocol is simpler than that. The request only needs to contain a
			// single blinded token, which the server signs and sends back. Done.
			//
			// The amount is known to be safe (by the mint) because the User asks the Mint to create
			// a denomination (say, 10) token. The Mint therefore uses the "Denomination 10" key to sign
			// the token, and will later use the "Denomination 10" key to verify the token. So the mint
			// obviously trusts its own keys... There is nothing else to "open and verify", since only the ID
			// itself is what gets blinded and verified.  The amount on the token (as well as the asset type)
			// is only there to help the bank to look up the right key, without which the token will DEFINITELY
			// NOT verify. So it is in the user's interest to supply the correct amount, because otherwise he'll
			// just get the wrong key and then get rejected by the bank.
			
			OTString strPurse;
			pItem->GetAttachment(strPurse);
			
			// Todo do more security checking in here, like making sure the withdrawal amount matches the
			// total of the proto-tokens. Update: I think this is done, since the Debits are done one-at-a-time
			// for each token and it's amount/denomination
			
			OTPurse thePurse(SERVER_ID, ASSET_TYPE_ID);
			OTPurse theOutputPurse(SERVER_ID, ASSET_TYPE_ID); 
			OTToken * pToken = NULL;
			dequeOfTokenPtrs theDeque;
			
			bool bSuccess = false;
			bool bLoadContractFromString = thePurse.LoadContractFromString(strPurse);
			
			if (!bLoadContractFromString)
			{
				OTLog::vError("ERROR loading purse from string in OTServer::NotarizeWithdrawal:\n%s\n",
						strPurse.Get());
			}
			else if (!(pBalanceItem->VerifyBalanceStatement(thePurse.GetTotalValue() * (-1), // This amount will be subtracted from my acct. 
															theNym,
															*pInbox,
															*pOutbox,
															theAccount,
															tranIn)))
			{
				OTLog::vOutput(0, "ERROR verifying balance statement while withdrawing cash. Acct ID:\n%s\n",
							   strAccountID.Get());
			}
			else // successfully loaded the purse from the string...
			{
				pResponseBalanceItem->SetStatus(OTItem::acknowledgement); // the transaction agreement was successful.
				
				// Pull the token(s) out of the purse that was received from the client.
				while (pToken = thePurse.Pop(m_nymServer))
				{
					// We are responsible to cleanup pToken
					// So I grab a copy here for later...
					theDeque.push_front(pToken);
					
					if ((pMint = GetMint(ASSET_TYPE_ID, pToken->GetSeries())) &&
						(pMintCashReserveAcct = pMint->GetCashReserveAccount()) &&
						!pMint->Expired())	// Mints expire halfway into their token expiration period. So if a mint creates
					{						// tokens valid from Jan 1 through Jun 1, then the Mint itself expires Mar 1.
						// That's when the next series Mint is phased in to start issuing tokens, even
						// though the server continues redeeming the first series tokens until June.
						OTString		theStringReturnVal;
						
						// TokenIndex is for cash systems that send multiple proto-tokens, so the Mint
						// knows which proto-token has been chosen for signing.
						// But Lucre only uses a single proto-token, so the token index is always 0.
						if (!(pToken->GetAssetID() == ASSET_TYPE_ID) ||
							!(pMint->SignToken(m_nymServer, *pToken, theStringReturnVal, 0))) // nTokenIndex = 0 // ******************************************
						{
							bSuccess = false;
							OTLog::Error("ERROR signing token in OTServer::NotarizeWithdrawal\n");
							break;
						}
						else
						{
							OTASCIIArmor	theArmorReturnVal(theStringReturnVal);
							
							pToken->ReleaseSignatures(); // this releases the normal signatures, not the Lucre signed token from the Mint, above.
							
							pToken->SetSignature(theArmorReturnVal, 0); // nTokenIndex = 0
							
							// Sign and Save the token
							pToken->SignContract(m_nymServer);
							pToken->SaveContract();
							
							// Now the token is in signedToken mode, and the other prototokens have been released.
							
							// Deduct the amount from the account...
							if (theAccount.Debit(pToken->GetDenomination()))
							{//todo need to be able to "roll back" if anything inside this block fails.
								bSuccess = true;
								
								// Credit the server's cash account for this asset type in the same
								// amount that was debited. When the token is deposited again, Debit that same
								// server cash account and deposit in the depositor's acct.
								// Why, you might ask? Because if the token expires, the money will stay in 
								// the bank's cash account instead of being lost (and screwing up the overall
								// issuer balance, with the issued money disappearing forever.) The bank knows
								// that once the series expires, whatever funds are left in that cash account are
								// for the bank to keep. They can be transferred to another account and kept, instead
								// of being lost.
								if (!pMintCashReserveAcct->Credit(pToken->GetDenomination()))
								{
									OTLog::Error("Error crediting mint cash reserve account...\n");
									
									// Reverse the account debit (even though we're not going to save it anyway.)
									theAccount.Credit(pToken->GetDenomination());
									bSuccess = false;
									break;
								}
							}
							else {
								bSuccess = false;
								OTLog::Output(0, "Unable to debit account in OTServer::NotarizeWithdrawal.\n");
								break; // Once there's a failure, we ditch the loop.
							}
						}					
					}
					else {
						bSuccess = false;
						OTLog::Error( "Unknown or expired Mint, or missing cash reserve for mint, in OTServer::NotarizeWithdrawal.\n");
						break; // Once there's a failure, we ditch the loop.
					}				
				} // While success popping token out of the purse...
				
				if (bSuccess)
				{
					while (!theDeque.empty()) 
					{
						pToken = theDeque.front();
						theDeque.pop_front();
						
						theOutputPurse.Push(theNym, *pToken); // these were in reverse order. Fixing with theDeque.
						
						delete pToken;
						pToken = NULL;
					} 
					
					strPurse.Release(); // just in case it only concatenates.
					
					theOutputPurse.SignContract(m_nymServer);
					theOutputPurse.SaveContract(); // todo this is probably unnecessary
					theOutputPurse.SaveContract(strPurse);				
					
					
					// Add the digital cash token to the response message
					pResponseItem->SetAttachment(strPurse);
					pResponseItem->SetStatus(OTItem::acknowledgement);
					
					// Release any signatures that were there before (They won't
					// verify anymore anyway, since the content has changed.)
					theAccount.	ReleaseSignatures();
					
					// Sign 
					theAccount.	SignContract(m_nymServer);
					
					// Save 
					theAccount.	SaveContract();
					
					// Save to file
					theAccount.	SaveAccount();
					
					// We also need to save the Mint's cash reserve.
					// (Any cash issued by the Mint is automatically backed by this reserve
					// account. If cash is deposited, it comes back out of this account. If the
					// cash expires, then after the expiry period, if it remains in the account,
					// it is now the property of the transaction server.)
					pMintCashReserveAcct->ReleaseSignatures();
					pMintCashReserveAcct->SignContract(m_nymServer);
					pMintCashReserveAcct->SaveContract();
					pMintCashReserveAcct->SaveAccount();
					
					// Notice if there is any failure in the above loop, then we will never enter this block.
					// Therefore the account will never be saved with the new debited balance, and the output
					// purse will never be added to the response item.  No tokens will be returned to the user
					// and the account will not be saved, thus retaining the original balance.
					//
					// Only if everything is successful do we enter this block, save the output purse onto the
					// response, and save the newly-debitted account back to disk.
				}
				// Still need to clean up theDeque
				else 
				{
					while (!theDeque.empty()) 
					{
						pToken = theDeque.front();
						theDeque.pop_front();
						
						delete pToken;
						pToken = NULL;
					} 				
				}
				
			} // purse loaded successfully from string
			
		} // the Account ID on the item matched properly
		
		
		
		// sign the response item before sending it back (it's already been added to the transaction above)
		// Now, whether it was rejection or acknowledgement, it is set properly and it is signed, and it
		// is owned by the transaction, who will take it from here.
		pResponseItem->SignContract(m_nymServer);
		pResponseItem->SaveContract(); // the signing was of no effect because I forgot to save.
		
		pResponseBalanceItem->SignContract(m_nymServer);
		pResponseBalanceItem->SaveContract();
	} // if pItem = tranIn.GetItem(OTItem::withdrawal)
	else 
	{
		OTLog::Error( "Error, expected OTItem::withdrawal in OTServer::NotarizeWithdrawal\n");
	}	
}
												  
								






/// for depositing a cheque or cash.
void OTServer::NotarizeDeposit(OTPseudonym & theNym, OTAccount & theAccount, OTTransaction & tranIn, OTTransaction & tranOut)
{
	// The outgoing transaction is an "atDeposit", that is, "a reply to the deposit request"
	tranOut.SetType(OTTransaction::atDeposit);
	
	OTItem * pItem			= NULL;
	OTItem * pBalanceItem	= NULL;
	OTItem * pResponseItem	= NULL;
	OTItem * pResponseBalanceItem	= NULL;
	
	// The incoming transaction may be sent to inboxes and outboxes, and it
	// will probably be bundled in our reply to the user as well. Therefore,
	// let's grab it as a string.
	OTString strInReferenceTo;
	OTString strBalanceItem;
	
	// Grab the actual server ID from this object, and use it as the server ID here.
	const OTIdentifier	SERVER_ID(m_strServerID),		USER_ID(theNym),	ACCOUNT_ID(theAccount),
						SERVER_USER_ID(m_nymServer),	ASSET_TYPE_ID(theAccount.GetAssetTypeID());
	
	const OTString strUserID(USER_ID), strAccountID(ACCOUNT_ID);
	
	OTMint		* pMint					= NULL; // the Mint itself.
	OTAccount	* pMintCashReserveAcct	= NULL; // the Mint's funds for cash withdrawals.


	// -------------------------------------------------------------------------------------------
	// DEPOSIT CHEQUE  (Deposit Cash is the bottom half of the function, deposit cheque is the top half.)
	
	// Deposit (the transaction) now supports deposit (the item) and depositCheque (the item)
	if ((pItem			= tranIn.GetItem(OTItem::depositCheque)) &&
		(pBalanceItem	= tranIn.GetItem(OTItem::balanceStatement)))  // must have included a balance statement for this transaction.
	{
		// The response item, as well as the sender's inbox, will soon contain a copy
		// of the request item. So I save it into a string here so they can grab a copy of it
		// into their "in reference to" fields.
		pItem->SaveContract(strInReferenceTo);
		pBalanceItem->SaveContract(strBalanceItem);
				
		// Server response item being added to server response transaction (tranOut)
		// They're getting SOME sort of response item.
		
		pResponseItem = OTItem::CreateItemFromTransaction(tranOut, OTItem::atDepositCheque);	 
		pResponseItem->SetStatus(OTItem::rejection); // the default.
		pResponseItem->SetReferenceString(strInReferenceTo); // the response item carries a copy of what it's responding to.
		pResponseItem->SetReferenceToNum(pItem->GetTransactionNum()); // This response item is IN RESPONSE to pItem and its Owner Transaction.
		tranOut.AddItem(*pResponseItem); // the Transaction's destructor will cleanup the item. It "owns" it now.		
		
		pResponseBalanceItem = OTItem::CreateItemFromTransaction(tranOut, OTItem::atBalanceStatement);	 
		pResponseBalanceItem->SetStatus(OTItem::rejection); // the default.
		pResponseBalanceItem->SetReferenceString(strBalanceItem); // the response item carries a copy of what it's responding to.
		pResponseBalanceItem->SetReferenceToNum(pItem->GetTransactionNum()); // This response item is IN RESPONSE to pItem and its Owner Transaction.
		tranOut.AddItem(*pResponseBalanceItem); // the Transaction's destructor will cleanup the item. It "owns" it now.		
		
		// If the ID on the "from" account that was passed in,
		// does not match the "Acct From" ID on this transaction item
		if (ACCOUNT_ID != pItem->GetPurportedAccountID())
		{
			// TODO: Verify that this if block is unnecessary, and if so, remove it.
			// (The item should already have been verified when the transaction itself was
			// verified, before this function was even called. I think this is just an oversight.)
			OTLog::Output(0, "Error: account ID does not match account ID on the deposit item.\n");
		} 
		else
		{
			// Get the cheque from the Item and load it up into a Cheque object.
			OTString strCheque;
			pItem->GetAttachment(strCheque);
			OTCheque theCheque(SERVER_ID, ASSET_TYPE_ID); // allocated on the stack :-)
			bool bLoadContractFromString = theCheque.LoadContractFromString(strCheque);
			
			if (!bLoadContractFromString)
			{
				OTLog::vError("ERROR loading cheque from string in OTServer::NotarizeDeposit:\n%s\n",
						strCheque.Get());
			}
			// You can't deposit a cheque into the same account that it's drawn on. (Otherwise, in loading
			// both accounts, I would cause one of them to  be overwritten. I'm not willing to do the same
			// pointer magic that I'm doing with Nyms... instead I just disallow this entirely.)
			else if (ACCOUNT_ID == theCheque.GetSenderAcctID()) // Depositor ACCOUNT_ID is recipient's acct. (theNym.) But pSenderNym is someone else (the sender).
			{
				OTLog::vError("ERROR in OTServer::NotarizeDeposit: Unable to deposit into the same account cheque was drawn on:\n%s\n",
							  strCheque.Get());
			}
			else
			{
				const OTIdentifier & SOURCE_ACCT_ID(theCheque.GetSenderAcctID());
				const OTIdentifier & SENDER_USER_ID(theCheque.GetSenderUserID());
				const OTIdentifier & RECIPIENT_USER_ID(theCheque.GetRecipientUserID());
				
				const OTString	strSenderUserID(SENDER_USER_ID), strRecipientUserID(RECIPIENT_USER_ID),
								strSourceAcctID(SOURCE_ACCT_ID);

				OTAccount *	pSourceAcct = NULL;	// We'll load this up and change its balance, save it then delete the instance.
												// (I'll use OTCleanup to take care of deleting the instance, so it's automatic.)
				OTCleanup<OTAccount> theSourceAcctGuardian; // This is set below, right after OTAccount::LoadExistingAccount().
				
				OTPseudonym		theSenderNym(SENDER_USER_ID);
				OTPseudonym *	pSenderNym = &theSenderNym;
								
				// Don't want to overwrite files or db records in cases where the sender is also the depositor.
				// (Similar concern if the server is also the depositor, but that's already partly handled
				// before we get to this point... theNym is already substituted for m_nymServer,
				// if the IDs match, before any of the commands are processed.)
				//
				// The conundrum is in the multiplicity of combinations. The server COULD be the sender
				// OR the depositor, or he could be BOTH, or the server might NOT be the sender OR depositor,
				// yet they could still be the same person.  Normally all 3 are separate entities.  That's a
				// lot of combinations. I want to make sure that I don't overwrite ANY files while juggling the 
				// respective nymfiles, transaction numbers, request numbers, etc.
				//
				// Solution:  When commands are first processed, and the Request Number is processed, theNym
				// is ALREADY replaced with m_nymServer IF the IDs match and the signature verifies. It is then
				// passed that way to all of the commands (including the one we are in now.)
				//
				// I THEN do the logic BELOW as additional to that. Make sure if you change anything that you
				// think long and hard about what you are doing!!
				// 
				// Here's the logic:
				// -- theNym is the depositor (for sure.)
				// -- m_nymServer is the server nym (for sure.)
				// -- By the time we get here, IF the ServerUserID and UserID match,
				//	  then theNym IS ALREADY m_nymServer, literally a reference to it.
				//    (This is performed before we even get to this point, so that the 
				//	  same problem doesn't occur with request numbers.)
				// -- In cases where the "server is also the depositor", it's therefore
				//	  ALREADY handled, since theNym already points to m_nymServer.
				// -- theSenderNym is used to load the sender nym in cases where we have 
				//	  to load it from file or db ourselves. (Most normal cases.)
				// -- In those normal cases, pSenderNym will point to theSenderNym and
				//	  we load it up from file or database.
				// -- In cases where the sender is also the user (the depositor), then
				//	  pSenderNym will point to theNym instead of to theSenderNym, and we
				//	  no longer bother loading it, since the user is already loaded.
				// -- In cases where the sender is also the server, then pSenderNym will
				//	  point to m_nymServer instead of to theSenderNym, and we no longer
				//	  bother loading it, since the server's nym is already loaded.
				
				bool	bDepositorIsServer	= ((USER_ID			== SERVER_USER_ID)	? true	: false);
				bool	bSenderIsServer		= ((SENDER_USER_ID	== SERVER_USER_ID)	? true	: false);
				bool	bDepositorIsSender	= ((SENDER_USER_ID	== USER_ID)			? true	: false);
				
				bool	bSenderAlreadyLoaded = false;
				
				// The depositor is already loaded, (for sure.)
				
				// The server is already loaded, (for sure.)
				
				// If the depositor IS the server, then it already points there (for sure.)
				if (bDepositorIsServer)
				{
					//OTPseudonym & theNym = m_nymServer; // Already handled in the code that calls IncrementRequestNum().
					//bSenderAlreadyLoaded = false; // Sender is either determined to be already loaded (directly below) or 
													// it is loaded as part of the cheque verification process below that.
													// At this point I can't set it because I just don't know yet.
				}
				
				// If the depositor IS the sender, pSenderNym points to depositor, and we're already loaded.
				if (bDepositorIsSender)
				{
					pSenderNym = &theNym;
					bSenderAlreadyLoaded = true;
				}
				
				// If the server IS the sender, pSenderNym points to the server, and we're already loaded.
				if (bSenderIsServer) 
				{
					pSenderNym = &m_nymServer;
					bSenderAlreadyLoaded = true;
				}
	
				OTLedger	theSenderInbox(SENDER_USER_ID, SOURCE_ACCT_ID, SERVER_ID); 
				
				// To deposit a cheque, need to verify:  (in no special order)
				// 
				// -- DONE Load the source account and verify it exists.
				// -- DONE Make sure the source acct is verified for the server signature.
				// -- DONE Make sure the Asset Type of the cheque matches the Asset Type of BOTH source and recipient accts.
				// -- DONE See if there is a Recipient User ID. If so, MAKE SURE it matches the user depositing the cheque!
				// -- DONE See if the Sender User even exists.
				// -- DONE See if the Sender User ID matches the hash of the actual public key in the sender's pubkey file.
				// -- DONE Make sure the cheque has the right server ID.
				// -- DONE Make sure the cheque has not yet EXPIRED.
				// -- DONE Make sure the cheque signature is verified with the sender's pubkey.
				// -- DONE Make sure the account ID on the transaction item matches the depositor account ID.
				// -- DONE Verify the funds are in the source acct.
				//
				// -- DONE Plus deal with sender's inbox.
				
				// Load source account's inbox
				bool bSuccessLoadingInbox	= theSenderInbox.LoadInbox();				
				
				// ...If it loads, verify it. Otherwise, generate it...
				if (true == bSuccessLoadingInbox)
					bSuccessLoadingInbox	= theSenderInbox.VerifyAccount(m_nymServer);
				else
					bSuccessLoadingInbox	= theSenderInbox.GenerateLedger(SOURCE_ACCT_ID, SERVER_ID, OTLedger::inbox, true); // bGenerateFile=true
				
				// --------------------------------------------------------------------

				OTLedger * pInbox	= theAccount.LoadInbox(m_nymServer); 
				OTLedger * pOutbox	= theAccount.LoadOutbox(m_nymServer); 
				
				OTCleanup<OTLedger> theInboxAngel(pInbox);
				OTCleanup<OTLedger> theOutboxAngel(pOutbox);
				
				if (NULL == pInbox || !pInbox->VerifyAccount(m_nymServer))
				{
					OTLog::Error("Error loading or verifying inbox.\n");
				}
				
				else if (NULL == pOutbox || !pOutbox->VerifyAccount(m_nymServer))
				{
					OTLog::Error("Error loading or verifying outbox.\n");
				}
				
				// --------------------------------------------------------------------
				
				else if (false == bSuccessLoadingInbox)
				{
					OTLog::vError("ERROR verifying or generating inbox ledger in OTServer::NotarizeDeposit for source acct ID:\n%s\n",
							strSourceAcctID.Get());
				}
				
				// See if the cheque is drawn on the same server as the deposit account (the server running this code right now.)
				else if (SERVER_ID != theCheque.GetServerID())
				{
					OTLog::vOutput(0, "Cheque rejected: Incorrect Server ID. Recipient User ID is:\n%s\n",
							strRecipientUserID.Get());					
				}
				
				// See if the cheque is already expired or otherwise not within it's valid date range.
				else if (false == theCheque.VerifyCurrentDate())
				{
					OTLog::vOutput(0, "Cheque rejected: Not within valid date range. Sender User ID:\n%s\nRecipient User ID:\n%s\n",
							strSenderUserID.Get(), strRecipientUserID.Get());					
				}
				
				// See if we can load the sender's public key (to verify cheque signature)
				// if !bSenderAlreadyLoaded since the server already had its public key loaded at boot-time.
				// (also since the depositor and sender might be the same person.)
				else if (!bSenderAlreadyLoaded && (false == theSenderNym.LoadPublicKey()))
				{
					OTLog::vOutput(0, "Error loading public key for cheque signer during deposit:\n%s\nRecipient User ID:\n%s\n", 
							strSenderUserID.Get(), strRecipientUserID.Get());
				}
		
				// See if the Nym ID (User ID) that we have matches the message digest of the public key.
				else if (false == pSenderNym->VerifyPseudonym())
				{
					OTLog::vOutput(0, "Failure verifying cheque: Bad Sender User ID (fails hash check of pubkey)"
							":\n%s\nRecipient User ID:\n%s\n",
							strSenderUserID.Get(), strRecipientUserID.Get());
				}
				
				// See if we can load the sender's nym file (to verify the transaction # on the cheque)
				// if !bSenderAlreadyLoaded since the server already had its nym file loaded at boot-time.
				// (also since the depositor and sender might be the same person.)
				else if (!bSenderAlreadyLoaded && (false == theSenderNym.LoadSignedNymfile(m_nymServer)))
				{
					OTLog::vOutput(0, "Error loading nymfile for cheque signer during deposit:\n%s\nRecipient User ID:\n%s\n", 
							strSenderUserID.Get(), strRecipientUserID.Get());
				}
				
				// Make sure they're not double-spending this cheque.
				else if (false == VerifyTransactionNumber(*pSenderNym, theCheque.GetTransactionNum()))
				{
					OTLog::vOutput(0, "Failure verifying cheque: Bad transaction number.\nRecipient User ID:\n%s\n",
							strRecipientUserID.Get());					
				}
				
				// Let's see if the sender's signature matches the one on the cheque...
				else if (false == theCheque.VerifySignature(*pSenderNym)) 
				{
					OTLog::vOutput(0, "Failure verifying cheque signature for sender ID:\n%s\nRecipient User ID:\n%s\n",
							strSenderUserID.Get(), strRecipientUserID.Get());					
				}
				
				// If there is a recipient user ID on the check, it must match the user depositing the cheque.
				// (But if there is NO recipient user ID, then it's a blank cheque and ANYONE can deposit it.)
				else if (theCheque.HasRecipient() && !(USER_ID == RECIPIENT_USER_ID))
				{
					OTLog::vOutput(0, "Failure matching cheque recipient to depositor. Depositor User ID:\n%s\n"
							"Cheque Recipient User ID:\n%s\n",
							strUserID.Get(), strRecipientUserID.Get());					
				}
				
				// Try to load the source account (that cheque is drawn on) up into memory.
				// We'll need to debit funds from it...  Also, set the cleanup object onto this pointer.
				else if (
							(
							 NULL == (pSourceAcct = OTAccount::LoadExistingAccount(SOURCE_ACCT_ID, SERVER_ID))
							) 
						 ||
							(
							 theSourceAcctGuardian.SetCleanupTargetPointer(pSourceAcct), false	// I want this to eval to false, but I want SetCleanup to call.
							)																	// Also, SetCleanup() is safe even if pointer is NULL.
						 )	
					// ----------------------------------------------------------------------------------
				{	
					OTLog::vOutput(0, "Cheque deposit failure, trying to load source acct, ID:\n%s\nRecipient User ID:\n%s\n",
							strSourceAcctID.Get(), strRecipientUserID.Get());					
				}
				
				// Does it verify?
				// I call VerifySignature here since VerifyContractID was already called in LoadExistingAccount().
				// (Otherwise I might normally call VerifyAccount(), which does both...)
				//
				// Someone can't just alter an account file, because then the server's signature
				// won't verify anymore on that file and transactions will fail such as right here:
				else if (!pSourceAcct->VerifySignature(m_nymServer))
				{
					OTLog::vOutput(0, "ERROR verifying signature on source account while depositing cheque. Acct ID:\n%s\n",
							strAccountID.Get());
					
//					delete pSourceAcct; // NO NEED TO DO THIS ANYMORE -- OTCleanup HANDLES THIS NOW! (The pointer
//					pSourceAcct = NULL; // will be cleaned up automatically when its guardian goes out of scope.)
				}
								
				// Need to make sure the signer is the owner of the account...
				else if (!pSourceAcct->VerifyOwner(*pSenderNym))
				{
					OTLog::vOutput(0, "ERROR verifying signer's ownership of source account while depositing cheque. Source Acct ID:\n%s\n",
							strAccountID.Get());
				}
								
				// Are both of the accounts, AND the cheque, all of the same Asset Type?
				else if (!(theCheque.GetAssetID() == pSourceAcct->GetAssetTypeID()) || 
						 !(theCheque.GetAssetID() == theAccount.GetAssetTypeID()))
				{
					OTString	strSourceAssetID(pSourceAcct->GetAssetTypeID()), 
								strRecipientAssetID(theAccount.GetAssetTypeID());
					
					OTLog::vOutput(0, "ERROR - user attempted to deposit cheque between accounts of 2 different "
							"asset types. Source Acct:\n%s\nType:\n%s\nRecipient Acct:\n%s\nType:\n%s\n",
							strSourceAcctID.Get(), strSourceAssetID.Get(),
							strAccountID.Get(), strRecipientAssetID.Get());
				}

								
				// The BALANCE AGREEMENT includes a signed and dated:
				/*
				 user ID, server ID, account ID, transaction ID.
				 
				 BY THE TIME you are ever inside the procesing for ANY transaction. we know for 
				 a fact that NotarizeTransaction has ALREADY checked all the items on the transaction
				 (the ones in its list) to make sure they ALL have the same owner, and signature,
				 and transaction number, and account ID, and server ID. This happens when the items
				 first load via VerifyContractID(), and then in NotarizeTransaction() with a call to
				 VerifyItems(). Therefore I can consider the above variables COVERED for pItem as
				 well as pBalanceItem.
				 
				 Balance Agreement also includes:
				 -- A copy of all the transaction numbers that should still be issued to the Nym,
				    AFTER one is removed from depositing this cheque. (The same number on tranIn and pItem.)
					NEED TO VERIFY BOTH LISTS ARE THE SAME AFTER REMOVING ONE ON MY SIDE.
				 -- Account balance.
				    (NEED TO VERIFY BALANCE WOULD BE THE SAME AFTER PROCESSING TRANSACTION.
				 -- Inbox and Outbox reports on a single list of sub-items.
				    (NEED TO VERIFY INBOX AND OUTBOX ITEMS MATCH BY RE-CREATING AND THEN COMPARING.)
				 
				 All these are now done in VerifyBalanceStatement().
				 
				 */
								
				else if (!(pBalanceItem->VerifyBalanceStatement(theCheque.GetAmount(), 
																theNym,
																*pInbox,
																*pOutbox,
																theAccount,
																tranIn)))
				{
					OTLog::vOutput(0, "ERROR verifying balance statement while depositing cheque. Acct ID:\n%s\n",
								   strAccountID.Get());
				}
				
				// Debit Source account, Credit Recipient Account, add to Sender's inbox.
				//
				// Also clear the transaction number so this cheque can't be deposited again.
				//
				else
				{	
					pResponseBalanceItem->SetStatus(OTItem::acknowledgement); // the transaction agreement was successful.

					// Deduct the amount from the source account, and add it to the recipient account...
					if (pSourceAcct->Debit(theCheque.GetAmount()) && 
						theAccount.Credit(theCheque.GetAmount()) &&
						
						// Clear the transaction number. Sender Nym was responsible for it (and still is, until
						// he signs to accept the cheque reecipt). Still, however, he HAS used the cheque, so
						// I'm removing his ability to use that number twice. It will remain on his issued list 
						// until he signs for the receipt.
						//
						RemoveTransactionNumber(*pSenderNym, theCheque.GetTransactionNum(), true) //bSave=true
						)
					{	// need to be able to "roll back" if anything inside this block fails.
						// update: actually does pretty good roll-back as it is. The debits and credits
						// don't save unless everything is a success.
						
						// Generate new transaction number (for putting the check receipt in the sender's inbox.)
						// todo check this generation for failure (can it fail?)
						long lNewTransactionNumber = 0;
						
						IssueNextTransactionNumber(m_nymServer, lNewTransactionNumber, false); // bStoreTheNumber = false
						
						OTTransaction * pInboxTransaction	= OTTransaction::GenerateTransaction(theSenderInbox, OTTransaction::chequeReceipt,
																								 lNewTransactionNumber);
						
						// The depositCheque request OTItem is saved as a "in reference to" field,
						// on the inbox chequeReceipt transaction.
						//todo put these two together in a method.
						pInboxTransaction->SetReferenceString(strInReferenceTo);
						pInboxTransaction->SetReferenceToNum(pItem->GetTransactionNum());
												
						// Now we have created a new transaction from the server to the sender's inbox
						// Let's sign and save it...
						pInboxTransaction->SignContract(m_nymServer);
						pInboxTransaction->SaveContract();
						
						// Here the transaction we just created is actually added to the source acct's inbox.
						theSenderInbox.AddTransaction(*pInboxTransaction);
						
						// ---------------------------------------------------------------------------------
						// AT THIS POINT, the source account is debited, the recipient account is credited,
						// and the sender's inbox has had the cheque transaction added to it as his receipt.
						// (He must perform a balance agreement in order to get it out of his inbox.)
						//
						// THERE IS NOTHING LEFT TO DO BUT SAVE THE FILES!!
						
						// Release any signatures that were there before (They won't
						// verify anymore anyway, since the content has changed.)
						pSourceAcct->	ReleaseSignatures();
						theAccount.		ReleaseSignatures();
						theSenderInbox.	ReleaseSignatures();
						
						// Sign all three of them.
						pSourceAcct->	SignContract(m_nymServer);
						theAccount.		SignContract(m_nymServer);
						theSenderInbox.	SignContract(m_nymServer);
						
						// Save all three of them internally
						pSourceAcct->	SaveContract();
						theAccount.		SaveContract();
						theSenderInbox.	SaveContract();
						
						// Save all three of their internals (signatures and all) to file.
						pSourceAcct->	SaveAccount();
						theAccount.		SaveAccount();
						theSenderInbox.	SaveInbox();
						
						// Now we can set the response item as an acknowledgement instead of the default (rejection)
						// otherwise, if we never entered this block, then it would still be set to rejection, and the
						// new item would never have been added to the inbox, and the inbox file, along with the
						// account files, would never have had their signatures released, or been re-signed or 
						// re-saved back to file.  The debit failed, so all of those other actions would fail also.
						// BUT... if the message comes back with acknowledgement--then all of these actions must have
						// happened, and here is the server's signature to prove it.
						// Otherwise you get no items and no signature. Just a rejection item in the response transaction.
						pResponseItem->SetStatus(OTItem::acknowledgement);
						
						
						// TODO: Our code that actually saves the new balance statement receipt should go here 
						// (that is, only after ultimate success.) Otherwise we still want to store the old receipt.
						// For now I'm verifying it, but not storing it.  This means the security for it works, but
						// in a dispute, I can't prove it / cover my ass.  So very soon a receipt WILL be saved here
						// that is, a copy of the user's signed BalanceAgreement.)
						
					}
					else 
					{
						OTLog::vOutput(0, "OTServer::NotarizeDeposit cheque: Presumably unable to debit %ld from source account ID:\n%s\n", 
								theCheque.GetAmount(), strSourceAcctID.Get());
					}
					
					// Make sure we clean this up.
//					delete pSourceAcct; // No longer necessary -- handled by OTCleanup in this case.
//					pSourceAcct = NULL; // OTCleanup handles this now.
				}
			} // successfully loaded cheque from string
		} // account ID DOES match item's account ID
		
		
		// sign the response item before sending it back (it's already been added to the transaction above)
		// Now, whether it was rejection or acknowledgement, it is set properly and it is signed, and it
		// is owned by the transaction, who will take it from here.
		pResponseItem->SignContract(m_nymServer);
		pResponseItem->SaveContract(); // the signing was of no effect because I forgot to save.
		
		pResponseBalanceItem->SignContract(m_nymServer);
		pResponseBalanceItem->SaveContract();

		//		OTString strTestInRefTo;
		//		pResponseItem->GetReferenceString(strTestInRefTo);
		//		OTLog::vOutput(0, "DEBUG: Item in reference to: %s\n", strTestInRefTo.Get());
		
	} // deposit cheque
	
	// ---------------------------------------------------------------------------------
	
	// BELOW -- DEPOSIT CASH
	
	// For now, there should only be one of these deposit items inside the transaction.
	// So we treat it that way... I either get it successfully or not.
	if ((pItem			= tranIn.GetItem(OTItem::deposit)) &&
		(pBalanceItem	= tranIn.GetItem(OTItem::balanceStatement)))  // must have also included a balance statement for this transaction.
	{
		// The response item, as well as the inbox and outbox items, will contain a copy
		// of the request item. So I save it into a string here so they can all grab a copy of it
		// into their "in reference to" fields.
		pItem->SaveContract(strInReferenceTo);
		pBalanceItem->SaveContract(strBalanceItem);
		
		// Server response item being added to server response transaction (tranOut)
		// They're getting SOME sort of response item.
		
		pResponseItem = OTItem::CreateItemFromTransaction(tranOut, OTItem::atDeposit);	 
		pResponseItem->SetStatus(OTItem::rejection); // the default.
		pResponseItem->SetReferenceString(strInReferenceTo); // the response item carries a copy of what it's responding to.
		pResponseItem->SetReferenceToNum(pItem->GetTransactionNum()); // This response item is IN RESPONSE to pItem and its Owner Transaction.
		tranOut.AddItem(*pResponseItem); // the Transaction's destructor will cleanup the item. It "owns" it now.		
		
		pResponseBalanceItem = OTItem::CreateItemFromTransaction(tranOut, OTItem::atBalanceStatement);	 
		pResponseBalanceItem->SetStatus(OTItem::rejection); // the default.
		pResponseBalanceItem->SetReferenceString(strBalanceItem); // the response item carries a copy of what it's responding to.
		pResponseBalanceItem->SetReferenceToNum(pItem->GetTransactionNum()); // This response item is IN RESPONSE to pItem and its Owner Transaction.
		tranOut.AddItem(*pResponseBalanceItem); // the Transaction's destructor will cleanup the item. It "owns" it now.		
		
		// If the ID on the "from" account that was passed in,
		// does not match the "Acct From" ID on this transaction item
		if (ACCOUNT_ID != pItem->GetPurportedAccountID())
		{
			OTLog::vOutput(0, "Error: 'From' account ID on the transaction does not match 'from' account ID on the deposit item.\n");
		} 
		else
		{
			// --------------------------------------------------------------------
			
			OTLedger * pInbox	= theAccount.LoadInbox(m_nymServer); 
			OTLedger * pOutbox	= theAccount.LoadOutbox(m_nymServer); 
			
			OTCleanup<OTLedger> theInboxAngel(pInbox);
			OTCleanup<OTLedger> theOutboxAngel(pOutbox);
			
			if (NULL == pInbox || !pInbox->VerifyAccount(m_nymServer))
			{
				OTLog::Error("Error loading or verifying inbox.\n");
			}
			
			else if (NULL == pOutbox || !pOutbox->VerifyAccount(m_nymServer))
			{
				OTLog::Error("Error loading or verifying outbox.\n");
			}
			
			// --------------------------------------------------------------------
			
			OTString strPurse;
			pItem->GetAttachment(strPurse);
						
			OTPurse thePurse(SERVER_ID, ASSET_TYPE_ID); 
			OTToken * pToken = NULL;
			
			bool bLoadContractFromString = thePurse.LoadContractFromString(strPurse);
			
			if (!bLoadContractFromString)
			{
				OTLog::vError("ERROR loading purse from string in OTServer::NotarizeDeposit:\n%s\n",
						strPurse.Get());
			}
			
			else if (!(pBalanceItem->VerifyBalanceStatement(thePurse.GetTotalValue(),
															theNym,
															*pInbox,
															*pOutbox,
															theAccount,
															tranIn)))
			{
				OTLog::vOutput(0, "ERROR verifying balance statement while depositing cheque. Acct ID:\n%s\n",
							   strAccountID.Get());
			}
			
			// TODO: double-check all verification stuff all around on the purse and token, transaction, mint, etc.

			else // the purse loaded successfully from the string
			{
				pResponseBalanceItem->SetStatus(OTItem::acknowledgement); // the transaction agreement was successful.
				
				bool bSuccess = false;
				
				// Pull the token(s) out of the purse that was received from the client.
				while(pToken = thePurse.Pop(m_nymServer))
				{
					// This way I don't have to worry about cleaning up pToken or leaking memory.
					OTCleanup<OTToken> theTokenGuardian(*pToken);
					
					pMint = GetMint(ASSET_TYPE_ID, pToken->GetSeries());
					
					if (NULL == pMint)
					{
						OTLog::Error("Unable to get or load Mint in OTServer::NotarizeDeposit.\n");
						break;
					}
					else if (pMintCashReserveAcct = pMint->GetCashReserveAccount())
					{
//						OTString DEBUG_STR(*pToken);
//						OTLog::vError("\n**************\nEXTRACTED TOKEN FROM PURSE:\n%s\n", DEBUG_STR.Get());
						
						OTString	strSpendableToken;
						bool bToken = pToken->GetSpendableString(m_nymServer, strSpendableToken);
//						OTLog::vError("\n**************\nSPENDABLE STRING:\n%s\n", strSpendableToken.Get());
						
						if (!bToken)  // if failure getting the spendable token data from the token object
						{
							bSuccess = false;
							OTLog::vOutput(0, "ERROR verifying token in OTServer::NotarizeDeposit: Failure retrieving token data. \n");
							break;
						}
						else if (!(pToken->GetAssetID() == ASSET_TYPE_ID)) // or if failure verifying asset type
						{
							bSuccess = false;
							OTLog::vOutput(0, "ERROR verifying token in OTServer::NotarizeDeposit: Wrong asset type. \n");
							break;
						}
						else if (!(pToken->GetServerID() == SERVER_ID))	// or if failure verifying server ID
						{
							bSuccess = false;
							OTLog::vOutput(0, "ERROR verifying token in OTServer::NotarizeDeposit: Wrong server ID. \n");
							break;
						}
						// This call to VerifyToken verifies the token's Series and From/To dates against the
						// mint's, and also verifies that the CURRENT date is inside that valid date range.
						//
						// It also verifies the Lucre coin data itself against the key for that series and
						// denomination. (The signed and unblinded Lucre coin is finally verified in Lucre
						// using the appropriate Mint private key.)						
						else if (!(pMint->VerifyToken(m_nymServer, strSpendableToken, pToken->GetDenomination())))
						{
							bSuccess = false;
							OTLog::vOutput(0, "ERROR verifying token in OTServer::NotarizeDeposit: Token verification failed. \n");
							break;
						}
						// Lookup the token in the SPENT TOKEN DATABASE, and make sure
						// that it hasn't already been spent...
						else if (pToken->IsTokenAlreadySpent(strSpendableToken))
						{
							bSuccess = false;
							OTLog::vOutput(0, "ERROR verifying token in OTServer::NotarizeDeposit: Token was already spent. \n");
							break;
						}
						else
						{					
							OTLog::vOutput(0, "SUCCESS verifying token!\n");
							// CREDIT the amount to the account...
							if (theAccount.Credit(pToken->GetDenomination()))
							{	// need to be able to "roll back" if anything inside this block fails.
								// so unless bSuccess is true, I don't save the account below.
								bSuccess = true;
								
								OTLog::vOutput(0, "SUCCESS crediting account.\n");
								
								// two defense mechanisms here:  mint cash reserve acct, and spent token database
								
								if (!pMintCashReserveAcct->Debit(pToken->GetDenomination()))
								{
									OTLog::Error("Error debiting the mint cash reserve account. Re-debiting user's asset account...\n");
									theAccount.Debit(pToken->GetDenomination());
									bSuccess = false;								
									break;
								}
								
								// Spent token database. This is where the call is made to add 
								// the token to the spent token database.
								// IF IT FAILS, we must set success back to false  :-(
								
								if (!pToken->RecordTokenAsSpent(strSpendableToken))
								{
									OTLog::Error("Error recording token as spent! Re-debiting account...\n");
									
									// Not necessary to put these back up since they aren't being saved (since failure)
									// but I just like being thorough...
									theAccount.Debit(pToken->GetDenomination());
									pMintCashReserveAcct->Credit(pToken->GetDenomination());
									bSuccess = false;								
									break;
								}
							}
							else {
								bSuccess = false;
								OTLog::Error("Unable to credit account in OTServer::NotarizeDeposit.\n");
								break;
							}
						}					
					}
					else 
					{
						OTLog::Error("Unable to get cash reserve account for Mint in OTServer::NotarizeDeposit.\n");
						break;
					}
					
//					delete pToken; // Unnecessary now, handled by OTCleanup.
//					pToken = NULL;
					
				} // while success popping token from purse

				if (bSuccess)
				{
					// Release any signatures that were there before (They won't
					// verify anymore anyway, since the content has changed.)
					theAccount.	ReleaseSignatures();
					
					// Sign 
					theAccount.	SignContract(m_nymServer);
					
					// Save 
					theAccount.	SaveContract();
					
					// Save to file
					theAccount.	SaveAccount();
					
					// We also need to save the Mint's cash reserve.
					// (Any cash issued by the Mint is automatically backed by this reserve
					// account. If cash is deposited, it comes back out of this account. If the
					// cash expires, then after the expiry period, if it remains in the account,
					// it is now the property of the transaction server.)
					pMintCashReserveAcct->ReleaseSignatures();
					pMintCashReserveAcct->SignContract(m_nymServer);
					pMintCashReserveAcct->SaveContract();
					pMintCashReserveAcct->SaveAccount();
									
					pResponseItem->SetStatus(OTItem::acknowledgement);
					
					// TODO:  Right here, again, I need to save the receipt from the new balance agreement, since we have
					// "ultimate success".  Also need to save the Nym, since he had a transaction number removed in
					// the above call to VerifyBalanceAgreement. If we failed here, then we wouldn't WANT to save, since
					// that number should stay on him! Same reason we don't save the accounts if anything goes wrong.
				}
			} // the purse loaded successfully from the string
		} // the account ID matches correctly to the acct ID on the item.
		
		
		// sign the response item before sending it back (it's already been added to the transaction above)
		// Now, whether it was rejection or acknowledgement, it is set properly and it is signed, and it
		// is owned by the transaction, who will take it from here.
		pResponseItem->SignContract(m_nymServer);
		pResponseItem->SaveContract(); // the signing was of no effect because I forgot to save.
		
		pResponseBalanceItem->SignContract(m_nymServer);
		pResponseBalanceItem->SaveContract();

		//		OTString strTestInRefTo;
		//		pResponseItem->GetReferenceString(strTestInRefTo);
		//		OTLog::vError("DEBUG: Item in reference to: %s\n", strTestInRefTo.Get());
		
	} // if pItem = tranIn.GetItem(OTItem::deposit)
	else 
	{
		OTLog::Error("Error, expected OTItem::deposit in OTServer::NotarizeDeposit\n");
	}	
}





/// 1) The Payer must generate the Payment Plan. (Using one of his own transaction numbers.) 
/// 2) Then the payer AND payee must sign it.
/// 3) Then the payer must activate the payment plan. (Using a transaction with the same number as the plan.)
///
/// There will be easier ways in the future, but this gets us started.
/// 
void OTServer::NotarizePaymentPlan(OTPseudonym & theNym, OTAccount & theSourceAccount, OTTransaction & tranIn, OTTransaction & tranOut)
{
	// The outgoing transaction is an "atPaymentPlan", that is, "a reply to the paymentPlan request"
	tranOut.SetType(OTTransaction::atPaymentPlan);
	
	OTItem * pItem			= NULL;
	OTItem * pBalanceItem	= NULL;
	OTItem * pResponseItem	= NULL;
	OTItem * pResponseBalanceItem	= NULL;
	
	// The incoming transaction may be sent to inboxes and outboxes, and it
	// will definitely be bundled in our reply to the user as well. Therefore,
	// let's grab it as a string.
	OTString strInReferenceTo;
	OTString strBalanceItem;
	
	// Grab the actual server ID from this object, and use it as the server ID here.
	const OTIdentifier	SERVER_ID(m_strServerID),		SENDER_USER_ID(theNym), 
						SERVER_USER_ID(m_nymServer),	SOURCE_ACCT_ID(theSourceAccount);
	
	
	pItem			= tranIn.GetItem(OTItem::paymentPlan);
	pBalanceItem	= tranIn.GetItem(OTItem::transactionStatement);
	
	pResponseItem = OTItem::CreateItemFromTransaction(tranOut, OTItem::atPaymentPlan);	 
	pResponseItem->SetStatus(OTItem::rejection); // the default.
	tranOut.AddItem(*pResponseItem); // the Transaction's destructor will cleanup the item. It "owns" it now.		
	
	pResponseBalanceItem = OTItem::CreateItemFromTransaction(tranOut, OTItem::atTransactionStatement);	 
	pResponseBalanceItem->SetStatus(OTItem::rejection); // the default.
	tranOut.AddItem(*pResponseBalanceItem); // the Transaction's destructor will cleanup the item. It "owns" it now.		

	// --------------------------------------------------------------------
	
	// For now, there should only be one of these paymentPlan items inside the transaction.
	// So we treat it that way... I either get it successfully or not.
	if (NULL == pItem || NULL == pBalanceItem)
	{
		OTLog::Error("Error, expected OTItem::paymentPlan and OTItem::transactionStatement in OTServer::NotarizePaymentPlan\n");
	}
	else if (SOURCE_ACCT_ID != pItem->GetPurportedAccountID())
	{
		OTLog::Output(0, "Error: Source account ID on the transaction does not match sender's account ID on the transaction item.\n");
	}
	else if (false == pBalanceItem->VerifyTransactionStatement(theNym))
	{
		OTLog::Output(0, "Failed verifying transaction statement in OTServer::NotarizePaymentPlan.\n");
	}
	else
	{
		pResponseBalanceItem->SetStatus(OTItem::acknowledgement); // the transaction agreement was successful.

		// The response item will contain a copy of the request item. So I save it into a string
		// here so it can be saved into the "in reference to" field.
		pItem->SaveContract(strInReferenceTo);
		pBalanceItem->SaveContract(strBalanceItem);
		
		// Server response item being added to server response transaction (tranOut)
		// They're getting SOME sort of response item.
		
		pResponseItem->SetReferenceString(strInReferenceTo); // the response item carries a copy of what it's responding to.
		pResponseItem->SetReferenceToNum(pItem->GetTransactionNum()); // This response item is IN RESPONSE to pItem and its Owner Transaction.
				
		pResponseBalanceItem->SetReferenceString(strBalanceItem); // the response item carries a copy of what it's responding to.
		pResponseBalanceItem->SetReferenceToNum(pItem->GetTransactionNum()); // This response item is IN RESPONSE to pItem and its Owner Transaction.
		
		// Also load up the Payment Plan from inside the transaction item.
		OTString	strPaymentPlan;
		pItem->GetAttachment(strPaymentPlan);
		OTPaymentPlan * pPlan = new OTPaymentPlan();
		OT_ASSERT(NULL != pPlan);
		
		// If we failed to load the plan...
		if ((false == pPlan->LoadContractFromString(strPaymentPlan)))
		{
			OTLog::vError("ERROR loading payment plan from string in OTServer::NotarizePaymentPlan:\n%s\n",
						  strPaymentPlan.Get());
		}
		else if (pPlan->GetTransactionNum() != pItem->GetTransactionNum())
		{
			OTLog::Output(0, "ERROR bad transaction number on payment plan in OTServer::NotarizePaymentPlan\n");			
		}
		else if (!pPlan->VerifySignature(theNym))
		{
			OTLog::Output(0, "ERROR verifying sender signature on Payment Plan in OTServer::NotarizePaymentPlan\n");	
		}
		else if (pPlan->GetServerID() != SERVER_ID)
		{
			OTLog::Output(0, "ERROR bad server ID on payment plan in OTServer::NotarizePaymentPlan\n");
		}
		else if (pPlan->GetSenderUserID() != SENDER_USER_ID)
		{
			OTLog::Output(0, "ERROR wrong user ID on payment plan in OTServer::NotarizePaymentPlan\n");
		}
		else if (pPlan->GetAssetID() != theSourceAccount.GetAssetTypeID())
		{
			OTLog::Output(0, "ERROR wrong Asset Type ID on payment plan in OTServer::NotarizePaymentPlan\n");
		}
		else if (pPlan->GetSenderAcctID() != SOURCE_ACCT_ID)
		{
			OTLog::Output(0, "ERROR wrong Asset Acct ID on payment plan in OTServer::NotarizePaymentPlan\n");
		}
		else  // The plan is good (so far.)
		{
			// The RECIPIENT_ACCT_ID is the ID on the "To" Account. (When doing a transfer, normally 2nd acct is the Payee.)
			const OTIdentifier	RECIPIENT_ACCT_ID(pPlan->GetRecipientAcctID()),
								RECIPIENT_USER_ID(pPlan->GetRecipientUserID());
			
			bool bRecipientNymIsServerNym	= ((RECIPIENT_USER_ID	== SERVER_USER_ID)		? true : false);
			bool bUsersAreSameNym			= ((SENDER_USER_ID		== RECIPIENT_USER_ID)	? true : false);
			
			OTPseudonym		theRecipientNym;		// We'll probably use this, but maybe not. So I use a pointer that will maybe point here.
			OTPseudonym *	pRecipientNym	= NULL;	// Here's the pointer.  (Logic explained directly below.)
						
			// ------------------------------------------------------------------------

			// Set pRecipientNym to point to the right one so we can use it below. (Do NOT use theRecipientNym,
			// since it won't always point to that one.)
			
			bool bFoundRecipientNym = false;
			
			// Find out if Recipient Nym is also the Server Nym...
			if (bRecipientNymIsServerNym)		
			{
				// If the Recipient Nym is the server, then just point to that.
				pRecipientNym		= &m_nymServer;
				bFoundRecipientNym	= true;

				// (No need to verify Nym here since already done in this case.)
			}
			else if (bUsersAreSameNym)	// Else if the participants are the same Nym, point to the one we already loaded. 
			{
				pRecipientNym		= &theNym;
				bFoundRecipientNym	= true;
				
				// (No need to verify Nym here since already done in this case, before we even got here.)
			}
			else	// Otherwise load the Recipient Nym from Disk and point to that.
			{				
				theRecipientNym.SetIdentifier(RECIPIENT_USER_ID);
				
				if (false == theRecipientNym.LoadPublicKey())
				{
					OTString strNymID(RECIPIENT_USER_ID);
					OTLog::vError("Failure loading Recipient Nym public key in OTServer::NotarizePaymentPlan: %s\n", 
								  strNymID.Get());
					bFoundRecipientNym = false;
				}				
				else if (!theRecipientNym.VerifyPseudonym()	|| !theRecipientNym.LoadSignedNymfile(m_nymServer))
				{
					OTString strNymID(RECIPIENT_USER_ID);
					OTLog::vError("Failure loading or verifying Recipient Nym public key in OTServer::NotarizePaymentPlan: %s\n", 
								  strNymID.Get());
					bFoundRecipientNym = false;
				}
				else
				{
					pRecipientNym = &theRecipientNym; //  <=====
					bFoundRecipientNym = true;
				}
			}
			
			// Below this point, ALWAYS use pRecipientNym, NOT theRecipientNym.
			// pRecipientNym is always guaranteed below here to point to the right one.
			
			
			// ------------------------------------------------------------------------
			
			
			if (!bFoundRecipientNym || (NULL == pRecipientNym))
			{
				// (No need to log here; already logged right above.)
				// OTLog::Output("Unable to load or verify Recipient Nym in OTServer::NotarizePaymentPlan()");
			}
			
			// Below this point, we know for sure that the Recipient Nym is loaded and verified, and we know
			// that if the Server or Sender is actually the Recipient, that the pRecipientNym pointer will
			// always point to the right one, and no files can be overwritten. *phew*

			
			// You CAN have both accounts owned by the same Nym, but you CANNOT have them both actually be the SAME ACCT.
			else if (SOURCE_ACCT_ID == RECIPIENT_ACCT_ID)
			{
				OTLog::Output(0, "Error: Source account ID matches Recipient account ID on attempted Payment Plan notarization.\n");
			}
			else if (!pPlan->VerifySignature(*pRecipientNym)) // BOTH parties must be signers to a payment plan.
			{
				OTLog::Output(0, "ERROR verifying Recipient's signature on Payment Plan.\n");	
			}		
			else	// -----------------------------------------------------------------
			{
				// Load up the recipient ACCOUNT and validate it.
				OTAccount * pRecipientAcct = OTAccount::LoadExistingAccount(RECIPIENT_ACCT_ID, SERVER_ID);
				OTCleanup<OTAccount> theRecipientAcctGuardian(pRecipientAcct); // This will cleanup pRecipAcct, or do nothing if it's NULL.

				if (NULL == pRecipientAcct)
				{
					OTLog::Output(0, "ERROR loading Recipient account in OTServer::NotarizePaymentPlan\n");
				}
				else if (!pRecipientAcct->VerifyOwner(*pRecipientNym))
				{
					OTLog::Output(0, "ERROR verifying ownership of the recipient account in OTServer::NotarizePaymentPlan\n");
				}
				// Are both of the accounts of the same Asset Type?
				else if (pRecipientAcct->GetAssetTypeID() != theSourceAccount.GetAssetTypeID())
				{
					OTString	strSourceAssetID(theSourceAccount.GetAssetTypeID()), 
								strRecipAssetID(pRecipientAcct->GetAssetTypeID());
					OTLog::vOutput(0, "ERROR - user attempted to make a payment plan between dissimilar "
								   "asset types in OTServer::NotarizePaymentPlan:\n%s\n%s\n", 
								   strSourceAssetID.Get(),
								   strRecipAssetID.Get());
				}
				// Does it verify?
				// I call VerifySignature here since VerifyContractID was already called in LoadExistingAccount().
				else if (!pRecipientAcct->VerifySignature(m_nymServer))
				{
					OTLog::Output(0, "ERROR verifying signature on the Recipient account in OTServer::NotarizePaymentPlan\n");
				}
				// This one is superfluous, but I'm leaving it. (pPlan and pRecip are both already 
				// matches to a 3rd value: source acct asset type ID.)
				else if (pRecipientAcct->GetAssetTypeID() != pPlan->GetAssetID()) 
				{
					OTLog::Output(0, "ERROR wrong Asset Type ID on Recipient Acct in OTServer::NotarizePaymentPlan\n");
				}
				
				// At this point I feel pretty confident that the Payment Plan is a valid request from both parties.
				// I have both users AND both accounts and validated against the Payment Plan, signatures and all.
				
				else 
				{
					// We add the payment plan to the server's Cron object, which does regular processing.
					// That object will take care of processing the payment plan according to its terms.
					//
					// NOTE: FYI, inside AddCronItem, since this is a new CronItem, a Cron Receipt will
					// be saved with the User's signature on it, containing the Cron Item from the user's
					// original request. After that, the item is stored internally to Cron itself, and
					// signed by the server--and changes over time as cron processes. (The original receipt
					// can always be loaded when necessary.)
					if (m_Cron.AddCronItem(*pPlan, true)) // bSaveReceipt=true
					{//todo need to be able to "roll back" if anything inside this block fails.
						// Now we can set the response item as an acknowledgement instead of the default (rejection)
						pResponseItem->SetStatus(OTItem::acknowledgement);
						OTLog::Output(2, "Successfully added payment plan to Cron object.\n");
						
						// TODO: ULTIMATE SUCCESS HERE -- Need to save the transaction agreement receipt (pBalanceItem).
						// At least we're VERIFYING it! that's a good first step. Next we need to save it.
						
					}
					else 
					{
						OTLog::Output(0, "Unable to add payment plan to Cron object OTServer::NotarizePaymentPlan\n");
					}
				}
			} // If recipient Nym successfully loaded from storage.	
		} // If Payment Plan successfully loaded from Transaction Item.
		
		// If the payment plan WAS successfully added to Cron, then we don't need to
		// delete it here, since Cron owns it now, and will deal with cleaning
		// it up at the right time. (So I can't use OTCleanup on pPlan.)
		if ((NULL != pPlan) && (pResponseItem->GetStatus() != OTItem::acknowledgement))
		{
			delete pPlan;
			pPlan = NULL;
		}
		
		// sign the response item before sending it back (it's already been added to the transaction above)
		// Now, whether it was rejection or acknowledgement, it is set properly and it is signed, and it
		// is owned by the transaction, who will take it from here.
		pResponseItem->SignContract(m_nymServer);
		pResponseItem->SaveContract(); // the signing was of no effect because I forgot to save.
		
		pResponseBalanceItem->SignContract(m_nymServer);
		pResponseBalanceItem->SaveContract();
	} // if pItem = tranIn.GetItem(OTItem::paymentPlan)
}







void OTServer::NotarizeMarketOffer(OTPseudonym & theNym, OTAccount & theAssetAccount, OTTransaction & tranIn, OTTransaction & tranOut)
{
	// The outgoing transaction is an "atMarketOffer", that is, "a reply to the marketOffer request"
	tranOut.SetType(OTTransaction::atMarketOffer);
	
	OTItem * pItem			= NULL;
	OTItem * pBalanceItem	= NULL;
	OTItem * pResponseItem	= NULL;
	OTItem * pResponseBalanceItem	= NULL;
	
	// The incoming transaction may be sent to inboxes and outboxes, and it
	// will definitely be bundled in our reply to the user as well. Therefore,
	// let's grab it as a string.
	OTString strInReferenceTo;
	OTString strBalanceItem;

	// Grab the actual server ID from this object, and use it as the server ID here.
	const OTIdentifier SERVER_ID(m_strServerID), USER_ID(theNym), SERVER_USER_ID(m_nymServer);
	
	// For now, there should only be one of these marketOffer items inside the transaction.
	// So we treat it that way... I either get it successfully or not.
	if ((pItem = tranIn.GetItem(OTItem::marketOffer)) &&
		(pBalanceItem = tranIn.GetItem(OTItem::transactionStatement)))
	{
		// The response item will contain a copy of the request item. So I save it into a string
		// here so it can be saved into the "in reference to" field.
		pItem->SaveContract(strInReferenceTo);
		pBalanceItem->SaveContract(strBalanceItem);
		
		// ASSET_ACCT_ID is the ID on the "from" Account that was passed in.
		// The CURRENCY_ACCT_ID is the ID on the "To" Account. (When doing a transfer, normally 2nd acct is the Payee.)
		const OTIdentifier ASSET_ACCT_ID(theAssetAccount), CURRENCY_ACCT_ID(pItem->GetDestinationAcctID());
		
		// Server response item being added to server response transaction (tranOut)
		// They're getting SOME sort of response item.
		
		pResponseItem = OTItem::CreateItemFromTransaction(tranOut, OTItem::atMarketOffer);	 
		pResponseItem->SetStatus(OTItem::rejection); // the default.
		pResponseItem->SetReferenceString(strInReferenceTo); // the response item carries a copy of what it's responding to.
		pResponseItem->SetReferenceToNum(pItem->GetTransactionNum()); // This response item is IN RESPONSE to pItem and its Owner Transaction.
		tranOut.AddItem(*pResponseItem); // the Transaction's destructor will cleanup the item. It "owns" it now.		
		
		pResponseBalanceItem = OTItem::CreateItemFromTransaction(tranOut, OTItem::atTransactionStatement);	 
		pResponseBalanceItem->SetStatus(OTItem::rejection); // the default.
		pResponseBalanceItem->SetReferenceString(strBalanceItem); // the response item carries a copy of what it's responding to.
		pResponseBalanceItem->SetReferenceToNum(pItem->GetTransactionNum()); // This response item is IN RESPONSE to pItem and its Owner Transaction.
		tranOut.AddItem(*pResponseBalanceItem); // the Transaction's destructor will cleanup the item. It "owns" it now.		
		
		if (false == (pBalanceItem->VerifyTransactionStatement(theNym)))
		{
			OTLog::vOutput(0, "ERROR verifying transaction statement.\n");
		}		
		else 
		{
			pResponseBalanceItem->SetStatus(OTItem::acknowledgement); // the transaction agreement was successful.
			
			// Load up the currency account and validate it.
			OTAccount * pCurrencyAcct = OTAccount::LoadExistingAccount(CURRENCY_ACCT_ID, SERVER_ID);
			OTCleanup<OTAccount> theCurrencyAcctGuardian(pCurrencyAcct); // Now I don't have to worry about deleting pCurrencyAcct.
			
			// Also load up the Trade from inside the transaction item.
			OTString	strOffer;
			OTOffer		theOffer;
			
			OTString	strTrade;
			pItem->GetAttachment(strTrade);
			
			OTTrade * pTrade = new OTTrade();
			
			OT_ASSERT(NULL != pTrade);
			
			// First load the Trade up (from the string that was passed in on the transaction item.)
			bool bLoadContractFromString = pTrade->LoadContractFromString(strTrade);
			
			// If failed to load the trade...
			if (!bLoadContractFromString)
			{
				OTLog::vError("ERROR loading trade from string in OTServer::NotarizeMarketOffer:\n%s\n",
							  strTrade.Get());
			}			
			// I'm using the operator== because it exists. (Although now I believe != exists also)
			// If the ID on the "from" account that was passed in,
			// does not match the "Acct From" ID on this transaction item
			else if (!(ASSET_ACCT_ID == pItem->GetPurportedAccountID()))
			{
				OTLog::Output(0, "Error: Asset account ID on the transaction does not match asset account ID on the transaction item.\n");
			} 
			// ok so the IDs match. Does the currency account exist? 
			else if (NULL == pCurrencyAcct)
			{
				OTLog::Output(0, "ERROR verifying existence of the currency account in OTServer::NotarizeMarketOffer\n");
			}
			else if (!pCurrencyAcct->VerifyContractID())
			{
				OTLog::Output(0, "ERROR verifying Contract ID on the currency account in OTServer::NotarizeMarketOffer\n");	
			}
			else if (!pCurrencyAcct->VerifyOwner(theNym))
			{
				OTLog::Output(0, "ERROR verifying ownership of the currency account in OTServer::NotarizeMarketOffer\n");
			}
			// Are both of the accounts of the same Asset Type?
			else if (theAssetAccount.GetAssetTypeID() == pCurrencyAcct->GetAssetTypeID())
			{
				OTString	strAssetTypeID(theAssetAccount.GetAssetTypeID()), 
				strCurrencyTypeID(pCurrencyAcct->GetAssetTypeID());
				OTLog::vOutput(0, "ERROR - user attempted to trade between identical "
							   "asset types in OTServer::NotarizeMarketOffer:\n%s\n%s\n", 
							   strAssetTypeID.Get(),
							   strCurrencyTypeID.Get());
			}
			// Does it verify?
			// I call VerifySignature here since VerifyContractID was already called in LoadExistingAccount().
			else if (!pCurrencyAcct->VerifySignature(m_nymServer))
			{
				OTLog::Output(0, "ERROR verifying signature on the Currency account in OTServer::NotarizeMarketOffer\n");
			}
			else if (!pTrade->VerifySignature(theNym))
			{
				OTLog::Output(0, "ERROR verifying signature on the Trade in OTServer::NotarizeMarketOffer\n");	
			}
			else if (pTrade->GetTransactionNum() != pItem->GetTransactionNum())
			{
				OTLog::Output(0, "ERROR bad transaction number on trade in OTServer::NotarizeMarketOffer\n");			
			}
			else if (pTrade->GetServerID() !=	SERVER_ID)
			{
				OTLog::Output(0, "ERROR bad server ID on Trade in OTServer::NotarizeMarketOffer\n");
			}
			else if (pTrade->GetSenderUserID() != USER_ID)
			{
				OTLog::Output(0, "ERROR wrong user ID on Trade in OTServer::NotarizeMarketOffer\n");
			}
			else if (pTrade->GetAssetID() != theAssetAccount.GetAssetTypeID())
			{
				OTLog::Output(0, "ERROR wrong Asset Type ID on Trade in OTServer::NotarizeMarketOffer\n");
			}
			else if (pTrade->GetSenderAcctID() != ASSET_ACCT_ID)
			{
				OTLog::Output(0, "ERROR wrong Asset Acct ID on Trade in OTServer::NotarizeMarketOffer\n");
			}
			else if (pTrade->GetCurrencyID() != pCurrencyAcct->GetAssetTypeID())
			{
				OTLog::Output(0, "ERROR wrong Currency Type ID OTServer::NotarizeMarketOffer\n");
			}
			else if (pTrade->GetCurrencyAcctID() != CURRENCY_ACCT_ID)
			{
				OTLog::Output(0, "ERROR wrong Currency Acct ID on Trade in OTServer::NotarizeMarketOffer\n");	
			}
			// If the Trade successfully verified, but I couldn't get the offer out of it, then it
			// actually DIDN'T successfully load still.  :-(
			else if (!pTrade->GetOfferString(strOffer))
			{
				OTLog::vError("ERROR getting offer string in OTServer::NotarizeMarketOffer:\n%s\n",
							  strTrade.Get());
			}
			else if (!theOffer.LoadContractFromString(strOffer))
			{
				OTLog::vError("ERROR loading offer from string in OTServer::NotarizeMarketOffer:\n%s\n",
							  strTrade.Get());
			}
			// ...And then we use that same Nym to verify the signature on the offer.
			else if (!theOffer.VerifySignature(theNym))
			{
				OTLog::Error("ERROR verifying Offer signature in OTServer::NotarizeMarketOffer.\n");
			}
			else if (!pTrade->VerifyOffer(theOffer))
			{
				OTLog::Output(0, "ERROR verifying Offer for Trade in OTServer::NotarizeMarketOffer\n");	
			}
			// At this point I feel pretty confident that the Trade is a valid request from the user.
			
			
			
			// The top half of this function is oriented around finding the "marketOffer" item (in the "marketOffer"
			// transaction) and setting up the response item that will go into the response transaction. It also
			// retrieves the Trade object and fully validates it.
			// 
			// Next all we need to do is add it to the market...
			
			
			else 
			{
				// We don't actually add the trade to a market here. Instead, we add it to the server's Cron object.
				// That object will take care of processing the offer on and off of any market.
				//
				// NOTE: FYI, inside AddCronItem, since this is a new CronItem, a Cron Receipt will
				// be saved with the User's signature on it, containing the Cron Item from the user's
				// original request. After that, the item is stored internally to Cron itself, and
				// signed by the server--and changes over time as cron processes. (The original receipt
				// can always be loaded when necessary.)
				if (m_Cron.AddCronItem(*pTrade, true)) // bSaveReceipt=true
				{//todo need to be able to "roll back" if anything inside this block fails.
					
					// Now we can set the response item as an acknowledgement instead of the default (rejection)
					pResponseItem->SetStatus(OTItem::acknowledgement);
					OTLog::Output(2, "Successfully added Trade to Cron object.\n");
					
					//ULTIMATE SUCCESS -- ToDO: Need to remove issued number for real, and save Nym, since
					// the Verify transaction statement call currently removes it and doesn't re-add if success.
					
				}
				else 
				{
					OTLog::Output(0, "Unable to add trade to Cron object OTServer::NotarizeMarketOffer\n");
				}
			}
			
			// If the trade WAS successfully added to Cron, then we don't need to
			// delete it here, since Cron owns it now, and will deal with cleaning
			// it up at the right time.
			if ((NULL != pTrade) && pResponseItem->GetStatus() != OTItem::acknowledgement)
			{
				delete pTrade;
				pTrade = NULL;
			}
			
			
			// sign the response item before sending it back (it's already been added to the transaction above)
			// Now, whether it was rejection or acknowledgement, it is set properly and it is signed, and it
			// is owned by the transaction, who will take it from here.
			pResponseItem->SignContract(m_nymServer);
			pResponseItem->SaveContract(); // the signing was of no effect because I forgot to save.
			
			pResponseBalanceItem->SignContract(m_nymServer);
			pResponseBalanceItem->SaveContract();
		} // transaction statement verified.

	} // if pItem = tranIn.GetItem(OTItem::marketOffer)
	else {
		OTLog::Error("Error, expected OTItem::marketOffer in OTServer::NotarizeMarketOffer\n");
	}
}






/// If the server receives a notarizeTransactions command, it will be accompanied by a payload
/// containing a ledger to be notarized.  UserCmdNotarizeTransactions will loop through that ledger,
/// and for each transaction within, it calls THIS method.
/// TODO think about error reporting here and sending a message back to user.
void OTServer::NotarizeTransaction(OTPseudonym & theNym, OTTransaction & tranIn, OTTransaction & tranOut)
{
	bool bSuccess = false;
	
	const	long			lTransactionNumber = tranIn.GetTransactionNum();
	const	OTIdentifier	SERVER_ID(m_strServerID), SERVER_USER_ID(m_strServerUserID);
			OTIdentifier	USER_ID;
	theNym.GetIdentifier(	USER_ID);

	OTAccount theFromAccount(USER_ID, tranIn.GetPurportedAccountID(), SERVER_ID);
	
	// Make sure the "from" account even exists...
	if (!theFromAccount.LoadContract())
	{
		OTLog::vOutput(0, "Error loading 'from' account in OTServer::NotarizeTransaction\n");
	}
	// Make sure the Account ID loaded from the file matches the one we just set and used as the filename.
	else if (!theFromAccount.VerifyContractID())
	{
		// this should never happen. How did the wrong ID get into the account file, if the right
		// ID is on the filename itself? and vice versa.
		OTLog::Error("Error verifying account ID in OTServer::NotarizeTransaction\n");
	}
	// Make sure the nymID loaded up in the account as its actual owner matches the nym who was
	// passed in to this function requesting a transaction on this account... otherwise any asshole
	// could do transactions on your account, no?
	else if (!theFromAccount.VerifyOwner(theNym))
	{
		OTLog::vOutput(0, "Error verifying account ownership in OTServer::NotarizeTransaction\n");		
	}
	// Make sure I, the server, have signed this file.
	else if (!theFromAccount.VerifySignature(m_nymServer))
	{
		OTLog::Error("Error verifying server signature on account in OTServer::NotarizeTransaction\n");
	}
	// No need to call VerifyAccount() here since the above calls go above and beyond that method.
	
	else if (!VerifyTransactionNumber(theNym, lTransactionNumber))
	{
		// The user may not submit a transaction using a number he's already used before.
		OTLog::Output(0, "Error verifying transaction number on user nym in OTServer::NotarizeTransaction\n");
	}
	
	// The items' acct and server ID were already checked in VerifyContractID() when they were loaded. 
	// Now this checks a little deeper, to verify ownership, signatures, and transaction number
	// on each item.  That way those things don't have to be checked for security over and over
	// again in the subsequent calls.
	//
	else if (!tranIn.VerifyItems(theNym)) 
	{
		OTLog::Output(0, "Error verifying transaction items OTServer::NotarizeTransaction\n");
	}
	
	// any other security stuff?
	// Todo do I need to verify the server ID here as well?
	else
	{
		// We don't want any transaction number being used twice.
		// (The number, at this point, is STILL issued to the user, who is still responsible
		// for that number and must continue signing for it. All this means here is that the
		// user no longer has the number on his AVAILABLE list. Removal from issued list happens separately.)
		//
		if (false == RemoveTransactionNumber(theNym, lTransactionNumber, true)) //bSave=true
		{
			OTLog::Error("Error removing transaction number (as available) from user nym in OTServer::NotarizeTransaction\n");
		}			
		
		// -------------------------------------------------------------------
		
		else 
		{
			OTItem::itemType theReplyItemType = OTItem::error_state;
			
			switch (tranIn.GetType()) 
			{
					// TRANSFER (account to account)
					// Alice sends a signed request to the server asking it to
					// transfer from her account ABC to the inbox of account DEF.
					// A copy will also remain in her outbox until canceled or accepted.
				case OTTransaction::transfer:
					OTLog::Output(0, "NotarizeTransaction type: Transfer\n");
					NotarizeTransfer(theNym, theFromAccount, tranIn, tranOut);
					bSuccess = true;
					theReplyItemType = OTItem::atTransfer;
					break;
					
					// PROCESS INBOX (currently, all incoming transfers must be accepted.)
					// Bob sends a signed request to the server asking it to reject
					// some of his inbox items and/or accept some into his account DEF.
				case OTTransaction::processInbox:
					OTLog::Output(0, "NotarizeTransaction type: Process Inbox\n");
					NotarizeProcessInbox(theNym, theFromAccount, tranIn, tranOut);	
					bSuccess = true;
//					theReplyItemType = OTItem::atProcessInbox; // Nonexistent, and here, unused.
					break;
					
					// WITHDRAWAL (cash or voucher)	
					// Alice sends a signed request to the server asking it to debit her
					// account ABC and then issue her a purse full of blinded cash tokens
					// --OR-- a voucher (a cashier's cheque, made out to any recipient's 
					// User ID, or made out to a blank recipient, just like a blank cheque.)
				case OTTransaction::withdrawal:
					OTLog::Output(0, "NotarizeTransaction type: Withdrawal\n");
					NotarizeWithdrawal(theNym, theFromAccount, tranIn, tranOut);
					bSuccess = true;
					theReplyItemType = OTItem::atWithdrawal;
					break;
					
					// DEPOSIT	(cash or cheque)
					// Bob sends a signed request to the server asking it to deposit into his
					// account ABC. He includes with his request a signed cheque made out to
					// Bob's user ID (or blank), --OR-- a purse full of tokens.
				case OTTransaction::deposit:
					OTLog::Output(0, "NotarizeTransaction type: Deposit\n");
					NotarizeDeposit(theNym, theFromAccount, tranIn, tranOut);
					bSuccess = true;
					theReplyItemType = OTItem::atDeposit;
					break;
					
					// MARKET OFFER
					// Bob sends a signed request to the server asking it to put an offer
					// on the market. He includes with his request a signed trade listing
					// the relevant information, asset types and account IDs.
				case OTTransaction::marketOffer:
					OTLog::Output(0, "NotarizeTransaction type: Market Offer\n");
					NotarizeMarketOffer(theNym, theFromAccount, tranIn, tranOut);
					bSuccess = true;
					theReplyItemType = OTItem::atMarketOffer;
					break;
					
					// PAYMENT PLAN
					// Bob sends a signed request to the server asking it to make regular
					// payments to Alice. (BOTH Alice AND Bob must have signed the same contract.)
				case OTTransaction::paymentPlan:
					OTLog::Output(0, "NotarizeTransaction type: Payment Plan\n");
					NotarizePaymentPlan(theNym, theFromAccount, tranIn, tranOut);
					bSuccess = true;
					theReplyItemType = OTItem::atPaymentPlan;
					break;
					
				default:
					OTLog::vError("OTServer::NotarizeTransaction: Error, unexpected type: %s\n", tranIn.GetTypeString());	
					break;
			}
			
			// ------------------------------------------
			
			// Where appropriate, remove a transaction number from my issued list 
			// (the list of numbers I must sign for in every balance agreement.)
			
			switch (tranIn.GetType()) 
			{
				case OTTransaction::transfer:
				case OTTransaction::marketOffer:
				case OTTransaction::paymentPlan:
					// If success, then Issued number stays on Nym's issued list until the transfer, paymentPlan or marketOffer 
					//  is entirely closed and removed. In the case of transfer, that's when the transfer receipt is accepted.
					//  In the case of markets and paymentplans, that's when they've been entirely removed from Cron (many 
					//  intermediary receipts might occur before that happens.)
					//
					// But if failure, then Issued number is immediately removed. 
					// (It already can't be used again, and there's no receipt to clear later, thus no reason to save it...)
				{
					OTItem * pItem	= tranOut.GetItem(theReplyItemType);
					
					if ((NULL != pItem))
					{
						if (OTItem::rejection == pItem->GetStatus())
						{
							if (false == RemoveIssuedNumber(theNym, lTransactionNumber, true)) //bSave=true
							{
								OTLog::Error("Error removing issued number from user nym in OTServer::NotarizeTransaction\n");
							}
						}
					}
				}
					break;

				case OTTransaction::processInbox:
				case OTTransaction::withdrawal:
				case OTTransaction::deposit:
					if (false == RemoveIssuedNumber(theNym, lTransactionNumber, true)) //bSave=true
					{
						OTLog::Error("Error removing issued number from user nym in OTServer::NotarizeTransaction\n");
					}			
					break;

				default:
					OTLog::vError("OTServer::NotarizeTransaction: Error, unexpected type: %s\n", tranIn.GetTypeString());	
					break;
			}
		}

		// Add a new transaction number item to each outgoing transaction.
		// So that the client can use it with his next request. Might as well
		// send it now, otherwise the client will have to request one later
		// before his next request.
		//
		// UPDATE: We NO LONGER send a transaction number here. Instead, the
		// user MUST request it, and we MUST drop it into his Nymbox, and he
		// MUST retrieve it from there by processing his nymbox (and therefore
		// SIGNING for it, via a transactionStatement.)
		//
		// This is what makes it possible for both sides to prove balances
		// without having to store a transaction history (as long as they do
		// save the last receipt.)
		//
//		long lTransactionNum = 0;
//		
//		// This call to IssueNextTransactionNumber will save the new transaction
//		// number to the nym's file on the server side. 
//		if (bSuccess
//			&& IssueNextTransactionNumber(theNym, lTransactionNum)
//			)
//		{
//			// But we still have to bundle it into the message and send it, so
//			// it can also be saved into the same nym's file on the client side.
//			OTPseudonym theMessageNym;
//			theMessageNym.AddTransactionNum(m_strServerID, lTransactionNum); // This version of AddTransactionNum doesn't bother saving to file. No need here...
//			
//			OTString	strMessageNym(theMessageNym);
//			
//			OTItem * pItem	= OTItem::CreateItemFromTransaction(tranOut, OTItem::atTransaction);
//			
//			if (pItem)
//			{
//				pItem->SetStatus(OTItem::acknowledgement);
//				pItem->SetAttachment(strMessageNym);
//				pItem->SignContract(m_nymServer);
//				pItem->SaveContract(); // the signing was of no effect because I forgot to save.
//				tranOut.AddItem(*pItem); // the Transaction's destructor will cleanup the item. It "owns" it now.		
//			}
//		}
	}

	// sign the outoing transaction
	tranOut.SignContract(m_nymServer);	
	tranOut.SaveContract();	 // don't forget to save (to internal raw file member)
	
	// Contracts store an internal member that contains the "Raw File" contents
	// That is, the unsigned XML portion, plus the signatures, attached in a standard
	// PGP-compatible format. It's not enough to sign it, you must also save it into
	// that Raw file member variable (using SaveContract) and then you must sometimes
	// THEN save it into a file (or a string or wherever you want to put it.)
}


/// There will be more code here to handle all that. In the meantime, I just send
/// a test response back to make sure the communication works.
///
/// An existing user is sending a list of transactions to be notarized.
void OTServer::UserCmdNotarizeTransactions(OTPseudonym & theNym, OTMessage & MsgIn, OTMessage & msgOut)
{
	// (1) set up member variables 
	msgOut.m_strCommand		= "@notarizeTransactions";	// reply to notarizeTransactions
	msgOut.m_strNymID		= MsgIn.m_strNymID;	// UserID
	msgOut.m_strServerID	= m_strServerID;	// ServerID, a hash of the server contract.
	msgOut.m_strAcctID		= MsgIn.m_strAcctID;	// The Account ID in question
	
	const OTIdentifier	USER_ID(MsgIn.m_strNymID), ACCOUNT_ID(MsgIn.m_strAcctID), SERVER_ID(m_strServerID),
						SERVER_USER_ID(m_nymServer);
	
	OTLedger theLedger(USER_ID, ACCOUNT_ID, SERVER_ID);			// These are ledgers used as messages. The one we received and the one 
																// that we're sending back in response.
	OTLedger * pResponseLedger = OTLedger::GenerateLedger(SERVER_USER_ID, ACCOUNT_ID, SERVER_ID, OTLedger::message, false);
	
	OTCleanup<OTLedger> theRespLedgerGuardian(pResponseLedger); // So I don't have to worry about cleaning it up.
	
	// Since the one going back (above) is a new ledger, we have to call GenerateLedger.
	// Whereas the ledger we received from the server was generated there, so we don't
	// have to generate it again. We just load it.
	
	OTString strLedger(MsgIn.m_ascPayload);
	
	// as long as the request ledger loads from the message into memory, success is true
	// from there, the success or failure of the transactions within will be carried in
	// their own status variables and those of the items inside those transactions.
	if (msgOut.m_bSuccess = theLedger.LoadContractFromString(strLedger))
	{
		// In this case we need to process the ledger items
		// and create a corresponding ledger where each of the new items
		// contains the answer to the ledger item sent.
		// Then we send that new "response ledger" back to the user in MsgOut.Payload.
		// That is all done here. Until I write that, in the meantime,
		// let's just fprintf it out and see what it looks like.
		//		OTLog::Error("Loaded ledger out of message payload:\n%s\n", strLedger.Get());
//		OTLog::Error("Loaded ledger out of message payload.\n");
 		
		// TODO: Loop through ledger transactions, and do a "NotarizeTransaction" call for each one.
		// Inside that function it will do the various necessary authentication and processing, not this one.
		
		OTTransaction * pTransaction	= NULL;
		OTTransaction * pTranResponse	= NULL;
		
		for (mapOfTransactions::iterator ii = theLedger.GetTransactionMap().begin(); 
			 ii != theLedger.GetTransactionMap().end(); ++ii)
		{	
			// for each transaction in the ledger, we create a transaction response and add
			// that to the response ledger.
			if (pTransaction = (*ii).second)
			{
				
				// I don't call IssueNextTransactionNumber here because I'm not creating a new transaction
				// in someone's inbox or outbox. Instead, I'm making a transaction response to a transaction
				// request, with a MATCHING transaction number (so don't need to issue a new one) to be sent
				// back to the client in a message.
				//
				// On this new "response transaction", I set the ACCT ID, the serverID, and Transaction Number.
				pTranResponse = OTTransaction::GenerateTransaction(*pResponseLedger, OTTransaction::error_state, pTransaction->GetTransactionNum());
				// Add the response transaction to the response ledger.
				// That will go into the response message and be sent back to the client.
				pResponseLedger->AddTransaction(*pTranResponse);
				
				// Now let's make sure the response transaction has a copy of the transaction
				// it is responding to.
				//				OTString strResponseTo;
				//				pTransaction->SaveContract(strResponseTo);
				//				pTranResponse->m_ascInReferenceTo.SetString(strResponseTo);
				// I commented out the above because we are keeping too many copies.
				// Message contains a copy of the message it's responding to.
				// Then each transaction contains a copy of the transaction responding to...
				// Then each ITEM in each transaction contains a copy of each item it's responding to.
				//
				// Therefore, for the "notarizeTransactions" message, I have decided (for now) to have
				// the extra copy in the items themselves, and in the overall message, but not in the
				// transactions. Thus, the above is commented out.
				
				
				// It should always return something. Success, or failure, that goes into pTranResponse.
				// I don't think there's need for more return value than that. The user has gotten deep 
				// enough that they deserve SOME sort of response.
				//
				// This function also SIGNS the transaction, so there is no need to sign it after this.
				// There's also no point to change it after this, unless you plan to sign it twice.
				NotarizeTransaction(theNym, *pTransaction, *pTranResponse);
				
				pTranResponse = NULL; // at this point, the ledger now "owns" the response, and will handle deleting it.
			}
			else 
			{
				OTLog::Error("NULL transaction pointer in OTServer::UserCmdNotarizeTransactions\n");
			}		
		}
		
		// TODO: should consider saving a copy of the response ledger here on the server. 
		// Until the user signs off of the responses, maybe the user didn't receive them.
		// The server should be able to re-send them until confirmation, then delete them.
		// So might want to consider a SAVE TO FILE here of that ledger we're sending out...
		
		// sign the ledger
		pResponseLedger->SignContract(m_nymServer);
		pResponseLedger->SaveContract();
		
		// extract the ledger in ascii-armored form
		OTString strPayload(*pResponseLedger);
		
		msgOut.m_ascPayload.SetString(strPayload);  // now the outgoing message has the response ledger in its payload.
	}
	else 
	{
		OTLog::Error("ERROR loading ledger from message in OTServer::UserCmdNotarizeTransactions\n");
	}
	
	
	// todo: consider commenting this out since the transaction reply items already include a copy
	// of the original client communication that the server is responding to. No point beating a
	// dead horse.
	//
	// Send the user's command back to him as well.
	{
		OTString tempInMessage(MsgIn);
		msgOut.m_ascInReferenceTo.SetString(tempInMessage);
	}
	
	// (2) Sign the Message 
	msgOut.SignContract(m_nymServer);		
	
	// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
	//
	// FYI, SaveContract takes m_xmlUnsigned and wraps it with the signatures and ------- BEGIN  bookends
	// If you don't pass a string in, then SaveContract saves the new version to its member, m_strRawFile
	msgOut.SaveContract();
}



void OTServer::UserCmdGetAccount(OTPseudonym & theNym, OTMessage & MsgIn, OTMessage & msgOut)
{
	// (1) set up member variables 
	msgOut.m_strCommand		= "@getAccount";	// reply to getAccount
	msgOut.m_strNymID		= MsgIn.m_strNymID;	// UserID
	msgOut.m_strServerID	= m_strServerID;	// ServerID, a hash of the server contract.
	msgOut.m_strAcctID		= MsgIn.m_strAcctID;	// The Account ID in question
	
	const OTIdentifier USER_ID(MsgIn.m_strNymID), ACCOUNT_ID(MsgIn.m_strAcctID), SERVER_ID(MsgIn.m_strServerID);
	
	OTAccount * pAccount		= OTAccount::LoadExistingAccount(ACCOUNT_ID, SERVER_ID);
	bool bSuccessLoadingAccount = ((pAccount != NULL) ? true:false );
	
	// Yup the account exists. Yup it has the same user ID.
	if (bSuccessLoadingAccount && (pAccount->GetUserID() == USER_ID))
	{
		msgOut.m_bSuccess = true;
		// extract the account in ascii-armored form on the outgoing message
		OTString strPayload(*pAccount); // first grab it in plaintext string form
		msgOut.m_ascPayload.SetString(strPayload);  // now the outgoing message has the inbox ledger in its payload in base64 form.
	}
	// Send the user's command back to him if failure.
	else
	{
		msgOut.m_bSuccess = false;
		OTString tempInMessage(MsgIn); // Grab the incoming message in plaintext form
		msgOut.m_ascInReferenceTo.SetString(tempInMessage); // Set it into the base64-encoded object on the outgoing message
	}
	
	// (2) Sign the Message 
	msgOut.SignContract((const OTPseudonym &)m_nymServer);
	
	// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
	//
	// FYI, SaveContract takes m_xmlUnsigned and wraps it with the signatures and ------- BEGIN  bookends
	// If you don't pass a string in, then SaveContract saves the new version to its member, m_strRawFile
	msgOut.SaveContract();
}



void OTServer::UserCmdGetContract(OTPseudonym & theNym, OTMessage & MsgIn, OTMessage & msgOut)
{
	// (1) set up member variables 
	msgOut.m_strCommand		= "@getContract";	// reply to getContract
	msgOut.m_strNymID		= MsgIn.m_strNymID;	// UserID
	msgOut.m_strServerID	= m_strServerID;	// ServerID, a hash of the server contract.
	msgOut.m_strAssetID		= MsgIn.m_strAssetID;	// The Asset Type ID in question
	
	const OTIdentifier ASSET_TYPE_ID(MsgIn.m_strAssetID);
	
	OTAssetContract * pContract	= GetAssetContract(ASSET_TYPE_ID);
	
	bool bSuccessLoadingContract = ((pContract != NULL) ? true:false );
	
	// Yup the asset contract exists.
	if (bSuccessLoadingContract)
	{
		msgOut.m_bSuccess = true;
		// extract the account in ascii-armored form on the outgoing message
		OTString strPayload(*pContract); // first grab it in plaintext string form
		msgOut.m_ascPayload.SetString(strPayload);  // now the outgoing message has the inbox ledger in its payload in base64 form.
	}
	// Send the user's command back to him if failure.
	else
	{
		msgOut.m_bSuccess = false;
		OTString tempInMessage(MsgIn); // Grab the incoming message in plaintext form
		msgOut.m_ascInReferenceTo.SetString(tempInMessage); // Set it into the base64-encoded object on the outgoing message
	}
	
	// (2) Sign the Message 
	msgOut.SignContract((const OTPseudonym &)m_nymServer);
	
	// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
	//
	// FYI, SaveContract takes m_xmlUnsigned and wraps it with the signatures and ------- BEGIN  bookends
	// If you don't pass a string in, then SaveContract saves the new version to its member, m_strRawFile
	msgOut.SaveContract();
}



void OTServer::UserCmdGetMint(OTPseudonym & theNym, OTMessage & MsgIn, OTMessage & msgOut)
{
	// (1) set up member variables 
	msgOut.m_strCommand		= "@getMint";	// reply to getMint
	msgOut.m_strNymID		= MsgIn.m_strNymID;	// UserID
	msgOut.m_strServerID	= m_strServerID;	// ServerID, a hash of the server contract.
	msgOut.m_strAssetID		= MsgIn.m_strAssetID;	// The Asset Type ID in question
	
	const OTIdentifier ASSET_TYPE_ID(MsgIn.m_strAssetID);	
	const OTString ASSET_ID_STR(ASSET_TYPE_ID);
	
	// --------------------------------------------------------------------

	bool bSuccessLoadingMint = false;
	
	OTMint theMint(m_strServerID, ASSET_ID_STR);

	if (true == (bSuccessLoadingMint = theMint.LoadMint(".PUBLIC")))
	{
		// You cannot hash the Mint to get its ID. 
		// (The ID is a hash of the asset contract, not the mint contract.)
		// Instead, you must READ the ID from the Mint file, and then compare it to the one expected
		// to see if they match (similar to how Account IDs are verified.)
		
		bSuccessLoadingMint = theMint.VerifyMint(m_nymServer);
		
		// Yup the asset contract exists.
		if (bSuccessLoadingMint)
		{
			msgOut.m_bSuccess = true;
			
			// extract the account in ascii-armored form on the outgoing message
			OTString strPayload(theMint); // first grab it in plaintext string form
			msgOut.m_ascPayload.SetString(strPayload);  // now the outgoing message has the inbox ledger in its payload in base64 form.
		}
		// Send the user's command back to him if failure.
	}
	
	if (!bSuccessLoadingMint)
	{
		msgOut.m_bSuccess = false;
		OTString tempInMessage(MsgIn); // Grab the incoming message in plaintext form
		msgOut.m_ascInReferenceTo.SetString(tempInMessage); // Set it into the base64-encoded object on the outgoing message
	}
	
	// (2) Sign the Message 
	msgOut.SignContract((const OTPseudonym &)m_nymServer);
	
	// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
	//
	// FYI, SaveContract takes m_xmlUnsigned and wraps it with the signatures and ------- BEGIN  bookends
	// If you don't pass a string in, then SaveContract saves the new version to its member, m_strRawFile
	msgOut.SaveContract();
}




void OTServer::UserCmdGetNymbox(OTPseudonym & theNym, OTMessage & MsgIn, OTMessage & msgOut)
{
	// (1) set up member variables 
	msgOut.m_strCommand		= "@getNymbox";	// reply to getInbox
	msgOut.m_strNymID		= MsgIn.m_strNymID;	// UserID
	msgOut.m_strServerID	= m_strServerID;	// ServerID, a hash of the server contract.
	
	const OTIdentifier USER_ID(MsgIn.m_strNymID), SERVER_ID(MsgIn.m_strServerID);
	
	OTLedger theLedger(USER_ID, USER_ID, SERVER_ID);
	
	if (msgOut.m_bSuccess = theLedger.LoadNymbox())
	{ 		
		// extract the ledger in ascii-armored form on the outgoing message
		OTString strPayload(theLedger); // first grab it in plaintext string form
		msgOut.m_ascPayload.SetString(strPayload);  // now the outgoing message has the nymbox ledger in its payload in base64 form.
	}
	// Send the user's command back to him if failure.
	else
	{
		OTString tempInMessage(MsgIn); // Grab the incoming message in plaintext form
		msgOut.m_ascInReferenceTo.SetString(tempInMessage); // Set it into the base64-encoded object on the outgoing message
	}
	
	// (2) Sign the Message 
	msgOut.SignContract((const OTPseudonym &)m_nymServer);
	
	// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
	//
	// FYI, SaveContract takes m_xmlUnsigned and wraps it with the signatures and ------- BEGIN  bookends
	// If you don't pass a string in, then SaveContract saves the new version to its member, m_strRawFile
	msgOut.SaveContract();
}



void OTServer::UserCmdGetInbox(OTPseudonym & theNym, OTMessage & MsgIn, OTMessage & msgOut)
{
	// (1) set up member variables 
	msgOut.m_strCommand		= "@getInbox";	// reply to getInbox
	msgOut.m_strNymID		= MsgIn.m_strNymID;	// UserID
	msgOut.m_strServerID	= m_strServerID;	// ServerID, a hash of the server contract.
	msgOut.m_strAcctID		= MsgIn.m_strAcctID;	// The Account ID in question
	
	const OTIdentifier USER_ID(MsgIn.m_strNymID), ACCOUNT_ID(MsgIn.m_strAcctID), SERVER_ID(MsgIn.m_strServerID);
	
	OTLedger theLedger(USER_ID, ACCOUNT_ID, SERVER_ID);
	
	if (msgOut.m_bSuccess = theLedger.LoadInbox())
	{ 		
		// extract the ledger in ascii-armored form on the outgoing message
		OTString strPayload(theLedger); // first grab it in plaintext string form
		msgOut.m_ascPayload.SetString(strPayload);  // now the outgoing message has the inbox ledger in its payload in base64 form.
	}
	// Send the user's command back to him if failure.
	else
	{
		OTString tempInMessage(MsgIn); // Grab the incoming message in plaintext form
		msgOut.m_ascInReferenceTo.SetString(tempInMessage); // Set it into the base64-encoded object on the outgoing message
	}
	
	// (2) Sign the Message 
	msgOut.SignContract((const OTPseudonym &)m_nymServer);
	
	// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
	//
	// FYI, SaveContract takes m_xmlUnsigned and wraps it with the signatures and ------- BEGIN  bookends
	// If you don't pass a string in, then SaveContract saves the new version to its member, m_strRawFile
	msgOut.SaveContract();
}



void OTServer::UserCmdGetOutbox(OTPseudonym & theNym, OTMessage & MsgIn, OTMessage & msgOut)
{
	// (1) set up member variables 
	msgOut.m_strCommand		= "@getOutbox";	// reply to getOutbox
	msgOut.m_strNymID		= MsgIn.m_strNymID;	// UserID
	msgOut.m_strServerID	= m_strServerID;	// ServerID, a hash of the server contract.
	msgOut.m_strAcctID		= MsgIn.m_strAcctID;	// The Account ID in question
	
	const OTIdentifier USER_ID(MsgIn.m_strNymID), ACCOUNT_ID(MsgIn.m_strAcctID), SERVER_ID(MsgIn.m_strServerID);
	
	OTLedger theLedger(USER_ID, ACCOUNT_ID, SERVER_ID);
	
	if (msgOut.m_bSuccess = theLedger.LoadOutbox())
	{ 		
		// extract the ledger in ascii-armored form on the outgoing message
		OTString strPayload(theLedger); // first grab it in plaintext string form
		msgOut.m_ascPayload.SetString(strPayload);  // now the outgoing message has the outbox ledger in its payload in base64 form.
	}
	// Send the user's command back to him if failure.
	else
	{
		OTString tempInMessage(MsgIn); // Grab the incoming message in plaintext form
		msgOut.m_ascInReferenceTo.SetString(tempInMessage); // Set it into the base64-encoded object on the outgoing message
	}
	
	// (2) Sign the Message 
	msgOut.SignContract((const OTPseudonym &)m_nymServer);
	
	// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
	//
	// FYI, SaveContract takes m_xmlUnsigned and wraps it with the signatures and ------- BEGIN  bookends
	// If you don't pass a string in, then SaveContract saves the new version to its member, m_strRawFile
	msgOut.SaveContract();
}






void OTServer::UserCmdProcessNymbox(OTPseudonym & theNym, OTMessage & MsgIn, OTMessage & msgOut)
{
	// (1) set up member variables 
	msgOut.m_strCommand		= "@processNymbox";	// reply to processNymbox
	msgOut.m_strNymID		= MsgIn.m_strNymID;	// UserID
	msgOut.m_strServerID	= m_strServerID;	// ServerID, a hash of the server contract.
	
	const OTIdentifier	USER_ID(msgOut.m_strNymID), 
						SERVER_ID(m_strServerID),
						SERVER_USER_ID(m_nymServer);
	
	OTLedger theLedger(USER_ID, USER_ID, SERVER_ID);	// These are ledgers used as messages. The one we received 
														// and the one we're sending back.
	OTLedger * pResponseLedger = OTLedger::GenerateLedger(SERVER_USER_ID, USER_ID, SERVER_ID, OTLedger::message, false); // bCreateFile=false
	OTCleanup<OTLedger> theRespLedgerGuardian(pResponseLedger);
	
	// Grab the string (containing the request ledger) out of ascii-armored form.
	OTString strLedger(MsgIn.m_ascPayload);	
	
	// theLedger contains a single transaction from the client, with an item inside
	// for each inbox transaction the client wants to accept or reject.
	// Let's see if we can load it from the string that came in the message...
	if (msgOut.m_bSuccess = theLedger.LoadContractFromString(strLedger))
	{		
		// In this case we need to process the transaction items from the ledger
		// and create a corresponding transaction where each of the new items
		// contains the answer to the transaction item sent.
		// Then we send that new "response ledger" back to the user in MsgOut.Payload
		// as an @processNymbox message.
		
		OTTransaction * pTransaction	= NULL;
		OTTransaction * pTranResponse	= NULL;
		
		for (mapOfTransactions::iterator ii = theLedger.GetTransactionMap().begin(); 
			 ii != theLedger.GetTransactionMap().end(); ++ii)
		{	
			pTransaction = (*ii).second;
			
			OT_ASSERT_MSG(NULL != pTransaction, "NULL transaction pointer in OTServer::UserCmdProcessNymbox\n");
			
			// for each transaction in the ledger, we create a transaction response and add
			// that to the response ledger.
			pTranResponse = OTTransaction::GenerateTransaction(*pResponseLedger, OTTransaction::error_state, pTransaction->GetTransactionNum());
			
			// Add the response transaction to the response ledger.
			// That will go into the response message and be sent back to the client.
			pResponseLedger->AddTransaction(*pTranResponse);
			
			// Now let's make sure the response transaction has a copy of the transaction
			// it is responding to.
			//				OTString strResponseTo;
			//				pTransaction->SaveContract(strResponseTo);
			//				pTranResponse->m_ascInReferenceTo.SetString(strResponseTo);
			// I commented out the above because we are keeping too many copies.
			// Message contains a copy of the message it's responding to.
			// Then each transaction contains a copy of the transaction responding to...
			// Then each ITEM in each transaction contains a copy of each item it's responding to.
			//
			// Therefore, for the "processNymbox" message, I have decided (for now) to have
			// the extra copy in the items themselves, and in the overall message, but not in the
			// transactions. Thus, the above is commented out.
			
			
			// It should always return something. Success, or failure, that goes into pTranResponse.
			// I don't think there's need for more return value than that. The user has gotten deep 
			// enough that they deserve SOME sort of response.
			//
			// This function also SIGNS the transaction, so there is no need to sign it after this.
			// There's also no point to change it after this, unless you plan to sign it twice.
			NotarizeProcessNymbox(theNym, *pTransaction, *pTranResponse);
			
			pTranResponse = NULL; // at this point, the ledger now "owns" the response, and will handle deleting it.
		}
		
		// TODO: should consider saving a copy of the response ledger here on the server. 
		// Until the user signs off of the responses, maybe the user didn't receive them.
		// The server should be able to re-send them until confirmation, then delete them.
		// So might want to consider a SAVE TO FILE here of that ledger we're sending out...
		
		// sign the ledger
		pResponseLedger->SignContract(m_nymServer);
		pResponseLedger->SaveContract();
		// extract the ledger in ascii-armored form
		OTString strPayload(*pResponseLedger);
		// now the outgoing message has the response ledger in its payload.
		msgOut.m_ascPayload.SetString(strPayload); 
	
	}
	else {
		OTLog::Error("ERROR loading ledger from message in OTServer::UserCmdProcessNymbox\n");
	}
	
	
	// todo: consider commenting this out since the transaction reply items already include a copy
	// of the original client communication that the server is responding to. No point beating a
	// dead horse.
	//
	// Send the user's command back to him as well.
	{
		OTString tempInMessage(MsgIn);
		msgOut.m_ascInReferenceTo.SetString(tempInMessage);
	}
	
	// (2) Sign the Message 
	msgOut.SignContract(m_nymServer);		
	
	// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
	//
	// FYI, SaveContract takes m_xmlUnsigned and wraps it with the signatures and ------- BEGIN  bookends
	// If you don't pass a string in, then SaveContract saves the new version to its member, m_strRawFile
	msgOut.SaveContract();
}





/// The client may send multiple transactions in the ledger when he calls processNymbox.
/// This function will be called for each of those.  Each may contain multiple items accepting
/// or rejecting certain transactions. The server acknowledges and notarizes those transactions
/// accordingly.
/// (And each of those transactions must be accepted or rejected in whole.)
void OTServer::NotarizeProcessNymbox(OTPseudonym & theNym, OTTransaction & tranIn, OTTransaction & tranOut)
{
	// The outgoing transaction is an "atProcessNymbox", that is, "a reply to the process nymbox request"
	tranOut.SetType(OTTransaction::atProcessNymbox);
	
	OTItem * pItem			= NULL;
	OTItem * pBalanceItem	= tranIn.GetItem(OTItem::transactionStatement);
	OTItem * pResponseItem	= NULL;
	OTItem * pResponseBalanceItem	= NULL;
	
	// The incoming transaction may be sent to inboxes and outboxes, and it
	// will probably be bundled in our reply to the user as well. Therefore,
	// let's grab it as a string.
	OTString strInReferenceTo;
	OTString strBalanceItem;
	
	// Grab the actual server ID from this object, and use it as the server ID here.
	const OTIdentifier SERVER_ID(m_strServerID), USER_ID(theNym), SERVER_USER_ID(m_nymServer);
	
	// --------------------------------------------------------------------
	
	OTPseudonym theTempNym;

	OTLedger theNymbox(USER_ID, USER_ID, SERVER_ID);
	OTString strNymID(USER_ID);

	bool bSuccessLoadingNymbox	= theNymbox.LoadNymbox();
	
	if (true == bSuccessLoadingNymbox)
		bSuccessLoadingNymbox	= theNymbox.VerifyAccount(m_nymServer); // make sure it's all good.
	
	// --------------------------------------------------------------------
	
	if (false == bSuccessLoadingNymbox)
	{
		OTLog::vOutput(0, "OTServer::NotarizeProcessNymbox: Failed loading or verifying Nymbox for user:\n%s\n", 
					  strNymID.Get());
	}
	else if (NULL == pBalanceItem)
	{
		OTLog::Output(0, "OTServer::NotarizeProcessNymbox: No Transaction Agreement item found on this transaction (required).\n");
	}
	else 
	{
		pBalanceItem->SaveContract(strBalanceItem);
		
		pResponseBalanceItem = OTItem::CreateItemFromTransaction(tranOut, OTItem::atTransactionStatement);	 
		pResponseBalanceItem->SetStatus(OTItem::rejection); // the default.
		pResponseBalanceItem->SetReferenceString(strBalanceItem); // the response item carries a copy of what it's responding to.
		pResponseBalanceItem->SetReferenceToNum(pBalanceItem->GetTransactionNum()); // This response item is IN RESPONSE to tranIn's balance agreement
		tranOut.AddItem(*pResponseBalanceItem); // the Transaction's destructor will cleanup the item. It "owns" it now.		
		
		
		// The incoming transaction accepts various messages and transaction numbers.
		// So when it's all finished, my list of transaction numbers will be higher.
		// 
		// I would like to not even process the whole giant loop below, 
		// if I can verify here now that the transaction agreement is wrong.
		//
		// Thus I will actually loop through the acceptTransaction items in tranIn, and then for each one, I'll
		// lookup the ACTUAL transaction in the nymbox, and get its ACTUAL value. (And store them all up on a temp nym.)
		//
		// The ones being accepted will therefore be added to my Nym, so the Transaction Statement will be signed
		// as if that is already the case. (So they'll match.)
		//
		// I need to add them all to the Nym, verify the transaction statement, and then remove them again.
		// (which is why I stored them on a temp Nym :-) Then if it succeeds for real, at the bottom of this function,
		// I'll go ahead and add them properly (so it adds them to both lists.)
		//
		
		bool bSuccessFindingAllTransactions = true;
		long lTotalBeingAccepted = 0;
		
		for (listOfItems::iterator ii = tranIn.GetItemList().begin(); ii != tranIn.GetItemList().end(); ++ii)
		{
			pItem = *ii;
			
			OT_ASSERT_MSG(NULL != pItem, "Pointer should not have been NULL.");
			
			if (pItem->GetType() == OTItem::acceptTransaction)
			{
				OTTransaction * pTransaction = theNymbox.GetTransaction(pItem->GetReferenceToNum());
				
				if ((NULL != pTransaction) && (pTransaction->GetType() == OTTransaction::blank))
				{
					bSuccessFindingAllTransactions = true;
					
					theNym.AddIssuedNum(m_strServerID, pItem->GetReferenceToNum()); 
					theTempNym.AddIssuedNum(m_strServerID, pItem->GetReferenceToNum()); // so I can remove from theNym after VerifyTransactionStatement call
				}
				else 
				{
					bSuccessFindingAllTransactions = false;
					break;
				}
			}
		}
		
		// ------------------------------------------
		
		if (false == bSuccessFindingAllTransactions)
		{
			OTLog::Output(0, "OTServer::NotarizeProcessNymbox: transactions in processNymbox message do not match actual nymbox.\n");

			// Remove all issued nums from theNym that are stored on theTempNym HERE.
			for (int i = 0; i < theTempNym.GetIssuedNumCount(SERVER_ID); i++)
			{
				long lTemp = theTempNym.GetIssuedNum(SERVER_ID, i);
				theNym.RemoveIssuedNum(m_strServerID, lTemp);
			}			
		}
		else if (false == pBalanceItem->VerifyTransactionStatement(theNym, false)) // bIsRealTransaction=false (since we're doing Nymbox) // <========
		{
			OTLog::vOutput(0, "OTServer::NotarizeProcessNymbox: ERROR verifying transaction statement.\n");
			
			// Remove all issued nums from theNym that are stored on theTempNym HERE.
			for (int i = 0; i < theTempNym.GetIssuedNumCount(SERVER_ID); i++)
			{
				long lTemp = theTempNym.GetIssuedNum(SERVER_ID, i);
				theNym.RemoveIssuedNum(m_strServerID, lTemp);
			}			
		}
		
		else // TRANSACTION AGREEMENT WAS SUCCESSFUL.......
		{
			// Remove all issued nums from theNym that are stored on theTempNym HERE.
			for (int i = 0; i < theTempNym.GetIssuedNumCount(SERVER_ID); i++)
			{
				long lTemp = theTempNym.GetIssuedNum(SERVER_ID, i);
				theNym.RemoveIssuedNum(m_strServerID, lTemp);
			}			

			pResponseBalanceItem->SetStatus(OTItem::acknowledgement); // the transaction agreement was successful.

			// --------------------------------------------------------------------
			
			// THE ABOVE LOOP WAS JUST A TEST RUN 
			//
			// (TO **VERIFY TRANSACTION AGREEMENT** BEFORE WE BOTHERED TO RUN THIS LOOP BELOW...)
			// (AND TO GET THE LIST OF NUMBERS FOR THE STATEMENT ONTO TEMP NYM.)
		
			
			// loop through the items that make up the incoming transaction, and add them
			// to the Nym, and remove them from the Nymbox, as appropriate.
			//
			for (listOfItems::iterator ii = tranIn.GetItemList().begin(); ii != tranIn.GetItemList().end(); ++ii)
			{
				pItem = *ii;
				
				OT_ASSERT_MSG(NULL != pItem, "Pointer should not have been NULL.");
				
				// We already handled this one (if we're even in this block in the first place.)
				//
				if (OTItem::transactionStatement	== pItem->GetType())
				{
					continue;
				}
				
				// If the client sent an accept item then let's process it.
				if ( 
					(OTItem::request == pItem->GetStatus())
					&&
					(
					 (OTItem::acceptTransaction	== pItem->GetType()) ||	// Accepting new transaction number.
					 (OTItem::acceptMessage		== pItem->GetType())	// Accepted message.
					 )
					)
				{
					// The response item will contain a copy of the "accept" request.
					// So I'm just setting aside a copy now for those purposes later.
					pItem->SaveContract(strInReferenceTo);
					
					OTItem::itemType theReplyItemType;
					switch (pItem->GetType()) 
					{
						case OTItem::acceptTransaction:
							theReplyItemType = OTItem::atAcceptTransaction;
							break;
						case OTItem::acceptMessage:
							theReplyItemType = OTItem::atAcceptMessage;
							break;
						default:
							theReplyItemType = OTItem::error_state; // should never happen based on above 'if' statement.
							break;									// saving this anyway just cause it's cleaner.
					} 
					
					
					// Server response item being added to server response transaction (tranOut)
					// They're getting SOME sort of response item.
					
					pResponseItem = OTItem::CreateItemFromTransaction(tranOut, theReplyItemType);	 
					pResponseItem->SetStatus(OTItem::rejection); // the default.
					pResponseItem->SetReferenceString(strInReferenceTo); // the response item carries a copy of what it's responding to.
//					pResponseItem->SetReferenceToNum(pItem->GetTransactionNum()); // This was just 0 every time, since Nymbox needs no transaction numbers.
					pResponseItem->SetReferenceToNum(pItem->GetReferenceToNum()); // So the reference was useless. I'm hoping to change it to this and make sure nothing breaks.
																				// ReferenceNum actually means you can match it up against the request items, and also, that is where THEY store it.
					tranOut.AddItem(*pResponseItem); // the Transaction's destructor will cleanup the item. It "owns" it now.		
					
					// ---------------------------------------------
					
					OTTransaction * pServerTransaction = NULL;
					
					if ( 
							 (NULL != (pServerTransaction = theNymbox.GetTransaction(pItem->GetReferenceToNum()))) 
							 &&
							 (
							  (OTTransaction::blank		== pServerTransaction->GetType()) ||	// new transaction number waiting to be picked up.
							  (OTTransaction::message	== pServerTransaction->GetType())		// message in the nymbox
							 )																	
							)																
					{																				
						// the accept item will come with the transaction number that
						// it's referring to. So we'll just look up that transaction
						// in the nymbox, and now that it's been accepted, we'll process it.
						
						// At this point, pItem points to the client's attempt to accept pServerTransaction
						// and pServerTransaction is the server's created transaction in my nymbox that might
						// have a message or transaction number on it I might find useful.
						
							
						// What are we doing in this code?
						//
						// I need to accept various items that are sitting in my nymbox, such as:
						//
						// -- transaction numbers waiting to be accepted (they cannot be rejected.)
						//
						// -- messages waiting to be accepted (they cannot be rejected.)
						//
							
						// ----------------------------------------------------------------------------------------------
							
						// The below block only executes for ACCEPTING a MESSAGE
						if (
							(OTItem::acceptMessage	== pItem->GetType()) 
							&&
							(OTTransaction::message	== pServerTransaction->GetType())
						   )
							
						{	
							// pItem contains the current user's attempt to accept the 
							// ['message'] located in pServerTransaction.
							// Now we have the user's item and the item he is trying to accept.
							
							theNymbox.	RemoveTransaction(pServerTransaction->GetTransactionNum());
							
							theNymbox.	ReleaseSignatures();
							theNymbox.	SignContract(m_nymServer);
							theNymbox.	SaveContract();
							theNymbox.	SaveNymbox();
							
							// Now we can set the response item as an acknowledgement instead of the default (rejection)
							pResponseItem->SetStatus(OTItem::acknowledgement);
						}// its type is OTItem::aacceptMessage
						

						// The below block only executes for ACCEPTING a TRANSACTION NUMBER
						else if (
								 (OTItem::acceptTransaction == pItem->GetType())
								 &&
								 (OTTransaction::blank == pServerTransaction->GetType())
								)
						{
							// pItem contains the current user's attempt to accept the 
							// transaction number located in pServerTransaction.
							// Now we have the user's item and the item he is trying to accept.
							
							theNymbox.	RemoveTransaction(pServerTransaction->GetTransactionNum());
							
							theNymbox.	ReleaseSignatures();
							theNymbox.	SignContract(m_nymServer);
							theNymbox.	SaveContract();
							theNymbox.	SaveNymbox();
							
							// Now we can set the response item as an acknowledgement instead of the default (rejection)
							pResponseItem->SetStatus(OTItem::acknowledgement);
						}
					}
					else 
					{
						OTLog::vError("Error finding original transaction that client is trying to accept: %ld\n",
									  pItem->GetReferenceToNum());
					}
					
					// sign the response item before sending it back (it's already been added to the transaction above)
					// Now, whether it was rejection or acknowledgement, it is set properly and it is signed, and it
					// is owned by the transaction, who will take it from here.
					pResponseItem->SignContract(m_nymServer);
					pResponseItem->SaveContract();
				}
				else 
				{
					const int nStatus	= pItem->GetStatus();
					OTString strItemType;
					pItem->GetTypeString(strItemType);
					
					OTLog::vError("Error, unexpected item type (%s) and/or status (%d) in OTServer::NotarizeProcessNymbox\n",
								 strItemType.Get(), nStatus);
				} // if type == ACCEPT (only)
			} // for each item
		} // else (balance agreement verified.)
		
		pResponseBalanceItem->SignContract(m_nymServer);
		pResponseBalanceItem->SaveContract();

	} // Balance Agreement item found.
	
	// ----------------------------------------
	
	tranOut.ReleaseSignatures();
	tranOut.SignContract(m_nymServer);
	tranOut.SaveContract();

	// ----------------------------------------
	
	OTString strPath;
	
	// On the server side, response will only have chance to succeed if balance agreement succeeds first.
	// Therefore, you will never see successful response but failed balance, since it would stop at the
	// balance and response itself would remain failed with no chance of changing.
	//
	// Thus, "success" must be when balance succeeded and transaction succeeded,
	// and "failure" must be when balance succeeded but transaction failed.
	//
	// If NEITHER succeeded, then there is no point recording it to a file, now is there?
	
	if ((NULL != pResponseBalanceItem) && OTItem::acknowledgement == pResponseBalanceItem->GetStatus())
	{
		if (tranOut.GetSuccess())
		{
			// Transaction agreement was a success, AND process nymbox was a success.
			// Therefore, add any new issued numbers to theNym, and save.
			
			theNym.HarvestIssuedNumbers(m_nymServer, theTempNym, true); // bSave=true
			
			strPath.Format((char*)"%s.success", strNymID.Get());
		}
		else
			strPath.Format((char*)"%s.fail", strNymID.Get());
		
		const char * szFoldername = OTLog::ReceiptFolder();
		
		tranOut.SaveContract(szFoldername, strPath.Get());	
	}
}






void OTServer::UserCmdProcessInbox(OTPseudonym & theNym, OTMessage & MsgIn, OTMessage & msgOut)
{
	// (1) set up member variables 
	msgOut.m_strCommand		= "@processInbox";	// reply to processInbox
	msgOut.m_strNymID		= MsgIn.m_strNymID;	// UserID
	msgOut.m_strServerID	= m_strServerID;	// ServerID, a hash of the server contract.
	msgOut.m_strAcctID		= MsgIn.m_strAcctID;	// The Account ID in question
	
	const OTIdentifier	USER_ID(msgOut.m_strNymID), 
						ACCOUNT_ID(MsgIn.m_strAcctID), 
						SERVER_ID(m_strServerID),
						SERVER_USER_ID(m_nymServer);
	
	OTLedger theLedger(USER_ID, ACCOUNT_ID, SERVER_ID);			// These are ledgers used as messages. The one we received, 
																// and the one we're sending back.
	OTLedger * pResponseLedger = OTLedger::GenerateLedger(SERVER_USER_ID, ACCOUNT_ID, SERVER_ID, OTLedger::message, false); // bCreateFile=false
	OTCleanup<OTLedger> theRespLedgerGuardian(pResponseLedger);
	
	// Grab the string (containing the request ledger) out of ascii-armored form.
	OTString strLedger(MsgIn.m_ascPayload);	
	
	// theLedger contains a single transaction from the client, with an item inside
	// for each inbox transaction the client wants to accept or reject.
	// Let's see if we can load it from the string that came in the message...
	if (msgOut.m_bSuccess = theLedger.LoadContractFromString(strLedger))
	{		
		OTAccount theAccount(USER_ID, ACCOUNT_ID, SERVER_ID);

		// Make sure the "from" account even exists...
		if (!theAccount.LoadContract())
		{
			OTLog::vOutput(0, "Failed loading account in OTServer::UserCmdProcessInbox\n");
		}
		// Make sure the Account ID loaded from the file matches the one we just set and used as the filename.
		else if (!theAccount.VerifyContractID())
		{
			// this should never happen. How did the wrong ID get into the account file, if the right
			// ID is on the filename itself? and vice versa.
			OTLog::Error("Error verifying account ID in OTServer::UserCmdProcessInbox\n");
		}
		// Make sure the nymID loaded up in the account as its actual owner matches the nym who was
		// passed in to this function requesting a transaction on this account... otherwise any asshole
		// could do transactions on your account, no?
		else if (!theAccount.VerifyOwner(theNym))
		{
			OTLog::vOutput(0, "Failed verifying account ownership in OTServer::UserCmdProcessInbox\n");		
		}
		// Make sure I, the server, have signed this file.
		else if (!theAccount.VerifySignature(m_nymServer))
		{
			OTLog::Error("Error verifying server signature on account in OTServer::UserCmdProcessInbox\n");
		}
		// No need to call VerifyAccount() here since the above calls go above and beyond that method.
		
		else 
		{
			// In this case we need to process the transaction items from the ledger
			// and create a corresponding transaction where each of the new items
			// contains the answer to the transaction item sent.
			// Then we send that new "response ledger" back to the user in MsgOut.Payload
			// as an @processInbox message.
			
			OTTransaction * pTransaction	= theLedger.GetTransaction(OTTransaction::processInbox);
			OTTransaction * pTranResponse	= NULL;
			
			if (NULL == pTransaction) // I'm assuming there's only one in the ledger (for now anyways..)
			{
				OTLog::Error("Expected processInbox transaction in OTServer::UserCmdProcessInbox\n");
			}
			else
			{
				// We create a transaction response and add that to the response ledger...
				//
				pTranResponse = OTTransaction::GenerateTransaction(*pResponseLedger, OTTransaction::error_state, pTransaction->GetTransactionNum());
				
				// Add the response transaction to the response ledger.
				// That will go into the response message and be sent back to the client.
				pResponseLedger->AddTransaction(*pTranResponse);
				
				//---------------------------------------------------
				
				const long lTransactionNumber = pTransaction->GetTransactionNum();
				
				//---------------------------------------------------

				if (!VerifyTransactionNumber(theNym, lTransactionNumber))
				{
					// The user may not submit a transaction using a number he's already used before.
					OTLog::Output(0, "Error verifying transaction number in OTServer::UserCmdProcessInbox\n");
				}
				
				// The items' acct and server ID were already checked in VerifyContractID() when they were loaded. 
				// Now this checks a little deeper, to verify ownership, signatures, and transaction number
				// on each item.  That way those things don't have to be checked for security over and over
				// again in the subsequent calls.
				//
				else if (!pTransaction->VerifyItems(theNym)) 
				{
					OTLog::Output(0, "Error verifying transaction items OTServer::UserCmdProcessInbox\n");
				}
				
				// any other security stuff?
				// Todo do I need to verify the server ID here as well?
				else
				{
					// We don't want any transaction number being used twice.
					// (The number, at this point, is STILL issued to the user, who is still responsible
					// for that number and must continue signing for it. All this means here is that the
					// user no longer has the number on his AVAILABLE list. Removal from issued list happens separately.)
					//
					if (false == RemoveTransactionNumber(theNym, lTransactionNumber, true)) //bSave=true
					{
						OTLog::Error("Error removing transaction number (as available) from user nym in OTServer::UserCmdProcessInbox\n");
					}			
					
					// -------------------------------------------------------------------
					
					else 
					{						
						OTLog::Output(0, "UserCmdProcessInbox type: Process Inbox\n");
						
						NotarizeProcessInbox(theNym, theAccount, *pTransaction, *pTranResponse);	
						
						// ------------------------------------------
						
						// Where appropriate, remove a transaction number from my issued list 
						// (the list of numbers I must sign for in every balance agreement.)
						
						if (false == RemoveIssuedNumber(theNym, lTransactionNumber, true)) //bSave=true
						{
							OTLog::Error("Error removing issued number from user nym in OTServer::UserCmdProcessInbox\n");
						}	
					}
				}
				
				// sign the outoing transaction
				pTranResponse->SignContract(m_nymServer);	
				pTranResponse->SaveContract();	 // don't forget to save (to internal raw file member)			
				
				pTranResponse = NULL; // at this point, the ledger now "owns" the response, and will handle deleting it.
			} // for loop
			
			// TODO: should consider saving a copy of the response ledger here on the server. 
			// Until the user signs off of the responses, maybe the user didn't receive them.
			// The server should be able to re-send them until confirmation, then delete them.
			// So might want to consider a SAVE TO FILE here of that ledger we're sending out...
			
			// sign the ledger
			pResponseLedger->SignContract(m_nymServer);
			pResponseLedger->SaveContract();
			// extract the ledger in ascii-armored form
			OTString strPayload(*pResponseLedger);
			// now the outgoing message has the response ledger in its payload.
			msgOut.m_ascPayload.SetString(strPayload); 
		}
	}
	else 
	{
		OTLog::Error("ERROR loading ledger from message in OTServer::UserCmdProcessInbox\n");
	}
	
	
	// todo: consider commenting this out since the transaction reply items already include a copy
	// of the original client communication that the server is responding to. No point beating a
	// dead horse.
	//
	// Send the user's command back to him as well.
	{
		OTString tempInMessage(MsgIn);
		msgOut.m_ascInReferenceTo.SetString(tempInMessage);
	}
	
	// (2) Sign the Message 
	msgOut.SignContract(m_nymServer);		
	
	// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
	//
	// FYI, SaveContract takes m_xmlUnsigned and wraps it with the signatures and ------- BEGIN  bookends
	// If you don't pass a string in, then SaveContract saves the new version to its member, m_strRawFile
	msgOut.SaveContract();
}




/// The client may send multiple transactions in the ledger when he calls processInbox.
/// This function will be called for each of those.  Each may contain multiple items accepting
/// or rejecting certain transactions. The server acknowledges and notarizes those transactions
/// accordingly.
/// (And each of those transactions must be accepted or rejected in whole.)
void OTServer::NotarizeProcessInbox(OTPseudonym & theNym, OTAccount & theAccount, OTTransaction & tranIn, OTTransaction & tranOut)
{
	// The outgoing transaction is an "atProcessInbox", that is, "a reply to the process inbox request"
	tranOut.SetType(OTTransaction::atProcessInbox);
	
	OTItem * pItem			= NULL;
	OTItem * pBalanceItem	= tranIn.GetItem(OTItem::balanceStatement);
	OTItem * pResponseItem	= NULL;
	OTItem * pResponseBalanceItem	= NULL;
	
	// The incoming transaction may be sent to inboxes and outboxes, and it
	// will probably be bundled in our reply to the user as well. Therefore,
	// let's grab it as a string.
	OTString strInReferenceTo;
	OTString strBalanceItem;
	
	// Grab the actual server ID from this object, and use it as the server ID here.
	const OTIdentifier	SERVER_ID(m_strServerID),	ACCOUNT_ID(theAccount), 
						USER_ID(theNym),			SERVER_USER_ID(m_nymServer);

	OTPseudonym theTempNym;

	// --------------------------------------------------------------
	
	OTLedger * pInbox	= theAccount.LoadInbox(m_nymServer); 
	OTLedger * pOutbox	= theAccount.LoadOutbox(m_nymServer); 
	
	OTCleanup<OTLedger> theInboxAngel(pInbox);
	OTCleanup<OTLedger> theOutboxAngel(pOutbox);

	// --------------------------------------------------------------

	if (NULL == pBalanceItem)
	{
		OTLog::Output(0, "OTServer::NotarizeProcessInbox: No Balance Agreement item found on this transaction.\n");
	}
	else if (NULL == pInbox || !pInbox->VerifyAccount(m_nymServer))
	{
		OTLog::Error("Error loading or verifying inbox.\n");
	}
	else if (NULL == pOutbox || !pOutbox->VerifyAccount(m_nymServer))
	{
		OTLog::Error("Error loading or verifying outbox.\n");
	}
	else 
	{
		pBalanceItem->SaveContract(strBalanceItem);

		pResponseBalanceItem = OTItem::CreateItemFromTransaction(tranOut, OTItem::atBalanceStatement);	 
		pResponseBalanceItem->SetStatus(OTItem::rejection); // the default.
		pResponseBalanceItem->SetReferenceString(strBalanceItem); // the response item carries a copy of what it's responding to.
		pResponseBalanceItem->SetReferenceToNum(pBalanceItem->GetTransactionNum()); // This response item is IN RESPONSE to tranIn's balance agreement
		tranOut.AddItem(*pResponseBalanceItem); // the Transaction's destructor will cleanup the item. It "owns" it now.		

		
		// This transaction accepts various incoming pending transfers.
		// So when it's all done, my balance will be higher.
		// AND pending inbox items will be removed from my inbox.
		// 
		// I would like to not even process the whole giant loop below, 
		// if I can verify here now that the balance agreement is wrong.
		//
		// Thus I will actually loop through the acceptPending items in tranIn, and then for each one, I'll
		// lookup the ACTUAL transaction in the inbox, and get its ACTUAL value. (And total them all up.)
		//
		// The total of those, (WITHOUT the user having to tell me what it will be, since I'm looking them all up),
		// should equal the difference in the account balance! Meaning the current balance plus that total will be
		// the expected NEW balance, according to this balance agreement -- if it wants to be approved, that is.
		//
		//
		
		bool bSuccessFindingAllTransactions = true;
		long lTotalBeingAccepted = 0;
		
		for (listOfItems::iterator ii = tranIn.GetItemList().begin(); ii != tranIn.GetItemList().end(); ++ii)
		{
			pItem = *ii;
			
			OT_ASSERT_MSG(NULL != pItem, "Pointer should not have been NULL.");
			
			if (pItem->GetType() == OTItem::acceptCronReceipt)
			{
				OTTransaction * pServerTransaction = pInbox->GetTransaction(pItem->GetReferenceToNum());

				OTLog::vOutput(0, "Checking server-side inbox for expected cron receipt: %ld... ",
							   pItem->GetReferenceToNum()); // temp remove
				
				if (NULL == pServerTransaction)
				{
					bSuccessFindingAllTransactions = false;
					break;
				}
				else if (pServerTransaction->GetReceiptAmount() != pItem->GetAmount())
				{
					OTLog::vError("OTServer::NotarizeProcessInbox: Receipt amounts don't match: %ld and %ld\n", 
								  pServerTransaction->GetReceiptAmount(), pItem->GetAmount());
					
					bSuccessFindingAllTransactions = false;
					break;
				}
				else 
				{
					bSuccessFindingAllTransactions = true;
					
					pInbox->RemoveTransaction(pServerTransaction->GetTransactionNum());					
				}					
			}
			else if ((pItem->GetType() == OTItem::acceptPending) ||
					 (pItem->GetType() == OTItem::acceptItemReceipt))
			{
				OTTransaction * pServerTransaction = pInbox->GetPendingTransaction(pItem->GetReferenceToNum());
				
				OTLog::vOutput(0, "Checking server-side inbox for expected pending or receipt transaction: %ld... ",
							   pItem->GetReferenceToNum()); // temp remove
				
				if (NULL == pServerTransaction)
				{
					bSuccessFindingAllTransactions = false;

					break;
				}
				else if (pServerTransaction->GetReceiptAmount() != pItem->GetAmount())
				{
					OTLog::vError("OTServer::NotarizeProcessInbox: Amounts don't match: %ld and %ld, trans#s: %ld and %ld\n", 
								  pServerTransaction->GetReceiptAmount(), pItem->GetAmount(),
								  pItem->GetTransactionNum(), pServerTransaction->GetTransactionNum());
					
					bSuccessFindingAllTransactions = false;
					break;
				}
				else 
				{
					bSuccessFindingAllTransactions = true;
					
					// IF I'm accepting a pending transfer, then add the amount to my counter of total amount being accepted.
					//
					// ELSE if I'm accepting an item receipt (which will remove my responsibility for that item) then add it
					// to the temp Nym (which is a list of transaction numbers that will be removed from my responsibility if
					// all is successful.)  Also remove all the Temp Nym numbers from theNym, so we can verify the Balance
					// Statement AS IF they were already removed. Add them 
					//
					if (pItem->GetType() == OTItem::acceptPending) // acceptPending
					{
						lTotalBeingAccepted += pServerTransaction->GetReceiptAmount();
					}
					else if (pItem->GetType() == OTItem::acceptItemReceipt) // acceptItemReceipt
					{
						// What number do I remove here? the user is accepting a transfer receipt, which
						// is in reference to the recipient's acceptPending. THAT item is in reference to
						// my original transfer (or contains a cheque with my original number.) (THAT's the # I need.)
						//
						OTString strOriginalItem;
						pServerTransaction->GetReferenceString(strOriginalItem);
						
						OTItem * pOriginalItem = OTItem::CreateItemFromString(strOriginalItem, SERVER_ID, pServerTransaction->GetReferenceToNum());
						OTCleanup<OTItem> theOrigItemGuardian(pOriginalItem); // So I don't have to clean it up later. No memory leaks.
						
						if (NULL != pOriginalItem)
						{
							// If pOriginalItem is acceptPending, that means the client is accepting the transfer receipt from the server, (from his inbox),
							// which has the recipient's acceptance inside of the client's transfer as the original item. This means the transfer that
							// the client originally sent is now finally closed!
							// 
							// If it's a depositCheque, that means the client is accepting the cheque receipt from the server, (from his inbox)
							// which has the recipient's deposit inside of it as the original item. This means that the cheque that
							// the client originally wrote is now finally closed!
							//
							// In both cases, the "original item" itself is not from the client, but from the recipient! Therefore,
							// the number on that item is useless for removing numbers from the client's list of issued numbers.
							// Rather, I need to load that original cheque, or pending transfer, from WITHIN the original item,
							// in order to get THAT number, to remove it from the client's issued list. (Whether for real, or for
							// setting up dummy data in order to verify the balance agreement.) *sigh*
							//						
							if (OTItem::depositCheque == pOriginalItem->GetType()) // client is accepting a cheque receipt, which has a depositCheque (from the recipient) as the original item within.
							{
								// Get the cheque from the Item and load it up into a Cheque object.
								OTString strCheque;
								pOriginalItem->GetAttachment(strCheque);
								
								OTCheque theCheque; // allocated on the stack :-)
								
								if (false == ((strCheque.GetLength() > 2) && 
											  theCheque.LoadContractFromString(strCheque)))
								{
									OTLog::vError("ERROR loading cheque from string in OTServer::NotarizeProcessInbox:\n%s\n",
												  strCheque.Get());
								}
								else	// Since the client wrote the cheque, and he is now accepting the cheque receipt, he can be cleared for that transaction number...
								{		
									theNym.RemoveIssuedNum(m_strServerID, theCheque.GetTransactionNum()); // Just removing temporarily so I can check the balance statement...
									theTempNym.AddIssuedNum(m_strServerID, theCheque.GetTransactionNum()); // (I need to add it back later, so I store here in a temp variable.)
								}
							}
							// client is accepting a transfer receipt, which has an acceptPending from the recipient as the original item within,
							else if (OTItem::acceptPending == pOriginalItem->GetType()) // (which is in reference to the client's outoing original transfer.)
							{
								theNym.RemoveIssuedNum(m_strServerID, pOriginalItem->GetReferenceToNum()); // Just removing temporarily so I can check the balance statement...
								theTempNym.AddIssuedNum(m_strServerID, pOriginalItem->GetReferenceToNum()); // (So I can add it back later, I store here in a temp variable.)
							}
							else 
							{
								OTString strOriginalItemType;
								pOriginalItem->GetTypeString(strOriginalItemType);
								OTLog::vError("OTServer::NotarizeProcessInbox: Original item has wrong type, while accepting item receipt:\n%s\n",
											  strOriginalItemType.Get());
							}
						}
						else 
						{
							OTLog::vError("OTServer::NotarizeProcessInbox: Unable to load original item from string while accepting item receipt:\n%s\n",
										  strOriginalItem.Get());
						}
					}
					
					
					// I'll also go ahead and remove each transaction from pInbox, and pass said inbox into the VerifyBalanceAgreement call...
					// (So it can simulate as if the inbox was already changed, and the total is already calculated, and if it succeeds,
					// then we can allow the giant loop below to do it all for real.)
					// (I'm not saving this copy of the inbox anyway--there's another one below.)
					//
					//pInbox->RemovePendingTransaction(pItem->GetReferenceToNum());
					// Let's remove it this way instead:
					pInbox->RemoveTransaction(pServerTransaction->GetTransactionNum());					
				}
			}
		}
		
		// ------------------------------------------
		
		if (false == bSuccessFindingAllTransactions)
		{
			OTLog::Output(0, "OTServer::NotarizeProcessInbox: transactions in processInbox message do not match actual inbox.\n");
			
			// Here, add all the issued nums back (that had been temporarily removed from theNym) that were stored on theTempNym.
			for (int i = 0; i < theTempNym.GetIssuedNumCount(SERVER_ID); i++)
			{
				long lTemp = theTempNym.GetIssuedNum(SERVER_ID, i);
				theNym.AddIssuedNum(m_strServerID, lTemp);
			}						
		}
		// Now after all that setup, we do the balance agreement!
		else if (false == pBalanceItem->VerifyBalanceStatement(lTotalBeingAccepted, 
															   theNym,
															   *pInbox,
															   *pOutbox,
															   theAccount,
															   tranIn))
		{
			OTLog::vOutput(0, "OTServer::NotarizeProcessInbox: ERROR verifying balance statement.\n");

			// Here, add all the issued nums back (that had been temporarily removed from theNym) that were stored on theTempNym for safe-keeping.
			for (int i = 0; i < theTempNym.GetIssuedNumCount(SERVER_ID); i++)
			{
				long lTemp = theTempNym.GetIssuedNum(SERVER_ID, i);
				theNym.AddIssuedNum(m_strServerID, lTemp);
			}						
		}
		
		else // BALANCE AGREEMENT WAS SUCCESSFUL.......
		{
			// Add all issued nums back (temporarily removed from theNym) that are stored on theTempNym HERE. Why add them back? Because
			// only when the actual TRANSACTION (below, that we did the above balance agreement FOR) is SUCCESSFUL will we then ACTUALLY remove the issued nums.
			for (int i = 0; i < theTempNym.GetIssuedNumCount(SERVER_ID); i++)
			{
				long lTemp = theTempNym.GetIssuedNum(SERVER_ID, i);
				theNym.AddIssuedNum(m_strServerID, lTemp);
			}						

			pResponseBalanceItem->SetStatus(OTItem::acknowledgement); // the transaction agreement was successful.
			
			// --------------------------------------------------------------------
			
			// THE ABOVE LOOP WAS JUST A TEST RUN 
			//
			// (TO VERIFY BALANCE AGREEMENT BEFORE WE BOTHERED TO RUN THIS LOOP BELOW...)
			
			// loop through the items that make up the incoming transaction 
			for (listOfItems::iterator ii = tranIn.GetItemList().begin(); ii != tranIn.GetItemList().end(); ++ii)
			{
				pItem = *ii;

				OT_ASSERT_MSG(NULL != pItem, "Pointer should not have been NULL.");
				
				// If the client sent an accept item, (or reject/dispute) then let's process it.
				if ( 
					(OTItem::request	== pItem->GetStatus())
					&&
					(
					(OTItem::acceptCronReceipt	== pItem->GetType()) ||	// Accepting notice of market trade or payment processing. (Original in Cron Receipt.)
		//			(OTItem::disputeCronReceipt	== pItem->GetType()) ||	// Disputing said notice.  With Cron receipts, original is stored as an OTCronItem...
					(OTItem::acceptItemReceipt	== pItem->GetType()) ||	// Accepted item receipt (cheque, transfer)
		//			(OTItem::disputeItemReceipt	== pItem->GetType()) ||	// Disputing said notice. 
					(OTItem::acceptPending	== pItem->GetType())		// Accepting notice of pending transfer 
		//			(OTItem::rejectPending	== pItem->GetType())		// With pending, the Original is stored in OTItem pOriginalItem...
					)
				)
				{
					// The response item will contain a copy of the "accept" request.
					// So I'm just setting aside a copy now for those purposes later.
					strInReferenceTo.Release();
					
					pItem->SaveContract(strInReferenceTo);
					
					OTItem::itemType theReplyItemType;
					switch (pItem->GetType()) 
					{
						case OTItem::acceptPending:
							theReplyItemType = OTItem::atAcceptPending;
							break;
						case OTItem::rejectPending:
							theReplyItemType = OTItem::atRejectPending;
							break;						
						case OTItem::acceptCronReceipt:
							theReplyItemType = OTItem::atAcceptCronReceipt;
							break;
						case OTItem::disputeCronReceipt:
							theReplyItemType = OTItem::atDisputeCronReceipt;
							break;
						case OTItem::acceptItemReceipt:
							theReplyItemType = OTItem::atAcceptItemReceipt;
							break;
						case OTItem::disputeItemReceipt:
							theReplyItemType = OTItem::atDisputeItemReceipt;
							break;
						default:
							theReplyItemType = OTItem::error_state; // should never happen based on above 'if' statement.
							break;									// saving this anyway just cause it's cleaner.
					} 

					
					// Server response item being added to server response transaction (tranOut)
					// They're getting SOME sort of response item.
					
					pResponseItem = OTItem::CreateItemFromTransaction(tranOut, theReplyItemType);	 
					pResponseItem->SetStatus(OTItem::rejection); // the default.
					pResponseItem->SetReferenceString(strInReferenceTo); // the response item carries a copy of what it's responding to.
					pResponseItem->SetReferenceToNum(pItem->GetTransactionNum());
					
					tranOut.AddItem(*pResponseItem); // the Transaction's destructor will cleanup the item. It "owns" it now.		
					
					
					// Need to load the Inbox first, in order to look up the transaction that
					// the client is accepting. This is possible because the client has included
					// the transaction number.  I'll just look it up in his inbox and then 
					// process it.
					// theAcctID is the ID on the client Account that was passed in.
					OTLedger theInbox(USER_ID, ACCOUNT_ID, SERVER_ID); 
					
					OTTransaction * pServerTransaction = NULL;
					
					if (false == theInbox.LoadInbox())
					{
						OTLog::Error("Error loading inbox during processInbox\n");
					}
					else if (false == theInbox.VerifyAccount(m_nymServer))
					{
						OTLog::Error("Error verifying inbox during processInbox\n");
					}
					// Warning! In the case of a OTTransaction::paymentReceipt or OTTransaction::marketReceipt,
					// the "in reference to" string will NOT contain an OTItem at all, but an OTPaymentPlan or
					// an OTTrade!! I handle those two cases first, here:
					//
					//
					else if ( 
							 (
		//					 (OTItem::disputeCronReceipt == pItem->GetType()) ||
							 (OTItem::acceptCronReceipt == pItem->GetType())// This is checked above, but just keeping this safe.
							)												// especially in case this block moves or is used elsewhere.
							 &&												
							 (NULL != (pServerTransaction = theInbox.GetTransaction(pItem->GetReferenceToNum())))
							&&							// Notice here I use theInbox.GetTransaction, whereas in the next
							 (							// section, I use theInbox.GetPendingTransaction instead. That's the 
							  (OTTransaction::paymentReceipt== pServerTransaction->GetType()) ||	// big difference between cron
							  (OTTransaction::marketReceipt	== pServerTransaction->GetType())		// receipts and other inbox items.
							 )
							)
					{
						// pItem contains the current user's attempt to accept the Receipt
						// represented by pServerTransaction. Therefore we have the user's
						// item AND the receipt he is trying to accept.
						
						theInbox.	RemoveTransaction(pServerTransaction->GetTransactionNum());
						
						theInbox.	ReleaseSignatures();
						theInbox.	SignContract(m_nymServer);
						theInbox.	SaveContract();
						theInbox.	SaveInbox();
						
						// Now we can set the response item as an acknowledgement instead of the default (rejection)
						pResponseItem->SetStatus(OTItem::acknowledgement);
					}
					
					// Careful here.  I'm looking up the original transaction number (1, say) which is stored
					// in my inbox as a "in reference to" on transaction number 41. (Which is a pending transaction
					// or receipt
					// that the server created in my inbox, and only REFERS to the original transaction, but is not
					// the original transaction in and of itself.)
					//
					// In other words, in this case below, I am looking for the transaction in the Inbox
					// that REFERS to the same transaction that the accept item REFERS to. That process, necessary
					// for pending transactions and cheque receipts, is NOT the case above, with receipts from cron.
					else if ( (
							   (OTItem::acceptItemReceipt	== pItem->GetType())	// acceptItemReceipt includes checkReceipt and transferReceipts.
		//					   (OTItem::rejectItemReceipt	== pItem->GetType())	
							|| (OTItem::acceptPending	== pItem->GetType())	// acceptPending includes checkReceipts. Because they are
		//					   (OTItem::rejectPending	== pItem->GetType())	// stored/loaded similarly, not like the above Cron Receipts.
							  ) 
							 &&
							  (NULL != (pServerTransaction = theInbox.GetPendingTransaction(pItem->GetReferenceToNum()))) 
							 &&
							  (
							   (OTTransaction::pending			== pServerTransaction->GetType()) ||	// pending transfer.
							   (OTTransaction::transferReceipt	== pServerTransaction->GetType()) ||	// transfer receipt.
							   (OTTransaction::chequeReceipt	== pServerTransaction->GetType())		// cheque receipt is down here in the pending section,
							  )																		// because this is where an OTItem is loaded up (since it
							 )																		// originated with a deposit transaction, not a cron receipt.)
					{																				
						// the accept item will come with the transaction number that
						// it's referring to. So we'll just look up that transaction
						// in the inbox, and now that it's been accepted, we'll process it.
						
						// At this point, pItem points to the client's attempt to accept pServerTransaction
						// and pServerTransaction is the server's created transaction in my inbox that contains
						// the original item (from the sender) as the "referenced to" object. So let's extract
						// it.
						OTString strOriginalItem;
						pServerTransaction->GetReferenceString(strOriginalItem);

						OTItem * pOriginalItem = OTItem::CreateItemFromString(strOriginalItem, SERVER_ID, pServerTransaction->GetReferenceToNum());
						OTCleanup<OTItem> theOrigItemGuardian(pOriginalItem); // So I don't have to clean it up later. No memory leaks.
						
						if (NULL != pOriginalItem)
						{
							
							// What are we doing in this code?
							//
							// I need to accept various items that are sitting in my inbox, such as:
							//
							// -- transfers waiting to be accepted (or rejected.)
							//
							// -- cheque deposit receipts waiting to be accepted (they cannot be rejected.)
							//
							// -- transfer receipts waiting to be accepted (they cannot be rejected.)

							//
							// ONLY in the case of pending transfers also do I need to mess around with my account,
							// and the sender's inbox and outbox. In the other cases, I merely need to remove
							// the item from my inbox.
							// Although when 'accepting the reject', I do need to take the money back into
							// my inbox...
							
							
							
							// ----------------------------------------------------------------------------------------------
							
							
							// The depositCheque request OTItem is saved as a "in reference to" field
							// on the inbox chequeReceipt transaction.
							
							// Therefore, if I am processing an acceptPending item from the client,
							// for accepting a chequeReceipt Transaction that's in his inbox, and
							// the original item (that the receipt is for) is a depositCheque,
							// then I can go ahead and clear it from his inbox.

							
							// The below block only executes for ACCEPTING a CHEQUE deposit receipt, or
							// for 'Accepting an ACCEPT.'
							//
							// I can't 'Accept a REJECT' without also transferring the rejected money back into
							// my own account. And that means fiddling with my account, and that means it will
							// be in a different block of code than this one.
							//
							// Whereas with accepting a cheque deposit receipt, or accepting an accepted transfer notice,
							// in both of those cases, my account balance doesn't change at all. I just need to accept
							// those notices in order to get them out of my inbox. So that's the simplest case, and it's
							// handled by THIS block of code:
							//
							if (
								(OTItem::acceptItemReceipt	== pItem->GetType()) 
								&&
								 (
								  (
									 (OTTransaction::transferReceipt	== pServerTransaction->GetType()) &&
									 (OTItem::acceptPending				== pOriginalItem->GetType())
								  )
								  ||	
								  (
									(OTTransaction::chequeReceipt	== pServerTransaction->GetType()) &&
									(OTItem::depositCheque			== pOriginalItem->GetType())
								  )
								)
								
							   )	
							{	// (The funds are already paid out...)
								// pItem contains the current user's attempt to accept the 
								// ['depositCheque' OR 'acceptPending'] located in theOriginalItem.
								// Now we have the user's item and the item he is trying to accept.

								theInbox.	RemoveTransaction(pServerTransaction->GetTransactionNum());
								
								theInbox.	ReleaseSignatures();
								theInbox.	SignContract(m_nymServer);
								theInbox.	SaveContract();
								theInbox.	SaveInbox();
								
								// Now we can set the response item as an acknowledgement instead of the default (rejection)
								pResponseItem->SetStatus(OTItem::acknowledgement);
							
								// Don't I need to remove from responsibility list?
								// No, because that is done at the bottom of the function.	
								//
							}// its type is OTItem::acceptPending or OTItem::depositCheque
							
							
							
							// ----------------------------------------------------------------------------------------------
							
							// TODO: 'Accept a REJECT' -- NEED TO PERFORM THE TRANSFER OF FUNDS BACK TO THE SENDER'S ACCOUNT WHEN TRANSFER IS REJECTED.
												
							// ----------------------------------------------------------------------------------------------
												
							// The below block only executes for ACCEPTING a TRANSFER
							
							else if (
									 (OTTransaction::pending == pServerTransaction->GetType())
									 &&
									 (OTItem::transfer == pOriginalItem->GetType())
									 )
							{
								// pItem contains the current user's attempt to accept the transfer located in theOriginalItem.
								// Now we have both items.
								OTIdentifier IDFromAccount(pOriginalItem->GetPurportedAccountID());
								OTIdentifier IDToAccount(pOriginalItem->GetDestinationAcctID());
								
								// I'm using the operator== because it exists.
								// If the ID on the "To" account from the original transaction does not
								// match the Acct ID of the client trying to accept the transaction...
								if (!(ACCOUNT_ID == IDToAccount))
								{
									OTLog::Error("Error: Destination account ID on the transaction does not match account ID of client transaction item.\n");
								} 
								
								// -------------------------------------------------------------------
								
								// The 'from' outbox is loaded to remove the outgoing transfer, since it has been accepted.
								// The 'from' inbox is loaded in order to put a notice of this acceptance for the sender's records.
								OTLedger	theFromOutbox(IDFromAccount, SERVER_ID),	// Sender's *OUTBOX*
											theFromInbox(IDFromAccount, SERVER_ID);		// Sender's *INBOX*
								
								bool bSuccessLoadingInbox	= theFromInbox.LoadInbox();
								bool bSuccessLoadingOutbox	= theFromOutbox.LoadOutbox();
								
								// --------------------------------------------------------------------
								
								// THE FROM INBOX -- We are adding an item here (acceptance of transfer),
								// so we will create this inbox if we have to, so we can add that record to it.
								
								if (true == bSuccessLoadingInbox)
									bSuccessLoadingInbox	= theFromInbox.VerifyAccount(m_nymServer);
								else
									bSuccessLoadingInbox	= theFromInbox.GenerateLedger(IDFromAccount, SERVER_ID, OTLedger::inbox, true); // bGenerateFile=true
								
								
								// --------------------------------------------------------------------
								
								// THE FROM OUTBOX -- We are removing an item, so this outbox SHOULD already exist.
								
								if (true == bSuccessLoadingOutbox)
									bSuccessLoadingOutbox	= theFromOutbox.VerifyAccount(m_nymServer);
								else // If it does not already exist, that is an error condition. For now, log and fail.
									OTLog::Error("ERROR missing 'from' outbox in OTServer::NotarizeProcessInbox.\n");
								
								
								// ---------------------------------------------------------------------
								
								if (false == bSuccessLoadingInbox || false == bSuccessLoadingOutbox)
								{
									OTLog::Error("ERROR loading 'from' inbox or outbox in OTServer::NotarizeProcessInbox.\n");
								}
								else 
								{
									// Generate a new transaction number for the sender's inbox (to notice him of acceptance.)
									long lNewTransactionNumber = 0;
									IssueNextTransactionNumber(m_nymServer, lNewTransactionNumber, false); // bStoreTheNumber = false
									
									// Generate a new transaction... (to notice the sender of acceptance.)
									OTTransaction * pInboxTransaction	= OTTransaction::GenerateTransaction(theFromInbox, OTTransaction::transferReceipt,
																											 lNewTransactionNumber);
									
									// Here we give the sender (by dropping into his inbox) a copy of my acceptance of
									// his transfer, including the transaction number of my acceptance of his transfer.
									pInboxTransaction->SetReferenceString(strInReferenceTo);
									pInboxTransaction->SetReferenceToNum(pItem->GetTransactionNum());	// Right now this has the 'accept the transfer' transaction number.
																										// It could be changed to the original transaction number, as a better
																										// receipt for the original sender. TODO? Decisions....
									
									// Now we have created a new transaction from the server to the sender's inbox
									// Let's sign it and add to his inbox.
									pInboxTransaction->SignContract(m_nymServer);
									pInboxTransaction->SaveContract();
									
									// At this point I have theInbox ledger, theFromOutbox ledger, theFromINBOX ledger,
									// and theAccount.  So I should remove the appropriate item from each ledger, and
									// add the acceptance to the sender's inbox, and credit the account....
									
									// First try to credit the amount to the account...
									if (theAccount.Credit(pOriginalItem->GetAmount()))
									{
										// Add a transfer receipt to the sender's inbox, containing the "accept" transaction as the ref string. 
										// (to notify him that his transfer was accepted; once he accepts it, the trans# can be removed from his issued list.)
										//
										theFromInbox.	AddTransaction(*pInboxTransaction);								
										
										// The original item carries the transaction number that the original
										// sender used to generate the transfer in the first place. This is the number
										// by which that transaction is available in the sender's outbox.
										//
										// Then ANOTHER transaction was created, by the server, in order to put
										// a pending transfer into the recipient's inbox. This has its own transaction
										// number, generated by the server at that time.
										//
										// So we remove the original transfer from the sender's outbox using the
										// transaction number on the original item, and we remove the pending transfer
										// from the recipient's inbox using the transaction number from the pending
										// transaction.
										
										// UPDATE: These two transactions correspond to each other, so I am now creating
										// them with the same transaction number. As you can see, this makes them easy
										// to remove as well.
										theFromOutbox.	RemoveTransaction(pServerTransaction->GetTransactionNum());
										theInbox.		RemoveTransaction(pServerTransaction->GetTransactionNum());
										
										// Release any signatures that were there before (Old ones won't
										// verify anymore anyway, since the content has changed.)
										theInbox.		ReleaseSignatures();
										theAccount.		ReleaseSignatures();
										theFromInbox.	ReleaseSignatures();
										theFromOutbox.	ReleaseSignatures();
										
										// Sign all of them.
										theInbox.		SignContract(m_nymServer);
										theAccount.		SignContract(m_nymServer);
										theFromInbox.	SignContract(m_nymServer);
										theFromOutbox.	SignContract(m_nymServer);
										
										theInbox.		SaveContract();
										theAccount.		SaveContract();
										theFromInbox.	SaveContract();
										theFromOutbox.	SaveContract();
										
										// Save all of them.
										theInbox.		SaveInbox();
										theAccount.		SaveAccount();
										theFromInbox.	SaveInbox();
										theFromOutbox.	SaveOutbox();
										
										// Now we can set the response item as an acknowledgement instead of the default (rejection)
										// otherwise, if we never entered this block, then it would still be set to rejection, and the
										// new items would never have been added to the inbox/outboxes, and those files, along with
										// the account file, would never have had their signatures released, or been re-signed or 
										// re-saved back to file.  The debit failed, so all of those other actions would fail also.
										// BUT... if the message comes back with acknowledgement--then all of these actions must have
										// happened, and here is the server's signature to prove it.
										// Otherwise you get no items and no signature. Just a rejection item in the response transaction.
										pResponseItem->SetStatus(OTItem::acknowledgement);
									}
									else 
									{
										delete pInboxTransaction; pInboxTransaction = NULL;
										OTLog::Error("Unable to credit account in OTServer::NotarizeProcessInbox.\n");
									}
								} // outbox was successfully loaded
							}// its type is OTItem::transfer
						}// loaded original item from string
						else 
						{
							OTLog::Error("Error loading original item from inbox transaction.\n");
						}
					}
					else 
					{
						OTLog::vError("Error finding original transaction that client is trying to accept: %ld\n",
								pItem->GetReferenceToNum());
					}
					
					// sign the response item before sending it back (it's already been added to the transaction above)
					// Now, whether it was rejection or acknowledgement, it is set properly and it is signed, and it
					// is owned by the transaction, who will take it from here.
					pResponseItem->SignContract(m_nymServer);
					pResponseItem->SaveContract();					
				}
				else 
				{
//					OTString strItemType;
//					pItem->GetTypeString(strItemType);
//
//					OTLog::vError("Error, unexpected OTItem::itemType in OTServer::NotarizeProcessInbox: %s\n", 
//								  strItemType.Get());
				} // if type == ACCEPT, REJECT, DISPUTE
			} // for LOOP (each item)
			
		} // else (balance agreement verified.)
		
		// I put this here so it's signed/saved whether the balance agreement itself was successful OR NOT.
		pResponseBalanceItem->SignContract(m_nymServer);
		pResponseBalanceItem->SaveContract();
		
	} // Balance Agreement item found.
	
	// -------------------------------------------------
	
	tranOut.ReleaseSignatures();
	tranOut.SignContract(m_nymServer);
	tranOut.SaveContract();

	// -------------------------------------------------
	
	
	OTString strPath; // SAVE THE RECEIPT TO LOCAL STORAGE (for dispute resolution.)
	
	// On the server side, response will only have chance to succeed if balance agreement succeeds first.
	// Therefore, you will never see successful response but failed balance, since it would stop at the
	// balance and response itself would remain failed with no chance of changing.
	//
	// Thus, "success" must be when balance succeeded and transaction succeeded,
	// and "failure" must be when balance succeeded but transaction failed.
	//
	// If NEITHER succeeded, then there is no point recording it to a file, now is there?
	
	const OTString strAcctID(ACCOUNT_ID);

	if (tranOut.GetSuccess())
	{
		// Balance agreement was a success, AND process inbox was a success.
		// Therefore, remove any relevant issued numbers from theNym, and save.
		for (int i = 0; i < theTempNym.GetIssuedNumCount(SERVER_ID); i++)
		{
			long lTemp = theTempNym.GetIssuedNum(SERVER_ID, i);
			
			theNym.RemoveIssuedNum(m_nymServer, m_strServerID, lTemp, false); // bSave = false (saved immediately below)
		}
		
		theNym.SaveSignedNymfile(m_nymServer);
		
		//-------------------------------------------
		
		strPath.Format((char*)"%s.success", strAcctID.Get());
	}
	else
		strPath.Format((char*)"%s.fail", strAcctID.Get());
	
	const char * szFoldername = OTLog::ReceiptFolder();
	
	// Save the receipt. (My outgoing transaction including the client's signed request that triggered it.)
	tranOut.SaveContract(szFoldername, strPath.Get());	
}





bool OTServer::ValidateServerIDfromUser(OTString & strServerID)
{
	static bool bFirstTime = true;
	
	if (bFirstTime)
	{
		bFirstTime=false;
		
		// This part is now done when the server XML file is first loaded
//		if (!m_nymServer.Loadx509CertAndPrivateKey())
//		{
//			OTLog::Error("Error loading server certificate and keys.\n");
//		}
//		else {
//			OTLog::Error("Success loading server certificate and keys.\n");
//		}

		//TODO..  Notice after calling Loadx509CertAndPrivateKey, I do not call
		// VerifyPseudonym immediately after, like the client does. That's because
		// the client's ID is a hash of his public key, so that function compares
		// the two.
		//
		// But the server ID is a hash of the SERVER CONTRACT. Which will NOT match
		// the hash of the server public key.
		//
		// Ideally the server will load the contract, and then EXTRACT the public key
		// from the contract, and then use it to verify the signature on the contract,
		// and THEN hash the contract, to get the ServerID, 
		
		// Here's basically what I need to add:  m_ServerContract
		// 
		// ServerContract.SetFilename("server contract file")
		// ServerContract.LoadContract()
		// ServerContract.VerifyContractID()
		// if (success)
		//    ServerContract.VerifySignature(m_nymServer);
		// if (success)
		//    SUCCESS LOADING SERVER CERTIFICATES AND KEYS.
	}
	
	
	if (m_strServerID == strServerID)
	{
		return true;
	}
	
	return false;
}	





		
OTServer::OTServer()
{
	// This will be set when the server main xml file is loaded. For now, initialize to 0.
	m_lTransactionNumber = 0;
	
	m_pServerContract = NULL;
	
	m_bShutdownFlag = false;	// If I ever set this to true, then the caller will shutdown gracefully.	
								// (Caller must regularly check the flag and shutdown when it sees the change.)
}


OTServer::~OTServer()
{
	if (m_pServerContract)
		delete m_pServerContract;
	
	m_pServerContract = NULL;
}




bool OTServer::ProcessUserCommand(OTMessage & theMessage, OTMessage & msgOut, OTClientConnection * pConnection/*=NULL*/)
{	
	// Validate the server ID, to keep users from intercepting a valid requst
	// and sending it to the wrong server.
	if (false == ValidateServerIDfromUser(theMessage.m_strServerID))
	{
		OTLog::Error("Invalid server ID sent in command request.\n");
		return false;
	}
	else {
		OTLog::Error("Received valid Server ID with command request.\n");
	}

	OTPseudonym theNym(theMessage.m_strNymID);
	
	//**********************************************************************************************
	 
	// This command is special because the User sent his public key, not just his ID.
	// We have to verify the two together.
	//
	// At this point the user doesn't even have an account, so there is no public key
	// to look up from the database.
	//
	// If the ServerID in the reply matches the ID calculated from the Server Contract,
	// that means the user, without asking for the server's public key, can just extract
	// the public key from the contract from which the serverID was first calculated. (The
	// ID is a hash of the contract.)
	//
	// In other words, the user reads a contract. It's signed. The signature is verified
	// by a public key that is embedded in the contract. If the server, a URL also embedded in
	// the contract, acknowledges the ServerID, then the user can encrypt everything to the
	// public key in the contract, without asking the server for a copy of that key.
	//
	// Only the private key who signed that contract will be able to read the communications from
	// the user.
	//
	// I definitely have to build in an option for x509 certs to be used in lieu of public keys.
	// Otherwise the key is not ever revokable -- yet it's in a contract!  What is the issuer supposed
	// to do if that key is stolen? Make a public announcement?
	//
	// In such a case, the issuer would have to put a "check this URL to make sure contract still good"
	// variable into the contract so that the users have the chance to make sure the contract is still
	// good and the contract's private key hasn't been stolen. Well guess what? That's what x509 does.
	// Therefore the appropriate solution is for the server to support x509s, and to look up the authority
	// and verify certs, so that users have recourse in the event their private key is stolen. (They can
	// just use their Cert to issue a new public key, which the transaction server would be smart enough
	// to use, once the certificate authority signs off on it. (Since the user uses an x509 from a 
	// specific authority, then I can trust that whatever that authority says, that user wanted it to say.)
	// Without knowing the authority itself, I can now trust it because the user has asked me to trust it.
	// Fair enough!
	//
	// Similarly a user should be able to use his x509 Cert instead of his public key, and the server
	// should verify that cert whenever it's used to make sure it's up to date.  This takes the
	// problem off of the user's hands by way of a trusted authority.
	//
	// In fact this transaction server is really just a transaction VERIFIER. It's just another form
	// of trusted 3rd party. Just like Verisign is an authority who ceritifies an identity, so this
	// server is an authority who certifies a transaction. It's like a timestamping server. In fact
	// it should have timestamping built in as one of the functions.
	//
	// Transactions do not actually occur on the server, per se. They occur between the USERS.
	// All the server does it certify that the numbers are correct. It's like accounting software.
	// Ultimately the users are the ones making a transaction, and they are the ones who are 
	// responsible to back up their promises in real life and potentially in court. All the software
	// does is CERTIFY that the users DID make certain agreements at certain times, and digitally sign
	// those certifications.
	//
	// Thus, this server is very similar to Verisign. It is a trusted 3rd party who users can trust
	// to authenticate their transactions. Instead of authenticating certifications like Verisign does,
	// it authenticates transactions.
	//
	// UPDATE: May not want x509's after all, since it provides an opening for governments to 
	// serve warrants on the authority site and switch certs whenever they want to (BAD THING!)
	//
	if (theMessage.m_strCommand.Compare("checkServerID"))
	{
		OTLog::vOutput(0, "\n==> Received a checkServerID message. Processing...\n");
		
		OTAsymmetricKey & nymPublicKey = (OTAsymmetricKey &)theNym.GetPublicKey();
		
		bool bIfNymPublicKey = 
		nymPublicKey.SetPublicKey(theMessage.m_strNymPublicKey, true/*bEscaped*/);
		
		if (bIfNymPublicKey)
		{
			// Now the Nym has his public key set. Let's compare it to a hash of his ID (should match)
			if (theNym.VerifyPseudonym())
			{
				OTLog::vOutput(0, "Pseudonym verified! The Nym ID is a perfect hash of the public key.\n");
				
				if (theMessage.VerifySignature(theNym)) 
				{
					OTLog::vOutput(0, "Signature verified! The message WAS signed by "
							"the Nym\'s Private Key.\n");
					
					
					// This is only for verified Nyms, (and we're verified in here!) We do this so that 
					// we have the option later to encrypt the replies back to the client...(using the 
					// client's public key that we set here.)
					if (NULL != pConnection)
						pConnection->SetPublicKey(theMessage.m_strNymPublicKey);
					
					
					UserCmdCheckServerID(theNym, theMessage, msgOut);

					return true;
				}
				else 
				{
					OTLog::vOutput(0, "Signature failed!\nThe message was NOT signed by the Nym, OR the "
							"message was changed after signing.\n");
					return false;
				}
				
			}
			else
			{
				OTLog::vOutput(0, "Pseudonym failed to verify. Hash of public key doesn't match "
						"Nym ID that was sent.\n");
				return false;
			}
		}
		else {
			OTLog::Error("Failure reading Nym's public key from message.\n");
			return false;
		}
	}
	
	// This command is also special because again, the User sent his public key, not just his ID.
	// We have to verify the two together.
	else if (theMessage.m_strCommand.Compare("createUserAccount"))
	{
		OTLog::Output(0, "\n==> Received a createUserAccount message. Processing...\n");
		
		OTAsymmetricKey & nymPublicKey = (OTAsymmetricKey &)theNym.GetPublicKey();
		bool bIfNymPublicKey = 
		nymPublicKey.SetPublicKey(theMessage.m_strNymPublicKey, true/*bEscaped*/);
		
		if (bIfNymPublicKey)
		{
			// Now the Nym has his public key set. Let's compare it to a hash of his ID (should match)
			if (theNym.VerifyPseudonym())
			{
				OTLog::Output(0, "Pseudonym verified! The Nym ID is a perfect hash of the public key.\n");
				
				if (theMessage.VerifySignature(theNym)) 
				{
					OTLog::Output(0, "Signature verified! The message WAS signed by "
							"the Nym\'s Private Key.\n");
					//
					// Look up the NymID and see if it's already a valid user account.
					// 
					// If it is, then we can't very well create it twice, can we?
					theNym.SetIdentifier(theMessage.m_strNymID);
					
					OTLog::Output(0, "Verifying account doesn't already exist... (IGNORE ERRORS HERE ABOUT FAILURE OPENING FILES)\n");

					// Prepare to send success or failure back to user.
					// (1) set up member variables 
					msgOut.m_strCommand		= "@createUserAccount";	// reply to createUserAccount
					msgOut.m_strNymID		= theMessage.m_strNymID;	// UserID
					msgOut.m_strServerID	= m_strServerID;	// ServerID, a hash of the server contract.
					msgOut.m_bSuccess		= false;
					
					// We send the user's message back to him, ascii-armored,
					// as part of our response.
					OTString tempInMessage;
					theMessage.SaveContract(tempInMessage);
					msgOut.m_ascInReferenceTo.SetString(tempInMessage);
					

					if (false == theNym.LoadSignedNymfile(m_nymServer) && false == theNym.LoadPublicKey())
					{
						// Good -- this means the account doesn't already exist.
						// Let's create it.

						// First we save the createUserAccount message in the accounts folder...
						if (msgOut.m_bSuccess = theMessage.SaveContract(OTLog::UserAcctFolder(), theMessage.m_strNymID.Get()))
						{
							OTLog::Output(0, "Success saving new user account verification file.\n");
							
							OTString strPath(theMessage.m_strNymID.Get());
							
							// Next we save the public key in the pubkeys folder...
							if (msgOut.m_bSuccess = theNym.SavePublicKey(strPath))
							{
								// This is only for verified Nyms, (and we're verified in here!) We do this so that 
								// we have the option later to encrypt the replies back to the client...(using the 
								// client's public key that we set here.)
								if (NULL != pConnection)
									pConnection->SetPublicKey(theMessage.m_strNymPublicKey);
								
								OTLog::vOutput(0, "Success saving new nym\'s public key file.\n");
								
								OTIdentifier theNewNymID, SERVER_ID(m_strServerID);
								theNym.GetIdentifier(theNewNymID);
								
								OTLedger theNymbox(theNewNymID, theNewNymID, SERVER_ID);
								
								bool bSuccessLoadingNymbox	= theNymbox.LoadNymbox();
								
								if (true == bSuccessLoadingNymbox) // that's strange, this user didn't exist... but maybe I allow people to drop notes anyway, so then the nymbox might already exist, with usage tokens and messages inside....
									bSuccessLoadingNymbox	= theNymbox.VerifyAccount(m_nymServer); // make sure it's all good.
								else
								{
									bSuccessLoadingNymbox	= theNymbox.GenerateLedger(theNewNymID, SERVER_ID, OTLedger::nymbox, true); // bGenerateFile=true
									
									if (bSuccessLoadingNymbox)
									{
										bSuccessLoadingNymbox	= theNymbox.SignContract(m_nymServer);
										
										if (bSuccessLoadingNymbox)
										{
											bSuccessLoadingNymbox = theNymbox.SaveContract();
											
											if (bSuccessLoadingNymbox)
												bSuccessLoadingNymbox	= theNymbox.SaveNymbox();
										}
									}
								}
								
								// by this point, the nymbox DEFINITELY exists -- or not. (generation might have failed, or verification.)
								
								if (false == bSuccessLoadingNymbox)
								{
									OTLog::vError("Error during user account registration. Failed verifying or generating nymbox for user:\n%s\n",
												 theMessage.m_strNymID.Get());
								}
								else if (msgOut.m_bSuccess = theNym.SaveSignedNymfile(m_nymServer))
								{
									OTLog::vOutput(0, "Success saving new Nymfile. (User account fully created.)\n");

									
									// (2) Sign the Message 
									msgOut.SignContract(m_nymServer);		
									
									// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
									//
									// FYI, SaveContract takes m_xmlUnsigned and wraps it with the signatures and ------- BEGIN  bookends
									// If you don't pass a string in, then SaveContract saves the new version to its member, m_strRawFile
									msgOut.SaveContract();

									return true;
								}
								else 
								{
									// (2) Sign the Message 
									msgOut.SignContract(m_nymServer);		
									
									// (3) Save the Message
									msgOut.SaveContract();

									return true;
								}
							}
							else
							{
								OTLog::Error("Error saving new user account verification file.\n");
								// (2) Sign the Message 
								msgOut.SignContract(m_nymServer);		
								
								// (3) Save the Message 
								msgOut.SaveContract();
								
								return true;
							}
						}
						else {
							OTLog::Error("Error creating Account in OTServer::ProcessUserCommand.\n");
							// (2) Sign the Message 
							msgOut.SignContract(m_nymServer);		
							
							// (3) Save the Message 
							msgOut.SaveContract();
							
							return true;
						}
					}
					else
					{
						OTLog::vOutput(0, "Error: User attempted to create account that already exists: %s\n", 
								theMessage.m_strNymID.Get());
						// (2) Sign the Message 
						msgOut.SignContract(m_nymServer);		
						
						// (3) Save the Message
						msgOut.SaveContract();
						
						return true;
					}

					return true;
				}
				else 
				{
					OTLog::Output(0, "Signature failed!\nThe message was NOT signed by the Nym, OR the "
							"message was changed after signing.\n");
					return false;
				}
				
			}
			else
			{
				OTLog::Output(0, "Pseudonym failed to verify. Hash of public key doesn't match "
						"Nym ID that was sent.\n");
				return false;
			}
		}
		else {
			OTLog::Error("Failure reading Nym's public key from message.\n");
			return false;
		}
	}

	
	// ------------------------------------------------------------------------------------------
	
		
	// Look up the NymID and see if it's a valid user account.
	// 
	// If we didn't receive a public key (above)
	// Or read one from our files (below)
	// ... then we'd have no way of validating the requests.
	//
	// If it is, then we read the public key from that Pseudonym and use it to verify any
	// requests bearing that NymID.
	
	// I appear to already be setting this variable near the top of the function.
	// No idea why I'm setting it twice, probably an oversight. TODO: remove.
	theNym.SetIdentifier(theMessage.m_strNymID);
	
	// For special cases where the Nym sending the transaction has the same public key as
	// the server itself. (IE it IS the server Nym, then we'd want to use the already-loaded
	// server nym object instead of loading a fresh one, so the two don't overwrite each other.)
	//
	bool bNymIsServerNym = (m_strServerUserID.Compare(theMessage.m_strNymID) ? true : false);
	OTPseudonym * pNym = &theNym;
	
	if (bNymIsServerNym)
		pNym = &m_nymServer;
	
	if (!bNymIsServerNym && (false == theNym.LoadPublicKey()))
	{
		OTLog::vError("Failure loading Nym public key: %s\n", theMessage.m_strNymID.Get());
		return false;
	}
	
	// Okay, the file was read into memory and Public Key was successfully extracted!
	// Next, let's use that public key to verify (1) the NymID and (2) the signature
	// on the message that we're processing.

	if (pNym->VerifyPseudonym())
	{
		OTLog::Output(0, "Pseudonym verified! The Nym ID is a perfect hash of the public key.\n");
		
		// So far so good. Now let's see if the signature matches...
		if (theMessage.VerifySignature(*pNym)) 
		{
			OTLog::Output(0, "Signature verified! The message WAS signed by "
					"the Nym\'s Private Key.\n");
			
			// Now we might as well load up the rest of the Nym.
			// Notice I use the || to only load the nymfile if it's NOT the server Nym.
			if (bNymIsServerNym || theNym.LoadSignedNymfile(m_nymServer))
			{
				OTLog::Output(1,  "Successfully loaded Nymfile into memory.\n");
				
				// *****************************************************************************
				// ENTERING THE INNER SANCTUM OF SECURITY. If the user got all the way to here,
				// Then he has passed multiple levels of security, and all commands below will
				// assume the Nym is secure, validated, and loaded into memory for use.
				//
				// But still need to verify the Request Number for all other commands except 
				// Get Request Number itself...
				// *****************************************************************************
				
				// Request numbers start at 1 (currently).
				long lRequestNumber = 0;
				
				if (false == pNym->GetCurrentRequestNum(m_strServerID, lRequestNumber))
				{
					OTLog::Output(0, "Nym file request number doesn't exist. Apparently first-ever request to server--but everything checks out. "
							"(Shouldn't this request number have been created already when the NymFile was first created???????\n");
					// FIRST TIME!  This account has never before made a single request to this server.
					// The above call always succeeds unless the number just isn't there for that server.
					// Therefore, since it's the first time, we'll create it now:
					pNym->IncrementRequestNum(m_nymServer, m_strServerID);

					// Call it again so that lRequestNumber is set to 1 also
					if (pNym->GetCurrentRequestNum(m_strServerID, lRequestNumber))
					{
						OTLog::Output(0, "Created first request number in Nym file, apparently first-ever request. "
								"(Shouldn't this have been created already when the NymFile was first created???????\n");
					}
					else {
						OTLog::Error("ERROR creating first request number in Nym file.\n");	
						return false;
					}
				}
				
				// At this point, I now have the current request number for this nym in lRequestNumber
				// Let's compare it to the one that was sent in the message... (This prevents attackers 
				// from repeat-sending intercepted messages to the server.)
				if (false == theMessage.m_strCommand.Compare("getRequest"))		   // IF it's NOT a getRequest CMD, (therefore requires a request number)
				{
					if (lRequestNumber != atol(theMessage.m_strRequestNum.Get()))  // AND the request number attached does not match what we just read out of the file...
					{
						OTLog::vOutput(0, "Request number sent in this message %ld does not match the one in the file! (%ld)\n",
								atol(theMessage.m_strRequestNum.Get()), lRequestNumber);
						return false;
					}
					else // it's not a getRequest CMD, and the request number sent DOES match what we read out of the file!!
					{
						OTLog::vOutput(0, "Request number sent in this message %ld DOES match the one in the file!\n", lRequestNumber);
						
						// At this point, it is some OTHER command (besides getRequest)
						// AND the request number verifies, so we're going to increment
						// the number, and let the command process.
						pNym->IncrementRequestNum(m_nymServer, m_strServerID);
						
						// *****************************************************************************
						// **INSIDE** THE INNER SANCTUM OF SECURITY. If the user got all the way to here,
						// Then he has passed multiple levels of security, and all commands below will
						// assume the Nym is secure, validated, and loaded into memory for use. They can
						// also assume that the request number has been verified on this message.
						// EVERYTHING checks out.
						// *****************************************************************************
						
						// NO RETURN HERE!!!! ON PURPOSE!!!!
					}

				}
				else  // If you entered this else, that means it IS a getRequest command 
					  // So we allow it to go through without verifying this step, and without incrementing the counter.
				{
					//pNym->IncrementRequestNum(m_strServerID); // commented out cause this is the one case where we DON'T increment this number.
														   // We allow the user to get the number, we DON'T increment it, and now the user
														   // can send it on his next request for some other command, and it will verify 
														   // properly. This prevents repeat messages.

					// NO RETURN HERE!!!! ON PURPOSE!!!!
				}

					
				// At this point, we KNOW that it is EITHER a GetRequest command, which doesn't require a request number,
				// OR it was some other command, but the request number they sent in the command MATCHES the one that we
				// just read out of the file.
				
				// Therefore, we can process ALL messages below this 
				// point KNOWING that the Nym is properly verified in all ways.
				// No messages need to worry about verifying the Nym, or about 
				// dealing with the Request Number. It's all handled in here.
				

				
				// Get the public key from theNym, and set it into the connection.
				// This is only for verified Nyms, (and we're verified in here!) We do this so that 
				// we have the option later to encrypt the replies back to the client...(using the 
				// client's public key that we set here.)
				if (NULL != pConnection)
					pConnection->SetPublicKey(pNym->GetPublicKey());
			}
			else {
				OTLog::vError("Error loading Nymfile: %s\n", theMessage.m_strNymID.Get());
				return false;
			}

		}
		else 
		{
			OTLog::Output(0, "Signature failed!\nThe message was NOT signed by the Nym, OR the "
					"message was changed after signing.\n");
			return false;
		}
		
	}
	else
	{
		OTLog::Output(0, "Pseudonym failed to verify. Hash of public key doesn't match "
				"Nym ID that was sent.\n");
		return false;
	}
	
	
	// ----------------------------------------------------------------------------------------
	
	
	// If you made it down this far, that means the Pseudonym verifies! The message is legit.
	//
	// (Server ID was good, NymID is a valid hash of User's public key, and the Signature on
	// the message was signed by the user's private key.)
	//
	// Now we can process the message.
	//
	// All the commands below here, it is assumed that the user account exists and is
	// referenceable via theNym. (An OTPseudonym object.)
	//
	// ALL commands below can assume the Nym is real, and that the NymID and Public Key are
	// available for use -- and that they verify -- without having to check again and again.
	
	
	if (theMessage.m_strCommand.Compare("getRequest")) // This command is special because it's the only one that doesn't require a request number.
													   // All of the other commands, below, will fail above if the proper request number isn't included
													   // in the message.  They will already have failed by this point if they didn't verify.
	{
		OTLog::Output(0, "\n==> Received a getRequest message. Processing...\n");
		
		UserCmdGetRequest(*pNym, theMessage, msgOut);
		
		return true;
	}
	else if (theMessage.m_strCommand.Compare("getTransactionNum"))
	{
		OTLog::Output(0, "\n==> Received a getTransactionNum message. Processing...\n");
		
		UserCmdGetTransactionNum(*pNym, theMessage, msgOut);
		
		return true;
	}
	else if (theMessage.m_strCommand.Compare("checkUser"))
	{
		OTLog::Output(0, "\n==> Received a checkUser message. Processing...\n");
		
		UserCmdCheckUser(*pNym, theMessage, msgOut);
		
		return true;
	}
	else if (theMessage.m_strCommand.Compare("sendUserMessage"))
	{
		OTLog::Output(0, "\n==> Received a sendUserMessage message. Processing...\n");
		
		UserCmdSendUserMessage(*pNym, theMessage, msgOut);
		
		return true;
	}
	else if (theMessage.m_strCommand.Compare("createAccount"))
	{
		OTLog::Output(0, "\n==> Received a createAccount message. Processing...\n");
		
		UserCmdCreateAccount(*pNym, theMessage, msgOut);
		
		return true;
	}
	else if (theMessage.m_strCommand.Compare("issueAssetType"))
	{
		OTLog::Output(0, "\n==> Received an issueAssetType message. Processing...\n");
		
		UserCmdIssueAssetType(*pNym, theMessage, msgOut);
		
		return true;
	}
	else if (theMessage.m_strCommand.Compare("issueBasket"))
	{
		OTLog::Output(0, "\n==> Received an issueBasket message. Processing...\n");
		
		UserCmdIssueBasket(*pNym, theMessage, msgOut);
		
		return true;
	}
	else if (theMessage.m_strCommand.Compare("exchangeBasket"))
	{
		OTLog::Output(0, "\n==> Received an exchangeBasket message. Processing...\n");
		
		UserCmdExchangeBasket(*pNym, theMessage, msgOut);
		
		return true;
	}
	else if (theMessage.m_strCommand.Compare("notarizeTransactions"))
	{
		OTLog::Output(0, "\n==> Received a notarizeTransactions message. Processing...\n");
		
		UserCmdNotarizeTransactions(*pNym, theMessage, msgOut);
		
		return true;
	}
	else if (theMessage.m_strCommand.Compare("getNymbox"))
	{
		OTLog::Output(0, "\n==> Received a getNymbox message. Processing...\n");
		
		UserCmdGetNymbox(*pNym, theMessage, msgOut);
		
		return true;
	}
	else if (theMessage.m_strCommand.Compare("getInbox"))
	{
		OTLog::Output(0, "\n==> Received a getInbox message. Processing...\n");
		
		UserCmdGetInbox(*pNym, theMessage, msgOut);
		
		return true;
	}
	else if (theMessage.m_strCommand.Compare("getOutbox"))
	{
		OTLog::Output(0, "\n==> Received a getOutbox message. Processing...\n");
		
		UserCmdGetOutbox(*pNym, theMessage, msgOut);
		
		return true;
	}
	else if (theMessage.m_strCommand.Compare("processNymbox"))
	{
		OTLog::Output(0, "\n==> Received a processNymbox message. Processing...\n");
		
		UserCmdProcessNymbox(*pNym, theMessage, msgOut);
		
		return true;
	}
	else if (theMessage.m_strCommand.Compare("processInbox"))
	{
		OTLog::Output(0, "\n==> Received a processInbox message. Processing...\n");
		
		UserCmdProcessInbox(*pNym, theMessage, msgOut);
		
		return true;
	}
	else if (theMessage.m_strCommand.Compare("getAccount"))
	{
		OTLog::Output(0, "\n==> Received a getAccount message. Processing...\n");
		
		UserCmdGetAccount(*pNym, theMessage, msgOut);
		
		return true;
	}
	else if (theMessage.m_strCommand.Compare("getContract"))
	{
		OTLog::Output(0, "\n==> Received a getContract message. Processing...\n");
		
		UserCmdGetContract(*pNym, theMessage, msgOut);
		
		return true;
	}
	else if (theMessage.m_strCommand.Compare("getMint"))
	{
		OTLog::Output(0, "\n==> Received a getMint message. Processing...\n");
		
		UserCmdGetMint(*pNym, theMessage, msgOut);
		
		return true;
	}
	else
	{
		OTLog::vError("Unknown command type in the XML, or missing payload, in ProcessMessage.\n");
		return false;
	}
}





bool OTServer::GetConnectInfo(OTString & strHostname, int & nPort)
{
	if (NULL == m_pServerContract)
		return false;
	
	return m_pServerContract->GetConnectInfo(strHostname, nPort);
}











































































