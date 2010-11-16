/************************************************************************************
 *    
 *  OTAPI_funcdef.h  -- Any function defs added to the OTAPI interface go here.
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
 *       XmlRpc++       --- LGPL, Copyright (c) 2002-2003 by C. Morley
 *                          http://xmlrpcpp.sourceforge.net/
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


// DO NOT INCLUDE THIS FILE, anywhere!
// 
// (It's used internally.)
// Instead, if you want to use the functions defined here, #include "OTAPI.h" instead.
//
// (That file will include this one, but in the appropriate way.)

	


// --------------------------------------------------------------------
/*
 INITIALIZE the OTAPI
 
 Call this first, to initialize the library. It needs to know the path
 to the data_folder, which on the client side is inside the testwallet folder.
 
 Something like this:
 
 OT_BOOL bInit = OT_API_Init("/absolute-path-goes-here/Open-Transactions/testwallet/data_folder");
 
 */
int OT_API_Init(const char * szClientPath); // actually returns BOOL



// --------------------------------------------------------------------
/* 
 LOAD WALLET
 
 Next you'll want to load your wallet up. It needs to be in the data_folder.
 Just pass in the filename.  Like this:
 
 OT_API_LoadWallet("wallet.xml");
  
 */
int OT_API_LoadWallet(const char * szPath); // actually returns BOOL



// --------------------------------------------------------------------
// CONNECT TO SERVER, and PROCESS SOCKETS
//
// NOTE: These two functions are NOT NECESSARY in XmlRpc mode!
// They are only useful in TCP/SSL mode. --Otherwise IGNORE THEM.--
//
// actually returns BOOL  // Not necessary in HTTP mode.
int OT_API_ConnectServer(const char * SERVER_ID, const char * USER_ID, 
						 const char * szCA_FILE, const char * szKEY_FILE, 
						 const char * szKEY_PASSWORD);
int OT_API_ProcessSockets(void);	// Probably not necessary in HTTP mode.
// --------------------------------------------------------------------





// --------------------------------------------------

// NOTE:  THE BELOW FUNCTIONS *DO NOT* SEND ANY MESSAGE TO THE SERVER,
//        BUT RATHER, THEY ONLY QUERY FOR DATA FROM LOCAL STORAGE.
//
// Often a server response will cause a change to the data in local storage.
// These functions allow you to re-load that data so your GUI can reflect
// the updates to those files.

int OT_API_GetNymCount(void);
int OT_API_GetServerCount(void);
int OT_API_GetAssetTypeCount(void);
int OT_API_GetAccountCount(void);

const char * OT_API_GetNym_ID(int nIndex); // based on Index (above 4 functions) this returns the Nym's ID
const char * OT_API_GetNym_Name(const char * NYM_ID); // Returns Nym Name (based on NymID)

const char * OT_API_GetServer_ID(int nIndex); // based on Index (above 4 functions) this returns the Server's ID
const char * OT_API_GetServer_Name(const char * SERVER_ID); // Return's Server's name (based on server ID)

const char * OT_API_GetAssetType_ID(int nIndex); // returns Asset Type ID (based on index from GetAssetTypeCount)
const char * OT_API_GetAssetType_Name(const char * ASSET_TYPE_ID); // Returns asset type name based on Asset Type ID

// You already have accounts in your wallet (without any server communications)
// and these functions allow you to query the data members of those accounts.
//
const char * OT_API_GetAccountWallet_ID(int nIndex);	 // returns a string containing the account ID, based on index.
const char * OT_API_GetAccountWallet_Name(const char * ACCOUNT_ID);	 // returns the account name, based on account ID.
const char * OT_API_GetAccountWallet_Balance(const char * ACCOUNT_ID);	 // returns the account balance, based on account ID.
const char * OT_API_GetAccountWallet_Type(const char * ACCOUNT_ID);	 // returns the account type (simple, issuer, etc)
const char * OT_API_GetAccountWallet_AssetTypeID(const char * ACCOUNT_ID);	 // returns asset type of the account


/*
// ----------------------------------------------------------------------

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




// -----------------------------------------------------------------
// LOAD PUBLIC KEY  -- from local storage
//
// (returns as STRING)
//
const char * OT_API_LoadUserPubkey(const char * USER_ID); // returns NULL, or a public key.




// ------------------------------------------------------------------------
//
// Verify that USER_ID (including its Private Key) is an 
// available and verified user in local storage.
//
// Loads the user's private key, verifies, then returns OT_TRUE or OT_FALSE.
//
int OT_API_VerifyUserPrivateKey(const char * USER_ID); // returns OT_BOOL



// --------------------------------------------------------------
// LOAD PURSE / MINT / ASSET CONTRACT -- (from local storage)
//
// Based on Asset Type ID: load a purse, a public mint, or an asset contract
// and return it as a string -- or return NULL if it wasn't found.
//
const char * OT_API_LoadPurse(const char * SERVER_ID,
							  const char * ASSET_TYPE_ID); // returns NULL, or a purse.

const char * OT_API_LoadMint(const char * SERVER_ID,
							 const char * ASSET_TYPE_ID); // returns NULL, or a mint

const char * OT_API_LoadAssetContract(const char * ASSET_TYPE_ID); // returns NULL, or an asset contract.


// --------------------------------------------------------------
// LOAD ACCOUNT / INBOX / OUTBOX   --  (from local storage)
//
// Loads an acct, or inbox or outbox, based on account ID, (from local storage)
// and returns it as string (or returns NULL if it couldn't load it.)
//
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
/*
 SO HOW WOULD YOU **USE** THIS?  To process your inbox...
 
 -- First you call OT_API_getInbox to grab the latest inbox from the server.
 
 -- Then you call OT_API_LoadInbox to load it from local storage.
 
 (During this time, your user has the opportunity to peruse the
 inbox, and to decide which transactions therein he wishes to 
 accept or reject.)
 
 -- Then call OT_API_Ledger_CreateResponse in order to create a
 'response' ledger for that inbox, which will be send to the server.
 
 -- Then call OT_API_Ledger_GetCount (pass it the inbox) to find out how many 
 transactions are inside of it.  Use that count to LOOP through them...
 
 -- Use OT_API_Ledger_GetTransactionByIndex to grab each transaction as
 you iterate through the inbox.
 
 -- Call OT_API_Transaction_CreateResponse to create a response for each
 transaction, accepting or rejecting it, and adding it to the response
 ledger.
 
 -- Finally, call OT_API_processInbox to send that response ledger to the
 server and process the various items.
 */

int OT_API_Ledger_GetCount(const char * SERVER_ID,
						   const char * USER_ID,
						   const char * ACCOUNT_ID,
						   const char * THE_LEDGER); // Returns number of transactions within.


// -----------------------------------------------------------------------
// Creates a new 'response' ledger, set up with the right Server ID, etc, so you can
// add the 'response' transactions to it, one by one. (Pass in the original ledger  
// that you are responding to, as it uses the data from it to set up the response.)
//
const char * OT_API_Ledger_CreateResponse(const char * SERVER_ID,
										  const char * USER_ID,
										  const char * ACCOUNT_ID,
										  const char * ORIGINAL_LEDGER); 


// -------------------------------------------------------------------------
// Lookup a transaction or its ID (from within a ledger) based on index or
// transaction number.
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
// Add a transaction to a ledger.
//
const char * OT_API_Ledger_AddTransaction(const char * SERVER_ID,
										  const char * USER_ID,
										  const char * ACCOUNT_ID,
										  const char * THE_LEDGER,
										  const char * THE_TRANSACTION);


// --------------------------------------------------------------
// Create a 'response' transaction, that will be used to indicate my
// acceptance or rejection of another transaction. Usually an entire
// ledger full of these is sent to the server as I process the various
// transactions in my inbox.
//
const char * OT_API_Transaction_CreateResponse(const char * SERVER_ID,
											   const char * USER_ID,
											   const char * ACCOUNT_ID,
											   const char * RESPONSE_LEDGER, // To be sent to the server...
											   const char * ORIGINAL_TRANSACTION, // Responding to...?
											   int BOOL_DO_I_ACCEPT);   // 0 or 1  (OT_TRUE or OT_FALSE.)




// Get Transaction Type  (internally uses GetTransactionTypeString().)
const char * OT_API_Transaction_GetType(const char * SERVER_ID,
										const char * USER_ID,
										const char * ACCOUNT_ID,
										const char * THE_TRANSACTION);






// --------------------------------------------------------------------





// *** MESSAGES BEING SENT TO THE SERVER -- BELOW!!! ***




/*
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
/*
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
/*
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
/*
 - GET REQUEST NUMBER
 - GET TRANSACTION NUMBER
 
 Nearly every message to the server needs to have the current "Request
 Number" attached to it. This is a number that, for each user, starts at
 0, and increments with each command.  Usually, the number simply
 increments on both sides, and there is no need to communicate it.
 
 BUT SOMETIMES the request number GOES OUT OF SYNC... When this happen,
 none of your commands will work anymore!
 
 To fix it, just call this function:
 
 void OT_API_getRequest(const char * SERVER_ID,
                        const char * USER_ID);
 
 After you call it, it will automatically synchronize your wallet with
 the request number on the server side, and your commands will start
 working again.
 
 ----------------------------
 
 Similarly, every TRANSACTION must be accompanied by a TRANSACTION
 NUMBER, and you can only use a transaction number that was given to you
 previously by the server.  If you run out of transaction numbers, then
 just call the below API function to get a new one (call it a few times
 so your wallet has a few in reserve.)
 
 void OT_API_getTransactionNumber(const char * SERVER_ID,
                                  const char * USER_ID);
 
 The server usually sends you new transaction numbers whenever you
 successfully do commands, but if you run out, you just call that function.
 
 -----------------------------
 
 Without understanding these two functions (though they are easy)
 none of your messages or transactions will ever go through!
 */
void OT_API_getRequest(const char * SERVER_ID,
					   const char * USER_ID);

void OT_API_getTransactionNumber(const char * SERVER_ID,
								 const char * USER_ID);



// --------------------------------------------------------------------
// ISSUE ASSET TYPE   --  Ask the server to issue a new asset type.
//
// THE_CONTRACT is actually a string containing the asset contract itself.
// (And the server will not issue the new asset type unless the key in the
// contract matches YOUR UserID.  Only the contract signer may issue it.)
//
void OT_API_issueAssetType(const char *	SERVER_ID,
						   const char *	USER_ID,
						   const char *	THE_CONTRACT);



// --------------------------------------------------------------------
// GET CONTRACT -- Get server’s copy of any asset contract, by asset type ID.
//
void OT_API_getContract(const char * SERVER_ID,
						const char * USER_ID,
						const char * ASSET_ID);




// --------------------------------------------------------------------------
// Get server’s copy of public Mint file (which contains the public minting
// keys for each asset type. Withdrawal requests will not work for any given
// asset type until you have downloaded the mint for that asset type.)
//
void OT_API_getMint(const char * SERVER_ID,
					const char * USER_ID,
					const char * ASSET_ID);





// ---------------------------------------------------------------------------
// CREATE ASSET ACCOUNT -- of any asset type, (just pass in the Asset Type ID.) 
//
void OT_API_createAssetAccount(const char * SERVER_ID,
							   const char * USER_ID,
							   const char * ASSET_ID);




// --------------------------------------------------------------------------
// GET ACCOUNT -- Send a message to the server asking it to send you the latest
//                copy of any of your asset accounts (incl. the current balance.)
//
void OT_API_getAccount(const char * SERVER_ID,
					   const char * USER_ID,
					   const char * ACCT_ID);



// --------------------------------------------------------------------------
// ISSUE BASKET CURRENCY
//
// Issue a new asset type based on a BASKET of other asset types!
// You cannot call this function until you first set up the BASKET_INFO object.
// I will provide functions for setting up that object, so that you can then
// call this function to actually message the server with your request.
//
// ANYONE can issue a new basket type, but they will have no control over the
// issuer account. Normally when issuing a currency, you therefore control the
// issuer account. But with baskets, that is managed internally by the server.
// This means anyone can define a basket, and all may use it -- but no one
// controls it except the server.
//
void OT_API_issueBasket(const char * SERVER_ID,
						const char * USER_ID,
						const char * BASKET_INFO);

// --------------------------------------------------------------------------
// EXCHANGE BASKET
//
// Send a request to the server asking to exchange in or out of a basket
// currency.
// 
// For example, maybe you have 3 gold, 2 silver, and 5 dollars, and those are
// the ingredients of the "Rand" basket currency. This message allows you to
// ask the server to convert from your gold, silver, and dollar accounts into
// your Rand account. (Or convert from your Rand account back into your gold,
// silver, and dollar accounts.)
//
// Other than this conversion process, (with the reserves stored internally by
// the server) basket accounts are identical to normal asset accounts -- they
// are merely another asset type ID, and you can use them the same as you would
// use any other asset type (open accounts, write cheques, withdraw cash, trade
// on markets, etc.)
//
void OT_API_exchangeBasket(const char * SERVER_ID,
						   const char * USER_ID,
						   const char * BASKET_ASSET_ID,
						   const char * BASKET_INFO);


// --------------------------------------------------------------------------
// WITHDRAW CASH
//
// User is requesting the server to withdraw AMOUNT from ACCT_ID and return
// a purse containing cash tokens.
//
// Cash tokens come in specific denominations, such as 10, 25, 100, etc.
// Thus, if you want to withdraw a specific amount, such as 1291, then
// you are not withdrawing a single token, but a purse full of them.
// (An "OTPurse" is the object that contains a list of tokens.)
//
// Therefore, any transactions involving cash withdrawals or deposits,
// you are actually using an OTPurse, rather than manipulating the individual
// tokens.
// 
// If Open Transactions receives a purse in reply from the server, it
// will automatically save the tokens in that purse into your purse
// file for that asset type. You can then reload the purse using 
// OT_API_LoadPurse, if you want to see the updated contents.
//
void OT_API_notarizeWithdrawal(const char * SERVER_ID,
							   const char * USER_ID,
							   const char * ACCT_ID,
							   const char * AMOUNT);

// --------------------------------------------------------------------------
// DEPOSIT CASH
//
// Use OT_API_LoadPurse to load a purse from storage, and then use this
// function to actually deposit that cash into a server account. (The cash
// must, of course, be the same asset type as the account.)
//
void OT_API_notarizeDeposit(const char * SERVER_ID,
							const char * USER_ID,
							const char * ACCT_ID,
							const char * THE_PURSE);

// --------------------------------------------------------------------------
// TRANSFER FROM ONE ASSET ACCOUNT TO ANOTHER
//
// Send a request to the server to initiate a transfer from my account to
// another account’s inbox. (With "transfer pending" notice in my outbox).
// Until the recipient accepts the transfer, I have the option to cancel
// it while it is still sitting in my outbox. But once he accepts it, it 
// cannot be reversed.
// The server has signatures from BOTH parties requesting the transfer, and
// each party has the signature on the other party's request. Receipts are
// dropped into their respective inboxes.
//
void OT_API_notarizeTransfer(const char * SERVER_ID,
							 const char * USER_ID,
							 const char * ACCT_FROM,
							 const char * ACCT_TO,
							 const char * AMOUNT,
							 const char * NOTE);

// --------------------------------------------------------------------------
// GET A COPY OF MY INBOX
//
// Each asset account has its own inbox/outbox.
// If a pending transfer is in my inbox, or a new receipt, I might want to see
// that.  This message asks the server to send me the latest copy of the inbox
// for any given account (and will save it to my local storage, so I can then
// load it using OT_API_LoadInbox, which I haven't written yet.
/* 
 NOTE: the test client, upon receiving a @getInbox response from the server, 
 will automatically process that into a processInbox command back to the server, 
 automatically accepting all of the transactions, resulting in a final 
 @processInbox reply from the server. Obviously a real GUI client would merely 
 display the inbox to the user, where the user could choose to accept the items 
 individually.
 */
void OT_API_getInbox(const char * SERVER_ID,
					 const char * USER_ID,
					 const char * ACCT_ID);


// --------------------------------------------------------------------------
/*
 PROCESS INBOX
 
 Assuming I have gone through the various transactions in my inbox,
 and chosen some that I wish to accept or reject, this message asks
 the server to accept or reject those transactions.
 
 You must include a copy of the ledger, which contains your accept or
 reject requests for the various inbox items. In other words, you will
 need to use some other function call first to set up that ledger with
 the various requests (accept transfer, accept receipt, etc) before you 
 can then use THIS function call to actually send those requests to
 the server. Coming soon.
 
 (Try the 'i' command in the test client, if you want to empty out the
 inbox and automatically accept all of the transactions within.)
 
 */
void OT_API_processInbox(const char * SERVER_ID,
						 const char * USER_ID,
						 const char * ACCT_ID,
						 const char * ACCT_LEDGER);


// --------------------------------------------------------------------------
// WITHDRAW VOUCHER  --   aka CASHIER'S CHEQUE.
//
// This is VERY similar to withdrawing cash, except the server gives you
// a voucher instead of cash. It's the same thing as a CASHIER'S CHEQUE...
//
// Basically the funds are moved into an internal server account, and then
// the server gives you a cheque drawn on its own account. This way you can
// use it like a cheque, but it will never bounce.
//
void OT_API_withdrawVoucher(const char * SERVER_ID,
							const char * USER_ID,
							const char * ACCT_ID,
							const char * RECIPIENT_USER_ID,
							const char * CHEQUE_MEMO,
							const char * AMOUNT);

// --------------------------------------------------------------------------
// DEPOSIT A CHEQUE (or VOUCHER) INTO AN ASSET ACCOUNT.
//
// If someone gives you a cheque, you can use this function to message the
// server asking it to deposit the cheque into one of your asset accounts.
// (Of course the account and the cheque must be the same asset type.)
//
// Since a voucher is simply a cheque drawn on an internal server account,
// you can deposit a voucher the same as any other cheque.
//
void OT_API_depositCheque(const char * SERVER_ID,
						  const char * USER_ID,
						  const char * ACCT_ID,
						  const char * THE_CHEQUE);



// --------------------------------------------------


// COMING SOON:  The Library already supports Markets and Payment Plans 
// (And so do the Server and test client) but I haven't yet added those
// to the API. (Coming soon.)
//
// I am actively supporting developers on the API and will be responsive...
// So feel free to ask for what you need on the API, and I'll add it for you.
//









































