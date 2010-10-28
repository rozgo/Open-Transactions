/************************************************************************************
 *    
 *  OTTrackable.cpp
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




#include <cstring>


#include "irrxml/irrXML.h"

using namespace irr;
using namespace io;




#include "OTTrackable.h"

// This class is like OTInstrument except with identifying info (such as transaction number) added.



OTTrackable::OTTrackable() : 
			OTInstrument()
{
	InitTrackable();
}




OTTrackable::OTTrackable(const OTIdentifier & SERVER_ID, const OTIdentifier & ASSET_ID) : 
			OTInstrument(SERVER_ID, ASSET_ID)
{
	InitTrackable();
}

OTTrackable::OTTrackable(const OTIdentifier & SERVER_ID, const OTIdentifier & ASSET_ID,
						 const OTIdentifier & ACCT_ID, const OTIdentifier & USER_ID) : 
			OTInstrument(SERVER_ID, ASSET_ID)
{
	InitTrackable();
	
	SetSenderAcctID(ACCT_ID);
	SetSenderUserID(USER_ID);
}

OTTrackable::~OTTrackable()
{
	// OTInstrument::~OTInstrument is called here automatically, and it calls Release() already.
	// So I don't need to call Release() here again, since it's already called by the parent.

}

void OTTrackable::InitTrackable()
{
	m_strContractType.Set("TRACKABLE"); // Should never happen in practice. A child class will overwrite it.

	m_lTransactionNum = 0;
	
}


void OTTrackable::Release()
{
	// If there were any dynamically allocated objects, clean them up here.
	m_SENDER_ACCT_ID.Release();	
	m_SENDER_USER_ID.Release();

	OTInstrument::Release(); // since I've overridden the base class, I call it now...
	
	// Then I call this to re-initialize everything for myself.
	InitTrackable(); 	
}



// return -1 if error, 0 if nothing, and 1 if the node was processed.
int OTTrackable::ProcessXMLNode(irr::io::IrrXMLReader*& xml)
{
	return 1;
}


void OTTrackable::UpdateContents()
{
	
}


bool OTTrackable::SaveContractWallet(std::ofstream & ofs)
{
	return true;
}
