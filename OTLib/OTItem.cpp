/************************************************************************************
 *    
 *  OTItem.cpp
 *  
 *		Open Transactions:  Library, Protocol, Server, and Test Client
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



#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cstring>

#include "irrxml/irrXML.h"

using namespace irr;
using namespace io;


#include "OTIdentifier.h"
#include "OTAccount.h"
#include "OTPayload.h"
#include "OTMessage.h"
#include "OTStringXML.h"

#include "OTTransactionType.h"
#include "OTTransaction.h"
#include "OTItem.h"
#include "OTLog.h"






void OTItem::ReleaseItems()
{
	OTItem * pItem = NULL;
	
	while (!m_listItems.empty())
	{
		pItem = m_listItems.front();
		m_listItems.pop_front();
		delete pItem;
		pItem = NULL;
	}
}



// You have to allocate the item on the heap and then pass it in as a reference. 
// OTTransaction will take care of it from there and will delete it in destructor.
void OTItem::AddItem(OTItem & theItem) 
{ 
	m_listItems.push_back(&theItem);  
} 


// While processing a transaction, you may wish to query it for items of a certain type.
OTItem * OTItem::GetItem(int nIndex) 
{
	OTItem * pItem = NULL;
	
	int nTempIndex = (-1);
	
	for (listOfItems::iterator ii = m_listItems.begin(); ii != m_listItems.end(); ++ii)
	{
		pItem = *ii;
		
		OT_ASSERT(NULL != pItem);
		
		nTempIndex++; // first iteration this becomes 0 here.
		
		if (nTempIndex == nIndex)
			return pItem;
	}
	
	return NULL;
}









void OTItem::GetAttachment(OTString & theStr) const
{
	m_ascAttachment.GetString(theStr);
}

void OTItem::SetAttachment(const OTString & theStr)
{
	m_ascAttachment.SetString(theStr);
}



#define MINIMUM_CLEARTEXT_SIZE_OTASCIIARMOR	100

#define OTASSCIIARMOR_PADDING_TEXT  " IGNORE -- NOTE PADDING -- IGNORE -- NOTE PADDING \nIGNORE -- NOTE PADDING -- IGNORE -- NOTE PADDING \n"

void OTItem::SetNote(const OTString & theStr)
{
	if (theStr.Exists() && theStr.GetLength() > 2)
	{
		OTString theString(theStr);
		if (theStr.GetLength() < MINIMUM_CLEARTEXT_SIZE_OTASCIIARMOR)
		{
			OTString strPadding(OTASSCIIARMOR_PADDING_TEXT);
			
			theString.Concatenate(strPadding);
		}
		
		m_ascNote.SetString(theString);
	}
	else 
	{
		m_ascNote.Release();
	}

}

void OTItem::GetNote(OTString & theStr) const
{
	if (m_ascNote.GetLength() > 2)
	{
		m_ascNote.GetString(theStr);
		
		if (theStr.Contains(OTASSCIIARMOR_PADDING_TEXT))
			theStr.Truncate(theStr.GetLength() - MINIMUM_CLEARTEXT_SIZE_OTASCIIARMOR);
	}
	else 
	{
		theStr.Release();
	}

}
		



// this one is private (I hope to keep it that way.)
// probvably not actually. If I end up back here, it's because
// sometimes I dont' WANT to assign the stuff, but leave it blank
// because I'm about to load it.
OTItem::OTItem() : OTTransactionType()
{
	InitItem();
}


// Let's say you have created a transaction, and you are creating an item to put into it.
// Well in that case, you don't care to verify that the real IDs match the purported IDs, since
// you are creating this item yourself, not verifying it from someone else.
// Use this function to create the new Item before you add it to your new Transaction.
OTItem * OTItem::CreateItemFromTransaction(const OTTransaction & theOwner, OTItem::itemType theType, OTIdentifier * pDestinationAcctID/*=NULL*/)
{
	OTItem * pItem = new OTItem(theOwner.GetUserID(), theOwner, theType, pDestinationAcctID);
	
	if (pItem)
	{
		pItem->SetPurportedAccountID(theOwner.GetPurportedAccountID());
		pItem->SetPurportedServerID(theOwner.GetPurportedServerID());
		return pItem;
	}
	return NULL;
}


// Sometimes I don't know user ID of the originator, or the account ID of the originator,
// until after I have loaded the item. It's simply impossible to set those values ahead
// of time, sometimes. In those cases, we set the values appropriately but then we need
// to verify that the user ID is actually the owner of the AccountID. TOdo that.
OTItem * OTItem::CreateItemFromString(const OTString & strItem, const OTIdentifier & theServerID, long lTransactionNumber)
{
	OTItem * pItem = new OTItem();

	// So when it loads its own server ID, we can compare to this one.
	pItem->SetRealServerID(theServerID);
	
	// This loads up the purported account ID and the user ID.
	if (pItem->LoadContractFromString(strItem))
	{
		const OTIdentifier & ACCOUNT_ID = pItem->GetPurportedAccountID();
		pItem->SetRealAccountID(ACCOUNT_ID);// I do this because it's all we've got in this case. It's what's in the
											// xml, so it must be right. If it's a lie, the signature will fail or the
											// user will not show as the owner of that account. But remember, the server
											// sent the message in the first place.
	
		pItem->SetTransactionNum(lTransactionNumber);
		
		if (pItem->VerifyContractID()) // this compares purported and real account IDs, as well as server IDs.
		{
			return pItem;
		}
		else {
			delete pItem;
			pItem = NULL;
		}
	}

	return NULL;
}




void OTItem::InitItem()
{
	
	m_lAmount			= 0; // Accounts default to ZERO.  They can only change that amount by receiving from another account.
	m_Status			= OTItem::request;					// (Unless an issuer account, which can create currency of that type.)
	m_Type				= OTItem::error_state;
	m_strContractType	= "TRANSACTION ITEM"; // CONTRACT, MESSAGE, TRANSACTION, LEDGER, TRANSACTION ITEM 
}


// From owner we can get acct ID, server ID, and transaction Num
OTItem::OTItem(const OTIdentifier & theUserID, const OTTransaction & theOwner) 
: OTTransactionType(theUserID, theOwner.GetRealAccountID(), theOwner.GetRealServerID(), theOwner.GetTransactionNum())
{
	InitItem();
	
}

// From owner we can get acct ID, server ID, and transaction Num
OTItem::OTItem(const OTIdentifier & theUserID, const OTItem & theOwner) 
: OTTransactionType(theUserID, theOwner.GetRealAccountID(), theOwner.GetRealServerID(), theOwner.GetTransactionNum())
{
	InitItem();
	
}

OTItem::OTItem(const OTIdentifier & theUserID, const OTTransaction & theOwner, OTItem::itemType theType, OTIdentifier * pDestinationAcctID/*=NULL*/)
		: OTTransactionType(theUserID, theOwner.GetRealAccountID(), theOwner.GetRealServerID(), theOwner.GetTransactionNum())
{
	InitItem();
	
	m_Type	= theType;  // This has to be below the InitItem() call that appears just above
	
	// Most transactions items don't HAVE a "to" account, just a primary account.
	// (If you deposit, or withdraw, you don't need a "to" account.)
	// But for the ones that do, you can pass the "to" account's ID in 
	// as a pointer, and we'll set that too....
	if (NULL != pDestinationAcctID)
	{
		m_AcctToID = *pDestinationAcctID;
	}	
}


/*
OTItem& OTItem::operator=(const OTItem& rhs)
{
	m_Type				= rhs.m_Type;	
	m_Status			= rhs.m_Status;
	m_lAmount			= rhs.m_lAmount;
	m_lTransactionNum	= rhs.m_lTransactionNum;
	m_strNote			= rhs.m_strNote;
	m_AcctFromID		= rhs.m_AcctFromID;		
	m_AcctToID			= rhs.m_AcctToID;
	m_AcctServerID		= rhs.m_AcctServerID;		
	m_OutboxHash		= rhs.m_OutboxHash;		
	m_ascInReferenceTo	= rhs.m_ascInReferenceTo;
	m_lInReferenceToTrans = rhs.m_lInReferenceToTrans;
	
	// Until there is a contract::op=, we'll just do it by hand here.
	// (these are the members of OTContract)
	m_strName			= rhs.m_strName;    
	m_strFilename		= rhs.m_strFilename;
	m_ID				= rhs.m_ID;	 
	m_xmlUnsigned		= rhs.m_xmlUnsigned; 
	m_strRawFile		= rhs.m_strRawFile; 
	m_strSigHashType	= rhs.m_strSigHashType;
	m_strContractType	= rhs.m_strContractType;
	m_strVersion		= rhs.m_strVersion;

	return *this;
}
*/
OTItem::~OTItem()
{
	ReleaseItems();
}







OTItem::itemType GetItemTypeFromString(const OTString & strType)
{
	OTItem::itemType theType = 0;
	
	if (strType.Compare("transaction"))
		theType = OTItem::transaction;
	else if (strType.Compare("atTransaction"))
		theType = OTItem::atTransaction;
	// --------------------------------------------------------------
	else if (strType.Compare("transfer"))
		theType = OTItem::transfer;
	else if (strType.Compare("atTransfer"))
		theType = OTItem::atTransfer;
	else if (strType.Compare("acceptPending"))
		theType = OTItem::acceptPending;
	else if (strType.Compare("atAcceptPending"))
		theType = OTItem::atAcceptPending;
	else if (strType.Compare("rejectPending"))
		theType = OTItem::rejectPending;
	else if (strType.Compare("atRejectPending"))
		theType = OTItem::atRejectPending;
	// --------------------------------------------------------------
	else if (strType.Compare("acceptCronReceipt"))
		theType = OTItem::acceptCronReceipt;
	else if (strType.Compare("atAcceptCronReceipt"))
		theType = OTItem::atAcceptCronReceipt;
	else if (strType.Compare("disputeCronReceipt"))
		theType = OTItem::disputeCronReceipt;
	else if (strType.Compare("atDisputeCronReceipt"))
		theType = OTItem::atDisputeCronReceipt;
	else if (strType.Compare("acceptItemReceipt"))
		theType = OTItem::acceptItemReceipt;
	else if (strType.Compare("atAcceptItemReceipt"))
		theType = OTItem::atAcceptItemReceipt;
	else if (strType.Compare("disputeItemReceipt"))
		theType = OTItem::disputeItemReceipt;
	else if (strType.Compare("atDisputeItemReceipt"))
		theType = OTItem::atDisputeItemReceipt;
	// --------------------------------------------------------------
	else if (strType.Compare("serverfee"))
		theType = OTItem::serverfee;
	else if (strType.Compare("atServerfee"))
		theType = OTItem::atServerfee;
	else if (strType.Compare("issuerfee"))
		theType = OTItem::issuerfee;
	else if (strType.Compare("atIssuerfee"))
		theType = OTItem::atIssuerfee;
	// --------------------------------------------------------------
	else if (strType.Compare("balanceStatement"))
		theType = OTItem::balanceStatement;
	else if (strType.Compare("atBalanceStatement"))
		theType = OTItem::atBalanceStatement;
	else if (strType.Compare("transactionStatement"))
		theType = OTItem::transactionStatement;
	else if (strType.Compare("atTransactionStatement"))
		theType = OTItem::atTransactionStatement;
	// --------------------------------------------------------------
	else if (strType.Compare("withdrawal"))
		theType = OTItem::withdrawal;
	else if (strType.Compare("atWithdrawal"))
		theType = OTItem::atWithdrawal;
	else if (strType.Compare("deposit"))
		theType = OTItem::deposit;
	else if (strType.Compare("atDeposit"))
		theType = OTItem::atDeposit;
	// --------------------------------------------------------------
	else if (strType.Compare("withdrawVoucher"))
		theType = OTItem::withdrawVoucher;
	else if (strType.Compare("atWithdrawVoucher"))
		theType = OTItem::atWithdrawVoucher;
	else if (strType.Compare("depositCheque"))
		theType = OTItem::depositCheque;
	else if (strType.Compare("atDepositCheque"))
		theType = OTItem::atDepositCheque;
	// --------------------------------------------------------------
	else if (strType.Compare("marketOffer"))
		theType = OTItem::marketOffer;
	else if (strType.Compare("atMarketOffer"))
		theType = OTItem::atMarketOffer;
	// --------------------------------------------------------------
	else if (strType.Compare("paymentPlan"))
		theType = OTItem::paymentPlan;
	else if (strType.Compare("atPaymentPlan"))
		theType = OTItem::atPaymentPlan;
	// --------------------------------------------------------------
	else if (strType.Compare("chequeReceipt"))
		theType = OTItem::chequeReceipt;
	else if (strType.Compare("marketReceipt"))
		theType = OTItem::marketReceipt;
	else if (strType.Compare("paymentReceipt"))
		theType = OTItem::paymentReceipt;
	// --------------------------------------------------------------
	else
		theType = OTItem::error_state;
	// --------------------------------------------------------------
	
	return theType;
}



// return -1 if error, 0 if nothing, and 1 if the node was processed.
int OTItem::ProcessXMLNode(irr::io::IrrXMLReader*& xml)
{
	if (!strcmp("item", xml->getNodeName()))
	{	
		OTString strType, strStatus;
		
		strType		= xml->getAttributeValue("type");
		strStatus	= xml->getAttributeValue("status");
		
		// Type
		m_Type = GetItemTypeFromString(strType); // just above.
				
		// Status
		if (strStatus.Compare("request"))
			m_Status = OTItem::request;
		else if (strStatus.Compare("acknowledgement"))
			m_Status = OTItem::acknowledgement;
		else if (strStatus.Compare("rejection"))
			m_Status = OTItem::rejection;
		else
			m_Status = OTItem::error_status;
		
		OTString strAcctFromID, strAcctToID, strServerID, strUserID;
		
		strAcctFromID		= xml->getAttributeValue("fromAccountID"); 
		strAcctToID			= xml->getAttributeValue("toAccountID"); 
		strServerID			= xml->getAttributeValue("serverID");
		strUserID			= xml->getAttributeValue("userID");
		
		OTIdentifier	ACCOUNT_ID(strAcctFromID), SERVER_ID(strServerID), DESTINATION_ACCOUNT(strAcctToID),
						USER_ID(strUserID);
		
		SetPurportedAccountID(ACCOUNT_ID);		// OTTransactionType::m_AcctID  the PURPORTED Account ID
		SetPurportedServerID(SERVER_ID);		// OTTransactionType::m_AcctServerID the PURPORTED Server ID
		SetDestinationAcctID(DESTINATION_ACCOUNT);
		SetUserID(USER_ID);
		SetTransactionNum(atol(xml->getAttributeValue("transactionNum")));
		SetReferenceToNum(atol(xml->getAttributeValue("inReferenceTo")));
		
		m_lAmount	= atol(xml->getAttributeValue("amount"));
		
		OTLog::vOutput(0, "Loaded transaction Item, transaction num %ld, In Reference To: %ld, type: %s, status: %s\n",
//				"fromAccountID:\n%s\n UserID:\n%s\n toAccountID:\n%s\n serverID:\n%s\n----------\n", 
				GetTransactionNum(),
				GetReferenceToNum(), strType.Get(), strStatus.Get()
//				strAcctFromID.Get(), strUserID.Get(), strAcctToID.Get(), strServerID.Get()
				);
		
		return 1;
	}
	else if (!strcmp("note", xml->getNodeName())) 
	{		
		if (false == LoadEncodedTextField(xml, m_ascNote))
		{
			OTLog::Error("Error in OTItem::ProcessXMLNode: note field without value.\n");
			return (-1); // error condition
		}
		
		return 1;
	}
	else if (!strcmp("inReferenceTo", xml->getNodeName())) 
	{		
		if (false == LoadEncodedTextField(xml, m_ascInReferenceTo))
		{
			OTLog::Error("Error in OTItem::ProcessXMLNode: inReferenceTo field without value.\n");
			return (-1); // error condition
		}
		
		return 1;
	}
	else if (!strcmp("attachment", xml->getNodeName())) 
	{		
		if (false == LoadEncodedTextField(xml, m_ascAttachment))
		{
			OTLog::Error("Error in OTItem::ProcessXMLNode: attachment field without value.\n");
			return (-1); // error condition
		}
		
		return 1;
	}
	else if (!strcmp("transactionReport", xml->getNodeName())) 
	{		
		OTItem * pItem = new OTItem(GetUserID(), *this); // But I've also got ITEM types with the same names...
														// That way, it will translate the string and set the type correctly.
		OT_ASSERT(NULL != pItem);						// That way I can use each item to REPRESENT an inbox transaction
				
		// Type
		OTString strType;		
		strType		= xml->getAttributeValue("type"); // it's reading a TRANSACTION type: chequeReceipt, marketReceipt, or paymentReceipt
		
		pItem->SetType(GetItemTypeFromString(strType)); // It's actually translating a transaction type to an item type. (Same names in the case of the 3 receipts that matter for inbox reports for balance agreements.)
		
		pItem->SetAmount(atol(xml->getAttributeValue("adjustment")));

		// Status
		pItem->SetStatus(OTItem::acknowledgement); // I don't need this, but I'd rather it not say error state.
		
		OTString strAccountID, strServerID, strUserID;
		
		strAccountID		= xml->getAttributeValue("accountID"); 
		strServerID			= xml->getAttributeValue("serverID");
		strUserID			= xml->getAttributeValue("userID");
		
		OTIdentifier	ACCOUNT_ID(strAccountID), SERVER_ID(strServerID), USER_ID(strUserID);
		
		pItem->SetPurportedAccountID(ACCOUNT_ID);		// OTTransactionType::m_AcctID  the PURPORTED Account ID
		pItem->SetPurportedServerID(SERVER_ID);		// OTTransactionType::m_AcctServerID the PURPORTED Server ID
		pItem->SetUserID(USER_ID);
		pItem->SetTransactionNum(atol(xml->getAttributeValue("transactionNum")));
		pItem->SetReferenceToNum(atol(xml->getAttributeValue("inReferenceTo")));
				
		m_listItems.push_back(pItem); // <======= adding to list.

		OTLog::vOutput(1, "Loaded transactionReport Item, transaction num %ld, In Reference To: %ld, type: %s\n",
					   //				"fromAccountID:\n%s\n UserID:\n%s\n toAccountID:\n%s\n serverID:\n%s\n----------\n", 
					   pItem->GetTransactionNum(),
					   pItem->GetReferenceToNum(), strType.Get()
					   //				strAcctFromID.Get(), strUserID.Get(), strAcctToID.Get(), strServerID.Get()
					   );
		return 1;
	}
	
	return 0;	
}



void GetStringFromType(OTItem::itemType theType, OTString & strType)
{
	switch (theType) {
		case OTItem::transaction:
			strType.Set("transaction");
			break;
		case OTItem::transfer:
			strType.Set("transfer");
			break;
		case OTItem::acceptPending:
			strType.Set("acceptPending");
			break;
		case OTItem::rejectPending:
			strType.Set("rejectPending");
			break;
		case OTItem::acceptCronReceipt:
			strType.Set("acceptCronReceipt");
			break;
		case OTItem::disputeCronReceipt:
			strType.Set("disputeCronReceipt");
			break;
		case OTItem::acceptItemReceipt:
			strType.Set("acceptItemReceipt");
			break;
		case OTItem::disputeItemReceipt:
			strType.Set("disputeItemReceipt");
			break;
		case OTItem::serverfee:
			strType.Set("serverfee");
			break;
		case OTItem::issuerfee:
			strType.Set("issuerfee");
			break;
		case OTItem::balance:
			strType.Set("balance");
			break;
		case OTItem::outboxhash:
			strType.Set("outboxhash");
			break;
		case OTItem::withdrawal:
			strType.Set("withdrawal");
			break;
		case OTItem::deposit:
			strType.Set("deposit");
			break;
		case OTItem::withdrawVoucher:
			strType.Set("withdrawVoucher");
			break;
		case OTItem::depositCheque:
			strType.Set("depositCheque");
			break;
		case OTItem::marketOffer:
			strType.Set("marketOffer");
			break;
		case OTItem::paymentPlan:
			strType.Set("paymentPlan");
			break;
		case OTItem::balanceStatement:
			strType.Set("balanceStatement");
			break;
		case OTItem::transactionStatement:
			strType.Set("transactionStatement");
			break;
			
			
			
		case OTItem::chequeReceipt:			// used for inbox statements in balance agreement.
			strType.Set("chequeReceipt");
			break;
		case OTItem::marketReceipt:			// used as market receipt, and also for inbox statement containing market receipt will use this as well.
			strType.Set("marketReceipt");
			break;
		case OTItem::paymentReceipt:		// used as payment receipt, also used in inbox statement as payment receipt.
			strType.Set("paymentReceipt");
			break;
			
			
			
		case OTItem::atTransaction:
			strType.Set("atTransaction");
			break;
		case OTItem::atTransfer:
			strType.Set("atTransfer");
			break;
		case OTItem::atAcceptPending:
			strType.Set("atAcceptPending");
			break;
		case OTItem::atRejectPending:
			strType.Set("atRejectPending");
			break;
		case OTItem::atAcceptCronReceipt:
			strType.Set("atAcceptCronReceipt");
			break;
		case OTItem::atDisputeCronReceipt:
			strType.Set("atDisputeCronReceipt");
			break;
		case OTItem::atAcceptItemReceipt:
			strType.Set("atAcceptItemReceipt");
			break;
		case OTItem::atDisputeItemReceipt:
			strType.Set("atDisputeItemReceipt");
			break;
		case OTItem::atServerfee:
			strType.Set("atServerfee");
			break;
		case OTItem::atIssuerfee:
			strType.Set("atIssuerfee");
			break;
		case OTItem::atBalance:
			strType.Set("atBalance");
			break;
		case OTItem::atOutboxhash:
			strType.Set("atOutboxhash");
			break;
		case OTItem::atWithdrawal:
			strType.Set("atWithdrawal");
			break;
		case OTItem::atDeposit:
			strType.Set("atDeposit");
			break;
		case OTItem::atWithdrawVoucher:
			strType.Set("atWithdrawVoucher");
			break;
		case OTItem::atDepositCheque:
			strType.Set("atDepositCheque");
			break;
		case OTItem::atMarketOffer:
			strType.Set("atMarketOffer");
			break;
		case OTItem::atPaymentPlan:
			strType.Set("atPaymentPlan");
			break;
		case OTItem::atBalanceStatement:
			strType.Set("atBalanceStatement");
			break;
		case OTItem::atTransactionStatement:
			strType.Set("atTransactionStatement");
			break;
			
			
			
			
			
		default:
			strType.Set("error-unknown");
			break;
	}
	
}


void OTItem::UpdateContents() // Before transmission or serialization, this is where the ledger saves its contents 
{
	OTString strFromAcctID(GetPurportedAccountID()), strToAcctID(GetDestinationAcctID()), strServerID(GetPurportedServerID()), 
			 strType, strStatus, strUserID(GetUserID());
	
	GetStringFromType(m_Type, strType);
	
	switch (m_Status) {
		case OTItem::request:
			strStatus.Set("request");
			break;
		case OTItem::acknowledgement:
			strStatus.Set("acknowledgement");
			break;
		case OTItem::rejection:
			strStatus.Set("rejection");
			break;
		default:
			strStatus.Set("error-unknown");
			break;
	}
	
	// I release this because I'm about to repopulate it.
	m_xmlUnsigned.Release();
		
	m_xmlUnsigned.Concatenate("<item type=\"%s\"\n status=\"%s\"\n"
							  " transactionNum=\"%ld\"\n"
							  " serverID=\"%s\"\n"
							  " userID=\"%s\"\n"
							  " fromAccountID=\"%s\"\n"
							  " toAccountID=\"%s\"\n"
							  " inReferenceTo=\"%ld\"\n" 
							  " amount=\"%ld\" >\n\n", 
							  strType.Get(), strStatus.Get(), GetTransactionNum(), strServerID.Get(), 
							  strUserID.Get(),
							  strFromAcctID.Get(), strToAcctID.Get(), GetReferenceToNum(), m_lAmount);
		
	if (m_ascNote.GetLength() > 2)
	{
		m_xmlUnsigned.Concatenate("<note>\n%s</note>\n\n", m_ascNote.Get());
	}
	
	if (m_ascInReferenceTo.GetLength() > 2)
	{
		m_xmlUnsigned.Concatenate("<inReferenceTo>\n%s</inReferenceTo>\n\n", m_ascInReferenceTo.Get());
	}
	
	if (m_ascAttachment.GetLength() > 2)
	{
		m_xmlUnsigned.Concatenate("<attachment>\n%s</attachment>\n\n", m_ascAttachment.Get());
	}
	
	
	// loop through the sub-items (only used for balance agreement.)
	
	OTItem * pItem = NULL;
	
	for (listOfItems::iterator ii = m_listItems.begin(); ii != m_listItems.end(); ++ii)
	{
		pItem = *ii;
		
		OT_ASSERT(NULL != pItem);
		
		OTString	strAcctID(pItem->GetPurportedAccountID()), 
					strServerID(pItem->GetPurportedServerID()),
					strUserID(pItem->GetUserID());
		
		OTString strType;
		GetStringFromType(pItem->GetType(), strType);
		
		m_xmlUnsigned.Concatenate("<transactionReport type=\"%s\"\n"
							  " adjustment=\"%ld\"\n"
							  " accountID=\"%s\"\n"
							  " userID=\"%s\"\n"
							  " serverID=\"%s\"\n"
							  " transactionNum=\"%ld\"\n"
							  " inReferenceTo=\"%ld\" />\n\n", 
							  strType.Exists() ? strType.Get() : "error_state", 
							  pItem->GetAmount(),
							  strAcctID.Get(), strUserID.Get(), 
							  strServerID.Get(), 
							GetTransactionNum(),
								  GetReferenceToNum());
	}	

	
	m_xmlUnsigned.Concatenate("</item>\n");					
}



bool OTItem::SaveContractWallet(std::ofstream & ofs)
{
	return true;
}





































