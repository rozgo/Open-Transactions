/************************************************************************************
 *    
 *  OTTrade.cpp
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


#include "OTIdentifier.h"
#include "OTCron.h"
#include "OTTrade.h"
#include "OTOffer.h"
#include "OTMarket.h"
#include "OTLog.h"



#ifndef TRADE_PROCESS_INTERVAL	

#define TRADE_PROCESS_INTERVAL		10		// 10 seconds

#endif


// This class is like: you are placing an order to do a trade.
// Your order will continue processing until it is complete.
// PART of that process is putting an offer on the market. See OTOffer for that.
//
// Trades are like cron items, they can expire, they can have rules.
//
// An OTTrade is derived from OTCronItem. OTCron has a list of those items.





// -------------------------------------------------------------

// return -1 if error, 0 if nothing, and 1 if the node was processed.
int OTTrade::ProcessXMLNode(irr::io::IrrXMLReader*& xml)
{
	int nReturnVal = 0;

	// Here we call the parent class first.
	// If the node is found there, or there is some error,
	// then we just return either way.  But if it comes back
	// as '0', then nothing happened, and we'll continue executing.
	//
	// -- Note you can choose not to call the parent if
	// you don't want to use any of those xml tags.
	// As I do below, in the case of OTAccount.
	//if (nReturnVal = OTContract::ProcessXMLNode(xml))
	//	return nReturnVal;


	if (!strcmp("trade", xml->getNodeName())) 
	{
		m_strVersion		=		xml->getAttributeValue("version");
		m_nTradesAlreadyDone= atoi(	xml->getAttributeValue("completedNoTrades"));
		
		SetTransactionNum(	atol(xml->getAttributeValue("transactionNum")) );
		SetCreationDate(	atoi(xml->getAttributeValue("creationDate")));
		SetValidFrom(		atoi(xml->getAttributeValue("validFrom")));
		SetValidTo(			atoi(xml->getAttributeValue("validTo")));
		
		// ---------------------
		
		OTString strActivated(xml->getAttributeValue("hasActivated"));
		
		if (strActivated.Compare("true"))
			m_bHasTradeActivated = true;
		else
			m_bHasTradeActivated = false;
		
		
		// ---------------------
		
		const OTString	strServerID(xml->getAttributeValue("serverID")),
						strUserID(xml->getAttributeValue("userID")),
						strAssetTypeID(xml->getAttributeValue("assetTypeID")),
						strAssetAcctID(xml->getAttributeValue("assetAcctID")),
						strCurrencyTypeID(xml->getAttributeValue("currencyTypeID")),
						strCurrencyAcctID(xml->getAttributeValue("currencyAcctID"));
		
		const OTIdentifier	SERVER_ID(strServerID),					USER_ID(strUserID),		
							ASSET_TYPE_ID(strAssetTypeID),			ASSET_ACCT_ID(strAssetAcctID),
							CURRENCY_TYPE_ID(strCurrencyTypeID),	CURRENCY_ACCT_ID(strCurrencyAcctID);
		
		SetServerID(SERVER_ID);
		SetSenderUserID(USER_ID);
		SetAssetID(ASSET_TYPE_ID);
		SetSenderAcctID(ASSET_ACCT_ID);
		SetCurrencyID(CURRENCY_TYPE_ID);
		SetCurrencyAcctID(CURRENCY_ACCT_ID);
		
		// ---------------------
		
		OTLog::vOutput(0, "\n\nTrade. Transaction Number: %ld   Completed # of Trades: %d\n", 
					   m_lTransactionNum, m_nTradesAlreadyDone);
		
		OTLog::vOutput(1,
					   " Creation Date: %d   Valid From: %d\n Valid To: %d\n"
					   " assetTypeID: %s\n assetAcctID: %s\n"
					   " ServerID: %s\n UserID: %s\n "
					   " currencyTypeID: %s\n currencyAcctID: %s\n ", 
					   GetCreationDate(), GetValidFrom(), GetValidTo(),
					   strAssetTypeID.Get(), strAssetAcctID.Get(),
					   strServerID.Get(), strUserID.Get(), 
					   strCurrencyTypeID.Get(), strCurrencyAcctID.Get());
		
		nReturnVal = 1;
	}
	
	if (!strcmp("stopOrder", xml->getNodeName())) 
	{		
		OTString strSign(xml->getAttributeValue("sign"));
		
		if (strSign.Compare("0"))
		{
			m_cStopSign = 0; // Zero means it isn't a stop order. So why is the tag in the file?
			OTLog::vError("Strange: Stop order tag found in trade, but sign character set to 0.\n"
						  "(Zero means: NOT a stop order.)\n", strSign.Get());
			return (-1);
		}
		else if (strSign.Compare("<"))
			m_cStopSign = '<';
		else if (strSign.Compare(">"))
			m_cStopSign = '>';
		else
		{
			m_cStopSign = 0;
			OTLog::vError("Unexpected or nonexistent value in stop order sign: %s\n", strSign.Get());
			return (-1);
		}
		// ---------------------
		
		// Now we know the sign is properly formed, let's grab the price value.
		
		m_lStopPrice = atol(xml->getAttributeValue("price"));
		
		// ---------------------
		
		OTString strActivated(xml->getAttributeValue("hasActivated"));

		if (strActivated.Compare("true"))
			m_bHasStopActivated = true;
		else
			m_bHasStopActivated = false;

		// ---------------------
		
		OTLog::vOutput(1,
					   "\n\nStop order -- %s when price %s %s: %ld.\n",
					   (m_bHasStopActivated ? "Already activated" : "Will activate"), 					   
					   (m_bHasStopActivated ? "was" : "reaches"), 					   
					   (('<' == m_cStopSign) ? "LESS THAN" : "GREATER THAN"), 
					   m_lStopPrice);
		
		nReturnVal = 1;
	}
	
	else if (!strcmp("offer", xml->getNodeName())) 
	{		
		if (false == LoadEncodedTextField(xml, m_strOffer))
		{
			OTLog::Error("Error in OTTrade::ProcessXMLNode: offer field without value.\n");
			return (-1); // error condition
		}
		
		nReturnVal = 1;
	}
		
	return nReturnVal;
}


void OTTrade::UpdateContents()
{
	// I release this because I'm about to repopulate it.
	m_xmlUnsigned.Release();
	
	m_xmlUnsigned.Concatenate("<?xml version=\"%s\"?>\n\n", "1.0");		
	
	// -------------------------------------------------------------
	
	const OTString	SERVER_ID(GetServerID()),			USER_ID(GetSenderUserID()),
					ASSET_TYPE_ID(GetAssetID()),		ASSET_ACCT_ID(GetSenderAcctID()),
					CURRENCY_TYPE_ID(GetCurrencyID()),	CURRENCY_ACCT_ID(GetCurrencyAcctID());
	
	m_xmlUnsigned.Concatenate("<trade\n version=\"%s\"\n"
							  " hasActivated=\"%s\"\n"
							  " serverID=\"%s\"\n"
							  " assetTypeID=\"%s\"\n"
							  " assetAcctID=\"%s\"\n"
							  " currencyTypeID=\"%s\"\n"
							  " currencyAcctID=\"%s\"\n"
							  " userID=\"%s\"\n"
							  " completedNoTrades=\"%d\"\n"
							  " transactionNum=\"%ld\"\n"
							  " creationDate=\"%d\"\n"
							  " validFrom=\"%d\"\n"
							  " validTo=\"%d\""							  
							  " >\n\n", 
							  m_strVersion.Get(),
							  (m_bHasTradeActivated ? "true" : "false"),
							  SERVER_ID.Get(),
							  ASSET_TYPE_ID.Get(), 
							  ASSET_ACCT_ID.Get(),
							  CURRENCY_TYPE_ID.Get(),
							  CURRENCY_ACCT_ID.Get(),
							  USER_ID.Get(),
							  m_nTradesAlreadyDone,
							  m_lTransactionNum,
							  GetCreationDate(), 
							  GetValidFrom(), GetValidTo() );	
	
	// -------------------------------------------------------------
	
	if (('<' == m_cStopSign) || ('>' == m_cStopSign))
	{		
		m_xmlUnsigned.Concatenate("<stopOrder\n"
								  " hasActivated=\"%s\"\n"
								  " sign=\"%c\"\n"
								  " price=\"%ld\""
								  " />\n\n", 
								  (m_bHasStopActivated ? "true" : "false"),
								  m_cStopSign, 
								  m_lStopPrice);								  		
	}
		
	// -------------------------------------------------------------
	
	if (m_strOffer.Exists())
	{
		OTASCIIArmor ascOffer(m_strOffer);		
		m_xmlUnsigned.Concatenate("<offer>\n%s</offer>\n\n", ascOffer.Get());
	}
	
	// -------------------------------------------------------------
	
	m_xmlUnsigned.Concatenate("</trade>\n");					
}



// The trade stores a copy of the Offer in string form.
// This function verifies that offer against the trade,
// and also verifies the signature on the offer.
//
// The Nym's ID is compared to theOffer's SenderUserID, and then the Signature is checked
// on the offer.  It also compares the server ID, asset and currency IDs, transaction #, etc
// between this trade and the offer, in order to fully verify the offer's authenticity.
//
bool OTTrade::VerifyOffer(OTOffer & theOffer)
{
	// At this point, I have a working, loaded, model of the Offer.
	// Let's verify the thing.
	
	if (GetTransactionNum() != theOffer.GetTransactionNum())
	{
		OTLog::Error("While verifying offer, failed matching transaction number.\n");
		return false;
	}
	else if (GetServerID() != theOffer.GetServerID())
	{
		OTLog::Error("While verifying offer, failed matching Server ID.\n");
		return false;
	}
	else if (GetAssetID() != theOffer.GetAssetID())
	{
		OTLog::Error("While verifying offer, failed matching asset type ID.\n");
		return false;
	}
	else if (GetCurrencyID() != theOffer.GetCurrencyID())
	{
		OTLog::Error("While verifying offer, failed matching currency type ID.\n");
		return false;
	}
	
	// the Offer validates properly for this Trade.
	return true;
}


// Assuming the offer is ON the market, this will get the pointer to that offer.
// Otherwise it will try to add it to the market.
OTOffer	* OTTrade::GetOffer(OTIdentifier * pOFFER_MARKET_ID/*=NULL*/, OTMarket ** ppMarket/*=NULL*/)
{
	OT_ASSERT(NULL != GetCron());
			  
	// See if the offer has already been instantiated.
	if (NULL != m_pOffer)
	{
		m_pOffer->SetTrade(*this);	// Probably don't need this one. I'll remove it someday while optimizing.
		return m_pOffer;			// In fact since it should already be set, having this here would basically
									// hide it from me if the memory was ever walked on from a bug somewhere.
	}
	
	if (!m_strOffer.Exists())
	{
		OTLog::Error("OTTrade::GetOffer called with empty m_strOffer.\n");
		return NULL;
	}
	
	OTOffer * pOffer = new OTOffer();
	
	OT_ASSERT(NULL != pOffer);

	// --------------------------------------------------
	
	// Trying to load the offer from the trader's original signed request
	// (So I can use it to lookup the Market ID, so I can see the offer is
	// already there on the market.)
	if (!pOffer->LoadContractFromString(m_strOffer))
	{
		OTLog::Error("Error loading offer from string in OTTrade::GetOffer\n");
		delete pOffer; pOffer = NULL;
		return NULL;
	}
	
	// No need to do any additional security verification here on the Offer,
	// since the Offer is already heavily verified in OTServer::NotarizeMarketOffer().
	// So as long as you feel safe about the Trade, then you can feel safe about
	// the Offer already, with no further checks.
	// *Also remember we saved a copy of the original in the cron folder.
	
	// It loaded. Let's get the Market ID off of it so we can locate the market.
	OTIdentifier OFFER_MARKET_ID(*pOffer);
	
	if (NULL != pOFFER_MARKET_ID)
	{
		// Sometimes the caller function would like a copy of this ID. So I 
		// give the option to pass in a pointer so I can give it here.
		pOFFER_MARKET_ID->Assign(OFFER_MARKET_ID);
	}
	
	
	// Previously if a user tried to use a market that didn't exist, I'd just return failure.
	// But now we will create any market that doesn't already exist.
	// (Remember, the server operator could just erase the market folder--it wouldn't 
	// affect anyone's balances!)
	//
//	OTMarket * pMarket = m_pCron->GetMarket(OFFER_MARKET_ID);
	OTMarket * pMarket = GetCron()->GetOrCreateMarket(GetAssetID(), GetCurrencyID(), pOffer->GetScale()); 

	
	// Couldn't find (or create) the market.
	if (NULL == pMarket)
	{
		OTLog::Output(3, "Unable to find or create market within requested parameters in OTTrade::GetOffer.");
		delete pOffer; pOffer = NULL;
		return NULL;
	}
	
	// If the caller passed in the address of a market pointer (optional)
	if (NULL != ppMarket)
	{
		// Sometimes the caller function would like a copy of this market pointer, when available.
		// So I pass it back to him here, if he wants. That way he doesn't have to do this work again
		// to look it up.
		*ppMarket = pMarket;
	}
	
	// --------------------------------------------------
	
	// At this point, I have heap-allocated the offer, used it to get the Market ID, and successfully
	// used that to get a pointer to the market matching that ID.
	//
	// Let's see if the offer is ALREADY allocated and on this market! 
	// If so, delete the one I just allocated. If not, add it to the market.
	OTOffer * pMarketOffer = pMarket->GetOffer(pOffer->GetTransactionNum());
	
	// The Offer is already on the Market.
	// NOTE: It may just start out this way, without ever being added.
	// How is that possible? Because maybe it was in the market file when we first loaded up,
	// and had been added on some previous run of the software. So since we started running,
	// the pMarket->AddOffer() code below has literally never run for that offer. Instead we
	// first find it here, and thus return the pointer before getting any farther.
	//
	// IN ALL CASES, we make sure to call m_pOffer->SetTrade() so that it has a pointer BACK to
	// this Trade object! (When actually processing the offer, the market will need the account
	// numbers and Nym IDs... which are stored here on the trade.)
	if (NULL != pMarketOffer)
	{
		m_pOffer = pMarketOffer;
		
		// Since the Offer already exists on the market, no need anymore for the
		// one we allocated above (to get the market ID.) So we delete it now.
		delete pOffer;
		pOffer = NULL;
		
		m_pOffer->SetTrade(*this);
		
		return m_pOffer;
	}
	
	// Okay so the offer ISN'T already on the market. If it's not a stop order, let's ADD the one we
	// allocated to the market now! (Stop orders are activated through their own logic, which is in the else.)
	if (!IsStopOrder())
	{
		if (m_bHasTradeActivated)
		{
			// Error -- how has the trade already activated, yet not on the market and null in my pointer?
			OTLog::Error("How has the trade already activated, yet not on the market and null in my pointer?\n");			
		}
		else if (!pMarket->AddOffer(*pOffer, true))	// Since we're actually adding an offer to the market (not just
		{											// loading from disk) the we actually want to save the market. bSaveFile=true.
			
			// Error adding the offer to the market!
			OTLog::Error("Error adding the offer to the market! (Even though supposedly the right market.)\n");
		}
		else 
		{
			// SUCCESS!
			m_pOffer = pOffer;
			
			m_bHasTradeActivated = true;
			
			// The Trade (stored on Cron) has a copy of the Original Offer, with the User's signature on it.
			// A copy of that original Trade object (itself with the user's signature) is already stored in
			// the cron folder (by transaction number.) This happens when the Trade is FIRST added to cron,
			// so it's already safe before we even get here.
			//
			// So thus I am FREE to release the signatures on the offer, and sign with the server instead.
			// The server-signed offer will be stored by the OTMarket.
			m_pOffer->ReleaseSignatures();
			m_pOffer->SignContract(*(GetCron()->GetServerNym()));
			m_pOffer->SaveContract();
			
			pMarket->SaveMarket();
			
			// Now when the market loads next time, it can verify this offer using the server's signature,
			// instead of having to load the user. Because the server has verified it and added it, and now
			// signs it, vouching for it.
			
			
			// The Trade itself (all its other variables) are now allowed to change, since its signatures
			// are also released and it is now server-signed. (With a copy stored of the original.)

			m_pOffer->SetTrade(*this);

			return m_pOffer;
		}
	}
	else if(IsStopOrder() && !m_bHasStopActivated) // It's a stop order. Should we activate it now?
	{
		long lRelevantPrice = 0;
		
		// If the stop order is trying to sell something, then it cares about the highest bidder.
		if (pOffer->IsAsk()) 
			lRelevantPrice = pMarket->GetHighestBidPrice();
		else // But if the stop order is trying to buy something, then it cares about the lowest ask price.
			lRelevantPrice = pMarket->GetLowestAskPrice();
		
		// It's a stop order that hasn't activated yet. SHOULD IT ACTIVATE NOW?
		if ((IsGreaterThan()	&& (lRelevantPrice > GetStopPrice())) ||
			(IsLessThan()		&& (lRelevantPrice < GetStopPrice())))
		{
			// Activate the stop order!
			if (!pMarket->AddOffer(*pOffer, true))	// Since we're actually adding an offer to the market (not just
			{										// loading from disk) the we actually want to save the market. bSaveFile=true.
				// Error adding the offer to the market!
				OTLog::Error("Error adding the stop order to the market! (Even though supposedly the right market.)\n");
			}
			else 
			{
				// SUCCESS!
				m_pOffer = pOffer;
				
				m_bHasStopActivated		= true;
				m_bHasTradeActivated	= true;
				
				// The Trade (stored on Cron) has a copy of the Original Offer, with the User's signature on it.
				// A copy of that original Trade object (itself with the user's signature) is already stored in
				// the cron folder (by transaction number.) This happens when the Trade is FIRST added to cron,
				// so it's already safe before we even get here.
				//
				// So thus I am FREE to release the signatures on the offer, and sign with the server instead.
				// The server-signed offer will be stored by the OTMarket.
				m_pOffer->ReleaseSignatures();
				m_pOffer->SignContract(*(GetCron()->GetServerNym()));
				m_pOffer->SaveContract();
				
				pMarket->SaveMarket();
				
				// Now when the market loads next time, it can verify this offer using the server's signature,
				// instead of having to load the user. Because the server has verified it and added it, and now
				// signs it, vouching for it.
				
				
				// The Trade itself (all its other variables) are now allowed to change, since its signatures
				// are also released and it is now server-signed. (With a copy stored of the original.)
				
				
				m_pOffer->SetTrade(*this);

				return m_pOffer;
			}
		}		
	}

	delete pOffer;
	pOffer = NULL;

	return NULL;
}




// OTCron calls this regularly, which is my chance to expire, etc.
// Return True if I should stay on the Cron list for more processing.
// Return False if I should be removed and deleted.
bool OTTrade::ProcessCron()
{	
	// -----------------------------------------------------------------
	// Right now Cron is called 10 times per second.
	// I'm going to slow down all trades so they are once every GetProcessInterval()
	if (GetLastProcessDate() > 0)
	{
		// (Default ProcessInternal is 1 second, but Trades will use 10 seconds,
		// and Payment Plans will use an hour or day.)
		if ((GetCurrentTime() - GetLastProcessDate()) <= GetProcessInterval())
			return true;
	}
	// Keep a record of the last time this was processed.
	// (NOT saved to storage, only used while the software is running.)
	// (Thus no need to release signatures, sign contract, save contract, etc.)
	SetLastProcessDate(GetCurrentTime());
	// -----------------------------------------------------------------

	
	// PAST END DATE? --------------------------------
	// First call the parent's version (which this overrides) so it has
	// a chance to check its stuff. Currently it checks IsExpired().
	if (!OTCronItem::ProcessCron())
		return false;	// It's expired--remove it from Cron.

	
	// REACHED START DATE? --------------------------------
	// Okay, so it's not expired. But might not have reached START DATE yet...
	if (!VerifyCurrentDate())
		return true;	// The Trade is not yet valid, so we return. BUT, we return 
						//  true, so it will stay on Cron until it BECOMES valid.
	
	
	
	// TRADE-specific stuff below. --------------------------------
	
	bool bStayOnMarket = true; // by default stay on the market (until some rule expires me.)
	
	OTIdentifier OFFER_MARKET_ID;
	OTMarket * pMarket = NULL;
	
	// If the Offer is already active on a market, then I already have a pointer to
	// it. This function returns that pointer. If NULL, it tries to find the offer on
	// the market and then sets the pointer and returns. If it can't find it, IT TRIES
	// TO ADD IT TO THE MARKET and sets the pointer and returns it.
	OTOffer * pOffer = GetOffer(&OFFER_MARKET_ID, &pMarket); // Both of these parameters are optional.

	
	// In this case, the offer is NOT on the market. 
	// Perhaps it wasn't ready to activate yet.
	if (NULL == pOffer)
	{
		// The offer SHOULD HAVE been on the market, since we're within the valid range,
		// and GetOffer adds it when it's not already there.
//		OTLog::Error("OTTrade::ProcessCron: Offer SHOULD have been on Market. I might ASSERT this.\n");
		
		// Actually! If it's a Stop Order, then it WOULD be within the valid range, yet would
		// not yet have activated. So I don't want to log some big error every time a stop order
		// checks its prices.
	}	
	else if (NULL == pMarket)
	{
		//todo. (This will already leave a log above in GetOffer somewhere.)
	}	
	else  // If a valid pointer was returned, that means the offer is on the market.
	{
		// Make sure it hasn't already been flagged by someone else...
		if (this->IsFlaggedForRemoval())
			bStayOnMarket = false;
		else
		{ // Process it!  <===================
			bStayOnMarket = pMarket->ProcessTrade(*this, *pOffer);
			// No need to save the Trade or Offer, since they will
			// be saved inside this call if they are changed.
		}			
	}
	
	// The offer needs to be removed from the market.
	// (Which means this trade also needs to be removed from Cron.
	// I assume calling function will do that.)
	if (!bStayOnMarket)
	{
		pMarket->RemoveOffer(GetTransactionNum());
	}

	// Return True if I should stay on the Cron list for more processing.
	// Return False if I should be removed and deleted.
	return bStayOnMarket; // defaults true, so if false, that means someone is removing it for a reason.
}


/*
X OTIdentifier	m_CURRENCY_TYPE_ID;	// GOLD (Asset) is trading for DOLLARS (Currency).
X OTIdentifier	m_CURRENCY_ACCT_ID;	// My Dollar account, used for paying for my Gold (say) trades.

X long			m_lStopPrice;		// The price limit that activates the STOP order.
X char			m_cStopSign;		// Value is 0, or '<', or '>'.

X time_t		m_CREATION_DATE;	// The date, in seconds, when the trade was authorized.
X int			m_nTradesAlreadyDone;	// How many trades have already processed through this order? We keep track.
*/

// This is called by the client side. First you call MakeOffer() to set up the Offer,
// then you call IssueTrade() and pass the Offer into it here.
bool OTTrade::IssueTrade(OTOffer & theOffer, char cStopSign/*=0*/, long lStopPrice/*=0*/)
{
	// Make sure the Stop Sign is within parameters (0, '<', or '>')
	if ((cStopSign ==  0 )	||
		(cStopSign == '<')	||
		(cStopSign == '>'))
		m_cStopSign = cStopSign;
	else
	{
		OTLog::vError("Bad data in Stop Sign while issuing trade: %c\n", cStopSign);
		return false;
	}
	
	// Make sure, if this IS a Stop order, that the price is within parameters and set.
	if ((m_cStopSign == '<')	||
		(m_cStopSign == '>'))
	{
		if (0 >= lStopPrice)
		{
			OTLog::Error("Expected Stop Price for trade.\n");
			return false;
		}
		
		m_lStopPrice = lStopPrice;
	}

	m_nTradesAlreadyDone	= 0;
	
	SetCreationDate(time(NULL)); // This time is set to TODAY NOW  (OTCronItem)
	
	// ------------------------------------------------------------------------
	
	// Validate the Server ID, Asset Type ID, Currency Type ID, and Date Range.
	if ((GetServerID()			!= theOffer.GetServerID())		||
		(GetCurrencyID()		!= theOffer.GetCurrencyID())	||
		(GetAssetID()			!= theOffer.GetAssetID())		||
		
		(theOffer.GetValidFrom() <	0)							||
		(theOffer.GetValidTo()	 < theOffer.GetValidFrom())	)
	{
		return false;
	}
	
//	m_CURRENCY_TYPE_ID // This is already set in the constructors of this and the offer. (And compared.)
//	m_CURRENCY_ACCT_ID // This is already set in the constructor of this.
	
	// Set the (now validated) date range as per the Offer.
	SetValidFrom(theOffer.GetValidFrom());
	SetValidTo(theOffer.GetValidTo());
	
	// Get the transaction number from the Offer.
	SetTransactionNum(theOffer.GetTransactionNum());
	
	// Save a copy of the offer, in XML form, here on this Trade.
	OTString strOffer(theOffer);
	m_strOffer.Set(strOffer);
	
	return true;
}


OTTrade::OTTrade() : OTCronItem()
{
	m_bRemovalFlag		= false;
	m_pOffer			= NULL;	// NOT responsible to clean this up. Just keeping the pointer for convenience.
								// You might ask, "but what if it goes bad?" Actually only THIS object should ever decide that.
								// Only the Trade object decides when to add or remove an offer from any market.
	
	InitTrade();
}

OTTrade::OTTrade(const OTIdentifier & SERVER_ID, const OTIdentifier & ASSET_ID) :
			OTCronItem(SERVER_ID, ASSET_ID)
{
	m_bRemovalFlag		= false;
	m_pOffer			= NULL;	// NOT responsible to clean this up. Just keeping the pointer for convenience.
								// You might ask, "but what if it goes bad?" Actually only THIS object should ever decide that.
								// Only the Trade object decides when to add or remove an offer from any market.
	
	InitTrade();
}


OTTrade::OTTrade(const OTIdentifier & SERVER_ID, 
				 const OTIdentifier & ASSET_ID, const OTIdentifier & ASSET_ACCT_ID, 
				 const OTIdentifier & USER_ID, 
				 const OTIdentifier & CURRENCY_ID, const OTIdentifier & CURRENCY_ACCT_ID) :
			OTCronItem(SERVER_ID, ASSET_ID, ASSET_ACCT_ID, USER_ID)
{
	m_bRemovalFlag		= false;
	m_pOffer			= NULL;	// NOT responsible to clean this up. Just keeping the pointer for convenience.
								// You might ask, "but what if it goes bad?" Actually only THIS object should ever decide that.
								// Only the Trade object decides when to add or remove an offer from any market.

	InitTrade();

	SetCurrencyID(CURRENCY_ID);
	SetCurrencyAcctID(CURRENCY_ACCT_ID);
}

OTTrade::~OTTrade()
{
	// no need to call Release(), the framework will call it.
}


// This CAN have values that are reset 
void OTTrade::InitTrade()
{
	// initialization here. Sometimes also called during cleanup to zero values.
	m_strContractType	= "TRADE";
	
	SetProcessInterval(TRADE_PROCESS_INTERVAL);	// Trades default to processing every 10 seconds. 
												// (vs 1 second for Cron items and 1 hour for payment plans)

	m_nTradesAlreadyDone= 0;
	
	m_cStopSign		= 0;		// IS THIS a STOP order? Value is 0, or '<', or '>'. 
	m_lStopPrice	= 0;		// The price limit that activates the STOP order.
	m_bHasStopActivated	= false;// Once the Stop Order activates, it puts the order on the market.
								// I'll put a "HasOrderOnMarket()" bool method that answers this for u.
	m_bHasTradeActivated = false;// I want to keep track of general activations as well, not just stop orders.
}

// the framework will call this at the right time.
void OTTrade::Release()
{
	// If there were any dynamically allocated objects, clean them up here.
	m_CURRENCY_TYPE_ID.Release();
	m_CURRENCY_ACCT_ID.Release();
	
	m_strOffer.Release();
	
	OTCronItem::Release(); // since I've overridden the base class, I call it now...
	
	// Then I call this to re-initialize everything
	// (Only cause it's convenient...)
	InitTrade();
}




bool OTTrade::SaveContractWallet(std::ofstream & ofs)
{
	return true;
}

