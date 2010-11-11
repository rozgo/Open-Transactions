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

// DO NOT include this file anywhere. It's used internally.
// Instead, include OTAPI.h if you want to use these functions.
// That file will include this one, but in the appropriate way.

	
int OT_API_Init(const char * szClientPath); // actually returns BOOL

int OT_API_loadWallet(const char * szPath); // actually returns BOOL

// actually returns BOOL  // Not necessary in HTTP mode.
int OT_API_connectServer(const char * SERVER_ID, const char * USER_ID, const char * szCA_FILE, const char * szKEY_FILE, const char * szKEY_PASSWORD);

 // actually returns BOOL
int OT_API_processSockets(void);	// Probably not necessary in HTTP mode.

void OT_API_checkServerID(const char * SERVER_ID, const char * USER_ID);

void OT_API_createUserAccount(const char * SERVER_ID,
							  const char * USER_ID);

void OT_API_checkUser(const char * SERVER_ID,
					  const char * USER_ID,
					  const char * USER_ID_CHECK);

void OT_API_getRequest(const char * SERVER_ID,
					   const char * USER_ID);

void OT_API_issueAssetType(const char *	SERVER_ID,
						   const char *	USER_ID,
						   const char *	THE_CONTRACT);

void OT_API_getContract(const char * SERVER_ID,
						const char * USER_ID,
						const char * ASSET_ID);

void OT_API_getMint(const char * SERVER_ID,
					const char * USER_ID,
					const char * ASSET_ID);

void OT_API_createAssetAccount(const char * SERVER_ID,
							   const char * USER_ID,
							   const char * ASSET_ID);

void OT_API_getAccount(const char * SERVER_ID,
					   const char * USER_ID,
					   const char * ACCT_ID);

void OT_API_issueBasket(const char * SERVER_ID,
						const char * USER_ID,
						const char * BASKET_INFO);

void OT_API_exchangeBasket(const char * SERVER_ID,
						   const char * USER_ID,
						   const char * BASKET_ASSET_ID,
						   const char * BASKET_INFO);

void OT_API_getTransactionNumber(const char * SERVER_ID,
								 const char * USER_ID);

void OT_API_notarizeWithdrawal(const char * SERVER_ID,
							   const char * USER_ID,
							   const char * ACCT_ID,
							   const char * AMOUNT);

void OT_API_notarizeDeposit(const char * SERVER_ID,
							const char * USER_ID,
							const char * ACCT_ID,
							const char * THE_PURSE);

void OT_API_notarizeTransfer(const char * SERVER_ID,
							 const char * USER_ID,
							 const char * ACCT_FROM,
							 const char * ACCT_TO,
							 const char * AMOUNT,
							 const char * NOTE);

void OT_API_getInbox(const char * SERVER_ID,
					 const char * USER_ID,
					 const char * ACCT_ID);

void OT_API_processInbox(const char * SERVER_ID,
						 const char * USER_ID,
						 const char * ACCT_ID,
						 const char * ACCT_LEDGER);

void OT_API_withdrawVoucher(const char * SERVER_ID,
							const char * USER_ID,
							const char * ACCT_ID,
							const char * RECIPIENT_USER_ID,
							const char * CHEQUE_MEMO,
							const char * AMOUNT);

void OT_API_depositCheque(const char * SERVER_ID,
						  const char * USER_ID,
						  const char * ACCT_ID,
						  const char * THE_CHEQUE);


// --------------------------------------------------

int OT_API_getNymCount(void);
int OT_API_getServerCount(void);
int OT_API_getAssetTypeCount(void);
int OT_API_getAccountCount(void);

int OT_API_getNym(int iIndex, const char * NYM_ID, const char * NYM_NAME); // actually returns BOOL
int OT_API_getServer(int iIndex, const char * THE_ID, const char * THE_NAME); // actually returns BOOL
int OT_API_getAssetType(int iIndex, const char * THE_ID, const char * THE_NAME); // actually returns BOOL

int OT_API_GetAccountWallet(int iIndex, const char * THE_ID, const char * THE_NAME);	 // actually returns BOOL	
	
	
	







