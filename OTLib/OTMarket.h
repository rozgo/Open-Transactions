/************************************************************************************
 *    
 *  OTMarket.h
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

// A market has a list of OTOffers for all the bids, and another list of OTOffers for all the asks.
// Presumably the server will have different markets for different asset types.

#ifndef __OTMARKET_H__
#define __OTMARKET_H__

#include "OTContract.h"
#include "OTOffer.h"


// Multiple offers, mapped by price limit.
// Using multi-map since there will be more than one offer for each single price.
// (Map would only allow a single item on the map for each price.)
typedef std::multimap<long, OTOffer *>	mapOfOffers;

// The same offers are also mapped (uniquely) to transaction number.
typedef std::map  <long, OTOffer *>	mapOfOffersTrnsNum;


class OTMarket : public OTContract
{
private:
	
	OTCron *	m_pCron;	// The Cron object that owns this Market.

	
	mapOfOffers			m_mapBids;		// The buyers, ordered by price limit
	mapOfOffers			m_mapAsks;		// The sellers, ordered by price limit
	
	mapOfOffersTrnsNum	m_mapOffers;	// All of the offers on a single list, ordered by transaction number.
	
	OTIdentifier	m_SERVER_ID;	// Always store this in any object that's associated with a specific server.

	// Every market involves a certain asset type being traded in a certain currency.
	OTIdentifier	m_ASSET_TYPE_ID;	// This is the GOLD market. (Say.)	| (GOLD for
	OTIdentifier	m_CURRENCY_TYPE_ID;	// Gold is trading for DOLLARS.		|  DOLLARS, for example.)
	
	// Each Offer on the market must have a minimum increment that this divides equally into.
	// (There is a "gold for dollars, minimum 1 oz" market, a "gold for dollars, min 500 oz" market, etc.)
	long			m_lScale;

	// The server stores a map of markets, one for each unique combination of asset types.
	// That's what this market class represents: one asset type being traded and priced in another.
	// It could be wheat for dollars, wheat for yen, or gold for dollars, or gold for wheat, or
	// gold for oil, or oil for wheat.  REALLY, THE TWO ARE JUST ARBITRARY ASSET TYPES. But in 
	// order to keep terminology clear, I will refer to one as the "asset type" and the other as
	// the "currency type" so that it stays VERY clear which asset type is up for sale, and which
	// asset type (currency type) it is being priced in. Other than that, the two are technically
	// interchangeable.
	
public: 
	bool ValidateOfferForMarket(OTOffer & theOffer);
	
	OTOffer *	GetOffer(const long & lTransactionNum);
	bool		AddOffer(OTOffer & theOffer, bool bSaveFile=true);
	bool		RemoveOffer(const long & lTransactionNum);
	
	// -----------------------------------------------------

	// Assumes a few things: Offer is part of Trade, and both have been
	// proven already to be a part of this market.
	// Basically the Offer is looked up on the Market by the Trade, and
	// then both are passed in here.
	// --Returns True if Trade should stay on the Cron list for more processing.
	// --Returns False if it should be removed and deleted.
	void ProcessTrade(OTTrade & theTrade, OTOffer & theOffer, OTOffer & theOtherOffer);
	bool ProcessTrade(OTTrade & theTrade, OTOffer & theOffer);

	long	GetHighestBidPrice();
	long	GetLowestAskPrice();

	// -----------------------------------------------------
	
	inline void SetAssetID(const OTIdentifier &		ASSET_ID)		{ m_ASSET_TYPE_ID		= ASSET_ID; }
	inline void SetCurrencyID(const OTIdentifier &	CURRENCY_ID)	{ m_CURRENCY_TYPE_ID	= CURRENCY_ID; }
	inline void SetServerID(const OTIdentifier &	SERVER_ID)		{ m_SERVER_ID			= SERVER_ID; }
	
	inline const OTIdentifier & GetAssetID()	const { return m_ASSET_TYPE_ID; }
	inline const OTIdentifier & GetCurrencyID()	const { return m_CURRENCY_TYPE_ID; }
	inline const OTIdentifier & GetServerID()	const { return m_SERVER_ID; }	
	
	inline const long & GetScale() 
		{ if (m_lScale < 1) m_lScale = 1; return m_lScale; }
	inline void SetScale(const long & lScale) 
		{ m_lScale = lScale; if (m_lScale < 1) m_lScale = 1; }

	// -----------------------------------------------------
	
	OTMarket();
	OTMarket(const char * szFilename);
	OTMarket(const OTIdentifier & SERVER_ID, const OTIdentifier & ASSET_TYPE_ID,
			 const OTIdentifier & CURRENCY_TYPE_ID, const long & lScale);
	virtual ~OTMarket();
	
	
	// Overridden from OTContract.
	virtual void GetIdentifier(OTIdentifier & theIdentifier);
	
	inline void SetCronPointer(OTCron & theCron) { m_pCron = &theCron; }	
	inline OTCron * GetCron() { return m_pCron; }
	
	// -----------------------------------------------------

	bool LoadMarket();
	bool SaveMarket();
	
	void InitMarket();
	
	virtual void Release();

	// return -1 if error, 0 if nothing, and 1 if the node was processed.
	virtual int ProcessXMLNode(irr::io::IrrXMLReader*& xml);
	
	virtual void UpdateContents(); // Before transmission or serialization, this is where the ledger saves its contents 
	
	virtual bool SaveContractWallet(std::ofstream & ofs);	
};

#endif // __OTMARKET_H__















