/************************************************************************************
 *    
 *  OTLog.h
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
 *        continue to operate.
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


// The long-awaited logging class.

#ifndef __OTLOG_H__
#define __OTLOG_H__

// x must be a boolean expression

#define    OT_ASSERT(x)			( (false == (x)) ? OTLog::Assert(__FILE__, __LINE__)		: (1))
#define    OT_ASSERT_MSG(x, s)	( (false == (x)) ? OTLog::Assert(__FILE__, __LINE__, (s))	: (1))

#include "OTString.h"


class OTLog
{
private:
	OTLog();

	static int		__CurrentLogLevel;
	static OTString	__Version;			// current version of Open Transactions is stored here.

	static OTString	__OTPath;			// Path to either server or client directory. (Whichever is running.)
	static OTString	__OTPathSeparator;	// double-backslash in Windows, forward-slash in others.
	
	static OTString __OTCronFolder;		// Just the folder name for the cron records (trades, payment plans...)
	static OTString __OTNymFolder;		// Just the folder name
	static OTString __OTAccountFolder;	// Just the folder name
	static OTString __OTUserAcctFolder;	// Just the folder name
	static OTString __OTInboxFolder;	// Just the folder name
	static OTString __OTOutboxFolder;	// Just the folder name
	static OTString __OTCertFolder;		// Just the folder name
	static OTString __OTPubkeyFolder;	// Just the folder name
	static OTString __OTContractFolder;	// Just the folder name
	static OTString __OTMintFolder;		// Just the folder name
	static OTString __OTSpentFolder;	// Just the folder name
	static OTString __OTPurseFolder;	// Just the folder name
	static OTString __OTMarketFolder;	// Just the folder name
	
public:	
	~OTLog();
	
	static void SleepSeconds(long lSeconds);
	static void SleepMilliseconds(long lMilliseconds);
	
	// Used for making sure that certain necessary folders actually exist. (Creates them otherwise.)
	// Creates inside Path(). IE:  <path>/szFolderName
	static bool ConfirmOrCreateFolder(const char * szFolderName);
	static bool ConfirmFile(const char * szFileName);
	static bool ConfirmExactPath(const char * szFileName);

	
	// OTPath is where all the subdirectories can be found.
	// If the server is what's running, then it's the server folder.
	// Otherwise it's the client folder.
	
	// ------------------------------------------------------------
	
	static const char *	Path()			{ return __OTPath.Get(); }
	static const char *	PathSeparator()	{ return __OTPathSeparator.Get(); }
	
	static void SetMainPath(const char * szPath) { __OTPath.Set(szPath); }
	static void SetPathSeparator(const char * szPathSeparator) { __OTPathSeparator.Set(szPathSeparator); }
	
	// ------------------------------------------------------------
	
	static const char *	CronFolder()				{ return __OTCronFolder.Get(); }
	static void SetCronFolder(const char * szPath)	{ __OTCronFolder.Set(szPath); }
	
	static const char *	NymFolder()				{ return __OTNymFolder.Get(); }
	static void SetNymFolder(const char * szPath)	{ __OTNymFolder.Set(szPath); }
	
	static const char *	AccountFolder()				{ return __OTAccountFolder.Get(); }
	static void SetAccountFolder(const char * szPath){ __OTAccountFolder.Set(szPath); }
	
	static const char *	UserAcctFolder()				{ return __OTUserAcctFolder.Get(); }
	static void SetUserAcctFolder(const char * szPath){ __OTUserAcctFolder.Set(szPath); }
	
	static const char *	InboxFolder()				{ return __OTInboxFolder.Get(); }
	static void SetInboxFolder(const char * szPath)	{ __OTInboxFolder.Set(szPath); }
	
	static const char *	OutboxFolder()				{ return __OTOutboxFolder.Get(); }
	static void SetOutboxFolder(const char * szPath)	{ __OTOutboxFolder.Set(szPath); }
	
	static const char *	CertFolder()				{ return __OTCertFolder.Get(); }
	static void SetCertFolder(const char * szPath)	{ __OTCertFolder.Set(szPath); }
	
	static const char *	PubkeyFolder()				{ return __OTPubkeyFolder.Get(); }
	static void SetPubkeyFolder(const char * szPath){ __OTPubkeyFolder.Set(szPath); }
	
	static const char *	ContractFolder()			{ return __OTContractFolder.Get(); }
	static void SetContractFolder(const char * szPath)	{ __OTContractFolder.Set(szPath); }
	
	static const char *	MintFolder()			{ return __OTMintFolder.Get(); }
	static void SetMintFolder(const char * szPath)	{ __OTMintFolder.Set(szPath); }
	
	static const char *	SpentFolder()				{ return __OTSpentFolder.Get(); }
	static void SetSpentFolder(const char * szPath)	{ __OTSpentFolder.Set(szPath); }
	
	static const char *	PurseFolder()				{ return __OTPurseFolder.Get(); }
	static void SetPurseFolder(const char * szPath)	{ __OTPurseFolder.Set(szPath); }
	
	static const char *	MarketFolder()				{ return __OTMarketFolder.Get(); }
	static void SetMarketFolder(const char * szPath){ __OTMarketFolder.Set(szPath); }
	
	// ------------------------------------------------------------
	
	static const char * Version() { return __Version.Get(); }
	
	static int			GetLogLevel() { return __CurrentLogLevel; }
	static void			SetLogLevel(int nLevel) { __CurrentLogLevel = nLevel; }
	
	// For things that represent internal inconsistency in the code. 
	// Normally should NEVER happen even with bad input from user.
	// (Don't call this directly. Use the above #defined macro instead.)
	static int Assert(const char * szFilename, int nLinenumber); // assert
	static int Assert(const char * szFilename, int nLinenumber, const char * szMessage); // assert

	// Output() logs normal output, which carries a verbosity level.
	//
	// If nVerbosity of a message is 0, the message will ALWAYS log. (ALL output levels are higher or equal to 0.)
	// If nVerbosity is 1, the message will run only if __CurrentLogLevel is 1 or higher.
	// If nVerbosity if 2, the message will run only if __CurrentLogLevel is 2 or higher.
	// Etc.
	// THEREFORE: The higher the verbosity level for a message, the more verbose the
	// software must be configured in order to display that message.
	//
	// Default verbosity level for the software is 0, and output that MUST appear on
	// the screen should be set at level 0. For output that you don't want to see as often,
	// set it up to 1. Set it up even higher for the really verbose stuff (e.g. only if you
	// really want to see EVERYTHING.)
	
	static void Output(int nVerbosity, const char * szOutput); // stdout
	static void Output(int nVerbosity, OTString & strOutput); // stdout
	static void vOutput(int nVerbosity, const char *szOutput, ...);

	// This logs an error condition, which usually means bad input from the user, or a file wouldn't open,
	// or something like that.  This contrasted with Assert() which should NEVER actually happen. The software
	// expects bad user input from time to time. But it never expects a loaded mint to have a NULL pointer.
	// The bad input would log with Error(), whereas the NULL pointer would log with Assert();
	static void Error(const char * szError); // stderr
	static void Error(OTString & strError); // stderr
	static void vError(const char * szError, ...); // stderr
};

#endif // __OTLOG_H__
