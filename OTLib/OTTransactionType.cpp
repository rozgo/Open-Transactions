/************************************************************************************
 *    
 *  OTTransactionType.cpp
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


#include "OTStorage.h"

#include "OTTransactionType.h"
#include "OTLog.h"



// keeping constructor private in order to force people to use the other constructors and 
// therefore provide the requisite IDs.
OTTransactionType::OTTransactionType() : OTContract()
{
 // this function is private to prevent people from using it.	
	// Should never actually get called.
	
	InitTransactionType(); // Just in case.
}


OTTransactionType::OTTransactionType(const OTIdentifier & theUserID, const OTIdentifier & theAccountID, 
									 const OTIdentifier & theServerID)
											: OTContract(theAccountID)
{
	InitTransactionType();
	
	// m_ID			= theAccountID  -- This happens in OTContract, no need to do it twice.
	m_ServerID		= theServerID;
	m_AcctUserID	= theUserID;
	
	// do NOT set m_AcctID and m_AcctServerID here.  Let the child classes LOAD them or GENERATE them.
}

OTTransactionType::OTTransactionType(const OTIdentifier & theUserID, const OTIdentifier & theAccountID, 
									 const OTIdentifier & theServerID, long lTransactionNum)
											: OTContract(theAccountID)
{
	// This initializes m_lTransactionNum, so it must come FIRST. 
	// In fact, that's the general rule with this function.
	InitTransactionType();
	
	// m_ID				= theAccountID  -- This happens in OTContract, no need to do it twice.
	m_ServerID			= theServerID;
	m_AcctUserID		= theUserID;
	m_lTransactionNum	= lTransactionNum;

	// do NOT set m_AcctID and m_AcctServerID here.  Let the child classes LOAD them or GENERATE them.
}



void OTTransactionType::InitTransactionType()
{
	m_lTransactionNum			= 0;
	m_lInReferenceToTransaction	= 0;
}

OTTransactionType::~OTTransactionType()
{
	// No need to call Release() here, it's called already by the framework.
	
}

void OTTransactionType::Release()
{
	// If there were any dynamically allocated objects, clean them up here.
		
	OTContract::Release(); // since I've overridden the base class, I call it now...
	
	// Then I call this to re-initialize everything for myself.
	InitTransactionType(); 		
}


void OTTransactionType::GetReferenceString(OTString & theStr) const
{
	m_ascInReferenceTo.GetString(theStr);
}

void OTTransactionType::SetReferenceString(const OTString & theStr)
{
	m_ascInReferenceTo.SetString(theStr);
}



bool OTTransactionType::SaveContractWallet(std::ofstream & ofs)
{
	return true;
}


// Make sure this contract checks out. Very high level. 
// Verifies ID and signature.
// I do NOT call VerifyOwner() here, because the server may
// wish to verify its signature on this account, even though
// the server may not be the actual owner.
// So if you wish to VerifyOwner(), then call it.
bool OTTransactionType::VerifyAccount(OTPseudonym & theNym)
{
	// Make sure that the supposed Contract ID that was set is actually
	// a hash of the contract file, signatures and all.
	if (false == VerifyContractID())
	{
		OTLog::Error("Error verifying account ID in OTTransactionType::VerifyAccount\n");
		return false;
	}
	else if (false == VerifySignature(theNym))
	{
		OTLog::Error("Error verifying signature in OTTransactionType::VerifyAccount.\n");
		return false;
	}
	
	OTLog::Output(1, "\nWe now know that...\n"
			"1) The expected Account ID matches the ID that was found on the object.\n"
			"2) The SIGNATURE VERIFIED on the object.\n\n");
	return true;
}

bool OTTransactionType::VerifyContractID()
{	
	//m_AcctID contains the number we read from the xml file
	//we can compare it to the existing and actual identifier.
	
	// m_AcctID  contains the "IDENTIFIER" of the object, according to the xml file. 
	// 
	// Meanwhile m_ID contains the same identifier, except it was generated.
	//
	// Now let's compare the two and make sure they match...
	
	// Also, for this class, we compare ServerID as well.  They go hand in hand.
	
	// I use the == operator here because there is no != operator at this time.
	// That's why you see the ! outside the parenthesis.
	if (!(m_ID == m_AcctID) || !(m_ServerID == m_AcctServerID))
	{
		OTString str1(m_ID), str2(m_AcctID), str3(m_ServerID), str4(m_AcctServerID);
		OTLog::vError("Identifiers do NOT match in OTTransactionType::VerifyContractID.\n"
				"m_ID: %s\n m_AcctID: %s\n m_ServerID: %s\n m_AcctServerID: %s\n",
				str1.Get(), str2.Get(), str3.Get(), str4.Get());
		return false;
	}
	else {
//		OTString str1(m_AcctID), str2(m_AcctServerID);
//		OTLog::vError("Expected Account ID and Server ID both *SUCCESSFUL* match to "
//				"IDs in the xml:\n Account ID:\n%s\n ServerID:\n%s\n"
//				"-----------------------------------------------------------------------------\n",
//				str1.Get(), str2.Get());
		return true;
	}
}




// need to know the transaction number of this transaction? Call this.
long OTTransactionType::GetTransactionNum() const
{
	return m_lTransactionNum; 
}	


void OTTransactionType::SetTransactionNum(const long lTransactionNum)
{
	m_lTransactionNum = lTransactionNum;
}


// need to know the transaction number of this transaction? Call this.
long OTTransactionType::GetReferenceToNum() const
{
	return m_lInReferenceToTransaction; 
}	


void OTTransactionType::SetReferenceToNum(const long lTransactionNum)
{
	m_lInReferenceToTransaction = lTransactionNum;
}

