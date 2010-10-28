/************************************************************************************
 *    
 *  OTOffer.h
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

// Each instance of OTOffer represents a Bid or Ask. (A Market has a list of bid offers and a list of ask offers.)


#ifndef __OTOFFER_H__
#define __OTOFFER_H__

#include <fstream>

//#include "OTTrade.h"
#include "OTInstrument.h"


class OTTrade;

/*
 OTOffer
 
 Offer MUST STORE:
 
 X 1) Transaction ID (MUST be linked to a trade, so it can expire, and so it can be paid for.)
 X 2) ASSET TYPE ID of whatever I’m trying to BUY or SELL. (Is this the Gold market?)
 X 7) CURRENCY TYPE ID of whatever I’m trying to buy or sell it WITH. (Is it dollars? Euro? Yen?)
 X 8) BUY OR SELL? (BOOL) 
 X 9) Bid/Ask price (limit / per minimum increment.)

 X 4) Total number of assets available for sale or purchase. (4 ounces of gold? 12 ounces of gold?)
 X 5) Number of assets already traded, against the above total.
 X 6) Minimum increment for sale or purchase (if matches “total number of assets for sale”, effectively becomes a FILL OR KILL order. MUST be 1 or greater. CANNOT be zero.)
*/

class OTOffer : public OTInstrument
{
	// From OTInstrument (parent class of this)
	/*
public:
	 inline time_t GetValidFrom()	const { return m_VALID_FROM; }
	 inline time_t GetValidTo()		const { return m_VALID_TO; }
	 
	 inline void SetValidFrom(time_t TIME_FROM)	{ m_VALID_FROM	= TIME_FROM; }
	 inline void SetValidTo(time_t TIME_TO)		{ m_VALID_TO	= TIME_TO; }
	 
	 
	 inline const OTIdentifier & GetAssetID() const { return m_AssetTypeID; }
	 inline const OTIdentifier & GetServerID() const { return m_ServerID; }
	 
	 inline void SetAssetID(const OTIdentifier & ASSET_ID)  { m_AssetTypeID	= ASSET_ID; }
	 inline void SetServerID(const OTIdentifier & SERVER_ID) { m_ServerID	= SERVER_ID; }
	 
	 bool VerifyCurrentDate(); // Verify the current date against the VALID FROM / TO dates.
	 */	
protected:
	OTTrade		*	m_pTrade;		// If this offer is actually connected to a trade, it will have a pointer.
	
	OTIdentifier	m_CURRENCY_TYPE_ID;	// GOLD (Asset) is trading for DOLLARS (Currency).
	bool			m_bSelling;			// true = ask. false = bid.

	// If a bid, this is the most I will pay. If an ask, this is the least I will sell for. My limit.
	// (Normally the price I get is whatever is the best one on the market right now.)
	long	m_lPriceLimit;			// Denominated in CURRENCY TYPE, and priced per SCALE. 
									// 1oz market price limit might be 1,300
									// 100oz market price limit might be 130,000 (or 127,987 or whatever)
	
	long	m_lTransactionNum;		// Matches to an OTTrade stored in OTCron.
	long	m_lTotalAssetsOffer;	// Total amount of ASSET TYPE trying to BUY or SELL, this trade. 
	long	m_lFinishedSoFar;		// Number of ASSETs bought or sold already against the above total.
	
	long	m_lScale;				// 1oz market? 100oz market? 10,000oz market? This determines size and granularity.
	long	m_lMinimumIncrement;	// Each sale or purchase against the above total must be in minimum increments.
									// Minimum Increment must be evenly divisible by m_lScale. 
	// (This effectively becomes a "FILL OR KILL" order if set to the same value as m_lTotalAssetsOffer. Also, MUST be 1
	// or great. CANNOT be zero. Enforce this at class level. You cannot sell something in minimum increments of 0.)
	
	inline void SetTransactionNum(const long & lTransactionNum) { m_lTransactionNum = lTransactionNum; }
	inline void SetPriceLimit(const long & lPriceLimit) { m_lPriceLimit = lPriceLimit; }
	inline void SetTotalAssetsOnOffer(const long & lTotalAssets) { m_lTotalAssetsOffer = lTotalAssets; }
	inline void SetFinishedSoFar(const long & lFinishedSoFar) { m_lFinishedSoFar = lFinishedSoFar; }
	inline void SetMinimumIncrement(const long & lMinIncrement) 
	{ m_lMinimumIncrement = lMinIncrement; if (m_lMinimumIncrement < 1) m_lMinimumIncrement = 1; }
	inline void SetScale(const long & lScale) 
	{ m_lScale = lScale; if (m_lScale < 1) m_lScale = 1; }

public:
		bool	MakeOffer(bool bBuyingOrSelling,			// True == SELLING, False == BUYING
						  const long & lPriceLimit,			// Per Scale...
						  const long & lTotalAssetsOffer,	// Total assets available for sale or purchase.
						  const long & lMinimumIncrement,	// The minimum increment that must be bought or sold for each transaction
						  const long & lTransactionNum,		// The transaction number authorizing this trade.
						  const time_t & VALID_FROM	= 0,	// defaults to RIGHT NOW
						  const time_t & VALID_TO	= 0);	// defaults to 24 hours (a "Day Order")
	
	// ---------------------------------------------------------

	
	inline void IncrementFinishedSoFar(const long & lFinishedSoFar) { m_lFinishedSoFar += lFinishedSoFar; }

	
	inline long			GetAmountAvailable() const { return GetTotalAssetsOnOffer() - GetFinishedSoFar(); }
	inline const long & GetTransactionNum() const { return m_lTransactionNum; }

	inline const long & GetPriceLimit() const { return m_lPriceLimit; }
	inline const long & GetTotalAssetsOnOffer() const { return m_lTotalAssetsOffer; }
	inline const long & GetFinishedSoFar() const { return m_lFinishedSoFar; }
	inline const long & GetMinimumIncrement() 
	{ if (m_lMinimumIncrement < 1) m_lMinimumIncrement = 1; return m_lMinimumIncrement; }
	inline const long & GetScale() 
	{ if (m_lScale < 1) m_lScale = 1; return m_lScale; }
	
	inline const OTIdentifier & GetCurrencyID() const { return m_CURRENCY_TYPE_ID; }
	inline void SetCurrencyID(const OTIdentifier & CURRENCY_ID) { m_CURRENCY_TYPE_ID = CURRENCY_ID; }	

	// Buying or selling?
	inline bool IsBid() { return !m_bSelling; }
	inline bool IsAsk() { return m_bSelling; }
	
	// Stores a pointer to theTrade for later use. (Not responsible to clean up, just convenient.)
	inline OTTrade * GetTrade() { return m_pTrade; }
	inline void SetTrade(const OTTrade & theTrade) { m_pTrade = &((OTTrade &)theTrade); }
	
	// ----------------------------------------------------------
	
	OTOffer();		// The constructor contains the 3 variables needed to identify any market.
	OTOffer(const OTIdentifier & SERVER_ID, const OTIdentifier & ASSET_ID, const OTIdentifier & CURRENCY_ID, const long & MARKET_SCALE);
	virtual ~OTOffer();

	// Overridden from OTContract.
	virtual void GetIdentifier(OTIdentifier & theIdentifier);

	void InitOffer();

	virtual void Release();

	// return -1 if error, 0 if nothing, and 1 if the node was processed.
	virtual int ProcessXMLNode(irr::io::IrrXMLReader*& xml);

	virtual void UpdateContents(); // Before transmission or serialization, this is where the ledger saves its contents 

	virtual bool SaveContractWallet(std::ofstream & ofs);
};

#endif // __OTOFFER_H__




