/************************************************************************************
 *    
 *  OTMint.h
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


#ifndef __OTMINT_H__
#define __OTMINT_H__

#include <ctime>

#include "OTContract.h"
#include "OTEnvelope.h"
#include "OTASCIIArmor.h"
#include "OTToken.h"
#include "OTAccount.h"


class OTMint : public OTContract
{
protected:
	virtual int ProcessXMLNode(irr::io::IrrXMLReader*& xml);
		
	void InitMint();

	mapOfArmor		m_mapPrivate;	// An ENVELOPE. You need to pass the Pseudonym to every method that uses this. Private.
									// Then you have to set it into an envelope and then open it using the Nym. Encrypted.
	mapOfArmor		m_mapPublic;	// An Ascii-armored string of the mint Public information. Base64-encoded only.
	
	
	OTIdentifier	m_ServerID;		// The Server ID, (a hash of the server contract whose public key is m_keyPublic)
	OTIdentifier	m_ServerNymID;	// The Nym ID of the Server, whose public key is m_keyPublic
	
	OTAsymmetricKey m_keyPublic;	// The server's public key.
	
	OTIdentifier	m_AssetID;		// Each Asset type has its own mint.
	
	int				m_nDenominationCount; // How many denominations of the currency are issued by this Mint?
										  // (Each requires its own key pair.)

	bool			m_bSavePrivateKeys; // Determines whether it serializes private keys (no if true)
	
	
	// --- MINT SERIES with EXPIRATION DATES ------------------
	
	int				m_nSeries;		// Each series of the mint has a valid from and to date. Series should rotate.
									// (That is, the new one should be introduced halfway through the validity period
									// of the current one, and so on...)
	
	time_t			m_VALID_FROM;	// All tokens generated by this series will have the same From and To dates.
	time_t			m_VALID_TO;		// This way they cannot be tracked by expiration date.
	
	time_t			m_EXPIRATION;	// The Mint itself expires before the tokens do. (As the new series rotates in...)
	
	OTIdentifier	m_CashAccountID;// The Account ID for the cash reserve account. (Pointer below.)
	
	OTAccount	*	m_pReserveAcct;	// When you withdraw cash, the Mint removes X dollars from your account, then
									// it puts those X dollars into this reserve account, and then issues you the 
									// blinded tokens. When the tokens are deposited again, the money comes back out
									// of the same reserve account and goes into the depositor's account. This way, 
									// all tokens will have 1-for-1 funds backing them, and any funds left over after
									// the tokens expire, is the server operator's money to keep!
	
public:
	
	inline	int		GetSeries()		const { return m_nSeries; }		// The series ID
	inline	time_t	GetValidFrom()	const { return m_VALID_FROM; }	// The token "valid from" date for this series
	inline	time_t	GetValidTo()	const { return m_VALID_TO; }	// The token "valid until" date for this series
	inline	time_t	GetExpiration()	const { return m_EXPIRATION; }	// The date the mint expires (should be halfway
																	// between the above two dates.)
	bool Expired() const;	// true or false. Expired? 
							// Valid range is GetValidFrom() through GetExpiration().
	
	inline OTAccount * GetCashReserveAccount() const { return m_pReserveAcct; }
	
	OTMint();
	OTMint(const OTString & strServerID, const OTString & strAssetTypeID);
	OTMint(const OTString & strServerID, const OTString & strServerNymID, const OTString & strAssetTypeID);
	virtual ~OTMint();
	virtual void Release();
	void ReleaseDenominations();
	
	bool LoadMint(const char * szAppend=NULL);
	bool SaveMint(const char * szAppend=NULL);
	
	virtual bool LoadContract();
	
	// Will save the private keys on next serialization (not just public keys)
	// (SignContract sets m_bSavePrivateKeys back to false again.)
	inline void SetSavePrivateKeys(bool bDoIt=true) { m_bSavePrivateKeys = bDoIt; }	
	
	
	// The denomination indicated here is the actual denomination...1, 5, 20, 50, 100, etc
	bool GetPrivate(OTASCIIArmor & theArmor, long lDenomination);
	bool GetPublic(OTASCIIArmor & theArmor, long lDenomination);
	
	long GetDenomination(int nIndex);
	long GetLargestDenomination(long lAmount);
	bool AddDenomination(OTPseudonym & theNotary, long lDenomination, int nPrimeLength=1024);
	inline int GetDenominationCount() const { return m_nDenominationCount; }

	virtual bool VerifyContractID();
	
	bool VerifyMint(OTPseudonym & theOperator);
	
	virtual void UpdateContents(); // Before transmission or serialization, this is where the token saves its contents 

	inline void SetAssetID(const OTIdentifier & newID) { m_AssetID = newID; }
	
	// Lucre step 1: generate new mint
	void GenerateNewMint(int nSeries, time_t VALID_FROM, time_t VALID_TO,  time_t MINT_EXPIRATION, 
						 const OTIdentifier & theAssetID, const OTIdentifier & theServerID, 
						 OTPseudonym & theNotary, 
						 long nDenom1=0, long nDenom2=0, long nDenom3=0, long nDenom4=0, long nDenom5=0,
						 long nDenom6=0, long nDenom7=0, long nDenom8=0, long nDenom9=0, long nDenom10=0);

	// step 2: (coin request is in OTToken)
	
	// Lucre step 3: mint signs token
	bool SignToken(OTPseudonym & theNotary, OTToken & theToken, OTString & theOutput, int nTokenIndex);
	
	// step 4: (unblind coin is in OTToken)
	
	// Lucre step 5: mint verifies token when it is redeemed by merchant.
	bool VerifyToken(OTPseudonym & theNotary, OTString & theCleartextToken, long lDenomination);

	virtual bool SaveContractWallet(std::ofstream & ofs);
//	virtual bool SaveContractWallet(FILE * fl);	
};


#endif // __OTMINT_H__
