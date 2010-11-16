/************************************************************************************
 *    
 *  OpenTransactions.h   This is the header to include if you link to OTAPI.a
 *  
 *              Open Transactions:  Library, Protocol, Server, and Test Client
 *    
 *                      -- Anonymous Numbered Accounts
 *                      -- Untraceable Digital Cash
 *                      -- Triple-Signed Receipts
 *                      -- Basket Currencies
 *                      -- Signed XML Contracts
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
 *        If you would like to use this software outside of the free software
 *        license, please contact FellowTraveler. (Unfortunately many will run
 *        anonymously and untraceably, so who could really stop them?)
 *   
 *        This library is also "dual-license", meaning that Ben Laurie's license
 *        must also be included and respected, since the code for Lucre is also
 *        included with Open Transactions.
 *        The Laurie requirements are light, but if there is any problem with his
 *        license, simply remove the deposit/withdraw commands. Although there are 
 *        no other blind token algorithms in Open Transactions (yet), the other 
 *        functionality will continue to operate.
 *    
 *    OpenSSL WAIVER:
 *        This program is released under the AGPL with the additional exemption 
 *        that compiling, linking, and/or using OpenSSL is allowed.
 *    
 *    DISCLAIMER:
 *        This program is distributed in the hope that it will be useful,
 *        but WITHOUT ANY WARRANTY; without even the implied warranty of
 *        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *        GNU Affero General Public License for more details.
 *      
 ************************************************************************************/


#ifndef __OPEN_TRANSACTIONS_INTERFACE_H__
#define __OPEN_TRANSACTIONS_INTERFACE_H__

class OTString;
class OTIdentifier;
class OTServerContract;
class OTEnvelope;
class OTWallet;
class OTClient;
class OTPseudonym;
class OTAccount;
class OTAssetContract;
class OTServerContract;
class OTPurse;
class OTCheque;
class OTMint;
class OTLedger;


// This function is what makes Open Transactions go over XmlRpc/HTTP instead of TCP/SSL
// (If you compile it in rpc mode using "make rpc"
//
#if defined(OT_XMLRPC_MODE)
void OT_XmlRpcCallback(OTServerContract & theServerContract, OTEnvelope & theEnvelope);
#endif


// --------------------------------------------------------------------

class OT_API // The C++ high-level interface to the Open Transactions client-side.
{
	OTWallet *		m_pWallet;
	OTClient *		m_pClient;

	bool			m_bInitialized;
	
public:

	inline OTWallet * GetWallet() { return m_pWallet; }
	inline OTClient * GetClient() { return m_pClient; }
	
	OT_API();
	~OT_API();
	
			bool Init(OTString & strClientPath);	// Per instance.
	static	bool InitOTAPI();						// Once per run.

	bool LoadWallet(OTString & strPath);
	
	// Note: these two functions are NOT used in XmlRpc Mode
	// ONLY for SSL/TCP mode...
	bool ConnectServer(OTIdentifier & SERVER_ID,
					   OTIdentifier	& USER_ID,
					   OTString & strCA_FILE, 
					   OTString & strKEY_FILE, 
					   OTString & strKEY_PASSWORD);
	bool ProcessSockets();
	// --------------------------------------------------
	
	// Reading data about the local wallet.. presumably already loaded.
	
	int GetNymCount();
	int GetServerCount();
	int GetAssetTypeCount();
	int GetAccountCount();
	
	bool GetNym(int iIndex, OTIdentifier & NYM_ID, OTString & NYM_NAME);
	bool GetServer(int iIndex, OTIdentifier & THE_ID, OTString & THE_NAME);
	bool GetAssetType(int iIndex, OTIdentifier & THE_ID, OTString & THE_NAME);
	bool GetAccount(int iIndex, OTIdentifier & THE_ID, OTString & THE_NAME);
	
	// ----------------------------------------------------
	// In this case, the ID is input, the pointer is output.
	// Gets the data from Wallet.
	//
	OTPseudonym *		GetNym(const OTIdentifier & NYM_ID);
	OTServerContract *	GetServer(const OTIdentifier & THE_ID);
	OTAssetContract *	GetAssetType(const OTIdentifier & THE_ID);
	OTAccount *			GetAccount(const OTIdentifier & THE_ID);	
	
	// ----------------------------------------------------
	
	// Accessing local storage...
	// (Caller responsible to delete.)
	//
	OTPseudonym *		LoadPublicNym(const OTIdentifier & NYM_ID);
	OTPseudonym *		LoadPrivateNym(const OTIdentifier & NYM_ID);
	
	// ----------------------------------------------------
	//
	// Returns an OTCheque pointer, or NULL. 
	// (Caller responsible to delete.)
	OTCheque * WriteCheque(const OTIdentifier & SERVER_ID,
						   const long &			CHEQUE_AMOUNT, 
						   const time_t &		VALID_FROM, 
						   const time_t &		VALID_TO,
						   const OTIdentifier & SENDER_ACCT_ID,
						   const OTIdentifier & SENDER_USER_ID,
						   const OTString &		CHEQUE_MEMO, 
						   const OTIdentifier * pRECIPIENT_USER_ID=NULL);
	
	// ----------------------------------------------------
	
	OTPurse * LoadPurse(const OTIdentifier & SERVER_ID,
						const OTIdentifier & ASSET_ID);
	
	OTMint * LoadMint(const OTIdentifier & SERVER_ID,
					  const OTIdentifier & ASSET_ID);
	
	OTAssetContract * LoadAssetContract(const OTIdentifier & ASSET_ID);
	
	// ----------------------------------------------------

	OTAccount * LoadAssetAccount(const OTIdentifier & SERVER_ID,
								 const OTIdentifier & USER_ID,
								 const OTIdentifier & ACCOUNT_ID);
	
	OTLedger * LoadInbox(const OTIdentifier & SERVER_ID,
						 const OTIdentifier & USER_ID,
						 const OTIdentifier & ACCOUNT_ID);
	
	OTLedger * LoadOutbox(const OTIdentifier & SERVER_ID,
						  const OTIdentifier & USER_ID,
						  const OTIdentifier & ACCOUNT_ID);
	
	// ****************************************************
	
	// These commands below send messages to the server:
	
	void checkServerID(OTIdentifier & SERVER_ID,
					   OTIdentifier & USER_ID);
	
	void createUserAccount(OTIdentifier & SERVER_ID,
						   OTIdentifier & USER_ID);
	
	void checkUser(OTIdentifier & SERVER_ID,
				   OTIdentifier & USER_ID,
				   OTIdentifier & USER_ID_CHECK);
	
	void getRequest(OTIdentifier & SERVER_ID,
					OTIdentifier & USER_ID);
	
	
	void issueAssetType(OTIdentifier	&	SERVER_ID,
						OTIdentifier	&	USER_ID,
						OTString		&	THE_CONTRACT);
	
	void getContract(OTIdentifier & SERVER_ID,
					 OTIdentifier & USER_ID,
					 OTIdentifier & ASSET_ID);
	
	void getMint(OTIdentifier & SERVER_ID,
				 OTIdentifier & USER_ID,
				 OTIdentifier & ASSET_ID);
	
	void createAssetAccount(OTIdentifier & SERVER_ID,
							OTIdentifier & USER_ID,
							OTIdentifier & ASSET_ID);
	
	void getAccount(OTIdentifier & SERVER_ID,
					OTIdentifier & USER_ID,
					OTIdentifier & ACCT_ID);
	
	void issueBasket(OTIdentifier	& SERVER_ID,
					 OTIdentifier	& USER_ID,
					 OTString		& BASKET_INFO);
	
	void exchangeBasket(OTIdentifier	& SERVER_ID,
						OTIdentifier	& USER_ID,
						OTIdentifier	& BASKET_ASSET_ID,
						OTString		& BASKET_INFO);
	
	void getTransactionNumber(OTIdentifier & SERVER_ID,
							  OTIdentifier & USER_ID);
	
	void notarizeWithdrawal(OTIdentifier	& SERVER_ID,
							OTIdentifier	& USER_ID,
							OTIdentifier	& ACCT_ID,
							OTString		& AMOUNT);
	
	void notarizeDeposit(OTIdentifier	& SERVER_ID,
						 OTIdentifier	& USER_ID,
						 OTIdentifier	& ACCT_ID,
						 OTString		& THE_PURSE);
	
	void notarizeTransfer(OTIdentifier	& SERVER_ID,
						  OTIdentifier	& USER_ID,
						  OTIdentifier	& ACCT_FROM,
						  OTIdentifier	& ACCT_TO,
						  OTString		& AMOUNT,
						  OTString		& NOTE);
	
	void getInbox(OTIdentifier & SERVER_ID,
				  OTIdentifier & USER_ID,
				  OTIdentifier & ACCT_ID);
	
	void processInbox(OTIdentifier	& SERVER_ID,
					  OTIdentifier	& USER_ID,
					  OTIdentifier	& ACCT_ID,
					  OTString		& ACCT_LEDGER);
	
	void withdrawVoucher(OTIdentifier	& SERVER_ID,
						 OTIdentifier	& USER_ID,
						 OTIdentifier	& ACCT_ID,
						 OTIdentifier	& RECIPIENT_USER_ID,
						 OTString		& CHEQUE_MEMO,
						 OTString		& AMOUNT);
	
	void depositCheque(OTIdentifier	& SERVER_ID,
					   OTIdentifier	& USER_ID,
					   OTIdentifier	& ACCT_FROM_ID,
					   OTString		& THE_CHEQUE);
};
		


#endif // __OPEN_TRANSACTIONS_INTERFACE_H__
