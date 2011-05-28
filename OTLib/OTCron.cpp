/***************************************************************
 *    
 *  OTCron.cpp
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


// OTCron has a list of OTCronItems. (Really subclasses of that such as OTTrade and OTAgreement.)

#include <map>
#include <list>

#include <cstring>


#include "irrxml/irrXML.h"

using namespace irr;
using namespace io;

using namespace std;

#include "OTStorage.h"


#include "OTLog.h"

#include "OTCron.h"
#include "OTCronItem.h"

#include "OTOffer.h"
#include "OTTrade.h"
#include "OTMarket.h"
#include "OTPaymentPlan.h"




// Make sure Server Nym is set on this cron object before loading or saving, since it's
// used for signing and verifying..
bool OTCron::LoadCron()
{
	const char * szFoldername	= OTLog::CronFolder();
	const char * szFilename		= "OT-CRON.crn"; // todo stop hardcoding filenames.
	
	OT_ASSERT(NULL != GetServerNym());
		
	// --------------------------------------------------------------------
	
	bool bSuccess = false;

	bSuccess = LoadContract(szFoldername, szFilename);
		
	if (bSuccess)
		bSuccess = VerifySignature(*GetServerNym());
	
	return bSuccess;
}


bool OTCron::SaveCron()
{
	const char * szFoldername	= OTLog::CronFolder();
	const char * szFilename		= "OT-CRON.crn"; // todo stop hardcoding filenames.
	
	OT_ASSERT(NULL != GetServerNym());
	
	// ------------------------------------------------------------------------
	
	ReleaseSignatures();

	// Sign it, save it internally to string, and then save that out to the file.
	if (!SignContract(*m_pServerNym) || !SaveContract() || !SaveContract(szFoldername, szFilename))
	{
		OTLog::vError("Error saving main Cronfile:\n%s%s%s\n", szFoldername,
					  OTLog::PathSeparator(), szFilename);
		return false;
	}
	else
		return true;	
}




int OTCron::GetTransactionCount() const
{
	if (m_listTransactionNumbers.empty())
		return 0;

	return m_listTransactionNumbers.size();
}

void OTCron::AddTransactionNumber(const long & lTransactionNum)
{
	m_listTransactionNumbers.push_back(lTransactionNum);
}



// Once this starts returning 0, OTCron can no longer process trades and
// payment plans until the server object replenishes this list.
long OTCron::GetNextTransactionNumber()
{
	if (m_listTransactionNumbers.empty())
		return 0;
	
	long lTransactionNum = m_listTransactionNumbers.front();
	
	m_listTransactionNumbers.pop_front();
	
	return lTransactionNum;
}





// return -1 if error, 0 if nothing, and 1 if the node was processed.
int OTCron::ProcessXMLNode(irr::io::IrrXMLReader*& xml)
{
	OT_ASSERT(NULL != GetServerNym());
	
	int nReturnVal = 0;
	
	// Here we call the parent class first.
	// If the node is found there, or there is some error,
	// then we just return either way.  But if it comes back
	// as '0', then nothing happened, and we'll continue executing.
	//
	// -- Note you can choose not to call the parent if
	// you don't want to use any of those xml tags.
	// As I do below, in the case of OTAccount.
	//if (nReturnVal = OTContract::ProcessXMLNode(xml))
	//	return nReturnVal;
	
	
	if (!strcmp("cron", xml->getNodeName())) 
	{		
		m_strVersion		= xml->getAttributeValue("version");
		
		// ---------------------
		
		const OTString	strServerID(xml->getAttributeValue("serverID"));
		
		m_SERVER_ID.SetString(strServerID);
		
		// ---------------------
		
		OTLog::vOutput(0, "\n\nLoading an OTCron object. ServerID:\n%s\n", 
					   strServerID.Get());
				
		nReturnVal = 1;
	}
	else if (!strcmp("transactionNum", xml->getNodeName()))
	{
		long lTransactionNum = 0;
		
		lTransactionNum	= atol(xml->getAttributeValue("value"));
		
		OTLog::vOutput(1, "Transaction Number %ld available for Cron.\n",
					   lTransactionNum);
		
		AddTransactionNumber(lTransactionNum); // This doesn't save to disk. Make sure to save Cron when it changes.

		nReturnVal = 1;
	}	
	
	else if (!strcmp("cronItem", xml->getNodeName())) 
	{		
		OTString strData;
		
		if (!LoadEncodedTextField(xml, strData) || !strData.Exists())
		{
			OTLog::Error("Error in OTCron::ProcessXMLNode: cronItem field without value.\n");
			return (-1); // error condition
		}
		else 
		{
			OTCronItem * pItem = OTCronItem::NewCronItem(strData);
			
			if (NULL == pItem)
			{
				OTLog::Error("Unable to create cron item from data in cron file.\n");
				return (-1);
			}
			
			if (AddCronItem(*pItem, false))	// bSaveReceipt=false. The receipt is only saved once: When item FIRST added to cron.
			{								// But here, the item was ALREADY in cron, and is merely being loaded from disk. Thus,
				// it would be wrong to try to create the "original record" as if it were brand new
				// and still had the user's signature on it. (Once added to Cron, the signatures are 
				// released and the SERVER signs it from there. That's why the user's version is saved
				// as a receipt in the first place -- so we have a record of the user's authorization.)
				OTLog::Output(2, "Successfully loaded cron item and added to list.\n");
			}
			else 
			{
				OTLog::Error("Though loaded successfully, unable to add cron item (from cron file) to cron list.\n");
				delete pItem;
				pItem = NULL;
				return (-1);
			}
		}
		
		nReturnVal = 1;
	}
	
	else if (!strcmp("market", xml->getNodeName()))
	{
		const OTString	strMarketID(xml->getAttributeValue("marketID"));
		const OTString	strAssetID(xml->getAttributeValue("assetID"));
		const OTString	strCurrencyID(xml->getAttributeValue("currencyID"));
		
		const long		lScale = atol(xml->getAttributeValue("marketScale"));
		
		const OTIdentifier	ASSET_ID(strAssetID), CURRENCY_ID(strCurrencyID);
		
		OTLog::vOutput(1, "Loaded cron entry for Market:\n%s.\n", strMarketID.Get());
		
		// LoadMarket() needs this info to do its thing.
		OTMarket * pMarket = new OTMarket(m_SERVER_ID, ASSET_ID, CURRENCY_ID, lScale);
		
		OT_ASSERT(NULL != pMarket);
		
		pMarket->SetCronPointer(*this); // This way every Market has a pointer to Cron.

		//	AddMarket normally saves to file, but we don't want that when we're LOADING from file, now do we?
		if (!pMarket->LoadMarket() || !pMarket->VerifySignature(*GetServerNym()) ||
			!AddMarket(*pMarket, false)) // bSaveFile=false: don't save this file WHILE loading it!!! 
		{
			OTLog::Error("Somehow error while loading, verifying, or adding market while loading Cron file.\n");
			delete pMarket; pMarket = NULL;
			return (-1);
		}
		else 
		{
			OTLog::Output(1, "Loaded market entry from cronfile, and also loaded the market file itself.\n");
		}
		nReturnVal = 1;
	}
	
	return nReturnVal;	
}


void OTCron::UpdateContents()
{
	// I release this because I'm about to repopulate it.
	m_xmlUnsigned.Release();
	
	m_xmlUnsigned.Concatenate("<?xml version=\"%s\"?>\n\n", "1.0");		
	
	// -------------------------------------------------------------
	
	const OTString	SERVER_ID(m_SERVER_ID);
	
	m_xmlUnsigned.Concatenate("<cron\n version=\"%s\"\n"
							  " serverID=\"%s\""
							  " >\n\n", 
							  m_strVersion.Get(),
							  SERVER_ID.Get());	
		
	// -------------------------------------------------------------
	
	// Save the Market entries (the markets themselves are saved in a markets folder.)
	OTMarket * pMarket = NULL;
	for (mapOfMarkets::iterator ii = m_mapMarkets.begin(); ii != m_mapMarkets.end(); ++ii)
	{
		pMarket = (*ii).second;
		
		OT_ASSERT(NULL != pMarket);
		
		OTIdentifier	MARKET_ID(*pMarket);
		OTString		str_MARKET_ID(MARKET_ID);
		
		OTString		str_ASSET_ID(pMarket->GetAssetID());
		OTString		str_CURRENCY_ID(pMarket->GetCurrencyID());
		
		m_xmlUnsigned.Concatenate("<market\n marketID=\"%s\"\n"
								  " assetID=\"%s\"\n"
								  " currencyID=\"%s\"\n"
								  " marketScale=\"%ld\""
								  " >\n\n", 
								  str_MARKET_ID.Get(),
								  str_ASSET_ID.Get(),
								  str_CURRENCY_ID.Get(),
								  pMarket->GetScale());	
	}		
	
	// -------------------------------------------------------------
	
	
	// Save the Cron Items
	OTCronItem * pItem = NULL;
	for (mapOfCronItems::iterator ii = m_mapCronItems.begin(); ii != m_mapCronItems.end(); ++ii)
	{
		pItem = (*ii).second;
		
		OT_ASSERT(NULL != pItem);
		
		OTString strItem(*pItem);		// Extract the cron item contract into string form.
		OTASCIIArmor ascItem(strItem);	// Base64-encode that for storage.
		
		m_xmlUnsigned.Concatenate("<cronItem>\n%s</cronItem>\n\n", ascItem.Get());
	}		
	
	// -------------------------------------------------------------
	
	// Save the transaction numbers.
	
	long lTransactionNumber = 0;
	
	for (listOfTransactionNumbers::iterator iii = m_listTransactionNumbers.begin(); 
		 iii != m_listTransactionNumbers.end(); ++iii)
	{	
		lTransactionNumber = *iii;
		
		m_xmlUnsigned.Concatenate("<transactionNum value=\"%ld\" />\n\n", 
						   lTransactionNumber);
	} // for

	// -------------------------------------------------------------

	m_xmlUnsigned.Concatenate("</cron>\n");							
}





// Make sure to call this regularly so the CronItems get a chance to process and expire.
void OTCron::ProcessCronItems()
{
	if (!m_bIsActivated)
		return;	// No Cron processing until Cron is activated.
	
	if (GetTransactionCount() < 10) // todo stop hardcoding.
	{
		OTLog::Error("Cron is out of transaction numbers!");
		return;
	}
	
	bool bNeedToSave = false;
	
	// loop through the cron items and tell each one to ProcessCron().
	// If the item returns true, that means leave it on the list. Otherwise,
	// if it returns false, that means "it's done: remove it."
	OTCronItem * pItem = NULL;
	
	for (mapOfCronItems::iterator ii = m_mapCronItems.begin(); ii != m_mapCronItems.end(); )
	{
		pItem = (*ii).second;
		
		OT_ASSERT(NULL != pItem);
		
		// returns true if should stay on the list.
		// returns false if should be removed from the list.
		if (!pItem->VerifySignature(*m_pServerNym) || (false == pItem->ProcessCron())) 
		{
			m_mapCronItems.erase(ii++);
			delete pItem;
			pItem = NULL;
			
			bNeedToSave = true; // We'll save to file at the bottom if anything was removed.
		} 
		else	// the special i++ and ++i arrangement here allows me to erase an item
		{		// from the list WHILE iterating through it  :-)   (Supposedly.)
			++ii;
		}
	}
	
	// Items were removed from Cron -- Save to storage!
	if (bNeedToSave)
		SaveCron();
}




// OTCron IS responsible for cleaning up theItem, and takes ownership.
// So make SURE it is allocated on the HEAP before you pass it in here, and
// also make sure to delete it again if this call fails!
bool OTCron::AddCronItem(OTCronItem & theItem, bool bSaveReceipt/*=true*/)
{	
	OT_ASSERT(NULL != GetServerNym());
	
	// See if there's something else already there with the same transaction number.
	mapOfCronItems::iterator ii = m_mapCronItems.find(theItem.GetTransactionNum());
	
	// If it's not already on the list, then add it...
	if ( ii == m_mapCronItems.end() )
	{
		// If I've been instructed to save the receipt, and theItem did NOT successfully save the receipt,
		// then return false.
		// This will happen if filesystem problems, but it will also happen if the cron item WAS ALREADY THERE.
		// I don't want to save over it. If I'm trying to save over one that is already there, then THAT is the
		// real problem.
		if (bSaveReceipt && !theItem.SaveCronReceipt())
		{
			OTLog::Error("Error saving receipt while adding new Cronitem to Cron.\n");
			return false;
		}
		
		m_mapCronItems[theItem.GetTransactionNum()] = &theItem;
		theItem.SetCronPointer(*this); // This way every CronItem has a pointer to momma.

		bool bSuccess = true;
		
		// When an item is added to Cron for the first time, a copy of it is saved to the
		// cron folder, and it has the user's original signature on it. (If it's a Trade, 
		// it also contains an Offer with the user's original signature.) This occurs
		// wherever this function is called with bSaveReceipt=true.
		//
		if (bSaveReceipt)	// This executes only the first time that an item is added to Cron. 
							// (versus when it's just being reloaded from file and added back to the internal list.)
		{
			// Now that a copy of the cronitem is safely stored, I can release the signature on it
			// and sign it with the Server's Nym instead. That way I can use the server to verify
			// all cron and market-related activity from here on out.
			theItem.ReleaseSignatures();
			theItem.SignContract(*GetServerNym());
			theItem.SaveContract();	
			
			// Since we added an item to the Cron, we SAVE it. 
			bSuccess = SaveCron();
			
			if (bSuccess) 
				OTLog::Output(3, "New Cronitem has been added to Cron.\n");
			else 				
				OTLog::Error("Error saving while adding new Cronitem to Cron.\n");
		}
		
		return bSuccess; 
	}
	// Otherwise, if it was already there, log an error.
	else 
	{
		OTLog::vError("Attempt to add CronItem with pre-existing transaction number: %ld\n",
					  theItem.GetTransactionNum());
	}
	
	return false;
}




bool OTCron::RemoveCronItem(long lTransactionNum) // if false, item wasn't found.
{
	// See if there's something there with that transaction number.
	mapOfCronItems::iterator ii = m_mapCronItems.find(lTransactionNum);
	
	// If it's not already on the list, then there's nothing to remove.
	if ( ii == m_mapCronItems.end() )
	{
		OTLog::vError("Attempt to remove non-existent CronItem from OTCron. Transaction #: %ld\n",
					  lTransactionNum);
		return false;
	}
	// Otherwise, if it WAS already there, remove it properly.
	else 
	{
		OTCronItem * pItem = (*ii).second;
		
		OT_ASSERT(NULL != pItem);
		
		m_mapCronItems.erase(ii);
		delete pItem;
		
		// An item has been removed from Cron. SAVE.		
		return SaveCron();		
	}
	
	return false;
}



// Look up a transaction by transaction number and see if it is in the ledger.
// If it is, return a pointer to it, otherwise return NULL.
OTCronItem * OTCron::GetCronItem(long lTransactionNum)
{
	// See if there's something there with that transaction number.
	mapOfCronItems::iterator ii = m_mapCronItems.find(lTransactionNum);
	
	if ( ii == m_mapCronItems.end() )
	{
		// nothing found.
		return NULL;
	}
	// Found it!
	else 
	{
		OTCronItem * pItem = (*ii).second;
		
		OT_ASSERT((NULL != pItem));
		
		if (pItem->GetTransactionNum() == lTransactionNum)
			return pItem;
		else 
			OTLog::vError("Expected CronItem with transaction number %ld, but found %ld inside. Bad data?\n",
						  lTransactionNum, pItem->GetTransactionNum());
	}
	
	return NULL;
}



// ----------------------------------------------------------


// OTCron IS responsible for cleaning up theMarket, and takes ownership.
// So make SURE it is allocated on the HEAP before you pass it in here, and
// also make sure to delete it again if this call fails!
bool OTCron::AddMarket(OTMarket & theMarket, bool bSaveMarketFile/*=true*/)
{	
	OT_ASSERT(NULL != GetServerNym());

	theMarket.SetCronPointer(*this); // This way every Market has a pointer to Cron.
	
	OTIdentifier	MARKET_ID(theMarket);
	OTString		str_MARKET_ID(MARKET_ID);
	std::string		std_MARKET_ID = str_MARKET_ID.Get();
	
	// See if there's something else already there with the same market ID.
	mapOfMarkets::iterator ii = m_mapMarkets.find(std_MARKET_ID);
	
	// If it's not already on the list, then add it...
	if ( ii == m_mapMarkets.end() )
	{
		// If I've been instructed to save the market, and Cron did NOT successfully save the market
		//  (to its own file), then return false.  This will happen if filesystem problems.
		if (bSaveMarketFile && !theMarket.SaveMarket())
		{
			OTLog::vError("Error saving market file while adding new Market to Cron:\n%s\n",
						 std_MARKET_ID.c_str());
			return false;
		}
		
		m_mapMarkets[std_MARKET_ID] = &theMarket;
		
		bool bSuccess = true;
		
		// When Cron serializes, it stores a list of all its markets in the main cron file.
		// The actual markets themselves serialize separately to the market folder.
		//
		if (bSaveMarketFile)	// This executes only the first time that a market is added to Cron. 
			// (versus when it's just being reloaded from file and added back to the internal list.)
		{
			// Since we added a market to the Cron, we SAVE it. 
			bSuccess = SaveCron(); // If we're loading from file, and bSaveMarketFile is false, I don't want to save here. that's why it's in this block.
			
			if (bSuccess) 
				OTLog::Output(3, "New Market has been added to Cron.\n");
			else 				
				OTLog::Error("Error saving while adding new Market to Cron.\n");
		}
		
		return bSuccess; 
	}
	// Otherwise, if it was already there, log an error.
	else 
	{
		OTLog::vError("Attempt to add Market that was already there: %s\n", std_MARKET_ID.c_str());
	}
	
	return false;
}


bool OTCron::RemoveMarket(const OTIdentifier & MARKET_ID) // if false, market wasn't found.
{
	OTString		str_MARKET_ID(MARKET_ID);
	std::string		std_MARKET_ID = str_MARKET_ID.Get();
	
	// See if there's something there with that transaction number.
	mapOfMarkets::iterator ii = m_mapMarkets.find(std_MARKET_ID);
	
	// If it's not already on the list, then there's nothing to remove.
	if ( ii == m_mapMarkets.end() )
	{
		OTLog::vError("Attempt to remove non-existent Market from OTCron:\n%s\n",
					  std_MARKET_ID.c_str());
		return false;
	}
	// Otherwise, if it WAS already there, remove it properly.
	else 
	{
		OTMarket * pMarket = (*ii).second;
		
		OT_ASSERT(NULL != pMarket);
		
		m_mapMarkets.erase(ii);
		delete pMarket;
		
		// A market has been removed from Cron. SAVE.		
		return SaveCron();		
	}
	
	return false;
}


// Create it if it's not there.
OTMarket * OTCron::GetOrCreateMarket(const OTIdentifier & ASSET_ID, 
									 const OTIdentifier & CURRENCY_ID, const long & lScale)
{	
	OTMarket * pMarket = new OTMarket(GetServerID(), ASSET_ID, CURRENCY_ID, lScale);
	
	OT_ASSERT(NULL != pMarket);
	
	OTIdentifier MARKET_ID(*pMarket);
	
	OTMarket * pExistingMarket = GetMarket(MARKET_ID);
	
	// If it was already there, there's no need to create it.
	if (NULL != pExistingMarket)
	{
		delete pMarket; pMarket = NULL;
		return pExistingMarket;
	}
	
	// If we got this far, it means the Market does NOT already exist in this Cron.
	// So let's add it...
	bool bAdded = AddMarket(*pMarket, true); // bool bSaveMarketFile=true, since it was created new.

	if (bAdded)
	{
		OTLog::Output(0, "New market created and added to Cron.\n");
	}
	else 
	{
		OTLog::Error("Error trying to add new market to Cron.\n");
		delete pMarket;
		pMarket = NULL;
	}
	
	return pMarket;
}


// Look up a transaction by transaction number and see if it is in the ledger.
// If it is, return a pointer to it, otherwise return NULL.
OTMarket * OTCron::GetMarket(const OTIdentifier & MARKET_ID)
{
	OTString		str_MARKET_ID(MARKET_ID);
	std::string		std_MARKET_ID = str_MARKET_ID.Get();
	
	// See if there's something there with that transaction number.
	mapOfMarkets::iterator ii = m_mapMarkets.find(std_MARKET_ID);
	
	if ( ii == m_mapMarkets.end() )
	{
		// nothing found.
		return NULL;
	}
	// Found it!
	else 
	{
		OTMarket * pMarket = (*ii).second;
		
		OT_ASSERT((NULL != pMarket));
		
		const OTIdentifier	LOOP_MARKET_ID(*pMarket);
		const OTString		str_LOOP_MARKET_ID(LOOP_MARKET_ID);
		
		if (MARKET_ID == LOOP_MARKET_ID)
			return pMarket;
		else 
			OTLog::vError("Expected Market with ID:\n%s\n but found %s\n",
						  std_MARKET_ID.c_str(), str_LOOP_MARKET_ID.Get());
	}
	
	return NULL;
}


// ------------------------------------------------------------


OTCron::OTCron() : OTContract()
{
	m_bIsActivated = false;
	m_pServerNym	= NULL;  // just here for convenience, not responsible to cleanup this pointer.
	InitCron();
	OTLog::Output(3, "Finished calling InitCron.\n");
}

OTCron::OTCron(const OTIdentifier & SERVER_ID) : OTContract()
{
	m_bIsActivated = false;
	m_pServerNym	= NULL;  // just here for convenience, not responsible to cleanup this pointer.
	InitCron();
	
	SetServerID(SERVER_ID);
	OTLog::Output(3, "Finished calling InitCron.\n");
}

OTCron::OTCron(const char * szFilename) : OTContract()
{
	OT_ASSERT(NULL != szFilename);
	
	m_bIsActivated = false;
	m_pServerNym	= NULL;  // just here for convenience, not responsible to cleanup this pointer.
	InitCron();
	
	m_strFoldername.Set(OTLog::CronFolder());
	m_strFilename.Set(szFilename);
	OTLog::Output(3, "Finished calling InitCron.\n");
}



OTCron::~OTCron()
{
// no need to call Release() here, the framework will take care of it.	
}


void OTCron::InitCron()
{
	m_strContractType = "CRON";
}


void OTCron::Release()
{
	// If there were any dynamically allocated objects, clean them up here.
	while (!m_mapCronItems.empty())
	{		
		OTCronItem * pItem = m_mapCronItems.begin()->second;
		mapOfCronItems::iterator ii = m_mapCronItems.begin();
		m_mapCronItems.erase(ii);
		delete pItem;
		pItem = NULL;
	}
	
	while (!m_mapMarkets.empty())
	{
		OTMarket * pMarket = m_mapMarkets.begin()->second;
		mapOfMarkets::iterator ii = m_mapMarkets.begin();
		m_mapMarkets.erase(ii);
		delete pMarket;
		pMarket = NULL;		
	}
	
	
	OTContract::Release(); // since I've overridden the base class, I call it now...
	
	// Then I call this to re-initialize everything for myself.
	InitCron(); 		
}




bool OTCron::SaveContractWallet(std::ofstream & ofs)
{
	return true;
}

