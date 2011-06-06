/************************************************************************************
 *    
 *  xmlrpcxx_server.cpp  (The web-services implementation of the Open Transactions server.)
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



// NOTE:  The PATH and the PASSWORD are configurable on the command line!!!
//
//        They are only here as defaults for convenience, so I don't have to
//        type them over and over again.  You can blank them out if you want, 
//        or set them to whatever is convenient for you on your system.
//

#define KEY_PASSWORD        "test"

#ifdef _WIN32
#define SERVER_PATH_DEFAULT	"C:\\~\\Open-Transactions\\transaction\\data_folder"
#define CA_FILE             "certs\\special\\ca.crt"
#define DH_FILE             "certs\\special\\dh_param_1024.pem"
#define KEY_FILE            "certs\\special\\server.pem"

#else

#define SERVER_PATH_DEFAULT	"./data_folder"
#define CA_FILE             "certs/special/ca.crt"
#define DH_FILE             "certs/special/dh_param_1024.pem"
#define KEY_FILE            "certs/special/server.pem"

#endif

// NOTE: the CA file, DH file, and Key file are most likely not necessary in this XML-RPC version.
// I left them here for now but so far I don't see that I need them for anything.

// ----------------------------------------------------------------

#ifdef _WIN32
#include "OTLib/stdafx.h"
#endif

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>
#include <list>
#include <string>
#include <unistd.h>


#include <zmq.hpp>

//#include "zhelpers.hpp"


extern "C" 
{
#ifdef _WIN32
#include <WinSock.h>
#else
#include <netinet/in.h>
#endif
	
#include <openssl/err.h>
#include <openssl/ssl.h>
}

// ------------------------------------


#include "SimpleIni.h"


// ------------------------------------

//#include "XmlRpc.h"

#include "OTStorage.h"

#include "main.h"

#include "OTMessage.h"
#include "OTEnvelope.h"

#include "OTServer.h"

#include "OTLog.h"


void ProcessMessage_ZMQ(const std::string & str_Message, std::string & str_Reply);

// -------------------------------------------------------------

//using namespace XmlRpc;


// The HTTP server
//XmlRpcServer theXmlRpcServer; // This object handles the network transport. (Over HHTP, in this case.)


// The Open Transactions server
OTServer * g_pServer = NULL;  // This object handles all the actual OT notarization processing.


// -------------------------------------------------------------

// This function is called for every OT Message that is sent for processing.
// One argument is passed, and a result string is passed back.
//
/*
class OT_XML_RPC : public XmlRpcServerMethod
{
public:
	OT_XML_RPC(XmlRpcServer* s) : XmlRpcServerMethod("OT_XML_RPC", s) 
	{
		// Do I need to do anything here? Doubt it.
	}
	
	void execute(XmlRpcValue& params, XmlRpcValue& result)
	{
		OT_ASSERT(NULL != g_pServer);
		
		// return value.
		std::string resultString = ""; // Whatever we put in this string is what will get returned.
		
		// First we grab the client's message (it's the first parameter.)
		std::string str_Message = std::string(params[0]); // Here I read the string containing the message.
		OTASCIIArmor ascMessage = str_Message.c_str();
		
		// ----------------------------------------------------------------------
		
		OTMessage theMsg, theReply; // we'll need these in a sec...

		OTEnvelope theEnvelope(ascMessage); // Now the base64 is decoded and the envelope is in binary form again.
		if (ascMessage.Exists())
		{
			OTLog::Output(2, "Successfully retrieved envelope from XmlRpc argument string...\n");
			
			OTString strEnvelopeContents;
			
			// Decrypt the Envelope.    
			if (theEnvelope.Open(g_pServer->GetServerNym(), strEnvelopeContents)) // now strEnvelopeContents contains the decoded message.
			{
				// All decrypted--now let's load the results into an OTMessage.
				// No need to call theMsg.ParseRawFile() after, since
				// LoadContractFromString handles it.
				//
				if (strEnvelopeContents.Exists() && theMsg.LoadContractFromString(strEnvelopeContents))
				{
					
					// In case you want to see all the incoming messages...
//					OTLog::vOutput(0, "%s\n\n", strEnvelopeContents.Get());
					
					// By constructing this without a socket, I put it in XmlRpc/http mode, instead of tcp/ssl.
					OTClientConnection theClient(*g_pServer); 

					// By optionally passing in &theClient, the client Nym's public key will be
					// set on it whenever verification is complete. (So for the reply, I'll 
					// have the key and thus I'll be able to encrypt reply to the recipient.)
					if (g_pServer->ProcessUserCommand(theMsg, theReply, &theClient))	
					{	
						// At this point the reply is ready to go, and theClient has the public key of the recipient...
						
						OTLog::vOutput(0, "Successfully processed user command: %s.\n", theMsg.m_strCommand.Get());
						
						// The transaction is now processed, and the server's reply message is in theReply.
						// Let's seal it up to the recipient's nym (in an envelope) and send back to the user...
						OTEnvelope theRecipientEnvelope;
						
						bool bSealed = theClient.SealMessageForRecipient(theReply, theRecipientEnvelope);

						if (bSealed)
						{
							OTASCIIArmor ascReply(theRecipientEnvelope);
							resultString = ascReply.Get();
						}
						else
							OTLog::Output(0, "Unable to seal envelope in OT_XML_RPC.\n");
					}
					else
						OTLog::Output(0, "Unable to process user command in OT_XML_RPC.\n");
				}
				else 
					OTLog::Error("Error loading message from envelope contents.\n");
			}
			else 
				OTLog::Error("Unable to open envelope.\n");
		}
		else 
			OTLog::Error("Error retrieving envelope from rpc.\n");


	// ----------------------------------------------------------------------
			
		result = resultString;
		
	}
} theOTXmlRpc(&theXmlRpcServer);
*/

	

// ----------------------------------------------------------------------


// The MAIN function for the server software, which starts up the XmlRpc (http server), 
// as well as Open Transactions.
//
int main(int argc, char* argv[])
{
	OTLog::vOutput(0, "\n\nWelcome to Open Transactions... Test Server -- version %s\n"
				   "(transport build: OTMessage -> ZMQ -> TCP)\n\n", OTLog::Version());
	// -----------------------------------------------------------------------

#ifdef _WIN32
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD( 2, 2 );
	int nWSA = WSAStartup( wVersionRequested, &wsaData );
	OT_ASSERT_MSG(0 != nWSA, "Error calling WSAStartup.\n");	
#endif
	
	// -----------------------------------------------------------------------
	// I instantiate this here (instead of globally) so that I am assured all the globals
	// are ready to go before the server is created.  I still have it as a global pointer, though,
	// so I can get to it wherever I need to.
	g_pServer = new OTServer;
	// (This file you are reading is a wrapper for OTServer, which adds the transport layer.)

	OT_ASSERT_MSG(NULL != g_pServer, "Unable to instantiate OT server...\n");
	
	// -----------------------------------------------------------------------
	// The beginnings of an INI file!!
	
	OTString strPath(SERVER_PATH_DEFAULT);
	
	{
		CSimpleIniA ini; // We're assuming this file is on the path.
		SI_Error rc = ini.LoadFile("./.ot_ini"); // todo: stop hardcoding. 
		
		if (rc >=0)
		{
			const char * pVal = ini.GetValue("paths", "server_path", strPath.Get()); // todo stop hardcoding.
			
			if (NULL != pVal)
			{
				strPath.Set(pVal);
				OTLog::vOutput(0, "Loaded Server data path from ini file: %s \n", strPath.Get());
			}
			else
			{
				strPath.Set(SERVER_PATH_DEFAULT);
				OTLog::vOutput(0, "Error reading Server data path from ini file. Has been set to: %s \n", strPath.Get());
			}
		}
		else 
		{
			strPath.Set(SERVER_PATH_DEFAULT);
			OTLog::vOutput(0, "Error loading ini file. Server data path has been set to: %s \n", strPath.Get());
		}
	}
	// -----------------------------------------------------------------------

	OTString strCAFile, strDHFile, strKeyFile, strSSLPassword;
	
	if (argc < 2)
	{
		OTLog::vOutput(0, "\n==> USAGE:    %s  <SSL-password>  <absolute_path_to_data_folder>\n\n"
#if defined (FELLOW_TRAVELER)					   
					   "(Password defaults to '%s' if left blank.)\n"
					   "(Folder defaults to '%s' if left blank.)\n"
#else
					   "(The test password is always 'test'.\n'cd data_folder' then 'pwd' to see the absolute path.)\n"
#endif
					   "\n\n", argv[0]
#if defined (FELLOW_TRAVELER)					   
					   , KEY_PASSWORD, 
					   strPath.Get()
#endif					   
					   );
		
#if defined (FELLOW_TRAVELER)
		strSSLPassword.Set(KEY_PASSWORD);
		OTLog::SetMainPath(strPath.Get());
#else
		exit(1);
#endif
	}
	else if (argc < 3)
	{
		OTLog::vOutput(0, "\n==> USAGE:  %s <SSL-password> <absolute_path_to_data_folder>\n\n"
#if defined (FELLOW_TRAVELER)					      
					   "(Folder defaults to '%s' if left blank.)\n"
#endif
					   "\n\n", argv[0]
#if defined (FELLOW_TRAVELER)
					   , strPath.Get()
#endif
					   );
		
#if defined (FELLOW_TRAVELER)					   
		strSSLPassword.Set(argv[1]);
		OTLog::SetMainPath(strPath.Get());
#else
		exit(1);
#endif
	}
	else 
	{
		strSSLPassword.Set(argv[1]);
		OTLog::SetMainPath(argv[2]);
	}	
	
	OTLog::vOutput(0, "Using as path to data folder:  %s\n", OTLog::Path());
	
	strCAFile. Format("%s%s%s", OTLog::Path(), OTLog::PathSeparator(), CA_FILE);
	strDHFile. Format("%s%s%s", OTLog::Path(), OTLog::PathSeparator(), DH_FILE);
	strKeyFile.Format("%s%s%s", OTLog::Path(), OTLog::PathSeparator(), KEY_FILE);
	
	
	
	// -----------------------------------------------------------------------
	
	// Initialize SSL -- This MUST occur before any Private Keys are loaded!
	SSL_library_init();
	SSL_load_error_strings();
	
	// Init loads up server's nym so it can decrypt messages sent in envelopes.
	// It also does various other initialization work.
	//
	// (Envelopes prove that ONLY someone who actually had the server contract,
	// and had loaded it into his wallet, could ever connect to the server or 
	// communicate with it. And if that person is following the contract, there
	// is only one server he can connect to, and one key he can use to talk to it.)
	
	OTLog::vOutput(0, 
				   "\nNow loading the server nym, which will also ask you for a password, to unlock\n"
				   "its private key. (Default password is \"%s\".)\n", KEY_PASSWORD);
	
	g_pServer->Init(); // Keys, etc are loaded here.
	
	// -----------------------------------------------------------------------

	// We're going to listen on the same port that is listed in our server contract.
	//
	//
	OTString	strHostname;	// The hostname of this server, according to its own contract.
	int			nPort=0;		// The port of this server, according to its own contract.
	
	OT_ASSERT_MSG(g_pServer->GetConnectInfo(strHostname, nPort),
				  "Unable to find my own connect info (which is in my server contract BTW.)\n");
	
	const int	nServerPort = nPort;
	
	//	int nSFSocketInit = SFSocketInit(socket,
	//									 strCAFile.Get(), 
	//									 strDHFile.Get(), 
	//									 strKeyFile.Get(),
	//									 strSSLPassword.Get(), 
	//									 NULL);
	
	// -----------------------------------------------------------------------
	
	// For re-occuring actions (like markets and payment plans.)
	//
	g_pServer->ActivateCron();

	// -----------------------------------
	
	//  Prepare our context and socket
	zmq::context_t context(1);
	zmq::socket_t socket(context, ZMQ_REP);

	OTString strBindPath; strBindPath.Format("%s%d", "tcp://*:", nServerPort);

	socket.bind(strBindPath.Get());

	// -----------------------------------------------------------------------
	// Let's get the HTTP server up and running...
	// Switching out XmlRpc for 0MQ (ZeroMQ)
	//
//	XmlRpc::setVerbosity(1);
//
//	// Create the server socket on the specified port
//	theXmlRpcServer.bindAndListen(nServerPort);
//
//	// Enable introspection, so clients can see what services this server supports. (Open Transactions...)
//	theXmlRpcServer.enableIntrospection(true);

	// -----------------------------------------------------------------------

	//  Initialize poll set
	zmq::pollitem_t items [] =
	{
	{ socket, 0, ZMQ_POLLIN, 0 },
	};

	do 
	{
		// The Server now processes certain things on a regular basis.
		// This method call is what gives it the opportunity to do that.
		
		g_pServer->ProcessCron();
		
		// -----------------------------------------------------------------------
		
		// Wait for client http requests (and process replies out to them.)
		//
//		theXmlRpcServer.work(10.0); // supposedly milliseconds -- but it's actually seconds.

		// process up to 10 requests, sleep for 1/10th second, check for shutdown, process cron, repeat.
		for (int i = 0; i < 10; i++) 
		{
			// Switching to ZeroMQ library.
			zmq::message_t message;

			zmq::poll(&items[0], 1, -1);

			if (items[0].revents & ZMQ_POLLIN)
			{
				socket.recv(&message);

				// Convert the ZMQ message to a std::string
				std::string str_Message;
				str_Message.reserve(message.size());
				str_Message.append(static_cast<const char *>(message.data()), message.size());

				//  Process task
				std::string str_Reply; // Output.
				ProcessMessage_ZMQ(str_Message, str_Reply);

				// Convert the std::string (reply) into a ZMQ message
				zmq::message_t reply (str_Reply.length());

				if (str_Reply.length() > 0)
					memcpy((void *) reply.data(), str_Reply.c_str(), str_Reply.length());

				//  Send reply back to client
				socket.send (reply);
			}
		} //  for		
		// -----------------------------------------------------------------------
		
		// Now go to sleep for a tenth of a second.
		// (Main loop processes ten times per second, currently.)
		
		OTLog::SleepMilliseconds(100); // 100 ms == (1 second / 10)
		
		// -----------------------------------------------------------------------

		if (g_pServer->IsFlaggedForShutdown())
		{
			OTLog::Output(0, "Server is shutting down gracefully....\n");
			break;
		}
    } while (1);
	
	
	// TODO: cleanup OpenSSL here.
	
#ifdef _WIN32
	WSACleanup();
#endif
	
	return 0;
}



void ProcessMessage_ZMQ(const std::string & str_Message, std::string & str_Reply)
{
	OT_ASSERT(NULL != g_pServer);
	
	if (str_Message.size() < 1)
		return;
	
	// --------------------
	
	// return value.
	std::string resultString = ""; // Whatever we put in this string is what will get returned.
	
	// First we grab the client's message
	OTASCIIArmor ascMessage;
	ascMessage.MemSet(str_Message.data(), str_Message.size());
	
	// ------------------
//	
//	OTPayload thePayload;
//	thePayload.SetPayloadSize(str_Message.size());	
//	memcpy((void*)thePayload.GetPayloadPointer(), str_Message.data(), str_Message.size());
	
	// ----------------------------------------------------------------------
	
//	OTLog::vError("Envelope: \n%s\n Size: %ld\n", ascMessage.Get(), ascMessage.GetLength());
	
	OTMessage theMsg, theReply; // we'll need these in a sec...
	
//	OTEnvelope theEnvelope(ascMessage); // Now the base64 is decoded and unpacked, and the envelope is in binary form again.
	OTEnvelope theEnvelope; // Now the base64 is decoded and the envelope is in binary form again.
	
	if (theEnvelope.SetAsciiArmoredData(ascMessage))
	{
		OTLog::Output(2, "Successfully retrieved envelope from ZMQ message...\n");
		
		OTString strEnvelopeContents;
		
//		OTString strPubkeyPath("TESTPUBKEY.txt");
//		g_pServer->GetServerNym().SavePublicKey(strPubkeyPath);
		
		// Decrypt the Envelope.    
		if (theEnvelope.Open(g_pServer->GetServerNym(), strEnvelopeContents)) // now strEnvelopeContents contains the decoded message.
		{
			// All decrypted--now let's load the results into an OTMessage.
			// No need to call theMsg.ParseRawFile() after, since
			// LoadContractFromString handles it.
			//
			if (strEnvelopeContents.Exists() && theMsg.LoadContractFromString(strEnvelopeContents))
			{
				
				// In case you want to see all the incoming messages...
				//					OTLog::vOutput(0, "%s\n\n", strEnvelopeContents.Get());
				
				// By constructing this without a socket, I put it in XmlRpc/http mode, instead of tcp/ssl.
				OTClientConnection theClient(*g_pServer); 
				
				// By optionally passing in &theClient, the client Nym's public key will be
				// set on it whenever verification is complete. (So for the reply, I'll 
				// have the key and thus I'll be able to encrypt reply to the recipient.)
				if (g_pServer->ProcessUserCommand(theMsg, theReply, &theClient))	
				{	
					// At this point the reply is ready to go, and theClient has the public key of the recipient...
					
					OTLog::vOutput(0, "Successfully processed user command: %s.\n", theMsg.m_strCommand.Get());
					
					// The transaction is now processed, and the server's reply message is in theReply.
					// Let's seal it up to the recipient's nym (in an envelope) and send back to the user...
					OTEnvelope theRecipientEnvelope;
					
					bool bSealed = theClient.SealMessageForRecipient(theReply, theRecipientEnvelope);
					
					if (bSealed)
					{
//						OTPayload theReplyPayload;
//						theReplyPayload.SetEnvelope(theRecipientEnvelope);
//						
//						resultString = ascReply.Get();
//						resultString.assign(theReplyPayload.GetPayloadPointer(), theReplyPayload.GetPayloadSize());
						
						OTASCIIArmor ascReply;
						if (theRecipientEnvelope.GetAsciiArmoredData(ascReply));
							resultString.assign(ascReply.Get(), ascReply.GetLength());
					}
					else
						OTLog::Output(0, "Unable to seal envelope in ProcessMessage_ZMQ.\n");
				}
				else
					OTLog::Output(0, "Unable to process user command in ProcessMessage_ZMQ.\n");
			}
			else 
				OTLog::Error("Error loading message from envelope contents. ProcessMessage_ZMQ.\n");
		}
		else 
			OTLog::Error("Unable to open envelope. ProcessMessage_ZMQ.\n");
	}
	else 
		OTLog::Error("Error retrieving envelope from ProcessMessage_ZMQ.\n");

	// ----------------------------------------------------------------------
	
	str_Reply = resultString;	
}















































