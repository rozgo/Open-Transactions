/************************************************************
 *    
 *  OTCronItem.cpp
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


#include "irrxml/irrXML.h"

using namespace irr;
using namespace io;



#include "OTCronItem.h"
#include "OTAgreement.h"
#include "OTPaymentPlan.h"
#include "OTTrade.h"
#include "OTLog.h"

// Base class for OTTrade and OTAgreement and OTPaymentPlan.
// OTCron contains lists of these for regular processing.


// static -- class factory.
//
// I just realized, I don't have to use this only for CronItems.
// If I wanted to, I could put ANY Open-Transactions class in here,
// if there was some need for it, and it would work just fine right here.
// Like if I wanted to have different Token types for different cash
// algorithms. All I have to do is change the return type.
OTCronItem * OTCronItem::NewCronItem(const OTString & strCronItem)
{
	static char		buf[45] = "";
	OTCronItem *	pItem = NULL;
	
	if (!strCronItem.Exists())
		return NULL;
	
	OTString strContract(strCronItem);
	
	strContract.reset(); // for sgets
	buf[0] = 0; // probably unnecessary.
	bool bGotLine = strContract.sgets(buf, 40);

	if (!bGotLine)
		return NULL;
	
	OTString strFirstLine(buf);
	strContract.reset(); // set the "file" pointer within this string back to index 0.
	
	// Now I feel pretty safe -- the string I'm examining is within
	// the first 45 characters of the beginning of the contract, and
	// it will NOT contain the escape "- " sequence. From there, if
	// it contains the proper sequence, I will instantiate that type.
	if (!strFirstLine.Exists() || strFirstLine.Contains("- -"))
		return NULL;
		
	if (strFirstLine.Contains("-----BEGIN SIGNED AGREEMENT-----"))  // this string is 32 chars long.
	{	pItem = new OTAgreement();		OT_ASSERT(NULL != pItem); }
	
	else if (strFirstLine.Contains("-----BEGIN SIGNED PAYMENT PLAN-----"))  // this string is 35 chars long.
	{	pItem = new OTPaymentPlan();	OT_ASSERT(NULL != pItem); }
	
	else if (strFirstLine.Contains("-----BEGIN SIGNED TRADE-----"))  // this string is 28 chars long.
	{	pItem = new OTTrade();			OT_ASSERT(NULL != pItem); }
	
	
	// The string didn't match any of the options in the factory.
	if (NULL == pItem)
		return NULL;
	
	// Does the contract successfully load from the string passed in?
	if (pItem->LoadContractFromString(strContract))
		return pItem;
	else
		delete pItem;
	
	
	return NULL;
}


// OTCron calls this regularly, which is my chance to expire, etc.
// Child classes will override this, AND call it (to verify valid date range.)
//
// Return False:	REMOVE this Cron Item from Cron.
// Return True:		KEEP this Cron Item on Cron (for now.)
//
bool OTCronItem::ProcessCron()
{
	OT_ASSERT(m_pCron);
	
	// I call IsExpired() here instead of VerifyCurrentDate(). The Cron Item will stay on
	// Cron even if it is NOT YET valid. But once it actually expires, this will remove it.
	if (IsExpired())
	{
		OTLog::vOutput(3, "Cron: Expired %s.\n", m_strContractType.Get());
		return false;
	}
	
	// As far as this code is concerned, the item can stay on cron for now. Return true.
	return true;
}



OTCronItem * OTCronItem::LoadCronReceipt(const long & lTransactionNum)
{
	OTString strFilename;
	strFilename.Format("%ld.crn", lTransactionNum);
	
	const char * szFoldername	= OTLog::CronFolder();
	const char * szFilename		= strFilename.Get();
		
	// --------------------------------------------------------------------
	
	if (false == OTDB::Exists(szFoldername, szFilename))
	{
		OTLog::vError("OTCronItem::LoadCronReceipt: File does not exist: %s%s%s\n", 
					  szFoldername, OTLog::PathSeparator(), szFilename);
		return NULL;
	}
	
	// --------------------------------------------------------------------
	//
	OTString strFileContents(OTDB::QueryPlainString(szFoldername, szFilename)); // <=== LOADING FROM DATA STORE.
	
	if (strFileContents.GetLength() < 2)
	{
		OTLog::vError("OTCronItem::LoadCronReceipt: Error reading file: %s%s%s\n", 
					  szFoldername, OTLog::PathSeparator(), szFilename);
		return NULL;
	}
	else
		return OTCronItem::NewCronItem(strFileContents);
}


// When first adding anything to Cron, a copy needs to be saved in a folder somewhere.
// (Just for our records.) For example, before I start updating the status on any Trade,
// I have already saved the user's original Trade object (from his request) to a folder.
// Now I have the freedom to ReleaseSignatures on the Trade and re-sign it with the
// server's Nym as it updates over time.  The user cannot challenge the Trade because
// the server has the original copy on file and sends it with all receipts.

bool OTCronItem::SaveCronReceipt()
{
	OTString strFilename;
	strFilename.Format("%ld.crn", GetTransactionNum());
	
	const char * szFoldername	= OTLog::CronFolder();
	const char * szFilename		= strFilename.Get();
	
	// --------------------------------------------------------------------
	
	if (OTDB::Exists(szFoldername, szFilename))
	{
		OTLog::vError("Cron Record exists for transaction %ld %s%s%s,\nyet attempted to record it again.\n",
					  GetTransactionNum(), szFoldername, OTLog::PathSeparator(), szFilename);
		return false;
	}
	
	// --------------------------------------------------------------------
	
	OTString strFinal;
	SaveContract(strFinal);
	
	bool bSaved = OTDB::StorePlainString(strFinal.Get(), szFoldername, szFilename);
	
	if (!bSaved)
	{
		OTLog::vError("OTCronItem::SaveCronReceipt: Error saving file: %s%s%s\n", 
					  szFoldername, OTLog::PathSeparator(), szFilename);
		return false;
	}
	// --------------------------------------------------------------------
		
	return bSaved;
}



OTCronItem::OTCronItem() : OTTrackable()
{
	SetLastProcessDate(0); // not stored, just used while running.
	m_pCron			= NULL; // NOT responsible to delete this pointer. Just storing it for convenience.
	InitCronItem();
}


OTCronItem::OTCronItem(const OTIdentifier & SERVER_ID, const OTIdentifier & ASSET_ID) : 
			OTTrackable(SERVER_ID, ASSET_ID)
{
	SetLastProcessDate(0); // not stored, just used while running.
	m_pCron			= NULL; // NOT responsible to delete this pointer. Just storing it for convenience.
	InitCronItem();
}

OTCronItem::OTCronItem(const OTIdentifier & SERVER_ID, const OTIdentifier & ASSET_ID,
					   const OTIdentifier & ACCT_ID, const OTIdentifier & USER_ID) : 
			OTTrackable(SERVER_ID, ASSET_ID, ACCT_ID, USER_ID)
{
	SetLastProcessDate(0); // not stored, just used while running.
	m_pCron			= NULL; // NOT responsible to delete this pointer. Just storing it for convenience.
	InitCronItem();
}


OTCronItem::~OTCronItem()
{
// No need to call Release() here, it's handled by the framework.	
}

void OTCronItem::InitCronItem()
{
	m_strContractType.Set("CRONITEM"); // in practice should never appear. Child classes will overwrite.
	
	SetCreationDate(0);
	SetProcessInterval(1); // Default for any cron item is to execute once per second. todo put this in config file.
}


void OTCronItem::Release()
{
	// If there were any dynamically allocated objects, clean them up here.
	
	OTTrackable::Release(); // since I've overridden the base class, I call it now...
	
	// Then I call this to re-initialize everything
	InitCronItem();
}


/*
// return -1 if error, 0 if nothing, and 1 if the node was processed.
int OTCronItem::ProcessXMLNode(irr::io::IrrXMLReader*& xml)
{
	
}


void OTCronItem::UpdateContents()
{
	
}


bool OTCronItem::SaveContractWallet(std::ofstream & ofs)
{
	return true;
}
*/
