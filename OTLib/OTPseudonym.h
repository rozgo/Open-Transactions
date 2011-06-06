/*************************************************************
 *    
 *  OTPseudonym.h
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


#ifndef __OTPSEUDONYM_H__
#define __OTPSEUDONYM_H__

#include <cstdio>


#include <map>
#include <deque>
#include <string>
#include <fstream>

#include "OTString.h"
#include "OTData.h"
#include "OTIdentifier.h"

#include "OTASCIIArmor.h"
#include "OTAsymmetricKey.h"

/*
 
 I need to map transaction server ID, each for a pointer to deque of long.
 

 */

class OTItem;
class OTTransaction;
class OTMessage;

typedef std::deque<OTMessage *>		dequeOfMail;

typedef std::map<std::string, long>	mapOfRequestNums;

typedef std::deque<long>							dequeOfTransNums;
typedef std::map<std::string, dequeOfTransNums *>	mapOfTransNums;

class OTPseudonym
{
private:
	OTString		m_strName;      // Used by the wallet so the nym is easily identified by the user
									// The internals, and server, prefer nymID to name.	
	OTString		m_strNymfile;   // This contains the request numbers and other user acct info. XML.
									// Client-side only, since the server uses nymID for filenames
	OTString		m_strCertfile;  // Filename for pem file that contains the x509 Certificate. ----BEGIN etc...
									// Client-side only for now.

	OTString		m_strVersion;   // This goes with the Nymfile
	
	OTASCIIArmor	m_ascCert;		// Just the ascii-armor portion without BEGIN and END
	
	OTIdentifier	m_nymID;		// hashed public key
	

	OTAsymmetricKey *m_pkeyPublic;	// This nym's public key
	

	OTAsymmetricKey *m_pkeyPrivate;	// This nym's private key

	dequeOfMail		m_dequeMail;	// Any mail messages received by this Nym. (And not yet deleted.)
	dequeOfMail		m_dequeOutmail;	// Any mail messages sent by this Nym. (And not yet deleted.)
		
	mapOfRequestNums m_mapRequestNum;	// Whenever this user makes a request to a transaction server
										// he must use the latest request number. Each user has a request
										// number for EACH transaction server he accesses.
	mapOfTransNums	m_mapTransNum;	// Each Transaction Request must be accompanied by a fresh transaction #,
									// one that has previously been issued to the Nym by the Server. This list
									// is used so that I know WHICH transaction numbers I still have to USE.
	
	mapOfTransNums	m_mapIssuedNum;	// If the server has issued me (1,2,3,4,5) and I have already used 1-3,
									// then (4,5) are the only remaining numbers on the ABOVE list, but the
									// entire (1,2,3,4,5) are still on THIS list--each only to be removed 
									// when I have ACCEPTED THE RECEIPT IN MY NYMBOX FOR EACH ONE. This list
									// is so I can do agreements with the server concerning which RECEIPTS I'VE ACCEPTED.
	
public:
	
	// ------------------------------------------------
	
	inline OTString &	GetNymName() { return m_strName; }
	inline void			SetNymName(const OTString & strName) { m_strName = strName; }
	
	OTPseudonym();
	OTPseudonym(const OTIdentifier & nymID);
	OTPseudonym(const OTString & strNymID);
	OTPseudonym(const OTString & name, const OTString & filename, const OTString & nymID);
	virtual ~OTPseudonym();
	
	void Initialize();
	void ReleaseTransactionNumbers();
	
	bool VerifyPseudonym() const;

	
	// use this to actually generate a new key pair and assorted nym files.
	//
	bool GenerateNym();

	// ---------------------------------------------
	
	// Some messages require "transaction agreement" as opposed to "balance agreement."
	// That is, cases where only transactions change and not balances.
	//
	
	OTItem * GenerateTransactionStatement(const OTTransaction & theOwner); // like balance agreement

	// ---------------------------------------------
		
	// This version WILL handle the bookends -----BEGIN PUBLIC KEY------ 
	bool SetPublicKey(const OTString & strKey, bool bEscaped=true);
	
	// This version WILL handle the bookends: -----BEGIN CERTIFICATE------ 
	// It also handles the escaped version:   - -----BEGIN CERTIFICATE-----
	bool SetCertificate(const OTString & strCert, bool bEscaped=true);
	
	// This will set the public key on this Nym 
	// based on the public key as it appears in an
	// ascii-armored string.
	bool SetPublicKey(const OTASCIIArmor & strKey);
	
	
	// The signer is whoever wanted to make sure these nym files haven't changed.
	// Usually that means the server nym.  Most of the time, m_nymServer will be used as signer.
	bool LoadSignedNymfile(OTPseudonym & SIGNER_NYM);
	bool SaveSignedNymfile(OTPseudonym & SIGNER_NYM);
	
	bool LoadNymfile(const char * szFilename=NULL);
	bool LoadFromString(const OTString & strNym);

	bool LoadPublicKey();
	bool Loadx509CertAndPrivateKey();
	
//	bool SavePseudonymWallet(FILE * fl) const;
	bool SavePseudonymWallet(OTString & strOutput) const;
	bool SavePseudonymWallet(std::ofstream & ofs) const;

	bool SavePublicKey(const OTString & strPath) const;
//	bool SavePublicKey(FILE * fl) const;
	bool SavePublicKey(std::ofstream & ofs) const;

	bool SavePseudonym(); // saves to filename m_strNymfile
	bool SavePseudonym(const char * szFoldername, const char * szFilename);
	bool SavePseudonym(OTString & strNym);
//	bool SavePseudonym(FILE * fl);
	bool SavePseudonym(std::ofstream & ofs);

	bool SetIdentifierByPubkey();
	
	void GetIdentifier(OTIdentifier & theIdentifier) const;
	void SetIdentifier(const OTIdentifier & theIdentifier);
	
	void GetIdentifier(OTString & theIdentifier) const;
	void SetIdentifier(const OTString & theIdentifier);

	void HarvestTransactionNumbers(OTPseudonym & SIGNER_NYM, OTPseudonym & theOtherNym, bool bSave=true); // OtherNym is used as container for server to send us new transaction numbers
	void HarvestIssuedNumbers(OTPseudonym & SIGNER_NYM, OTPseudonym & theOtherNym, bool bSave=false); // OtherNym is used as container for us to send list of issued numbers to the server (for balance agreement)

	void IncrementRequestNum(OTPseudonym & SIGNER_NYM, const OTString & strServerID); // Increment the counter or create a new one for this serverID starting at 1
	void OnUpdateRequestNum(OTPseudonym & SIGNER_NYM, const OTString & strServerID, long lNewRequestNumber); // if the server sends us a @getRequest
	bool GetCurrentRequestNum(const OTString & strServerID, long &lReqNum); // get the current request number for the serverID

	inline mapOfTransNums & GetMapTransNum() { return m_mapTransNum; }
	inline mapOfTransNums & GetMapIssuedNum() { return m_mapIssuedNum; }

	void RemoveAllNumbers();
	
	bool	IsRegisteredAtServer(const OTString & strServerID); // You can't go using a Nym at a certain server, if it's not registered there...
	
	// HIGH LEVEL:
	bool	AddTransactionNum(OTPseudonym & SIGNER_NYM, const OTString & strServerID, long lTransNum, bool bSave); // We have received a new trans num from server. Store it.
	bool	GetNextTransactionNum(OTPseudonym & SIGNER_NYM, const OTString & strServerID, long &lTransNum); // Get the next available transaction number for the serverID passed. Saves.
	bool	RemoveIssuedNum(OTPseudonym & SIGNER_NYM, const OTString & strServerID, const long & lTransNum, bool bSave); // SAVE OR NOT (your choice)

	bool	VerifyIssuedNum(const OTString & strServerID, const long & lTransNum); // verify user is still responsible for (signed for) a certain trans# that was previous issued to him. (i.e. it's been used, but not yet accepted receipt through inbox.)
	bool	VerifyTransactionNum(const OTString & strServerID, const long & lTransNum); // server verifies that nym has this TransNum available for use.

	// These two functions are for when you re-download your nym/account/inbox/outbox, and you
	// need to verify it against the last signed receipt to make sure you aren't getting screwed.
	bool VerifyIssuedNumbersOnNym(OTPseudonym & THE_NYM);
	bool VerifyTransactionStatementNumbersOnNym(OTPseudonym & THE_NYM);

	// -------------------------------------
	// These functions are for transaction numbers that were assigned to me, 
	// until I accept the receipts or put stop payment onto them.
	int		GetIssuedNumCount(const OTIdentifier & theServerID); // count
	long	GetIssuedNum(const OTIdentifier & theServerID, int nIndex); // index
	
	bool	AddIssuedNum(const OTString & strServerID, const long & lTransNum); // doesn't save
	
	bool	RemoveIssuedNum(OTPseudonym & SIGNER_NYM, const OTString & strServerID, const long & lTransNum); // saves
	bool	RemoveIssuedNum(const OTString & strServerID, const long & lTransNum); // doesn't save

	// -------------------------------------
	// These functions are for transaction numbers that I still have available to use.
	//
	int GetTransactionNumCount(const OTIdentifier & theServerID); // count
	long GetTransactionNum(const OTIdentifier & theServerID, int nIndex); // index
	
	bool AddTransactionNum(const OTString & strServerID, const long lTransNum); // doesn't save
		
	bool RemoveTransactionNum(OTPseudonym & SIGNER_NYM, const OTString & strServerID, const long & lTransNum); // server removes spent number from nym file. Saves.
	bool RemoveTransactionNum(const OTString & strServerID, const long & lTransNum); // doesn't save.
	
	// ---------------------------------------------
	
	// The "issued" numbers and the "transaction" numbers both use these functions
	// to do the actual work (just avoiding code duplication.)
	bool VerifyGenericNum(mapOfTransNums & THE_MAP, const OTString & strServerID, const long & lTransNum);
	
	bool RemoveGenericNum(mapOfTransNums & THE_MAP, OTPseudonym & SIGNER_NYM, const OTString & strServerID, const long & lTransNum); // saves
	bool RemoveGenericNum(mapOfTransNums & THE_MAP, const OTString & strServerID, const long & lTransNum); // doesn't save
	
	bool AddGenericNum(mapOfTransNums & THE_MAP, const OTString & strServerID, const long lTransNum); // doesn't save
	
	int  GetGenericNumCount(mapOfTransNums & THE_MAP, const OTIdentifier & theServerID); 
	
	// -------------------------------------
	
	// Whenever a Nym receives a message via his Nymbox, and then the Nymbox is processed, (which happens automatically)
	// that processing will drop all mail messages into this deque for safe-keeping, after Nymbox is cleared.
	//
	void		AddMail(OTMessage & theMessage); // a mail message is the original OTMessage from the sender, transported via Nymbox of recipient (me).
	int			GetMailCount(); // How many mail messages does this Nym currently store?
	OTMessage *	GetMailByIndex(const int nIndex); // Get a specific piece of mail, at a specific index.
	bool		RemoveMailByIndex(const int nIndex); // if returns false, mail index was bad (or something else must have gone seriously wrong.)
	
	void		ClearMail(); // called by the destructor. (Not intended to erase messages from local storage.)
	
	// -------------------------------------
	
	// Whenever a Nym sends a message, a copy is dropped into his Outmail.
	//
	void		AddOutmail(OTMessage & theMessage); // a mail message is the original OTMessage that this Nym sent.
	int			GetOutmailCount(); // How many outmail messages does this Nym currently store?
	OTMessage *	GetOutmailByIndex(const int nIndex); // Get a specific piece of outmail, at a specific index.
	bool		RemoveOutmailByIndex(const int nIndex); // if returns false, outmail index was bad (or something else must have gone seriously wrong.)
	
	void		ClearOutmail(); // called by the destructor. (Not intended to erase messages from local storage.)
	
	// -------------------------------------
	
	const OTAsymmetricKey & GetPublicKey() const;
	const OTAsymmetricKey & GetPrivateKey() const;
	
	void DisplayStatistics(OTString & strOutput);
};

#endif // __OTPSEUDONYM_H__









































