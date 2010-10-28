/************************************************************************************
 *    
 *  OTAgreement.cpp
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


// OTAgreement is derived from OTCronItem.  It handles re-occuring billing.

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

