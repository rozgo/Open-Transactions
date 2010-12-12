/************************************************************************************
 *    
 *  OTPurse.cpp
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


#include <cstring>


#include "irrxml/irrXML.h"

using namespace irr;
using namespace io;


#include "OTToken.h"
#include "OTPurse.h"
#include "OTPseudonym.h"
#include "OTEnvelope.h"
#include "OTASCIIArmor.h"
#include "OTLog.h"




OTPurse::OTPurse(const OTPurse & thePurse) : OTContract()
{
	InitPurse();
	
	m_ServerID	= thePurse.GetServerID();
	m_AssetID	= thePurse.GetAssetID();
}

// Don't use this unless you really don't have the asset type handy.
// Perhaps you know you're about to read this purse from a string and you
// know the asset type is in there anyway. So you use this constructor.
OTPurse::OTPurse(const OTIdentifier & SERVER_ID) : OTContract()
{
	InitPurse();
	
	m_ServerID	= SERVER_ID;
}

OTPurse::OTPurse(const OTIdentifier & SERVER_ID, const OTIdentifier & ASSET_ID) : OTContract()
{
	InitPurse();
	
	m_ServerID	= SERVER_ID;
	m_AssetID	= ASSET_ID;
}

OTPurse::OTPurse(const OTIdentifier & SERVER_ID, 
				 const OTIdentifier & ASSET_ID, const OTIdentifier & USER_ID) : OTContract()
{
	InitPurse();
	
	m_ServerID	= SERVER_ID;
	m_AssetID	= ASSET_ID;
	m_UserID	= USER_ID;
}

OTPurse::~OTPurse()
{
//	Release();
	// OTContract::~OTContract is called here automatically, and it calls Release() already.
	// So I don't need to call Release() here again, since it's already called by the parent.

}

void OTPurse::InitPurse()
{
	m_strContractType.Set("PURSE");
	
	m_lTotalValue = 0;
}


void OTPurse::Release()
{
	// This sets m_lTotalValue to 0.
	ReleaseTokens();
	
	OTContract::Release();
}



int OTPurse::ProcessXMLNode(irr::io::IrrXMLReader*& xml)
{
	if (!strcmp("purse", xml->getNodeName()))
	{	
		OTString strServerID, strUserID, strAssetID, strTotalValue;
		
				
		m_strVersion	= xml->getAttributeValue("version"); 
		strUserID		= xml->getAttributeValue("userID");
		strServerID		= xml->getAttributeValue("serverID");
		strAssetID		= xml->getAttributeValue("assetTypeID");
		strTotalValue	= xml->getAttributeValue("totalValue");
		
		m_AssetID.SetString(strAssetID);
		m_UserID.SetString(strUserID);
		m_ServerID.SetString(strServerID);
		
		m_lTotalValue = 0;
		
		if (strTotalValue.Exists() && (atol(strTotalValue.Get()) > 0))
			m_lTotalValue = atol(strTotalValue.Get());
			
		OTLog::vOutput(0, "Loaded purse...\n ServerID:\n%s\n UserID: %s\n Asset ID: %s\n----------\n", strServerID.Get(),
				strUserID.Get(), strAssetID.Get());
		
		return 1;
	}
	
	else if (!strcmp("token", xml->getNodeName())) 
	{		
		OTASCIIArmor * pArmor = new OTASCIIArmor;
		
		OT_ASSERT(NULL != pArmor);
		
		if (!LoadEncodedTextField(xml, *pArmor) || !pArmor->Exists())
		{
			OTLog::Error("Error in OTPurse::ProcessXMLNode: token field without value.\n");
			
			delete pArmor;
			pArmor = NULL;
			
			return (-1); // error condition
		}
		else 
		{			
			m_dequeTokens.push_front(pArmor);
		}
		
		return 1;
	}

	return 0;
}



bool OTPurse::SaveContractWallet(std::ofstream & ofs)	
{
	return true;
}


void OTPurse::UpdateContents() // Before transmission or serialization, this is where the Purse saves its contents 
{
	OTString SERVER_ID(m_ServerID), USER_ID(m_UserID), ASSET_TYPE_ID(m_AssetID);
	
	// I release this because I'm about to repopulate it.
	m_xmlUnsigned.Release();
	
	m_xmlUnsigned.Concatenate("<?xml version=\"%s\"?>\n\n", "1.0");		
	
	m_xmlUnsigned.Concatenate("<purse version=\"%s\"\n"
							  " totalValue=\"%ld\"\n" // Total of all the tokens within.
							  " userID=\"%s\"\n" // UserID is optional.
							  " assetTypeID=\"%s\"\n serverID=\"%s\">\n\n",
							  m_strVersion.Get(), 
							  m_lTotalValue,
							  USER_ID.Get(), 
							  ASSET_TYPE_ID.Get(), SERVER_ID.Get());		
	
	for (int i = 0; i < Count(); i++)
	{
		m_xmlUnsigned.Concatenate("<token>\n%s</token>\n\n", m_dequeTokens[i]->Get());
	}
	
	m_xmlUnsigned.Concatenate("</purse>\n");			
	
}

// Hypocritically (compared to Push) in the case of Pop(), we DO
// allocate a OTToken and return the pointer. The caller IS
// responsible to delete it when he's done with it.
// 
// The apparent discrepancy is due to the fact that internally,
// we aren't storing the token object but an encrypted string of it.
// But this is hidden from the user of the purse, who perceives only
// that he is passing tokens in and getting them back out again.
OTToken * OTPurse::Pop(const OTPseudonym & theOwner)
{
	if (m_dequeTokens.empty())
		return NULL;
	
	
	// Grab a copy of the pointer and remove it from the deque
	OTASCIIArmor * pArmor =  m_dequeTokens.front();
	m_dequeTokens.pop_front();
	
//	OTLog::vError("$$$$$$$$$$$$$$ ARMORED TEXT in PURSE POP:\n--------->%s<-----------\n", pArmor->Get());
	
	// Copy the token contents into an Envelope, and delete the pointer.
	OTEnvelope theEnvelope(*pArmor);
	delete pArmor;
	pArmor = NULL;	

	// Open the envelope into a string.
	OTString strToken;
	theEnvelope.Open(theOwner, strToken);
	
//	OTLog::vError("$$$$$$$$$$$$$$$ OPENED ENVELOPE TEXT in PURSE POP:\n--------->%s<-----------\n", strToken.Get());

	// Create a new token with the same server and asset IDs as this purse.
	OTToken * pToken =  new OTToken(*this);
	
	OT_ASSERT(NULL != pToken);
	
	// Load the token from the string we got out of the envelope.
	pToken->LoadContractFromString(strToken);
	
	if (pToken->GetAssetID() != m_AssetID ||
		pToken->GetServerID() != m_ServerID)
	{
		delete pToken;
		pToken = NULL;
		
		OTLog::Error("ERROR: Token with wrong asset type in OTPurse::Pop\n");
	}
	else 
	{
		// We keep track of the purse's total value.
		m_lTotalValue -= pToken->GetDenomination();
	}

	// CALLER is responsible to delete this token.
	return pToken;
}


// Use a local variable for theToken, do NOT allocate it on the heap 
// unless you are going to delete it yourself.
// Repeat: OTPurse is NOT responsible to delete it. We create our OWN internal
// variable here, new that, and add it to the stack. We do not add the one passed in.
bool OTPurse::Push(const OTPseudonym & theOwner, const OTToken & theToken)
{
	if (theToken.GetAssetID() == m_AssetID)
	{
		OTString strToken(theToken);
		
//		OTLog::vError("$$$$$$$$$$$$$$$  PUSHING token to Purse:\n---------->%s<-------------\n", strToken.Get());
		
		OTEnvelope theEnvelope;
		theEnvelope.Seal(theOwner, strToken);
		
		OTASCIIArmor * pArmor = new OTASCIIArmor(theEnvelope);
//		OTLog::vError("$$$$$$$$$$$$$$$  PUSHING token to Purse in armored form:\n---------->%s<-------------\n", 
//				pArmor->Get());

		m_dequeTokens.push_front(pArmor);
		
		// We keep track of the purse's total value.
		m_lTotalValue += theToken.GetDenomination();
		
		return true;
	}
	else {
		OTString strPurseAssetType(m_AssetID), strTokenAssetType(theToken.GetAssetID());
		OTLog::vError("ERROR: Tried to push token with wrong asset type in OTPurse::Push\nPurse Asset Type:\n%s\n"
				"Token Asset Type:\n%s\n", strPurseAssetType.Get(), strTokenAssetType.Get());
		
		return false;
	}
}

int OTPurse::Count() const
{
	return m_dequeTokens.size();
}

bool OTPurse::IsEmpty() const
{
	return m_dequeTokens.empty();
}

void OTPurse::ReleaseTokens()
{
	OTASCIIArmor * pArmor = NULL;
	
	while (!m_dequeTokens.empty()) {
		pArmor = m_dequeTokens.front();
		m_dequeTokens.pop_front();
		delete pArmor;
	}
	
	m_lTotalValue = 0;
}

