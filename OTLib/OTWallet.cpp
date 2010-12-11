/************************************************************************************
 *    
 *  OTWallet.cpp
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


#include <cstdio>
#include <cstring>	

#include "OTIdentifier.h"
#include "OTString.h"
#include "OTPseudonym.h"

#include "OTWallet.h"
#include "OTLog.h"

#include "OTAssetContract.h"
#include "OTServerContract.h"
#include "OTContract.h"
#include "OTAccount.h"
#include "OTEnvelope.h"
#include "OTPurse.h"

#include "irrxml/irrXML.h"

using namespace irr;
using namespace io;


// TODO remove this pTemporaryNym variable, used for testing only.
extern OTPseudonym	* g_pTemporaryNym; 



OTWallet::OTWallet()
{
	m_pWithdrawalPurse = NULL;
}

OTWallet::~OTWallet()
{	
	Release();
}

void OTWallet::Release()
{	
	//1) Go through the map of Nyms and delete them. (They were dynamically allocated.)
	while (!m_mapNyms.empty())
	{		
		OTPseudonym * pNym = m_mapNyms.begin()->second;
		
		OT_ASSERT(NULL != pNym);
		
		delete pNym;
		pNym = NULL;
		
		m_mapNyms.erase(m_mapNyms.begin());
	}	
	
	//2) Go through the map of Contracts and delete them. (They were dynamically allocated.)
	while (!m_mapContracts.empty())
	{		
		OTAssetContract * pContract = m_mapContracts.begin()->second;
		
		OT_ASSERT(NULL != pContract);
		
		delete pContract;
		pContract = NULL;
		
		m_mapContracts.erase(m_mapContracts.begin());
	}	
	
	//3) Go through the map of Servers and delete them. (They were dynamically allocated.)
	while (!m_mapServers.empty())
	{		
		OTServerContract * pContract = m_mapServers.begin()->second;
		
		OT_ASSERT(NULL != pContract);
		
		delete pContract;
		pContract = NULL;
		
		m_mapServers.erase(m_mapServers.begin());
	}	
	
	//4) Go through the map of Accounts and delete them. (They were dynamically allocated.)
	while (!m_mapAccounts.empty())
	{		
		OTAccount * pAccount = m_mapAccounts.begin()->second;
		
		OT_ASSERT(NULL != pAccount);
		
		delete pAccount;
		pAccount = NULL;
		
		m_mapAccounts.erase(m_mapAccounts.begin());
	}	
}


// While waiting on server response to a withdrawal, we keep the private coin
// data here so we can unblind the response.
// This information is so important (as important as the digital cash token
// itself, until the unblinding is done) that we need to save the file right away.
void OTWallet::AddPendingWithdrawal(const OTPurse & thePurse)
{
	// TODO maintain a list here (I don't know why, the server response is nearly
	// instant and then it's done.)
	
	// TODO notice I don't check the pointer here to see if it's already set, I 
	// just start using it.. Fix that.
	m_pWithdrawalPurse = (OTPurse *)&thePurse;
}

void OTWallet::RemovePendingWithdrawal()
{
	if (m_pWithdrawalPurse)
		delete m_pWithdrawalPurse;
	
	m_pWithdrawalPurse = NULL;
}





bool OTWallet::SignContractWithFirstNymOnList(OTContract & theContract)
{
	if (g_pTemporaryNym)
	{
		theContract.SignContract(*g_pTemporaryNym);
		return true;
	}

	return false;
}



// Pass in the Server ID and get the pointer back.
OTServerContract * OTWallet::GetServerContract(const OTIdentifier & SERVER_ID)
{
	OTContract * pServer = NULL;

	for (mapOfServers::iterator ii = m_mapServers.begin(); ii != m_mapServers.end(); ++ii)
	{
		pServer = (*ii).second;
		
		OT_ASSERT_MSG((NULL != pServer), "NULL server pointer in OTWallet::m_mapServers, OTWallet::GetServerContract");
		
		OTIdentifier id_CurrentContract;
		pServer->GetIdentifier(id_CurrentContract);
		
		if (id_CurrentContract == SERVER_ID)
			return (OTServerContract *)pServer;
	}
	
	return NULL;
}


// The wallet presumably has multiple Nyms listed within.
// I should be able to pass in a Nym ID and, if the Nym is there,
// the wallet returns a pointer to that nym.
OTPseudonym * OTWallet::GetNymByID(const OTIdentifier & NYM_ID)
{
	OTPseudonym * pNym = NULL;
	
	for (mapOfNyms::iterator ii = m_mapNyms.begin(); ii != m_mapNyms.end(); ++ii)
	{		
		pNym = (*ii).second;
		
		OT_ASSERT_MSG((NULL != pNym), "NULL pseudonym pointer in OTWallet::GetNymByID.");

		OTIdentifier id_CurrentNym;
		pNym->GetIdentifier(id_CurrentNym);
		
		if (id_CurrentNym == NYM_ID)
			return pNym;
	}	
	
	return NULL;
}


// used by high-level wrapper.
int OTWallet::GetNymCount()
{
	return m_mapNyms.size();
}

int OTWallet::GetServerCount()
{
	return m_mapServers.size();
}

int OTWallet::GetAssetTypeCount()
{
	return m_mapContracts.size();
}

int OTWallet::GetAccountCount()
{
	return m_mapAccounts.size();
}


// used by high-level wrapper.
bool OTWallet::GetNym(const int iIndex, OTIdentifier & NYM_ID, OTString & NYM_NAME)
{
	// if iIndex is within proper bounds (0 through count minus 1)
	if (iIndex < GetNymCount() && iIndex >= 0)
	{
		OTPseudonym * pNym	= NULL;
		int iCurrentIndex	= (-1);
		
		for (mapOfNyms::iterator ii = m_mapNyms.begin(); ii != m_mapNyms.end(); ++ii)
		{	
			iCurrentIndex++; // On first iteration, this becomes 0 here. (For 0 index.) Increments thereafter.
			
			if ((iIndex == iCurrentIndex) && (pNym = (*ii).second)) // if not null
			{
				pNym->GetIdentifier(NYM_ID);
				NYM_NAME.Set(pNym->GetNymName());
				return true;
			}
		}	
	}
	
	return false;
}


// used by high-level wrapper.
bool OTWallet::GetServer(const int iIndex, OTIdentifier & THE_ID, OTString & THE_NAME)
{
	// if iIndex is within proper bounds (0 through count minus 1)
	if (iIndex < GetServerCount() && iIndex >= 0)
	{
		OTServerContract * pServer	= NULL;
		int iCurrentIndex	= (-1);
		
		for (mapOfServers::iterator ii = m_mapServers.begin(); ii != m_mapServers.end(); ++ii)
		{	
			iCurrentIndex++; // On first iteration, this becomes 0 here. (For 0 index.) Increments thereafter.
			
			if ((iIndex == iCurrentIndex) && (pServer = (*ii).second)) // if not null
			{
				pServer->GetIdentifier(THE_ID);
				pServer->GetName(THE_NAME);
				return true;
			}
		}	
	}
	
	return false;
}

// used by high-level wrapper.
bool OTWallet::GetAssetType(const int iIndex, OTIdentifier & THE_ID, OTString & THE_NAME)
{
	// if iIndex is within proper bounds (0 through count minus 1)
	if (iIndex < GetAssetTypeCount() && iIndex >= 0)
	{
		OTAssetContract	* pAssetType = NULL;
		int iCurrentIndex	= (-1);
		
		for (mapOfContracts::iterator ii = m_mapContracts.begin(); ii != m_mapContracts.end(); ++ii)
		{	
			iCurrentIndex++; // On first iteration, this becomes 0 here. (For 0 index.) Increments thereafter.
			
			if ((iIndex == iCurrentIndex) && (pAssetType = (*ii).second)) // if not null
			{
				pAssetType->GetIdentifier(THE_ID);
				pAssetType->GetName(THE_NAME);
				return true;
			}
		}	
	}
	
	return false;
}

// used by high-level wrapper.
bool OTWallet::GetAccount(const int iIndex, OTIdentifier & THE_ID, OTString & THE_NAME)
{
	// if iIndex is within proper bounds (0 through count minus 1)
	if (iIndex < GetAccountCount() && iIndex >= 0)
	{
		OTAccount * pAccount	= NULL;
		int iCurrentIndex	= (-1);
		
		for (mapOfAccounts::iterator ii = m_mapAccounts.begin(); ii != m_mapAccounts.end(); ++ii)
		{	
			iCurrentIndex++; // On first iteration, this becomes 0 here. (For 0 index.) Increments thereafter.
			
			if ((iIndex == iCurrentIndex) && (pAccount = (*ii).second)) // if not null
			{
				pAccount->GetIdentifier(THE_ID);
				pAccount->GetName(THE_NAME);
				return true;
			}
		}	
	}
	
	return false;
}


void OTWallet::DisplayStatistics(OTString & strOutput)
{
	strOutput.Concatenate("\n-------------------------------------------------\n");
	strOutput.Concatenate("WALLET STATISTICS:\n");
	
	OTPseudonym * pNym = NULL;
	
	strOutput.Concatenate("\nPSEUDONYM(s):\n\n");

	for (mapOfNyms::iterator ii = m_mapNyms.begin(); ii != m_mapNyms.end(); ++ii)
	{		
		pNym = (*ii).second;
		
		OT_ASSERT_MSG((NULL != pNym), "NULL pseudonym pointer in OTWallet::m_mapNyms, OTWallet::DisplayStatistics.");

		pNym->DisplayStatistics(strOutput);
	}
	
	// ---------------------------------------------------------------
	
	strOutput.Concatenate("\n-------------------------------------------------\n");
	strOutput.Concatenate("ASSET CONTRACTS:\n\n");

	OTContract * pContract = NULL;
	
	for (mapOfContracts::iterator ii = m_mapContracts.begin(); ii != m_mapContracts.end(); ++ii)
	{
		pContract = (*ii).second;
	 
		OT_ASSERT_MSG(NULL != pContract, "NULL contract pointer in OTWallet::m_mapContracts, OTWallet::DisplayStatistics");
	 
		pContract->SaveContractWallet(strOutput);
	}
	
	// ---------------------------------------------------------------
	
	strOutput.Concatenate("-------------------------------------------------\n");
	strOutput.Concatenate("SERVER CONTRACTS:\n\n");

	OTContract * pServer = NULL;
	
	for (mapOfServers::iterator ii = m_mapServers.begin(); ii != m_mapServers.end(); ++ii)
	{
		pServer = (*ii).second;
	 
		OT_ASSERT_MSG(NULL != pServer, "NULL server pointer in OTWallet::m_mapServers, OTWallet::DisplayStatistics");
	 
		pServer->SaveContractWallet(strOutput);
	}
	
	// ---------------------------------------------------------------


	strOutput.Concatenate("-------------------------------------------------\n");
	strOutput.Concatenate("ACCOUNTS:\n\n");
	
	OTAccount * pAccount = NULL;
	
	for (mapOfAccounts::iterator ii = m_mapAccounts.begin(); ii != m_mapAccounts.end(); ++ii)
	{
		pAccount = (*ii).second;
		
		OT_ASSERT_MSG(NULL != pAccount, "NULL account pointer in OTWallet::m_mapAccounts, OTWallet::DisplayStatistics");
		
		pAccount->DisplayStatistics(strOutput);
		
		strOutput.Concatenate("-------------------------------------------------\n\n");
	}
	
	// ---------------------------------------------------------------
	
	
}



// Pass in the name only, NOT the full path.
// If you pass NULL, it remembers full path from last time.
// (Better to do that.)
//
bool OTWallet::SaveWallet(const char * szFilename/*=NULL*/)
{	
	char * szFilenameToUse = NULL;
	
	if (NULL != szFilename)
		m_strFilename.Format("%s%s%s", OTLog::Path(), OTLog::PathSeparator(), szFilename);
	
	szFilenameToUse = (char *)m_strFilename.Get();
	
	OT_ASSERT_MSG(NULL != szFilenameToUse, "Null filename in OTWallet::SaveWallet\n");

	/*
#ifdef _WIN32
	FILE * fl = NULL;
	errno_t err = fopen_s(&fl, szFilenameToUse, "wb");
#else
	FILE * fl = fopen(szFilenameToUse, "w");
#endif

	if (NULL == fl)
	{
		OTLog::vOutput(0, "Failed opening file in OTWallet::SaveWallet: %s\n", szFilenameToUse);
		return false;
	}
	*/
	
	std::ofstream ofs(szFilenameToUse, std::ios::binary);
	
	if (ofs.fail())
	{
		OTLog::vOutput(0, "Failed opening file in OTWallet::SaveWallet: %s\n", szFilenameToUse);
		return false;
	}

	ofs.clear();
	
	// ---------------------------------------------------------------
	
	OTASCIIArmor ascName;
	
	if (m_strName.Exists()) // name is in the clear in memory, and base64 in storage.
	{
		ascName.SetString(m_strName, false); // linebreaks == false
	}
	
	
	ofs << "<?xml version=\"1.0\"?>\n<wallet name=\"" << ascName.Get() <<
	"\" version=\"" << m_strVersion.Get() <<
	"\">\n\n";
	
	//mapOfNyms			m_mapNyms;		// So far no file writing for these (and none needed...)
	//mapOfContracts	m_mapContracts; // This is what I'm testing now, which includes the other 3.
	//mapOfServers		m_mapServers;
	//mapOfAccounts		m_mapAccounts; 

	OTPseudonym * pNym = NULL;
	
	for (mapOfNyms::iterator ii = m_mapNyms.begin(); ii != m_mapNyms.end(); ++ii)
	{	
		pNym = (*ii).second;
		
		OT_ASSERT_MSG(NULL != pNym, "NULL pseudonym pointer in OTWallet::m_mapNyms, OTWallet::SaveWallet");
		
		pNym->SavePseudonymWallet(ofs);
	}

	// ---------------------------------------------------------------

	OTContract * pContract = NULL;
	
	for (mapOfContracts::iterator ii = m_mapContracts.begin(); ii != m_mapContracts.end(); ++ii)
	{
		pContract = (*ii).second;
		
		OT_ASSERT_MSG(NULL != pContract, "NULL contract pointer in OTWallet::m_mapContracts, OTWallet::SaveWallet");
		
		pContract->SaveContractWallet(ofs);

		//TODO remove this test code---------------
		// Used for putting new signatures on contracts
/*
		{
			// Right now it's configured to sign with USER public key, not server.
//			OTString strNewFile, strIdentifier("1"); // This is where I've got the server Nym
			OTString strNewFile;
			pContract->GetFilename(strNewFile);
			strNewFile.Concatenate("NEW");
		
//			OTPseudonym theSigningNym;
//			theSigningNym.SetIdentifier(strIdentifier);
			
//			if (theSigningNym.Loadx509CertAndPrivateKey()) // with ID 1 in the certs folder.
				if (g_pTemporaryNym)
					pContract->SignContract(*g_pTemporaryNym);						

			//TODO remove this test code.
			pContract->SaveContract(strNewFile.Get());
		}
*/
		// ----------------------------------------
	}
	
	// ---------------------------------------------------------------
	
	OTContract * pServer = NULL;
	
	for (mapOfServers::iterator ii = m_mapServers.begin(); ii != m_mapServers.end(); ++ii)
	{
		pServer = (*ii).second;
		
		OT_ASSERT_MSG(NULL != pServer, "NULL server pointer in OTWallet::m_mapServers, OTWallet::SaveWallet");
		
		pServer->SaveContractWallet(ofs);
		/*
		//TODO remove this test code---------------
		// Used for putting new signatures on contracts
	
		{
			OTString strNewFile, strIdentifier("1");
			pServer->GetFilename(strNewFile);
			strNewFile.Concatenate("NEW");
			
			OTPseudonym theSigningNym;
			theSigningNym.SetIdentifier(strIdentifier);
			
			if (theSigningNym.Loadx509CertAndPrivateKey()) // with ID 1 in the certs folder
				pServer->SignContract(theSigningNym);						
			
			//TODO remove this test code.
			pServer->SaveContract(strNewFile.Get());
		}
		*/
		// ----------------------------------------
	}
	
	// ---------------------------------------------------------------
	
	OTContract * pAccount = NULL;
	
	for (mapOfAccounts::iterator ii = m_mapAccounts.begin(); ii != m_mapAccounts.end(); ++ii)
	{
		pAccount = (*ii).second;
		
		OT_ASSERT_MSG(NULL != pAccount, "NULL account pointer in OTWallet::m_mapAccounts, OTWallet::SaveWallet");
		
		pAccount->SaveContractWallet(ofs);

		//TODO remove this test code
		/*
		OTString strNewFile;
		pAccount->GetFilename(strNewFile);
		strNewFile.Concatenate("NEW");
		
		// The others, I merely save them.
		// But the accounts, I must sign them first.
		// Only when the account is signed, is the signed portion
		// updated to match the new account balance and date.
		if (g_pTemporaryNym)
		{
			if (!pAccount->SignContract(*g_pTemporaryNym))
			{
				OTLog::Error("Error signing account in OTWallet::SaveWallet\n");
			}
		}
		
		pAccount->SaveContract(strNewFile.Get());
		*/
		// ----------------------------------------
	}
	
	// ---------------------------------------------------------------
	
	ofs << "</wallet>\n";

	ofs.close();
	
	return true;
}





// Wallet takes ownership and will delete.
// theNym is passed as reference only to prove that it's real.
//
// This function assumes the Nym has already been loaded, verified, etc.
// AND that it's been dynamically allocated.
//
void OTWallet::AddNym(const OTPseudonym & theNym)
{
	// TODO remove this temporary block, used for testing only.	
	if (NULL == g_pTemporaryNym)
		g_pTemporaryNym = (OTPseudonym *)&theNym; 

	
	const OTIdentifier	NYM_ID(theNym);

	OTPseudonym * pNym	= NULL;
	OTIdentifier aNymID;
	
	for (mapOfNyms::iterator ii = m_mapNyms.begin(); ii != m_mapNyms.end(); ++ii)
	{	
		pNym = (*ii).second;
		
		OT_ASSERT(NULL != pNym);
		
		pNym->GetIdentifier(aNymID);
		
		if (aNymID == NYM_ID)
		{
			OTString strName(pNym->GetNymName());
			((OTPseudonym &)theNym).SetNymName(strName);
			
			m_mapNyms.erase(ii);
			delete pNym;
			pNym = NULL;
			
//			OTLog::Error("Error: Adding Nym to wallet when there was already one there with same ID...\n");
			
			break;
		}
	}
		
	const OTString	strNymID(NYM_ID);
	m_mapNyms[strNymID.Get()] = (OTPseudonym *)&theNym; // Insert to wallet's list of Nyms.
}


void OTWallet::AddAccount(const OTAccount & theAcct)
{
	const OTIdentifier	ACCOUNT_ID(theAcct);
	
	// See if there is already an account object on this wallet with the same ID
	// (Otherwise if we don't delete it, this would be a memory leak.)
	// Should use a smart pointer.
	OTAccount * pAccount = NULL;
	OTIdentifier anAccountID;
	
	for (mapOfAccounts::iterator ii = m_mapAccounts.begin(); ii != m_mapAccounts.end(); ++ii)
	{
		pAccount = (*ii).second;
		
		OT_ASSERT(NULL != pAccount);
		
		pAccount->GetIdentifier(anAccountID);
		
		if (anAccountID == ACCOUNT_ID)
		{
			OTString strName;
			pAccount->GetName(strName);
			
			if (strName.Exists())
				((OTAccount &)theAcct).SetName(strName);
						
			m_mapAccounts.erase(ii);
			delete pAccount;
			pAccount = NULL;
			
			break;
		}
	}
	
	const OTString	strAcctID(ACCOUNT_ID);
	m_mapAccounts[strAcctID.Get()] = (OTAccount *)&theAcct;
}


// Look up an account by ID and see if it is in the wallet.
// If it is, return a pointer to it, otherwise return NULL.
OTAccount * OTWallet::GetAccount(const OTIdentifier & theAccountID)
{
	// loop through the items that make up this transaction and print them out here, base64-encoded, of course.
	OTAccount * pAccount = NULL;
	OTIdentifier anAccountID;
	
	for (mapOfAccounts::iterator ii = m_mapAccounts.begin(); ii != m_mapAccounts.end(); ++ii)
	{
		pAccount = (*ii).second;
		
		OT_ASSERT(NULL != pAccount);
		
		pAccount->GetIdentifier(anAccountID);
		
		if (anAccountID == theAccountID)
			return pAccount;
	}
	
	return NULL;
}


// The wallet "owns" theContract and will handle cleaning it up.
// So make SURE you allocate it on the heap.
void OTWallet::AddAssetContract(const OTAssetContract & theContract)
{
	OTIdentifier	CONTRACT_ID(theContract);
	OTString		STR_CONTRACT_ID(CONTRACT_ID);
	
	OTAssetContract * pContract = GetAssetContract(CONTRACT_ID);
	
	if (pContract)
	{
		OTLog::Error("Error: Attempt to add Asset Contract but it is already in the wallet.\n");
	}
	else {
		m_mapContracts[STR_CONTRACT_ID.Get()] = &((OTAssetContract &)theContract);
	}
}

OTAssetContract * OTWallet::GetAssetContract(const OTIdentifier & theContractID)
{
	// loop through the items that make up this transaction and print them out here, base64-encoded, of course.
	OTAssetContract * pContract = NULL;
	OTIdentifier aContractID;
	
	for (mapOfContracts::iterator ii = m_mapContracts.begin(); ii != m_mapContracts.end(); ++ii)
	{
		pContract = (*ii).second;
		
		OT_ASSERT(NULL != pContract);
		
		pContract->GetIdentifier(aContractID);
		
		if (aContractID == theContractID)
			return pContract;
	}
	
	return NULL;	
}





bool OTWallet::LoadWallet(const char * szFilename)
{
	OT_ASSERT_MSG(NULL != szFilename, "NULL filename in OTWallet::LoadWallet.\n");
			
	Release();
	
	// Save this for later... (the full path to this file.)
	m_strFilename.Format("%s%s%s", OTLog::Path(), OTLog::PathSeparator(), szFilename);
	
	// --------------------------------------------------------------------
	
	if (!OTLog::ConfirmExactPath(OTLog::Path()))
	{
		OTLog::vError("Unable to find data folder: %s\n", OTLog::Path());
		return false;
	}
	
	if (!OTLog::ConfirmFile(szFilename))
	{
		OTLog::vError("Unable to find wallet file: %s\n", szFilename);
		return false;
	}
	
	// --------------------------------------------------------------------
	
	OTStringXML xmlFileContents;
		
	std::ifstream in(m_strFilename.Get(), std::ios::binary);
	
	if (in.fail())
	{
		OTLog::vError("Error opening wallet file: %s\n", m_strFilename.Get());
		return false;		
	}
	
	std::stringstream buffer;
	buffer << in.rdbuf();
	
	std::string contents(buffer.str());
	
	xmlFileContents.Set(contents.c_str());
	
	if (xmlFileContents.GetLength() < 2)
	{
		OTLog::vError("Error reading wallet file: %s\n", m_strFilename.Get());
		return false;
	}
	
	// --------------------------------------------------------------------

	IrrXMLReader* xml = createIrrXMLReader(&xmlFileContents);

	// parse the file until end reached
	while(xml && xml->read())
	{
		// strings for storing the data that we want to read out of the file
		OTString NymName;
		OTString NymID;
		
		OTString AssetName;
		OTString AssetContract;
		OTString AssetID;
		
		OTString ServerName;
		OTString ServerContract;
		OTString ServerID;
		
		OTString AcctName;
		OTString AcctFile;
		OTString AcctID;
		
		switch(xml->getNodeType())
		{
			case EXN_NONE:
			case EXN_TEXT:
			case EXN_COMMENT:
			case EXN_ELEMENT_END:
			case EXN_CDATA:
				// in this xml file, the only text which occurs is the messageText
				//messageText = xml->getNodeData();
				break;
			case EXN_ELEMENT:
			{
				if (!strcmp("wallet", xml->getNodeName()))	// -------------------------------------------------------------
				{
					OTASCIIArmor ascWalletName = xml->getAttributeValue("name");
					
					if (ascWalletName.Exists())
						ascWalletName.GetString(m_strName, false); // linebreaks == false

//					m_strName			= xml->getAttributeValue("name");					
//					OTLog::OTPath		= xml->getAttributeValue("path");					
					m_strVersion		= xml->getAttributeValue("version");					
					
					OTLog::vOutput(0, "\nLoading wallet: %s, version: %s\n", m_strName.Get(), m_strVersion.Get());
				}
				else if (!strcmp("pseudonym", xml->getNodeName()))  // -------------------------------------------------------------
				{
					OTASCIIArmor ascNymName = xml->getAttributeValue("name");
					
					if (ascNymName.Exists())
						ascNymName.GetString(NymName, false); // linebreaks == false

//					NymName = xml->getAttributeValue("name");// user-assigned name for GUI usage				
					NymID = xml->getAttributeValue("nymID"); // message digest from hash of x.509 cert
					
					OTLog::vOutput(0, "\n\n** Pseudonym ** (wallet listing): %s\nID: %s\n",
							NymName.Get(), NymID.Get());

					OTPseudonym * pNym = new OTPseudonym(NymName, NymID, NymID);

					OT_ASSERT_MSG((NULL != pNym), "Unable to allocate memory for an OTPseudonym");

					if (pNym->Loadx509CertAndPrivateKey())
					{
						if (pNym->VerifyPseudonym()) 
						{
						//	if (false == pNym->LoadSignedNymfile(*pNym)) // Uncomment this line to generate a new Nym by hand.
 							if (pNym->LoadSignedNymfile(*pNym))  // (Uncomment) Comment OUT this line to generate a new nym by hand.
							{
	   // pNym->SaveSignedNymfile(*pNym); // Uncomment this if you want to generate a new nym by hand. NORMALLY LEAVE IT COMMENTED OUT!!!! IT'S DANGEROUS!!!
								
								this->AddNym(*pNym); // Nym loaded. Insert to wallet's list of Nyms.
							}
							else 
							{
								OTLog::Output(0, "Error loading Nym in OTWallet::LoadWallet\n");
							}
						}
						else 
						{
							OTLog::Output(0, "Error verifying public key against Nym ID in OTWallet::LoadWallet\n");
						}
					}
					else {
						OTLog::Output(0, "Error loading x509 file for Pseudonym in OTWallet::LoadWallet\n");
					}
				}
				else if (!strcmp("assetType", xml->getNodeName()))	// -------------------------------------------------------------
				{
					// From Server:
					AssetName		= xml->getAttributeValue("name");			
					AssetID			= xml->getAttributeValue("assetTypeID");	// hash of contract itself
					
					OTLog::vOutput(0, "\n\n****Asset Contract**** (server listing) Name: %s\nContract ID:\n%s\n",
								   AssetName.Get(), AssetID.Get());
					
					OTString strContractPath;
					strContractPath.Format("%s%s%s%s%s", OTLog::Path(), OTLog::PathSeparator(),
										   OTLog::ContractFolder(),
										   OTLog::PathSeparator(), AssetID.Get());
					OTAssetContract * pContract = new OTAssetContract(AssetName, strContractPath, AssetID);

					OT_ASSERT_MSG(NULL != pContract, "Error allocating memory for Asset Contract in OTWallet::LoadWallet\n");
			
					if (pContract->LoadContract()) 
					{
						if (pContract->VerifyContract())
						{
							OTLog::Output(0, "** Asset Contract Verified **\n-----------------------------------------------------------------------------\n\n");
							
							m_mapContracts[AssetID.Get()] = pContract;
						}
						else
						{
							delete pContract; pContract = NULL;
							OTLog::Output(0, "Contract FAILED to verify.\n");
						}							
					}
					else 
					{
						delete pContract; pContract = NULL;
						OTLog::Error("Error reading file for Asset Contract in OTWallet::LoadWallet\n");
					}

				}
				else if (!strcmp("notaryProvider", xml->getNodeName()))	// -------------------------------------------------------------
				{
					ServerName = xml->getAttributeValue("name");					
					ServerID = xml->getAttributeValue("serverID"); // hash of contract
					
					OTLog::vOutput(0, "\n\n\n****Notary Server (contract)**** (wallet listing): %s\n ServerID:\n%s\n",
							ServerName.Get(), ServerID.Get());
				
					OTString strContractPath;
					strContractPath.Format("%s%s%s%s%s", OTLog::Path(), OTLog::PathSeparator(),
										   OTLog::ContractFolder(),
										   OTLog::PathSeparator(), ServerID.Get());

					
					OTServerContract * pContract = new OTServerContract(ServerName, strContractPath, ServerID);
					
					OT_ASSERT_MSG(NULL != pContract, "Error allocating memory for Server Contract in OTWallet::LoadWallet\n");
					
					if (pContract->LoadContract()) 
					{
						if (pContract->VerifyContract())
						{
							OTLog::Output(0, "** Server Contract Verified **\n-----------------------------------------------------------------------------\n\n");
							// Uncomment : Move these lines back above the 'if' block to regenerate some newly-signed contracts.
							// (for testing only.) Otherwise leave here where it belongs.
							m_mapServers[ServerID.Get()] = pContract;							
						}
						else
						{
							delete pContract; pContract = NULL;
							OTLog::Output(0, "Server contract failed to verify.\n");
						}
					}
					else 
					{
						delete pContract; pContract = NULL;
						OTLog::Error("Error reading file for Transaction Server in OTWallet::LoadWallet\n");
					}
				}
				else if (!strcmp("assetAccount", xml->getNodeName()))	// -------------------------------------------------------------
				{
					OTASCIIArmor ascAcctName = xml->getAttributeValue("name");	
					
					if (ascAcctName.Exists())
						ascAcctName.GetString(AcctName, false); // linebreaks == false
					
					AcctID	 = xml->getAttributeValue("accountID");
					ServerID = xml->getAttributeValue("serverID");
										
					OTLog::vOutput(0, "\n--------------------------------------------------------------------------\n"
							"****Account**** (wallet listing) "
							"name: %s\n AccountID: %s\n ServerID: %s\n", 
							AcctName.Get(), AcctID.Get(), ServerID.Get());
					
					const OTIdentifier ACCOUNT_ID(AcctID), SERVER_ID(ServerID);
					
					OTAccount * pAccount =  OTAccount::LoadExistingAccount(ACCOUNT_ID, SERVER_ID);
					
					if (pAccount)
					{
						pAccount->SetName(AcctName);
						this->AddAccount(*pAccount);
					}
					else 
					{
						OTLog::Error("Error loading existing Asset Account in OTWallet::LoadWallet\n");
					}
				}
				else
				{
					// unknown element type
					OTLog::vError("unknown element type: %s\n", xml->getNodeName());
				}
			}
				break;
			default:
				OTLog::vOutput(5, "Unknown XML type in OTWallet::LoadWallet: %s\n", xml->getNodeName());
				break;
		}
	}
	
	
	
	
	
	
	// TODO remove this test code
	//bool GetAsciiArmoredData(OTASCIIArmor & theArmoredText) const;
	//bool SetAsciiArmoredData(const OTASCIIArmor & theArmoredText)
	
	/*
	OTString strPlaintext("Testing testing testing testing blah blah blah");
	OTLog::vError("\n\nTesting new RSA ENVELOPES (public key crypto).\n\nPlaintext: %s\n", strPlaintext.Get());
	
	OTEnvelope theEVP;
	theEVP.Seal(*g_pTemporaryNym, strPlaintext);
	
	
	OTASCIIArmor ascCiphertext;
	theEVP.GetAsciiArmoredData(ascCiphertext); // Now the contents of encrypted envelope are ascii-encoded
	
	OTLog::vError("\nASCII-ARMORED Ciphertext:\n%s\n", ascCiphertext.Get());

	
	// Now decrypt it
	OTEnvelope evpReceived;
	evpReceived.SetAsciiArmoredData(ascCiphertext);
	
	OTString strDecrypted;
	evpReceived.Open(*g_pTemporaryNym, strDecrypted);
	
	OTLog::vError("Decrypted text: %s\n\n\n", strDecrypted.Get());
	*/
		

	// delete the xml parser after usage
	if (xml)
		delete xml;
	
	return true;
}












































