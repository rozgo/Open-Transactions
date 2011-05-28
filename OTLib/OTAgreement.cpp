/**************************************************************
 *    
 *  OTAgreement.cpp
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


// OTAgreement is derived from OTCronItem.  It handles re-occuring billing.

#include "OTStorage.h"

#include "OTIdentifier.h"
#include "OTAgreement.h"
#include "OTLog.h"





// OTCron calls this regularly, which is my chance to expire, etc.
// Child classes will override this, AND call it (to verify valid date range.)
bool OTAgreement::ProcessCron()
{
	// END DATE --------------------------------
	// First call the parent's version (which this overrides) so it has
	// a chance to check its stuff. Currently it checks IsExpired().
	if (!OTCronItem::ProcessCron())
		return false;	// It's expired--removed it from Cron.
	
	
	// START DATE --------------------------------
	// Okay, so it's not expired. But might not have reached START DATE yet...
	if (!VerifyCurrentDate())
		return true;	// The Trade is not yet valid, so we return. BUT, we return 
						//  true, so it will stay on Cron until it BECOMES valid.
	
	
	// Process my Agreement-specific stuff below.--------------------------------
	
	
	return true;
}


// (Make sure to set Creation date here.)

bool OTAgreement::SetAgreement(const long & lTransactionNum,	const OTString & strConsideration,
							   const time_t & VALID_FROM/*=0*/,	const time_t & VALID_TO/*=0*/)
{
	// Set the Transaction Number...
	SetTransactionNum(lTransactionNum);

	// Set the Consideration memo...
	m_strConsideration.Set(strConsideration);

	// ------------------------------------------- 
	
	time_t CURRENT_TIME = time(NULL);
	
	// Set the Creation Date.
	SetCreationDate(CURRENT_TIME);

	// ------------------------------------------- 

	// The default "valid from" time is NOW.
	if (0 >= VALID_FROM) // if it's 0 or less, set to current time.
		SetValidFrom(CURRENT_TIME);
	else // Otherwise use whatever was passed in.
		SetValidFrom(VALID_FROM);

	// ------------------------------------------- 

	// The default "valid to" time is 0 (which means no expiration date / cancel anytime.)
	if (0 == VALID_TO) // VALID_TO is 0
	{
		SetValidTo(VALID_TO); // Keep it at zero then, so it won't expire.
	}
	else if (0 < VALID_TO) // VALID_TO is ABOVE zero...
	{
		if (VALID_TO < VALID_FROM) // If Valid-To date is EARLIER than Valid-From date...
		{
			long lValidTo = VALID_TO, lValidFrom = VALID_FROM;
			OTLog::vError("VALID_TO is earlier than VALID_FROM in SetAgreement: %ld, %ld\n", lValidTo, lValidFrom);
			return false;
		}
		
		SetValidTo(VALID_TO); // Set it to whatever it is, since it is now validated as higher than Valid-From.
	}
	else // VALID_TO is a NEGATIVE number... Error.
	{
		long lValidTo = VALID_TO;
		OTLog::vError("Negative value for valid_to in SetAgreement: %ld\n", lValidTo);
		return false;
	}

	// ------------------------------------------- 
	
	OTLog::Output(4, "Successfully performed SetAgreement()\n");
	
	return true;
}



OTAgreement::OTAgreement() : OTCronItem()
{
	InitAgreement();
}

OTAgreement::OTAgreement(const OTIdentifier & SERVER_ID, const OTIdentifier & ASSET_ID) :
			OTCronItem(SERVER_ID, ASSET_ID)
{
	InitAgreement();
}


OTAgreement::OTAgreement(const OTIdentifier & SERVER_ID,			const OTIdentifier & ASSET_ID,
						 const OTIdentifier & SENDER_ACCT_ID,		const OTIdentifier & SENDER_USER_ID,
						 const OTIdentifier & RECIPIENT_ACCT_ID,	const OTIdentifier & RECIPIENT_USER_ID) :
			OTCronItem(SERVER_ID, ASSET_ID, SENDER_ACCT_ID, SENDER_USER_ID)
{
	InitAgreement();
	
	SetRecipientAcctID(RECIPIENT_ACCT_ID);
	SetRecipientUserID(RECIPIENT_USER_ID);
}

OTAgreement::~OTAgreement()
{
	// no need to call Release(), the framework will call it.
}


void OTAgreement::InitAgreement()
{
	m_strContractType = "AGREEMENT";
	
}

// the framework will call this at the right time.
void OTAgreement::Release()
{
	// If there were any dynamically allocated objects, clean them up here.
	m_RECIPIENT_ACCT_ID.Release();	
	m_RECIPIENT_USER_ID.Release();
	
	m_strConsideration.Release();
	
	OTCronItem::Release(); // since I've overridden the base class, I call it now...
	
	// Then I call this to re-initialize everything
	InitAgreement();
}





// return -1 if error, 0 if nothing, and 1 if the node was processed.
int OTAgreement::ProcessXMLNode(irr::io::IrrXMLReader*& xml)
{
	return 1;
}


void OTAgreement::UpdateContents()
{
	
}


bool OTAgreement::SaveContractWallet(std::ofstream & ofs)
{
	return true;
}

