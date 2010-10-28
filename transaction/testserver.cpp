

/************************************************************************************
 *    
 *  server.cpp  (as opposed to OTServer, this is the project's encapsulation.)
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


#ifdef _WIN32
#include "OTLib/stdafx.h"
#endif

#include <cstring>
#include <cstdio>

extern "C" 
{
#ifdef _WIN32
#include <WinSock.h>
#else
#include <netinet/in.h>
#endif

#include "SSL-Example/SFSocket.h"
}

#include "OTLog.h"


// NOTE:  The PATH and the PASSWORD are configurable on the command line!!!
//
//        They are only here for convenience, so I don't have to type them
//        over and over again.  You can blank them out if you want, or set
//        them to whatever is convenient for you on your system.
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

// NOTE: this SSL connection is entirely different from the user's cert/pubkey that he uses for his UserID while 
// talking to the server. I may be using the same key for that, but this code here is not about my wallet talking
// to its mint. Rather, it's about an SSL client app talking to an SSL server, at a lower layer, before my app's
// intelligence takes over.  Just like when you use SSH to connect somewhere on a terminal. There is some immediate
// key negotiation going on. Once connected, you might run software that asks you for a public key, which could be
// AN ENTIRELY DIFFERENT PUBLIC KEY. THAT is where, metaphorically, your Public Key / User ID comes into play.


#include <list>

#include "main.h"

#include "OTMessage.h"
#include "OTServer.h"
#include "OTClientConnection.h"

#include "OTLog.h"





/*
 if (bSuccess = theServer.ProcessUserCommand(theMessage, theReply))
 {
	 OTLog::vOutput(1, "Successfully processed user command: %s\n", theMessage.m_strCommand.Get());
	 ProcessReply(ssl, theReply);
 }
 else
 {
	 OTLog::Output(1, "Unable to process user command in XML, or missing payload, in ProcessMessage.\n");
 } 
 
 */



int main (int argc, char **argv) 
{
	OTLog::vOutput(0, "\n\nWelcome to Open Transactions... Test Server -- version %s\n"
				   "(transport build: OTMessage -> TCP -> SSL)\n"
				   "NOTE: IF YOU PREFER TO USE XmlRpc with Http transport, then rebuild using:\n"
				   "\"make -f Makefile.rpc\" (but make sure the client is built the same way.)\n\n", 
				   OTLog::Version());
	
	// -----------------------------------------------------------------------
	
	// This object handles all the actual transaction notarization details.
	// (This file you are reading is a wrapper for OTServer, which adds the transport layer.)
	OTServer theServer;

	// -----------------------------------------------------------------------
	
#ifdef _WIN32
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD( 2, 2 );
	int nWSA = WSAStartup( wVersionRequested, &wsaData );
	OT_ASSERT_MSG(0 != nWSA, "Error calling WSAStartup.\n");	
#endif

	OTLog::vOutput(0, "\n\nWelcome to Open Transactions, version %s.\n\n", OTLog::Version());
	
	// -----------------------------------------------------------------------

	OTString strCAFile, strDHFile, strKeyFile, strSSLPassword;

	if (argc < 2)
	{
		OTLog::vOutput(0, "Usage:  transaction <SSL-password> <data_folder path>\n\n"
				"(Password defaults to '%s' if left blank on the command line.)\n"
				"(Folder defaults to '%s' if left blank.)\n", KEY_PASSWORD, SERVER_PATH_DEFAULT);
		
		strSSLPassword.Set(KEY_PASSWORD);
		OTLog::SetMainPath(SERVER_PATH_DEFAULT);
	}
	else if (argc < 3)
	{
		OTLog::vOutput(0, "Usage:  transaction <SSL-password> <data_folder path>\n\n"
				"(Folder defaults to '%s' if left blank.)\n", SERVER_PATH_DEFAULT);
		
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

	// Init loads up server's nym so it can decrypt messages sent in envelopes.
	// It also does various other initialization work.
	//
	// (Envelopes prove that ONLY someone who actually had the server contract,
	// and had loaded it into his wallet, could ever connect to the server or 
	// communicate with it. And if that person is following the contract, there
	// is only one server he can connect to, and one key he can use to talk to it.)
	
	OTLog::Output(0, 
				  "\n\nNow loading the server nym, which will also ask you for a password, to unlock\n"
				  "its private key. (Default password is \"test\".)\n");

	// Initialize SSL -- This MUST occur before any Private Keys are loaded!
    SFSocketGlobalInit(); // Any app that uses OT has to initialize SSL first.

	theServer.Init(); // Keys, etc are loaded here.

	// -----------------------------------------------------------------------

	// We're going to listen on the same port that is listed in our server contract.
	//
	//
	OTString	strHostname;	// The hostname of this server, according to its own contract.
	int			nPort=0;		// The port of this server, according to its own contract.

	OT_ASSERT_MSG(theServer.GetConnectInfo(strHostname, nPort),
				  "Unable to find my own connect info (which is in my server contract BTW.)\n");
	
	const int	nServerPort = nPort;
	
	// -----------------------------------------------------------------------
	
	
	SFSocket *socket = NULL;
	listOfConnections theConnections;
	
    // Alloc Socket
	socket = SFSocketAlloc();
	OT_ASSERT_MSG(NULL != socket, "SFSocketAlloc Failed\n");
	
    // Initialize SSL Socket
	int nSFSocketInit = SFSocketInit(socket,
					 strCAFile.Get(), 
					 strDHFile.Get(), 
					 strKeyFile.Get(),
					 strSSLPassword.Get(), 
									 NULL);
	
	OT_ASSERT_MSG(nSFSocketInit >= 0, "SFSocketInit Context Failed\n");
	
    // Listen on Address/Port
	int nSFSocketListen = SFSocketListen(socket, INADDR_ANY, nServerPort);
	
	OT_ASSERT_MSG(nSFSocketListen >= 0, "nSFSocketListen Failed\n");
	
	
	theServer.ActivateCron();
	
    do 
	{
        SFSocket * clientSocket = NULL;

        // Accept Client Connection
        if (NULL != (clientSocket = SFSocketAccept(socket)))
		{
			OTClientConnection * pClient = new OTClientConnection(*clientSocket, theServer);
			theConnections.push_back(pClient);
			OTLog::Output(0, "Accepting new connection.\n");
		}
		
		// READ THROUGH ALL CLIENTS HERE, LOOP A LIST
		// AND process in-buffer onto our list of messages.
		
		OTClientConnection * pConnection = NULL;
		
		for (listOfConnections::iterator ii = theConnections.begin(); 
			 ii != theConnections.end(); ++ii)
		{
			if (pConnection = *ii)
			{
				// Here we read the bytes from the pipe into the client's buffer
				// As necessary this function also processes those bytes into OTMessages
				// and adds them to the Input List for that client.
				pConnection->ProcessBuffer();
			}
		}
		
		
		
		// Now loop through them all again, and process their messages onto the reply list.
		
		pConnection = NULL;
		
		for (listOfConnections::iterator ii = theConnections.begin(); 
			 ii != theConnections.end(); ++ii)
		{
			if (pConnection = *ii)
			{
				OTMessage * pMsg = NULL;
				
				while (pMsg = pConnection->GetNextInputMessage())
				{
					OTMessage * pReply = new OTMessage;
					
					OT_ASSERT(NULL != pReply);
					
					if (theServer.ProcessUserCommand(*pMsg, *pReply, pConnection))
					{
						OTLog::vOutput(0, "Successfully processed user command: %s.\n", 
								pMsg->m_strCommand.Get());
						
						pConnection->AddToOutputList(*pReply);
					}
					else
					{
						OTLog::Output(0, "Unable to process user command in XML, or missing payload, in main.\n");
						delete pReply;
						pReply = NULL;
					}
					
					// I am responsible to delete this here.
					delete pMsg;
					pMsg = NULL;
				}
			}
		}
		
		
		// Now loop through them all again, and process their replies down the pipe
		
		pConnection = NULL;
		
		for (listOfConnections::iterator ii = theConnections.begin(); 
			 ii != theConnections.end(); ++ii)
		{
			if (pConnection = *ii)
			{
				OTMessage * pMsg = NULL;
				
				while (pMsg = pConnection->GetNextOutputMessage())
				{
					pConnection->ProcessReply(*pMsg);
						
					// I am responsible to delete this here.
					delete pMsg;
					pMsg = NULL;
				}
			}
		}
		
		
		
		
		
		// The Server now processes certain things on a regular basis.
		// This method call is what gives it the opportunity to do that.
	
		theServer.ProcessCron();
		
		
		
		
		// Now go to sleep for a tenth of a second.
		// (Main loop processes ten times per second, currently.)
		
		OTLog::SleepMilliseconds(100); // 100 ms == (1 second / 10)
		
		
		
		
    } while (1);

    // Close and Release Socket Resources
    SFSocketRelease(socket);

#ifdef _WIN32
	WSACleanup();
#endif

    return(0);
}

/*
 int do_server_loop(SSL *ssl)
 {
 int  err, nread;
 union u_header theCMD;
 int retVal = 0;
 int bClosed = 0;
 
 do
 {
 // clear the buffer.	
 memset((void *)theCMD.buf, 0, OT_CMD_HEADER_SIZE);
 
 for (nread = 0;  nread < OT_CMD_HEADER_SIZE;  nread += err)
 {
 err = SSL_read(ssl, theCMD.buf + nread, OT_CMD_HEADER_SIZE - nread);
 if (err <= 0)
 {
 bClosed = 1;
 break;
 }
 }
 
 if (bClosed)
 break;
 
 OTLog::vOutput(0, "\n===> Processing header from client message. First 5 bytes are: %d %d %d %d %d...\n",
 theCMD.buf[0],theCMD.buf[1],theCMD.buf[2],theCMD.buf[3],theCMD.buf[4]);
 
 ProcessMessage(ssl, &theCMD);
 }
 while (!(retVal = ((SSL_get_shutdown(ssl) & SSL_RECEIVED_SHUTDOWN) ? 1 : 0)));
 return retVal;
 }
 
 

*/


























