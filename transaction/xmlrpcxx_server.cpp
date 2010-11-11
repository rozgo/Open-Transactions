/************************************************************************************
 *    
 *  xmlrpcxx_server.cpp  (The web-services implementation of the Open Transactions server.)
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

#define SERVER_PATH_DEFAULT	"/Users/REDACTED/Projects/Open-Transactions/transaction/data_folder"
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

// I have XmlRpc installed in /usr/local/include/XmlRpc and /usr/local/lib/XmlRpc
// (In order to avoid naming conflicts with other similar libraries on my system.)
#if defined(linux)
#include "XmlRpc.h"
#else
#include "XmlRpc/XmlRpc.h"
#endif


#include "main.h"

#include "OTMessage.h"
#include "OTEnvelope.h"

#include "OTServer.h"

#include "OTLog.h"


// -------------------------------------------------------------

using namespace XmlRpc;


// The HTTP server
XmlRpcServer theXmlRpcServer; // This object handles the network transport. (Over HHTP, in this case.)


// The Open Transactions server
OTServer * g_pServer = NULL;  // This object handles all the actual OT notarization processing.


// -------------------------------------------------------------

// This function is called for every OT Message that is sent for processing.
// One argument is passed, and a result string is passed back.
//
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


// ----------------------------------------------------------------------


// The MAIN function for the server software, which starts up the XmlRpc (http server), 
// as well as Open Transactions.
//
int main(int argc, char* argv[])
{
	OTLog::vOutput(0, "\n\nWelcome to Open Transactions... Test Server -- version %s\n"
				   "(transport build: OTMessage -> XmlRpc -> HTTP)\n\n", OTLog::Version());
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
	
	OTString strCAFile, strDHFile, strKeyFile, strSSLPassword;
	
	if (argc < 2)
	{
		OTLog::vOutput(0, "Usage:  transaction <SSL-password> <data_folder>\n\n"
					   "(Password DEFAULTS to '%s' if left blank on the command line.)\n"
					   "(Folder DEFAULTS to '%s' if left blank.)\n", KEY_PASSWORD, SERVER_PATH_DEFAULT);
		
		strSSLPassword.Set(KEY_PASSWORD);
		OTLog::SetMainPath(SERVER_PATH_DEFAULT);
	}
	else if (argc < 3)
	{
		OTLog::vOutput(0, "Usage:  transaction <SSL-password> <data_folder>\n\n"
					   "(Folder DEFAULTS to '%s' if left blank.)\n", SERVER_PATH_DEFAULT);
		
		strSSLPassword.Set(argv[1]);
		OTLog::SetMainPath(SERVER_PATH_DEFAULT);
	}
	else 
	{
		strSSLPassword.Set(argv[1]);
		OTLog::SetMainPath(argv[2]);
	}	
	
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
	
	// -----------------------------------------------------------------------
	
	// Let's get the HTTP server up and running...
	
	XmlRpc::setVerbosity(1);

	// Create the server socket on the specified port
	theXmlRpcServer.bindAndListen(nServerPort);

	// Enable introspection, so clients can see what services this server supports. (Open Transactions...)
	theXmlRpcServer.enableIntrospection(true);

	// -----------------------------------------------------------------------

	do 
	{
		// The Server now processes certain things on a regular basis.
		// This method call is what gives it the opportunity to do that.
		
		g_pServer->ProcessCron();
		
		// -----------------------------------------------------------------------
		
		// Wait for client http requests (and process replies out to them.)
		//
		theXmlRpcServer.work(10.0); // supposedly milliseconds -- but it's actually seconds.
		
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















































