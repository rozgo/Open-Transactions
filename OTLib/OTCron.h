/************************************************************************************
 *    
 *  OTCron.h
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

// OTCron has a list of OTCronItems. (Really subclasses of that such as OTTrade and OTAgreement.)

#ifndef __OTCRON_H__
#define __OTCRON_H__

#include <map>
#include <list>

#include "OTIdentifier.h"
#include "OTContract.h"
#include "OTCronItem.h"
#include "OTLog.h"

class OTCronItem;
class OTPseudonym;
class OTMarket;



// Mapped (uniquely) to transaction number.
typedef std::map  <long, OTCronItem *>	mapOfCronItems;

// Mapped (uniquely) to market ID.
typedef std::map  <std::string, OTMarket *>	mapOfMarkets;


// Cron stores a bunch of these on this list, 
// which the server refreshes from time to time.
typedef std::list<long> listOfTransactionNumbers;



class OTCron : public OTContract
{
private:
	mapOfMarkets	m_mapMarkets;	// A list of all valid markets.
	mapOfCronItems	m_mapCronItems;
	OTIdentifier	m_SERVER_ID;	// Always store this in any object that's associated with a specific server.

	OTPseudonym *	m_pServerNym;	// I'll need this for later.
	
	listOfTransactionNumbers	m_listTransactionNumbers; // I can't put receipts in people's inboxes without a supply of these.
   
	bool			m_bIsActivated; // I don't want to start Cron processing until everything else is all loaded up and ready to go.
	
public:
	inline bool		IsActivated() const { return m_bIsActivated; }
	inline bool		ActivateCron() { if (!m_bIsActivated) return m_bIsActivated = true; else return false; }
	bool			AddCronItem(OTCronItem & theItem, bool bSaveReceipt=true);
	bool			RemoveCronItem(long lTransactionNum); // if false, CronItem wasn't found.
	OTCronItem *	GetCronItem(long lTransactionNum);

	bool AddMarket(OTMarket & theMarket, bool bSaveMarketFile=true);
	bool RemoveMarket(const OTIdentifier & MARKET_ID); // if returns false, market wasn't found.
	OTMarket * GetMarket(const OTIdentifier & MARKET_ID);
	OTMarket * GetOrCreateMarket(const OTIdentifier & ASSET_ID, 
								 const OTIdentifier & CURRENCY_ID, const long & lScale);
	
	// The server starts out putting a bunch of numbers in here so Cron can use them.
	// Then the internal trades and payment plans get numbers from here as needed.
	// Server MUST replenish from time-to-time, or Cron will stop working.
	// Part of using Cron properly is to call ProcessCron() regularly, as well
	// as to call AddTransactionNumber() regularly, in order to keep GetTransactionCount()
	// at some minimum threshold.
	void	AddTransactionNumber(const long & lTransactionNum);
	long	GetNextTransactionNumber();
	int		GetTransactionCount() const; // How many numbers do I currently have on the list?

	// Make sure every time you call this, you check the GetTransactionCount() first and replenish it
	// to whatever your minimum supply is. (The transaction numbers in there must be enough to last for
	// the entire ProcessCronItems() call, and all the trades and payment plans within, since it will not
	// be replenished again at least until the call has finished.) 
	void	ProcessCronItems();
	
	inline void SetServerID(const OTIdentifier & SERVER_ID)	{ m_SERVER_ID = SERVER_ID; }
	inline const OTIdentifier & GetServerID()	const		{ return m_SERVER_ID; }	

	inline void SetServerNym(OTPseudonym * pServerNym) { OT_ASSERT(NULL != pServerNym); m_pServerNym = pServerNym; }
	inline OTPseudonym * GetServerNym() const { return m_pServerNym; }
	
	// -----------------------------------------------------
	
	bool LoadCron();
	bool SaveCron();
	
	// -----------------------------------------------------
	
	OTCron();
	OTCron(const OTIdentifier & SERVER_ID);
	OTCron(const char * szFilename);
	virtual ~OTCron();
	
	
	void InitCron();
	
	virtual void Release();
	
	// return -1 if error, 0 if nothing, and 1 if the node was processed.
	virtual int ProcessXMLNode(irr::io::IrrXMLReader*& xml);
	
	virtual void UpdateContents(); // Before transmission or serialization, this is where the ledger saves its contents 
	
	virtual bool SaveContractWallet(std::ofstream & ofs);
	
};





#endif // __OTCRON_H__

