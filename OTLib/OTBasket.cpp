/****************************************************************
 *    
 *  OTBasket.cpp
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

#include "OTStorage.h"


#include "OTBasket.h"
#include "OTLog.h"


// For generating a user request to exchange in/out of a basket.
// Assumes that SetTransferMultiple has already been called.
void OTBasket::AddRequestSubContract(const OTIdentifier & SUB_CONTRACT_ID, const OTIdentifier & SUB_ACCOUNT_ID)
{
	BasketItem * pItem = new BasketItem;
	
	OT_ASSERT_MSG(NULL != pItem, "Error allocating memory in OTBasket::AddRequestSubContract\n");
	
	pItem->SUB_CONTRACT_ID		= SUB_CONTRACT_ID;
	pItem->SUB_ACCOUNT_ID		= SUB_ACCOUNT_ID;
	
	// Minimum transfer amount is not set on a request. The server already knows its value.
	// Also there is no multiple on the item, only on the basket as a whole.
	// ALL items are multiplied by the same multiple. Even the basket amount itself is also.
	
	m_dequeItems.push_back(pItem);
}


// For generating a real basket
void OTBasket::AddSubContract(const OTIdentifier & SUB_CONTRACT_ID, long lMinimumTransferAmount)
{
	BasketItem * pItem = new BasketItem;
	
	OT_ASSERT_MSG(NULL != pItem, "Error allocating memory in OTBasket::AddSubContract\n");
	
	pItem->SUB_CONTRACT_ID			= SUB_CONTRACT_ID;
	// server adds this later. Client can't know it in advance.
//	pItem->SUB_ACCOUNT_ID			= SUB_ACCOUNT_ID; 
	pItem->lMinimumTransferAmount	= lMinimumTransferAmount;

	m_dequeItems.push_back(pItem);
}

BasketItem * OTBasket::At(int nIndex)
{
	if (nIndex < Count() && nIndex >= 0)
		return m_dequeItems.at(nIndex);
	
	return NULL;
}

int OTBasket::Count() const
{
	return m_dequeItems.size();
}


/* 
 struct BasketItem 
 {
 OTIdentifier SUB_CONTRACT_ID;
 OTIdentifier SUB_ACCOUNT_ID;
 long		lMinimumTransferAmount;
 
 BasketItem() { lMinimumTransferAmount = 0; }
 ~BasketItem();
 };

 */


// return -1 if error, 0 if nothing, and 1 if the node was processed.
int OTBasket::ProcessXMLNode(irr::io::IrrXMLReader*& xml)
{	
	if (!strcmp("currencyBasket", xml->getNodeName()))
	{		
		OTString strSubCount, strMinTrans;
		strSubCount			= xml->getAttributeValue("contractCount");
		strMinTrans			= xml->getAttributeValue("minimumTransfer"); 
		
		m_nSubCount			= atoi(strSubCount.Get());
		m_lMinimumTransfer	= atol(strMinTrans.Get()); 
		
		OTLog::Output(0, "Loading currency basket...\n");
		
		return 1;
	}
	else if (!strcmp("transferMultiple", xml->getNodeName()))
	{		
		OTString strTransferMultiple, strRequestAccountID;
		
		strTransferMultiple	= xml->getAttributeValue("value");
		strRequestAccountID	= xml->getAttributeValue("transferAccountID");
		
		m_nTransferMultiple	= atoi(strTransferMultiple.Get());
		m_RequestAccountID.SetString(strRequestAccountID);
		
		OTLog::vOutput(1, "Transfer multiple is %d. Target account is:\n%s\n", 
				m_nTransferMultiple, strRequestAccountID.Get());
		
		return 1;
	}
	else if (!strcmp("basketItem", xml->getNodeName()))
	{
		BasketItem * pItem = new BasketItem;
		
		OT_ASSERT_MSG(NULL != pItem, "Error allocating memory in OTBasket::ProcessXMLNode\n");
		
		OTString strMinTrans = xml->getAttributeValue("minimumTransfer");
		pItem->lMinimumTransferAmount	= atol(	strMinTrans.Get()	);
		
		OTString	strSubAccountID(xml->getAttributeValue("accountID")),
					strContractID(xml->getAttributeValue("assetID"));
		pItem->SUB_ACCOUNT_ID.SetString(strSubAccountID); 
		pItem->SUB_CONTRACT_ID.SetString(strContractID);
		
		m_dequeItems.push_back(pItem);

		OTLog::Output(1, "Loaded basket item.\n");
		
		return 1;
	}
	
	return 0;	
}

void OTBasket::UpdateContents() // Before transmission or serialization, this is where the basket updates its contents 
{		
	// I release this because I'm about to repopulate it.
	m_xmlUnsigned.Release();
	
	m_xmlUnsigned.Concatenate("<currencyBasket contractCount=\"%d\"\n" 
							  " minimumTransfer=\"%ld\" >\n\n", 
							  m_nSubCount, m_lMinimumTransfer);
	
	if (m_nTransferMultiple)
	{
		OTString strRequestAcctID(m_RequestAccountID);
		m_xmlUnsigned.Concatenate("<transferMultiple value=\"%d\"\n transferAccountID=\"%s\" />\n\n", 
								  m_nTransferMultiple, strRequestAcctID.Get());
	}
	
	for (int i = 0; i < Count(); i++)
	{
		BasketItem * pItem = m_dequeItems[i];
		
		OT_ASSERT_MSG(NULL != pItem, "Error allocating memory in OTBasket::UpdateContents\n");
		
		OTString strAcctID(pItem->SUB_ACCOUNT_ID), strContractID(pItem->SUB_CONTRACT_ID);
		
		m_xmlUnsigned.Concatenate("<basketItem minimumTransfer=\"%ld\"\n"
								" accountID=\"%s\"\n"
								" assetID=\"%s\" />\n\n", 
								pItem->lMinimumTransferAmount,
								m_bHideAccountID ? "" : strAcctID.Get(),
								strContractID.Get());
	}
	
	m_xmlUnsigned.Concatenate("</currencyBasket>\n");					
}

// Most contracts calculate their ID by hashing the Raw File (signatures and all).
// The Basket only hashes the unsigned contents, and only with the account IDs removed.
// This way, the basket will produce a consistent ID across multiple different servers.
void OTBasket::CalculateContractID(OTIdentifier & newID)
{	
	m_bHideAccountID	= true;

	// Produce a version of the file without account IDs (which are different from server to server.)
	UpdateContents();
	
	newID.CalculateDigest(m_xmlUnsigned);

	// Put it back the way it was.
	m_bHideAccountID	= false;
	UpdateContents();
}


OTBasket::OTBasket(int nCount, long lMinimumTransferAmount) :  OTContract()
{
	InitBasket();
	
	m_nSubCount			= nCount;
	m_lMinimumTransfer	= lMinimumTransferAmount;
}

OTBasket::OTBasket() :  OTContract()
{
	InitBasket();
}

OTBasket::~OTBasket()
{
	ReleaseBasket();
}
	
void OTBasket::InitBasket()
{
	m_nSubCount			= 0;
	m_lMinimumTransfer	= 0;
	m_nTransferMultiple	= 0;
	m_bHideAccountID	= false;
}

void OTBasket::ReleaseBasket()
{
	BasketItem * pItem = NULL;
	
	m_RequestAccountID.Release();
	
	while (!m_dequeItems.empty()) 
	{
		pItem = m_dequeItems.front();
		m_dequeItems.pop_front();
		delete pItem;
	}

	m_nSubCount			= 0;
	m_lMinimumTransfer	= 0;
	m_nTransferMultiple	= 0;
	m_bHideAccountID	= false;
}

	

bool OTBasket::SaveContractWallet(std::ofstream & ofs)
{
	return true;
}


