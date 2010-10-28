/************************************************************************************
 *    
 *  OTCronItem.cpp
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
	
	// ------------------------------------------------------------------------
	
	bool bFolderExists = OTLog::ConfirmOrCreateFolder(OTLog::CronFolder()); // <path>/cron is where all cronlogs go.
	
	if (!bFolderExists)
	{
		OTLog::vError("Unable to create or confirm folder \"%s\"\n in order to load Cron Receipt %ld.\n",
					  OTLog::CronFolder(), lTransactionNum);
		return NULL;
	}
	
	// ------------------------------------------------------------------------
	
	OTString strCronItemLocalPath;
	strCronItemLocalPath.Format("%s%s%ld.crn", OTLog::CronFolder(), 
								OTLog::PathSeparator(), lTransactionNum);
	
	bool bFileExists = OTLog::ConfirmFile(strCronItemLocalPath.Get());
	
	if (!bFileExists)
	{
		OTLog::vError("Attempted to load non-existent Cron Record for transaction %ld in folder %s.\n",
					  lTransactionNum, strCronItemLocalPath.Get());
		return NULL;
	}
	
	// ------------------------------------------------------------------------
	
	OTString strCronItemPath;
	strCronItemPath.Format("%s%s%s", OTLog::Path(), OTLog::PathSeparator(), 
						   strCronItemLocalPath.Get());
	
	std::ifstream in(strCronItemPath.Get(), std::ios::binary);
	
	if (in.fail())
	{
		OTLog::vError("Error opening file in OTCronItem::LoadCronReceipt: %s\n",
					  strCronItemPath.Get());
		return NULL;
	}
	
	std::stringstream buffer;
	buffer << in.rdbuf();
	
	std::string contents(buffer.str());
	
	OTString strRawFile = contents.c_str();
	
	if (strRawFile.GetLength())
		return OTCronItem::NewCronItem(strRawFile);
	
	return NULL;
	
	// ------------------------------------------------------------------------
}



// When first adding anything to Cron, a copy needs to be saved in a folder somewhere.
// (Just for our records.) For example, before I start updating the status on any Trade,
// I have already saved the user's original Trade object (from his request) to a folder.
// Now I have the freedom to ReleaseSignatures on the Trade and re-sign it with the
// server's Nym as it updates over time.  The user cannot challenge the Trade because
// the server has the original copy on file and sends it with all receipts.

bool OTCronItem::SaveCronReceipt()
{
	
	// ------------------------------------------------------------------------

	bool bFolderExists = OTLog::ConfirmOrCreateFolder(OTLog::CronFolder()); // <path>/cron is where all cronlogs go.

	if (!bFolderExists)
	{
		OTLog::vError("Unable to create or confirm folder \"%s\"\n in order to save Cron Receipt:\n%s\n",
					  OTLog::CronFolder(), m_xmlUnsigned.Get());
		return false;
	}
	
	// ------------------------------------------------------------------------

	OTString strCronItemLocalPath;
	strCronItemLocalPath.Format("%s%s%ld.crn", OTLog::CronFolder(), OTLog::PathSeparator(), GetTransactionNum());
	
	bool bFileExists = OTLog::ConfirmFile(strCronItemLocalPath.Get());
	
	if (bFileExists)
	{
		OTLog::vError("Cron Record exists for transaction %ld in folder %s,\nyet attempted to record it again.\n",
					  GetTransactionNum(), strCronItemLocalPath.Get());
		return false;
	}

	// ------------------------------------------------------------------------
	
	OTString strCronItemPath;
	strCronItemPath.Format("%s%s%s", OTLog::Path(), OTLog::PathSeparator(), strCronItemLocalPath.Get());

	bool bSaved =  SaveContract(strCronItemPath.Get());
	
	if (!bSaved)
	{
		OTLog::vError("Error saving Transaction Number %ld, Cron Receipt:\n%s\n",
					  GetTransactionNum(), m_xmlUnsigned.Get());
	}
	
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
