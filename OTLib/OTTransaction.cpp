/************************************************************************************
 *    
 *  OTTransaction.cpp
 *  
 */

/************************************************************
 -----BEGIN PGP SIGNED MESSAGE-----
 Hash: SHA256
 
 *                 OPEN TRANSACTIONS
 *
 *       Financial Cryptography and Digital Cash
 *       Library, Protocol, API, Server, and GUI 
 *    
 *    	 -- Anonymous Numbered Accounts.
 *    	 -- Untraceable Digital Cash.
 *    	 -- Triple-Signed Receipts.
 *    	 -- Cheques, Vouchers, Transfers, Inboxes.
 *    	 -- Basket Currencies, Markets, Payment Plans.
 *    	 -- Signed, XML, Ricardian-style Contracts.
 *    
 *  Copyright (C) 2010-2011 by "Fellow Traveler" (A pseudonym)
 *
 *  EMAIL:
 *  FellowTraveler@rayservers.net --- SEE PGP KEY BELOW.
 *  F3llowTraveler@gmail.com --- (not preferred.)
 *  
 *  BITCOIN:  1NtTPVVjDsUfDWybS4BwvHpG2pdS9RnYyQ
 *
 *  KEY FINGERPRINT:
 *  9DD5 90EB 9292 4B48 0484  7910 0308 00ED F951 BB8E
 *
 *  OFFICIAL PROJECT WIKI(s):
 *  http://wiki.github.com/FellowTraveler/Open-Transactions/wiki 
 *  http://wiki.github.com/FellowTraveler/Moneychanger/wiki 
 *
 *  WEBSITE:
 *  http://www.OpenTransactions.org/
 *    
 *  Components and licensing:
 *   -- Moneychanger..A Java client GUI.....LICENSE:.....GPLv3
 *   -- OTLib.........A class library.......LICENSE:...LAGPLv3 
 *   -- OT-API........A client API..........LICENSE:...LAGPLv3
 *   -- testwallet....Command-line client...LICENSE:...LAGPLv3
 *   -- OT-Server.....Server Application....LICENSE:....AGPLv3
 *  Github.com/FellowTraveler/Open-Transactions/wiki/Components
 *
 *  All of the above OT components were designed and written by
 *  Fellow Traveler, with the exception of Moneychanger, which
 *  was contracted out to Vicky C (livewire_3001@yahoo.com).
 *
 *  -----------------------------------------------------
 *
 *   LICENSE:
 *   This program is free software: you can redistribute it
 *   and/or modify it under the terms of the GNU Affero
 *   General Public License as published by the Free Software
 *   Foundation, either version 3 of the License, or (at your
 *   option) any later version.
 *    
 *   ADDITIONAL PERMISSION under the GNU Affero GPL version 3
 *   section 7: (This paragraph applies only to the LAGPLv3
 *   components listed above.) If you modify this Program, or
 *   any covered work, by linking or combining it with other
 *   code, such other code is not for that reason alone subject
 *   to any of the requirements of the GNU Affero GPL version 3.
 *   (==> This means if you are only using the OT-API, then you
 *   don't have to open-source your code--only your changes to
 *   Open Transactions itself must be open source. Similar to
 *   LGPLv3, except it applies to software-as-a-service, not
 *   just to distributing binaries.)
 *
 *   Extra WAIVER for OpenSSL, Lucre, and all other libraries
 *   used by Open Transactions: This program is released under
 *   the AGPL with the additional exemption that compiling,
 *   linking, and/or using OpenSSL is allowed. The same is true
 *   for any other open source libraries included in this
 *   project: complete waiver from the AGPL is hereby granted to
 *   compile, link, and/or use them with Open Transactions,
 *   according to their own terms, as long as the rest of the
 *   Open Transactions terms remain respected, with regard to
 *   the Open Transactions code itself.
 *    
 *   Lucre License:
 *   This code is also "dual-license", meaning that Ben Lau-
 *   rie's license must also be included and respected, since
 *   the code for Lucre is also included with Open Transactions.
 *   See Open-Transactions/OTLib/Lucre/LUCRE_LICENSE.txt
 *   The Laurie requirements are light, but if there is any
 *   problem with his license, simply remove the Lucre code.
 *   Although there are no other blind token algorithms in Open
 *   Transactions (yet. credlib is coming), the other functions
 *   will continue to operate.
 *   -----------------------------------------------------
 *   You should have received a copy of the GNU Affero General
 *   Public License along with this program.  If not, see:
 *   http://www.gnu.org/licenses/
 *
 *   If you would like to use this software outside of the free
 *   software license, please contact FellowTraveler.
 *   (Unfortunately many will run anonymously and untraceably,
 *   so who could really stop them?)
 *   
 *   DISCLAIMER:
 *   This program is distributed in the hope that it will be
 *   useful, but WITHOUT ANY WARRANTY; without even the implied
 *   warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *   PURPOSE.  See the GNU Affero General Public License for
 *   more details.
 
 -----BEGIN PGP SIGNATURE-----
 Version: GnuPG v1.4.10 (Darwin)
 
 iQIcBAEBCAAGBQJNsV9NAAoJEAMIAO35UbuOB3IP/12THBedTYrR2F2hkhYKK+0H
 YlVwRJyFnX3uKjDkYx2fpB2yNaMPPyiQRFpQBpiUxB2wSMHelM+m4YxVegx7h15s
 nD+jMLeVnlhgfKYsVZZiCKT58HXVsuGDc/iycXBBIQYBjCzbeCCG0vyEapR+sCwF
 eGR5l7yGbcMWaVqjPawqSMe/5Ie0wstWMrNAkLlWHRn/ISXb8vMusaxCe9kSeUX8
 7ZSZ0ojy3gLTZnUHFFZ2RaMepVB9jVoMSdVG89mEHX383foTuaxedjI2Wsw6J8YR
 D7PFp6PLGhm1eqArmotCj5NeV9lleULdnvR7T4QwzOZjI65kMwi/e1W6GyvzT3RZ
 RrLaZwiagcyKTXyEX5qSBQfSVNwC761rgNTG0fCBrBmDbQxet4A6Y+ZMxZmE0QXb
 Xch/g4g9Lki0TrSOx0zSAAcpLCIrqdvGX2jcmmJ/Ex4ZhzVhMvtkGfui9bUaY2bU
 bdu1GY0CfmElZ7+wXh2AutkMscRtnu62VSdGjrqry3KJMBWbtxNA9Q+U+NipWnYN
 yisBlQBADkXNtkL3EXEqX6OnjGfHNZ3G1bwuELcZjoOL+K0aQKCojRf8Ii5DW0A3
 niqzq/dwpt45VaQ+uYSG7Sg19FNvADg+WILdFcyszfS8Wks6BsKYzHUc5zbf3SFc
 JaOXLV9Ss58mj57JpNp8
 =VjLJ
 -----END PGP SIGNATURE-----
 **************************************************************/




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
#include "OTPseudonym.h"
#include "OTAccount.h"
#include "OTPayload.h"
#include "OTMessage.h"
#include "OTStringXML.h"

#include "OTCheque.h"
#include "OTItem.h"
#include "OTLedger.h"
#include "OTTransactionType.h"
#include "OTTransaction.h"
#include "OTLog.h"


const char * OTTransaction::_TypeStrings[] = 
{
	"blank",			// freshly issued, not used yet  // comes from server, stored on Nym.
	"message",			// in nymbox, message from one user to another.
	"pending",			// Pending transfer, in the inbox/outbox.
	// --------------------------------------------------------------------------------------
	"transferReceipt",	// the server drops this into your inbox, when someone accepts your transfer.
	// --------------------------------------------------------------------------------------
	"chequeReceipt",	// the server drops this into your inbox, when someone cashes your cheque.
	"marketReceipt",	// server drops this into inbox periodically, if you an offer on market.
	"paymentReceipt",	// the server drops this into people's inboxes, periodically.
	// --------------------------------------------------------------------------------------
	"processNymbox",	// process nymbox transaction	 // comes from client
	"atProcessNymbox",	// process nymbox reply			 // comes from server
	"processInbox",		// process inbox transaction	 // comes from client
	"atProcessInbox",	// process inbox reply			 // comes from server
	// --------------------------------------------------------------------------------------
	"transfer",			// or "spend". This transaction is a transfer from one account to another
	"atTransfer",		// reply from the server regarding a transfer request
	// --------------------------------------------------------------------------------------
	"deposit",			// this transaction is a deposit of bearer tokens (from client)
	"atDeposit",		// reply from the server regarding a deposit request
	// --------------------------------------------------------------------------------------
	"withdrawal",		// this transaction is a withdrawal of bearer tokens
	"atWithdrawal",		// reply from the server regarding a withdrawal request
	// --------------------------------------------------------------------------------------
	"marketOffer",		// this transaction is a market offer
	"atMarketOffer",	// reply from the server regarding a market offer
	// --------------------------------------------------------------------------------------
	"paymentPlan",		// this transaction is a payment plan
	"atPaymentPlan",	// reply from the server regarding a payment plan
	// --------------------------------------------------------------------------------------
	"error_state"	
};




// This transaction actually was saved as a transaction receipt (filename nymID.success)
// and now, for whatever reason, I want to verify the receipt against the local data (the Nym).
//
// Let's say the Nym has the numbers 9 and 10. He signs a receipt to that effect. Until a new
// receipt is signed, they should STILL be 9 and 10!  Therefore I should be able to load up
// the last receipt, pass it the Nym, and verify this.
//
// But what if the last receipt is a balance receipt, instead of a transaction receipt? Let's
// say I grab the Nym and he has only a 9! And though this transaction receipt shows a 9
// and 10, there is a newer balance receipt that shows only a 9? That means even when
// verifying a transaction receipt, I need to also load the last balance receipt and (for
// transaction numbers, anyway) use whichever one is newer.
//
// From there, it's simple: Make sure they match.
// I should do this when I already have the last receipt and I just grabbed a copy of the Nym.
// 
// BUT!! I can't load the last balance receipt, since I don't have the account number.
// So let's say #10 disappears, as the last balance receipt would show (but which I can't see.)
// That means THE_NYM will show that 10 is missing, even though *this shows that #10 is still
// on the list. Is that bad?
// 
// New transaction numbers can only be issued to my signed-out list of responsibility in the
// case where I SIGNED for each number using a transaction agreement.
// Whereas transaction numbers can only be REMOVED via a balance agreement (processInbox.)
// Therefore, at most, I will see that a number has disappeared, NOT that one was added.
//
// Conclusion: as long as numbers only DISAPPEAR, and are not ADDED, then this verify is good.
// But in VerifyBalanceReceipt (next function down) I will need to load the transaction receipt
// and use it for verifying issued numbers, in cases where that receipt is newer than the balance
// receipt. (Because in that case, numbers may have been ADDED..)
//
bool OTTransaction::VerifyTransactionReceipt(OTPseudonym & SERVER_NYM, // For verifying a signature.
											 OTPseudonym & THE_NYM)
{
	// ------------------------------------
	
	// LOAD "AT TRANSACTION STATEMENT" (ITEM)
	
	OTItem * pBalanceItem = NULL;
	
	OTItem * pResponseBalanceItem = GetItem(OTItem::atTransactionStatement);
	
	if (NULL == pResponseBalanceItem)
	{
		// error, return.
		OTLog::Output(0, "No atTransactionStatement item found on receipt (strange.)\n");
		return false;
	}
	else if (OTItem::acknowledgement != pResponseBalanceItem->GetStatus())
	{
		// error, return.
		OTLog::Output(0, "Error: atTransactionStatement found on receipt, but not a successful one.\n");
		return false;		
	}
	else if (!pResponseBalanceItem->VerifySignature(SERVER_NYM))
	{		
		OTLog::Output(0, "Unable to verify signature on atTransactionStatement item in OTTransaction::VerifyTransactionReceipt.\n");
		return false;				
	}
	
	// ------------------------------------
	
	// LOAD "TRANSACTION STATEMENT" (ITEM)
	
	OTString strBalanceItem;
	pResponseBalanceItem->GetReferenceString(strBalanceItem);
	
	if (!strBalanceItem.Exists())
	{
		// error, return.
		OTLog::Output(0, "No transactionStatement item found as 'in ref to' string on a receipt containing atTransactionStatement item.\n");
		return false;				
	}
	
	pBalanceItem = OTItem::CreateItemFromString(strBalanceItem, GetPurportedServerID(), pResponseBalanceItem->GetReferenceToNum());
	
	if (NULL == pBalanceItem)
	{
		OTLog::Output(0, "Unable to load transactionStatement item from string (from a receipt containing an atTransactionStatement item.)\n");
		return false;				
	}
	else if (pBalanceItem->GetType() != OTItem::transactionStatement)
	{
		OTLog::Output(0, "Wrong type on pBalanceItem (expected OTItem::transactionStatement)\n");
		return false;				
	}
	else if (!pBalanceItem->VerifySignature(THE_NYM))
	{
		OTLog::Output(0, "Unable to verify signature on transactionStatement item in OTTransaction::VerifyTransactionReceipt.\n");
		return false;				
	}
	
	// ---------------------------------------------------------
	
	// LOAD MESSAGE NYM (THE LIST OF ISSUED NUMBERS ACCORDING TO THE RECEIPT.)
	
	OTPseudonym theMessageNym;
	OTString	strMessageNym; // Okay now we have the transaction numbers in this MessageNym string.
	
	pBalanceItem->GetAttachment(strMessageNym);	
	
	if (!strMessageNym.Exists() || !theMessageNym.LoadFromString(strMessageNym))
	{
		OTLog::Output(0, "Unable to load message nym in OTTransaction::VerifyTransactionReceipt.\n");
		return false;				
	}
	
	// ------------------------------------
	
	// VERIFY THE LIST OF ISSUED (SIGNED FOR) TRANSACTION NUMBERS ON THE NYM AGAINST THE RECEIPT.
	
	// It's okay if some transaction #s in theMessageNym (the receipt) aren't found on THE_NYM, since the last balance agreement
	// may have cleaned them out after they were recorded in theMessageNym (from the transaction statement receipt).
	//
	// But I should never see transaction #s APPEAR in THE_NYM that aren't in theMessageNym, since a balance agreement
	// can ONLY remove numbers, not add them.
	//
	if (!THE_NYM.VerifyTransactionStatementNumbersOnNym(theMessageNym))
	{
		OTLog::Output(0, "Unable to verify issued numbers on last signed receipt with numbers on THE_NYM in OTTransaction::VerifyTransactionReceipt.\n");
		return false;				
	}
	
	// -------------------------------------------------------	
	
	return true;
}




// static
bool OTTransaction::VerifyTransactionReceipt(OTPseudonym & SERVER_NYM,
											 OTPseudonym & THE_NYM,
											 OTIdentifier & SERVER_ID)
{
	OTIdentifier USER_ID(THE_NYM), SERVER_USER_ID(SERVER_NYM);
	const OTString strServerID(SERVER_ID), strReceiptID(USER_ID);
	
	// -----------------------------------
	
	// Load the last successful TRANSACTION STATEMENT...
	
	OTTransaction tranOut(SERVER_USER_ID, USER_ID, SERVER_ID);
	
	bool bConfirmReceiptMAINFolder = OTLog::ConfirmOrCreateFolder(OTLog::ReceiptFolder());
	
	if (!bConfirmReceiptMAINFolder)
	{
		OTLog::vError("OTTransaction::VerifyTransactionReceipt: Unable to find or "
					  "create main Receipt directory: %s%s%s\n", 
					  OTLog::Path(), OTLog::PathSeparator(), OTLog::ReceiptFolder());	
		return false;
	}
	// -----------------------------------------------------------------
	else 
	{
		OTString strReceiptDirectoryPath;
		strReceiptDirectoryPath.Format("%s%s%s", 
									   OTLog::ReceiptFolder(), OTLog::PathSeparator(),
									   strServerID.Get());
		
		bool bConfirmReceiptFolder = OTLog::ConfirmOrCreateFolder(strReceiptDirectoryPath.Get());
		
		if (!bConfirmReceiptFolder)
		{
			OTLog::vError("OTTransaction::VerifyTransactionReceipt: Unable to find or create Receipt subdir "
						  "for server ID: %s\n\n", 
						  strReceiptDirectoryPath.Get());
			return false;
		}				
		// ----------------------------------------------------------------------------
		else 
		{			
			OTString strReceiptPath;
			
			strReceiptPath.Format("%s%s%s%s%s.success", OTLog::Path(), OTLog::PathSeparator(), 
								  strReceiptDirectoryPath.Get(), OTLog::PathSeparator(), strReceiptID.Get());
			
			if (!tranOut.LoadContract(strReceiptPath.Get()) || !tranOut.VerifySignature(SERVER_NYM))
			{
				OTLog::vError("OTTransaction::VerifyTransactionReceipt: Unable to load transaction statement: %s\n", 
							  strReceiptPath.Get());
				return false;
			}				
		}
	}
	
	// At this point, tranOut is successfully loaded and verified, containing the last transaction receipt.
	
	return tranOut.VerifyTransactionReceipt(SERVER_NYM, THE_NYM);
}



// static
bool OTTransaction::VerifyBalanceReceipt(OTPseudonym & SERVER_NYM,
										 OTPseudonym & THE_NYM,
										 OTIdentifier & SERVER_ID,
										 OTIdentifier & ACCT_ID)
{
	OTIdentifier USER_ID(THE_NYM), SERVER_USER_ID(SERVER_NYM);
	const OTString strServerID(SERVER_ID), strReceiptID(ACCT_ID);
	
	// -----------------------------------
	
	// Load the last successful BALANCE STATEMENT...
	
	OTTransaction tranOut(SERVER_USER_ID, ACCT_ID, SERVER_ID);
	
	bool bConfirmReceiptMAINFolder = OTLog::ConfirmOrCreateFolder(OTLog::ReceiptFolder());
	
	if (!bConfirmReceiptMAINFolder)
	{
		OTLog::vError("OTTransaction::VerifyBalanceReceipt: Unable to find or "
					  "create main Receipt directory: %s%s%s\n", 
					  OTLog::Path(), OTLog::PathSeparator(), OTLog::ReceiptFolder());	
		return false;
	}
	// -----------------------------------------------------------------
	else 
	{
		OTString strReceiptDirectoryPath;
		strReceiptDirectoryPath.Format("%s%s%s", 
									   OTLog::ReceiptFolder(), OTLog::PathSeparator(),
									   strServerID.Get());
		
		bool bConfirmReceiptFolder = OTLog::ConfirmOrCreateFolder(strReceiptDirectoryPath.Get());
		
		if (!bConfirmReceiptFolder)
		{
			OTLog::vError("OTTransaction::VerifyBalanceReceipt: Unable to find or create Receipt subdir "
						  "for server ID: %s\n\n", 
						  strReceiptDirectoryPath.Get());
			return false;
		}				
		// ----------------------------------------------------------------------------
		else 
		{			
			OTString strReceiptPath;
			
			strReceiptPath.Format("%s%s%s%s%s.success", OTLog::Path(), OTLog::PathSeparator(), 
								  strReceiptDirectoryPath.Get(), OTLog::PathSeparator(), strReceiptID.Get());
			
			if (!tranOut.LoadContract(strReceiptPath.Get()) || !tranOut.VerifySignature(SERVER_NYM))
			{
				OTLog::vError("OTTransaction::VerifyBalanceReceipt: Unable to load balance statement: %s\n", 
							  strReceiptPath.Get());
				return false;
			}				
		}
	}
	
	// At this point, tranOut is successfully loaded and verified, containing the last balance receipt.
	
	return tranOut.VerifyBalanceReceipt(SERVER_NYM, THE_NYM);
}




// This transaction actually was saved as a balance receipt (filename accountID.success)
// and now, for whatever reason, I want to verify the receipt against the local data (the Nym,
// the inbox, the outbox, and the account balance).
//
// Let's say the Nym has the numbers 9 and 10. He signs a receipt to that effect. Until a new
// receipt is signed, they should STILL be 9 and 10!  Therefore I should be able to load up
// the last receipt, pass it the Nym, and verify this.
//
// But what if the last receipt is a transaction receipt, instead of a balance receipt? Let's
// say I grab the Nym and he has 9, 10, and 15! And though this balance receipt shows 9 and 10,
// there is a newer one that shows 9, 10, and 15? That means even when verifying a balance 
// receipt, I need to also load the last transaction receipt and for transaction numbers, use
// whichever one is newer.
//
// When downloading the inbox, the outbox, the account, or the nym, if there is a receipt, I
// should compare what I've downloaded with the last receipt. Because if there's a discrepancy,
// then I don't want to USE that inbox/outbox/account/nym to sign a NEW receipt, causing me
// to sign agreement to invalid data!  Instead, I want a red flag to go up, and the receipt
// automatically saved to a disputes folder, etc.
//
bool OTTransaction::VerifyBalanceReceipt(OTPseudonym & SERVER_NYM, // For verifying a signature.
										 OTPseudonym & THE_NYM)	// transaction numbers issued according to nym must match this.
										 //OTLedger & THE_INBOX,	// All inbox items on *this must also be found in THE_INBOX. All new items (on THE_INBOX only) must be accounted for in the balance. 
										 //OTLedger & THE_OUTBOX,	// All inbox items that changed balance (cheque, market, payment) must be found on the list of issued numbers.
										 //const OTAccount & THE_ACCOUNT) // All outbox items must match, and the account balance must be accounted for as described.
{										// These are now loaded within this function, so no need to pass them in.
	// Load the other receipt (see above) if necessary.
	
	// Compare the inbox I just downloaded with what my last signed receipt SAYS it should say.
	// Let's say the inbox has transaction 9 in it -- well, my last signed receipt better show
	// that 9 was in my inbox then, too. But what if 9 was on a cheque, and it only recently hit?
	// Well it won't be in my old inbox, but it WILL still be signed for as an open transaction.
	
	// Since this involves verifying the outbox, inbox, AND account, this function should only
	// be called after all three have been downloaded, not after each one.
	// Basically the outbox should NEVER change, the inbox is EXPECTED to change, and the account
	// is EXPECTED to change, BUT ONLY in cases where the inbox justifies it!
	//
	// -- Verify the transaction numbers on the nym match those exactly on the newest transaction or balance receipt. (this)
	// -- Make sure outbox is the same.
	// -- Loop through all items in the inbox, AND in the inbox according to the receipt, and total the
	//    values of both. I might have 9 and 10 issued in the last receipt, with #9 in the inbox,
	//    showing 50 clams and a balance of 93. But now I downloaded an inbox showing #9 AND #10,
	//    with values of 50 and 4, and a balance of 89.
	//    The new inbox is still valid, and the new account balance is still valid, because the
	//    new number that appeared was issued to me and signed out, and because the last receipt's
	//    balance of 93 with 50 clams worth of receipts, matches up to the new account/inbox
	//    balance of 89 with 54 clams worth of receipts.
	//    The two totals still match!  That's what we're checking for.
	//
	// Not JUST that actually, but that, if #10 is NOT found in the old one, THEN the amount (4)
	// must be the DIFFERENCE between the balances (counting all new transactions like #10.)
	// Meaning, the difference between the two balances MUST be made up EXACTLY by the transactions
	// that are found now, that were not previously found, minus the total of the transactions
	// from before that are no longer there, but are also no longer on my issued list and thus don't matter.
	// 
	// Wow ! OTItem::VerifyBalanceStatement will have useful code but it doesn't encapsulate all this
	// new functionality, since this version must assume differences are there, and STILL verify things
	// by comparing details about those differences, whereas that version only serves to make sure
	// everything still matches.
	// ---------------------------------------------------
	
	// -- Verify nym transactions match. (issued.)
	// -- Verify outbox matches.
	// -- Loop through all items on receipt. If outbox item, should match exactly.
	// -- But for inbox items, total up: the amount of the total of the items from the receipt,
	//    for all those that would actually change the balance (chequeReceipt, marketReceipt, paymentReceipt.)
	//    These should ALL be found in the current version of the inbox. (They can only be removed by balance agreement which would update THIS RECEIPT to remove them...)
	// -- That was the receipt. Now loop through the above inbox items and do the reverse: for each item in the NEW inbox, 
	//    add up the total of those that would change the balance, for receipts found on the new but not the old, and account for that exactly as a difference in balance.
	/*
	 
	 Example.
	 
	 -- Oldest signed receipt shows a balance of 115 clams.
	    But then, cheque #78 hits my inbox and though I haven't yet accepted the receipt, I still need to do a transaction, like a 5 clam withdrawal, or whatever,
	    and somehow I end up doing a balance agreement.  That results in the below signed receipt:
	 
	 --- Old receipt shows inbox/account/nym as:
	 Currently signed out: 8, 9, 10, and 15
	 Balance of 100 clams (Last signed balance before this was for 115 clams above)
	 Inbox items:
	 #78 cheque receipt (#8) for 15 clams. (The missing money is already reflected in the above balance. BUT!! #8 must still be signed out for this to verify. Here I must sign to acknowledge the receipt is in my inbox, but I still have option to accept or dispute the receipt. Until then, server keeps it around since it has my signature on it and proves the current balance.)
	 #82 incoming transfer for 50 clams (A new balance agreement occurs during acceptance of this. And the number doesn't belong to me. So, irrelevant here.) 
	 #10 transfer receipt for some old transfer (does NOT change balance, which already happened in the past, BUT!! #10 must still be signed out for this to verify.)
	 
	 My nym ISSUED list should not change unless I have a new transaction agreement, therefore I expect the list to match every time.
	 My outbox should also match. Thus, only my account balance and inbox might change. (On the server side, which I'll see when I dl new versions of them and compare against my last receipt i.e. this function.)
	 How?  NOT via transfer receipt, since I would sign a new balance agreement whenever that would actually impact my balance.
	 But it could happen with a *** chequeReceipt, a paymentReceipt, or marketReceipt. *** Those mean, my balance has changed.
	 In those cases, my account balance WOULD be different, but there had better be matching receipts in the inbox!
	 
	 --- New inbox/account/nym shows:
	 Currently signed out: 8, 9, 10, and 15
	 Balance of 89 clams
	 Inbox items:
	 #78 cheque receipt (#8) for 15 clams. 
	 #82 incoming transfer for 50 clams (A new balance agreement occurs during acceptance. So this type has no affect on balance here.) 
	 #10 transfer receipt for some old transfer (does NOT change balance, which already happened in the past)
	 #96 cheque receipt for 7 clams (cheque #9)
     #97 marketReceipt for 4 clams (marketOffer #15)
	 #99 incoming transfer for 2000 clams (Accepting it will require a new balance agreement.)
	 
	 How do I interpret all this data?
	 -- Transaction numbers signed out had better match. (If #s issued had changed, I would have signed for it already.)
	 
	 Next loop through the inbox from the old receipt:
	 -- #78, cheque receipt, had better be there in the new inbox, since removing it requires a balance agreement, meaning it would already be off the receipt that I'm verifying... Since it's here in inbox, should therefore also be in the last receipt.
	 -- #82, incoming transfer from old receipt, had better be also on the new inbox, since I could only accept or reject it with a balance agreement, which I'm comparing the inbox to now.
	 -- #10 had also better be there in the new inbox for the same reason: if I had accepted this transfer receipt, then my last balance receipt would reflect that.
	 -- THEREFORE: ALL items from old receipt must be found inside new inbox!
	 
	 Next, loop through the new version of the inbox:
	 -- #78, though found in the new inbox, wouldn't necessarily be expected to be found in the last receipt, since someone may have cashed my cheque since the receipt was made.
	 -- #82, though found in the new inbox, wouldn't necessarily be expected to be found in the last receipt, since someone may have sent me the transfer since receipt was made.
	 -- #10 in new inbox, same thing: Someone may have recently accepted my transfer, and thus #10 only would have popped in since the last agreement. (It was there before, but I couldn't EXPECT that in every case.)
	 -- #96 and #97 represent balance CHANGES totalling -11 clams. They must correspond to a change in balance.
	 -- #96 is a cheque receipt.. it has changed the balance and I must account for that. But #78 is ALSO a cheque receipt, so why am I not accounting for ITs total (instead just assuming it's accounted for already in the prior balance, like 78?) Because it's NEW and wasn't on the old receipt like 78 is!
	 -- Due to the reasoning explained on the above line, ANY chequeReceipt, paymentReceipt, or marketReceipt found on the new version of the inbox but NOT on the old one, must be accounted for against the balance.
	 -- #99 is an incoming transfer, but it will not change the balance until that transfer is accepted with a new balance agreement sometime in the future.
	 */

	
	OTIdentifier USER_ID(THE_NYM), SERVER_USER_ID(SERVER_NYM);

	const OTString strServerID(GetRealServerID()), strReceiptID(USER_ID);

//	if (USER_ID != GetUserID())
//	{
//		OTLog::Error("*** OTIdentifier USER_ID(OTPseudonym THE_NYM) doesn't match OTTransactionType::GetUserID() in OTTransaction::VerifyBalanceReceipt\n");
//		return false;
//	}
	
	// -----------------------------------
	
	// Load the last TRANSACTION STATEMENT as well...
	
	OTTransaction tranOut(SERVER_USER_ID, USER_ID, GetRealServerID());

	bool bConfirmReceiptMAINFolder = OTLog::ConfirmOrCreateFolder(OTLog::ReceiptFolder());
	
	if (!bConfirmReceiptMAINFolder)
	{
		OTLog::vError("OTTransaction::VerifyBalanceReceipt: Unable to find or "
					  "create main Receipt directory: %s%s%s\n", 
					  OTLog::Path(), OTLog::PathSeparator(), OTLog::ReceiptFolder());	
		return false;
	}
	// -----------------------------------------------------------------
	else 
	{
		OTString strReceiptDirectoryPath;
		strReceiptDirectoryPath.Format("%s%s%s", 
									   OTLog::ReceiptFolder(), OTLog::PathSeparator(),
									   strServerID.Get());
		
		bool bConfirmReceiptFolder = OTLog::ConfirmOrCreateFolder(strReceiptDirectoryPath.Get());
		
		if (!bConfirmReceiptFolder)
		{
			OTLog::vError("OTTransaction::VerifyBalanceReceipt: Unable to find or create Receipt subdir "
						  "for server ID: %s\n\n", 
						  strReceiptDirectoryPath.Get());
			return false;
		}				
		// ----------------------------------------------------------------------------
		else 
		{			
			OTString strReceiptPath;
			
			strReceiptPath.Format("%s%s%s%s%s.success", OTLog::Path(), OTLog::PathSeparator(), 
									  strReceiptDirectoryPath.Get(), OTLog::PathSeparator(), strReceiptID.Get());
			
			if (!tranOut.LoadContract(strReceiptPath.Get()) || !tranOut.VerifySignature(SERVER_NYM))
			{
				OTLog::vError("OTTransaction::VerifyBalanceReceipt: Unable to load transaction statement: %s\n", 
							  strReceiptPath.Get());
				return false;
			}				
		}
	}

	// I ONLY need this transaction statement if it's newer than the balance statement.
	// Otherwise, I don't use it at all.  But if it's newer, then I use it instead of the current 
	// balance statement (only for verifying the list of issued numbers, not for anything else.)
	
	// And in the case where that happens, I ONLY expect to see new numbers added, NOT removed.
	// But again, ONLY if the transaction statement is MORE RECENT. Otherwise it may have extra
	// numbers alright: ones that were already removed and I don't want to re-sign responsibility for!
	
	
	// CHECK IF IT'S NEWER AND SET A POINTER BASED ON THIS.
	
	OTTransaction	* pTranWithIssuedList = this; // the transaction that actually has the issued list we'll be using. (Might be balance receipt or transaction receipt, whichever is newer)
	OTItem			* pItemWithIssuedList = NULL; // the item from that transaction that actually has the issued list we'll be using.
	
	OTItem * pResponseTransactionItem	= NULL; // only if it's new than balance receipt does this get set, to: tranOut.GetItem(OTItem::atTransactionStatement);
	OTItem * pTransactionItem			= NULL;

	
	if (tranOut.GetDateSigned() > this->GetDateSigned()) // it's newer.
	{
		pTranWithIssuedList = &tranOut;
		
		// GET THE "AT TRANSACTION STATEMENT" ITEM
		pResponseTransactionItem = tranOut.GetItem(OTItem::atTransactionStatement);
		
		if (NULL == pResponseTransactionItem)
		{
			// error, return.
			OTLog::Output(0, "No atTransactionStatement item found on receipt (strange.)\n");
			return false;
		}
		else if (OTItem::acknowledgement != pResponseTransactionItem->GetStatus())
		{
			// error, return.
			OTLog::Output(0, "Error: atTransactionStatement found on receipt, but not a successful one.\n");
			return false;		
		}
		else if (!pResponseTransactionItem->VerifySignature(SERVER_NYM))
		{		
			OTLog::Output(0, "Unable to verify signature on atTransactionStatement item in OTTransaction::VerifyBalanceReceipt.\n");
			return false;				
		}
		
		// ------------------------------------
		
		// LOAD "TRANSACTION STATEMENT" (ITEM) from within the above item we got.
		
		OTString strBalanceItem;
		pResponseTransactionItem->GetReferenceString(strBalanceItem);
		
		if (!strBalanceItem.Exists())
		{
			// error, return.
			OTLog::Output(0, "No transactionStatement item found as 'in ref to' string on a receipt containing atTransactionStatement item.\n");
			return false;				
		}
		
		pTransactionItem = OTItem::CreateItemFromString(strBalanceItem, GetRealServerID(), pResponseTransactionItem->GetReferenceToNum());
		
		if (NULL == pTransactionItem)
		{
			OTLog::Output(0, "Unable to load transactionStatement item from string (from a receipt containing an atTransactionStatement item.)\n");
			return false;				
		}
		else if (pTransactionItem->GetType() != OTItem::transactionStatement)
		{
			OTLog::Output(0, "Wrong type on pTransactionItem (expected OTItem::transactionStatement)\n");
			return false;				
		}
		else if (!pTransactionItem->VerifySignature(THE_NYM))
		{
			OTLog::Output(0, "Unable to verify signature on transactionStatement item in OTTransaction::VerifyBalanceReceipt.\n");
			return false;				
		}
		
		pItemWithIssuedList = pTransactionItem;
	}
	
	// Now use pTranWithIssuedList and pItemWithIssuedList for checking issued numbers.
	// (Even though I'll continue to use *this for all other data being verified.)
		
	// -------------------------------------------------------
	
	// LOAD THE ACCOUNT 
	
	
	OTAccount THE_ACCOUNT(USER_ID, GetRealAccountID(), GetRealServerID());

	if (!THE_ACCOUNT.LoadContract() || !THE_ACCOUNT.VerifyAccount(THE_NYM))
	{
		// error, return.
		OTLog::Output(0, "Failed loading or verifying account in OTTransaction::VerifyBalanceReceipt.\n");
		return false;		
	}
	else if (THE_ACCOUNT.GetPurportedServerID() != GetPurportedServerID()) // the account, inbox, and outbox all have the same Server ID. But does it match *this receipt?
	{
		// error, return.
		OTLog::Output(0, "Account, inbox or outbox server ID fails to match receipt server ID.\n");
		return false;
	}
	else if (THE_ACCOUNT.GetPurportedAccountID() != GetPurportedAccountID()) // Same as above except for account ID instead of server ID.
	{
		// error, return.
		OTLog::Output(0, "Account ID fails to match receipt account ID.\n");
		return false;
	}

	// -----------------------------------------------------
	
	// LOAD INBOX AND OUTBOX
	
	OTLedger * pInbox	= THE_ACCOUNT.LoadInbox(THE_NYM);
	OTLedger * pOutbox	= THE_ACCOUNT.LoadOutbox(THE_NYM); 
	OTCleanup<OTLedger> theInboxAngel(pInbox);
	OTCleanup<OTLedger> theOutboxAngel(pOutbox);
	
	if ((NULL == pInbox) || (NULL == pOutbox))
	{
		// error, return.
		OTLog::Output(0, "Inbox or outbox was NULL after THE_ACCOUNT.Load in OTTransaction::VerifyBalanceReceipt.\n");
		return false;
	}
	
	// ------------------------------------
	
	// LOAD "AT BALANCE STATEMENT" (ITEM)
	
	OTItem * pResponseBalanceItem = this->GetItem(OTItem::atBalanceStatement);
	
	if (NULL == pResponseBalanceItem)
	{
		// error, return.
		OTLog::Output(0, "No atBalanceStatement item found on receipt (strange.)\n");
		return false;
	}
	else if (OTItem::acknowledgement != pResponseBalanceItem->GetStatus())
	{
		// error, return.
		OTLog::Output(0, "Error: atBalanceStatement found on receipt, but not a successful one.\n");
		return false;		
	}
	else if (!pResponseBalanceItem->VerifySignature(SERVER_NYM))
	{		
		OTLog::Output(0, "Unable to verify signature on atBalanceStatement item in OTTransaction::VerifyBalanceReceipt.\n");
		return false;				
	}
	
	// ------------------------------------

	// LOAD "BALANCE STATEMENT" (ITEM)

	OTItem * pBalanceItem = NULL;
	
	OTString strBalanceItem;
	pResponseBalanceItem->GetReferenceString(strBalanceItem);
		
	if (!strBalanceItem.Exists())
	{
		// error, return.
		OTLog::Output(0, "No balanceStatement item found as 'in ref to' string on a receipt containing atBalanceStatement item.\n");
		return false;				
	}

	pBalanceItem = OTItem::CreateItemFromString(strBalanceItem, GetRealServerID(), pResponseBalanceItem->GetReferenceToNum());
			
	if (NULL == pBalanceItem)
	{
		OTLog::Output(0, "Unable to load balanceStatement item from string (from a receipt containing an atBalanceStatement item.)\n");
		return false;				
	}
	else if (pBalanceItem->GetType() != OTItem::balanceStatement)
	{
		OTLog::Output(0, "Wrong type on pBalanceItem (expected OTItem::balanceStatement)\n");
		return false;				
	}
	else if (!pBalanceItem->VerifySignature(THE_NYM))
	{
		OTLog::Output(0, "Unable to verify signature on balanceStatement item in OTTransaction::VerifyBalanceReceipt.\n");
		return false;				
	}
	

	// ---------------------------------------------------------

	// LOAD MESSAGE NYM (THE LIST OF ISSUED NUMBERS ACCORDING TO THE RECEIPT.)
	
	OTPseudonym theMessageNym;
	OTString	strMessageNym; // Okay now we have the transaction numbers in this MessageNym string.
	
	//
	if ((NULL != pTransactionItem) && (tranOut.GetDateSigned() > this->GetDateSigned())) // transaction statement is newer than (this) balance statement.
		pItemWithIssuedList = pTransactionItem; // already set above, but I'm re-stating here for clarity, since the else is now possible...
	else 
		pItemWithIssuedList = pBalanceItem; // Hereafter we can use pItemWithIssuedList to verify issued transaction numbers (and NOTHING ELSE.)

	// ------------
	
	pItemWithIssuedList->GetAttachment(strMessageNym);	// Like right here, for example.

	if (!strMessageNym.Exists() || !theMessageNym.LoadFromString(strMessageNym))
	{
		OTLog::Output(0, "Unable to load message nym in OTTransaction::VerifyBalanceReceipt.\n");
		return false;				
	}
			
	// ------------------------------------

	// Finally everything is loaded and verified!
	// I have the Nym and Server Nym
	// I have the account, inbox, and outbox
	// I have the original balance statement, AND the server's reply to it (a successful one)
	// 
	// Repeating a note from above:
	// -- Verify nym transactions match. (The issued / signed-for ones.)
	// -- Verify outbox matches.
	// -- Loop through all items on receipt. If outbox item, should match exactly.
	// -- But for inbox items, total up: the amount of the total of the items from the receipt,
	//    for all those that would actually change the balance (chequeReceipt, marketReceipt, paymentReceipt.)
	//    These should ALL be found in the current version of the inbox. (They can only be removed by balance agreement which would update THIS RECEIPT to remove them...)
	// -- That was the receipt. Now loop through the latest inbox items and do the reverse: for each item in the NEW inbox, 
	//    add up the total of those that would change the balance, for receipts found on the new but not the old, and account for that exactly as a difference in balance.
	//    Also make sure each receipt in the inbox (new or old) is an issued transaction number, signed out to THE_NYM.
	
		
	// VERIFY THE LIST OF ISSUED (SIGNED FOR) TRANSACTION NUMBERS ON THE NYM AGAINST THE RECEIPT.
	// The Nym should match whatever is on the newest receipt (determined just above.)
	//
	// NOTE: I used to VerifyIssuedNumbersOnNym -- but that won't work. Why? Because let's say I signed a balance agreement with #s 9, 10, and 11.
	// That's my last receipt. Now let's say, using a DIFFERENT ASSET ACCOUNT, I do a withdrawal, burning #9. Now my balance agreement says 10, 11 for
	// that other account, which correctly matches the server.  Now when the FIRST ACCOUNT verifies his (formerly valid) receipt, 9 is missing from his nym,
	// which doesn't match the receipt!  Of course that's because there's a newer balance receipt -- BUT ON A DIFFERENT ASSET ACCOUNT.
	//
	// VerifyTransactionStatement (vs VerifyBalanceStatement, where we are now) gets around this whole problem with VerifyTransactionStatementNumbersOnNym,
	// which only verifies that every issued number found on THE_NYM (below) is definitely also found in the receipt (theMessageNym). It does NOT do the reverse.
	// In other words, it does NOT make sure that every Trans# on theMessageNym is also found on THE_NYM.  Numbers may have been cleared since that receipt was signed,
	// due to a balance agreement FROM A DIFFERENT ASSET ACCOUNT. This is okay since numbers have not been ADDED to your list of responsibility (which is the danger.)
	// In order to ADD a number to your list, a transaction statement would have to be signed, since new transaction numbers can only be received through the Nymbox.
	// Since this function (VerifyBalanceStatement) uses the transactionStatement for verifying issued numbers in cases where it is newer than the balanceStatement,
	// then if a new number was added, it will be on the receipt already.
	//
//	if (!THE_NYM.VerifyIssuedNumbersOnNym(theMessageNym)) // Explained above. Balance Statements from other accts might be newer, and have burned #s already. Thus I
	if (!THE_NYM.VerifyTransactionStatementNumbersOnNym(theMessageNym))	// Can't expect a # on the receipt to still be available, though I MUST verify that every number on current Nym IS on the receipt (just not the other way around.)
	{
		OTLog::Output(0, "Unable to verify issued numbers on last signed receipt with numbers on THE_NYM in OTTransaction::VerifyBalanceReceipt.\n");
		return false;				
	}
	
	// -------------------------------------------------------
	
	// LOOP THROUGH THE BALANCE STATEMENT ITEMS (INBOX AND OUTBOX) TO GATHER SOME DATA...
	
	int nInboxItemCount = 0, nOutboxItemCount = 0;
	
	const char * szInbox = "Inbox";
	const char * szOutbox = "Outbox";
	
	const char * pszLedgerType = NULL;
	
	long lReceiptBalanceChange = 0; // For measuring the amount of the total of items in the inbox that have changed the balance (like cheque receipts)
	
	// Notice here, I'm back to using pBalanceItem instead of pItemWithIssuedList, since this is the inbox/outbox section...
	OTLog::vOutput(1, "Number of inbox/outbox items on the balance statement: %d\n", pBalanceItem->GetItemCount());
	
	for (int i=0; i < pBalanceItem->GetItemCount(); i++)
	{
		long lReceiptAmountMultiplier = 1; // for outbox calculations. (It's the only case where GetReceiptAmount() is wrong and needs -1 multiplication.)

		OTItem * pSubItem = pBalanceItem->GetItem(i);
		
		OT_ASSERT(NULL != pSubItem);
		
		OTLedger * pLedger	= NULL;
		
		switch (pSubItem->GetType()) 
		{
			case OTItem::chequeReceipt: 
			case OTItem::marketReceipt: 
			case OTItem::paymentReceipt:
				lReceiptBalanceChange += pSubItem->GetAmount();
			case OTItem::transferReceipt: 
				nInboxItemCount++;
				pLedger = pInbox;
				pszLedgerType = szInbox;
			case OTItem::transfer:
				break;
			default:
			{
				OTString strItemType;
				pSubItem->GetTypeString(strItemType);
				OTLog::vOutput(1, "OTTransaction::VerifyBalanceReceipt: Ignoring %s item "
							   "in balance statement while verifying it against inbox.\n", strItemType.Get());
			}				
				continue;
		}
		
		switch (pSubItem->GetType()) 
		{
			case OTItem::transfer:
				if (pSubItem->GetAmount() < 0) // it's an outbox item
				{
					lReceiptAmountMultiplier = -1; // transfers out always reduce your balance.
					nOutboxItemCount++;
					pLedger = pOutbox;
					pszLedgerType = szOutbox;
				}
				else
				{
					lReceiptAmountMultiplier = 1; // transfers in always increase your balance.
					nInboxItemCount++;
					pLedger = pInbox;
					pszLedgerType = szInbox;
				}
				break;
			case OTItem::transferReceipt: 
			case OTItem::chequeReceipt: 
			case OTItem::marketReceipt: 
			case OTItem::paymentReceipt:
				lReceiptAmountMultiplier = 1;
				break;
			default:
				continue; // This will never happen, due to the first continue above in the first switch.
		}
		
		OTTransaction * pTransaction = NULL;
		
		long lTempTransactionNum = 0; // Used for the below block.
		
		// What's going on here? In the original balance statement, ONLY IN CASES OF OUTOING TRANSFER, the user has put transaction # "1" in his outbox, in anticipation that
		// the server, upon success, will actually put a real pending transfer into his outbox, and issue a number for it (like "34").
		if ((pOutbox == pLedger) &&		// Thus it's understood that whenever the balanceStatement has a "1" in the outbox, I should find a corresponding "34" (or whatever # the
			(pSubItem->GetTransactionNum() == 1) &&	// server chose) as the GetNewOutboxTransNum member on the atBalanceStatement. Now here, when verifying the receipt,
			(pResponseBalanceItem->GetNewOutboxTransNum() > 0)) // this allows me to verify the outbox request '1' against the actual '34' that resulted.
		{
			pTransaction = pLedger->GetTransaction(pResponseBalanceItem->GetNewOutboxTransNum());
			lTempTransactionNum = pResponseBalanceItem->GetNewOutboxTransNum();

			OTLog::Output(1, "OTTransaction::VerifyBalanceReceipt: (This iteration, I'm handling an item listed as '1' in the outbox.)\n");
		}
		else
		{
			pTransaction = pLedger->GetTransaction(pSubItem->GetTransactionNum());
			lTempTransactionNum = pSubItem->GetTransactionNum();
		}

		// Make sure that the transaction number of each sub-item is found
		// on the appropriate ledger (inbox or outbox).
		if (NULL == pTransaction)
		{
			OTLog::vOutput(0, "OTTransaction::VerifyBalanceReceipt: Expected %s transaction (%ld) "
						   "not found. (Amount %ld.)\n",
						   pszLedgerType, lTempTransactionNum, pSubItem->GetAmount());
			return false;
		}
		
		// subItem is from the balance statement, and pTransaction is from the inbox/outbox
		if (pSubItem->GetReferenceToNum()	!= pTransaction->GetReferenceToNum())
		{
			OTLog::vOutput(0, "OTTransaction::VerifyBalanceReceipt: %s transaction (%ld) mismatch Reference Num: %ld, expected %ld\n",
						   pszLedgerType, lTempTransactionNum, pSubItem->GetReferenceToNum(),
						   pTransaction->GetReferenceToNum());
			return false;
		}
		
		long lTransactionAmount	=	pTransaction->GetReceiptAmount();
		lTransactionAmount		*=	lReceiptAmountMultiplier;
		
		if (pSubItem->GetAmount()	!= lTransactionAmount)
		{
			OTLog::vOutput(0, "OTTransaction::VerifyBalanceReceipt: %s transaction (%ld) "
						   "amounts don't match: Report says %ld, but expected %ld. Trans recpt amt: %ld, (pBalanceItem->GetAmount() == %ld.)\n",
						   pszLedgerType, lTempTransactionNum,
						   pSubItem->GetAmount(), lTransactionAmount, pTransaction->GetReceiptAmount(),
						   pBalanceItem->GetAmount());
			return false;
		}
		
		if ((pSubItem->GetType()		== OTItem::transfer) && 
			(pTransaction->GetType()	!= OTTransaction::pending))
		{
			OTLog::vOutput(0, "OTTransaction::VerifyBalanceReceipt: %s transaction (%ld) wrong type.\n",
						   pszLedgerType, lTempTransactionNum);
			return false;
		}
		
		if ((pSubItem->GetType()		== OTItem::chequeReceipt) && 
			(pTransaction->GetType()	!= OTTransaction::chequeReceipt))
		{
			OTLog::vOutput(0, "OTTransaction::VerifyBalanceReceipt: %s transaction (%ld) wrong type.\n",
						   pszLedgerType, lTempTransactionNum);
			return false;
		}
		
		if ((pSubItem->GetType()		== OTItem::marketReceipt) && 
			(pTransaction->GetType()	!= OTTransaction::marketReceipt))
		{
			OTLog::vOutput(0, "OTTransaction::VerifyBalanceReceipt: %s transaction (%ld) wrong type.\n",
						   pszLedgerType, lTempTransactionNum);
			return false;
		}
		
		if ((pSubItem->GetType()		== OTItem::paymentReceipt) && 
			(pTransaction->GetType()	!= OTTransaction::paymentReceipt))
		{
			OTLog::vOutput(0, "OTTransaction::VerifyBalanceReceipt: %s transaction (%ld) wrong type.\n",
						   pszLedgerType, lTempTransactionNum);
			return false;
		}
		
		if ((pSubItem->GetType()		== OTItem::transferReceipt) && 
			(pTransaction->GetType()	!= OTTransaction::transferReceipt))
		{
			OTLog::vOutput(0, "OTTransaction::VerifyBalanceReceipt: %s transaction (%ld) wrong type.\n",
						   pszLedgerType, lTempTransactionNum);
			return false;
		}
	}
	
	// By this point, I have an accurate count of the inbox items, and outbox items, represented
	// by *this receipt.
	// I also know that I found each item from the receipt on the new inbox or outbox (as I should have)
	// But do I have to verify that the items are all signed for. I'll do that below since this list
	// is a subset of that one (supposedly.)
	
	//-----------------------------------------------------------------
	
	
	if (nOutboxItemCount	!= pOutbox->GetTransactionCount())
	{
		OTLog::vOutput(0, "OTTransaction::VerifyBalanceReceipt: Outbox mismatch in expected transaction count.\n"
					   " --- THE_INBOX count: %d --- THE_OUTBOX count: %d\n"
					   "--- nInboxItemCount count: %d --- nOutboxItemCount count: %d\n\n", 
					   pInbox->GetTransactionCount(), pOutbox->GetTransactionCount(), 
					   nInboxItemCount, nOutboxItemCount);
		
		return false;
	}
	
	// Notice I don't check inbox item count here, since that actually CAN change.
	
	//-----------------------------------------------------------------

	// LOOP THROUGH LATEST INBOX AND GATHER DATA / VALIDATE.
	
	long lInboxBalanceChange = 0; // Change in the account balance we'd expect, based on TOTAL receipts in the inbox.
	long lInboxSupposedDifference = 0; // Change in the account balance we'd expect, based on the NEW receipts in the inbox.

	for (int i=0; i < pInbox->GetTransactionCount(); i++)
	{
		OTTransaction * pTransaction = pInbox->GetTransactionByIndex(i);
		
		OT_ASSERT(NULL != pTransaction);

		switch (pTransaction->GetType()) 
		{
			case OTTransaction::chequeReceipt: 
			case OTTransaction::marketReceipt: 
			case OTTransaction::paymentReceipt:
				lInboxBalanceChange += pTransaction->GetReceiptAmount(); // Here I total ALL relevant receipts.
			case OTTransaction::pending:
			case OTTransaction::transferReceipt: // transferReceipt has an amount, but it already came out of the account and thus isn't figured in here.
				break;
			default:
			{
				OTLog::vOutput(1, "OTTransaction::VerifyBalanceReceipt: Ignoring %s item "
							   "in inbox while verifying it against balance receipt.\n", pTransaction->GetTypeString());
			}				
				continue;
		}
		
		// May or may not be found..
		OTItem * pSubItem = pBalanceItem->GetItemByTransactionNum(pTransaction->GetTransactionNum());
		
		// Above loop already verified that all items in the receipt's inbox were found in the new inbox.
		// But THIS item was found in the new inbox, but not the OLD inbox (from the receipt.)
		// That means it needs to be accounted for against the account balance!
		//
		if (NULL == pSubItem)
		{
			switch (pTransaction->GetType()) 
			{
				case OTTransaction::chequeReceipt:  // Every one of these, we have to add up the total and reconcile against the latest balance.
				case OTTransaction::marketReceipt: 
				case OTTransaction::paymentReceipt:
					lInboxSupposedDifference += pTransaction->GetReceiptAmount(); // Here I only total the NEW receipts (not found in old receipt inbox but found in current inbox.)
				case OTTransaction::pending: // pending has value, why aren't we adding it? Because it hasn't changed the balance yet.
				case OTTransaction::transferReceipt:  // transferReceipt has an amount, but it already came out of the account and thus isn't figured in here.
					break;
				default:
					break; // this should never happen due to above switch.
			}
		}
		else // If the transaction from the inbox WAS found as an item on the old receipt, let's verify the two against each other...
		{
			// subItem is from the balance statement, and pTransaction is from the inbox
			if (pSubItem->GetReferenceToNum()	!= pTransaction->GetReferenceToNum())
			{
				OTLog::vOutput(0, "OTTransaction::VerifyBalanceReceipt: Inbox transaction (%ld) mismatch Reference Num: %ld, expected %ld\n",
							   pSubItem->GetTransactionNum(), pSubItem->GetReferenceToNum(),
							   pTransaction->GetReferenceToNum());
				return false;
			}
			
			// We're looping through the inbox here, so no multiplier is needed for the amount 
			// (that was only for outbox items.)
			if (pSubItem->GetAmount()	!= (pTransaction->GetReceiptAmount() ))
			{
				OTLog::vOutput(0, "OTTransaction::VerifyBalanceReceipt: Inbox transaction (%ld) "
							   "amounts don't match: %ld, expected %ld. (pBalanceItem->GetAmount() == %ld.)\n",
							   pSubItem->GetTransactionNum(),
							   pSubItem->GetAmount(), pTransaction->GetReceiptAmount(),
							   pBalanceItem->GetAmount());
				return false;
			}
			
			if ((pSubItem->GetType()		== OTItem::transfer) && 
				(pTransaction->GetType()	!= OTTransaction::pending))
			{
				OTLog::vOutput(0, "OTTransaction::VerifyBalanceReceipt: Inbox transaction (%ld) wrong type.\n",
							   pSubItem->GetTransactionNum());
				return false;
			}
			
			if ((pSubItem->GetType()		== OTItem::chequeReceipt) && 
				(pTransaction->GetType()	!= OTTransaction::chequeReceipt))
			{
				OTLog::vOutput(0, "OTTransaction::VerifyBalanceReceipt: Inbox transaction (%ld) wrong type.\n",
							   pSubItem->GetTransactionNum());
				return false;
			}
			
			if ((pSubItem->GetType()		== OTItem::marketReceipt) && 
				(pTransaction->GetType()	!= OTTransaction::marketReceipt))
			{
				OTLog::vOutput(0, "OTTransaction::VerifyBalanceReceipt: Inbox transaction (%ld) wrong type.\n",
							   pSubItem->GetTransactionNum());
				return false;
			}
			
			if ((pSubItem->GetType()		== OTItem::paymentReceipt) && 
				(pTransaction->GetType()	!= OTTransaction::paymentReceipt))
			{
				OTLog::vOutput(0, "OTTransaction::VerifyBalanceReceipt: Inbox transaction (%ld) wrong type.\n",
							   pSubItem->GetTransactionNum());
				return false;
			}

			if ((pSubItem->GetType()		== OTItem::transferReceipt) && 
				(pTransaction->GetType()	!= OTTransaction::transferReceipt))
			{
				OTLog::vOutput(0, "OTTransaction::VerifyBalanceReceipt: Inbox transaction (%ld) wrong type.\n",
							   pSubItem->GetTransactionNum());
				return false;
			}
		} // else pSubItem WAS found on the old receipt		
		
		// ---------------
		// Next I need to find out the transaction number that I ORIGINALLY used, that's somehow associated with the receipt
		// I found in my inbox, by looking up the number from within the receipt...
		//
		OTString strRespTo;
		long lIssuedNum = 0;
	
		switch (pTransaction->GetType()) 
		{
			case OTTransaction::transferReceipt: // a transfer receipt is in reference to some guy's acceptPending
				
				pTransaction->GetReferenceString(strRespTo);
				
				if (!strRespTo.Exists())
				{					
					OTLog::vOutput(0, "OTTransaction::VerifyBalanceReceipt: Inbox transaction (%ld) refers to another (%ld) but the ref string is missing.\n",
								   pTransaction->GetTransactionNum(), pTransaction->GetReferenceToNum());
					return false;
				}
				else
				{				
					OTItem * pOriginalItem = OTItem::CreateItemFromString(strRespTo, GetRealServerID(), pTransaction->GetReferenceToNum());
					OTCleanup<OTItem> theAngel(pOriginalItem);
					
					// This item was attached as the "in reference to" item. Perhaps Bob sent it to me.
					// Since that item was initiated by him, HIS would be the account ID on it, not mine.
					// So I DON'T want to create it with my account ID on it. I use above special function to instantiate it.
					//
					if (NULL == pOriginalItem)
					{
						OTLog::vError("Error loading original transaction item from string in OTTransaction::VerifyBalanceReceipt.\n");
						return false;
					}				
					else 
					{
						if ((OTItem::request == pOriginalItem->GetStatus())
							&&
							(OTItem::acceptPending	== pOriginalItem->GetType()))
						{
							lIssuedNum = pOriginalItem->GetReferenceToNum();	// <========= The whole reason we did all this crap.
						}
						else 
						{
							const int nOriginalType = pOriginalItem->GetType();
							OTLog::vError( "Unrecognized item type (%d) OTTransaction::VerifyBalanceReceipt (expected acceptPending request).\n", 
										  nOriginalType);
							return false;
						}
					}
				} // if strRespTo.Exists()
				break;
				
			case OTTransaction::marketReceipt: 
			case OTTransaction::paymentReceipt:		// a payment receipt #92 is IN REFERENCE TO my payment plan #13, which I am still signed out for until the plan closes for good.
				lIssuedNum = pTransaction->GetReferenceToNum();	// Same concept is true for market receipts.
				break;
				
			case OTTransaction::chequeReceipt:		// But a cheque receipt is in reference to some asshole's cheque deposit, which only then CONTAINS my signed cheque (with my # on it)
				
				pTransaction->GetReferenceString(strRespTo);
				
				if (!strRespTo.Exists())
				{					
					OTLog::vOutput(0, "OTTransaction::VerifyBalanceReceipt: Inbox transaction (%ld) refers to another (%ld) but the ref string is missing.\n",
												   pTransaction->GetTransactionNum(), pTransaction->GetReferenceToNum());
					return false;
				}
				else
				{				
					OTItem * pOriginalItem = OTItem::CreateItemFromString(strRespTo, GetRealServerID(), pTransaction->GetReferenceToNum());
					OTCleanup<OTItem> theAngel(pOriginalItem);
					
					// This item was attached as the "in reference to" item. Perhaps Bob sent it to me.
					// Since that item was initiated by him, HIS would be the account ID on it, not mine.
					// So I DON'T want to create it with my account ID on it. I use above special function to instantiate it.
					//
					if (NULL == pOriginalItem)
					{
						OTLog::vError("Error loading original transaction item from string in OTTransaction::VerifyBalanceReceipt.\n");
						return false;
					}				
					else 
					{
						if ((OTItem::request == pOriginalItem->GetStatus())
							&&
							(OTItem::depositCheque	== pOriginalItem->GetType()))
						{
							// Get the cheque from the Item and load it up into a Cheque object.
							OTString strCheque;
							pOriginalItem->GetAttachment(strCheque);
							
							OTCheque theCheque; // allocated on the stack :-)
							
							if (false == ((strCheque.GetLength() > 2) && 
										  theCheque.LoadContractFromString(strCheque)))
							{
								OTLog::vError("ERROR loading cheque from string in OTTransaction::VerifyBalanceReceipt:\n%s\n",
											  strCheque.Get());
								return false;
							}
							else
								lIssuedNum = theCheque.GetTransactionNum();	// <========= The whole reason we did all this crap.
						}
						else 
						{
							const int nOriginalType = pOriginalItem->GetType();
							OTLog::vError( "Unrecognized item type (%d) OTTransaction::VerifyBalanceReceipt (expected depositCheque request).\n", 
										  nOriginalType);
							return false;
						}
					}
				} // if strRespTo.Exists()
				break;
			default:
				continue; // Below this point (inside the loop) is ONLY for receipts that somehow represent a transaction number that's still issued / signed out to me.
		}
		// -----------------------------------------------
		
		// Whether pSubItem is NULL or not, pTransaction DEFINITELY exists either way, in the newest inbox.
		// Therefore, let's verify whether I'm even responsible for that transaction number... (Just because I signed
		// the instrument at some point in the past does NOT mean that I'm still responsible for the transaction number
		// that's listed on the instrument. Maybe I already used it up a long time ago...)
		//
		if (!theMessageNym.VerifyIssuedNum(strServerID, lIssuedNum))
		{
			OTLog::vError("Error verifying if transaction num in inbox (%ld) was actually signed out (%ld), in OTTransaction::VerifyBalanceReceipt.\n",
						  pTransaction->GetTransactionNum(), lIssuedNum);
			return false;
		}
	} // for
	
	// BY THIS POINT, I have lReceiptBalanceChange with the total change in the receipt, and
	// lInboxBalanceChange with the total change in the new inbox. The difference between the two
	// is the difference I should expect also in the account balances! That amount should also
	// be equal to lInboxSupposedDifference, which is the total of JUST the inbox receipts that
	// I DIDN'T find in the old receipt (they were ONLY in the new inbox.)
	//
	// I have looped through all inbox items, and I know they were either found in the receipt's inbox record 
	// (and verified), or their amounts were added to lInboxSupposedDifference as appropriate.
	//
	// I also verified, for each inbox item, IF IT TAKES MONEY, THEN IT MUST HAVE A TRANSACTION NUMBER
	// SIGNED OUT TO ME... Otherwise I could dispute it. The last code above verifies this.
	//
	// All that's left is to make sure the balance is right...
	//
	// --------------------------------------------------
	
	// VERIFY ACCOUNT BALANCE (RECONCILING WITH NEW INBOX RECEIPTS)

	
	const long lActualDifference = (lReceiptBalanceChange - lInboxBalanceChange); // How much money came out? (Or went in, if the chequeReceipt was for an invoice...)
	
	// If the actual difference between the two totals is not equal to the supposed difference from adding up just the new receipts,
	// (Which is probably impossible anyway) then return false.
	//
	if (lActualDifference != lInboxSupposedDifference)
	{
		OTLog::vError("OTTransaction::VerifyBalanceReceipt: lActualDifference (%ld) is not equal to lInboxSupposedDifference (%ld)\n",
						lActualDifference, lInboxSupposedDifference);
		return false;
	}
	
	// If the actual difference (according to inbox receipts) + actual account balance (according to newest copy of account)
	// is not equal to the last signed balance agreement, then return false.
	//
	if ((lActualDifference + THE_ACCOUNT.GetBalance())	// Let's say ActualDifference == 10-3 (prev balance minus current balance) == 7.
			!= 											// If that's the case, then 7 + THE_ACCT.Balance should equal 10 again from the last balance statement!
		pBalanceItem->GetAmount()) // the balance according to the last valid balance statement.
	{
		OTLog::vError("OTTransaction::VerifyBalanceReceipt: lActualDifference in receipts (%ld) plus current acct balance (%ld) is NOT equal to last signed balance (%ld)\n",
					  lActualDifference, THE_ACCOUNT.GetBalance(), pBalanceItem->GetAmount());
		return false;		
	}
	
	// At this point: all good!
	// 
	
	return true;
}




// When the items are first loaded up, VerifyContractID() is called on them.
// Therefore, the serverID and account ID have already been verified.
// Now I want to go deeper, before actually processing a transaction, and 
// make sure that the items on it also have the right owner, as well as that
// owner's signature, and a matching transaction number to boot.
//
bool OTTransaction::VerifyItems(OTPseudonym & theNym)
{
	// loop through the ALL items that make up this transaction and check to see if a response to deposit.
	OTItem * pItem = NULL;
	
	const OTIdentifier NYM_ID(theNym);
	
	if (NYM_ID != GetUserID())
	{
		OTLog::Error("Wrong owner passed to OTTransaction::VerifyItems\n");
		return false;
	}

	// I'm not checking signature on transaction itself since that is already
	// checked before this function is called. But I AM calling Verify Owner,
	// so that when Verify Owner is called in the loop below, it proves the items
	// and the transaction both have the same owner: Nym.
	
	// if pointer not null, and it's a withdrawal, and it's an acknowledgement (not a rejection or error)
	for (listOfItems::iterator ii = GetItemList().begin(); ii != GetItemList().end(); ++ii)
	{
		pItem = *ii;
		
		OT_ASSERT(NULL != pItem);
		
		if (GetTransactionNum() != pItem->GetTransactionNum())
			return false;
		
		if (NYM_ID != pItem->GetUserID())
			return false;
		
		if (false == pItem->VerifySignature(theNym)) // NO need to call VerifyAccount since VerifyContractID is ALREADY called and now here's VerifySignature().
			return false; 
	}	
	
	return true;
}


// all common OTTransaction stuff goes here.
// (I don't like constructor loops, prefer to use a separate function they all call.)
void OTTransaction::InitTransaction()
{
	m_Type				= OTTransaction::error_state;
	m_strContractType	= "TRANSACTION"; // CONTRACT, MESSAGE, TRANSACTION, LEDGER, TRANSACTION ITEM 
	
	m_DATE_SIGNED = 0; // Make sure to this to the current time whenever contract is signed.
}


// private and hopefully not needed
OTTransaction::OTTransaction() : OTTransactionType()
{
	InitTransaction();
}


// Let's say you never knew their UserID, you just loaded the inbox based on AccountID.
// Now you want to add a transaction to that inbox. Just pass the inbox into the
// transaction constructor (below) and it will get the rest of the info it needs off of
// the inbox itself (which you presumably just read from a file or socket.)
OTTransaction::OTTransaction(const OTLedger & theOwner)
: OTTransactionType(theOwner.GetUserID(), theOwner.GetPurportedAccountID(), theOwner.GetPurportedServerID())
{
	InitTransaction();

}

// By calling this function, I'm saying "I know the real account ID and Server ID, and here
// they are, and feel free to compare them with whatever YOU load up, which we'll leave
// blank for now unless you generate a transaction, or load one up, 

// ==> or maybe I might need to add a constructor where another transaction or a ledger is passed in.
//      Then it can grab whatever it needs from those. I'm doing something similar in OTItem
OTTransaction::OTTransaction(const OTIdentifier & theUserID, const OTIdentifier & theAccountID, const OTIdentifier & theServerID)
: OTTransactionType(theUserID, theAccountID, theServerID)
{
	InitTransaction();
	
//	m_AcctID	= theID;		// these must be loaded or generated. NOT set in constructor, for security reasons.
//	m_ServerID	= theServerID;	
}

OTTransaction::OTTransaction(const OTIdentifier & theUserID, const OTIdentifier & theAccountID, const OTIdentifier & theServerID, long lTransactionNum)
: OTTransactionType(theUserID, theAccountID, theServerID, lTransactionNum)
{
	InitTransaction();
	
//	m_lTransactionNum = lTransactionNum;	// This is set in OTTransactionType's constructor, as are m_ID and m_ServerID
//	m_AcctID	= theID;					// these must be loaded or generated. NOT set in constructor, for security reasons.
//	m_ServerID	= theServerID;	
}



OTTransaction * OTTransaction::GenerateTransaction(const OTLedger & theOwner, transactionType theType, long lTransactionNum/*=0*/)
{
	return GenerateTransaction(theOwner.GetUserID(), theOwner.GetPurportedAccountID(), 
							   theOwner.GetPurportedServerID(), theType, lTransactionNum);
}

OTTransaction * OTTransaction::GenerateTransaction(const OTIdentifier & theUserID, 
												   const OTIdentifier & theAccountID, 
												   const OTIdentifier & theServerID, transactionType theType,
												   long lTransactionNum/*=0*/)
{
	OTTransaction * pTransaction = new OTTransaction(theUserID, theAccountID, theServerID, lTransactionNum);

	OT_ASSERT(NULL != pTransaction);
	
	pTransaction->m_Type = theType;
	
	// Since we're actually generating this transaction, then we can go ahead
	// and set the purported account and server IDs (we have already set the
	// real ones in the constructor). Now both sets are fill with matching data.
	// No need to security check the IDs since we are creating this transaction
	// versus loading and inspecting it.
	pTransaction->SetPurportedAccountID(theAccountID);
	pTransaction->SetPurportedServerID(theServerID);
	
	return pTransaction;
}



// the constructors set the real IDs (account and server) but they do not set the
// IDs that are internal to this object, m_AcctID and m_AcctServerID. These, it is assumed,
// will match the real IDs,but they must be checked when they are loaded.
// If you wish to create a transaction object, but SET the internal members (you KNOW they are correct
// or you want to generate them here) then use this function or make one like it.
bool OTTransaction::GenerateTransaction(const OTIdentifier & theAccountID, const OTIdentifier & theServerID, long lTransactionNum)
{
	// Presumably the constructor was just called, so m_ID and m_ServerID are already set properly.
	// I might make a class factory in order to enforce this. Sounds like an appropriate situation.
	//m_ID
	//m_ServerID
	
	SetPurportedAccountID(theAccountID);
	SetPurportedServerID(theServerID);
	
	SetTransactionNum(lTransactionNum);
	
	// Make sure these match with the ones that were passed into the constructor.
	return VerifyContractID();
}




bool OTTransaction::SaveContractWallet(std::ofstream & ofs)
{
	return true;
}




OTTransaction::~OTTransaction()
{
	ReleaseItems();
}


void OTTransaction::ReleaseItems()
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
void OTTransaction::AddItem(OTItem & theItem) 
{ 
	m_listItems.push_back(&theItem);  
} 


// While processing a transaction, you may wish to query it for items of a certain type.
OTItem * OTTransaction::GetItem(const OTItem::itemType theType) 
{
	OTItem * pItem = NULL;

	for (listOfItems::iterator ii = m_listItems.begin(); ii != m_listItems.end(); ++ii)
	{
		pItem = *ii;
		
		OT_ASSERT(NULL != pItem);
		
		if (pItem->GetType() == theType)
			return pItem;
	}
	
	return NULL;
}


// Tries to determine, based on items within, whether it was a success or fail.
bool OTTransaction::GetSuccess()
{
	OTItem * pItem = NULL;
	
	for (listOfItems::iterator ii = m_listItems.begin(); ii != m_listItems.end(); ++ii)
	{
		pItem = *ii;
		
		OT_ASSERT(NULL != pItem);
		
		switch (pItem->GetType()) 
		{
			case OTItem::atTransaction:
			case OTItem::atTransfer:
				
			case OTItem::atAcceptTransaction:
			case OTItem::atAcceptMessage:
				
			case OTItem::atAcceptPending:
			case OTItem::atRejectPending:
				
			case OTItem::atAcceptCronReceipt:
			case OTItem::atDisputeCronReceipt:
			case OTItem::atAcceptItemReceipt:
			case OTItem::atDisputeItemReceipt:
				
			case OTItem::atServerfee:
			case OTItem::atIssuerfee:
			case OTItem::atBalanceStatement:
			case OTItem::atTransactionStatement:
			case OTItem::atWithdrawal:
			case OTItem::atDeposit:
			case OTItem::atWithdrawVoucher:
			case OTItem::atDepositCheque:
			case OTItem::atMarketOffer:
			case OTItem::atPaymentPlan:
				
//			case OTItem::chequeReceipt: // not needed in OTItem.
			case OTItem::chequeReceipt: // but it's here anyway for dual use reasons (balance agreement sub-items)
			case OTItem::marketReceipt:
			case OTItem::paymentReceipt:
			case OTItem::transferReceipt:
				
				if (OTItem::acknowledgement == pItem->GetStatus())
				{
					return true;
				}
				else if (OTItem::rejection == pItem->GetStatus())
				{
					return false;
				}
				break;
			default:
				OTLog::Error("Wrong transaction type passed to OTTransaction::GetSuccess()\n");
				break;
		}
	}
	
	return false;
}







// This is called automatically by SignContract to make sure what's being signed is the most up-to-date
// Before transmission or serialization, this is where the ledger saves its contents 
// So let's make sure this transaction has the right contents.
void OTTransaction::UpdateContents() 
{	
	const char * pTypeStr = GetTypeString();
	
	
	OTString	strType, 
	strAcctID(GetPurportedAccountID()), 
	strServerID(GetPurportedServerID()),
	strUserID(GetUserID());
	
	if (NULL != pTypeStr)
		strType.Set(pTypeStr);
	else
		strType.Set("error_state"); // todo: internationalization.
	
	
	m_DATE_SIGNED = time(NULL); // We store the timestamp of when this transaction was signed.
	const long lDateSigned = m_DATE_SIGNED;
	
	// I release this because I'm about to repopulate it.
	m_xmlUnsigned.Release();
	
	m_xmlUnsigned.Concatenate("<transaction type=\"%s\"\n"
							  " dateSigned=\"%ld\"\n"
							  " accountID=\"%s\"\n"
							  " userID=\"%s\"\n"
							  " serverID=\"%s\"\n"
							  " transactionNum=\"%ld\"\n"
							  " inReferenceTo=\"%ld\" >\n\n", 
							  strType.Get(), lDateSigned, strAcctID.Get(), strUserID.Get(), strServerID.Get(), GetTransactionNum(),
							  GetReferenceToNum());
	
	//	OTLog::vError("IN REFERENCE TO, LENGTH: %d\n", m_ascInReferenceTo.GetLength());
	
	// a transaction contains a list of items, but it is also in reference to some item, from someone else
	// We include that item here.
	if (m_ascInReferenceTo.GetLength())
		m_xmlUnsigned.Concatenate("<inReferenceTo>\n%s</inReferenceTo>\n\n", m_ascInReferenceTo.Get());
	
	// loop through the items that make up this transaction and print them out here, base64-encoded, of course.
	OTItem * pItem = NULL;
	
	for (listOfItems::iterator ii = m_listItems.begin(); ii != m_listItems.end(); ++ii)
	{
		if ((pItem = *ii)) // if pointer not null
		{
			OTString strItem;
			pItem->SaveContract(strItem);
			
			OTASCIIArmor ascItem;
			ascItem.SetString(strItem, true); // linebreaks = true
			
			m_xmlUnsigned.Concatenate("<item>\n%s</item>\n\n", ascItem.Get());
		}
	}	
	
	m_xmlUnsigned.Concatenate("</transaction>\n");					
}


// return -1 if error, 0 if nothing, and 1 if the node was processed.
int OTTransaction::ProcessXMLNode(irr::io::IrrXMLReader*& xml)
{	
	if (!strcmp("transaction", xml->getNodeName()))
	{	
		OTString strType, strAcctID, strServerID, strUserID;

		strType = xml->getAttributeValue("type");
		
		if (strType.Compare("blank"))
			m_Type = OTTransaction::blank;
		else if (strType.Compare("pending"))
			m_Type = OTTransaction::pending;
		else if (strType.Compare("message"))
			m_Type = OTTransaction::message;
		else if (strType.Compare("processNymbox"))
			m_Type = OTTransaction::processNymbox;
		else if (strType.Compare("atProcessNymbox"))
			m_Type = OTTransaction::atProcessNymbox;
		else if (strType.Compare("processInbox"))
			m_Type = OTTransaction::processInbox;
		else if (strType.Compare("atProcessInbox"))
			m_Type = OTTransaction::atProcessInbox;
		else if (strType.Compare("transfer"))
			m_Type = OTTransaction::transfer;
		else if (strType.Compare("atTransfer"))
			m_Type = OTTransaction::atTransfer;
		else if (strType.Compare("deposit"))
			m_Type = OTTransaction::deposit;
		else if (strType.Compare("atDeposit"))
			m_Type = OTTransaction::atDeposit;
		else if (strType.Compare("withdrawal"))
			m_Type = OTTransaction::withdrawal;
		else if (strType.Compare("atWithdrawal"))
			m_Type = OTTransaction::atWithdrawal;
		else if (strType.Compare("marketOffer"))
			m_Type = OTTransaction::marketOffer;
		else if (strType.Compare("atMarketOffer"))
			m_Type = OTTransaction::atMarketOffer;
		else if (strType.Compare("paymentPlan"))
			m_Type = OTTransaction::paymentPlan;
		else if (strType.Compare("atPaymentPlan"))
			m_Type = OTTransaction::atPaymentPlan;
		
		else if (strType.Compare("transferReceipt"))
			m_Type = OTTransaction::transferReceipt;
		else if (strType.Compare("chequeReceipt"))
			m_Type = OTTransaction::chequeReceipt;
		else if (strType.Compare("marketReceipt"))
			m_Type = OTTransaction::marketReceipt;
		else if (strType.Compare("paymentReceipt"))
			m_Type = OTTransaction::paymentReceipt;
		else
			m_Type = OTTransaction::error_state;
		
		
		OTString strDateSigned(xml->getAttributeValue("dateSigned"));
		
		const long lDateSigned = strDateSigned.Exists() ? atol(strDateSigned.Get()) : 0;
		
		m_DATE_SIGNED = lDateSigned;
		
		strAcctID	= xml->getAttributeValue("accountID"); 
		strServerID	= xml->getAttributeValue("serverID");
		strUserID	= xml->getAttributeValue("userID");
		
		OTIdentifier ACCOUNT_ID(strAcctID), SERVER_ID(strServerID), USER_ID(strUserID);
		
		SetPurportedAccountID(ACCOUNT_ID);
		SetPurportedServerID(SERVER_ID);
		SetUserID(USER_ID);
		SetTransactionNum(atol(xml->getAttributeValue("transactionNum")));
		SetReferenceToNum(atol(xml->getAttributeValue("inReferenceTo")));
		
		OTLog::vOutput(2, "Loaded transaction %ld, in reference to: %ld type: %s\n",
//				"accountID:\n%s\n serverID:\n%s\n----------\n", 
				GetTransactionNum(),
				GetReferenceToNum(), strType.Get()
//				strAcctID.Get(), strServerID.Get()
				);
		
		return 1;
	}
	else if (!strcmp("inReferenceTo", xml->getNodeName())) 
	{		
		if (false == LoadEncodedTextField(xml, m_ascInReferenceTo))
		{
			OTLog::Error("Error in OTTransaction::ProcessXMLNode: inReferenceTo field without value.\n");
			return (-1); // error condition
		}
		
		return 1;
	}
	
	else if (!strcmp("item", xml->getNodeName())) 
	{		
		OTString strData;

		if (!LoadEncodedTextField(xml, strData) || !strData.Exists())
		{
			OTLog::Error("Error in OTTransaction::ProcessXMLNode: transaction item field without value.\n");
			return (-1); // error condition
		}
		else 
		{
			OTItem * pItem = new OTItem(GetUserID(), *this);
			
			OT_ASSERT(NULL != pItem);
			
			// If we're able to successfully base64-decode the string and load it up as
			// a transaction, then add it to the ledger's list of transactions
			if (pItem->LoadContractFromString(strData) && pItem->VerifyContractID())
			{
				m_listItems.push_back(pItem);
//				OTLog::Output(5, "Loaded transaction Item and adding to m_listItems in OTTransaction\n");
			}
			else 
			{
				OTLog::Error("ERROR: loading transaction Item in OTTransaction::ProcessXMLNode\n");
				delete pItem;
				pItem = NULL;
				return (-1);
			}			
		}

		return 1;
	}
		
	return 0;
}




// The ONE case where an Item has SUB-ITEMS is in the case of Balance Agreement.
// For example, you might have a Withdrawal Transaction (request) that contains
// 2 items: the withdrawal item itself, and the balance agreement item for that
// withdrawal.  The balance agreement item contains a LIST OF SUB ITEMS, each of
// which represents a chequeReceipt, marketReceipt, or paymentReceipt from my 
// inbox. The Balance Agreement item needs to be able to report on the inbox
// status, so I give it a list of sub-items.
void OTTransaction::ProduceInboxReportItem(OTItem & theBalanceItem) 
{	
	OTItem::itemType theItemType = OTItem::error_state;
	
	OTLog::vOutput(1, "Producing statement report item for inbox item type: %s.\n", GetTypeString()); // temp remove.
	
	switch (m_Type) 
	{	// These are the types that have an amount (somehow)
		case OTTransaction::pending: // the amount is stored on the transfer item in my list.
			theItemType = OTItem::transfer;
			break;
		case OTTransaction::chequeReceipt: // the amount is stored on cheque (attached to depositCheque item, attached.)
			theItemType = OTItem::chequeReceipt;
			break;
		case OTTransaction::marketReceipt: // the amount is stored on marketReceipt item
			theItemType = OTItem::marketReceipt;
			break;
		case OTTransaction::paymentReceipt:	// amount is stored on paymentReceipt item
			theItemType = OTItem::paymentReceipt;			
			break;
		case OTTransaction::transferReceipt:	// amount is 0 according to GetReceiptAmount()
			theItemType = OTItem::transferReceipt;			
			break;
		default: // All other types are irrelevant for inbox reports
		{
			OTLog::vOutput(1, "OTTransaction::ProduceInboxReportItem: Ignoring %s transaction "
						   "in inbox while making balance statement.\n", GetTypeString());
		}
			return;
	}	// why not transfer receipt? Because the amount was already removed from your account when you transferred it,
	    // and you already signed a balance agreement at that time. Thus, nothing in your inbox is necessary to prove
	    // the change in balance -- you already signed off on it. UPDATE: that's okay since the below GetReceiptAmount()
	    // will return 0 for a transfer receipt anyway.
	
	// the item will represent THIS TRANSACTION, and will be added to theBalanceItem.
	
	OTItem * pReportItem = OTItem::CreateItemFromTransaction(*this, theItemType);
	
	if (NULL != pReportItem) // above line will assert if mem allocation fails.
	{		
		long lAmount = GetReceiptAmount();
		pReportItem->SetAmount(lAmount);
		
		pReportItem->SetTransactionNum(GetTransactionNum()); // Just making sure these both get set.
		pReportItem->SetReferenceToNum(GetReferenceToNum()); // Especially this one.
		
		theBalanceItem.AddItem(*pReportItem); // Now theBalanceItem will handle cleaning it up.
		
		// No need to sign/save pReportItem, since it is just used for in-memory storage, and is
		// otherwise saved as part of its owner's data, as part of its owner. (As long as theBalanceItem
		// is signed and saved, which the caller does, then we're fine.)
	}
}


// No longer using outbox hash :(
// Since I would have to add the pending items to the outbox and calculate
// it myself, and there's no way every single byte would be the same as the server
// (Well with this implementation there is, actually, but what one of the items
// in the outbox is SIGNED by me on one side, and by the server on the other? the
// hashes won't match!)  Therefore I'm sending a real outbox report, the same as
// I do for the inbox. In fact, it's the same report! Just more items being added.
//
void OTTransaction::ProduceOutboxReportItem(OTItem & theBalanceItem) 
{	
	OTItem::itemType theItemType = OTItem::error_state;
	
	switch (m_Type) 
	{
		case OTTransaction::pending:
			theItemType = OTItem::transfer;
			break;
		default: // All other types are irrelevant for outbox reports.
			return;
	}
	
	// the item will represent THIS TRANSACTION, and will be added to theBalanceItem.
	
	OTItem * pReportItem = OTItem::CreateItemFromTransaction(*this, theItemType);
	
	if (NULL != pReportItem) // above line will assert if mem allocation fails.
	{		
		const long lAmount = GetReceiptAmount()*(-1); // in outbox, a transfer is leaving my account. Balance gets smaller.
		pReportItem->SetAmount(lAmount);
		
		pReportItem->SetTransactionNum(GetTransactionNum()); // Just making sure these both get set.
		pReportItem->SetReferenceToNum(GetReferenceToNum()); // Especially this one.
		
		theBalanceItem.AddItem(*pReportItem); // Now theBalanceItem will handle cleaning it up.
		
		// No need to sign/save pReportItem, since it is just used for in-memory storage, and is
		// otherwise saved as part of its owner's data, as part of its owner. (As long as theBalanceItem
		// is signed and saved, which the caller does, then we're fine.)
	}
}



// A Transaction normally doesn't have an amount. (Only a transaction item does.)
// But this function will look up the item, when appropriate, and find out the amount.
//
// That way we can record it during a balance agreement.
// NOTE: Not ALL transaction types with an amount are listed here,
// just the ones necessary for balance agreement.
//
long OTTransaction::GetReceiptAmount()
{
	long lAdjustment = 0;
	
	OTString strReference;
	GetReferenceString(strReference);
	
	OTItem * pOriginalItem = NULL;
	
	switch (GetType()) 
	{	// These are the types that have an amount (somehow)
		case OTTransaction::pending: // amount is stored on the transfer item, on my list of items.
		case OTTransaction::chequeReceipt: // amount is stored on cheque (attached to depositCheque item, attached.)
		case OTTransaction::marketReceipt: // amount is stored on marketReceipt item
		case OTTransaction::transferReceipt:	// amount is stored on acceptPending item
		case OTTransaction::paymentReceipt:	// amount is stored on paymentReceipt item
			pOriginalItem = OTItem::CreateItemFromString(strReference, GetPurportedServerID(), GetReferenceToNum());
			break;
		default: // All other types have no amount -- return 0.
			return 0;
	}
	
	OTCleanup<OTItem> theItemAngel(pOriginalItem);
	
	if (NULL == pOriginalItem)
		return 0; // Should never happen, since we always expect one based on the transaction type.
	
	// -------------------------------------------------
	
	OTString strAttachment;
	
	OTCheque theCheque; // allocated on the stack :-)

	switch (GetType()) 
	{	// These are the types that have an amount (somehow)
		case OTTransaction::chequeReceipt: // amount is stored on cheque (attached to depositCheque item, attached.)
			
		{
			if (pOriginalItem->GetType() != OTItem::depositCheque)
			{
				OTLog::Error("Wrong item type attached to chequeReceipt\n");
				return 0;
			}
			
			// Get the cheque from the Item and load it up into a Cheque object.
			pOriginalItem->GetAttachment(strAttachment);
			bool bLoadContractFromString = theCheque.LoadContractFromString(strAttachment);
			
			if (!bLoadContractFromString)
			{
				OTString strCheque(theCheque);
				
				OTLog::vError("ERROR loading cheque from string in OTTransaction::GetReceiptAmount:\n%s\n",
							  strCheque.Get());
			}
			else 
			{
				lAdjustment = (theCheque.GetAmount()*(-1)); // a cheque reduces my balance, unless it's negative.
			}												// So if I wrote a 100clam cheque, that  means -100 hit my account when I got the
															// chequeReceipt, and writing a -100c cheque means 100 went in when I got the chequeReceipt.
		}
			break;
			
		case OTTransaction::transferReceipt: // amount is stored on acceptPending item. (Server refuses acceptPendings with wrong amount on them.)
			
			if (pOriginalItem->GetType() != OTItem::acceptPending)
			{
				OTLog::Error("Wrong item type attached to transferReceipt\n");
			}
			else
			{	// If I transfer 100 clams to someone, then my account is smaller by 100 clams. -100 has hit my account.
				// So it will show as -100 in my outbox, not 100, because that is the adjustment actually made to my account.
				lAdjustment = (pOriginalItem->GetAmount()*(-1));	
			}
			break;
		case OTTransaction::pending: // amount is stored on transfer item
			
			if (pOriginalItem->GetType() != OTItem::transfer)
			{
				OTLog::Error("Wrong item type attached to pending transfer\n");
			}
			else
			{
				// Pending transfer adds to my account if this is inbox, and removes if outbox. 
				// I'll let the caller multiply by (-1) or not. His choice.
				// Note: Indeed, if you look in ProduceOutboxReportItem(), it is multiplying by (-1).
				lAdjustment = pOriginalItem->GetAmount();	
			}
			break;
		case OTTransaction::marketReceipt: // amount is stored on marketReceipt item
			
			if (pOriginalItem->GetType() != OTItem::marketReceipt)
			{
				OTLog::Error("Wrong item type attached to marketReceipt\n");
			}
			else
			{
				lAdjustment = pOriginalItem->GetAmount();	// THIS WILL ALSO USE THE POSITIVE / NEGATIVE THING. (Already.)
			}
			break;
		case OTTransaction::paymentReceipt:	// amount is stored on paymentReceipt item
			
			if (pOriginalItem->GetType() != OTItem::paymentReceipt)
			{
				OTLog::Error("Wrong item type attached to paymentReceipt\n");
			}
			else
			{
				lAdjustment = pOriginalItem->GetAmount();	// THIS WILL ALSO USE THE POSITIVE / NEGATIVE THING. (Already.)
			}
			
			break;
		default: // All other types have no amount -- return 0.
			return 0;
	}
	
	return lAdjustment;
}




/// for display purposes. The "reference #" we show the user is not the same one we used internally.
///
/// The "display reference #" that we want to display for the User might be 
/// different depending on the type.
/// 
/// For example, if pending, then it's in ref to the original transfer request (sender's transaction #)
/// But if chequeReceipt, then it's in reference to the original cheque (also sender's transaction #)
/// But if marketReceipt, then it's in reference to the original market offer (which is my own trans#)
/// But if paymentReceipt, then it's in reference to the original "activate payment plan" request, which may or may not be mine.
///
/// Internally of course, a chequeReceipt is "in reference to" the depositor's deposit request.
/// But the user doesn't care about that number -- he wants to see the original cheque # from when he first wrote it.
/// Thus we have this function for resolving the "display reference #" in cases like that.
/// Another example: with market trades, you want the "in reference to" to show the trans# of the original market offer request.
/// Of course, if you load up the item within, you can get the "in reference to" showing a different trans# for EACH TRADE THAT HAS OCCURRED.
/// We use that internally, we need to be able to reference each of those trades. But the user merely wants to see that his receipt is
/// in reference to the original market offer, so he can line up his receipts with his offers. What else does he care?
///
long OTTransaction::GetReferenceNumForDisplay()
{
	long lReferenceNum = 0;
	
	OTItem * pOriginalItem = NULL;
	OTCleanup<OTItem> theItemAngel;
		
	switch (GetType()) 
	{
			// "in ref to #" is stored on me: GetReferenceToNum()
		case OTTransaction::pending: 
		case OTTransaction::marketReceipt:
		case OTTransaction::paymentReceipt:
			lReferenceNum = GetReferenceToNum();
			break;
			
		case OTTransaction::transferReceipt:
		{
			OTString strReference;
			GetReferenceString(strReference);
			
			pOriginalItem = OTItem::CreateItemFromString(strReference, GetPurportedServerID(), GetReferenceToNum()); 
			OT_ASSERT(NULL != pOriginalItem);
			theItemAngel.SetCleanupTarget(*pOriginalItem);
			
			if (pOriginalItem->GetType() != OTItem::acceptPending) 
			{
				OTLog::Error("Wrong item type attached to transferReceipt\n");
				return 0;
			}
			else 
			{
				lReferenceNum = pOriginalItem->GetReferenceToNum();				
			}
		}
			break;			
			
			// "in ref to #" is the transaction# on the cheque (attached to depositCheque item, attached.)
		case OTTransaction::chequeReceipt: 
		{
			OTString strReference;
			GetReferenceString(strReference);
			
			pOriginalItem = OTItem::CreateItemFromString(strReference, GetPurportedServerID(), GetReferenceToNum()); // in this case "reference to" is the depositor's trans#, which I use here, but the User doesn't care about on the screen.
			OT_ASSERT(NULL != pOriginalItem);
			theItemAngel.SetCleanupTarget(*pOriginalItem);
			
			OTString strAttachment;
			OTCheque theCheque; // allocated on the stack :-)
			
			if (pOriginalItem->GetType() != OTItem::depositCheque) // This is a deposit cheque item, signed by the depositor, presumably whomever I gave the cheque to.
			{
				OTLog::Error("Wrong item type attached to chequeReceipt\n");
				return 0;
			}
			
			// Get the cheque from the Item and load it up into a Cheque object.
			pOriginalItem->GetAttachment(strAttachment);
			bool bLoadContractFromString = theCheque.LoadContractFromString(strAttachment);
			
			if (!bLoadContractFromString)
			{
				OTString strCheque(theCheque);
				
				OTLog::vError("ERROR loading cheque from string in OTTransaction::CalcReferenceNum:\n%s\n",
							  strCheque.Get());
			}
			else 
			{
				lReferenceNum = theCheque.GetTransactionNum();				
			}
		}
			break;
			
		default: // All other types have no amount -- return 0.
			return 0;
	}
	
	
	// -------------------------------------------------
	
	return lReferenceNum;
}


// -----------------------------------------



bool OTTransaction::GetSenderUserIDForDisplay(OTIdentifier & theReturnID)
{
	bool bSuccess = false;
	
	OTString strReference;
	GetReferenceString(strReference);
	
	OTItem * pOriginalItem = NULL;
	
	switch (GetType()) 
	{	// These are the types that have an amount (somehow)
		case OTTransaction::pending: // amount is stored on the transfer item, on my list of items.
		case OTTransaction::chequeReceipt: // amount is stored on cheque (attached to depositCheque item, attached.)
		case OTTransaction::marketReceipt: // amount is stored on marketReceipt item
		case OTTransaction::paymentReceipt:	// amount is stored on paymentReceipt item
			pOriginalItem = OTItem::CreateItemFromString(strReference, GetPurportedServerID(), GetReferenceToNum());
			break;
		default: // All other types have no amount -- return 0.
			return false;
	}
	
	OTCleanup<OTItem> theItemAngel(pOriginalItem);
	
	if (NULL == pOriginalItem)
		return false; // Should never happen, since we always expect one based on the transaction type.
	
	// -------------------------------------------------
	
	OTString strAttachment;
	
	OTCheque theCheque; // allocated on the stack :-)
	
	switch (GetType()) 
	{	// These are the types that have an amount (somehow)
		case OTTransaction::chequeReceipt: // amount is stored on cheque (attached to depositCheque item, attached.)
			
		{
			if (pOriginalItem->GetType() != OTItem::depositCheque)
			{
				OTLog::Error("Wrong item type attached to chequeReceipt\n");
				return false;
			}
			
			// Get the cheque from the Item and load it up into a Cheque object.
			pOriginalItem->GetAttachment(strAttachment);
			bool bLoadContractFromString = theCheque.LoadContractFromString(strAttachment);
			
			if (!bLoadContractFromString)
			{
				OTString strCheque(theCheque);
				
				OTLog::vError("ERROR loading cheque from string in OTTransaction::GetSenderUserIDForDisplay:\n%s\n",
							  strCheque.Get());
			}
			else 
			{
				theReturnID = theCheque.GetSenderUserID(); 
				bSuccess = true;
			}
		}
			break;
			
		case OTTransaction::pending: // amount is stored on transfer item
			
			if (pOriginalItem->GetType() != OTItem::transfer)
			{
				OTLog::Error("Wrong item type attached to pending transfer\n");
			}
			else
			{
				theReturnID = pOriginalItem->GetUserID();	
				bSuccess = true;
			}
			break;
		case OTTransaction::marketReceipt: // amount is stored on marketReceipt item
			
			if (pOriginalItem->GetType() != OTItem::marketReceipt)
			{
				OTLog::Error("Wrong item type attached to marketReceipt\n");
			}
			else
			{
				theReturnID = pOriginalItem->GetUserID();	
				bSuccess = true;
			}
			break;
		case OTTransaction::paymentReceipt:	// amount is stored on paymentReceipt item
			
			if (pOriginalItem->GetType() != OTItem::paymentReceipt)
			{
				OTLog::Error("Wrong item type attached to paymentReceipt\n");
			}
			else
			{
				theReturnID = pOriginalItem->GetUserID();	
				bSuccess = true;
			}
			
			break;
		default: // All other types have no amount -- return 0.
			return false;
	}
	
	return bSuccess;
}



bool OTTransaction::GetRecipientUserIDForDisplay(OTIdentifier & theReturnID)
{
	bool bSuccess = false;
	
	OTString strReference;
	GetReferenceString(strReference);
	
	OTItem * pOriginalItem = NULL;
	
	switch (GetType()) 
	{	
		case OTTransaction::transferReceipt: 
		case OTTransaction::chequeReceipt: 
		case OTTransaction::marketReceipt:
		case OTTransaction::paymentReceipt:	
			pOriginalItem = OTItem::CreateItemFromString(strReference, GetPurportedServerID(), GetReferenceToNum());
			break;
		default: // All other types have no amount -- return 0.
			return false;
	}
	
	OTCleanup<OTItem> theItemAngel(pOriginalItem);
	
	if (NULL == pOriginalItem)
		return false; // Should never happen, since we always expect one based on the transaction type.
	
	// -------------------------------------------------
	
	switch (GetType()) 
	{	
		case OTTransaction::transferReceipt:
		{
			if (pOriginalItem->GetType() != OTItem::acceptPending)
			{
				OTLog::Error("Wrong item type attached to transferReceipt\n");
				return false;
			}
			else 
			{
				theReturnID = pOriginalItem->GetUserID();  // Even though a transfer has no recipient user (just a recipient acct) I still get the User ID when he accepts it!
				bSuccess = true;
			}
		}
			break;
			
		case OTTransaction::chequeReceipt: // amount is stored on cheque (attached to depositCheque item, attached.)
		{
			if (pOriginalItem->GetType() != OTItem::depositCheque)
			{
				OTLog::Error("Wrong item type attached to chequeReceipt\n");
				return false;
			}
			else 
			{
				theReturnID = pOriginalItem->GetUserID();  // Even if the cheque had a blank payee, I still get his UserID when he deposits it.
				bSuccess = true;
			}
		}
			break;
			
		case OTTransaction::marketReceipt: // amount is stored on marketReceipt item
			if (pOriginalItem->GetType() != OTItem::marketReceipt)
			{
				OTLog::Error("Wrong item type attached to marketReceipt\n");
			}
			else
			{
				theReturnID = pOriginalItem->GetUserID();	
				bSuccess = true;
			}
			break;
			
		case OTTransaction::paymentReceipt:	// amount is stored on paymentReceipt item
			
			if (pOriginalItem->GetType() != OTItem::paymentReceipt)
			{
				OTLog::Error("Wrong item type attached to paymentReceipt\n");
			}
			else
			{
				theReturnID = pOriginalItem->GetUserID();	
				bSuccess = true;
			}
			
			break;
			
		default: // All other types have no amount -- return 0.
			return false;
	}
	
	return bSuccess;
}


bool OTTransaction::GetSenderAcctIDForDisplay(OTIdentifier & theReturnID)
{
	bool bSuccess = false;
	
	OTString strReference;
	GetReferenceString(strReference);
	
	OTItem * pOriginalItem = NULL;
	
	switch (GetType()) 
	{	// These are the types that have an amount (somehow)
		case OTTransaction::pending: // amount is stored on the transfer item, on my list of items.
		case OTTransaction::chequeReceipt: // amount is stored on cheque (attached to depositCheque item, attached.)
		case OTTransaction::marketReceipt: // amount is stored on marketReceipt item
		case OTTransaction::paymentReceipt:	// amount is stored on paymentReceipt item
			pOriginalItem = OTItem::CreateItemFromString(strReference, GetPurportedServerID(), GetReferenceToNum());
			break;
		default: // All other types have no amount -- return 0.
			return false;
	}
	
	OTCleanup<OTItem> theItemAngel(pOriginalItem);
	
	if (NULL == pOriginalItem)
		return false; // Should never happen, since we always expect one based on the transaction type.
	
	// -------------------------------------------------
	
	OTString strAttachment;
	
	OTCheque theCheque; // allocated on the stack :-)
	
	switch (GetType()) 
	{	// These are the types that have an amount (somehow)
		case OTTransaction::chequeReceipt: // amount is stored on cheque (attached to depositCheque item, attached.)
			
		{
			if (pOriginalItem->GetType() != OTItem::depositCheque)
			{
				OTLog::Error("Wrong item type attached to chequeReceipt\n");
				return false;
			}
			
			// Get the cheque from the Item and load it up into a Cheque object.
			pOriginalItem->GetAttachment(strAttachment);
			bool bLoadContractFromString = theCheque.LoadContractFromString(strAttachment);
			
			if (!bLoadContractFromString)
			{
				OTString strCheque(theCheque);
				
				OTLog::vError("ERROR loading cheque from string in OTTransaction::GetSenderUserIDForDisplay:\n%s\n",
							  strCheque.Get());
			}
			else 
			{
				theReturnID = theCheque.GetSenderAcctID(); 
				bSuccess = true;
			}
		}
			break;
			
		case OTTransaction::pending: // amount is stored on transfer item
			
			if (pOriginalItem->GetType() != OTItem::transfer)
			{
				OTLog::Error("Wrong item type attached to pending transfer\n");
			}
			else
			{
				theReturnID = pOriginalItem->GetPurportedAccountID();	
				bSuccess = true;
			}
			break;
		case OTTransaction::marketReceipt: // amount is stored on marketReceipt item
			
			if (pOriginalItem->GetType() != OTItem::marketReceipt)
			{
				OTLog::Error("Wrong item type attached to marketReceipt\n");
			}
			else
			{
				theReturnID = pOriginalItem->GetPurportedAccountID();	
				bSuccess = true;
			}
			break;
		case OTTransaction::paymentReceipt:	// amount is stored on paymentReceipt item
			
			if (pOriginalItem->GetType() != OTItem::paymentReceipt)
			{
				OTLog::Error("Wrong item type attached to paymentReceipt\n");
			}
			else
			{
				theReturnID = pOriginalItem->GetPurportedAccountID();	
				bSuccess = true;
			}
			
			break;
		default: // All other types have no amount -- return 0.
			return false;
	}
	
	return bSuccess;
}


bool OTTransaction::GetRecipientAcctIDForDisplay(OTIdentifier & theReturnID)
{
	bool bSuccess = false;
	
	OTString strReference;
	GetReferenceString(strReference);
	
	OTItem * pOriginalItem = NULL;
	
	switch (GetType()) 
	{	
		case OTTransaction::pending: 
		case OTTransaction::transferReceipt: 
		case OTTransaction::chequeReceipt: 
		case OTTransaction::marketReceipt:
		case OTTransaction::paymentReceipt:
			pOriginalItem = OTItem::CreateItemFromString(strReference, GetPurportedServerID(), GetReferenceToNum());
			break;
		default: // All other types have no amount -- return 0.
			return false;
	}
	
	OTCleanup<OTItem> theItemAngel(pOriginalItem);
	
	if (NULL == pOriginalItem)
		return false; // Should never happen, since we always expect one based on the transaction type.
	
	// -------------------------------------------------
	
	OTString strAttachment;
	
	OTCheque theCheque; // allocated on the stack :-)
	
	switch (GetType()) 
	{
		case OTTransaction::transferReceipt:
		{
			if (pOriginalItem->GetType() != OTItem::acceptPending)
			{
				OTLog::Error("Wrong item type attached to transferReceipt\n");
				return false;
			}
			else 
			{
				theReturnID = pOriginalItem->GetPurportedAccountID();  
				bSuccess = true;
			}
		}
			break;
			
		case OTTransaction::chequeReceipt:
			
		{
			if (pOriginalItem->GetType() != OTItem::depositCheque)
			{
				OTLog::Error("Wrong item type attached to chequeReceipt\n");
				return false;
			}
			else 
			{
				theReturnID = pOriginalItem->GetPurportedAccountID(); // Here's the depositor's account ID (even though the cheque was made out to a user, not an account, it still eventually had to be DEPOSITED into an account... right?)
				bSuccess = true;
			}
		}
			break;
			
		case OTTransaction::pending: // amount is stored on transfer item
			
			if (pOriginalItem->GetType() != OTItem::transfer)
			{
				OTLog::Error("Wrong item type attached to pending transfer\n");
			}
			else
			{
				theReturnID = pOriginalItem->GetDestinationAcctID();	
				bSuccess = true;
			}
			break;
		case OTTransaction::marketReceipt: // amount is stored on marketReceipt item
			
			if (pOriginalItem->GetType() != OTItem::marketReceipt)
			{
				OTLog::Error("Wrong item type attached to marketReceipt\n");
			}
			else
			{
				theReturnID = pOriginalItem->GetDestinationAcctID();	
				bSuccess = true;
			}
			break;
		case OTTransaction::paymentReceipt:	// amount is stored on paymentReceipt item
			
			if (pOriginalItem->GetType() != OTItem::paymentReceipt)
			{
				OTLog::Error("Wrong item type attached to paymentReceipt\n");
			}
			else
			{
				theReturnID = pOriginalItem->GetDestinationAcctID();	
				bSuccess = true;
			}
			
			break;
		default: // All other types have no amount -- return 0.
			return false;
	}
	
	return bSuccess;
}

 



