/************************************************************************************
 *    
 *  OpenTransactions.cpp  (a high-level API)
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
 *       XmlRpc++       --- LGPL, Copyright (c) 2002-2003 by C. Morley
 *                          http://xmlrpcpp.sourceforge.net/
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


extern "C" 
{
#ifdef _WIN32
#include <WinSock.h>
#else
#include <netinet/in.h>
#endif
	
#include "SSL-Example/SFSocket.h"
}


#include "OTString.h"


#include "OTPseudonym.h"

#include "OTClient.h"
#include "OTServerConnection.h"
#include "OTServerContract.h"
#include "OTMessage.h"
#include "OTWallet.h"
#include "OTEnvelope.h"

#include "OTTransaction.h"
#include "OTMint.h"
#include "OTToken.h"
#include "OTPurse.h"
#include "OTLedger.h"
#include "OTCheque.h"
#include "OTLog.h"

#include "OpenTransactions.h"


// used for testing.
OTPseudonym *g_pTemporaryNym=NULL;


extern OT_API g_OT_API; 

// -------------------------------------------------------------------------
// When the server and client (this API being a client) are built in XmlRpc/HTTP
// mode, then a callback must be provided for passing the messages back and forth
// with the server. (Provided below.)
//
// IMPORTANT: If you ever wanted to use a different transport mechanism, it would
// be as easy as adding your own version of this callback function, but having it
// use your own transport mechanism instead of the xmlrpc in this example.
// Of course, the server would also have to support this transport layer...

#if defined(OT_XMLRPC_MODE)

// If you build in tcp/ssl mode, this file will build even if you don't have this library.
// But if you build in xml/rpc/http mode, 
#include "XmlRpc.h"  
using namespace XmlRpc;

// The Callback so OT can give us messages to send using our xmlrpc transport.
// Whenever OT needs to pop a message on over to the server, it calls this so we
// can do the work here.
//
//typedef bool (*OT_CALLBACK_MSG)(OTPayload & thePayload);
//
void OT_XmlRpcCallback(OTServerContract & theServerContract, OTEnvelope & theEnvelope)
{	
	int			nServerPort = 0;
	OTString	strServerHostname;
	
	OT_ASSERT((NULL != g_OT_API.GetClient()) && 
			  (NULL != g_OT_API.GetClient()->m_pConnection) && 
			  (NULL != g_OT_API.GetClient()->m_pConnection->GetNym()));
	
	if (false == theServerContract.GetConnectInfo(strServerHostname, nServerPort))
	{
		OTLog::Error("Failed retrieving connection info from server contract.\n");
		return;
	}
	
	OTASCIIArmor ascEnvelope(theEnvelope);
	
	if (ascEnvelope.Exists())
	{
		// Here's our connection...
#if defined (linux)
		XmlRpcClient theXmlRpcClient(strServerHostname.Get(), nServerPort, 0, false); // serverhost, port.
#else
		XmlRpcClient theXmlRpcClient(strServerHostname.Get(), nServerPort); // serverhost, port.
#endif
		// -----------------------------------------------------------
		//
		// Call the OT_XML_RPC method (thus passing the message to the server.)
		//
		XmlRpcValue oneArg, result;		// oneArg contains the outgoing message; result will contain the server reply.
		oneArg[0] = ascEnvelope.Get();	// Here's where I set the envelope string, as the only argument for the rpc call.
		
		if (theXmlRpcClient.execute("OT_XML_RPC", oneArg, result)) // The actual call to the server. (Hope my envelope string isn't too long for this...)
		{					
			std::string str_Result = result;
			OTASCIIArmor ascServerReply = str_Result.c_str();
			
			OTEnvelope theServerEnvelope(ascServerReply);
			OTString	strServerReply;	
			bool bOpened = theServerEnvelope.Open(*(g_OT_API.GetClient()->m_pConnection->GetNym()), strServerReply);
			
			OTMessage theServerReply;
			
			if (bOpened && strServerReply.Exists() && theServerReply.LoadContractFromString(strServerReply))
			{
				// Now the fully-loaded message object (from the server, this time) can be processed by the OT library...
				g_OT_API.GetClient()->ProcessServerReply(theServerReply); 
				// Could also use OTMessageBuffer here, just store the server reply, and then let the client
				// come back later and call another API function to read the replies out of the buffer
			}
			else
			{
				OTLog::Error("Error loading server reply from string after call to 'OT_XML_RPC'\n");
			}
		}
		else
		{
			OTLog::Error("Error calling 'OT_XML_RPC' over the XmlRpc transport layer.\n");
		}
	}
}

#endif  // (OT_XMLRPC_MODE)
// -------------------------------------------------------------------------




// The API begins here...


OT_API::OT_API()
{
	m_pWallet = NULL;
	m_pClient = NULL;
		
	m_bInitialized = false;
}

OT_API::~OT_API()
{
	if (NULL != m_pWallet)
		delete m_pWallet;
	if (NULL != m_pClient)
		delete m_pClient;
	
	m_pWallet = NULL;
	m_pClient = NULL;
}




// Call this once per instance of OT_API.
bool OT_API::Init(OTString & strClientPath)
{
	// TODO: Main path needs to be stored in OT_API global, not OTLog static.
	//		 This way, you can have multiple instances of OT_API,
	//		 Each with their own main path. This is necessary.
	//		 Now that the OT_API class exists might be time to take
	//       folders away from OTLog and move it all over. Ugh.
	// OR!! Maybe just code a mechanism so OTLog tracks the instances of OT_API.
	
	OT_ASSERT(strClientPath.Exists());
	
	OTLog::SetMainPath(strClientPath.Get()); // This currently does NOT support multiple instances of OT_API.  :-(
	
	m_pWallet = new OTWallet;
	m_pClient = new OTClient;
	
	OT_ASSERT(NULL != m_pWallet);
	OT_ASSERT(NULL != m_pClient);
	
	m_bInitialized = m_pClient->InitClient(*m_pWallet);
	
	return m_bInitialized;
}

// Call this once per run of the software. Static.
bool OT_API::InitOTAPI()
{
#ifdef _WIN32
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD( 2, 2 );
	int err = WSAStartup( wVersionRequested, &wsaData );
#endif
	
	// TODO: probably put all the OpenSSL init stuff here now. We'll see.
	
	// TODO in the case of Windows, figure err into this return val somehow.
	return true;
}


// "wallet.xml" (path set above.)
bool OT_API::loadWallet(OTString & strPath)
{
	return m_pWallet->LoadWallet(strPath.Get());
}


int OT_API::getNymCount()
{
	return m_pWallet->GetNymCount();
}

int OT_API::getServerCount()
{
	return m_pWallet->GetServerCount();
}

int OT_API::getAssetTypeCount()
{
	return m_pWallet->GetAssetTypeCount();
}

int OT_API::getAccountCount()
{
	return m_pWallet->GetAccountCount();
}

bool OT_API::getNym(int iIndex, OTIdentifier & NYM_ID, OTString & NYM_NAME)
{
	return m_pWallet->GetNym(iIndex, NYM_ID, NYM_NAME);
}

bool OT_API::getServer(int iIndex, OTIdentifier & THE_ID, OTString & THE_NAME)
{
	return m_pWallet->GetServer(iIndex, THE_ID, THE_NAME);
}

bool OT_API::getAssetType(int iIndex, OTIdentifier & THE_ID, OTString & THE_NAME)
{
	return m_pWallet->GetAssetType(iIndex, THE_ID, THE_NAME);
}

bool OT_API::getAccount(int iIndex, OTIdentifier & THE_ID, OTString & THE_NAME)
{
	return m_pWallet->GetAccount(iIndex, THE_ID, THE_NAME);
}






// NOTE: This is only for Message->TCP->SSL mode, NOT for Message->XmlRpc->HTTP mode...
//
// Eventually this connects to the server denoted by SERVER_ID
// But for right now, it just connects to the first server in the list.
// TODO: make it connect to the server ID instead of the first one in the list.
//
bool OT_API::connectServer(OTIdentifier & SERVER_ID, OTIdentifier	& USER_ID,
						   OTString & strCA_FILE, OTString & strKEY_FILE, OTString & strKEY_PASSWORD)
{
#if defined(OT_XMLRPC_MODE)
	return false;
#endif
	
	// Wallet, after loading, should contain a list of server
	// contracts. Let's pull the hostname and port out of
	// the first contract, and connect to that server.
	
	OTPseudonym * pNym = m_pWallet->GetNymByID(USER_ID);
	
	if (!pNym)
	{
		OTLog::Error("No Nym loaded but tried to connect to server.\n");
		return false;
	}
		
	bool bConnected = m_pClient->ConnectToTheFirstServerOnList(*pNym, strCA_FILE, strKEY_FILE, strKEY_PASSWORD); 
	
	if (bConnected)
	{
		OTLog::Output(0, "Success. (Connected to the first notary server on your wallet's list.)\n");
		return true;
	}
	else {
		OTLog::Output(0, "Either the wallet is not loaded, or there was an error connecting to server.\n");
		return false;
	}
}




// NOTE: this function NOT needed in XmlRpc / HTTP (web services) mode.
//
// Open Transactions maintains a connection to the server(s)
// The client should call THIS function after a message, and/or periodicallyt,
// to listen on the connections for any server replies and process them.
//
// Perhaps once per second, and more often immediately following
// a request.  (Usually only one response comes for each request.)
//
bool OT_API::processSockets()
{
#if defined(OT_XMLRPC_MODE)
	return false;
#endif
	
	bool bFoundMessage = false, bSuccess = false;
	
	do 
	{
		OTMessage theMsg;
		
		// If this returns true, that means a Message was
		// received and processed into an OTMessage object (theMsg)
		bFoundMessage = m_pClient->ProcessInBuffer(theMsg);
		
		if (true == bFoundMessage)
		{
			bSuccess = true;
			
			//				OTString strReply;
			//				theMsg.SaveContract(strReply);
			//				OTLog::vError("\n\n**********************************************\n"
			//						"Successfully in-processed server response.\n\n%s\n", strReply.Get());
			m_pClient->ProcessServerReply(theMsg);
		}
		
	} while (true == bFoundMessage);
	
	return bSuccess;
}
// NOTE: The above function only applies in Message / TCP / SSL mode, since server replies are instantly
// received in XmlRpc / HTTP mode. (Both are request / response, it's the same protocol no matter what transport.)



void OT_API::exchangeBasket(OTIdentifier	& SERVER_ID,
							OTIdentifier	& USER_ID,
							OTIdentifier	& BASKET_ASSET_ID,
							OTString		& BASKET_INFO)
{
	// -----------------------------------------------------------------
	
	OTServerContract * pServer = m_pWallet->GetServerContract(SERVER_ID);
	
	if (!pServer)
	{
		// todo error message
		
		return;
	}
	
	
	// -----------------------------------------------------------------
	
	OTPseudonym * pNym = m_pWallet->GetNymByID(USER_ID);
	
	if (!pNym)
	{
		// todo error message
		
		return;
	}
	
	// -----------------------------------------------------------------
	
	OTAssetContract * pAssetContract = m_pWallet->GetAssetContract(BASKET_ASSET_ID);
	
	if (!pAssetContract)
	{
		// todo error message
		
		return;
	}
	
	// -----------------------------------------------------------------
	
	OTMessage theMessage;
	long lRequestNumber = 0;
	
	OTString strServerID(SERVER_ID), strNymID(USER_ID), strAssetTypeID(BASKET_ASSET_ID);
	
	// (0) Set up the REQUEST NUMBER and then INCREMENT IT
	pNym->GetCurrentRequestNum(strServerID, lRequestNumber);
	theMessage.m_strRequestNum.Format("%ld", lRequestNumber); // Always have to send this.
	pNym->IncrementRequestNum(*pNym, strServerID); // since I used it for a server request, I have to increment it
	
	// (1) set up member variables 
	theMessage.m_strCommand			= "exchangeBasket";
	theMessage.m_strNymID			= strNymID;
	theMessage.m_strServerID		= strServerID;
	theMessage.m_strAssetID			= strAssetTypeID;
	
	theMessage.m_ascPayload.SetString(BASKET_INFO);
	
	// (2) Sign the Message 
	theMessage.SignContract(*pNym);		
	
	// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
	theMessage.SaveContract();
	
	// (Send it)
#if defined(OT_XMLRPC_MODE)
	m_pClient->SetFocusToServerAndNym(*pServer, *pNym, &OT_XmlRpcCallback);
#endif	
	m_pClient->ProcessMessageOut(theMessage);		
}





void OT_API::getTransactionNumber(OTIdentifier & SERVER_ID,
								  OTIdentifier & USER_ID)
{
	// -----------------------------------------------------------------
	
	OTServerContract * pServer = m_pWallet->GetServerContract(SERVER_ID);
	
	if (!pServer)
	{
		// todo error message
		
		return;
	}
	
	
	// -----------------------------------------------------------------
	
	OTPseudonym * pNym = m_pWallet->GetNymByID(USER_ID);
	
	if (!pNym)
	{
		// todo error message
		
		return;
	}
	
	// -----------------------------------------------------------------
	
	OTMessage theMessage;
	
	if (m_pClient->ProcessUserCommand(OTClient::getTransactionNum, theMessage, 
									*pNym, *pServer,
									NULL)) // NULL pAccount on this command.
	{				
#if defined(OT_XMLRPC_MODE)
		m_pClient->SetFocusToServerAndNym(*pServer, *pNym, &OT_XmlRpcCallback);
#endif	
		m_pClient->ProcessMessageOut(theMessage);
	}
	else
		OTLog::Error("Error processing getTransactionNumber command in OT_API::getTransactionNumber\n");
}





void OT_API::notarizeWithdrawal(OTIdentifier	& SERVER_ID,
								OTIdentifier	& USER_ID,
								OTIdentifier	& ACCT_ID,
								OTString		& AMOUNT)
{
	// -----------------------------------------------------------------
	
	OTServerContract * pServer = m_pWallet->GetServerContract(SERVER_ID);
	
	if (!pServer)
	{
		// todo error message
		
		return;
	}
	
	
	// -----------------------------------------------------------------
	
	OTPseudonym * pNym = m_pWallet->GetNymByID(USER_ID);
	
	if (!pNym)
	{
		// todo error message
		
		return;
	}
	
	// -----------------------------------------------------------------
	
	OTIdentifier	CONTRACT_ID;
	OTString		strContractID;
	
	OTAccount * pAccount = m_pWallet->GetAccount(ACCT_ID);
	
	if (!pAccount)
	{
		// todo error message
		
		return;
	}
	else {
		CONTRACT_ID = pAccount->GetAssetTypeID();
		CONTRACT_ID.GetString(strContractID);
	}
	
	
	// -----------------------------------------------------------------
	
	
	OTMessage theMessage;
	
	long lRequestNumber = 0;
	long lAmount = atol(AMOUNT.Get());
	
	OTString strServerID(SERVER_ID), strNymID(USER_ID), strFromAcct(ACCT_ID);
	
	long lStoredTransactionNumber=0;
	bool bGotTransNum = pNym->GetNextTransactionNum(*pNym, strServerID, lStoredTransactionNumber);
	
	if (bGotTransNum)
	{
		// Create a transaction
		OTTransaction * pTransaction = OTTransaction::GenerateTransaction (USER_ID, ACCT_ID, SERVER_ID, 
																		   OTTransaction::withdrawal, lStoredTransactionNumber); 
		
		// set up the transaction item (each transaction may have multiple items...)
		OTItem * pItem		= OTItem::CreateItemFromTransaction(*pTransaction, OTItem::withdrawal);
		pItem->m_lAmount	= lAmount;
		
		const OTPseudonym * pServerNym = pServer->GetContractPublicNym();
		
		OTString strMintPath;
		strMintPath.Format("%s%s%s%s%s", OTLog::Path(), OTLog::PathSeparator(), OTLog::MintFolder(),
						   OTLog::PathSeparator(), strContractID.Get()); 
		OTMint theMint(strContractID, strMintPath, strContractID);
		
		if (pServerNym && theMint.LoadContract() && theMint.VerifyMint((OTPseudonym&)*pServerNym))
		{
			OTPurse * pPurse		= new OTPurse(SERVER_ID, CONTRACT_ID);
			OTPurse * pPurseMyCopy	= new OTPurse(SERVER_ID, CONTRACT_ID);
			
			// Create all the necessary tokens for the withdrawal amount.
			// Push copies of each token into a purse to be sent to the server,
			// as well as a purse to be kept for unblinding when we receive the
			// server response.  (Coin private unblinding keys are not sent to
			// the server, obviously.)
			long lTokenAmount = 0;
			while (lTokenAmount = theMint.GetLargestDenomination(lAmount))
			{
				lAmount -= lTokenAmount;
				
				// Create the relevant token request with same server/asset ID as the purse.
				// the purse does NOT own the token at this point. the token's constructor
				// just uses it to copy some IDs, since they must match.
				OTToken theToken(*pPurse);
				
				// GENERATE new token, sign it and save it. 
				theToken.GenerateTokenRequest(*pNym, theMint, lTokenAmount);
				theToken.SignContract(*pNym);
				theToken.SaveContract();
				
				// Now the proto-token is generated, let's add it to a purse
				// By pushing theToken into pPurse with *pServerNym, I encrypt it to pServerNym.
				// So now only the server Nym can decrypt that token and pop it out of that purse.
				pPurse->Push(*pServerNym, theToken);	
				
				// I'm saving my own copy of all this, encrypted to my nym
				// instead of the server's, so I can get to my private coin data.
				// The server's copy of theToken is already Pushed, so I can re-use
				// the variable now for my own purse.
				theToken.ReleaseSignatures();
				theToken.SetSavePrivateKeys(); // This time it will save the private keys when I sign it
				theToken.SignContract(*pNym);
				theToken.SaveContract();
				
				pPurseMyCopy->Push(*pNym, theToken);// Now my copy of the purse has a version of the token,
			}
			
			pPurse->SignContract(*pNym);
			pPurse->SaveContract(); // I think this one is unnecessary.
			
			// Save the purse into a string...
			OTString strPurse;
			pPurse->SaveContract(strPurse);
			
			// Add the purse string as the attachment on the transaction item.
			pItem->SetAttachment(strPurse); // The purse is contained in the reference string.
			
			
			pPurseMyCopy->SignContract(*pNym);		// encrypted to me instead of the server, and including 
			pPurseMyCopy->SaveContract();			// the private keys for unblinding the server response.
			// This thing is neat and tidy. The wallet can just save it as an ascii-armored string as a
			// purse field inside the wallet file.  It doesn't do that for now (TODO) but it easily could.
			
			
			// Add the purse to the wallet
			// (We will need it to look up the private coin info for unblinding the token,
			//  when the response comes from the server.)
			m_pWallet->AddPendingWithdrawal(*pPurseMyCopy);
			
			delete pPurse;
			pPurse			= NULL; // We're done with this one.
			pPurseMyCopy	= NULL; // The wallet owns my copy now and will handle cleaning it up.
			
			
			// sign the item
			pItem->SignContract(*pNym);
			pItem->SaveContract();
			
			pTransaction->AddItem(*pItem); // the Transaction's destructor will cleanup the item. It "owns" it now.
			
			// sign the transaction
			pTransaction->SignContract(*pNym);
			pTransaction->SaveContract();
			
			
			// set up the ledger
			OTLedger theLedger(USER_ID, ACCT_ID, SERVER_ID);
			theLedger.GenerateLedger(ACCT_ID, SERVER_ID, OTLedger::message); // bGenerateLedger defaults to false, which is correct.
			theLedger.AddTransaction(*pTransaction);
			
			// sign the ledger
			theLedger.SignContract(*pNym);
			theLedger.SaveContract();
			
			// extract the ledger in ascii-armored form
			OTString		strLedger(theLedger);
			OTASCIIArmor	ascLedger; // I can't pass strLedger into this constructor because I want to encode it
			
			// Encoding...
			ascLedger.SetString(strLedger);
			
			
			// (0) Set up the REQUEST NUMBER and then INCREMENT IT
			pNym->GetCurrentRequestNum(strServerID, lRequestNumber);
			theMessage.m_strRequestNum.Format("%ld", lRequestNumber); // Always have to send this.
			pNym->IncrementRequestNum(*pNym, strServerID); // since I used it for a server request, I have to increment it
			
			// (1) Set up member variables 
			theMessage.m_strCommand			= "notarizeTransactions";
			theMessage.m_strNymID			= strNymID;
			theMessage.m_strServerID		= strServerID;
			theMessage.m_strAcctID			= strFromAcct;
			theMessage.m_ascPayload			= ascLedger;
			
			// (2) Sign the Message 
			theMessage.SignContract(*pNym);		
			
			// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
			theMessage.SaveContract();
			
			// (Send it)
#if defined(OT_XMLRPC_MODE)
			m_pClient->SetFocusToServerAndNym(*pServer, *pNym, &OT_XmlRpcCallback);
#endif	
			m_pClient->ProcessMessageOut(theMessage);	
		}
	}
	else {
		OTLog::Output(0, "No Transaction Numbers were available. Suggest requesting the server for a new one.\n");
	}
}





void OT_API::notarizeDeposit(OTIdentifier	& SERVER_ID,
							 OTIdentifier	& USER_ID,
							 OTIdentifier	& ACCT_ID,
							 OTString		& THE_PURSE)
{
	// -----------------------------------------------------------------
	
	OTServerContract * pServer = m_pWallet->GetServerContract(SERVER_ID);
	
	if (!pServer)
	{
		// todo error message
		
		return;
	}
	
	
	// -----------------------------------------------------------------
	
	OTPseudonym * pNym = m_pWallet->GetNymByID(USER_ID);
	
	if (!pNym)
	{
		// todo error message
		
		return;
	}
	
	// -----------------------------------------------------------------
	
	OTIdentifier	CONTRACT_ID;
	OTString		strContractID;
	
	OTAccount * pAccount = m_pWallet->GetAccount(ACCT_ID);
	
	if (!pAccount)
	{
		// todo error message
		
		return;
	}
	else {
		CONTRACT_ID = pAccount->GetAssetTypeID();
		CONTRACT_ID.GetString(strContractID);
	}
	
	
	// -----------------------------------------------------------------
	
	OTMessage theMessage;
	long lRequestNumber = 0;
	
	OTString strServerID(SERVER_ID), strNymID(USER_ID), strFromAcct(ACCT_ID);
	
	
	OTPurse thePurse(SERVER_ID, CONTRACT_ID);
	
	const OTPseudonym * pServerNym = pServer->GetContractPublicNym();
	
	long lStoredTransactionNumber=0;
	bool bGotTransNum = pNym->GetNextTransactionNum(*pNym, strServerID, lStoredTransactionNumber);
	
	if (!bGotTransNum)
	{
		OTLog::Output(0, "No Transaction Numbers were available. Try requesting the server for a new one.\n");
	}
	else if (pServerNym)
	{
		bool bSuccess = false;
		
		// Create a transaction
		OTTransaction * pTransaction = OTTransaction::GenerateTransaction (USER_ID, ACCT_ID, SERVER_ID, 
																		   OTTransaction::deposit, lStoredTransactionNumber); 
		
		// set up the transaction item (each transaction may have multiple items...)
		OTItem * pItem		= OTItem::CreateItemFromTransaction(*pTransaction, OTItem::deposit);
		
		OTPurse theSourcePurse(thePurse);
		
		if (theSourcePurse.LoadContractFromString(THE_PURSE))
			while (!theSourcePurse.IsEmpty()) 
			{
				OTToken * pToken = theSourcePurse.Pop(*pNym);
				
				if (pToken)
				{
					// TODO need 2-recipient envelopes. My request to the server is encrypted to the server's nym,
					// but it should be encrypted to my Nym also, so both have access to decrypt it.
					
					// Now the token is ready, let's add it to a purse
					// By pushing theToken into thePurse with *pServerNym, I encrypt it to pServerNym.
					// So now only the server Nym can decrypt that token and pop it out of that purse.
					if (false == pToken->ReassignOwnership(*pNym, *pServerNym))
					{
						OTLog::Error("Error re-assigning ownership of token (to server.)\n");
						delete pToken;
						pToken = NULL;
						bSuccess = false;
						break;
					}
					else 
					{
						OTLog::vOutput(3, "Success re-assigning ownership of token (to server.)\n");
						
						bSuccess = true;
						
						pToken->ReleaseSignatures();
						pToken->SignContract(*pNym);
						pToken->SaveContract();
						
						thePurse.Push(*pServerNym, *pToken);
						
						pItem->m_lAmount += pToken->GetDenomination();
					}
					
					delete pToken;
					pToken = NULL;
				}
				else {
					OTLog::Error("Error loading token from purse.\n");
					break;
				}
				
			}
		
		if (bSuccess)
		{
			thePurse.SignContract(*pNym);
			thePurse.SaveContract(); // I think this one is unnecessary.
			
			// Save the purse into a string...
			OTString strPurse;
			thePurse.SaveContract(strPurse);
			
			// Add the purse string as the attachment on the transaction item.
			pItem->SetAttachment(strPurse); // The purse is contained in the reference string.
			
			// sign the item
			pItem->SignContract(*pNym);
			pItem->SaveContract();
			
			// the Transaction "owns" the item now and will handle cleaning it up.
			pTransaction->AddItem(*pItem); // the Transaction's destructor will cleanup the item. It "owns" it now.
			
			// sign the transaction
			pTransaction->SignContract(*pNym);
			pTransaction->SaveContract();
			
			
			// set up the ledger
			OTLedger theLedger(USER_ID, ACCT_ID, SERVER_ID);
			theLedger.GenerateLedger(ACCT_ID, SERVER_ID, OTLedger::message); // bGenerateLedger defaults to false, which is correct.
			theLedger.AddTransaction(*pTransaction); // now the ledger "owns" and will handle cleaning up the transaction.
			
			// sign the ledger
			theLedger.SignContract(*pNym);
			theLedger.SaveContract();
			
			// extract the ledger in ascii-armored form... encoding...
			OTString		strLedger(theLedger);
			OTASCIIArmor	ascLedger(strLedger);
			
			// (0) Set up the REQUEST NUMBER and then INCREMENT IT
			pNym->GetCurrentRequestNum(strServerID, lRequestNumber);
			theMessage.m_strRequestNum.Format("%ld", lRequestNumber); // Always have to send this.
			pNym->IncrementRequestNum(*pNym, strServerID); // since I used it for a server request, I have to increment it
			
			// (1) Set up member variables 
			theMessage.m_strCommand			= "notarizeTransactions";
			theMessage.m_strNymID			= strNymID;
			theMessage.m_strServerID		= strServerID;
			theMessage.m_strAcctID			= strFromAcct;
			theMessage.m_ascPayload			= ascLedger;
			
			// (2) Sign the Message 
			theMessage.SignContract(*pNym);		
			
			// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
			theMessage.SaveContract();
			
			// (Send it)
#if defined(OT_XMLRPC_MODE)
			m_pClient->SetFocusToServerAndNym(*pServer, *pNym, &OT_XmlRpcCallback);
#endif	
			m_pClient->ProcessMessageOut(theMessage);	
			
		} // bSuccess
		else {
			delete pItem;		pItem = NULL;
			delete pTransaction;pTransaction = NULL;
		}
	} // if (pServerNym)
}



void OT_API::withdrawVoucher(OTIdentifier	& SERVER_ID,
							 OTIdentifier	& USER_ID,
							 OTIdentifier	& ACCT_ID,
							 OTIdentifier	& RECIPIENT_USER_ID,
							 OTString		& CHEQUE_MEMO,
							 OTString		& AMOUNT)
{
	// -----------------------------------------------------------------
	
	OTServerContract * pServer = m_pWallet->GetServerContract(SERVER_ID);
	
	if (!pServer)
	{
		// todo error message
		
		return;
	}
	
	
	// -----------------------------------------------------------------
	
	OTPseudonym * pNym = m_pWallet->GetNymByID(USER_ID);
	
	if (!pNym)
	{
		// todo error message
		
		return;
	}
	
	// -----------------------------------------------------------------
	
	OTIdentifier	CONTRACT_ID;
	OTString		strContractID;
	
	OTAccount * pAccount = m_pWallet->GetAccount(ACCT_ID);
	
	if (!pAccount)
	{
		// todo error message
		
		return;
	}
	else {
		CONTRACT_ID = pAccount->GetAssetTypeID();
		CONTRACT_ID.GetString(strContractID);
	}
	
	
	// -----------------------------------------------------------------
	
	OTMessage theMessage;
	
	long lAmount = atol(AMOUNT.Get());
	
	OTString strServerID(SERVER_ID), strNymID(USER_ID), strFromAcct(ACCT_ID);
	
	long lStoredTransactionNumber=0;
	bool bGotTransNum = pNym->GetNextTransactionNum(*pNym, strServerID, lStoredTransactionNumber);
	
	if (bGotTransNum)
	{
		const OTString strChequeMemo(CHEQUE_MEMO);
		const OTString strRecipientUserID(RECIPIENT_USER_ID);
		
		const long lAmount = atol(AMOUNT.Get());

		// -----------------------------------------------------------------------
		
		// Expiration (ignored by server -- it sets its own for its vouchers.)
		const	time_t	VALID_FROM	= time(NULL); // This time is set to TODAY NOW
		const	time_t	VALID_TO	= VALID_FROM + 15552000; // 6 months.
		
		// -----------------------------------------------------------------------
		// The server only uses the memo, amount, and recipient from this cheque when it
		// constructs the actual voucher.
		OTCheque theRequestVoucher(SERVER_ID, CONTRACT_ID);
		bool bIssueCheque = theRequestVoucher.IssueCheque(lAmount, lStoredTransactionNumber,// server actually ignores this and supplies its own transaction number for any voucher.
														  VALID_FROM, VALID_TO, ACCT_ID, USER_ID, strChequeMemo,
														  (strRecipientUserID.GetLength() > 2) ? &(RECIPIENT_USER_ID) : NULL);
		
		if (bIssueCheque)
		{
			// Create a transaction
			OTTransaction * pTransaction = OTTransaction::GenerateTransaction (USER_ID, ACCT_ID, SERVER_ID, 
																			   OTTransaction::withdrawal, lStoredTransactionNumber); 
			
			// set up the transaction item (each transaction may have multiple items...)
			OTItem * pItem		= OTItem::CreateItemFromTransaction(*pTransaction, OTItem::withdrawVoucher);
			pItem->m_lAmount	= lAmount;
			OTString strNote("Withdraw Voucher: ");
			pItem->SetNote(strNote);
			
			// Add the voucher request string as the attachment on the transaction item.
			theRequestVoucher.SignContract(*pNym);
			theRequestVoucher.SaveContract();
			OTString strVoucher(theRequestVoucher);
			pItem->SetAttachment(strVoucher); // The voucher request is contained in the reference string.
			
			// sign the item
			pItem->SignContract(*pNym);
			pItem->SaveContract();
			
			pTransaction->AddItem(*pItem); // the Transaction's destructor will cleanup the item. It "owns" it now.
			
			// sign the transaction
			pTransaction->SignContract(*pNym);
			pTransaction->SaveContract();
			
			
			// set up the ledger
			OTLedger theLedger(USER_ID, ACCT_ID, SERVER_ID);
			theLedger.GenerateLedger(ACCT_ID, SERVER_ID, OTLedger::message); // bGenerateLedger defaults to false, which is correct.
			theLedger.AddTransaction(*pTransaction);
			
			// sign the ledger
			theLedger.SignContract(*pNym);
			theLedger.SaveContract();
			
			// extract the ledger in ascii-armored form
			OTString		strLedger(theLedger);
			OTASCIIArmor	ascLedger(strLedger);
			
			long lRequestNumber = 0;
			
			// (0) Set up the REQUEST NUMBER and then INCREMENT IT
			pNym->GetCurrentRequestNum(strServerID, lRequestNumber);
			theMessage.m_strRequestNum.Format("%ld", lRequestNumber); // Always have to send this.
			pNym->IncrementRequestNum(*pNym, strServerID); // since I used it for a server request, I have to increment it
			
			// (1) Set up member variables 
			theMessage.m_strCommand			= "notarizeTransactions";
			theMessage.m_strNymID			= strNymID;
			theMessage.m_strServerID		= strServerID;
			theMessage.m_strAcctID			= strFromAcct;
			theMessage.m_ascPayload			= ascLedger;
			
			// (2) Sign the Message 
			theMessage.SignContract(*pNym);		
			
			// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
			theMessage.SaveContract();
			
			// (Send it)
#if defined(OT_XMLRPC_MODE)
			m_pClient->SetFocusToServerAndNym(*pServer, *pNym, &OT_XmlRpcCallback);
#endif	
			m_pClient->ProcessMessageOut(theMessage);	
		}
	}
	else {
		OTLog::Output(0, "No Transaction Numbers were available. Suggest requesting the server for a new one.\n");
	}
}





void OT_API::depositCheque(OTIdentifier	& SERVER_ID,
						   OTIdentifier	& USER_ID,
						   OTIdentifier	& ACCT_ID,
						   OTString		& THE_CHEQUE)
{
	// -----------------------------------------------------------------
	
	OTServerContract * pServer = m_pWallet->GetServerContract(SERVER_ID);
	
	if (!pServer)
	{
		// todo error message
		
		return;
	}
	
	
	// -----------------------------------------------------------------
	
	OTPseudonym * pNym = m_pWallet->GetNymByID(USER_ID);
	
	if (!pNym)
	{
		// todo error message
		
		return;
	}
	
	// -----------------------------------------------------------------
	
	OTIdentifier	CONTRACT_ID;
	OTString		strContractID;
	
	OTAccount * pAccount = m_pWallet->GetAccount(ACCT_ID);
	
	if (!pAccount)
	{
		// todo error message
		
		return;
	}
	else {
		CONTRACT_ID = pAccount->GetAssetTypeID();
		CONTRACT_ID.GetString(strContractID);
	}
	
	
	// -----------------------------------------------------------------
	
	OTMessage theMessage;
	long lRequestNumber = 0;
	
	OTString strServerID(SERVER_ID), strNymID(USER_ID), strFromAcct(ACCT_ID);
	
	OTCheque theCheque(SERVER_ID, CONTRACT_ID);
	
	long lStoredTransactionNumber=0;
	bool bGotTransNum = pNym->GetNextTransactionNum(*pNym, strServerID, lStoredTransactionNumber);
	
	if (!bGotTransNum)
	{
		OTLog::Output(0, "No Transaction Numbers were available. Try requesting the server for a new one.\n");
	}
	else if (theCheque.LoadContractFromString(THE_CHEQUE))
	{
		// Create a transaction
		OTTransaction * pTransaction = OTTransaction::GenerateTransaction (USER_ID, ACCT_ID, SERVER_ID, 
																		   OTTransaction::deposit, lStoredTransactionNumber); 
		
		// set up the transaction item (each transaction may have multiple items...)
		OTItem * pItem		= OTItem::CreateItemFromTransaction(*pTransaction, OTItem::depositCheque);
		
		OTString strNote("Deposit this cheque, please!");
		pItem->SetNote(strNote);
		
		OTString strCheque(theCheque);
		
		// Add the cheque string as the attachment on the transaction item.
		pItem->SetAttachment(strCheque); // The cheque is contained in the reference string.
		
		// sign the item
		pItem->SignContract(*pNym);
		pItem->SaveContract();
		
		// the Transaction "owns" the item now and will handle cleaning it up.
		pTransaction->AddItem(*pItem); // the Transaction's destructor will cleanup the item. It "owns" it now.
		
		// sign the transaction
		pTransaction->SignContract(*pNym);
		pTransaction->SaveContract();
		
		// set up the ledger
		OTLedger theLedger(USER_ID, ACCT_ID, SERVER_ID);
		theLedger.GenerateLedger(ACCT_ID, SERVER_ID, OTLedger::message); // bGenerateLedger defaults to false, which is correct.
		theLedger.AddTransaction(*pTransaction); // now the ledger "owns" and will handle cleaning up the transaction.
		
		// sign the ledger
		theLedger.SignContract(*pNym);
		theLedger.SaveContract();
		
		// extract the ledger in ascii-armored form... encoding...
		OTString		strLedger(theLedger);
		OTASCIIArmor	ascLedger(strLedger);
		
		// (0) Set up the REQUEST NUMBER and then INCREMENT IT
		pNym->GetCurrentRequestNum(strServerID, lRequestNumber);
		theMessage.m_strRequestNum.Format("%ld", lRequestNumber); // Always have to send this.
		pNym->IncrementRequestNum(*pNym, strServerID); // since I used it for a server request, I have to increment it
		
		// (1) Set up member variables 
		theMessage.m_strCommand			= "notarizeTransactions";
		theMessage.m_strNymID			= strNymID;
		theMessage.m_strServerID		= strServerID;
		theMessage.m_strAcctID			= strFromAcct;
		theMessage.m_ascPayload			= ascLedger;
		
		// (2) Sign the Message 
		theMessage.SignContract(*pNym);		
		
		// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
		theMessage.SaveContract();
			
		// (Send it)
#if defined(OT_XMLRPC_MODE)
		m_pClient->SetFocusToServerAndNym(*pServer, *pNym, &OT_XmlRpcCallback);
#endif	
		m_pClient->ProcessMessageOut(theMessage);	
		
	} // bSuccess
}







void OT_API::notarizeTransfer(OTIdentifier	& SERVER_ID,
							  OTIdentifier	& USER_ID,
							  OTIdentifier	& ACCT_FROM,
							  OTIdentifier	& ACCT_TO,
							  OTString		& AMOUNT,
							  OTString		& NOTE)
{
	// -----------------------------------------------------------------
	
	OTServerContract * pServer = m_pWallet->GetServerContract(SERVER_ID);
	
	if (!pServer)
	{
		// todo error message
		
		return;
	}
	
	
	// -----------------------------------------------------------------
	
	OTPseudonym * pNym = m_pWallet->GetNymByID(USER_ID);
	
	if (!pNym)
	{
		// todo error message
		
		return;
	}
	
	// -----------------------------------------------------------------
	
	OTAccount * pAccount = m_pWallet->GetAccount(ACCT_FROM);
	
	if (!pAccount)
	{
		// todo error message
		
		return;
	}
	
	
	// -----------------------------------------------------------------
	
	
	OTMessage theMessage;
	
	long lRequestNumber = 0;
	long lAmount = atol(AMOUNT.Get());
	
	OTString	strServerID(SERVER_ID), strNymID(USER_ID), 
				strFromAcct(ACCT_FROM), strToAcct(ACCT_TO);

	long lStoredTransactionNumber=0;
	bool bGotTransNum = pNym->GetNextTransactionNum(*pNym, strServerID, lStoredTransactionNumber);
	
	if (bGotTransNum)
	{
		// Create a transaction
		OTTransaction * pTransaction = OTTransaction::GenerateTransaction (USER_ID, ACCT_FROM, 
																		   SERVER_ID, 
																		   OTTransaction::transfer, 
																		   lStoredTransactionNumber); 
		
		// set up the transaction item (each transaction may have multiple items...)
		OTItem * pItem		= OTItem::CreateItemFromTransaction(*pTransaction, OTItem::transfer, &ACCT_TO);
		pItem->m_lAmount	= atol(AMOUNT.Get());
		
		// The user can include a note here for the recipient.
		pItem->SetNote(NOTE);
		
		// sign the item
		pItem->SignContract(*pNym);
		pItem->SaveContract();
		
		
		pTransaction->AddItem(*pItem); // the Transaction's destructor will cleanup the item. It "owns" it now.
		
		// sign the transaction
		pTransaction->SignContract(*pNym);
		pTransaction->SaveContract();
		
		
		// set up the ledger
		OTLedger theLedger(USER_ID, ACCT_FROM, SERVER_ID);
		theLedger.GenerateLedger(ACCT_FROM, SERVER_ID, OTLedger::message); // bGenerateLedger defaults to false, which is correct.
		theLedger.AddTransaction(*pTransaction);
		
		// sign the ledger
		theLedger.SignContract(*pNym);
		theLedger.SaveContract();
		
		// extract the ledger in ascii-armored form
		OTString		strLedger(theLedger);
		OTASCIIArmor	ascLedger;
		
		// Encoding...
		ascLedger.SetString(strLedger);
		
		
		// (0) Set up the REQUEST NUMBER and then INCREMENT IT
		pNym->GetCurrentRequestNum(strServerID, lRequestNumber);
		theMessage.m_strRequestNum.Format("%ld", lRequestNumber); // Always have to send this.
		pNym->IncrementRequestNum(*pNym, strServerID); // since I used it for a server request, I have to increment it
		
		// (1) Set up member variables 
		theMessage.m_strCommand			= "notarizeTransactions";
		theMessage.m_strNymID			= strNymID;
		theMessage.m_strServerID		= strServerID;
		theMessage.m_strAcctID			= strFromAcct;
		theMessage.m_ascPayload			= ascLedger;
		
		// (2) Sign the Message 
		theMessage.SignContract(*pNym);		
		
		// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
		theMessage.SaveContract();

		// (Send it)
#if defined(OT_XMLRPC_MODE)
		m_pClient->SetFocusToServerAndNym(*pServer, *pNym, &OT_XmlRpcCallback);
#endif	
		m_pClient->ProcessMessageOut(theMessage);	
	}
	else {
		OTLog::Output(0, "No transaction numbers were available. Suggest requesting the server for one.\n");
	}	
}





void OT_API::getInbox(OTIdentifier & SERVER_ID,
					  OTIdentifier & USER_ID,
					  OTIdentifier & ACCT_ID)
{
	// -----------------------------------------------------------------
	
	OTServerContract * pServer = m_pWallet->GetServerContract(SERVER_ID);
	
	if (!pServer)
	{
		// todo error message
		
		return;
	}
	
	
	// -----------------------------------------------------------------
	
	OTPseudonym * pNym = m_pWallet->GetNymByID(USER_ID);
	
	if (!pNym)
	{
		// todo error message
		
		return;
	}
	
	// -----------------------------------------------------------------
	
	OTAccount * pAccount = m_pWallet->GetAccount(ACCT_ID);
	
	if (!pAccount)
	{
		// todo error message
		
		return;
	}
	
	// -----------------------------------------------------------------
	
	OTMessage theMessage;
	long lRequestNumber = 0;
	
	OTString strServerID(SERVER_ID), strNymID(USER_ID), strAcctID(ACCT_ID);
	
	// (0) Set up the REQUEST NUMBER and then INCREMENT IT
	pNym->GetCurrentRequestNum(strServerID, lRequestNumber);
	theMessage.m_strRequestNum.Format("%ld", lRequestNumber); // Always have to send this.
	pNym->IncrementRequestNum(*pNym, strServerID); // since I used it for a server request, I have to increment it
	
	// (1) set up member variables 
	theMessage.m_strCommand			= "getInbox";
	theMessage.m_strNymID			= strNymID;
	theMessage.m_strServerID		= strServerID;
	theMessage.m_strAcctID			= strAcctID;
	
	// (2) Sign the Message 
	theMessage.SignContract(*pNym);		
	
	// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
	theMessage.SaveContract();
	
	// (Send it)
#if defined(OT_XMLRPC_MODE)
	m_pClient->SetFocusToServerAndNym(*pServer, *pNym, &OT_XmlRpcCallback);
#endif	
	m_pClient->ProcessMessageOut(theMessage);	
}





void OT_API::processInbox(OTIdentifier	& SERVER_ID,
						  OTIdentifier	& USER_ID,
						  OTIdentifier	& ACCT_ID,
						  OTString		& ACCT_LEDGER)
{
	// -----------------------------------------------------------------
	
	OTServerContract * pServer = m_pWallet->GetServerContract(SERVER_ID);
	
	if (!pServer)
	{
		// todo error message
		
		return;
	}
	
	
	// -----------------------------------------------------------------
	
	OTPseudonym * pNym = m_pWallet->GetNymByID(USER_ID);
	
	if (!pNym)
	{
		// todo error message
		
		return;
	}
	
	// -----------------------------------------------------------------
	
	OTAccount * pAccount = m_pWallet->GetAccount(ACCT_ID);
	
	if (!pAccount)
	{
		// todo error message
		
		return;
	}
	
	// -----------------------------------------------------------------
	
	OTMessage theMessage;
	long lRequestNumber = 0;
	
	OTString strServerID(SERVER_ID), strNymID(USER_ID), strAcctID(ACCT_ID);
	
	// (0) Set up the REQUEST NUMBER and then INCREMENT IT
	pNym->GetCurrentRequestNum(strServerID, lRequestNumber);
	theMessage.m_strRequestNum.Format("%ld", lRequestNumber); // Always have to send this.
	pNym->IncrementRequestNum(*pNym, strServerID); // since I used it for a server request, I have to increment it
	
	// (1) set up member variables 
	theMessage.m_strCommand			= "processInbox";
	theMessage.m_strNymID			= strNymID;
	theMessage.m_strServerID		= strServerID;
	theMessage.m_strAcctID			= strAcctID;
	
	// Presumably ACCT_LEDGER was already set up before this function was called...
	// See test client for example of it being done.
	theMessage.m_ascPayload.SetString(ACCT_LEDGER);

	// (2) Sign the Message 
	theMessage.SignContract(*pNym);		
	
	// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
	theMessage.SaveContract();
	
	// (Send it)
#if defined(OT_XMLRPC_MODE)
	m_pClient->SetFocusToServerAndNym(*pServer, *pNym, &OT_XmlRpcCallback);
#endif	
	m_pClient->ProcessMessageOut(theMessage);	
}




void OT_API::issueBasket(OTIdentifier	& SERVER_ID,
						 OTIdentifier	& USER_ID,
						 OTString		& BASKET_INFO)
{
	// -----------------------------------------------------------------
	
	OTServerContract * pServer = m_pWallet->GetServerContract(SERVER_ID);
	
	if (!pServer)
	{
		// todo error message
		
		return;
	}
	
	
	// -----------------------------------------------------------------
	
	OTPseudonym * pNym = m_pWallet->GetNymByID(USER_ID);
	
	if (!pNym)
	{
		// todo error message
		
		return;
	}
	
	// -----------------------------------------------------------------
	
	// AT SOME POINT, BASKET_INFO has been populated with the relevant data. (see test client for example.)
	
	OTString strServerID(SERVER_ID), strNymID(USER_ID);

	OTMessage theMessage;
	long lRequestNumber = 0;
	
	// (0) Set up the REQUEST NUMBER and then INCREMENT IT
	pNym->GetCurrentRequestNum(strServerID, lRequestNumber);
	theMessage.m_strRequestNum.Format("%ld", lRequestNumber); // Always have to send this.
	pNym->IncrementRequestNum(*pNym, strServerID); // since I used it for a server request, I have to increment it
	
	// (1) Set up member variables 
	theMessage.m_strCommand			= "issueBasket";
	theMessage.m_strNymID			= strNymID;
	theMessage.m_strServerID		= strServerID;
	
	theMessage.m_ascPayload.SetString(BASKET_INFO);
	
	// (2) Sign the Message 
	theMessage.SignContract(*pNym);		
	
	// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
	theMessage.SaveContract();
	
	// (Send it)
#if defined(OT_XMLRPC_MODE)
	m_pClient->SetFocusToServerAndNym(*pServer, *pNym, &OT_XmlRpcCallback);
#endif	
	m_pClient->ProcessMessageOut(theMessage);
}



void OT_API::issueAssetType(OTIdentifier	&	SERVER_ID,
							OTIdentifier	&	USER_ID,
							OTString		&	THE_CONTRACT)
{
	// -----------------------------------------------------------------
	
	OTServerContract * pServer = m_pWallet->GetServerContract(SERVER_ID);
	
	if (!pServer)
	{
		// todo error message
		
		return;
	}
	
	
	// -----------------------------------------------------------------
	
	OTPseudonym * pNym = m_pWallet->GetNymByID(USER_ID);
	
	if (!pNym)
	{
		// todo error message
		
		return;
	}
	
	// -----------------------------------------------------------------
		
	OTAssetContract theAssetContract;
	
	if (theAssetContract.LoadContractFromString(THE_CONTRACT))
	{
		OTIdentifier	newID;
		theAssetContract.CalculateContractID(newID);
		
		// -----------------------
		OTMessage theMessage;
		long lRequestNumber = 0;
		
		OTString strServerID(SERVER_ID), strNymID(USER_ID);
		
		// (0) Set up the REQUEST NUMBER and then INCREMENT IT
		pNym->GetCurrentRequestNum(strServerID, lRequestNumber);
		theMessage.m_strRequestNum.Format("%ld", lRequestNumber); // Always have to send this.
		pNym->IncrementRequestNum(*pNym, strServerID); // since I used it for a server request, I have to increment it
		
		// (1) set up member variables 
		theMessage.m_strCommand			= "issueAssetType";
		theMessage.m_strNymID			= strNymID;
		theMessage.m_strServerID		= strServerID;
		
		newID.GetString(theMessage.m_strAssetID);
		OTString strAssetContract(theAssetContract);
		theMessage.m_ascPayload.SetString(strAssetContract);
		
		// (2) Sign the Message 
		theMessage.SignContract(*pNym);		
		
		// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
		theMessage.SaveContract();
		
		// (Send it)
#if defined(OT_XMLRPC_MODE)
		m_pClient->SetFocusToServerAndNym(*pServer, *pNym, &OT_XmlRpcCallback);
#endif	
		m_pClient->ProcessMessageOut(theMessage);
	}
}



void OT_API::getContract(OTIdentifier & SERVER_ID,
						 OTIdentifier & USER_ID,
						 OTIdentifier & ASSET_ID)
{
	// -----------------------------------------------------------------
	
	OTServerContract * pServer = m_pWallet->GetServerContract(SERVER_ID);
	
	if (!pServer)
	{
		// todo error message
		
		return;
	}
	
	
	// -----------------------------------------------------------------
	
	OTPseudonym * pNym = m_pWallet->GetNymByID(USER_ID);
	
	if (!pNym)
	{
		// todo error message
		
		return;
	}
	
	// -----------------------------------------------------------------
	
	OTAssetContract * pAssetContract = m_pWallet->GetAssetContract(ASSET_ID);
	
	if (!pAssetContract)
	{
		// todo error message
		
		return;
	}
	
	// -----------------------------------------------------------------
	
	OTMessage theMessage;
	long lRequestNumber = 0;
	
	OTString strServerID(SERVER_ID), strNymID(USER_ID), strAssetTypeID(ASSET_ID);
	
	// (0) Set up the REQUEST NUMBER and then INCREMENT IT
	pNym->GetCurrentRequestNum(strServerID, lRequestNumber);
	theMessage.m_strRequestNum.Format("%ld", lRequestNumber); // Always have to send this.
	pNym->IncrementRequestNum(*pNym, strServerID); // since I used it for a server request, I have to increment it
	
	// (1) set up member variables 
	theMessage.m_strCommand			= "getContract";
	theMessage.m_strNymID			= strNymID;
	theMessage.m_strServerID		= strServerID;
	theMessage.m_strAssetID			= strAssetTypeID;
	
	// (2) Sign the Message 
	theMessage.SignContract(*pNym);		
	
	// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
	theMessage.SaveContract();
	
	// (Send it)
#if defined(OT_XMLRPC_MODE)
	m_pClient->SetFocusToServerAndNym(*pServer, *pNym, &OT_XmlRpcCallback);
#endif	
	m_pClient->ProcessMessageOut(theMessage);	
}






void OT_API::getMint(OTIdentifier & SERVER_ID,
					 OTIdentifier & USER_ID,
					 OTIdentifier & ASSET_ID)
{
	// -----------------------------------------------------------------
	
	OTServerContract * pServer = m_pWallet->GetServerContract(SERVER_ID);
	
	if (!pServer)
	{
		// todo error message
		
		return;
	}
	
	
	// -----------------------------------------------------------------
	
	OTPseudonym * pNym = m_pWallet->GetNymByID(USER_ID);
	
	if (!pNym)
	{
		// todo error message
		
		return;
	}
	
	// -----------------------------------------------------------------
	
	OTAssetContract * pAssetContract = m_pWallet->GetAssetContract(ASSET_ID);
	
	if (!pAssetContract)
	{
		// todo error message
		
		return;
	}
	
	// -----------------------------------------------------------------
	
	OTMessage theMessage;
	long lRequestNumber = 0;
	
	OTString strServerID(SERVER_ID), strNymID(USER_ID), strAssetTypeID(ASSET_ID);
	
	// (0) Set up the REQUEST NUMBER and then INCREMENT IT
	pNym->GetCurrentRequestNum(strServerID, lRequestNumber);
	theMessage.m_strRequestNum.Format("%ld", lRequestNumber); // Always have to send this.
	pNym->IncrementRequestNum(*pNym, strServerID); // since I used it for a server request, I have to increment it
	
	// (1) set up member variables 
	theMessage.m_strCommand			= "getMint";
	theMessage.m_strNymID			= strNymID;
	theMessage.m_strServerID		= strServerID;
	theMessage.m_strAssetID			= strAssetTypeID;
	
	// (2) Sign the Message 
	theMessage.SignContract(*pNym);		
	
	// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
	theMessage.SaveContract();
	
	// (Send it)
#if defined(OT_XMLRPC_MODE)
	m_pClient->SetFocusToServerAndNym(*pServer, *pNym, &OT_XmlRpcCallback);
#endif	
	m_pClient->ProcessMessageOut(theMessage);	
}





void OT_API::createAssetAccount(OTIdentifier & SERVER_ID,
								OTIdentifier & USER_ID,
								OTIdentifier & ASSET_ID)
{	
	// -----------------------------------------------------------------
	
	OTServerContract * pServer = m_pWallet->GetServerContract(SERVER_ID);
	
	if (!pServer)
	{
		// todo error message
		
		return;
	}
	
	
	// -----------------------------------------------------------------
	
	OTPseudonym * pNym = m_pWallet->GetNymByID(USER_ID);
	
	if (!pNym)
	{
		// todo error message
		
		return;
	}
	
	// -----------------------------------------------------------------
	
	OTAssetContract * pAssetContract = m_pWallet->GetAssetContract(ASSET_ID);
	
	if (!pAssetContract)
	{
		// todo error message
		
		return;
	}
	
	// -----------------------------------------------------------------
	
	OTMessage theMessage;
	long lRequestNumber = 0;
	
	OTString strServerID(SERVER_ID), strNymID(USER_ID), strAssetTypeID(ASSET_ID);
	
	// (0) Set up the REQUEST NUMBER and then INCREMENT IT
	pNym->GetCurrentRequestNum(strServerID, lRequestNumber);
	theMessage.m_strRequestNum.Format("%ld", lRequestNumber); // Always have to send this.
	pNym->IncrementRequestNum(*pNym, strServerID); // since I used it for a server request, I have to increment it
	
	// (1) set up member variables 
	theMessage.m_strCommand			= "createAccount";
	theMessage.m_strNymID			= strNymID;
	theMessage.m_strServerID		= strServerID;
	theMessage.m_strAssetID			= strAssetTypeID;
	
	// (2) Sign the Message 
	theMessage.SignContract(*pNym);		
	
	// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
	theMessage.SaveContract();
	
	// (Send it)
#if defined(OT_XMLRPC_MODE)
	m_pClient->SetFocusToServerAndNym(*pServer, *pNym, &OT_XmlRpcCallback);
#endif	
	m_pClient->ProcessMessageOut(theMessage);
}





void OT_API::getAccount(OTIdentifier	& SERVER_ID,
						OTIdentifier	& USER_ID,
						OTIdentifier	& ACCT_ID)
{	
	// -----------------------------------------------------------------
	
	OTServerContract * pServer = m_pWallet->GetServerContract(SERVER_ID);
	
	if (!pServer)
	{
		// todo error message
		
		return;
	}
	
	
	// -----------------------------------------------------------------
	
	OTPseudonym * pNym = m_pWallet->GetNymByID(USER_ID);
	
	if (!pNym)
	{
		// todo error message
		
		return;
	}
	
	// -----------------------------------------------------------------
	
	OTAccount * pAccount = m_pWallet->GetAccount(ACCT_ID);
	
	if (!pAccount)
	{
		// todo error message
		
		return;
	}
	
	// -----------------------------------------------------------------
	
	OTMessage theMessage;
	long lRequestNumber = 0;
	
	OTString strServerID(SERVER_ID), strNymID(USER_ID), strAcctID(ACCT_ID);
	
	// (0) Set up the REQUEST NUMBER and then INCREMENT IT
	pNym->GetCurrentRequestNum(strServerID, lRequestNumber);
	theMessage.m_strRequestNum.Format("%ld", lRequestNumber); // Always have to send this.
	pNym->IncrementRequestNum(*pNym, strServerID); // since I used it for a server request, I have to increment it
	
	// (1) set up member variables 
	theMessage.m_strCommand			= "getAccount";
	theMessage.m_strNymID			= strNymID;
	theMessage.m_strServerID		= strServerID;
	theMessage.m_strAcctID			= strAcctID;
	
	// (2) Sign the Message 
	theMessage.SignContract(*pNym);		
	
	// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
	theMessage.SaveContract();
	
	// (Send it)
#if defined(OT_XMLRPC_MODE)
	m_pClient->SetFocusToServerAndNym(*pServer, *pNym, &OT_XmlRpcCallback);
#endif	
	m_pClient->ProcessMessageOut(theMessage);
}


void OT_API::getRequest(OTIdentifier	& SERVER_ID,
						OTIdentifier	& USER_ID)
{	
	// -----------------------------------------------------------------
	
	OTServerContract * pServer = m_pWallet->GetServerContract(SERVER_ID);
	
	if (!pServer)
	{
		// todo error message
		
		return;
	}
	
	
	// -----------------------------------------------------------------
	
	OTPseudonym * pNym = m_pWallet->GetNymByID(USER_ID);
	
	if (!pNym)
	{
		// todo error message
		
		return;
	}
	
	// -----------------------------------------------------------------
	
	OTMessage theMessage;
	
	if (m_pClient->ProcessUserCommand(OTClient::getRequest, theMessage, 
									*pNym, *pServer,
									NULL)) // NULL pAccount on this command.
	{				
#if defined(OT_XMLRPC_MODE)
		m_pClient->SetFocusToServerAndNym(*pServer, *pNym, &OT_XmlRpcCallback);
#endif	
		m_pClient->ProcessMessageOut(theMessage);
	}
	else
		OTLog::Error("Error processing getRequest command in OT_API::getRequest\n");
}



void OT_API::checkUser(OTIdentifier & SERVER_ID,
					   OTIdentifier & USER_ID,
					   OTIdentifier & USER_ID_CHECK)
{	
	// -----------------------------------------------------------------
	
	OTPseudonym * pNym = m_pWallet->GetNymByID(USER_ID);
	
	if (!pNym)
	{
		// todo error message
		
		return;
	}
	
	// -----------------------------------------------------------------
	
	OTMessage theMessage;
	long lRequestNumber = 0;

	OTString strServerID(SERVER_ID), strNymID(USER_ID), strNymID2(USER_ID_CHECK);
	
	// (0) Set up the REQUEST NUMBER and then INCREMENT IT
	pNym->GetCurrentRequestNum(strServerID, lRequestNumber);
	theMessage.m_strRequestNum.Format("%ld", lRequestNumber); // Always have to send this.
	pNym->IncrementRequestNum(*pNym, strServerID); // since I used it for a server request, I have to increment it
	
	// (1) set up member variables 
	theMessage.m_strCommand			= "checkUser";
	theMessage.m_strNymID			= strNymID;
	theMessage.m_strNymID2			= strNymID2;
	theMessage.m_strServerID		= strServerID;
	
	// (2) Sign the Message 
	theMessage.SignContract(*pNym);		
	
	// (3) Save the Message (with signatures and all, back to its internal member m_strRawFile.)
	theMessage.SaveContract();
		
	// (Send it)
#if defined(OT_XMLRPC_MODE)
	// -----------------------------------------------------------------
	
	OTServerContract * pServer = m_pWallet->GetServerContract(SERVER_ID);
	
	if (!pServer)
	{
		// todo error message
		
		return;
	}
	
	m_pClient->SetFocusToServerAndNym(*pServer, *pNym, &OT_XmlRpcCallback);
#endif	
	m_pClient->ProcessMessageOut(theMessage);
}


void OT_API::createUserAccount(OTIdentifier	& SERVER_ID,
							   OTIdentifier	& USER_ID)
{	
	// -----------------------------------------------------------------
	
	OTServerContract * pServer = m_pWallet->GetServerContract(SERVER_ID);
	
	if (!pServer)
	{
		// todo error message
		
		return;
	}
	
	
	// -----------------------------------------------------------------
	
	OTPseudonym * pNym = m_pWallet->GetNymByID(USER_ID);
	
	if (!pNym)
	{
		// todo error message
		
		return;
	}
	
	// -----------------------------------------------------------------
	
	OTMessage theMessage;
	
	if (m_pClient->ProcessUserCommand(OTClient::createUserAccount, theMessage, 
									*pNym, *pServer,
									NULL)) // NULL pAccount on this command.
	{				
#if defined(OT_XMLRPC_MODE)
		m_pClient->SetFocusToServerAndNym(*pServer, *pNym, &OT_XmlRpcCallback);
#endif	
		m_pClient->ProcessMessageOut(theMessage);
	}
	else
		OTLog::Error("Error processing createUserAccount command in OT_API::createUserAccount\n");
	
}


void OT_API::checkServerID(OTIdentifier	& SERVER_ID,
						   OTIdentifier	& USER_ID)
{	
	// -----------------------------------------------------------------
	
	OTServerContract * pServer = m_pWallet->GetServerContract(SERVER_ID);
	
	if (!pServer)
	{
		// todo error message
		
		return;
	}
	
	
	// -----------------------------------------------------------------
	
	OTPseudonym * pNym = m_pWallet->GetNymByID(USER_ID);
	
	if (!pNym)
	{
		// todo error message
		
		return;
	}
	
	// -----------------------------------------------------------------
	
	OTMessage theMessage;
	
	if (m_pClient->ProcessUserCommand(OTClient::checkServerID, theMessage, 
									*pNym, *pServer,
									NULL)) // NULL pAccount on this command.
	{				
#if defined(OT_XMLRPC_MODE)
		m_pClient->SetFocusToServerAndNym(*pServer, *pNym, &OT_XmlRpcCallback);
#endif	
		m_pClient->ProcessMessageOut(theMessage);
	}
	else
		OTLog::Error("Error processing checkServerID command in OT_API::checkServerID\n");
	
}



































