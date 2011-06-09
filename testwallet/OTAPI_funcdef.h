/************************************************************************************
 *    
 *  OTAPI_funcdef.h  -- Any function defs added to the OTAPI interface go here.
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



// DO NOT INCLUDE THIS FILE, anywhere!
// 
// (It's used internally.)
// Instead, if you want to use the functions defined here, #include "OTAPI.h" instead.
//
// (That file will include this one, but in the appropriate way.)

	



// --------------------------------------------------------------------
/**
 INITIALIZE the OTAPI
 
 Call this first, to initialize the library. It needs to know the path
 to the data_folder, which on the client side is inside the testwallet folder.
 
 Something like this:
 
 OT_BOOL bInit = OT_API_Init("/absolute-path-goes-here/Open-Transactions/testwallet/data_folder");
 
 */
int OT_API_Init(const char * szClientPath); // actually returns BOOL





// --------------------------------------------------------------------
/**
 LOAD WALLET
 
 Next you'll want to load your wallet up. It needs to be in the data_folder.
 Just pass in the filename.  Like this:
 
 OT_API_LoadWallet("wallet.xml");
 
 */
int OT_API_LoadWallet(const char * szWalletFilename); // actually returns BOOL




// --------------------------------------------------------------------
/**
 SWITCH WALLET
 
 Experimental.
 If you want to switch to a completely different wallet, at a completely
 different path, then call this function.
  
 OT_API_SwitchWallet("/absolute-path-goes-here/Open-Transactions/testwallet/data_folder",
                     "wallet.xml");
 
 */
int OT_API_SwitchWallet(const char * szDataFolderPath, const char * szWalletFilename); // actually returns OT_BOOL


// ----------------------------------------------------
// The below functions are for retrieving log data programatically.

int OT_API_GetMemlogSize();

const char * OT_API_GetMemlogAtIndex(int nIndex);

const char * OT_API_PeekMemlogFront();
const char * OT_API_PeekMemlogBack();

int OT_API_PopMemlogFront(); // actually returns OT_BOOL
int OT_API_PopMemlogBack(); // actually returns OT_BOOL



// --------------------------------------------------
/// CREATE NYM  -- Create new User
///
/// Creates a new Nym and adds it to the wallet.
/// (Including PUBLIC and PRIVATE KEYS.)
///
/// Returns a new User ID (with files already created)
/// or NULL upon failure.
///
/// Once it exists, use OT_API_createUserAccount() to
/// register your new Nym at any given Server. (Nearly all
/// server requests require this...)
///
const char * OT_API_CreateNym(void);



// --------------------------------------------------
/// ADD SERVER CONTRACT
/// If you have a server contract that you'd like to add 
/// to your wallet, call this function.
///
int OT_API_AddServerContract(const char * szContract); // returns OT_TRUE (1) or OT_FALSE(0)




// --------------------------------------------------
/// ADD ASSET CONTRACT
/// If you have an asset contract that you'd like to add 
/// to your wallet, call this function.
///
int OT_API_AddAssetContract(const char * szContract); // returns OT_TRUE (1) or OT_FALSE(0)


	
// --------------------------------------------------

/// NOTE:  THE BELOW FUNCTIONS *DO NOT* SEND ANY MESSAGE TO THE SERVER,
///        BUT RATHER, THEY ONLY QUERY FOR DATA FROM LOCAL STORAGE.
///
/// Often a server response will cause a change to the data in local storage.
/// These functions allow you to re-load that data so your GUI can reflect
/// the updates to those files.
///
int OT_API_GetServerCount(void);
int OT_API_GetAssetTypeCount(void);
int OT_API_GetAccountCount(void);
int OT_API_GetNymCount(void);



const char * OT_API_GetServer_ID(int nIndex); // based on Index (above 4 functions) this returns the Server's ID
const char * OT_API_GetServer_Name(const char * SERVER_ID); // Return's Server's name (based on server ID)




const char * OT_API_GetAssetType_ID(int nIndex); // returns Asset Type ID (based on index from GetAssetTypeCount)
const char * OT_API_GetAssetType_Name(const char * ASSET_TYPE_ID); // Returns asset type name based on Asset Type ID



/// You already have accounts in your wallet (without any server communications)
/// and these functions allow you to query the data members of those accounts.
/// Thus, "AccountWallet" denotes that you are examining copies of your accounts that
/// are sitting in your wallet. Originally the purpose was to eliminate confusion with
/// a different set of similarly-named functions.
const char * OT_API_GetAccountWallet_ID(int nIndex);	 // returns a string containing the account ID, based on index.
const char * OT_API_GetAccountWallet_Name(const char * ACCOUNT_ID);	 // returns the account name, based on account ID.
const char * OT_API_GetAccountWallet_Balance(const char * ACCOUNT_ID);	 // returns the account balance, based on account ID.
const char * OT_API_GetAccountWallet_Type(const char * ACCOUNT_ID);	 // returns the account type (simple, issuer, etc)
const char * OT_API_GetAccountWallet_AssetTypeID(const char * ACCOUNT_ID);	 // returns asset type ID of the account
const char * OT_API_GetAccountWallet_ServerID(const char * ACCOUNT_ID);	 // returns Server ID of the account
const char * OT_API_GetAccountWallet_NymID(const char * ACCOUNT_ID);	 // returns Nym ID of the account

/// Returns OT_BOOL. Verifies any asset account (intermediary files) against its own last signed receipt.
/// Obviously this will fail for any new account that hasn't done any transactions yet, and thus has no receipts.
int OT_API_VerifyAccountReceipt(const char * SERVER_ID, const char * NYM_ID, const char * ACCT_ID);


//----------------------------------------------------------
/// GET NYM TRANSACTION NUM COUNT
/// How many transaction numbers does the Nym have (for a given server?)
///
/// This function returns the count of numbers available. If 0, then no
/// transactions will work until you call OT_API_getTransactionNumber()
/// to replenish your Nym's supply for that ServerID...
///
/// Returns a count (0 through N numbers available), 
/// or -1 for error (no nym found.)
///
int OT_API_GetNym_TransactionNumCount(const char * SERVER_ID, const char * NYM_ID);

const char * OT_API_GetNym_ID(int nIndex); /// based on Index (above 4 functions) this returns the Nym's ID
const char * OT_API_GetNym_Name(const char * NYM_ID); /// Returns Nym Name (based on NymID)
const char * OT_API_GetNym_Stats(const char * NYM_ID); /// Returns Nym Statistics (based on NymID)

int OT_API_IsNym_RegisteredAtServer(const char * NYM_ID, const char * SERVER_ID); // actually returns OT_BOOL


/// Each Nym has mail messages, they can come from different servers.
/// This allows you to peruse the mail for a given Nym, and erase messages.
///
/***
 
 So how would you actually USE this to browse a Nym's mail?
 
 -- Call OT_API_GetNym_MailCount() to find out how many mail items there are.
 
 -- Then LOOP through them, and use OT_API_GetNym_MailSenderIDByIndex and
    OT_API_GetNym_MailServerIDByIndex to populate the list.
 
 -- If you want to add a subject display, you'll have to call OT_API_GetNym_MailContentsByIndex()
    and check for a first line beginning in Subject:  (there may not be one.)
 
 -- OT_API_GetNym_MailContentsByIndex returns the body of the mail regardless.
 
 -- Use OT_API_Nym_VerifyMailByIndex() to verify the signature on the mail,
 
 -- and use OT_API_Nym_RemoveMailByIndex() to erase mail (when you want to.)
 
 */

int				OT_API_GetNym_MailCount(const char * NYM_ID);

const char *	OT_API_GetNym_MailContentsByIndex(const char * NYM_ID, int nIndex); /// returns the message itself (Subject: optionally as first line)

const char *	OT_API_GetNym_MailSenderIDByIndex(const char * NYM_ID, int nIndex); /// returns the NymID of the sender.
const char *	OT_API_GetNym_MailServerIDByIndex(const char * NYM_ID, int nIndex); /// returns the ServerID where the message came from.

int				OT_API_Nym_RemoveMailByIndex(const char * NYM_ID, int nIndex); /// actually returns OT_BOOL, (1 or 0.)
int				OT_API_Nym_VerifyMailByIndex(const char * NYM_ID, int nIndex); /// actually returns OT_BOOL. OT_TRUE if signature verifies. (Sender Nym MUST be in my wallet for this to work.)

// ---------------------------------------------------------

int				OT_API_GetNym_OutmailCount(const char * NYM_ID);

const char *	OT_API_GetNym_OutmailContentsByIndex(const char * NYM_ID, int nIndex); /// returns the message itself (Subject: optionally as first line)

const char *	OT_API_GetNym_OutmailRecipientIDByIndex(const char * NYM_ID, int nIndex); /// returns the NymID of the recipient.
const char *	OT_API_GetNym_OutmailServerIDByIndex(const char * NYM_ID, int nIndex); /// returns the ServerID where the message came from.

int				OT_API_Nym_RemoveOutmailByIndex(const char * NYM_ID, int nIndex); /// actually returns OT_BOOL, (1 or 0.)
int				OT_API_Nym_VerifyOutmailByIndex(const char * NYM_ID, int nIndex); /// actually returns OT_BOOL. OT_TRUE if signature verifies. (Sender Nym MUST be in my wallet for this to work.)

// ---------------------------------------------------------

/// *** FUNCTIONS FOR REMOVING VARIOUS CONTRACTS AND NYMS FROM THE WALLET ***

/// Can I remove this server contract from my wallet?
///
/// You cannot remove the server contract from your wallet if there are accounts in there using it.
/// This function tells you whether you can remove the server contract or not. (Whether there are accounts...)
/// returns OT_BOOL
///
int		OT_API_Wallet_CanRemoveServer(const char * SERVER_ID);

/// Remove this server contract from my wallet!
///
/// Try to remove the server contract from the wallet.
/// This will not work if there are any accounts in the wallet for the same server ID.
/// returns OT_BOOL
///
int		OT_API_Wallet_RemoveServer(const char * SERVER_ID);



/// Can I remove this asset contract from my wallet?
///
/// You cannot remove the asset contract from your wallet if there are accounts in there using it.
/// This function tells you whether you can remove the asset contract or not. (Whether there are accounts...)
/// returns OT_BOOL
///
int		OT_API_Wallet_CanRemoveAssetType(const char * ASSET_ID);


/// Remove this asset contract from my wallet!
///
/// Try to remove the asset contract from the wallet.
/// This will not work if there are any accounts in the wallet for the same asset type ID.
/// returns OT_BOOL
///
int		OT_API_Wallet_RemoveAssetType(const char * ASSET_ID);



/// Can I remove this Nym from my wallet?
///
/// You cannot remove the Nym from your wallet if there are accounts in there using it.
/// This function tells you whether you can remove the Nym or not. (Whether there are accounts...)
/// returns OT_BOOL
///
int		OT_API_Wallet_CanRemoveNym(const char * NYM_ID);


/// Remove this Nym from my wallet!
///
/// Try to remove the Nym from the wallet.
/// This will not work if there are any nyms in the wallet for the same server ID.
/// returns OT_BOOL
///
int		OT_API_Wallet_RemoveNym(const char * NYM_ID);



/// Can I remove this Account from my wallet?
///
/// You cannot remove the Account from your wallet if there are transactions still open.
/// This function tells you whether you can remove the Account or not. (Whether there are transactions...)
/// returns OT_BOOL
///
int		OT_API_Wallet_CanRemoveAccount(const char * ACCOUNT_ID);


/// Remove this Account from my wallet!
///
/// Try to remove the Account from the wallet.
/// This will not work if there are any transactions open for this account.
/// returns OT_BOOL
///
int		OT_API_Wallet_RemoveAccount(const char * ACCOUNT_ID);




const char * OT_API_Wallet_ImportNym(const char * DISPLAY_NAME, const char * KEY_FILE_CONTENTS);





// -----------------------------------
/// SET NYM NAME
///
/// You might have 40 of your friends' public nyms in
/// your wallet. You might have labels on each of them.
/// But whenever you change a label (and thus re-sign the
/// file for that Nym when you save it), you only SIGN
/// using one of your OWN nyms, for which you have a private
/// key available for signing.
///
/// Signer Nym?
/// When testing, there is only one nym, so you just pass it
/// twice.  But in real production, a user will have a default
/// signing nym, the same way that he might have a default 
/// signing key in PGP, and that must be passed in whenever
/// he changes the name on any of the other nyms in his wallet.
/// (In order to properly sign and save the change.)
///
/// Returns OT_TRUE (1) or OT_FALSE (0)
///
int OT_API_SetNym_Name(const char * NYM_ID, 
					   const char * SIGNER_NYM_ID, 
					   const char * NYM_NEW_NAME); // actually returns OT_BOOL.

/// Returns OT_TRUE (1) or OT_FALSE (0)
/// The asset account's name is merely a client-side label.
int OT_API_SetAccountWallet_Name(const char * ACCT_ID, 
								 const char * SIGNER_NYM_ID, 
								 const char * ACCT_NEW_NAME);
/// actually returns OT_BOOL.
int OT_API_SetAssetType_Name(const char * ASSET_ID, 
							 const char * STR_NEW_NAME);
/// actually returns OT_BOOL.
int OT_API_SetServer_Name(const char * SERVER_ID, 
						  const char * STR_NEW_NAME); 


/// (Above) IMPORTANT: USE the above functions for setting the CLIENT-SIDE
/// display labels that you use in your UI for the Nyms/Servers/AssetTypes/Accounts.
/// These labels are stored SEPARATELY from their own files, in the wallet file.
///
/// If you just added the contract, it will SET the label for you based on the contract type.
/// like if it's an asset contract, it uses the currency name field from the asset contract.
/// If it's a server contract it uses the entity short name. After that, it's 
/// configurable for the user, and stays on client side, and persists via wallet.
///
/// EVEN WHEN OT has to re-download one of those files, it will make sure to save
/// the display label properly in the wallet.
///
/// THIS MEANS *you*, as a client developer:
/// 1) CAN DEPEND on these labels to have the right value.
/// 2) Can expect them to start out with good default values.
/// 3) Can configure them from there.
/// 4) SHOULD DISPLAY THEM as appropriate in your application.
/// 5) Of course, use the ID behind the scenes for making all your
///    OT calls... just use the name for display purposes.
///



// --------------------------------------------------
/// Verify and Retrieve XML Contents.
///
/// Pass in a contract and a user ID, and this function will:
/// -- Load the contract up and verify it. (Most classes in OT
///    are derived in some way from OTContract.)
/// -- Verify the user's signature on it.
/// -- Remove the PGP-style bookends (the signatures, etc)
///    and return the XML contents of the contract in string form. <==
///
const char * OT_API_VerifyAndRetrieveXMLContents(const char * THE_CONTRACT,
												 const char * USER_ID);




// ----------------------------------------------------------------------
/**
 
 WRITE A CHEQUE  --- (Returns the cheque in string form.)
 
 ==> OT_API_WriteCheque() internally constructs an OTCheque 
 and issues it, like so:
 
 OTCheque theCheque( SERVER_ID, ASSET_TYPE_ID );
 
 theCheque.IssueCheque( AMOUNT // The amount of the cheque, in string form, which OTAPI
                               // will convert to a long integer. Negative amounts        
                               // allowed, since that is how OT implements invoices.
                               // (An invoice is just a cheque with a negative amount.)
 
 lTransactionNumber,   // The API will supply this automatically, as long as
                       // there are some transaction numbers in the wallet. (Call
                       // OT_API_getTransactionNumber() if your wallet needs more.)
 
 VALID_FROM, VALID_TO, // Valid date range (in seconds since Jan 1970...)
 
 ACCOUNT_ID, USER_ID,  // User ID and Acct ID for SENDER.
 
 CHEQUE_MEMO,  // The memo for the cheque. (Can be empty or be NULL.)
 
 RECIPIENT_USER_ID); // Recipient User ID is optional. (You can use an
                     // empty string here, to write a blank cheque, or pass NULL.)
 */
const char * OT_API_WriteCheque(const char * SERVER_ID,
								const char * CHEQUE_AMOUNT, 
								const char * VALID_FROM, 
								const char * VALID_TO,
								const char * SENDER_ACCT_ID,
								const char * SENDER_USER_ID,
								const char * CHEQUE_MEMO, 
								const char * RECIPIENT_USER_ID);




// ----------------------------------------------------------------------

/**
 
 WRITE A PAYMENT PLAN  --- (Returns the payment plan in string form.)
 

 PARAMETER NOTES:
 -- Payment Plan Delay, and Payment Plan Period, both default to 30 days (if you pass 0.)

 -- Payment Plan Length, and Payment Plan Max Payments, both default to 0, which means
    no maximum length and no maximum number of payments.

 -----------------------------------------------------------------
 FYI, the payment plan creation process (currently) is:

 1) Payment Plan is written by the sender (this function.)
 2) This is necessary because the transaction number must be on
    the sender's nym when he submits it to the server.
 3) Also, the sender must be the one to submit it.
 4) Recipient must sign it beforehand, so it must be sent to
    recipient and then sent BACK to sender for submittal.
 
 THAT SUCKS!   Here's what it should do:
 
 1) Payment plan is written, and signed, by the recipient. 
 2) He sends it to the sender, who signs it and submits it.
 3) The server loads the recipient nym to verify the transaction
    number. The sender also had to burn a transaction number (to
    submit it) so now, both have verified trns#s in this way.

 ==> Unfortunately, the current OT behavior is described by the first
 process above, not the second one. However, I think the API will be
 the same either way -- just need to change the server to support
 EITHER sender OR recipient being able to submit (it should simply
 check BOTH of them for the transaction number instead of sender only.) 
 We'll get there eventually...

 ----------------------------------

 FYI, here are all the OT library calls that are performed by this single API call:

OTPaymentPlan * pPlan = new OTPaymentPlan(pAccount->GetRealServerID(), 
										  pAccount->GetAssetTypeID(),
										  pAccount->GetRealAccountID(),	pAccount->GetUserID(),
										  RECIPIENT_ACCT_ID, RECIPIENT_USER_ID);

 From OTAgreement:  (This must be called first, before the other two methods below can be called.)	

	bool		OTAgreement::SetAgreement(	const long & lTransactionNum,	const OTString & strConsideration,
											const time_t & VALID_FROM=0,	const time_t & VALID_TO=0);

 (Optional initial payment):
bool		OTPaymentPlan::SetInitialPayment(const long & lAmount, time_t tTimeUntilInitialPayment=0); // default: now.

		These two (above and below) can be called independent of each other. You can 
		have an initial payment, AND/OR a payment plan.

 (Optional regular payments):
bool		OTPaymentPlan::SetPaymentPlan(const long & lPaymentAmount, 
						   time_t tTimeUntilPlanStart=LENGTH_OF_MONTH_IN_SECONDS, // Default: 1st payment in 30 days
						   time_t tBetweenPayments=LENGTH_OF_MONTH_IN_SECONDS, // Default: 30 days.
						   time_t tPlanLength=0, int nMaxPayments=0);
*/
const char * OT_API_WritePaymentPlan(const char * SERVER_ID,
									 // ----------------------------------------
									 const char * VALID_FROM,	// Default (0 or NULL) == NOW
									 const char * VALID_TO,		// Default (0 or NULL) == no expiry / cancel anytime
									 // ----------------------------------------
									 const char * SENDER_ACCT_ID,	// Mandatory parameters.
									 const char * SENDER_USER_ID,	// Both sender and recipient must sign before submitting.
									 // ----------------------------------------
									 const char * PLAN_CONSIDERATION,	// Like a memo.
									 // ----------------------------------------
									 const char * RECIPIENT_ACCT_ID,	// NOT optional.
									 const char * RECIPIENT_USER_ID,	// Both sender and recipient must sign before submitting.
									 // -------------------------------	
									 const char * INITIAL_PAYMENT_AMOUNT,	// zero or NULL == no initial payment.
									 const char * INITIAL_PAYMENT_DELAY,	// seconds from creation date. Default is zero or NULL.
									 // ---------------------------------------- .
									 const char * PAYMENT_PLAN_AMOUNT,		// zero or NULL == no regular payments.
									 const char * PAYMENT_PLAN_DELAY,		// No. of seconds from creation date. Default is zero or NULL.
									 const char * PAYMENT_PLAN_PERIOD,		// No. of seconds between payments. Default is zero or NULL.
									 // --------------------------------------- 
									 const char * PAYMENT_PLAN_LENGTH,		// In seconds. Defaults to 0 or NULL (no maximum length.)
									 const char * PAYMENT_PLAN_MAX_PAYMENTS	// Integer. Defaults to 0 or NULL (no maximum payments.)
									 );									





// -----------------------------------------------------------------
/// LOAD USER PUBLIC KEY  -- from local storage
///
/// (returns as STRING)
///
/// MEANT TO BE USED in cases where a private key is also available.
///
const char * OT_API_LoadUserPubkey(const char * USER_ID); // returns NULL, or a public key.



// -----------------------------------------------------------------
/// LOAD PUBLIC KEY  -- from local storage
///
/// (returns as STRING)
///
/// MEANT TO BE USED in cases where a private key is NOT available.
///
const char * OT_API_LoadPubkey(const char * USER_ID); // returns NULL, or a public key.






// ------------------------------------------------------------------------
///
/// Verify that USER_ID (including its Private Key) is an 
/// available and verified user in local storage.
///
/// Loads the user's private key, verifies, then returns OT_TRUE or OT_FALSE.
///
int OT_API_VerifyUserPrivateKey(const char * USER_ID); // returns OT_BOOL








// --------------------------------------------------------------
/// LOAD PURSE or MINT or ASSET CONTRACT or SERVER CONTRACT -- (from local storage)
///
/// Based on Asset Type ID: load a purse, a public mint, or an asset/server contract
/// and return it as a string -- or return NULL if it wasn't found.
///
const char * OT_API_LoadPurse(const char * SERVER_ID,
							  const char * ASSET_TYPE_ID,
							  const char * USER_ID); // returns NULL, or a purse.

const char * OT_API_LoadMint(const char * SERVER_ID,
							 const char * ASSET_TYPE_ID); // returns NULL, or a mint

const char * OT_API_LoadAssetContract(const char * ASSET_TYPE_ID); // returns NULL, or an asset contract.

const char * OT_API_LoadServerContract(const char * SERVER_ID); // returns NULL, or a server contract.










// --------------------------------------------------------------
/// IS BASKET CURRENCY ?
///
/// Tells you whether or not a given asset type is actually a basket currency.
///
int OT_API_IsBasketCurrency(const char * ASSET_TYPE_ID); // returns OT_BOOL (OT_TRUE or OT_FALSE aka 1 or 0.)


// --------------------------------------------------------------------
/// Get Basket Count (of backing asset types.)
///
/// Returns the number of asset types that make up this basket.
/// (Or zero.)
///
int OT_API_Basket_GetMemberCount(const char * BASKET_ASSET_TYPE_ID);


// --------------------------------------------------------------------
/// Get Asset Type of a basket's member currency, by index.
///
/// (Returns a string containing Asset Type ID, or NULL).
///
const char * OT_API_Basket_GetMemberType(const char * BASKET_ASSET_TYPE_ID,
										 const int nIndex);

// ----------------------------------------------------
/// GET BASKET MINIMUM TRANSFER AMOUNT
///
/// Returns a long (as string) containing the minimum transfer
/// amount for the entire basket.
///
/// FOR EXAMPLE: 
/// If the basket is defined as 10 Rands == 2 Silver, 5 Gold, 8 Euro,
/// then the minimum transfer amount for the basket is 10. This function
/// would return a string containing "10", in that example.
///
const char * OT_API_Basket_GetMinimumTransferAmount(const char * BASKET_ASSET_TYPE_ID);



// ----------------------------------------------------
/// GET BASKET MEMBER's MINIMUM TRANSFER AMOUNT
///
/// Returns a long (as string) containing the minimum transfer
/// amount for one of the member currencies in the basket.
///
/// FOR EXAMPLE: 
/// If the basket is defined as 10 Rands == 2 Silver, 5 Gold, 8 Euro,
/// then the minimum transfer amount for the member currency at index
/// 0 is 2, the minimum transfer amount for the member currency at
/// index 1 is 5, and the minimum transfer amount for the member 
/// currency at index 2 is 8.
///
const char * OT_API_Basket_GetMemberMinimumTransferAmount(const char * BASKET_ASSET_TYPE_ID,
														  const int nIndex);













// --------------------------------------------------------------
/// LOAD ACCOUNT / INBOX / OUTBOX   --  (from local storage)
///
/// Loads an acct, or inbox or outbox, based on account ID, (from local storage)
/// and returns it as string (or returns NULL if it couldn't load it.)
///
const char * OT_API_LoadAssetAccount(const char * SERVER_ID,
									 const char * USER_ID,
									 const char * ACCOUNT_ID); // Returns NULL, or an account.
const char * OT_API_LoadInbox(const char * SERVER_ID,
							  const char * USER_ID,
							  const char * ACCOUNT_ID); // Returns NULL, or an inbox.
const char * OT_API_LoadOutbox(const char * SERVER_ID,
							   const char * USER_ID,
							   const char * ACCOUNT_ID); // returns NULL, or an outbox.





// --------------------------------------------------------------
// Find out how many pending transactions (and receipts) are in this inbox.
int OT_API_Ledger_GetCount(const char * SERVER_ID,
						   const char * USER_ID,
						   const char * ACCOUNT_ID,
						   const char * THE_LEDGER); // Returns number of transactions within.



// -----------------------------------------------------------------------
/// Creates a new 'response' ledger, set up with the right Server ID, etc, so you can
/// add the 'response' transactions to it, one by one. (Pass in the original ledger  
/// that you are responding to, as it uses the data from it to set up the response.)
///
const char * OT_API_Ledger_CreateResponse(const char * SERVER_ID,
										  const char * USER_ID,
										  const char * ACCOUNT_ID,
										  const char * ORIGINAL_LEDGER); 


// -------------------------------------------------------------------------
/// Lookup a transaction or its ID (from within a ledger) based on index or
/// transaction number.
//
const char * OT_API_Ledger_GetTransactionByIndex(const char * SERVER_ID,
												 const char * USER_ID,
												 const char * ACCOUNT_ID,
												 const char * THE_LEDGER,
												 int nIndex); // returns transaction by index.

const char * OT_API_Ledger_GetTransactionByID(const char * SERVER_ID,
											  const char * USER_ID,
											  const char * ACCOUNT_ID,
											  const char * THE_LEDGER,
											  const char * TRANSACTION_NUMBER); // returns transaction by ID.

const char * OT_API_Ledger_GetTransactionIDByIndex(const char * SERVER_ID,
												   const char * USER_ID,
												   const char * ACCOUNT_ID,
												   const char * THE_LEDGER,
												   int nIndex); // returns transaction number by index.

// --------------------------------------------------------------
/// Add a transaction to a ledger.
///
const char * OT_API_Ledger_AddTransaction(const char * SERVER_ID,
										  const char * USER_ID,
										  const char * ACCOUNT_ID,
										  const char * THE_LEDGER,
										  const char * THE_TRANSACTION);


// --------------------------------------------------------------
/// Create a 'response' transaction, that will be used to indicate my
/// acceptance or rejection of another transaction. Usually an entire
/// ledger full of these is sent to the server as I process the various
/// transactions in my inbox.
///
const char * OT_API_Transaction_CreateResponse(const char * SERVER_ID,
											   const char * USER_ID,
											   const char * ACCOUNT_ID,
											   const char * RESPONSE_LEDGER, // To be sent to the server...
											   const char * ORIGINAL_TRANSACTION, // Responding to...?
											   int BOOL_DO_I_ACCEPT);   // 1 or 0  (OT_TRUE or OT_FALSE.)




/// -------------------------------------------------------------------------
/// (Response Ledger) LEDGER FINALIZE RESPONSE
///
/// AFTER you have set up all the transaction responses, call THIS function
/// to finalize them by adding a BALANCE AGREEMENT.
///
/// MAKE SURE you have the latest copy of the account file, inbox file, and
/// outbox file, since we will need those in here to create the balance statement
/// properly.
///
/// (Client software may wish to check those things, when downloaded, against
/// the local copies and the local signed receipts. In this way, clients can
/// protect themselves against malicious servers.)
///
const char * OT_API_Ledger_FinalizeResponse(const char * SERVER_ID,
											const char * USER_ID,
											const char * ACCOUNT_ID,
											const char * THE_LEDGER); // 'Response' ledger be sent to the server...
										


// --------------------------------------------------------------------
/// Get Transaction Type  (internally uses GetTransactionTypeString().)
//
const char * OT_API_Transaction_GetType(const char * SERVER_ID,
										const char * USER_ID,
										const char * ACCOUNT_ID,
										const char * THE_TRANSACTION);



// --------------------------------------------------------------------
/// Retrieve Voucher from Transaction
///
/// If you withdrew into a voucher instead of cash, this function allows
/// you to retrieve the actual voucher cheque from the reply transaction.
/// (A voucher is a cheque drawn on an internal server account instead
/// of a user's asset account, so the voucher cannot ever bounce due to 
/// insufficient funds. We are accustomed to this functionality already
/// in our daily lives, via "money orders" and "cashier's cheques".)
///
/// How would you use this in full?
///
/// First, call OT_API_withdrawVoucher() in order to send the request
/// to the server. (You may optionally call OT_API_FlushMessageBuffer()
/// before doing this.)
///
/// Then, call OT_API_PopMessageBuffer() to retrieve any server reply.
///
/// If there is a message from the server in reply, then call 
/// OT_API_Message_GetCommand to verify that it's a reply to the message
/// that you sent, and call OT_API_Message_GetSuccess to verify whether
/// the message was a success.
///
/// If it was a success, next call OT_API_Message_GetLedger to retrieve
/// the actual "reply ledger" from the server.
///
/// Penultimately, call OT_API_Ledger_GetTransactionByID() and then,
/// finally, call OT_API_Transaction_GetVoucher() (below) in order to
/// retrieve the voucher cheque itself from the transaction.
///
const char * OT_API_Transaction_GetVoucher(const char * SERVER_ID,
										   const char * USER_ID,
										   const char * ACCOUNT_ID,
										   const char * THE_TRANSACTION);



// --------------------------------------------------
///
/// Get Transaction Success   OT_TRUE  (1) == acknowledgment
///                           OT_FALSE (0) == rejection 
/// Returns OT_BOOL.
///
int OT_API_Transaction_GetSuccess(const char * SERVER_ID,
								  const char * USER_ID,
								  const char * ACCOUNT_ID,
								  const char * THE_TRANSACTION); 


/// --------------------------------------------------
///
/// Get Transaction Date Signed  (internally uses OTTransaction::GetDateSigned().)
///
const char * OT_API_Transaction_GetDateSigned(const char * SERVER_ID,
											  const char * USER_ID,
											  const char * ACCOUNT_ID,
											  const char * THE_TRANSACTION); 

const char * OT_API_Transaction_GetAmount(const char * SERVER_ID,
										  const char * USER_ID,
										  const char * ACCOUNT_ID,
										  const char * THE_TRANSACTION);


// --------------------------------------------------
///
/// PENDING TRANSFER (various functions)
///
/// When someone has sent you a PENDING TRANSFER (a form of transaction
/// that will be sitting in your inbox waiting for you to accept/reject it)
/// then, as you are reading the inbox, you can use these functions in
/// order to get data from each pending transfer. That way your user can
/// then decide whether to accept or reject it (see the ledger functions.)
///

const char * OT_API_Pending_GetNote(const char * SERVER_ID,
									const char * USER_ID,
									const char * ACCOUNT_ID,
									const char * THE_TRANSACTION);


// ----------

const char * OT_API_Transaction_GetSenderUserID(const char * SERVER_ID,
												const char * USER_ID,
												const char * ACCOUNT_ID,
												const char * THE_TRANSACTION);

const char * OT_API_Transaction_GetSenderAcctID(const char * SERVER_ID,
												const char * USER_ID,
												const char * ACCOUNT_ID,
												const char * THE_TRANSACTION);

const char * OT_API_Transaction_GetRecipientUserID(const char * SERVER_ID,
												   const char * USER_ID,
												   const char * ACCOUNT_ID,
												   const char * THE_TRANSACTION);

const char * OT_API_Transaction_GetRecipientAcctID(const char * SERVER_ID,
												   const char * USER_ID,
												   const char * ACCOUNT_ID,
												   const char * THE_TRANSACTION);


/// The pending notice in the inbox has a transaction number that
/// was issued to the server (so it could put the notice in your inbox.)
/// But it's IN REFERENCE TO a transfer that was initiated by another
/// user. THIS function will retrieve THAT transaction number, because
/// this function queries a pending transaction to see what transaction
/// it is "in reference to."
///
const char * OT_API_Transaction_GetDisplayReferenceToNum(const char * SERVER_ID,
														 const char * USER_ID,
														 const char * ACCOUNT_ID,
														 const char * THE_TRANSACTION);



// ---------------------------------------------------------



/*
 const char * OT_API_LoadPurse(	const char * SERVER_ID,
								const char * ASSET_TYPE_ID,
								const char * USER_ID); // returns NULL, or a purse. 
 */

/// This should, if USER_ID is NULL, create a Nym to encrypt the tokens to, and just attach 
/// it (the dummy nym) as a parameter on the purse, along with its ID.
/// Otherwise use the User ID that's there.
///
const char * OT_API_CreatePurse(const char * SERVER_ID,
								const char * ASSET_TYPE_ID,
								const char * USER_ID); // returns NULL, or a purse. UserID optional.

/// Warning! This will overwrite whatever purse is there.
/// The proper way to use this function is, LOAD the purse,
/// then IMPORT whatever other purse you want into it, then
/// SAVE it again.
int OT_API_SavePurse(const char * SERVER_ID,
					 const char * ASSET_TYPE_ID,
					 const char * USER_ID,
					 const char * THE_PURSE); // returns OT_BOOL

// --------------------------------------------------------------------
/// Get Purse Total Value  (internally uses GetTotalValue().)
///
/// Returns the purported sum of all the tokens within.
///
const char * OT_API_Purse_GetTotalValue(const char * SERVER_ID,
										const char * ASSET_TYPE_ID,
										const char * THE_PURSE);

// ---

int OT_API_Purse_Count(const char * SERVER_ID,
					   const char * ASSET_TYPE_ID,
					   const char * THE_PURSE);

/// Returns the TOKEN on top of the stock (LEAVING it on top of the stack,
/// but giving you a string copy of it.)
/// returns NULL if failure.
///
const char * OT_API_Purse_Peek(const char * SERVER_ID,
							   const char * ASSET_TYPE_ID,
							   const char * USER_ID,
							   const char * THE_PURSE);

/// Removes the token from the top of the stock and DESTROYS IT,
/// and RETURNS THE UPDATED PURSE (with the token now missing from it.)
/// WARNING: Do not call this function unless you have PEEK()d FIRST!!
/// Otherwise you will lose the token and get left "holding the bag".
/// returns NULL if failure.
const char * OT_API_Purse_Pop(const char * SERVER_ID,
							  const char * ASSET_TYPE_ID,
							  const char * USER_ID,
							  const char * THE_PURSE);

/// Pushes a token onto the stack (of the purse.)
/// Returns the updated purse (now including the token.)
/// Returns NULL if failure.
const char * OT_API_Purse_Push(const char * SERVER_ID,
							   const char * ASSET_TYPE_ID,
							   const char * USER_ID,
							   const char * THE_PURSE,
							   const char * THE_TOKEN);


// ------------------


/// Returns OT_BOOL
/// Should handle duplicates. Should load, merge, and save.
int OT_API_Wallet_ImportPurse(const char * SERVER_ID,
							  const char * ASSET_TYPE_ID,
							  const char * USER_ID, // you pass in the purse you're trying to import
							  const char * THE_PURSE); // It should either have your User ID on it, or the key should be inside so you can import.
						  
/// Messages the server. If failure, make sure you didn't lose that purse!!
/// If success, the new tokens will be returned shortly and saved into the appropriate purse.
/// Note that an asset account isn't necessary to do this... just a nym operating cash-only.
/// The same as exchanging a 20-dollar bill at the teller window for a replacement bill.
///
void OT_API_exchangePurse(const char * SERVER_ID,
						  const char * ASSET_TYPE_ID,
						  const char * USER_ID,
						  const char * THE_PURSE);

// --------------

/// Tokens are stored in an encrypted state for security reasons.
/// This function is used for exporting those tokens to another Nym,
/// such as a Dummy nym, or another user's Nym.
///
const char * OT_API_Token_ChangeOwner(const char * SERVER_ID,
									  const char * ASSET_TYPE_ID,
									  const char * THE_TOKEN,
									  const char * OLD_OWNER_NYM_ID,
									  const char * NEW_OWNER_NYM_ID);

/// Returns an encrypted form of the actual blinded token ID.
/// (There's no need to decrypt the ID until redeeming the token, when
/// you re-encrypt it to the server's public key, or until spending it,
/// when you re-encrypt it to the recipient's public key, or exporting
/// it, when you create a dummy recipient and attach it to the purse.)
///
const char * OT_API_Token_GetID(const char * SERVER_ID,
								const char * ASSET_TYPE_ID,
								const char * THE_TOKEN);

/// The actual cash value of the token. Returns a long int as a string.
///
const char * OT_API_Token_GetDenomination(const char * SERVER_ID,
										  const char * ASSET_TYPE_ID,
										  const char * THE_TOKEN);

int OT_API_Token_GetSeries(const char * SERVER_ID,
						   const char * ASSET_TYPE_ID,
						   const char * THE_TOKEN);


/// the date is seconds since Jan 1970, but returned as a string.
///
const char * OT_API_Token_GetValidFrom(const char * SERVER_ID,
									   const char * ASSET_TYPE_ID,
									   const char * THE_TOKEN);

/// the date is seconds since Jan 1970, but returned as a string.
///
const char * OT_API_Token_GetValidTo(const char * SERVER_ID,
									 const char * ASSET_TYPE_ID,
									 const char * THE_TOKEN);
						  

// ---------

const char * OT_API_Token_GetAssetID(const char * THE_TOKEN);

const char * OT_API_Token_GetServerID(const char * THE_TOKEN);

						  

// --------------------------------------------------------------------




// *** MESSAGES BEING SENT TO THE SERVER -- BELOW!!! ***




/**
 CHECK SERVER ID  -- (This is used for "pinging" the server...)
 
 Notice, if you ever want to send a message, you have to include the
 Server ID and the User ID.
 
 The OTAPI will use the Server ID to look-up the server contract. (FYI,
 the Server ID is a hash of the server contract itself, so it is impos-
 sible to change the contract, without also changing the ID.)
 
 Then it will connect to the server based on the connection information
 in that contract, send the message, get the reply, and disconnect. 
 (That's in HTTP mode -- in TCP mode it maintains the connection.)
 
 It will also encrypt the message to the public key found inside that
 contract, so only the person who signed the contract will be able to
 read the message.
 
 Open Transactions will also use the User ID to lookup the public key
 for that user. (The UserID, aka NymID, is a hash of the public key
 itself.)
 
 This message is basically just a ping -- it verifies that the server
 is really there, and that it can really open the messages that are
 encrypted to the key in the server contract.  It's the first thing
 your wallet software should do. Think of it like a way to PING the
 server.
 
 */
void OT_API_checkServerID(const char * SERVER_ID, const char * USER_ID);


// --------------------------------------------------------------------
/**
 CREATE USER's ACCOUNT  (On a specific server.)
 
 Note: There are USER accounts and ASSET accounts...
 
 A User account is simply a public key. Whenever you send a message
 to the server, you would normally have to send a public key with the
 message, so that the server can encrypt the reply back to you.
 
 Due to this, the server will cache the public key so you only have
 to send the ID (which is a hash of the key.) The server uses this ID
 to look up the public key and encrypt the response back to you.
 
 -- Any user can create as many public keys as they wish. So User
	accounts are pseudonymous.
 
 -- Cash token exchanges are possible without a User account (using
	an HTTPS proxy operated by the server operator) so users are NOT
    forced to create accounts, if they prefer to deal only in cash.
    However, it's worth noting that even if they do, the cash itself
    IS STILL UNTRACEABLE, due to the Chaumian blinding.
 
 -- A user may use the same public key at multiple servers, and he
    creates his own keys inside the wallet. So this function is less
    about "creating" the user account, and more about simply register-
    ing a public key on a specific server.  
 
 -- (Wallet software is capable, in OT, of distributing assets across
	multiple servers seamlessly, which means it's a requirement that
    the user generate his own keys and register them on whichever 
    servers that he sees fit to trust.
 
 Since the server contract and public key are both presumed to have
 been created by this point, you simply pass in their IDs and the
 library will do the rest of the work.
 */
void OT_API_createUserAccount(const char * SERVER_ID,
							  const char * USER_ID);

// --------------------------------------------------------------------
/**
 CHECK USER  --- (Grab his public key based on his User ID.)
 
 ServerID -- Must be included with every message.
 USER_ID  -- You must include your own userID so the server can reply.
 USER_CHECK_ID -- This is a SECOND user's ID. 
 
 In this message, you are requesting the server to send you the
 public key for another user, denoted by his ID in USER_ID_CHECK.
 
 The server's response will contain the public key of the other
 user, so you can encrypt messages or cash to him. Your wallet can
 verify that the key is the right one, by hashing it and comparing
 the result to the other user's ID. Since the User ID is a hash of
 the key, they should always match.

 */
void OT_API_checkUser(const char * SERVER_ID,
					  const char * USER_ID,
					  const char * USER_ID_CHECK);

// --------------------------------------------------------------------
/**
 SEND USER MESSAGE --- (Send a message to another user, encrypted to his pubkey.)
 
 ServerID -- Must be included with every message.
 USER_ID  -- You must include your own userID so the server can reply.
 USER_ID_RECIPIENT -- This is a recipient user ID.
 RECIPIENT_PUBKEY -- Recipient's public key in base64-encoded form.
 THE_MESSAGE -- plaintext message you want to send. A cheque? Some cash? A note? Etc.
 
 In this message, you are requesting the server to send a message to
 another user, encrypted to his public key and dropped in his nymbox.
  
 */
void OT_API_sendUserMessage(const char * SERVER_ID,
							const char * USER_ID,
							const char * USER_ID_RECIPIENT,
							const char * RECIPIENT_PUBKEY,
							const char * THE_MESSAGE);

// --------------------------------------------------------------------
/**
 GET REQUEST NUMBER
 
 Nearly every message to the server needs to have the current "Request
 Number" attached to it. This is a number that, for each user, starts at
 0, and increments with each command.  Usually, the number simply
 increments on both sides, and there is no need to communicate it.
 
 BUT SOMETIMES the request number GOES OUT OF SYNC... When this happen,
 none of your commands will work anymore!
 
 To fix it, just call this function.

 After you call it, it will automatically synchronize your wallet with
 the request number on the server side, and your commands will start
 working again.
 
 Without understanding this simple concept, NONE of your messages will
 go through! This mechanism prevents an attack from intercepting a message
 and sending it multiple times.
 */
void OT_API_getRequest(const char * SERVER_ID,
					   const char * USER_ID);

/**
 GET TRANSACTION NUMBER
  
 Every TRANSACTION must be accompanied by a TRANSACTION NUMBER
 and you can only use a transaction number that was given to you
 previously by the server.  If you run out of transaction numbers, then
 just call the below API function to get a new one (call it a few times
 so your wallet has a few in reserve.)
  
 The server usually sends you new transaction numbers whenever you
 successfully do commands, but if you run out, you just call that function.
 
 Without understanding this, none of your transactions would ever go
 through! This mechanism is what makes it possible to prove balances
 and transactions, without having to store any account history!
 */
void OT_API_getTransactionNumber(const char * SERVER_ID,
								 const char * USER_ID);



// --------------------------------------------------------------------
/// ISSUE ASSET TYPE   --  Ask the server to issue a new asset type.
///
/// THE_CONTRACT is actually a string containing the asset contract itself.
/// (And the server will not issue the new asset type unless the key in the
/// contract matches YOUR UserID.  Only the contract signer may issue it.)
///
void OT_API_issueAssetType(const char *	SERVER_ID,
						   const char *	USER_ID,
						   const char *	THE_CONTRACT);



// --------------------------------------------------------------------
/// GET CONTRACT -- Get server's copy of any asset contract, by asset type ID.
///
void OT_API_getContract(const char * SERVER_ID,
						const char * USER_ID,
						const char * ASSET_ID);




// --------------------------------------------------------------------------
/// Get server's copy of public Mint file (which contains the public minting
/// keys for each asset type. Withdrawal requests will not work for any given
/// asset type until you have downloaded the mint for that asset type.)
///
void OT_API_getMint(const char * SERVER_ID,
					const char * USER_ID,
					const char * ASSET_ID);





// ---------------------------------------------------------------------------
/// CREATE ASSET ACCOUNT -- of any asset type, (just pass in the Asset Type ID.) 
///
void OT_API_createAssetAccount(const char * SERVER_ID,
							   const char * USER_ID,
							   const char * ASSET_ID);




// --------------------------------------------------------------------------
/// GET ACCOUNT -- Send a message to the server asking it to send you the latest
///                copy of any of your asset accounts (incl. the current balance.)
///
void OT_API_getAccount(const char * SERVER_ID,
					   const char * USER_ID,
					   const char * ACCT_ID);


// --------------------------------------------------









// ----------------------------------------------------
/// GENERATE BASKET CREATION REQUEST
///
/// (returns the basket in string form.)
///
/// Call OT_API_AddBasketCreationItem multiple times to add
/// the various currencies to the basket, and then call 
/// OT_API_issueBasket to send the request to the server.
///
const char * OT_API_GenerateBasketCreation(const char * USER_ID,
										   const char * MINIMUM_TRANSFER); // If basket is X=2,3,4, then this is X.


// ----------------------------------------------------
/// ADD BASKET CREATION ITEM
///
/// (returns the updated basket in string form.)
///
/// Call OT_API_GenerateBasketCreation first (above), then
/// call this function multiple times to add the various
/// currencies to the basket, and then call OT_API_issueBasket 
/// to send the request to the server.
///
const char * OT_API_AddBasketCreationItem(const char * USER_ID, // for signature.
										  const char * THE_BASKET, // created in above call.
										  const char * ASSET_TYPE_ID, // Adding an asset type to the new basket.
										  const char * MINIMUM_TRANSFER); // If basket is 5=X,X,X then this is an X.


// --------------------------------------------------------------------------
/// ISSUE BASKET CURRENCY
///
/// Issue a new asset type based on a BASKET of other asset types!
/// You cannot call this function until you first set up the BASKET_INFO object.
/// I will provide functions for setting up that object, so that you can then
/// call this function to actually message the server with your request.
///
/// ANYONE can issue a new basket type, but they will have no control over the
/// issuer account. Normally when issuing a currency, you therefore control the
/// issuer account. But with baskets, that is managed internally by the server.
/// This means anyone can define a basket, and all may use it -- but no one
/// controls it except the server.
///
void OT_API_issueBasket(const char * SERVER_ID,
						const char * USER_ID,
						const char * THE_BASKET);










// ----------------------------------------------------
/// GENERATE BASKET EXCHANGE REQUEST
///
/// (Returns the new basket exchange request in string form.)
///
/// Call this function first. Then call OT_API_AddBasketExchangeItem
/// multiple times, and then finally call OT_API_exchangeBasket to
/// send the request to the server.
///
const char * OT_API_GenerateBasketExchange(const char * SERVER_ID,
										   const char * USER_ID,
										   const char * BASKET_ASSET_TYPE_ID,
										   const char * BASKET_ASSET_ACCT_ID,
										   // -------------------------------------
										   const int TRANSFER_MULTIPLE);
										// 1			2			 3
										// 5=2,3,4  OR  10=4,6,8  OR 15=6,9,12 Etc. (The MULTIPLE.)


// ----------------------------------------------------
/// ADD BASKET EXCHANGE ITEM
///
/// Returns the updated basket exchange request in string form.
/// (Or NULL.)
///
/// Call the above function first. Then call this one multiple
/// times, and then finally call OT_API_exchangeBasket to send
/// the request to the server.
///
const char * OT_API_AddBasketExchangeItem(const char * SERVER_ID,
										  const char * USER_ID,
										  const char * THE_BASKET, 
										  const char * ASSET_TYPE_ID,
										  const char * ASSET_ACCT_ID);

// --------------------------------------------------------------------------
/// EXCHANGE BASKET
///
/// Send a request to the server asking to exchange in or out of a basket
/// currency.
/// 
/// For example, maybe you have 3 gold, 2 silver, and 5 dollars, and those are
/// the ingredients of the "Rand" basket currency. This message allows you to
/// ask the server to convert from your gold, silver, and dollar accounts into
/// your Rand account. (Or convert from your Rand account back into your gold,
/// silver, and dollar accounts.)
///
/// Other than this conversion process, (with the reserves stored internally by
/// the server) basket accounts are identical to normal asset accounts -- they
/// are merely another asset type ID, and you can use them the same as you would
/// use any other asset type (open accounts, write cheques, withdraw cash, trade
/// on markets, etc.)
///
void OT_API_exchangeBasket(const char * SERVER_ID,
						   const char * USER_ID,
						   const char * BASKET_ASSET_ID,
						   const char * THE_BASKET,
						   const int BOOL_EXCHANGE_IN_OR_OUT); // exchanging in == OT_TRUE, out == OT_FALSE.










// --------------------------------------------------------------------------
/// WITHDRAW CASH
///
/// User is requesting the server to withdraw AMOUNT from ACCT_ID and return
/// a purse containing cash tokens.
///
/// Cash tokens come in specific denominations, such as 10, 25, 100, etc.
/// Thus, if you want to withdraw a specific amount, such as 1291, then
/// you are not withdrawing a single token, but a purse full of them.
/// (An "OTPurse" is the object that contains a list of tokens.)
///
/// Therefore, any transactions involving cash withdrawals or deposits,
/// you are actually using an OTPurse, rather than manipulating the individual
/// tokens.
/// 
/// If Open Transactions receives a purse in reply from the server, it
/// will automatically save the tokens in that purse into your purse
/// file for that asset type. You can then reload the purse using 
/// OT_API_LoadPurse, if you want to see the updated contents.
///
void OT_API_notarizeWithdrawal(const char * SERVER_ID,
							   const char * USER_ID,
							   const char * ACCT_ID,
							   const char * AMOUNT);

// --------------------------------------------------------------------------
/// DEPOSIT CASH
///
/// Use OT_API_LoadPurse to load a purse from storage, and then use this
/// function to actually deposit that cash into a server account. (The cash
/// must, of course, be the same asset type as the account.)
///
void OT_API_notarizeDeposit(const char * SERVER_ID,
							const char * USER_ID,
							const char * ACCT_ID,
							const char * THE_PURSE);

// --------------------------------------------------------------------------
/// TRANSFER FROM ONE ASSET ACCOUNT TO ANOTHER
///
/// Send a request to the server to initiate a transfer from my account to
/// another account's inbox. (With "transfer pending" notice in my outbox).
/// Until the recipient accepts the transfer, I have the option to cancel
/// it while it is still sitting in my outbox. But once he accepts it, it 
/// cannot be reversed.
/// The server has signatures from BOTH parties requesting the transfer, and
/// each party has the signature on the other party's request. Receipts are
/// dropped into their respective inboxes.
///
void OT_API_notarizeTransfer(const char * SERVER_ID,
							 const char * USER_ID,
							 const char * ACCT_FROM,
							 const char * ACCT_TO,
							 const char * AMOUNT,
							 const char * NOTE);

// --------------------------------------------------------------------------
/// GET A COPY OF MY INBOX
///
/// Each asset account has its own inbox/outbox.
/// If a pending transfer is in my inbox, or a new receipt, I might want to see
/// that.  This message asks the server to send me the latest copy of the inbox
/// for any given account (and will save it to my local storage, so I can then
/// load it using OT_API_LoadInbox, which I haven't written yet.
/* 
 NOTE: the test client, upon receiving a @getInbox response from the server, 
 will automatically process that into a processInbox command back to the server, 
 automatically accepting all of the transactions, resulting in a final 
 @processInbox reply from the server. Obviously a real GUI client would merely 
 display the inbox to the user, where the user could choose to accept the items 
 individually.
 */
/**
 SO HOW WOULD YOU **USE** THIS?  To process your inbox...
 
 -- First you call OT_API_getInbox to grab the latest inbox from the server.
 (You will also want to call OT_API_getOutbox as well as
 OT_API_getAccount, since you need to have the latest versions of
 those files, or your balance agreement will be calculated wrong,
 causing your transaction to fail.)
 
 -- Then you call OT_API_LoadInbox to load it from local storage.
 
 During this time, your user has the opportunity to peruse the
 inbox, and to decide which transactions therein he wishes to 
 accept or reject.  If you want to display the inbox items on
 the screen, use these functions to loop through them:
 OT_API_Ledger_GetCount
 OT_API_Ledger_GetTransactionByIndex
 OT_API_Ledger_GetTransactionIDByIndex
 
 You will probably ask me for more introspection on the transactions themselves. 
 (Just ask -- No problem.)  Here's what you have right now:
 OT_API_Transaction_GetType
 
 -- Then call OT_API_Ledger_CreateResponse in order to create a
 'response' ledger for that inbox, which will be sent to the server.
 
 -- Then call OT_API_Ledger_GetCount (pass it the inbox) to find out how many 
 transactions are inside of it.  Use that count to LOOP through them...
 
 -- Use OT_API_Ledger_GetTransactionByIndex to grab each transaction as
 you iterate through the inbox.
 
 -- Call OT_API_Transaction_CreateResponse to create a response for each
 transaction, accepting or rejecting it, and adding it to the response
 ledger.
  
 -- Penultimately, call OT_API_Ledger_FinalizeResponse() which will create
 a Balance Agreement for the ledger.
 
 -- Finally, call OT_API_processInbox to send that response ledger to the
 server and process the various items.
 */

void OT_API_getInbox(const char * SERVER_ID,
					 const char * USER_ID,
					 const char * ACCT_ID);

void OT_API_getOutbox(const char * SERVER_ID,
					  const char * USER_ID,
					  const char * ACCT_ID);



/// from server (pop message buf for the response)
void OT_API_getNymbox(const char * SERVER_ID,
					 const char * USER_ID);

/// from local storage.
const char * OT_API_LoadNymbox(const char * SERVER_ID,
							   const char * USER_ID); // Returns NULL, or a Nymbox.



// --------------------------------------------------------------------------
/**
 PROCESS INBOX
 
 Assuming I have gone through the various transactions in my inbox,
 and chosen some that I wish to accept or reject, this message asks
 the server to accept or reject those transactions.
 
 You must include a copy of the ledger, which contains your accept or
 reject requests for the various inbox items. In other words, you will
 need to use some other function call first to set up that ledger with
 the various requests (accept transfer, accept receipt, etc) before you 
 can then use THIS function call to actually send those requests to
 the server. (See all the Ledger functions.)
 
 (Try the 'i' command in the test client, if you want to empty out the
 inbox and automatically accept all of the transactions within.)
 
 */
void OT_API_processInbox(const char * SERVER_ID,
						 const char * USER_ID,
						 const char * ACCT_ID,
						 const char * ACCT_LEDGER);

/// I use this automatically to save the API developers the hassle (for now)
/// added here for completeness.
void OT_API_processNymbox(const char * SERVER_ID,
						  const char * USER_ID,
						  const char * ACCT_LEDGER);


// --------------------------------------------------------------------------
/// WITHDRAW VOUCHER  --   aka CASHIER'S CHEQUE.
///
/// This is VERY similar to withdrawing cash, except the server gives you
/// a voucher instead of cash. It's the same thing as a CASHIER'S CHEQUE...
///
/// Basically the funds are moved into an internal server account, and then
/// the server gives you a cheque drawn on its own account. This way you can
/// use it like a cheque, but it will never bounce.
///
void OT_API_withdrawVoucher(const char * SERVER_ID,
							const char * USER_ID,
							const char * ACCT_ID,
							const char * RECIPIENT_USER_ID,
							const char * CHEQUE_MEMO,
							const char * AMOUNT);
// --------------------------------------------------





// --------------------------------------------------------------------------
/// DEPOSIT A CHEQUE (or VOUCHER) INTO AN ASSET ACCOUNT.
///
/// If someone gives you a cheque, you can use this function to message the
/// server asking it to deposit the cheque into one of your asset accounts.
/// (Of course the account and the cheque must be the same asset type.)
///
/// Since a voucher is simply a cheque drawn on an internal server account,
/// you can deposit a voucher the same as any other cheque.
///
void OT_API_depositCheque(const char * SERVER_ID,
						  const char * USER_ID,
						  const char * ACCT_ID,
						  const char * THE_CHEQUE);
// --------------------------------------------------





// --------------------------------------------------
/// DEPOSIT (ACTIVATE) PAYMENT PLAN
///
/// See OT_API_WritePaymentPlan as well.
///
void OT_API_depositPaymentPlan(const char * SERVER_ID,
							   const char * USER_ID,
							   const char * THE_PAYMENT_PLAN);
// --------------------------------------------------





// --------------------------------------------------
/// ISSUE MARKET OFFER
///
void OT_API_issueMarketOffer(const char * SERVER_ID,
							 const char * USER_ID,
							 // -------------------------------------------
							 const char * ASSET_TYPE_ID, // Perhaps this is the
							 const char * ASSET_ACCT_ID, // wheat market.
							 // -------------------------------------------
							 const char * CURRENCY_TYPE_ID, // Perhaps I'm buying the
							 const char * CURRENCY_ACCT_ID, // wheat with rubles.
							 // -------------------------------------------
							 const char * MARKET_SCALE,				// Defaults to minimum of 1. Market granularity.
							 const char * MINIMUM_INCREMENT,		// This will be multiplied by the Scale. Min 1.
							 const char * TOTAL_ASSETS_ON_OFFER,	// Total assets available for sale or purchase. Will be multiplied by minimum increment.
							 const char * PRICE_LIMIT,				// Per Minimum Increment...
							 int	bBuyingOrSelling); // Actually OT_BOOL. SELLING == OT_TRUE, BUYING == OT_FALSE.


// --------------------------------------------------




/*
 
 What objects are actually stored in local storage after a successful server call?
 
 A "MarketList", which contains a list of Market Datas. Load this up and you can get 
 pointers to the elements as needed. THERE IS ONLY ONE OF THESE.
 
 An "OfferList" which contains "all" offers for a specific Market ID. There may be
 many markets, so this should be saved by Server / Asset / User the same as Purses.
 If you load this object, you can loop through its offers. I don't think a sub-object
 is necessary here since the data is so simple.
 
 A "TradeList" which contains "all" trades for a specific Market ID. There many be
 many markets, so this should be saved Server/Asset/User the same as purses.
 If you load this object you can loop through the trades, which again, no sub-object
 needed since the data here is so simple. But we shall see!
 
 A "NymOfferList" which contains all offers for a specific nym. Unlike the above offers,
 these offers are full-featured and should contain a LOT more details.
 
 
 A "NymTradeList" DO THIS LAST -- I'm not sure how this will work. Perhaps the wallet
 will be responsible for taking care of this. I will figure it out along the way.
 
 */


// Retrieves details for each market.
//
void OT_API_getMarketList(const char * SERVER_ID, const char * USER_ID);

// Gets all offers for a specific market and their details (up until maximum depth)
void OT_API_getMarketOffers(const char * SERVER_ID, const char * USER_ID, 
							const char * MARKET_ID, const char * MAX_DEPTH); // Market Depth

// Gets all recent trades (up until maximum depth)
void OT_API_getMarketRecentTrades(const char * SERVER_ID, const char * USER_ID, 
								  const char * MARKET_ID, const char * MAX_DEPTH); // Market Trades

// This "Market Offer" data is a lot more detailed than the OT_API_Market_GetOffers() call, which seems similar otherwise.
void OT_API_getNym_MarketOffers(const char * SERVER_ID, const char * USER_ID); // Offers this Nym has out on market.
// These may just be the Cron Receipts...

void OT_API_cancelNymMarketOffer(const char * SERVER_ID, const char * USER_ID, const char * TRANSACTION_NUMBER);


// Trade details for all trades associated with this offer.	
//
void OT_API_getOffer_Trades(const char * SERVER_ID, const char * USER_ID, const char * TRANSACTION_NUMBER); 








// -----------------------------------------------------------
/// POP MESSAGE BUFFER
/// 
/// If there are any replies from the server, they are stored in
/// the message buffer. This function will return those messages
/// (and remove them from the list) one-by-one, newest first.
///
/// Returns the message as a string.
///
const char * OT_API_PopMessageBuffer(void);

void OT_API_FlushMessageBuffer(void);


// -----------------------------------------------------------
/// GET MESSAGE COMMAND TYPE
///
/// This way you can discover what kind of command it was.
/// All server replies are pre-pended with the @ sign. For example, if
/// you send a "getAccount" message, the server reply is "@getAccount",
/// and if you send "getMint" the reply is "@getMint", and so on.
///
const char * OT_API_Message_GetCommand(const char * THE_MESSAGE);



// -----------------------------------------------------------
/// GET MESSAGE SUCCESS (True or False)
///
/// Returns OT_TRUE (1) for Success and OT_FALSE (0) for Failure.
/// Also returns OT_FALSE for error.
///
int OT_API_Message_GetSuccess(const char * THE_MESSAGE);


// -----------------------------------------------------------
/// GET MESSAGE TRANSACTION SUCCESS (True or False)
/// 
/// Returns OT_TRUE (1) for Success and OT_FALSE (0) for Failure.
/// Also returns OT_FALSE for error.
///
int OT_API_Message_GetTransactionSuccess(const char * SERVER_ID,
										 const char * USER_ID,
										 const char * ACCOUNT_ID,
										 const char * THE_MESSAGE);



// -----------------------------------------------------------
/// GET MESSAGE LEDGER 
///
/// If you just received a server response to a transaction, and
/// you want to actually iterate through the response ledger for
/// that transaction, this function will retrieve it for you.
///
const char * OT_API_Message_GetLedger(const char * THE_MESSAGE);




// -----------------------------------------------------------
/// GET NEW ASSET TYPE ID 
///
/// If you just issued a new asset type, you'll want to read the
/// server reply and get the new asset type ID out of it.
/// Otherwise how will you ever open accounts in that new type?
///
const char * OT_API_Message_GetNewAssetTypeID(const char * THE_MESSAGE);



// -----------------------------------------------------------
/// GET NEW ISSUER ACCOUNT ID 
///
/// If you just issued a new asset type, you'll want to read the
/// server reply and get the new issuer acct ID out of it.
/// Otherwise how will you ever issue anything with it?
///
const char * OT_API_Message_GetNewIssuerAcctID(const char * THE_MESSAGE);


// -----------------------------------------------------------
/// GET NEW ACCOUNT ID 
///
/// If you just opened a new asset account, you'll want to read the
/// server reply and get the new acct ID out of it.
/// Otherwise how will you know which account you just created?
/// This function allows you to get the new account ID out of the
/// server reply message.
///
const char * OT_API_Message_GetNewAcctID(const char * THE_MESSAGE);


// ------------------------------------------------------------







// --------------------------------------------------------------------
/// CONNECT TO SERVER, and PROCESS SOCKETS
///
/// NOTE: These two functions are NOT NECESSARY in ZMQ mode!
/// They are only useful in TCP/SSL mode. --Otherwise IGNORE THEM.--
///
/// actually returns BOOL  // Not necessary in HTTP mode.
int OT_API_ConnectServer(const char * SERVER_ID, const char * USER_ID, 
						 const char * szCA_FILE, const char * szKEY_FILE, 
						 const char * szKEY_PASSWORD);
int OT_API_ProcessSockets(void);	// Not necessary in ZMQ mode.
// --------------------------------------------------------------------














// =======>

// I am actively supporting developers on the API and will be responsive...
// So feel free to ask for what you need on the API, and I'll add it for you.
//











































