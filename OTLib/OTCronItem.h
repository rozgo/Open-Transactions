/************************************************************************************
 *    
 *  OTCronItem.h
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


// Base class for OTTrade and OTAgreement.
// OTCron contains lists of these for regular processing.

#ifndef __OTCRON_ITEM_H__
#define __OTCRON_ITEM_H__

#include "OTTrackable.h"


class OTIdentifier;
class OTCron;
class OTString;


class OTCronItem : public OTTrackable
{
	OTCron *	m_pCron;
	
	time_t		m_CREATION_DATE;		// The date, in seconds, when the CronItem was authorized.
	time_t		m_LAST_PROCESS_DATE;	// The last time this item was processed.

	time_t		m_PROCESS_INTERVAL;		// How often to Process Cron on this item.
	
protected:
	
	OTCronItem();
	OTCronItem(const OTIdentifier & SERVER_ID, const OTIdentifier & ASSET_ID);
	OTCronItem(const OTIdentifier & SERVER_ID, const OTIdentifier & ASSET_ID,
			   const OTIdentifier & ACCT_ID, const OTIdentifier & USER_ID);
public:
	inline void SetCronPointer(OTCron & theCron) { m_pCron = &theCron; }

	static OTCronItem * NewCronItem(const OTString & strCronItem);
	static OTCronItem * LoadCronReceipt(const long & lTransactionNum);
	
	inline void SetCreationDate(const time_t & CREATION_DATE) { m_CREATION_DATE = CREATION_DATE; }
	inline const time_t & GetCreationDate() const { return m_CREATION_DATE; }
	
	inline void SetLastProcessDate(const time_t & THE_DATE) { m_LAST_PROCESS_DATE = THE_DATE; }
	inline const time_t & GetLastProcessDate() const { return m_LAST_PROCESS_DATE; }
	
	inline void SetProcessInterval(const time_t & THE_DATE) { m_PROCESS_INTERVAL = THE_DATE; }
	inline const time_t & GetProcessInterval() const { return m_PROCESS_INTERVAL; }
	
	
	inline OTCron * GetCron() { return m_pCron; }
	
	
	// When first adding anything to Cron, a copy needs to be saved in a folder somewhere.
	bool SaveCronReceipt();
	
	
	// --------------------------------------------------------------------------
	// Return True if should stay on OTCron's list for more processing.
	// Return False if expired or otherwise should be removed.
	virtual bool ProcessCron(); // OTCron calls this regularly, which is my chance to expire, etc.
	
	// --------------------------------------------------------------------------
	
	// From OTTrackable (parent class of this)
	/*
	 inline long GetTransactionNum() const { return m_lTransactionNum; }
	 inline const OTIdentifier & GetSenderAcctID()		{ return m_SENDER_ACCT_ID; }
	 inline const OTIdentifier & GetSenderUserID()		{ return m_SENDER_USER_ID; }
	 */
	
	// --------------------------------------------------------------------------
	
	// From OTInstrument (parent class of OTTrackable, parent class of this)
	/*
	 OTInstrument(const OTIdentifier & SERVER_ID, const OTIdentifier & ASSET_ID) : OTContract()
	 
	 inline time_t GetValidFrom()	const { return m_VALID_FROM; }
	 inline time_t GetValidTo()		const { return m_VALID_TO; }
	 
	 inline void SetValidFrom(time_t TIME_FROM)	{ m_VALID_FROM	= TIME_FROM; }
	 inline void SetValidTo(time_t TIME_TO)		{ m_VALID_TO	= TIME_TO; }
	 
	 inline const OTIdentifier & GetAssetID() const { return m_AssetTypeID; }
	 inline const OTIdentifier & GetServerID() const { return m_ServerID; }
	 
	 inline void SetAssetID(const OTIdentifier & ASSET_ID)  { m_AssetTypeID	= ASSET_ID; }
	 inline void SetServerID(const OTIdentifier & SERVER_ID) { m_ServerID	= SERVER_ID; }
	 
	 bool VerifyCurrentDate(); // Verify the current date against the VALID FROM / TO dates.
	 bool IsExpired(); // Only tells if if it's past the "valid to" date.
	 */
	
	virtual ~OTCronItem();
	
	
	void InitCronItem();
	
	virtual void Release();
	
	
//	virtual int ProcessXMLNode(irr::io::IrrXMLReader*& xml);
	
//	virtual void UpdateContents(); // Before transmission or serialization, this is where the ledger saves its contents 
	
//	virtual bool SaveContractWallet(std::ofstream & ofs);	
};




#endif // __OTCRON_ITEM_H__
