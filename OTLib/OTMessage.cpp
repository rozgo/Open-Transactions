/************************************************************************************
 *    
 *  OTMessage.cpp
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


#include <cstring>


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "irrxml/irrXML.h"

using namespace irr;
using namespace io;

#include "OTStorage.h"

#include "OTMessage.h"
#include "OTString.h"
#include "OTStringXML.h"
#include "OTASCIIArmor.h"

#include "OTLog.h"

// PROTOCOL DOCUMENT -------------------------------------------

// --- This is the file that implements the entire message protocol.
// (Transactions are in a different file.)




// The framework (OTContract) will call this function at the appropriate time.
// OTMessage is special because it actually does something here, when most contracts
// are read-only and thus never update their contents. 
// Messages, obviously, are different every time, and this function will be called
// just prior to the signing of the message, in OTContract::SignContract.
void OTMessage::UpdateContents()
{	
	// I release this because I'm about to repopulate it.
	m_xmlUnsigned.Release();

	m_xmlUnsigned.Concatenate("<?xml version=\"%s\"?>\n\n", "1.0");		
	m_xmlUnsigned.Concatenate("<OTmessage\n version=\"%s\">\n\n", m_strVersion.Get());
	
	
		
	// ------------------------------------------------------------------------
	if (m_strCommand.Compare("getMarketList"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n"
								  " requestNum=\"%s\"\n"
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\""
								  ">\n\n",
								  m_strCommand.Get(),
								  m_strRequestNum.Get(),
								  m_strNymID.Get(),
								  m_strServerID.Get()
								  );
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	// ------------------------------------------------------------------------
	if (m_strCommand.Compare("@getMarketList"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n"
								  " success=\"%s\"\n"
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\""
								  ">\n\n",
								  m_strCommand.Get(),(m_bSuccess ? "true" : "false"),
								  m_strNymID.Get(),
								  m_strServerID.Get()
								  );
		
		if (m_bSuccess && (m_ascPayload.GetLength() > 2))
			m_xmlUnsigned.Concatenate("<messagePayload>\n%s</messagePayload>\n\n", m_ascPayload.Get());
		else if (!m_bSuccess && (m_ascInReferenceTo.GetLength() > 2))
			m_xmlUnsigned.Concatenate("<inReferenceTo>\n%s</inReferenceTo>\n\n", m_ascInReferenceTo.Get());

		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	// ------------------------------------------------------------------------
	if (m_strCommand.Compare("getMarketOffers"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n"
								  " requestNum=\"%s\"\n"
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " marketID=\"%s\"\n" // stored in NymID2
								  " depth=\"%ld\""
								  ">\n\n",
								  m_strCommand.Get(),
								  m_strRequestNum.Get(),
								  m_strNymID.Get(),
								  m_strServerID.Get(),
								  m_strNymID2.Get(),	// Storing Market ID
								  m_lDepth
								  );
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	// ------------------------------------------------------------------------
	if (m_strCommand.Compare("@getMarketOffers"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n"
								  " success=\"%s\"\n"
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " marketID=\"%s\"" // stored in NymID2
								  ">\n\n",
								  m_strCommand.Get(),(m_bSuccess ? "true" : "false"),
								  m_strNymID.Get(),
								  m_strServerID.Get(),
								  m_strNymID2.Get()		// Storing Market ID
								  );
		
		if (m_bSuccess && (m_ascPayload.GetLength() > 2))
			m_xmlUnsigned.Concatenate("<messagePayload>\n%s</messagePayload>\n\n", m_ascPayload.Get());
		else if (!m_bSuccess && (m_ascInReferenceTo.GetLength() > 2))
			m_xmlUnsigned.Concatenate("<inReferenceTo>\n%s</inReferenceTo>\n\n", m_ascInReferenceTo.Get());

		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	
	
	// ------------------------------------------------------------------------
	if (m_strCommand.Compare("getMarketRecentTrades"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n"
								  " requestNum=\"%s\"\n"
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " marketID=\"%s\"\n" // stored in NymID2
								  " depth=\"%ld\""
								  ">\n\n",
								  m_strCommand.Get(),
								  m_strRequestNum.Get(),
								  m_strNymID.Get(),
								  m_strServerID.Get(),
								  m_strNymID2.Get(),	// Storing Market ID
								  m_lDepth
								  );
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	// ------------------------------------------------------------------------
	if (m_strCommand.Compare("@getMarketRecentTrades"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n"
								  " success=\"%s\"\n"
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " marketID=\"%s\"" // stored in NymID2
								  ">\n\n",
								  m_strCommand.Get(),(m_bSuccess ? "true" : "false"),
								  m_strNymID.Get(),
								  m_strServerID.Get(),
								  m_strNymID2.Get()		// Storing Market ID
								  );
		
		if (m_bSuccess && (m_ascPayload.GetLength() > 2))
			m_xmlUnsigned.Concatenate("<messagePayload>\n%s</messagePayload>\n\n", m_ascPayload.Get());
		else if (!m_bSuccess && (m_ascInReferenceTo.GetLength() > 2))
			m_xmlUnsigned.Concatenate("<inReferenceTo>\n%s</inReferenceTo>\n\n", m_ascInReferenceTo.Get());

		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	
	
	// ------------------------------------------------------------------------
	if (m_strCommand.Compare("getNym_MarketOffers"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n"
								  " requestNum=\"%s\"\n"
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\""
								  ">\n\n",
								  m_strCommand.Get(),
								  m_strRequestNum.Get(),
								  m_strNymID.Get(),
								  m_strServerID.Get()
								  );
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	// ------------------------------------------------------------------------
	if (m_strCommand.Compare("@getNym_MarketOffers"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n"
								  " success=\"%s\"\n"
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\""
								  ">\n\n",
								  m_strCommand.Get(),(m_bSuccess ? "true" : "false"),
								  m_strNymID.Get(),
								  m_strServerID.Get()
								  );
		
		if (m_bSuccess && (m_ascPayload.GetLength() > 2))
			m_xmlUnsigned.Concatenate("<messagePayload>\n%s</messagePayload>\n\n", m_ascPayload.Get());
		else if (!m_bSuccess && (m_ascInReferenceTo.GetLength() > 2))
			m_xmlUnsigned.Concatenate("<inReferenceTo>\n%s</inReferenceTo>\n\n", m_ascInReferenceTo.Get());
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------

	
	
	
	
	// ------------------------------------------------------------------------
	if (m_strCommand.Compare("cancelNymMarketOffer"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n"
								  " requestNum=\"%s\"\n"
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " inRefToNum=\"%ld\""
								  ">\n\n",
								  m_strCommand.Get(),
								  m_strRequestNum.Get(),
								  m_strNymID.Get(),
								  m_strServerID.Get(),
								  m_lTransactionNum
								  );
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	// ------------------------------------------------------------------------
	if (m_strCommand.Compare("@cancelNymMarketOffer"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n"
								  " success=\"%s\"\n"
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " inRefToNum=\"%ld\""
								  ">\n\n",
								  m_strCommand.Get(),(m_bSuccess ? "true" : "false"),
								  m_strNymID.Get(),
								  m_strServerID.Get(),
								  m_lTransactionNum
								  );
		
		if (!m_bSuccess && (m_ascInReferenceTo.GetLength() > 2))
			m_xmlUnsigned.Concatenate("<inReferenceTo>\n%s</inReferenceTo>\n\n", m_ascInReferenceTo.Get());
				
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	

	
	
	// ------------------------------------------------------------------------
	if (m_strCommand.Compare("getOffer_Trades"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n"
								  " requestNum=\"%s\"\n"
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " inRefToNum=\"%ld\""
								  ">\n\n",
								  m_strCommand.Get(),
								  m_strRequestNum.Get(),
								  m_strNymID.Get(),
								  m_strServerID.Get(),
								  m_lTransactionNum
								  );
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	// ------------------------------------------------------------------------
	if (m_strCommand.Compare("@getOffer_Trades"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n"
								  " success=\"%s\"\n"
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " inRefToNum=\"%ld\""
								  ">\n\n",
								  m_strCommand.Get(),(m_bSuccess ? "true" : "false"),
								  m_strNymID.Get(),
								  m_strServerID.Get(),
								  m_lTransactionNum
								  );
		
		if (!m_bSuccess && (m_ascInReferenceTo.GetLength() > 2))
			m_xmlUnsigned.Concatenate("<inReferenceTo>\n%s</inReferenceTo>\n\n", m_ascInReferenceTo.Get());
		else if (m_bSuccess && (m_ascPayload.GetLength() > 2))
			m_xmlUnsigned.Concatenate("<messagePayload>\n%s</messagePayload>\n\n", m_ascPayload.Get());
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	

	
	
	// ------------------------------------------------------------------------
	if (m_strCommand.Compare("checkServerID"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n"
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\""
								  ">\n\n",
								  m_strCommand.Get(),
								  m_strNymID.Get(),
								  m_strServerID.Get()
								  );
		
		m_xmlUnsigned.Concatenate("<nymPublicKey>\n%s</nymPublicKey>\n\n", m_strNymPublicKey.Get());
		
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	// ------------------------------------------------------------------------
	if (m_strCommand.Compare("@checkServerID"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n"
								  " success=\"%s\"\n"
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\""
								  ">\n\n",
								  m_strCommand.Get(),(m_bSuccess ? "true" : "false"),
								  m_strNymID.Get(),
								  m_strServerID.Get()
								  );
				
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	// ------------------------------------------------------------------------
	if (m_strCommand.Compare("createUserAccount"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n"
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\""
								  ">\n\n",
								  m_strCommand.Get(),
								  m_strNymID.Get(),
								  m_strServerID.Get()
								  );
		
		m_xmlUnsigned.Concatenate("<nymPublicKey>\n%s</nymPublicKey>\n\n", m_strNymPublicKey.Get());
		
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	// ------------------------------------------------------------------------
	if (m_strCommand.Compare("@createUserAccount"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n"
								  " success=\"%s\"\n"
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\""
								  ">\n\n",
								  m_strCommand.Get(),(m_bSuccess ? "true" : "false"),
								  m_strNymID.Get(),
								  m_strServerID.Get()
								  );
		
		if (m_ascInReferenceTo.GetLength() > 2)
			m_xmlUnsigned.Concatenate("<inReferenceTo>\n%s</inReferenceTo>\n\n", m_ascInReferenceTo.Get());
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	
	
	
	// ------------------------------------------------------------------------
	
	if (m_strCommand.Compare("checkUser"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n"
								  " nymID=\"%s\"\n"
								  " nymID2=\"%s\"\n"
								  " requestNum=\"%s\"\n"
								  " serverID=\"%s\""
								  ">\n\n",
								  m_strCommand.Get(),
								  m_strNymID.Get(),
								  m_strNymID2.Get(),
								  m_strRequestNum.Get(),
								  m_strServerID.Get()
								  );
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	// ------------------------------------------------------------------------
	if (m_strCommand.Compare("@checkUser"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n"
								  " success=\"%s\"\n"
								  " nymID=\"%s\"\n"
								  " nymID2=\"%s\"\n"
								  " serverID=\"%s\""
								  ">\n\n",
								  m_strCommand.Get(), (m_bSuccess ? "true" : "false"),
								  m_strNymID.Get(),
								  m_strNymID2.Get(),
								  m_strServerID.Get()
								  );
		
		if (m_bSuccess)
			m_xmlUnsigned.Concatenate("<nymPublicKey>\n%s</nymPublicKey>\n\n", m_strNymPublicKey.Get());
		else
			m_xmlUnsigned.Concatenate("<inReferenceTo>\n%s</inReferenceTo>\n\n", m_ascInReferenceTo.Get());
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	
	// ------------------------------------------------------------------------
	// This one isn't part of the message protocol, but is used for outmail storage.
	// (Because outmail isn't encrypted like the inmail is, since the Nymfile itself
	// will soon be encrypted, and there's no need to be redundant also as well in addition on top of that.
	//
	if (m_strCommand.Compare("outmailMessage"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n"
								  " nymID=\"%s\"\n"
								  " nymID2=\"%s\"\n"
								  " requestNum=\"%s\"\n"
								  " serverID=\"%s\""
								  ">\n\n",
								  m_strCommand.Get(),
								  m_strNymID.Get(),
								  m_strNymID2.Get(),
								  m_strRequestNum.Get(),
								  m_strServerID.Get()
								  );
		
		if (m_ascPayload.GetLength() > 2)
			m_xmlUnsigned.Concatenate("<messagePayload>\n%s</messagePayload>\n\n", m_ascPayload.Get());
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------	
	
	// ------------------------------------------------------------------------
	
	if (m_strCommand.Compare("sendUserMessage"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n"
								  " nymID=\"%s\"\n"
								  " nymID2=\"%s\"\n"
								  " requestNum=\"%s\"\n"
								  " serverID=\"%s\""
								  ">\n\n",
								  m_strCommand.Get(),
								  m_strNymID.Get(),
								  m_strNymID2.Get(),
								  m_strRequestNum.Get(),
								  m_strServerID.Get()
								  );
		
		if (m_ascPayload.GetLength() > 2)
			m_xmlUnsigned.Concatenate("<messagePayload>\n%s</messagePayload>\n\n", m_ascPayload.Get());
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	// ------------------------------------------------------------------------
	if (m_strCommand.Compare("@sendUserMessage"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n"
								  " success=\"%s\"\n"
								  " nymID=\"%s\"\n"
								  " nymID2=\"%s\"\n"
								  " serverID=\"%s\""
								  ">\n\n",
								  m_strCommand.Get(), (m_bSuccess ? "true" : "false"),
								  m_strNymID.Get(),
								  m_strNymID2.Get(),
								  m_strServerID.Get()
								  );
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	// ------------------------------------------------------------------------
	if (m_strCommand.Compare("getRequest"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n"
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\""
								  ">\n\n",
								  m_strCommand.Get(),
								  m_strNymID.Get(),
								  m_strServerID.Get()
								  );
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	
	// ------------------------------------------------------------------------
	// This is the ONE command where you see a request number coming back from the server.
	// In all the other commands, it should be SENT to the server, not received from the server.
	if (m_strCommand.Compare("@getRequest"))
	{	
		m_xmlUnsigned.Concatenate("<%s\n" // command
								  " success=\"%s\"\n" // m_bSuccess
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " requestNum=\"%s\""
								  ">\n\n",
								  m_strCommand.Get(),
								  (m_bSuccess ? "true" : "false"),
								  m_strNymID.Get(),
								  m_strServerID.Get(),
								  m_strRequestNum.Get()
								  );
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	
	// ------------------------------------------------------------------------
	
	if (m_strCommand.Compare("issueAssetType"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n" // Command
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " requestNum=\"%s\"\n"
								  " assetType=\"%s\""
								  ">\n\n",
								  m_strCommand.Get(),
								  m_strNymID.Get(),
								  m_strServerID.Get(),
								  m_strRequestNum.Get(),
								  m_strAssetID.Get()
								  );
		
		if (m_ascPayload.GetLength())
			m_xmlUnsigned.Concatenate("<assetContract>\n%s</assetContract>\n\n", m_ascPayload.Get());
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	// ------------------------------------------------------------------------
	if (m_strCommand.Compare("@issueAssetType"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n" // Command
								  " success=\"%s\"\n"
								  " accountID=\"%s\"\n" // the new issuer account ID
								  " nymID=\"%s\"\n"
								  " assetType=\"%s\"\n"
								  " serverID=\"%s\""
								  ">\n\n",
								  m_strCommand.Get(), (m_bSuccess ? "true" : "false"),
								  m_strAcctID.Get(),
								  m_strNymID.Get(),
								  m_strAssetID.Get(),
								  m_strServerID.Get()
								  );
		
		if (m_ascInReferenceTo.GetLength())
			m_xmlUnsigned.Concatenate("<inReferenceTo>\n%s</inReferenceTo>\n\n", m_ascInReferenceTo.Get());
		
		if (m_bSuccess && m_ascPayload.GetLength())
			m_xmlUnsigned.Concatenate("<issuerAccount>\n%s</issuerAccount>\n\n", m_ascPayload.Get());
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	
	// ------------------------------------------------------------------------
	
	if (m_strCommand.Compare("exchangeBasket"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n" // Command
								  " exchange=\"%s\"\n"
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " assetType=\"%s\"\n" // the contract ID of the basket contract (asset type)
								  " requestNum=\"%s\"\n"
								  ">\n\n",
								  m_strCommand.Get(),
								  (m_bBool ? "in" : "out"),
								  m_strNymID.Get(),
								  m_strServerID.Get(),
								  m_strAssetID.Get(),
								  m_strRequestNum.Get()
								  );
		
		if (m_ascPayload.GetLength())
			m_xmlUnsigned.Concatenate("<exchangeRequest>\n%s</exchangeRequest>\n\n", m_ascPayload.Get());
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	// ------------------------------------------------------------------------
	if (m_strCommand.Compare("@exchangeBasket"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n" // Command
								  " success=\"%s\"\n"
								  " exchange=\"%s\"\n"
								  " assetType=\"%s\"\n" // the contract ID of the basket contract (asset type)
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\""
								  ">\n\n",
								  m_strCommand.Get(), 
								  (m_bSuccess ? "true" : "false"),
								  (m_bBool ? "in" : "out"),
								  m_strAssetID.Get(),
								  m_strNymID.Get(),
								  m_strServerID.Get()
								  );
		
		if (m_ascInReferenceTo.GetLength())
			m_xmlUnsigned.Concatenate("<inReferenceTo>\n%s</inReferenceTo>\n\n", m_ascInReferenceTo.Get());
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	// ------------------------------------------------------------------------
	
	if (m_strCommand.Compare("issueBasket"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n" // Command
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " requestNum=\"%s\"\n"
								  ">\n\n",
								  m_strCommand.Get(),
								  m_strNymID.Get(),
								  m_strServerID.Get(),
								  m_strRequestNum.Get()
								  );
		
		if (m_ascPayload.GetLength())
			m_xmlUnsigned.Concatenate("<currencyBasket>\n%s</currencyBasket>\n\n", m_ascPayload.Get());
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	// ------------------------------------------------------------------------
	if (m_strCommand.Compare("@issueBasket"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n" // Command
								  " success=\"%s\"\n"
								  " accountID=\"%s\"\n" // the new basket issuer account ID
								  " nymID=\"%s\"\n"
								  " assetType=\"%s\"\n" // the new Asset Type
								  " serverID=\"%s\""
								  ">\n\n",
								  m_strCommand.Get(), (m_bSuccess ? "true" : "false"),
								  m_strAcctID.Get(),
								  m_strNymID.Get(),
								  m_strAssetID.Get(),
								  m_strServerID.Get()
								  );
		
		if (m_ascInReferenceTo.GetLength())
			m_xmlUnsigned.Concatenate("<inReferenceTo>\n%s</inReferenceTo>\n\n", m_ascInReferenceTo.Get());
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	// ------------------------------------------------------------------------
	
	if (m_strCommand.Compare("createAccount"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n" // Command
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " requestNum=\"%s\"\n"
								  " assetType=\"%s\""
								  ">\n\n",
								  m_strCommand.Get(),
								  m_strNymID.Get(),
								  m_strServerID.Get(),
								  m_strRequestNum.Get(),
								  m_strAssetID.Get()
								  );
		
//		OTLog::vError("DEBUG: Asset Type length: %d, Value:\n%s\n", m_strAssetID.GetLength(),  m_strAssetID.Get());
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	// ------------------------------------------------------------------------
	if (m_strCommand.Compare("@createAccount"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n" // Command
								  " success=\"%s\"\n"
								  " accountID=\"%s\"\n"
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\""
								  ">\n\n",
								  m_strCommand.Get(), (m_bSuccess ? "true" : "false"),
								  m_strAcctID.Get(),
								  m_strNymID.Get(),
								  m_strServerID.Get()
								  );
		
		if (m_ascInReferenceTo.GetLength())
			m_xmlUnsigned.Concatenate("<inReferenceTo>\n%s</inReferenceTo>\n\n", m_ascInReferenceTo.Get());
		
		if (m_bSuccess && m_ascPayload.GetLength())
			m_xmlUnsigned.Concatenate("<newAccount>\n%s</newAccount>\n\n", m_ascPayload.Get());
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	
	// ------------------------------------------------------------------------
	
	// the Payload contains an ascii-armored OTLedger object.
	if (m_strCommand.Compare("notarizeTransactions"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n" // Command
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " accountID=\"%s\"\n"
								  " requestNum=\"%s\""
								  " >\n\n",
								  m_strCommand.Get(),
								  m_strNymID.Get(),
								  m_strServerID.Get(),
								  m_strAcctID.Get(),
								  m_strRequestNum.Get()
								  );
		
		// I would check if this was empty, but it should never be empty...
		// famous last words.
		if (m_ascPayload.GetLength())
			m_xmlUnsigned.Concatenate("<accountLedger>\n%s</accountLedger>\n\n", m_ascPayload.Get());
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	
	// ------------------------------------------------------------------------
	
	// the Payload contains an ascii-armored OTLedger object.
	if (m_strCommand.Compare("@notarizeTransactions"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n" // Command
								  " success=\"%s\"\n"
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " accountID=\"%s\""
								  " >\n\n",
								  m_strCommand.Get(),
								  (m_bSuccess ? "true" : "false"),
								  m_strNymID.Get(),
								  m_strServerID.Get(), 
								  m_strAcctID.Get()
								  );
		
		if (m_ascInReferenceTo.GetLength())
			m_xmlUnsigned.Concatenate("<inReferenceTo>\n%s</inReferenceTo>\n\n", m_ascInReferenceTo.Get());
		
		// I would check if this was empty, but it should never be empty...
		// famous last words.
		if (m_ascPayload.GetLength())
			m_xmlUnsigned.Concatenate("<responseLedger>\n%s</responseLedger>\n\n", m_ascPayload.Get());
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	
	// ------------------------------------------------------------------------
	
	// the Payload contains an ascii-armored OTLedger object.
	if (m_strCommand.Compare("getTransactionNum"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n" // Command
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " requestNum=\"%s\""
								  " >\n\n",
								  m_strCommand.Get(),
								  m_strNymID.Get(),
								  m_strServerID.Get(),
								  m_strRequestNum.Get()
								  );
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	
	// ------------------------------------------------------------------------
	
	// the Payload contains an ascii-armored OTLedger object.
	if (m_strCommand.Compare("@getTransactionNum"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n" // Command
								  " success=\"%s\"\n"
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\""
								  " >\n\n",
								  m_strCommand.Get(),
								  (m_bSuccess ? "true" : "false"),
								  m_strNymID.Get(),
								  m_strServerID.Get()
								  );

		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	
	// ------------------------------------------------------------------------
	
	// the Payload contains an ascii-armored OTLedger object.
	if (m_strCommand.Compare("getNymbox"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n" // Command
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " requestNum=\"%s\""
								  " >\n\n",
								  m_strCommand.Get(),
								  m_strNymID.Get(),
								  m_strServerID.Get(),
								  m_strRequestNum.Get()
								  );
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	
	// ------------------------------------------------------------------------
	
	// the Payload contains an ascii-armored OTLedger object.
	if (m_strCommand.Compare("@getNymbox"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n" // Command
								  " success=\"%s\"\n"
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\""
								  " >\n\n",
								  m_strCommand.Get(),
								  (m_bSuccess ? "true" : "false"),
								  m_strNymID.Get(),
								  m_strServerID.Get()
								  );
		
		if (!m_bSuccess && m_ascInReferenceTo.GetLength())
			m_xmlUnsigned.Concatenate("<inReferenceTo>\n%s</inReferenceTo>\n\n", m_ascInReferenceTo.Get());
		
		// I would check if this was empty, but it should never be empty...
		// famous last words.
		if (m_bSuccess && m_ascPayload.GetLength())
			m_xmlUnsigned.Concatenate("<nymboxLedger>\n%s</nymboxLedger>\n\n", m_ascPayload.Get());
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	
	
	// ------------------------------------------------------------------------
	
	// the Payload contains an ascii-armored OTLedger object.
	if (m_strCommand.Compare("getInbox"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n" // Command
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " accountID=\"%s\"\n"
								  " requestNum=\"%s\""
								  " >\n\n",
								  m_strCommand.Get(),
								  m_strNymID.Get(),
								  m_strServerID.Get(),
								  m_strAcctID.Get(),
								  m_strRequestNum.Get()
								  );
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	
	// ------------------------------------------------------------------------
	
	// the Payload contains an ascii-armored OTLedger object.
	if (m_strCommand.Compare("@getInbox"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n" // Command
								  " success=\"%s\"\n"
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " accountID=\"%s\""
								  " >\n\n",
								  m_strCommand.Get(),
								  (m_bSuccess ? "true" : "false"),
								  m_strNymID.Get(),
								  m_strServerID.Get(), 
								  m_strAcctID.Get()
								  );
		
		if (!m_bSuccess && m_ascInReferenceTo.GetLength())
			m_xmlUnsigned.Concatenate("<inReferenceTo>\n%s</inReferenceTo>\n\n", m_ascInReferenceTo.Get());
		
		// I would check if this was empty, but it should never be empty...
		// famous last words.
		if (m_bSuccess && m_ascPayload.GetLength())
			m_xmlUnsigned.Concatenate("<inboxLedger>\n%s</inboxLedger>\n\n", m_ascPayload.Get());
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	
	// ------------------------------------------------------------------------
	
	// the Payload contains an ascii-armored OTLedger object.
	if (m_strCommand.Compare("getOutbox"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n" // Command
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " accountID=\"%s\"\n"
								  " requestNum=\"%s\""
								  " >\n\n",
								  m_strCommand.Get(),
								  m_strNymID.Get(),
								  m_strServerID.Get(),
								  m_strAcctID.Get(),
								  m_strRequestNum.Get()
								  );
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	
	// ------------------------------------------------------------------------
	
	// the Payload contains an ascii-armored OTLedger object.
	if (m_strCommand.Compare("@getOutbox"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n" // Command
								  " success=\"%s\"\n"
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " accountID=\"%s\""
								  " >\n\n",
								  m_strCommand.Get(),
								  (m_bSuccess ? "true" : "false"),
								  m_strNymID.Get(),
								  m_strServerID.Get(), 
								  m_strAcctID.Get()
								  );
		
		if (!m_bSuccess && m_ascInReferenceTo.GetLength())
			m_xmlUnsigned.Concatenate("<inReferenceTo>\n%s</inReferenceTo>\n\n", m_ascInReferenceTo.Get());
		
		// I would check if this was empty, but it should never be empty...
		// famous last words.
		if (m_bSuccess && m_ascPayload.GetLength())
			m_xmlUnsigned.Concatenate("<outboxLedger>\n%s</outboxLedger>\n\n", m_ascPayload.Get());
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	
	
	// ------------------------------------------------------------------------
	
	if (m_strCommand.Compare("getAccount"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n" // Command
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " accountID=\"%s\"\n"
								  " requestNum=\"%s\""
								  " >\n\n",
								  m_strCommand.Get(),
								  m_strNymID.Get(),
								  m_strServerID.Get(),
								  m_strAcctID.Get(),
								  m_strRequestNum.Get()
								  );
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	
	// ------------------------------------------------------------------------
	
	// the Payload contains an ascii-armored OTAccount object.
	if (m_strCommand.Compare("@getAccount"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n" // Command
								  " success=\"%s\"\n"
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " accountID=\"%s\""
								  " >\n\n",
								  m_strCommand.Get(),
								  (m_bSuccess ? "true" : "false"),
								  m_strNymID.Get(),
								  m_strServerID.Get(), 
								  m_strAcctID.Get()
								  );
		
		if (!m_bSuccess && m_ascInReferenceTo.GetLength())
			m_xmlUnsigned.Concatenate("<inReferenceTo>\n%s</inReferenceTo>\n\n", m_ascInReferenceTo.Get());
		
		// I would check if this was empty, but it should never be empty...
		// famous last words.
		if (m_bSuccess && m_ascPayload.GetLength())
			m_xmlUnsigned.Concatenate("<assetAccount>\n%s</assetAccount>\n\n", m_ascPayload.Get());
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	

	
	
	// ------------------------------------------------------------------------
	
	if (m_strCommand.Compare("getContract"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n" // Command
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " assetType=\"%s\"\n"
								  " requestNum=\"%s\""
								  " >\n\n",
								  m_strCommand.Get(),
								  m_strNymID.Get(),
								  m_strServerID.Get(),
								  m_strAssetID.Get(),
								  m_strRequestNum.Get()
								  );
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	
	// ------------------------------------------------------------------------
	
	// the Payload contains an ascii-armored OTAssetContract object.
	if (m_strCommand.Compare("@getContract"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n" // Command
								  " success=\"%s\"\n"
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " assetType=\"%s\""
								  " >\n\n",
								  m_strCommand.Get(),
								  (m_bSuccess ? "true" : "false"),
								  m_strNymID.Get(),
								  m_strServerID.Get(), 
								  m_strAssetID.Get()
								  );
		
		if (!m_bSuccess && m_ascInReferenceTo.GetLength())
			m_xmlUnsigned.Concatenate("<inReferenceTo>\n%s</inReferenceTo>\n\n", m_ascInReferenceTo.Get());
		
		// I would check if this was empty, but it should never be empty...
		// famous last words.
		if (m_bSuccess && m_ascPayload.GetLength())
			m_xmlUnsigned.Concatenate("<assetContract>\n%s</assetContract>\n\n", m_ascPayload.Get());
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	
	// ------------------------------------------------------------------------
	
	if (m_strCommand.Compare("getMint"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n" // Command
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " assetType=\"%s\"\n"
								  " requestNum=\"%s\""
								  " >\n\n",
								  m_strCommand.Get(),
								  m_strNymID.Get(),
								  m_strServerID.Get(),
								  m_strAssetID.Get(),
								  m_strRequestNum.Get()
								  );
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	
	// ------------------------------------------------------------------------
	
	// the Payload contains an ascii-armored OTMint object.
	if (m_strCommand.Compare("@getMint"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n" // Command
								  " success=\"%s\"\n"
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " assetType=\"%s\""
								  " >\n\n",
								  m_strCommand.Get(),
								  (m_bSuccess ? "true" : "false"),
								  m_strNymID.Get(),
								  m_strServerID.Get(), 
								  m_strAssetID.Get()
								  );
		
		if (!m_bSuccess && m_ascInReferenceTo.GetLength())
			m_xmlUnsigned.Concatenate("<inReferenceTo>\n%s</inReferenceTo>\n\n", m_ascInReferenceTo.Get());
		
		// I would check if this was empty, but it should never be empty...
		// famous last words.
		if (m_bSuccess && m_ascPayload.GetLength())
			m_xmlUnsigned.Concatenate("<mint>\n%s</mint>\n\n", m_ascPayload.Get());
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	
	// ------------------------------------------------------------------------
	
	// the Payload contains an ascii-armored OTLedger object.
	if (m_strCommand.Compare("processInbox"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n" // Command
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " accountID=\"%s\"\n"
								  " requestNum=\"%s\""
								  " >\n\n",
								  m_strCommand.Get(),
								  m_strNymID.Get(),
								  m_strServerID.Get(),
								  m_strAcctID.Get(),
								  m_strRequestNum.Get()
								  );
		
		// I would check if this was empty, but it should never be empty...
		// famous last words.
		if (m_ascPayload.GetLength())
			m_xmlUnsigned.Concatenate("<processLedger>\n%s</processLedger>\n\n", m_ascPayload.Get());
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	
	// ------------------------------------------------------------------------
	
	// the Payload contains an ascii-armored OTLedger object.
	if (m_strCommand.Compare("@processInbox"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n" // Command
								  " success=\"%s\"\n"
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " accountID=\"%s\""
								  " >\n\n",
								  m_strCommand.Get(),
								  (m_bSuccess ? "true" : "false"),
								  m_strNymID.Get(),
								  m_strServerID.Get(), 
								  m_strAcctID.Get()
								  );
		
		if (m_ascInReferenceTo.GetLength())
			m_xmlUnsigned.Concatenate("<inReferenceTo>\n%s</inReferenceTo>\n\n", m_ascInReferenceTo.Get());
		
		// I would check if this was empty, but it should never be empty...
		// famous last words.
		if (m_ascPayload.GetLength())
			m_xmlUnsigned.Concatenate("<responseLedger>\n%s</responseLedger>\n\n", m_ascPayload.Get());
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	
	// ------------------------------------------------------------------------
	
	// the Payload contains an ascii-armored OTLedger object.
	if (m_strCommand.Compare("processNymbox"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n" // Command
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\"\n"
								  " requestNum=\"%s\""
								  " >\n\n",
								  m_strCommand.Get(),
								  m_strNymID.Get(),
								  m_strServerID.Get(),
								  m_strRequestNum.Get()
								  );
		
		// I would check if this was empty, but it should never be empty...
		// famous last words.
		if (m_ascPayload.GetLength())
			m_xmlUnsigned.Concatenate("<processLedger>\n%s</processLedger>\n\n", m_ascPayload.Get());
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	
	// ------------------------------------------------------------------------
	
	// the Payload contains an ascii-armored OTLedger object.
	if (m_strCommand.Compare("@processNymbox"))
	{		
		m_xmlUnsigned.Concatenate("<%s\n" // Command
								  " success=\"%s\"\n"
								  " nymID=\"%s\"\n"
								  " serverID=\"%s\""
								  " >\n\n",
								  m_strCommand.Get(),
								  (m_bSuccess ? "true" : "false"),
								  m_strNymID.Get(),
								  m_strServerID.Get()
								  );
		
		if (m_ascInReferenceTo.GetLength())
			m_xmlUnsigned.Concatenate("<inReferenceTo>\n%s</inReferenceTo>\n\n", m_ascInReferenceTo.Get());
		
		// I would check if this was empty, but it should never be empty...
		// famous last words.
		if (m_ascPayload.GetLength())
			m_xmlUnsigned.Concatenate("<responseLedger>\n%s</responseLedger>\n\n", m_ascPayload.Get());
		
		m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	} // ------------------------------------------------------------------------
	
	
	
	
	
	m_xmlUnsigned.Concatenate("</OTmessage>\n");
}












// return -1 if error, 0 if nothing, and 1 if the node was processed.
int OTMessage::ProcessXMLNode(IrrXMLReader*& xml)
{
	int nReturnVal = 0;
	
	// Here we call the parent class first.
	// If the node is found there, or there is some error,
	// then we just return either way.  But if it comes back
	// as '0', then nothing happened, and we'll continue executing.
	//
	// -- Note you can choose not to call the parent if
	// you don't want to use any of those xml tags.
	// As I do below, in the case of OTAccount.
	//if (nReturnVal = OTContract::ProcessXMLNode(xml))
	//	return nReturnVal;
	
	if (!strcmp("OTmessage", xml->getNodeName())) 
	{
		m_strVersion = xml->getAttributeValue("version");
		
		OTLog::vOutput(2, "\n===> Loading XML for Message into memory structures...\n", m_strVersion.Get());
		
		nReturnVal = 1;
	}
	// -------------------------------------------------------------------------------------------
		
	else if (!strcmp("getMarketList", xml->getNodeName())) 
	{		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strRequestNum = xml->getAttributeValue("requestNum");
		
		OTLog::vOutput(1, "\nCommand: %s\nNymID:    %s\nServerID: %s\nRequest #: %s\n", 
					   m_strCommand.Get(), m_strNymID.Get(), m_strServerID.Get(), m_strRequestNum.Get());
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	else if (!strcmp("@getMarketList", xml->getNodeName())) 
	{		
		OTString strSuccess;
		strSuccess		= xml->getAttributeValue("success");
		if (strSuccess.Compare("true"))
			m_bSuccess = true;
		else
			m_bSuccess = false;
		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		
		// -----------------------------------------------------
		
		const char * pElementExpected;
		if (m_bSuccess)
			pElementExpected = "messagePayload";
		else
			pElementExpected = "inReferenceTo";
		
		OTASCIIArmor 	ascTextExpected;
		
		if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
		{
			OTLog::vError("Error in OTMessage::ProcessXMLNode: "
						  "Expected %s element with text field, for %s.\n", 
						  pElementExpected, m_strCommand.Get());
			return (-1); // error condition
		}
		
		if (m_bSuccess)
			m_ascPayload.Set(ascTextExpected);
		else
			m_ascInReferenceTo = ascTextExpected;				
		
		// -----------------------------------------------------
		
		if (m_bSuccess)
			OTLog::vOutput(1, "\nCommand: %s   %s\nNymID:    %s\n ServerID: %s\n\n", 
						   m_strCommand.Get(), (m_bSuccess ? "SUCCESS" : "FAILED"),
						   m_strNymID.Get(), m_strServerID.Get()); // m_ascPayload.Get()
		else
			OTLog::vOutput(1, "\nCommand: %s   %s\nNymID:    %s\n ServerID: %s\n\n", 
						   m_strCommand.Get(), (m_bSuccess ? "SUCCESS" : "FAILED"),
						   m_strNymID.Get(), m_strServerID.Get() // m_ascInReferenceTo.Get()
						   );
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
		
	else if (!strcmp("getMarketOffers", xml->getNodeName())) 
	{		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strRequestNum = xml->getAttributeValue("requestNum");
		m_strNymID2		= xml->getAttributeValue("marketID");
		
		OTString strDepth = xml->getAttributeValue("depth");
		
		if (strDepth.GetLength() > 0)
			m_lDepth = atol(strDepth.Get());
		
		OTLog::vOutput(1, "\nCommand: %s\nNymID:    %s\nServerID: %s\n Market ID: %s\n Request #: %s\n", 
					   m_strCommand.Get(), m_strNymID.Get(), m_strServerID.Get(), m_strNymID2.Get(), 
					   m_strRequestNum.Get());
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	else if (!strcmp("@getMarketOffers", xml->getNodeName())) 
	{		
		OTString strSuccess;
		strSuccess		= xml->getAttributeValue("success");
		if (strSuccess.Compare("true"))
			m_bSuccess = true;
		else
			m_bSuccess = false;
		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strNymID2		= xml->getAttributeValue("marketID");
		
		// -----------------------------------------------------
		
		const char * pElementExpected;
		if (m_bSuccess)
			pElementExpected = "messagePayload";
		else
			pElementExpected = "inReferenceTo";
		
		OTASCIIArmor 	ascTextExpected;
		
		if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
		{
			OTLog::vError("Error in OTMessage::ProcessXMLNode: "
						  "Expected %s element with text field, for %s.\n", 
						  pElementExpected, m_strCommand.Get());
			return (-1); // error condition
		}
		
		if (m_bSuccess)
			m_ascPayload.Set(ascTextExpected);
		else
			m_ascInReferenceTo = ascTextExpected;				
		
		// -----------------------------------------------------
		
		if (m_bSuccess)
			OTLog::vOutput(1, "\nCommand: %s   %s\nNymID:    %s\n ServerID: %s\n MarketID: %s\n\n", 
						   m_strCommand.Get(), (m_bSuccess ? "SUCCESS" : "FAILED"),
						   m_strNymID.Get(), m_strServerID.Get(), m_strNymID2.Get()); // m_ascPayload.Get()
		else
			OTLog::vOutput(1, "\nCommand: %s   %s\nNymID:    %s\n ServerID: %s\n MarketID: %s\n\n", 
						   m_strCommand.Get(), (m_bSuccess ? "SUCCESS" : "FAILED"),
						   m_strNymID.Get(), m_strServerID.Get(), m_strNymID2.Get() // m_ascInReferenceTo.Get()
						   );
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	else if (!strcmp("getMarketRecentTrades", xml->getNodeName())) 
	{		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strRequestNum = xml->getAttributeValue("requestNum");
		m_strNymID2		= xml->getAttributeValue("marketID");
		
		OTString strDepth = xml->getAttributeValue("depth");
		
		if (strDepth.GetLength() > 0)
			m_lDepth = atol(strDepth.Get());
		
		OTLog::vOutput(1, "\nCommand: %s\nNymID:    %s\nServerID: %s\n Market ID: %s\n Request #: %s\n", 
					   m_strCommand.Get(), m_strNymID.Get(), m_strServerID.Get(), m_strNymID2.Get(), 
					   m_strRequestNum.Get());
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	else if (!strcmp("@getMarketRecentTrades", xml->getNodeName())) 
	{		
		OTString strSuccess;
		strSuccess		= xml->getAttributeValue("success");
		if (strSuccess.Compare("true"))
			m_bSuccess = true;
		else
			m_bSuccess = false;
		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strNymID2		= xml->getAttributeValue("marketID");
		
		// -----------------------------------------------------
		
		const char * pElementExpected;
		if (m_bSuccess)
			pElementExpected = "messagePayload";
		else
			pElementExpected = "inReferenceTo";
		
		OTASCIIArmor 	ascTextExpected;
		
		if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
		{
			OTLog::vError("Error in OTMessage::ProcessXMLNode: "
						  "Expected %s element with text field, for %s.\n", 
						  pElementExpected, m_strCommand.Get());
			return (-1); // error condition
		}
		
		if (m_bSuccess)
			m_ascPayload.Set(ascTextExpected);
		else
			m_ascInReferenceTo = ascTextExpected;				
		
		// -----------------------------------------------------
		
		if (m_bSuccess)
			OTLog::vOutput(1, "\nCommand: %s   %s\nNymID:    %s\n ServerID: %s\n MarketID: %s\n\n", 
						   m_strCommand.Get(), (m_bSuccess ? "SUCCESS" : "FAILED"),
						   m_strNymID.Get(), m_strServerID.Get(), m_strNymID2.Get()); // m_ascPayload.Get()
		else
			OTLog::vOutput(1, "\nCommand: %s   %s\nNymID:    %s\n ServerID: %s\n MarketID: %s\n\n", 
						   m_strCommand.Get(), (m_bSuccess ? "SUCCESS" : "FAILED"),
						   m_strNymID.Get(), m_strServerID.Get(), m_strNymID2.Get() // m_ascInReferenceTo.Get()
						   );
		
		nReturnVal = 1;
	}
	
	
	// -------------------------------------------------------------------------------------------
	
	else if (!strcmp("getNym_MarketOffers", xml->getNodeName())) 
	{		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strRequestNum = xml->getAttributeValue("requestNum");
		
		OTLog::vOutput(1, "\nCommand: %s\nNymID:    %s\nServerID: %s\nRequest #: %s\n", 
					   m_strCommand.Get(), m_strNymID.Get(), m_strServerID.Get(), m_strRequestNum.Get());
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	else if (!strcmp("@getNym_MarketOffers", xml->getNodeName())) 
	{		
		OTString strSuccess;
		strSuccess		= xml->getAttributeValue("success");
		if (strSuccess.Compare("true"))
			m_bSuccess = true;
		else
			m_bSuccess = false;
		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		
		// -----------------------------------------------------
		
		const char * pElementExpected;
		if (m_bSuccess)
			pElementExpected = "messagePayload";
		else
			pElementExpected = "inReferenceTo";
		
		OTASCIIArmor 	ascTextExpected;
		
		if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
		{
			OTLog::vError("Error in OTMessage::ProcessXMLNode: "
						  "Expected %s element with text field, for %s.\n", 
						  pElementExpected, m_strCommand.Get());
			return (-1); // error condition
		}
		
		if (m_bSuccess)
			m_ascPayload.Set(ascTextExpected);
		else
			m_ascInReferenceTo = ascTextExpected;				
		
		// -----------------------------------------------------
		
		if (m_bSuccess)
			OTLog::vOutput(1, "\nCommand: %s   %s\nNymID:    %s\n ServerID: %s\n\n", 
						   m_strCommand.Get(), (m_bSuccess ? "SUCCESS" : "FAILED"),
						   m_strNymID.Get(), m_strServerID.Get()); // m_ascPayload.Get()
		else
			OTLog::vOutput(1, "\nCommand: %s   %s\nNymID:    %s\n ServerID: %s\n\n", 
						   m_strCommand.Get(), (m_bSuccess ? "SUCCESS" : "FAILED"),
						   m_strNymID.Get(), m_strServerID.Get() // m_ascInReferenceTo.Get()
						   );
		
		nReturnVal = 1;
	}
	
	// -----------------------------------------------------
	
	else if (!strcmp("cancelNymMarketOffer", xml->getNodeName())) 
	{		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strRequestNum = xml->getAttributeValue("requestNum");
		
		OTString strTransactionNum;
		strTransactionNum = xml->getAttributeValue("inRefToNum");
		if (strTransactionNum.Exists())
			m_lTransactionNum = atol(strTransactionNum.Get());
		
		OTLog::vOutput(1, "\nCommand: %s\nNymID:    %s\nServerID: %s\nRequest #: %s\n", 
					   m_strCommand.Get(), m_strNymID.Get(), m_strServerID.Get(), m_strRequestNum.Get());
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	else if (!strcmp("@cancelNymMarketOffer", xml->getNodeName())) 
	{		
		OTString strSuccess, strTransactionNum;
		strSuccess		= xml->getAttributeValue("success");
		if (strSuccess.Compare("true"))
			m_bSuccess = true;
		else
			m_bSuccess = false;
		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		
		strTransactionNum = xml->getAttributeValue("inRefToNum");
		
		if (strTransactionNum.Exists())
			m_lTransactionNum = atol(strTransactionNum.Get());
		
		// -----------------------------------------------------
		
		if (false == m_bSuccess)
		{
			const char *	pElementExpected	= "inReferenceTo";
			OTASCIIArmor &	ascTextExpected		= m_ascInReferenceTo;
			
			if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
			{
				OTLog::vError("Error in OTMessage::ProcessXMLNode: "
							  "Expected %s element with text field, for %s.\n", 
							  pElementExpected, m_strCommand.Get());
				return (-1); // error condition
			}
		}
		
		// -----------------------------------------------------
		
		if (m_bSuccess)
			OTLog::vOutput(1, "\nCommand: %s   %s\nNymID:    %s\n ServerID: %s\n\n", 
						   m_strCommand.Get(), (m_bSuccess ? "SUCCESS" : "FAILED"),
						   m_strNymID.Get(), m_strServerID.Get()); // m_ascPayload.Get()
		else
			OTLog::vOutput(1, "\nCommand: %s   %s\nNymID:    %s\n ServerID: %s\n\n", 
						   m_strCommand.Get(), (m_bSuccess ? "SUCCESS" : "FAILED"),
						   m_strNymID.Get(), m_strServerID.Get() // m_ascInReferenceTo.Get()
						   );
		
		nReturnVal = 1;
	}

	// -------------------------------------------------------------------------------------------
	
	else if (!strcmp("getOffer_Trades", xml->getNodeName())) 
	{		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strRequestNum = xml->getAttributeValue("requestNum");
		
		OTString strTransactionNum;
		strTransactionNum = xml->getAttributeValue("inRefToNum");
		if (strTransactionNum.Exists())
			m_lTransactionNum = atol(strTransactionNum.Get());

		OTLog::vOutput(1, "\nCommand: %s\nNymID:    %s\nServerID: %s\nRequest #: %s\n", 
					   m_strCommand.Get(), m_strNymID.Get(), m_strServerID.Get(), m_strRequestNum.Get());
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	else if (!strcmp("@getOffer_Trades", xml->getNodeName())) 
	{		
		OTString strSuccess, strTransactionNum;
		strSuccess		= xml->getAttributeValue("success");
		if (strSuccess.Compare("true"))
			m_bSuccess = true;
		else
			m_bSuccess = false;
		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		
		strTransactionNum = xml->getAttributeValue("inRefToNum");
		
		if (strTransactionNum.Exists())
			m_lTransactionNum = atol(strTransactionNum.Get());
		
		// -----------------------------------------------------
		
		const char * pElementExpected;
		if (m_bSuccess)
			pElementExpected = "messagePayload";
		else
			pElementExpected = "inReferenceTo";
		
		OTASCIIArmor 	ascTextExpected;
		
		if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
		{
			OTLog::vError("Error in OTMessage::ProcessXMLNode: "
						  "Expected %s element with text field, for %s.\n", 
						  pElementExpected, m_strCommand.Get());
			return (-1); // error condition
		}
		
		if (m_bSuccess)
			m_ascPayload.Set(ascTextExpected);
		else
			m_ascInReferenceTo = ascTextExpected;				
		
		// -----------------------------------------------------
		
		if (m_bSuccess)
			OTLog::vOutput(1, "\nCommand: %s   %s\nNymID:    %s\n ServerID: %s\n\n", 
						   m_strCommand.Get(), (m_bSuccess ? "SUCCESS" : "FAILED"),
						   m_strNymID.Get(), m_strServerID.Get()); // m_ascPayload.Get()
		else
			OTLog::vOutput(1, "\nCommand: %s   %s\nNymID:    %s\n ServerID: %s\n\n", 
						   m_strCommand.Get(), (m_bSuccess ? "SUCCESS" : "FAILED"),
						   m_strNymID.Get(), m_strServerID.Get() // m_ascInReferenceTo.Get()
						   );
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------

	else if (!strcmp("checkServerID", xml->getNodeName())) 
	{		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		
		// -----------------------------------------------------
		
		const char *	pElementExpected	= "nymPublicKey";
		OTASCIIArmor 	ascTextExpected;
		
		if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
		{
			OTLog::vError("Error in OTMessage::ProcessXMLNode: "
						  "Expected %s element with text field, for %s.\n", 
						  pElementExpected, m_strCommand.Get());
			return (-1); // error condition
		}
		
		m_strNymPublicKey.Set(ascTextExpected);
		
		// -----------------------------------------------------
		
		OTLog::vOutput(1, "\nCommand: %s\nNymID:    %s\nServerID: %s\n\nPublic Key:\n%s\n", 
				m_strCommand.Get(), m_strNymID.Get(), m_strServerID.Get(), m_strNymPublicKey.Get());
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------

	else if (!strcmp("@checkServerID", xml->getNodeName())) 
	{	
		OTString strSuccess;
		strSuccess		= xml->getAttributeValue("success");
		if (strSuccess.Compare("true"))
			m_bSuccess = true;
		else
			m_bSuccess = false;
		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		
		OTLog::vOutput(1, "\nCommand: %s\nSuccess: %s\nNymID:    %s\n"
				"ServerID: %s\n\n", 
				m_strCommand.Get(), strSuccess.Get(), m_strNymID.Get(), 
				m_strServerID.Get());
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	else if (!strcmp("createUserAccount", xml->getNodeName())) 
	{		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		
		// -----------------------------------------------------
		
		const char *	pElementExpected	= "nymPublicKey";
		OTASCIIArmor 	ascTextExpected;
		
		if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
		{
			OTLog::vError("Error in OTMessage::ProcessXMLNode: "
						  "Expected %s element with text field, for %s.\n", 
						  pElementExpected, m_strCommand.Get());
			return (-1); // error condition
		}
		
		m_strNymPublicKey.Set(ascTextExpected);
		
		// -----------------------------------------------------
		
		OTLog::vOutput(1, "\nCommand: %s\nNymID:    %s\nServerID: %s\n\nPublic Key:\n%s\n", 
				m_strCommand.Get(), m_strNymID.Get(), m_strServerID.Get(), m_strNymPublicKey.Get());
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	
	else if (!strcmp("@createUserAccount", xml->getNodeName())) 
	{		
		OTString strSuccess;
		strSuccess		= xml->getAttributeValue("success");
		if (strSuccess.Compare("true"))
			m_bSuccess = true;
		else
			m_bSuccess = false;

		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		
		// -----------------------------------------------------
		
		const char *	pElementExpected	= "inReferenceTo";
		OTASCIIArmor &	ascTextExpected		= m_ascInReferenceTo;
		
		if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
		{
			OTLog::vError("Error in OTMessage::ProcessXMLNode: "
						  "Expected %s element with text field, for %s.\n", 
						  pElementExpected, m_strCommand.Get());
			return (-1); // error condition
		}
		
		// -----------------------------------------------------
		
		OTLog::vOutput(1, "\nCommand: %s  %s\nNymID:    %s\nServerID: %s\n\n\n", 
				m_strCommand.Get(), (m_bSuccess ? "SUCCESS" : "FAILED"), m_strNymID.Get(), 
				m_strServerID.Get());
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	
	
	else if (!strcmp("getRequest", xml->getNodeName())) 
	{		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		
		OTLog::vOutput(1, "\nCommand: %s\nNymID:    %s\nServerID: %s\n\n", 
				m_strCommand.Get(), m_strNymID.Get(), m_strServerID.Get());
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	else if (!strcmp("@getRequest", xml->getNodeName())) 
	{	
		OTString strSuccess;
		strSuccess		= xml->getAttributeValue("success");
		if (strSuccess.Compare("true"))
			m_bSuccess = true;
		else
			m_bSuccess = false;
		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strRequestNum = xml->getAttributeValue("requestNum");
		
		OTLog::vOutput(1, "\nCommand: %s   %s\nNymID:    %s\n"
				"ServerID: %s\nRequest Number:    %s\n\n", 
				m_strCommand.Get(), (m_bSuccess ? "SUCCESS" : "FAILED"), m_strNymID.Get(), 
				m_strServerID.Get(), m_strRequestNum.Get());
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	else if (!strcmp("outmailMessage", xml->getNodeName())) 
	{		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strNymID2		= xml->getAttributeValue("nymID2");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strRequestNum = xml->getAttributeValue("requestNum");
		
		// ----------------------------------------------------
		
		const char *	pElementExpected	= "messagePayload";
		OTASCIIArmor &	ascTextExpected		= m_ascPayload;
		
		if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
		{
			OTLog::vError("Error in OTMessage::ProcessXMLNode: "
						  "Expected %s element with text field, for %s.\n", 
						  pElementExpected, m_strCommand.Get());
			return (-1); // error condition
		}
		
		// ---------------------------------------------------
		
		OTLog::vOutput(1, "\nCommand: %s\nNymID:    %s\nNymID2:    %s\nServerID: %s\nRequest #: %s\n", 
					   m_strCommand.Get(), m_strNymID.Get(), m_strNymID2.Get(), m_strServerID.Get(), m_strRequestNum.Get());
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	
	else if (!strcmp("sendUserMessage", xml->getNodeName())) 
	{		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strNymID2		= xml->getAttributeValue("nymID2");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strRequestNum = xml->getAttributeValue("requestNum");
		
		const char *	pElementExpected	= "messagePayload";
		OTASCIIArmor &	ascTextExpected		= m_ascPayload;
		
		if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
		{
			OTLog::vError("Error in OTMessage::ProcessXMLNode: "
						  "Expected %s element with text field, for %s.\n", 
						  pElementExpected, m_strCommand.Get());
			return (-1); // error condition
		}
		
		OTLog::vOutput(1, "\nCommand: %s\nNymID:    %s\nNymID2:    %s\nServerID: %s\nRequest #: %s\n", 
					   m_strCommand.Get(), m_strNymID.Get(), m_strNymID2.Get(), m_strServerID.Get(), m_strRequestNum.Get());
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	else if (!strcmp("@sendUserMessage", xml->getNodeName())) 
	{		
		OTString strSuccess;
		strSuccess		= xml->getAttributeValue("success");
		if (strSuccess.Compare("true"))
			m_bSuccess = true;
		else
			m_bSuccess = false;
		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strNymID2		= xml->getAttributeValue("nymID2");
		m_strServerID	= xml->getAttributeValue("serverID");
				
		OTLog::vOutput(1, "\nCommand: %s   %s\nNymID:    %s\nNymID2:    %s\n"
					   "ServerID: %s\n\n", 
					   m_strCommand.Get(), (m_bSuccess ? "SUCCESS" : "FAILED"),
					   m_strNymID.Get(), m_strNymID2.Get(), m_strServerID.Get()
					   );
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	
	
	
	else if (!strcmp("checkUser", xml->getNodeName())) 
	{		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strNymID2		= xml->getAttributeValue("nymID2");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strRequestNum = xml->getAttributeValue("requestNum");
		
		OTLog::vOutput(1, "\nCommand: %s\nNymID:    %s\nNymID2:    %s\nServerID: %s\nRequest #: %s\n", 
					   m_strCommand.Get(), m_strNymID.Get(), m_strNymID2.Get(), m_strServerID.Get(), m_strRequestNum.Get());
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	else if (!strcmp("@checkUser", xml->getNodeName())) 
	{		
		OTString strSuccess;
		strSuccess		= xml->getAttributeValue("success");
		if (strSuccess.Compare("true"))
			m_bSuccess = true;
		else
			m_bSuccess = false;
		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strNymID2		= xml->getAttributeValue("nymID2");
		m_strServerID	= xml->getAttributeValue("serverID");
		
		// -----------------------------------------------------
		
		const char * pElementExpected;
		if (m_bSuccess)
			pElementExpected = "nymPublicKey";
		else
			pElementExpected = "inReferenceTo";

		OTASCIIArmor 	ascTextExpected;
		
		if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
		{
			OTLog::vError("Error in OTMessage::ProcessXMLNode: "
						  "Expected %s element with text field, for %s.\n", 
						  pElementExpected, m_strCommand.Get());
			return (-1); // error condition
		}
		
		if (m_bSuccess)
			m_strNymPublicKey.Set(ascTextExpected);
		else
			m_ascInReferenceTo = ascTextExpected;				

		// -----------------------------------------------------
		
		if (m_bSuccess)
			OTLog::vOutput(1, "\nCommand: %s   %s\nNymID:    %s\nNymID2:    %s\n"
						   "ServerID: %s\nNym2 Public Key:\n%s\n\n", 
						   m_strCommand.Get(), (m_bSuccess ? "SUCCESS" : "FAILED"),
						   m_strNymID.Get(), m_strNymID2.Get(), m_strServerID.Get(),
						   m_strNymPublicKey.Get());
		else
			OTLog::vOutput(1, "\nCommand: %s   %s\nNymID:    %s\nNymID2:    %s\n"
						   "ServerID: %s\n\n", 
						   m_strCommand.Get(), (m_bSuccess ? "SUCCESS" : "FAILED"),
						   m_strNymID.Get(), m_strNymID2.Get(), m_strServerID.Get() // m_ascInReferenceTo.Get()
						   );
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	
	else if (!strcmp("issueAssetType", xml->getNodeName())) 
	{	
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strAssetID	= xml->getAttributeValue("assetType");
		m_strRequestNum	= xml->getAttributeValue("requestNum");
		
		// ----------------------------------------------------
		
		const char *	pElementExpected	= "assetContract";
		OTASCIIArmor &	ascTextExpected		= m_ascPayload;
		
		if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
		{
			OTLog::vError("Error in OTMessage::ProcessXMLNode: "
						  "Expected %s element with text field, for %s.\n", 
						  pElementExpected, m_strCommand.Get());
			return (-1); // error condition
		}
		
		// ---------------------------------------------------
		
		OTLog::vOutput(1, "\nCommand: %s \nNymID:    %s\n"
				"ServerID: %s\nRequest#: %s\nAsset Type:\n%s\n\n", 
				m_strCommand.Get(), m_strNymID.Get(), 
				m_strServerID.Get(), m_strRequestNum.Get(), m_strAssetID.Get());
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	else if (!strcmp("@issueAssetType", xml->getNodeName())) 
	{	
		OTString strSuccess;
		strSuccess		= xml->getAttributeValue("success");
		if (strSuccess.Compare("true"))
			m_bSuccess = true;
		else
			m_bSuccess = false;
		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strAssetID	= xml->getAttributeValue("assetType");
		m_strAcctID		= xml->getAttributeValue("accountID");
		
		// If successful, we need to read 2 more things: inReferenceTo and issuerAccount payload.
		// If failure, then we only need to read 1 thing: inReferenceTo
		// At this point, we do not send the REASON WHY if it failed.
		
		// ----------------------------------------------------
		{
			const char *	pElementExpected	= "inReferenceTo";
			OTASCIIArmor &	ascTextExpected		= m_ascInReferenceTo;
			
			if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
			{
				OTLog::vError("Error in OTMessage::ProcessXMLNode: "
							  "Expected %s element with text field, for %s.\n", 
							  pElementExpected, m_strCommand.Get());
				return (-1); // error condition
			}
		}
		// ----------------------------------------------------
		if (m_bSuccess)
		{
			const char *	pElementExpected	= "issuerAccount";
			OTASCIIArmor &	ascTextExpected		= m_ascPayload;
			
			if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
			{
				OTLog::vError("Error in OTMessage::ProcessXMLNode: "
							  "Expected %s element with text field, for %s.\n", 
							  pElementExpected, m_strCommand.Get());
				return (-1); // error condition
			}
		}
		// ---------------------------------------------------
		
		// Did we find everything we were looking for?
		// If the "command responding to" isn't there, 
		// OR if it was successful but the Payload isn't there, then failure.
		if (!m_ascInReferenceTo.GetLength() || (m_bSuccess && !m_ascPayload.GetLength()))
		{
			OTLog::Error("Error in OTMessage::ProcessXMLNode:\n"
					"Expected issuerAccount and/or inReferenceTo elements with text fields in "
					"@issueAssetType reply\n");
			return (-1); // error condition			
		}
		
		OTString acctContents(m_ascPayload);
		OTLog::vOutput(1, "\nCommand: %s   %s\nNymID:    %s\nAccountID: %s\nAsset Type ID: %s\n"
				"ServerID: %s\n\n",
				//	"****New Account****:\n%s\n", 
				m_strCommand.Get(), (m_bSuccess?"SUCCESS":"FAILED"), m_strNymID.Get(), m_strAcctID.Get(),
				m_strAssetID.Get(), m_strServerID.Get()
				//	m_ascInReferenceTo.Get(), 
				//acctContents.Get()
				);
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	
	// -------------------------------------------------------------------------------------------
	
	
	else if (!strcmp("createAccount", xml->getNodeName())) 
	{	
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strAssetID	= xml->getAttributeValue("assetType");
		m_strRequestNum	= xml->getAttributeValue("requestNum");
		
		OTLog::vOutput(1, "\nCommand: %s \nNymID:    %s\n"
				"ServerID: %s\nRequest#: %s\nAsset Type:\n%s\n\n", 
				m_strCommand.Get(), m_strNymID.Get(), 
				m_strServerID.Get(), m_strRequestNum.Get(), m_strAssetID.Get());
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	else if (!strcmp("@createAccount", xml->getNodeName())) 
	{	
		OTString strSuccess;
		strSuccess		= xml->getAttributeValue("success");
		if (strSuccess.Compare("true"))
			m_bSuccess = true;
		else
			m_bSuccess = false;
		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strAcctID		= xml->getAttributeValue("accountID");
		
		
		// If successful, we need to read 2 more things: inReferenceTo and issuerAccount payload.
		// If failure, then we only need to read 1 thing: inReferenceTo
		// At this point, we do not send the REASON WHY if it failed.
		
		// ----------------------------------------------------
		{
			const char *	pElementExpected	= "inReferenceTo";
			OTASCIIArmor &	ascTextExpected		= m_ascInReferenceTo;
			
			if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
			{
				OTLog::vError("Error in OTMessage::ProcessXMLNode: "
							  "Expected %s element with text field, for %s.\n", 
							  pElementExpected, m_strCommand.Get());
				return (-1); // error condition
			}
		}
		// ----------------------------------------------------
		if (m_bSuccess)
		{
			const char *	pElementExpected	= "newAccount";
			OTASCIIArmor &	ascTextExpected		= m_ascPayload;
			
			if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
			{
				OTLog::vError("Error in OTMessage::ProcessXMLNode: "
							  "Expected %s element with text field, for %s.\n", 
							  pElementExpected, m_strCommand.Get());
				return (-1); // error condition
			}
		}
		// ---------------------------------------------------
				
		// Did we find everything we were looking for?
		// If the "command responding to" isn't there, 
		// OR if it was successful but the Payload isn't there, then failure.
		if (!m_ascInReferenceTo.GetLength() || (m_bSuccess && !m_ascPayload.GetLength()))
		{
			OTLog::Error("Error in OTMessage::ProcessXMLNode:\n"
					"Expected newAccount and/or inReferenceTo elements with text fields in "
					"@createAccount reply\n");
			return (-1); // error condition			
		}
		
		OTLog::vOutput(1, "\nCommand: %s   %s\nNymID:    %s\nAccountID: %s\n"
				"ServerID: %s\n\n",
				//	"****New Account****:\n%s\n", 
				m_strCommand.Get(), (m_bSuccess?"SUCCESS":"FAILED"), m_strNymID.Get(), m_strAcctID.Get(),
				m_strServerID.Get()
				//	m_ascInReferenceTo.Get(), 
				//acctContents.Get()
				);
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
		
	
	// -------------------------------------------------------------------------------------------
	
	else if (!strcmp("exchangeBasket", xml->getNodeName())) 
	{	
		OTString strExchange;
		strExchange		= xml->getAttributeValue("exchange");
		if (strExchange.Compare("in"))
			m_bBool = true;
		else
			m_bBool = false;
		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strAssetID	= xml->getAttributeValue("assetType");
		m_strRequestNum	= xml->getAttributeValue("requestNum");
		
		// ----------------------------------------------------
		{
			const char *	pElementExpected	= "exchangeRequest";
			OTASCIIArmor &	ascTextExpected		= m_ascPayload;
			
			if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
			{
				OTLog::vError("Error in OTMessage::ProcessXMLNode: "
							  "Expected %s element with text field, for %s.\n", 
							  pElementExpected, m_strCommand.Get());
				return (-1); // error condition
			}
		}
		// ----------------------------------------------------
				
		// Did we find everything we were looking for?
		// If the Payload isn't there, then failure.
		if (!m_ascPayload.GetLength())
		{
			OTLog::Error("Error in OTMessage::ProcessXMLNode:\n"
					"Expected exchangeRequest element with text field in "
					"exchangeBasket message\n");
			return (-1); // error condition			
		}
		
		OTLog::vOutput(1, "\nCommand: %s \nNymID:    %s\n"
				"ServerID: %s\nAsset Type: %s\nRequest#: %s\n\n", 
				m_strCommand.Get(), m_strNymID.Get(), 
				m_strServerID.Get(), m_strAssetID.Get(), m_strRequestNum.Get());
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	
	else if (!strcmp("@exchangeBasket", xml->getNodeName())) 
	{	
		OTString strSuccess;
		strSuccess		= xml->getAttributeValue("success");
		if (strSuccess.Compare("true"))
			m_bSuccess = true;
		else
			m_bSuccess = false;
		
		OTString strExchange;
		strExchange		= xml->getAttributeValue("exchange");
		if (strExchange.Compare("in"))
			m_bBool = true;
		else
			m_bBool = false;
		
		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strAssetID	= xml->getAttributeValue("assetType");
		
		// ----------------------------------------------------
		{
			const char *	pElementExpected	= "inReferenceTo";
			OTASCIIArmor &	ascTextExpected		= m_ascInReferenceTo;
			
			if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
			{
				OTLog::vError("Error in OTMessage::ProcessXMLNode: "
							  "Expected %s element with text field, for %s.\n", 
							  pElementExpected, m_strCommand.Get());
				return (-1); // error condition
			}
		}
		// ----------------------------------------------------
		
		// Did we find everything we were looking for?
		// If the "command responding to" isn't there, 
		// OR if it was successful but the Payload isn't there, then failure.
		if (!m_ascInReferenceTo.GetLength())
		{
			OTLog::Error("Error in OTMessage::ProcessXMLNode:\n"
					"Expected inReferenceTo element with text fields in "
					"@exchangeBasket reply\n");
			return (-1); // error condition			
		}
		
		OTLog::vOutput(1, "\nCommand: %s   %s\nNymID:    %s\nAsset Type ID: %s\nExchange: %s\n"
				"ServerID: %s\n\n",
				m_strCommand.Get(), (m_bSuccess?"SUCCESS":"FAILED"), 
				m_strNymID.Get(), 
				m_strAssetID.Get(),
				(m_bBool ? "IN" : "OUT"),
				m_strServerID.Get()
				);
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	
	
	// -------------------------------------------------------------------------------------------
	
	else if (!strcmp("issueBasket", xml->getNodeName())) 
	{	
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strRequestNum	= xml->getAttributeValue("requestNum");
		
		// ----------------------------------------------------
		{
			const char *	pElementExpected	= "currencyBasket";
			OTASCIIArmor &	ascTextExpected		= m_ascPayload;
			
			if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
			{
				OTLog::vError("Error in OTMessage::ProcessXMLNode: "
							  "Expected %s element with text field, for %s.\n", 
							  pElementExpected, m_strCommand.Get());
				return (-1); // error condition
			}
		}
		// ----------------------------------------------------
		
		// Did we find everything we were looking for?
		// If the Payload isn't there, then failure.
		if (!m_ascPayload.GetLength())
		{
			OTLog::Error("Error in OTMessage::ProcessXMLNode:\n"
					"Expected currencyBasket element with text fields in "
					"issueBasket message\n");
			return (-1); // error condition			
		}
		
		OTLog::vOutput(1, "\nCommand: %s \nNymID:    %s\n"
				"ServerID: %s\nRequest#: %s\n\n", 
				m_strCommand.Get(), m_strNymID.Get(), 
				m_strServerID.Get(), m_strRequestNum.Get());
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	else if (!strcmp("@issueBasket", xml->getNodeName())) 
	{	
		OTString strSuccess;
		strSuccess		= xml->getAttributeValue("success");
		if (strSuccess.Compare("true"))
			m_bSuccess = true;
		else
			m_bSuccess = false;
		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strAssetID	= xml->getAttributeValue("assetType");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strAcctID		= xml->getAttributeValue("accountID");
		
		// ----------------------------------------------------
		{
			const char *	pElementExpected	= "inReferenceTo";
			OTASCIIArmor &	ascTextExpected		= m_ascInReferenceTo;
			
			if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
			{
				OTLog::vError("Error in OTMessage::ProcessXMLNode: "
							  "Expected %s element with text field, for %s.\n", 
							  pElementExpected, m_strCommand.Get());
				return (-1); // error condition
			}
		}
		// ----------------------------------------------------
		
		// Did we find everything we were looking for?
		// If the "command responding to" isn't there, 
		// OR if it was successful but the Payload isn't there, then failure.
		if (!m_ascInReferenceTo.GetLength())
		{
			OTLog::Error("Error in OTMessage::ProcessXMLNode:\n"
					"Expected inReferenceTo element with text fields in "
					"@issueBasket reply\n");
			return (-1); // error condition			
		}
		
		OTLog::vOutput(1, "\nCommand: %s   %s\nNymID:    %s\nAccountID: %s\nAssetTypeID: %s\n"
				"ServerID: %s\n\n",
				m_strCommand.Get(), (m_bSuccess?"SUCCESS":"FAILED"), 
				m_strNymID.Get(), 
				m_strAcctID.Get(),
				m_strAssetID.Get(),
				m_strServerID.Get()
				);
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	
	
	// ------------------------------------------------------------------------
	
	else if (!strcmp("getTransactionNum", xml->getNodeName())) 
	{	
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strRequestNum	= xml->getAttributeValue("requestNum");
		
		OTLog::vOutput(1, "\n Command: %s \n NymID:    %s\n"
				" ServerID: %s\n Request#: %s\n\n", 
				m_strCommand.Get(), m_strNymID.Get(),
				m_strServerID.Get(), m_strRequestNum.Get());
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
		
	else if (!strcmp("@getTransactionNum", xml->getNodeName())) 
	{	
		OTString strSuccess;
		strSuccess		= xml->getAttributeValue("success");
		if (strSuccess.Compare("true"))
			m_bSuccess = true;
		else
			m_bSuccess = false;
		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		
		OTLog::vOutput(1, "\n Command: %s   %s\n NymID:    %s\n"
				" ServerID: %s\n\n",
				m_strCommand.Get(), (m_bSuccess?"SUCCESS":"FAILED"), 
				m_strNymID.Get(), m_strServerID.Get()
				);
		
		nReturnVal = 1;
	}
	
	
	// -------------------------------------------------------------------------------------------
	
	else if (!strcmp("notarizeTransactions", xml->getNodeName())) 
	{	
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strAcctID		= xml->getAttributeValue("accountID");
		m_strRequestNum	= xml->getAttributeValue("requestNum");
		
		// ----------------------------------------------------
		{
			const char *	pElementExpected	= "accountLedger";
			OTASCIIArmor &	ascTextExpected		= m_ascPayload;
			
			if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
			{
				OTLog::vError("Error in OTMessage::ProcessXMLNode: "
							  "Expected %s element with text field, for %s.\n", 
							  pElementExpected, m_strCommand.Get());
				return (-1); // error condition
			}
		}
		// ----------------------------------------------------
		
		OTLog::vOutput(1, "\n Command: %s \n NymID:    %s\n AccountID:    %s\n"
				" ServerID: %s\n Request#: %s\n\n", 
				m_strCommand.Get(), m_strNymID.Get(), m_strAcctID.Get(),
				m_strServerID.Get(), m_strRequestNum.Get());
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	else if (!strcmp("@notarizeTransactions", xml->getNodeName())) 
	{	
		OTString strSuccess;
		strSuccess		= xml->getAttributeValue("success");
		if (strSuccess.Compare("true"))
			m_bSuccess = true;
		else
			m_bSuccess = false;
		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strAcctID		= xml->getAttributeValue("accountID");
		
		// If successful or failure, we need to read 2 more things: 
		// inReferenceTo and the responseLedger payload.
		// At this point, we do not send the REASON WHY if it failed.
		
		// ----------------------------------------------------
		{
			const char *	pElementExpected	= "inReferenceTo";
			OTASCIIArmor &	ascTextExpected		= m_ascInReferenceTo;
			
			if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
			{
				OTLog::vError("Error in OTMessage::ProcessXMLNode: "
							  "Expected %s element with text field, for %s.\n", 
							  pElementExpected, m_strCommand.Get());
				return (-1); // error condition
			}
		}
		// ----------------------------------------------------
		{
			const char *	pElementExpected	= "responseLedger";
			OTASCIIArmor &	ascTextExpected		= m_ascPayload;
			
			if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
			{
				OTLog::vError("Error in OTMessage::ProcessXMLNode: "
							  "Expected %s element with text field, for %s.\n", 
							  pElementExpected, m_strCommand.Get());
				return (-1); // error condition
			}
		}
		// ----------------------------------------------------

		// Did we find everything we were looking for?
		// If the "command responding to" isn't there, or the Payload isn't there, then failure.
		if (!m_ascInReferenceTo.GetLength() || (!m_ascPayload.GetLength()))
		{
			OTLog::Error("Error in OTMessage::ProcessXMLNode:\n"
					"Expected responseLedger and/or inReferenceTo elements with text fields in "
					"@notarizeTransactions reply\n");
			return (-1); // error condition			
		}
		
		//		OTString acctContents(m_ascPayload);
		OTLog::vOutput(1, "\n Command: %s   %s\n NymID:    %s\n AccountID: %s\n"
				" ServerID: %s\n\n",
				//	"****New Account****:\n%s\n", 
				m_strCommand.Get(), (m_bSuccess?"SUCCESS":"FAILED"), 
				m_strNymID.Get(), m_strAcctID.Get(), m_strServerID.Get()
				//	m_ascInReferenceTo.Get(), 
				//acctContents.Get()
				);
		
		nReturnVal = 1;
	}
	
	
	// -------------------------------------------------------------------------------------------
	
	else if (!strcmp("getInbox", xml->getNodeName())) 
	{		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strAcctID		= xml->getAttributeValue("accountID");
		m_strRequestNum = xml->getAttributeValue("requestNum");
		
		OTLog::vOutput(1, "\nCommand: %s\nNymID:    %s\nServerID: %s\nAccountID:    %s\nRequest #: %s\n", 
					   m_strCommand.Get(), m_strNymID.Get(), m_strServerID.Get(), m_strAcctID.Get(), m_strRequestNum.Get());
		
		nReturnVal = 1;
	}
	
	
	// -------------------------------------------------------------------------------------------
	
	
	else if (!strcmp("getNymbox", xml->getNodeName())) 
	{		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strRequestNum = xml->getAttributeValue("requestNum");
		
		OTLog::vOutput(1, "\nCommand: %s\nNymID:    %s\nServerID: %s\nRequest #: %s\n", 
					   m_strCommand.Get(), m_strNymID.Get(), m_strServerID.Get(),m_strRequestNum.Get());
		
		nReturnVal = 1;
	}
	
	
	// -------------------------------------------------------------------------------------------
	
	
	else if (!strcmp("@getInbox", xml->getNodeName())) 
	{		
		OTString strSuccess;
		strSuccess		= xml->getAttributeValue("success");
		if (strSuccess.Compare("true"))
			m_bSuccess = true;
		else
			m_bSuccess = false;
		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strAcctID		= xml->getAttributeValue("accountID");
		
		// -----------------------------------------------------
		
		const char * pElementExpected;
		if (m_bSuccess)
			pElementExpected = "inboxLedger";
		else
			pElementExpected = "inReferenceTo";
		
		OTASCIIArmor 	ascTextExpected;
		
		if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
		{
			OTLog::vError("Error in OTMessage::ProcessXMLNode: "
						  "Expected %s element with text field, for %s.\n", 
						  pElementExpected, m_strCommand.Get());
			return (-1); // error condition
		}
		
		if (m_bSuccess)
			m_ascPayload = ascTextExpected;
		else
			m_ascInReferenceTo = ascTextExpected;				
		
		// -----------------------------------------------------
				
		OTLog::vOutput(1, "\nCommand: %s   %s\nNymID:    %s\nAccountID:    %s\n"
					   "ServerID: %s\n\n", 
					   m_strCommand.Get(), (m_bSuccess ? "SUCCESS" : "FAILED"),
					   m_strNymID.Get(), m_strAcctID.Get(), m_strServerID.Get());
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	
	
	else if (!strcmp("@getNymbox", xml->getNodeName())) 
	{		
		OTString strSuccess;
		strSuccess		= xml->getAttributeValue("success");
		if (strSuccess.Compare("true"))
			m_bSuccess = true;
		else
			m_bSuccess = false;
		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		
		// -----------------------------------------------------
		
		const char * pElementExpected;
		if (m_bSuccess)
			pElementExpected = "nymboxLedger";
		else
			pElementExpected = "inReferenceTo";
		
		OTASCIIArmor 	ascTextExpected;
		
		if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
		{
			OTLog::vError("Error in OTMessage::ProcessXMLNode: "
						  "Expected %s element with text field, for %s.\n", 
						  pElementExpected, m_strCommand.Get());
			return (-1); // error condition
		}
		
		if (m_bSuccess)
			m_ascPayload = ascTextExpected;
		else
			m_ascInReferenceTo = ascTextExpected;				
		
		// -----------------------------------------------------
		
		OTLog::vOutput(1, "\nCommand: %s   %s\nNymID:    %s\n"
					   "ServerID: %s\n\n", 
					   m_strCommand.Get(), (m_bSuccess ? "SUCCESS" : "FAILED"),
					   m_strNymID.Get(), m_strServerID.Get());
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	
	
	else if (!strcmp("getOutbox", xml->getNodeName())) 
	{		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strAcctID		= xml->getAttributeValue("accountID");
		m_strRequestNum = xml->getAttributeValue("requestNum");
		
		OTLog::vOutput(1, "\nCommand: %s\nNymID:    %s\nServerID: %s\nAccountID:    %s\nRequest #: %s\n", 
					   m_strCommand.Get(), m_strNymID.Get(), m_strServerID.Get(), m_strAcctID.Get(), m_strRequestNum.Get());
		
		nReturnVal = 1;
	}
	
	
	// -------------------------------------------------------------------------------------------
	
	
	else if (!strcmp("@getOutbox", xml->getNodeName())) 
	{		
		OTString strSuccess;
		strSuccess		= xml->getAttributeValue("success");
		if (strSuccess.Compare("true"))
			m_bSuccess = true;
		else
			m_bSuccess = false;
		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strAcctID		= xml->getAttributeValue("accountID");
		
		// -----------------------------------------------------
		
		const char * pElementExpected;
		if (m_bSuccess)
			pElementExpected = "outboxLedger";
		else
			pElementExpected = "inReferenceTo";
		
		OTASCIIArmor 	ascTextExpected;
		
		if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
		{
			OTLog::vError("Error in OTMessage::ProcessXMLNode: "
						  "Expected %s element with text field, for %s.\n", 
						  pElementExpected, m_strCommand.Get());
			return (-1); // error condition
		}
		
		if (m_bSuccess)
			m_ascPayload = ascTextExpected;
		else
			m_ascInReferenceTo = ascTextExpected;				
		
		// -----------------------------------------------------
		
		OTLog::vOutput(1, "\nCommand: %s   %s\nNymID:    %s\nAccountID:    %s\n"
					   "ServerID: %s\n\n", 
					   m_strCommand.Get(), (m_bSuccess ? "SUCCESS" : "FAILED"),
					   m_strNymID.Get(), m_strAcctID.Get(), m_strServerID.Get());
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	
	/*
	 
	 // ------------------------------------------------------------------------
	 
	 if (m_strCommand.Compare("getContract"))
	 {		
	 m_xmlUnsigned.Concatenate("<%s\n" // Command
	 " nymID=\"%s\"\n"
	 " serverID=\"%s\"\n"
	 " assetType=\"%s\"\n"
	 " requestNum=\"%s\""
	 " >\n\n",
	 m_strCommand.Get(),
	 m_strNymID.Get(),
	 m_strServerID.Get(),
	 m_strAssetID.Get(),
	 m_strRequestNum.Get()
	 );
	 
	 m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	 } // ------------------------------------------------------------------------
	 
	 
	 
	 // ------------------------------------------------------------------------
	 
	 // the Payload contains an ascii-armored OTAssetContract object.
	 if (m_strCommand.Compare("@getContract"))
	 {		
	 m_xmlUnsigned.Concatenate("<%s\n" // Command
	 " success=\"%s\"\n"
	 " nymID=\"%s\"\n"
	 " serverID=\"%s\"\n"
	 " assetType=\"%s\""
	 " >\n\n",
	 m_strCommand.Get(),
	 (m_bSuccess ? "true" : "false"),
	 m_strNymID.Get(),
	 m_strServerID.Get(), 
	 m_strAssetID.Get()
	 );
	 
	 if (!m_bSuccess && m_ascInReferenceTo.GetLength())
	 m_xmlUnsigned.Concatenate("<inReferenceTo>\n%s</inReferenceTo>\n\n", m_ascInReferenceTo.Get());
	 
	 // I would check if this was empty, but it should never be empty...
	 // famous last words.
	 if (m_bSuccess && m_ascPayload.GetLength())
	 m_xmlUnsigned.Concatenate("<assetContract>\n%s</assetContract>\n\n", m_ascPayload.Get());
	 
	 m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	 } // ------------------------------------------------------------------------
	 
	 
	 
	 // ------------------------------------------------------------------------
	 
	 if (m_strCommand.Compare("getMint"))
	 {		
	 m_xmlUnsigned.Concatenate("<%s\n" // Command
	 " nymID=\"%s\"\n"
	 " serverID=\"%s\"\n"
	 " assetType=\"%s\"\n"
	 " requestNum=\"%s\""
	 " >\n\n",
	 m_strCommand.Get(),
	 m_strNymID.Get(),
	 m_strServerID.Get(),
	 m_strAssetID.Get(),
	 m_strRequestNum.Get()
	 );
	 
	 m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	 } // ------------------------------------------------------------------------
	 
	 
	 
	 // ------------------------------------------------------------------------
	 
	 // the Payload contains an ascii-armored OTMint object.
	 if (m_strCommand.Compare("@getMint"))
	 {		
	 m_xmlUnsigned.Concatenate("<%s\n" // Command
	 " success=\"%s\"\n"
	 " nymID=\"%s\"\n"
	 " serverID=\"%s\"\n"
	 " assetType=\"%s\""
	 " >\n\n",
	 m_strCommand.Get(),
	 (m_bSuccess ? "true" : "false"),
	 m_strNymID.Get(),
	 m_strServerID.Get(), 
	 m_strAssetID.Get()
	 );
	 
	 if (!m_bSuccess && m_ascInReferenceTo.GetLength())
	 m_xmlUnsigned.Concatenate("<inReferenceTo>\n%s</inReferenceTo>\n\n", m_ascInReferenceTo.Get());
	 
	 // I would check if this was empty, but it should never be empty...
	 // famous last words.
	 if (m_bSuccess && m_ascPayload.GetLength())
	 m_xmlUnsigned.Concatenate("<mint>\n%s</mint>\n\n", m_ascPayload.Get());
	 
	 m_xmlUnsigned.Concatenate("</%s>\n\n", m_strCommand.Get());
	 */
	
	// ------------------------------------------------------------------------
	
	else if (!strcmp("getAccount", xml->getNodeName())) 
	{		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strAcctID		= xml->getAttributeValue("accountID");
		m_strRequestNum = xml->getAttributeValue("requestNum");
		
		OTLog::vOutput(1, "\nCommand: %s\nNymID:    %s\nServerID: %s\nAccountID:    %s\nRequest #: %s\n", 
				m_strCommand.Get(), m_strNymID.Get(), m_strServerID.Get(), m_strAcctID.Get(), m_strRequestNum.Get());
		
		nReturnVal = 1;
	}
	
	
	// -------------------------------------------------------------------------------------------
	
	
	else if (!strcmp("@getAccount", xml->getNodeName())) 
	{		
		OTString strSuccess;
		strSuccess		= xml->getAttributeValue("success");
		if (strSuccess.Compare("true"))
			m_bSuccess = true;
		else
			m_bSuccess = false;
		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strAcctID		= xml->getAttributeValue("accountID");
		
		// -----------------------------------------------------
		
		const char * pElementExpected;
		if (m_bSuccess)
			pElementExpected = "assetAccount";
		else
			pElementExpected = "inReferenceTo";
		
		OTASCIIArmor 	ascTextExpected;
		
		if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
		{
			OTLog::vError("Error in OTMessage::ProcessXMLNode: "
						  "Expected %s element with text field, for %s.\n", 
						  pElementExpected, m_strCommand.Get());
			return (-1); // error condition
		}
		
		if (m_bSuccess)
			m_ascPayload = ascTextExpected;
		else
			m_ascInReferenceTo = ascTextExpected;				
		
		// -----------------------------------------------------
		
		OTLog::vOutput(1, "\nCommand: %s   %s\nNymID:    %s\nAccountID:    %s\n"
				"ServerID: %s\n\n", 
				m_strCommand.Get(), (m_bSuccess ? "SUCCESS" : "FAILED"),
				m_strNymID.Get(), m_strAcctID.Get(), m_strServerID.Get());
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	
	// ------------------------------------------------------------------------
	
	else if (!strcmp("getContract", xml->getNodeName())) 
	{		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strAssetID	= xml->getAttributeValue("assetType");
		m_strRequestNum = xml->getAttributeValue("requestNum");
		
		OTLog::vOutput(1, "\nCommand: %s\nNymID:    %s\nServerID: %s\nAsset Type:    %s\nRequest #: %s\n", 
				m_strCommand.Get(), m_strNymID.Get(), m_strServerID.Get(), m_strAssetID.Get(), m_strRequestNum.Get());
		
		nReturnVal = 1;
	}
	
	
	// -------------------------------------------------------------------------------------------
	
	
	else if (!strcmp("@getContract", xml->getNodeName())) 
	{		
		OTString strSuccess;
		strSuccess		= xml->getAttributeValue("success");
		if (strSuccess.Compare("true"))
			m_bSuccess = true;
		else
			m_bSuccess = false;
		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strAssetID	= xml->getAttributeValue("assetType");
		
		// -----------------------------------------------------
		
		const char * pElementExpected;
		if (m_bSuccess)
			pElementExpected = "assetContract";
		else
			pElementExpected = "inReferenceTo";
		
		OTASCIIArmor 	ascTextExpected;
		
		if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
		{
			OTLog::vError("Error in OTMessage::ProcessXMLNode: "
						  "Expected %s element with text field, for %s.\n", 
						  pElementExpected, m_strCommand.Get());
			return (-1); // error condition
		}
		
		if (m_bSuccess)
			m_ascPayload = ascTextExpected;
		else
			m_ascInReferenceTo = ascTextExpected;				
		
		// -----------------------------------------------------
		
		OTLog::vOutput(1, "\nCommand: %s   %s\nNymID:    %s\nAsset Type ID:    %s\n"
				"ServerID: %s\n\n", 
				m_strCommand.Get(), (m_bSuccess ? "SUCCESS" : "FAILED"),
				m_strNymID.Get(), m_strAssetID.Get(), m_strServerID.Get());
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	
	// ------------------------------------------------------------------------
	
	else if (!strcmp("getMint", xml->getNodeName())) 
	{		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strAssetID	= xml->getAttributeValue("assetType");
		m_strRequestNum = xml->getAttributeValue("requestNum");
		
		OTLog::vOutput(1, "\nCommand: %s\nNymID:    %s\nServerID: %s\nAsset Type:    %s\nRequest #: %s\n", 
				m_strCommand.Get(), m_strNymID.Get(), m_strServerID.Get(), m_strAssetID.Get(), m_strRequestNum.Get());
		
		nReturnVal = 1;
	}
	
	
	// -------------------------------------------------------------------------------------------
	
	
	else if (!strcmp("@getMint", xml->getNodeName())) 
	{		
		OTString strSuccess;
		strSuccess		= xml->getAttributeValue("success");
		if (strSuccess.Compare("true"))
			m_bSuccess = true;
		else
			m_bSuccess = false;
		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strAssetID	= xml->getAttributeValue("assetType");
		
		// -----------------------------------------------------
		
		const char * pElementExpected;
		if (m_bSuccess)
			pElementExpected = "mint";
		else
			pElementExpected = "inReferenceTo";
		
		OTASCIIArmor 	ascTextExpected;
		
		if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
		{
			OTLog::vError("Error in OTMessage::ProcessXMLNode: "
						  "Expected %s element with text field, for %s.\n", 
						  pElementExpected, m_strCommand.Get());
			return (-1); // error condition
		}
		
		if (m_bSuccess)
			m_ascPayload = ascTextExpected;
		else
			m_ascInReferenceTo = ascTextExpected;				
		
		// -----------------------------------------------------
		
		OTLog::vOutput(1, "\nCommand: %s   %s\nNymID:    %s\nAsset Type ID:    %s\n"
				"ServerID: %s\n\n", 
				m_strCommand.Get(), (m_bSuccess ? "SUCCESS" : "FAILED"),
				m_strNymID.Get(), m_strAssetID.Get(), m_strServerID.Get());
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	
	
	// -------------------------------------------------------------------------------------------
	
	
	else if (!strcmp("processInbox", xml->getNodeName())) 
	{	
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strAcctID		= xml->getAttributeValue("accountID");
		m_strRequestNum	= xml->getAttributeValue("requestNum");
		
		// ----------------------------------------------------
		{
			const char *	pElementExpected	= "processLedger";
			OTASCIIArmor &	ascTextExpected		= m_ascPayload;
			
			if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
			{
				OTLog::vError("Error in OTMessage::ProcessXMLNode: "
							  "Expected %s element with text field, for %s.\n", 
							  pElementExpected, m_strCommand.Get());
				return (-1); // error condition
			}
		}
		// ---------------------------------------------------		
		
		OTLog::vOutput(1, "\n Command: %s \n NymID:    %s\n AccountID:    %s\n"
					   " ServerID: %s\n Request#: %s\n\n", 
					   m_strCommand.Get(), m_strNymID.Get(), m_strAcctID.Get(),
					   m_strServerID.Get(), m_strRequestNum.Get());
		
		nReturnVal = 1;
	}
	
	
	// -------------------------------------------------------------------------------------------
	
	
	else if (!strcmp("processNymbox", xml->getNodeName())) 
	{	
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strRequestNum	= xml->getAttributeValue("requestNum");
		
		// ----------------------------------------------------
		{
			const char *	pElementExpected	= "processLedger";
			OTASCIIArmor &	ascTextExpected		= m_ascPayload;
			
			if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
			{
				OTLog::vError("Error in OTMessage::ProcessXMLNode: "
							  "Expected %s element with text field, for %s.\n", 
							  pElementExpected, m_strCommand.Get());
				return (-1); // error condition
			}
		}
		// ---------------------------------------------------		
		
		OTLog::vOutput(1, "\n Command: %s \n NymID:    %s\n"
					   " ServerID: %s\n Request#: %s\n\n", 
					   m_strCommand.Get(), m_strNymID.Get(),
					   m_strServerID.Get(), m_strRequestNum.Get());
		
		nReturnVal = 1;
	}
	
	// -------------------------------------------------------------------------------------------
	
	else if (!strcmp("@processInbox", xml->getNodeName())) 
	{	
		OTString strSuccess;
		strSuccess		= xml->getAttributeValue("success");
		if (strSuccess.Compare("true"))
			m_bSuccess = true;
		else
			m_bSuccess = false;
		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		m_strAcctID		= xml->getAttributeValue("accountID");
		
		// If successful or failure, we need to read 2 more things: 
		// inReferenceTo and the responseLedger payload.
		// At this point, we do not send the REASON WHY if it failed.
		
		// ----------------------------------------------------
		{
			const char *	pElementExpected	= "inReferenceTo";
			OTASCIIArmor &	ascTextExpected		= m_ascInReferenceTo;
			
			if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
			{
				OTLog::vError("Error in OTMessage::ProcessXMLNode: "
							  "Expected %s element with text field, for %s.\n", 
							  pElementExpected, m_strCommand.Get());
				return (-1); // error condition
			}
		}
		// ----------------------------------------------------
		{
			const char *	pElementExpected	= "responseLedger";
			OTASCIIArmor &	ascTextExpected		= m_ascPayload;
			
			if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
			{
				OTLog::vError("Error in OTMessage::ProcessXMLNode: "
							  "Expected %s element with text field, for %s.\n", 
							  pElementExpected, m_strCommand.Get());
				return (-1); // error condition
			}
		}
		// ----------------------------------------------------
				
		// Did we find everything we were looking for?
		// If the "command responding to" isn't there, or the Payload isn't there, then failure.
		if (!m_ascInReferenceTo.GetLength() || (!m_ascPayload.GetLength()))
		{
			OTLog::Error("Error in OTMessage::ProcessXMLNode:\n"
					"Expected responseLedger and/or inReferenceTo elements with text fields in "
					"@processInbox reply\n");
			return (-1); // error condition			
		}
		
		OTLog::vOutput(1, "\n Command: %s   %s\n NymID:    %s\n AccountID: %s\n"
				" ServerID: %s\n\n",
				//	"****New Account****:\n%s\n", 
				m_strCommand.Get(), (m_bSuccess?"SUCCESS":"FAILED"), 
				m_strNymID.Get(), m_strAcctID.Get(), m_strServerID.Get()
				);
		
		nReturnVal = 1;
	}
	
	
	// -------------------------------------------------------------------------------------------
	
	
	else if (!strcmp("@processNymbox", xml->getNodeName())) 
	{	
		OTString strSuccess;
		strSuccess		= xml->getAttributeValue("success");
		if (strSuccess.Compare("true"))
			m_bSuccess = true;
		else
			m_bSuccess = false;
		
		m_strCommand	= xml->getNodeName();  // Command
		m_strNymID		= xml->getAttributeValue("nymID");
		m_strServerID	= xml->getAttributeValue("serverID");
		
		// If successful or failure, we need to read 2 more things: 
		// inReferenceTo and the responseLedger payload.
		// At this point, we do not send the REASON WHY if it failed.
		
		// ----------------------------------------------------
		{
			const char *	pElementExpected	= "inReferenceTo";
			OTASCIIArmor &	ascTextExpected		= m_ascInReferenceTo;
			
			if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
			{
				OTLog::vError("Error in OTMessage::ProcessXMLNode: "
							  "Expected %s element with text field, for %s.\n", 
							  pElementExpected, m_strCommand.Get());
				return (-1); // error condition
			}
		}
		// ----------------------------------------------------
		{
			const char *	pElementExpected	= "responseLedger";
			OTASCIIArmor &	ascTextExpected		= m_ascPayload;
			
			if (false == LoadEncodedTextFieldByName(xml, ascTextExpected, pElementExpected))
			{
				OTLog::vError("Error in OTMessage::ProcessXMLNode: "
							  "Expected %s element with text field, for %s.\n", 
							  pElementExpected, m_strCommand.Get());
				return (-1); // error condition
			}
		}
		// ----------------------------------------------------
				
		// Did we find everything we were looking for?
		// If the "command responding to" isn't there, or the Payload isn't there, then failure.
		if (!m_ascInReferenceTo.GetLength() || (!m_ascPayload.GetLength()))
		{
			OTLog::Error("Error in OTMessage::ProcessXMLNode:\n"
						 "Expected responseLedger and/or inReferenceTo elements with text fields in "
						 "@processNymbox reply\n");
			return (-1); // error condition			
		}
		
		OTLog::vOutput(1, "\n Command: %s   %s\n NymID:    %s\n"
					   " ServerID: %s\n\n",
					   //	"****New Account****:\n%s\n", 
					   m_strCommand.Get(), (m_bSuccess?"SUCCESS":"FAILED"), 
					   m_strNymID.Get(), m_strServerID.Get()
					   );
		
		nReturnVal = 1;
	}
	
	
	// -------------------------------------------------------------------------------------------

	return nReturnVal;
}


// Most contracts do not override this function...
// But OTMessage does, because every request sent to the server needs to be signed.
// And each new request is a new message, that requires a new signature, unlike most
// contracts, (that always stay the same after they are signed.)
//
// We need to update the m_xmlUnsigned member with the message members before the
// actual signing occurs. (Presumably this is the whole reason why the account is being re-signed.)
//
// Normally, in other OTContract and derived classes, m_xmlUnsigned is read
// from the file and then kept read-only, since contracts do not normally change.
// But as new messages are sent, they must be signed. This function insures that
// the most up-to-date member contents are included in the request before it is signed.
//
// Note: Above comment is slightly old. This override is now here only for the purpose
// of releasing the signatures.  The other functionality is now handled by the
// UpdateContents member, which is called by the framework, and otherwise empty in
// default, but child classes such as OTMessage and OTAccount override it to save
// their contents just before signing.
// See OTMessage::UpdateContents near the top of this file for an example.
//
bool OTMessage::SignContract(const EVP_PKEY * pkey, OTSignature & theSignature,
						  const OTString & strHashType)
{
	// I release these, I assume, because a message only has one signer.
	ReleaseSignatures();
	
	m_bIsSigned = OTContract::SignContract(pkey, theSignature, strHashType);
	
	if (m_bIsSigned)
	{
//		OTLog::vError("\n******************************************************\n"
//				"Contents of signed message:\n\n%s******************************************************\n\n", m_xmlUnsigned.Get());
	}
	else
		OTLog::vOutput(1, "Failure signing message:\n%s", m_xmlUnsigned.Get());

	return m_bIsSigned;
}


// Unlike other contracts, which do not change over time, and thus calculate their ID
// from a hash of the file itself, OTMessage objects are different every time. Thus, we 
// cannot use a hash of the file to produce the Message ID.
//
// Message ID will probably become an important part of the protocol (to prevent replay attacks..)
// So I will end up using it. But for now, VerifyContractID will always return true.
//
bool OTMessage::VerifyContractID()
{
	return true;
}


bool OTMessage::SignContract(const OTPseudonym & theNym)
{
	return OTContract::SignContract(theNym);	
}


OTMessage::OTMessage() : OTContract(),
	m_bIsSigned(false), m_lDepth(0), m_lTransactionNum(0), m_bSuccess(false), m_bBool(false)
	 
{
	OTContract::m_strContractType.Set("MESSAGE");
}


OTMessage::~OTMessage()
{
	
}




// This actually saves to any file you want to pass it to.

bool OTMessage::SaveContractWallet(std::ofstream & ofs)
{
	OTString strContract;
	
	if (SaveContract(strContract))
	{
		ofs << strContract.Get();
		
		return true;
	}
	else 
	{
		return false;
	}
}

/*
bool OTMessage::SaveContractWallet(FILE * fl)
{
	OTString strContract;
	
	if (SaveContract(strContract))
	{
		fprintf(fl, "%s", strContract.Get());		
		return true;
	}
	else {
		return false;
	}
}
*/

/*
 else if (!strcmp("condition", xml->getNodeName()))
 {
 strConditionName  = xml->getAttributeValue("name");
 
 xml->read();
 
 if (EXN_TEXT == xml->getNodeType())
 {
 strConditionValue = xml->getNodeData();
 }
 else {
OTLog::vError("Error in OTContract::ProcessXMLNode: Condition without value: %s\n",
 strConditionName.Get());
 return (-1); // error condition
 }
 
 //Todo: add the conditions to a list in memory (on this object)
 
OTLog::vError("Loading condition \"%s\": %s----------(END DATA)----------\n", strConditionName.Get(), 
 strConditionValue.Get());
 
 return 1;
 } 
 */








































