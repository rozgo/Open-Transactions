/************************************************************************************
 *    
 *  OTTrade.h
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


// An OTTrade is derived from OTCronItem. OTCron has a list of items, 
// which may be trades or agreements or who knows what next.
//

#ifndef __OTTRADE_H__
#define __OTTRADE_H__

//#include <ctime> // already included in parent somewhere.

#include "OTString.h"
#include "OTCronItem.h"
#include "OTOffer.h"

class OTIdentifier;



/*
 OTTrade
 
 Standing Order (for Trades) MUST STORE:
 
 X 1) Transaction ID // It took a transaction number to create this trade. We record it here and use it to uniquely identify the trade, like any other transaction.
 X 4) CURRENCY TYPE ID  (Currency type ID of whatever I’m trying to buy or sell WITH. Dollars? Euro?)
 X 5) Account ID SENDER (for above currency type. This is the account where I make my payments from, to satisfy the trades.)
 X 6) Valid date range. (Start. Expressed as an absolute date.)
 X 7) Valid date range. ( End. Expressed as an absolute date.)

 X 2) Creation date.
 X 3) INTEGER: Number of trades that have processed through this order.

 X 8) STOP ORDER — SIGN (NULL if not a stop order — otherwise GREATER THAN or LESS THAN…)
 X 9) STOP ORDER — PRICE (…AT X PRICE, POST THE OFFER TO THE MARKET.)
 
 Cron for these orders must check expiration dates and stop order prices.
 
 ———————————————————————————————
 */

class OTTrade : public OTCronItem
{
private:
	OTIdentifier	m_CURRENCY_TYPE_ID;	// GOLD (Asset) is trading for DOLLARS (Currency).
	OTIdentifier	m_CURRENCY_ACCT_ID;	// My Dollar account, used for paying for my Gold (say) trades.
	
	bool		m_bHasTradeActivated;	// Has the offer yet been first added to a market?
	
	long		m_lStopPrice;			// The price limit that activates the STOP order.
	char		m_cStopSign;			// Value is 0, or '<', or '>'.
	bool		m_bHasStopActivated;	// If the Stop Order has already activated, I need to know that.
	
	int			m_nTradesAlreadyDone;	// How many trades have already processed through this order? We keep track.

	OTString	m_strOffer;				// The market offer associated with this trade.
	
	OTOffer		* m_pOffer;				// The pointer to the Offer (NOT responsible for cleaning this up!!!
										// The offer is owned by the market and I only keep a pointer here for convenience.
	
	bool		m_bRemovalFlag;			// Set this to true and the trade will be removed from Cron on next process.
										// (And its offer will be removed from the Market as well.)
	
public:
	bool	VerifyOffer(OTOffer & theOffer);
	
	bool	IssueTrade(OTOffer & theOffer, char cStopSign=0, long lStopPrice=0);
	
	// The Trade always stores the original, signed version of its Offer.
	// This method allows you to grab a copy of it.
	inline bool GetOfferString(OTString & strOffer) 
	{ strOffer.Set(m_strOffer); return m_strOffer.Exists() ? true : false; }
	
	inline bool	IsStopOrder() const { if ((m_cStopSign == '<') || (m_cStopSign == '>')) return true; return false; }
	
	inline const long & GetStopPrice() const { return m_lStopPrice; }
	
	inline bool IsGreaterThan()	const { if ((m_cStopSign == '>')) return true; return false; }
	inline bool IsLessThan()	const { if ((m_cStopSign == '<')) return true; return false; }
	
	// optionally returns the offer's market ID and a pointer to the market.
	OTOffer	* GetOffer(OTIdentifier * pOFFER_MARKET_ID=NULL, OTMarket ** ppMarket=NULL); 
	
	// --------------------------------------------------------------------------

	inline const OTIdentifier & GetCurrencyID() const { return m_CURRENCY_TYPE_ID; }
	inline void SetCurrencyID(const OTIdentifier & CURRENCY_ID) { m_CURRENCY_TYPE_ID = CURRENCY_ID; }	
	
	inline const OTIdentifier & GetCurrencyAcctID() const { return m_CURRENCY_ACCT_ID; }
	inline void SetCurrencyAcctID(const OTIdentifier & CURRENCY_ACCT_ID) { m_CURRENCY_ACCT_ID = CURRENCY_ACCT_ID; }	
	
	// --------------------------------------------------------------------------

	inline void FlagForRemoval() { m_bRemovalFlag = true; }
	inline bool IsFlaggedForRemoval() const { return m_bRemovalFlag; }
	
	inline void IncrementTradesAlreadyDone() { m_nTradesAlreadyDone++; } 
	
	// --------------------------------------------------------------------------

	// From OTCronItem (parent class of this)
	/*
	 inline void SetCronPointer(OTCron & theCron) { m_pCron = &theCron; }

	 inline void SetCreationDate(const time_t & CREATION_DATE) { m_CREATION_DATE = CREATION_DATE; }
	 inline const time_t & GetCreationDate() const { return m_CREATION_DATE; }
	 */
	// Return True if should stay on OTCron's list for more processing.
	// Return False if expired or otherwise should be removed.
	virtual bool ProcessCron(); // OTCron calls this regularly, which is my chance to expire, etc.
	
	// --------------------------------------------------------------------------

	// From OTTrackable (parent class of OTCronItem, parent class of this)
	/*
	 inline long GetTransactionNum() const { return m_lTransactionNum; }
	 inline void SetTransactionNum(long lTransactionNum) { m_lTransactionNum = lTransactionNum; }

	 inline const OTIdentifier & GetSenderAcctID()	{ return m_SENDER_ACCT_ID; }
	 inline const OTIdentifier & GetSenderUserID()	{ return m_SENDER_USER_ID; }
	 inline void	SetSenderAcctID(const OTIdentifier & ACCT_ID)	{ m_SENDER_ACCT_ID = ACCT_ID; }
	 inline void	SetSenderUserID(const OTIdentifier & USER_ID)	{ m_SENDER_USER_ID = USER_ID; }
	 */
	
	// --------------------------------------------------------------------------

	// From OTInstrument (parent class of OTTrackable, parent class of OTCronItem, parent class of this)
	/*
	 OTInstrument(const OTIdentifier & SERVER_ID, const OTIdentifier & ASSET_ID) : OTContract()
	 
	 inline const OTIdentifier &	GetAssetID() const { return m_AssetTypeID; }
	 inline const OTIdentifier &	GetServerID() const { return m_ServerID; }
	 
	 inline void					SetAssetID(const OTIdentifier & ASSET_ID)  { m_AssetTypeID	= ASSET_ID; }
	 inline void					SetServerID(const OTIdentifier & SERVER_ID) { m_ServerID	= SERVER_ID; }
	 
	 inline time_t					GetValidFrom()	const { return m_VALID_FROM; }
	 inline time_t					GetValidTo()		const { return m_VALID_TO; }
	 
	 inline void					SetValidFrom(time_t TIME_FROM)	{ m_VALID_FROM	= TIME_FROM; }
	 inline void					SetValidTo(time_t TIME_TO)		{ m_VALID_TO	= TIME_TO; }
	 
	 bool VerifyCurrentDate(); // Verify the current date against the VALID FROM / TO dates.
	 */
	

	//----------------------------------------------------------------------
	
	OTTrade();
	OTTrade(const OTIdentifier & SERVER_ID, const OTIdentifier & ASSET_ID);
	OTTrade(const OTIdentifier & SERVER_ID, 
			const OTIdentifier & ASSET_ID, const OTIdentifier & ASSET_ACCT_ID, 
			const OTIdentifier & USER_ID, 
			const OTIdentifier & CURRENCY_ID, const OTIdentifier & CURRENCY_ACCT_ID);
	virtual ~OTTrade();

	void InitTrade();
	
	virtual void Release();
	
	// return -1 if error, 0 if nothing, and 1 if the node was processed.
	virtual int ProcessXMLNode(irr::io::IrrXMLReader*& xml);
	
	virtual void UpdateContents(); // Before transmission or serialization, this is where the ledger saves its contents 
	
	virtual bool SaveContractWallet(std::ofstream & ofs);
	
	
};


#endif // __OTTRADE_H__
