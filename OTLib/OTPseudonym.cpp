/************************************************************************************
 *    
 *  OTPseudonym.cpp
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


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>


extern "C"
{
#include <openssl/sha.h>

#include <openssl/pem.h>
#include <openssl/conf.h>
#include <openssl/x509v3.h>
#ifndef OPENSSL_NO_ENGINE
#include <openssl/engine.h>
#endif
	
int mkcert(X509 **x509p, EVP_PKEY **pkeyp, int bits, int serial, int days);
int add_ext(X509 *cert, int nid, char *value);
	
}




#include "irrxml/irrXML.h"

using namespace irr;
using namespace io;

#include "OTString.h"
#include "OTStringXML.h"
#include "OTIdentifier.h"
#include "OTAsymmetricKey.h"

#include "OTASCIIArmor.h"
#include "OTPseudonym.h"
#include "OTSignedFile.h"

#include "OTLog.h"



// use this to actually generate a new key pair and assorted nym files.
//
bool OTPseudonym::GenerateNym()
{
	bool bSuccess = false;
	
//	BIO			*	bio_err	=	NULL;
	X509		*	x509	=	NULL;
	EVP_PKEY	*	pNewKey	=	NULL;
	
//	CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ON); // memory leak detection. Leaving this for now.
	
//	bio_err	=	BIO_new_fp(stderr, BIO_NOCLOSE);
	
	
	mkcert(&x509, &pNewKey, 1024, 0, 3650); // actually generate the things. // TODO THESE PARAMETERS...
	// Note: 512 bit key CRASHES
	// 1024 is apparently a minimum requirement, if not an only requirement.
	// Will need to go over just what sorts of keys are involved here... todo.
	
	
	if (NULL == pNewKey)
	{
		OTLog::Error("Failed attempting to generate new private key.\n");
		
		if (NULL != x509)
			X509_free(x509);

		return false;
	}
	
	if (NULL ==  x509)
	{
		OTLog::Error("Failed attempting to generate new x509 cert.\n");

		if (NULL != pNewKey)
			EVP_PKEY_free(pNewKey);

		return false;
	}
	
	
	// --------COMMENT THIS OUT FOR PRODUCTION --------
	//                  (Debug only.)
	RSA_print_fp(stdout, pNewKey->pkey.rsa, 0); // human readable
	X509_print_fp(stdout, x509); // human readable
	
	// write the private key, then the x509, to stdout.
	PEM_write_PrivateKey(stdout, pNewKey, NULL, NULL, 0, NULL, NULL);
	PEM_write_X509(stdout, x509);
	// ------------------------------------------------
	
	
	
	BIO	*	bio_out_pri  = BIO_new(BIO_s_mem());
	BIO	*	bio_out_x509 = BIO_new(BIO_s_mem());

	PEM_write_bio_PrivateKey(bio_out_pri, pNewKey,  NULL, NULL, 0, NULL, NULL);
	PEM_write_bio_X509(bio_out_x509, x509);

	
	unsigned char buffer_pri[4096] = ""; // todo hardcoded
	unsigned char buffer_x509[8192] = ""; // todo hardcoded
	
	OTString strx509;
	OTString strPrivateKey;

	int len = 0;
	
	 // todo hardcoded 4080 (see array above.)
	if (0 < (len = BIO_read(bio_out_x509, buffer_x509, 8100))) // returns number of bytes successfully read.
	{
		buffer_x509[len] = '\0';
		
		strx509.Set((const char*)buffer_x509);

		EVP_PKEY * pPublicKey = X509_get_pubkey(x509); 
		
		if (NULL != pPublicKey)
			m_pkeyPublic->SetKey(pPublicKey);
		// else?
				
		// todo hardcoded 4080 (see array above.)
		if (0 < (len = BIO_read(bio_out_pri, buffer_pri, 4080))) // returns number of bytes successfully read.
		{
			buffer_pri[len] = '\0';
			
			strPrivateKey.Set((const char *)buffer_pri); // so I can write this string to file in a sec...

			m_pkeyPrivate->SetKey(pNewKey); // private key itself... might as well keep it loaded for now.
			
			bSuccess = true;
		}
	}
	
	
	
	// cleanup
	X509_free(x509);
	x509 = NULL;
	
	if (false == bSuccess) // if we failed, then free the key.
	{
		EVP_PKEY_free(pNewKey);
	}
	// if bsuccess is true, we do NOT free the key, since we just  
	// called SetKey() and thus gave ownership of it to m_keyPrivate.

	pNewKey = NULL;
	
	
	//#ifndef OPENSSL_NO_ENGINE
	//	ENGINE_cleanup();
	//#endif
	//	CRYPTO_cleanup_all_ex_data();
	//	
	//	CRYPTO_mem_leaks(bio_err);
	
	
	//	BIO_free(bio_err);
	
	
	BIO_free(bio_out_pri);
	BIO_free(bio_out_x509);

	
	
	
	// At this point, the Nym's private key is set, and its public key is also set.
	// So the object in memory is good to go.
	// Now we just need to create some files, especially where the keys are stored,
	// since the Nym normally never writes to those files (just reads.)
	//
	if (bSuccess)
	{
		m_strCertfile.Format((char *)"%s%s%s%s%s", OTLog::Path(), OTLog::PathSeparator(),
							 OTLog::CertFolder(),
							 OTLog::PathSeparator(), "temp.nym");
		
		// --------
		// Here's where the serialization code would be changed to CouchDB or whatever.
		// In a key/value database, szFilename is the "key" and strFinal.Get() is the "value".
		std::ofstream ofs(m_strCertfile.Get(), std::ios::binary);
		
		if (ofs.fail())
		{
			OTLog::vError("Error opening file in OTPseudonym::GenerateNym: %s\n", 
						  m_strCertfile.Get());
			return false;
		}
		
		ofs.clear();
		
		OTString strFinal;
		
		strFinal.Format((char*)"%s%s", 
						strPrivateKey.Get(), strx509.Get());
		
		ofs << strFinal.Get();
		ofs.close();
		// --------

		bool bPublic  = false;
		bool bPrivate = false;
		
		bPublic  = m_pkeyPublic->LoadPublicKeyFromCertFile(m_strCertfile);
		bPrivate = m_pkeyPrivate->LoadPrivateKey(m_strCertfile);
		
		if (!bPublic)
		{
			OTLog::vError("Although the ascii-armored file (%s) was read, LoadPublicKeyFromCert "
						  "returned false.\n", m_strCertfile.Get());
			return false;
		}
		else
		{
			OTLog::vOutput(2, "Successfully loaded public key from Certfile: %s\n", m_strCertfile.Get());
		}
		
		
		if (!bPrivate)
		{
			OTLog::vError("Although the ascii-armored file (%s) was read, LoadPrivateKey returned false.\n",
						  m_strCertfile.Get());
			return false;
		}
		else
		{
			OTLog::vOutput(2, "Successfully loaded private key from: %s\n", m_strCertfile.Get());
		}

		

		OTString strPublicKey;
		bool bGotPublicKey = GetPublicKey().GetPublicKey(strPublicKey);
		
		if (!bGotPublicKey)
		{
			OTLog::Error("Error getting public key in OTPseudonym::VerifyPseudonym.\n");
			return false;	
		}
		
		
		OTIdentifier newID;
		bool bSuccessCalculateDigest = newID.CalculateDigest(strPublicKey);
		
		if (!bSuccessCalculateDigest)
		{
			OTLog::Error("Error calculating Certificate digest.\n");
			return false;	
		}
		
		m_nymID = newID;
		
		
		OTString strID(m_nymID);
		
		m_strCertfile.Format((char *)"%s%s%s%s%s", OTLog::Path(), OTLog::PathSeparator(),
							 OTLog::CertFolder(),
							 OTLog::PathSeparator(), strID.Get());
		
		
		// --------
		// Here's where the serialization code would be changed to CouchDB or whatever.
		// In a key/value database, szFilename is the "key" and strFinal.Get() is the "value".
		std::ofstream ofs2(m_strCertfile.Get(), std::ios::binary);
		
		if (ofs2.fail())
		{
			OTLog::vError("Error opening file in OTPseudonym::GenerateNym: %s\n", 
						  m_strCertfile.Get());
			return false;
		}
		
		ofs2.clear();
		ofs2 << strFinal.Get();
		ofs2.close();
		// --------
		
		bSuccess = SaveSignedNymfile(*this); // Now we'll generate the NymFile as well!
	}
	
	return bSuccess;
}





/*
typedef std::deque<long>							dequeOfTransNums;
typedef std::map<std::string, dequeOfTransNums *>	mapOfTransNums;	
*/


// Verify whether a certain transaction number appears on a certain list.
//
bool OTPseudonym::VerifyGenericNum(mapOfTransNums & THE_MAP, const OTString & strServerID, const long & lTransNum)
{
	std::string strID	= strServerID.Get();
	
	// The Pseudonym has a deque of transaction numbers for each servers.
	// These deques are mapped by Server ID.
	// 
	// So let's loop through all the deques I have, and if the server ID on the map
	// matches the Server ID that was passed in, then find the transaction number on
	// that list, and then return true. Else return false.
	for (mapOfTransNums::iterator ii = THE_MAP.begin();  ii != THE_MAP.end(); ++ii)
	{
		// if the ServerID passed in matches the serverID for the current deque
		if ( strID == ii->first )
		{
			dequeOfTransNums * pDeque = (ii->second);
			
			OT_ASSERT(NULL != pDeque);
			
			if (!(pDeque->empty())) // there are some numbers for that server ID
			{
				// Let's loop through them and see if the culprit is there
				for (unsigned i = 0; i < pDeque->size(); i++)
				{
					// Found it!
					if (lTransNum == pDeque->at(i))
					{
						return true;
					}
				}
			}
			break;			
		}
	}
	
	return false;	
}

// On the server side: A user has submitted a specific transaction number. 
// Remove it from his file so he can't use it again.
bool OTPseudonym::RemoveGenericNum(mapOfTransNums & THE_MAP, OTPseudonym & SIGNER_NYM, const OTString & strServerID, const long & lTransNum)
{
	bool bRetVal = RemoveGenericNum(THE_MAP, strServerID, lTransNum);
	
	if (bRetVal)
	{
		SaveSignedNymfile(SIGNER_NYM);
	}
	
	return bRetVal;
}

// This function is a little lower level, and doesn't worry about saving. Used internally.
bool OTPseudonym::RemoveGenericNum(mapOfTransNums & THE_MAP, const OTString & strServerID, const long & lTransNum)
{
	bool bRetVal = false;
	std::string strID	= strServerID.Get();
	
	// The Pseudonym has a deque of transaction numbers for each servers.
	// These deques are mapped by Server ID.
	// 
	// So let's loop through all the deques I have, and if the server ID on the map
	// matches the Server ID that was passed in, then find the transaction number on
	// that list, and then remove it, and return true. Else return false.
	for (mapOfTransNums::iterator ii = THE_MAP.begin();  ii != THE_MAP.end(); ++ii)
	{
		// if the ServerID passed in matches the serverID for the current deque
		if ( strID == ii->first )
		{
			dequeOfTransNums * pDeque = (ii->second);
			
			OT_ASSERT(NULL != pDeque);
			
			if (!(pDeque->empty())) // there are some numbers for that server ID
			{
				// Let's loop through them and see if the culprit is there
				for (unsigned i = 0; i < pDeque->size(); i++)
				{
					// Found it!
					if (lTransNum == pDeque->at(i))
					{
						pDeque->erase(pDeque->begin() + i);
						bRetVal = true;
						break;
					}
				}
			}
			break;			
		}
	}
		
	return bRetVal;
}


// No signer needed for this one, and save is false.
// This version is ONLY for cases where we're not saving inside this function.
bool OTPseudonym::AddGenericNum(mapOfTransNums & THE_MAP, const OTString & strServerID, long lTransNum) 
{
	bool bSuccessFindingServerID = false, bSuccess = false;
	std::string strID	= strServerID.Get();
	
	// The Pseudonym has a deque of transaction numbers for each server.
	// These deques are mapped by Server ID.
	// 
	// So let's loop through all the deques I have, and if the server ID on the map
	// matches the Server ID that was passed in, then add the transaction number.
	for (mapOfTransNums::iterator ii = THE_MAP.begin();  ii != THE_MAP.end(); ++ii)
	{
		// if the ServerID passed in matches the serverID for the current deque
		if ( strID == ii->first )
		{
			dequeOfTransNums * pDeque = (ii->second);
			
			OT_ASSERT(NULL != pDeque);
			
			pDeque->push_front(lTransNum);
			bSuccess = true;
			
			bSuccessFindingServerID = true;
			break;			
		}
	}
	
	// Apparently there is not yet a deque stored for this specific serverID.
	// Fine. Let's create it then, and then add the transaction num to that new deque.
	if (!bSuccessFindingServerID)
	{
		dequeOfTransNums * pDeque = new dequeOfTransNums;
		
		OT_ASSERT(NULL != pDeque);
		
		THE_MAP[strID] = pDeque;
		pDeque->push_front(lTransNum);
		bSuccess = true;
	}
	
	return bSuccess;	
}


// Returns count of transaction numbers available for a given server.
//
int OTPseudonym::GetGenericNumCount(mapOfTransNums & THE_MAP, const OTIdentifier & theServerID) 
{
	int nReturnValue = 0;
	
	const OTString strServerID(theServerID);
	std::string strID	= strServerID.Get();
	
	dequeOfTransNums * pDeque = NULL;
	
	// The Pseudonym has a deque of transaction numbers for each server.
	// These deques are mapped by Server ID.
	// 
	// So let's loop through all the deques I have, and if the server ID on the map
	// matches the Server ID that was passed in, then we found the right server.
	for (mapOfTransNums::iterator ii = THE_MAP.begin();  ii != THE_MAP.end(); ++ii)
	{
		// if the ServerID passed in matches the serverID for the current deque
		if ( strID == ii->first )
		{
			pDeque = (ii->second);
			
			OT_ASSERT(NULL != pDeque);

			break;			
		}
	}
	
	// We found the right server, so let's count the transaction numbers
	// that this nym has already stored for it.
	if (NULL != pDeque)
	{		
		nReturnValue = pDeque->size();
	}
	
	return nReturnValue;	
}




// *************************************************************************************



// On the server side: A user has submitted a specific transaction number. 
// Verify whether he actually has a right to use it.
bool OTPseudonym::VerifyTransactionNum(const OTString & strServerID, const long & lTransNum)
{
	return VerifyGenericNum(m_mapTransNum, strServerID, lTransNum);
}

// On the server side: A user has submitted a specific transaction number. 
// Remove it from his file so he can't use it again.
bool OTPseudonym::RemoveTransactionNum(OTPseudonym & SIGNER_NYM, const OTString & strServerID, const long & lTransNum)
{
	return RemoveGenericNum(m_mapTransNum, SIGNER_NYM, strServerID, lTransNum);
}


// Returns count of transaction numbers available for a given server.
//
int OTPseudonym::GetTransactionNumCount(const OTIdentifier & theServerID) 
{
	return GetGenericNumCount(m_mapTransNum, theServerID);
}


// No signer needed for this one, and save is false.
// This version is ONLY for cases where we're not saving inside this function.
bool OTPseudonym::AddTransactionNum(const OTString & strServerID, long lTransNum) 
{
	return AddGenericNum(m_mapTransNum, strServerID, lTransNum);
}


// ----------------------------------------------------------------------


// On the server side: A user has submitted a specific transaction number. 
// Verify whether it was issued to him and still awaiting final closing.
bool OTPseudonym::VerifyIssuedNum(const OTString & strServerID, const long & lTransNum)
{
	return VerifyGenericNum(m_mapIssuedNum, strServerID, lTransNum);
}

// On the server side: A user has accepted a specific receipt. 
// Remove it from his file so he's not liable for it anymore.
bool OTPseudonym::RemoveIssuedNum(OTPseudonym & SIGNER_NYM, const OTString & strServerID, const long & lTransNum)
{
	return RemoveGenericNum(m_mapIssuedNum, SIGNER_NYM, strServerID, lTransNum);
}


// Returns count of transaction numbers not yet cleared for a given server.
//
int OTPseudonym::GetIssuedNumCount(const OTIdentifier & theServerID) 
{
	return GetGenericNumCount(m_mapIssuedNum, theServerID);
}


// No signer needed for this one, and save is false.
// This version is ONLY for cases where we're not saving inside this function.
bool OTPseudonym::AddIssuedNum(const OTString & strServerID, long lTransNum) 
{
	return AddGenericNum(m_mapIssuedNum, strServerID, lTransNum);
}



// ----------------------------------------------------------------------





// Client side: We have received a new trans num from server. Store it.
// Now the server uses this too, for storing these numbers so it can verify them later.
//
bool OTPseudonym::AddTransactionNum(OTPseudonym & SIGNER_NYM, const OTString & strServerID, long lTransNum, bool bSave) 
{
	bool bSuccess1 = AddTransactionNum(strServerID, lTransNum);	// Add to list of available-to-use, outstanding numbers.
	bool bSuccess2 = AddIssuedNum(strServerID, lTransNum);		// Add to list of numbers that haven't been closed yet.
	
	// -----------------------------------

	if (bSuccess1 && bSuccess2 && bSave)
	{
		SaveSignedNymfile(SIGNER_NYM);
	}
	
	// -----------------------------------
	
	if (bSuccess1 && !bSuccess2)
	{
		RemoveGenericNum(m_mapTransNum, strServerID, lTransNum);
	}
	else if (bSuccess2 && !bSuccess1)
	{
		RemoveGenericNum(m_mapIssuedNum, strServerID, lTransNum);
	}
	
	
	return (bSuccess1 && bSuccess2);
}




// OtherNym is used as container for server to send us new transaction numbers
void OTPseudonym::HarvestTransactionNumbers(OTPseudonym & SIGNER_NYM, OTPseudonym & theOtherNym, bool bSave/*=true*/)
{
	bool bSuccess = false;
	std::string	strServerID;
	long lTransactionNumber = 0;
	
	for (mapOfTransNums::iterator	iii	 =	theOtherNym.GetMapTransNum().begin(); 
		 iii !=	theOtherNym.GetMapTransNum().end(); ++iii)
	{	
		strServerID					= (*iii).first;
		dequeOfTransNums * pDeque	= (iii->second);
		
		OTString OTstrServerID = strServerID.c_str();
		
		OT_ASSERT(NULL != pDeque);
		
		if (!(pDeque->empty()))
		{
			for (unsigned i = 0; i < pDeque->size(); i++)
			{
				lTransactionNumber = pDeque->at(i);
				
				AddTransactionNum(SIGNER_NYM, OTstrServerID, lTransactionNumber, false); // bSave = false (but saved below...)
				
				bSuccess = true;
			}
		}
	} // for
	
	if (bSuccess && bSave)
	{
		SaveSignedNymfile(SIGNER_NYM);
	}
}




// OtherNym is used as container for us to send server list of issued transaction numbers.
void OTPseudonym::HarvestIssuedNumbers(OTPseudonym & SIGNER_NYM, OTPseudonym & theOtherNym, bool bSave/*=false*/)
{
	bool bSuccess = false;
	std::string	strServerID;
	long lTransactionNumber = 0;
	
	for (mapOfTransNums::iterator	iii	 =	theOtherNym.GetMapIssuedNum().begin(); 
		 iii !=	theOtherNym.GetMapIssuedNum().end(); ++iii)
	{	
		strServerID					= (*iii).first;
		dequeOfTransNums * pDeque	= (iii->second);
		
		OTString OTstrServerID = strServerID.c_str();
		
		OT_ASSERT(NULL != pDeque);
		
		if (!(pDeque->empty()))
		{
			for (unsigned i = 0; i < pDeque->size(); i++)
			{
				lTransactionNumber = pDeque->at(i);
				
				AddTransactionNum(SIGNER_NYM, OTstrServerID, lTransactionNumber, false); // bSave = false (but saved below...)
				
				bSuccess = true;
			}
		}
	} // for
	
	if (bSuccess && bSave)
	{
		SaveSignedNymfile(SIGNER_NYM);
	}
}




// Client side.
// Get the next available transaction number for the serverID
// The lTransNum parameter is for the return value.
bool OTPseudonym::GetNextTransactionNum(OTPseudonym & SIGNER_NYM, const OTString & strServerID, long &lTransNum)
{
	bool bRetVal		= false;
	std::string strID	= strServerID.Get();
	
	// The Pseudonym has a deque of transaction numbers for each servers.
	// These deques are mapped by Server ID.
	// 
	// So let's loop through all the deques I have, and if the server ID on the map
	// matches the Server ID that was passed in, then send out the transaction  number.
	for (mapOfTransNums::iterator ii = m_mapTransNum.begin();  ii != m_mapTransNum.end(); ++ii)
	{
		// if the ServerID passed in matches the serverID for the current deque
		if ( strID == ii->first )
		{
			dequeOfTransNums * pDeque = (ii->second);
			
			OT_ASSERT(NULL != pDeque);
			
			if (!(pDeque->empty()))
			{
				lTransNum = pDeque->front();
				
				pDeque->pop_front();
				
				// The call has succeeded
				bRetVal = true;
			}
			break;			
		}
	}
	
	if (bRetVal)
	{
		SaveSignedNymfile(SIGNER_NYM);
	}
	
	return bRetVal;
}




void OTPseudonym::ReleaseTransactionNumbers()
{
	while (!m_mapTransNum.empty())
	{		
		dequeOfTransNums * pDeque = m_mapTransNum.begin()->second;
		
		OT_ASSERT(NULL != pDeque);
		
		m_mapTransNum.erase(m_mapTransNum.begin());
		delete pDeque;
		pDeque = NULL;
	}	

	while (!m_mapIssuedNum.empty())
	{		
		dequeOfTransNums * pDeque = m_mapIssuedNum.begin()->second;
		
		OT_ASSERT(NULL != pDeque);
		
		m_mapIssuedNum.erase(m_mapIssuedNum.begin());
		delete pDeque;
		pDeque = NULL;
	}	
}







// returns true on success, value goes into lReqNum
// Make sure the Nym is LOADED before you call this,
// otherwise it won't be there to get.
// and if the request number needs to be incremented,
// then make sure you call IncrementRequestNum (below)
bool OTPseudonym::GetCurrentRequestNum(const OTString & strServerID, long &lReqNum)
{		
	bool bRetVal		= false;
	std::string strID	= strServerID.Get();
	
	// The Pseudonym has a map of the request numbers for different servers.
	// For Server Bob, with this Pseudonym, I might be on number 34.
	// For but Server Alice, I might be on number 59.
	// 
	// So let's loop through all the numbers I have, and if the server ID on the map
	// matches the Server ID that was passed in, then send out the request number.
	for (mapOfRequestNums::iterator ii = m_mapRequestNum.begin();  ii != m_mapRequestNum.end(); ++ii)
	{
		if ( strID == ii->first )
		{
			// Setup return value.
			lReqNum = (ii->second);
			
			// The call has succeeded
			bRetVal = true;
			
			break;
		}
	}
	
	return bRetVal;
}
	


// Make SURE you call SavePseudonym after you call this.
// Otherwise it will increment in memory but not in the file.
// In fact, I cannot allow that. I will call SavePseudonym myself.
// Therefore, make SURE you fully LOAD this Pseudonym before you save it.
// You don't want to overwrite what's in that file.
// THEREFORE we need a better database than the filesystem.
// I will research a good, free, secure database (or encrypt everything
// before storing it there) and soon these "load/save" commands will use that
// instead of the filesystem.
void OTPseudonym::IncrementRequestNum(OTPseudonym & SIGNER_NYM, const OTString & strServerID)
{
	bool bSuccess = false;

	// The Pseudonym has a map of the request numbers for different servers.
	// For Server Bob, with this Pseudonym, I might be on number 34.
	// For but Server Alice, I might be on number 59.
	// 
	// So let's loop through all the numbers I have, and if the server ID on the map
	// matches the Server ID that was passed in, then send out the request number and
	// increment it so it will be ready for the next request.
	//
	// Make sure to save the Pseudonym so the new request number is saved.
	std::string strID	= strServerID.Get();
	for (mapOfRequestNums::iterator ii = m_mapRequestNum.begin();  ii != m_mapRequestNum.end(); ++ii)
	{
		if ( strID == ii->first )
		{
			// We found it!
			// Presumably we ONLY found it because this Nym has been properly loaded first.
			// Good job! Otherwise, the list would have been empty even though the request number
			// was sitting in the file.
			
			
			// Grab a copy of the old request number
			long lOldRequestNumber = m_mapRequestNum[ii->first];
			
			// Set the new request number to the old one plus one.
			m_mapRequestNum[ii->first] = lOldRequestNumber + 1;
			
			// Now we can log BOTH, before and after... // debug here
			OTLog::vOutput(4, "Incremented Request Number from %ld to %ld. Saving...\n", 
					lOldRequestNumber, m_mapRequestNum[ii->first]);
			//			OTLog::Output(2, "DEBUG REQUESTNUM: first: %s   Second: %ld\n", ii->first.c_str(), ii->second);
			//			OTLog::Output(2, "SAVING PSEUDONYM TO FILE: %s\n", m_strNymfile.Get());

			// The call has succeeded
			bSuccess = true;
			break;
		}
	}
	
	// If I didn't find it in the list above (whether the list is empty or not....)
	// that means it does not exist. So create it.
	
	if (!bSuccess)
	{
		OTLog::Output(0, "Creating Request Number entry as '1'. Saving...\n");
		m_mapRequestNum[strServerID.Get()] = 1;
		bSuccess = true;
	}
	
	
	if (bSuccess)
	{
		SaveSignedNymfile(SIGNER_NYM);
	}
}






// if the server sends us a @getRequest
void OTPseudonym::OnUpdateRequestNum(OTPseudonym & SIGNER_NYM, const OTString & strServerID, long lNewRequestNumber)
{
	bool bSuccess = false;
	
	// The Pseudonym has a map of the request numbers for different servers.
	// For Server Bob, with this Pseudonym, I might be on number 34.
	// For but Server Alice, I might be on number 59.
	// 
	// So let's loop through all the numbers I have, and if the server ID on the map
	// matches the Server ID that was passed in, then send out the request number and
	// increment it so it will be ready for the next request.
	//
	// Make sure to save the Pseudonym so the new request number is saved.
	std::string strID	= strServerID.Get();
	for (mapOfRequestNums::iterator ii = m_mapRequestNum.begin();  ii != m_mapRequestNum.end(); ++ii)
	{
		if ( strID == ii->first )
		{
			// We found it!
			// Presumably we ONLY found it because this Nym has been properly loaded first.
			// Good job! Otherwise, the list would have been empty even though the request number
			// was sitting in the file.
			
			// The call has succeeded
			bSuccess = true;
			
			// Grab a copy of the old request number
			long lOldRequestNumber = m_mapRequestNum[ii->first];
			
			// Set the new request number to the old one plus one.
			m_mapRequestNum[ii->first] = lNewRequestNumber;
			
			// Now we can log BOTH, before and after...
			OTLog::vOutput(4, "Updated Request Number from %ld to %ld. Saving...\n", 
					lOldRequestNumber, m_mapRequestNum[ii->first]);
			//			OTLog::Output(2, "DEBUG REQUESTNUM: first: %s   Second: %ld\n", ii->first.c_str(), ii->second);
			//			OTLog::Output(2, "SAVING PSEUDONYM TO FILE: %s\n", m_strNymfile.Get());
			break;
		}
	}
	
	// If I didn't find it in the list above (whether the list is empty or not....)
	// that means it does not exist. So create it.
	
	if (!bSuccess)
	{
		OTLog::vOutput(0, "Creating Request Number entry as '%ld'. Saving...\n", lNewRequestNumber);
		m_mapRequestNum[strServerID.Get()] = lNewRequestNumber;
		bSuccess = true;
	}
	
	
	if (bSuccess)
	{
		SaveSignedNymfile(SIGNER_NYM);
	}
	
}



/*
bool OTPseudonym::VerifyPseudonym()
{
	OTData binCert; // Here's where we'll put the decoded binary content.
	
	// m_ascCert should already contain the ascii-armored text from the 
	// Nym's x509 certificate file. (this happened in LoadPseudonym())
	
	// This function decodes the base64 text into binary OTData...
	bool bSuccessfulDecode = m_ascCert.GetData(binCert); 
	
	if (!bSuccessfulDecode)
	{
		OTLog::Error("Error decoding Certificate!\n");
		return false;
	}
	
	// Next we get a Message Digest of that binary Cert...
	OTIdentifier newID;
	
	bool bSuccessCalculateDigest = newID.CalculateDigest(binCert);
	
	if (!bSuccessCalculateDigest)
	{
		OTLog::Error("Error calculating Certificate digest.\n");
		return false;	
	}
	
	// newID now contains the Hash aka Message Digest aka Fingerprint aka "IDENTIFIER" 
	// of the x.509 certificate (in its binary form). 
	// (Maybe later we'll choose to hash the text form instead.)
	// 
	// Now let's compare that identifier to the one already loaded by the wallet
	// and make sure they MATCH.
	
	if (!(m_nymID == newID))
	{
		OTString str1, str2;
		m_nymID.GetString(str1);
		newID.GetString(str2);
		OTLog::Output(0, "Hashes do NOT match in OTPseudonym::VerifyPseudonym!\n%s\n%s\n",
				str1.Get(), str2.Get());
		return false;
	}
	else {
		OTLog::Output(1, "\nNymID from wallet *SUCCESSFUL* match to "
				"sha256 hash of the Cert.\n"
				"---------------------------------------------------------------\n");
		return true;
	}
}
*/
/*
bool OTPseudonym::GetPublicKey(OTData & thePublicKey)
{
	
}
*/

/*
 // Save this code. It may be possible to send the entire file
 // to the library and just have it processed there. This code
 // reads the file and then we can pass it to such a library.
bool OTPseudonym::LoadPseudonym()
{	
	OTString & filename = m_strFilename;
	
	std::ifstream in(filename.Get(), std::ios::binary);
	
	if (in.fail())
	{
		OTLog::vError("Error opening file in OTPseudonym::LoadPseudonym: %s\n",
			m_strFilename.Get());
		return false;
	}
 
	std::stringstream buffer;
	buffer << in.rdbuf();
	
	std::string contents(buffer.str());

	m_strCertFileContents = contents.c_str();
	
	OTLog::Output(1, "Loaded x.509 Certificate:\n%s\n", m_strCertFileContents.Get());
	
	return true;
}
*/



/*
 <pseudonym name="REDACTED" 
 nymID="0094e344f6f437c55458873218b14651c4f0ecc88fc7b714fa3b98a83fdf8767"
 file="client.pem" />  <!-- ascii-armored x509 certificate -->
 
 <assetType name="Chuck-E-Cheese Tokens" 
 assetTypeID="65e6ecf1a72300dcb41a908246be1b53465e7edc9b14d90656ba845d71ef94b5" 
 contract="test.xml" />
 
 <transactionServer 
 name="transactions.com" 
 serverID="0535d64305fd10ee104bb79a994c5c58e833a1af664a939a49b1fa4a0445d590" 
 contract="transactionscom.xml" />
 
 <assetAccount name="LD Chuck-E-Cheese token side acct" 
 file="LD-side.xml" 
 AccountID="df9834lkjs5jf8" />
 
 <assetAccount name="LD Main Acct" 
 file="LD-main.xml" 
 AccountID="af9834lkjs5jf6" />
 
 <assetAccount name="Kacey Shopping Acct" 
 file="Kacey-main.xml" 
 AccountID="bw9834lkjs5jf6" />
 */



bool OTPseudonym::VerifyPseudonym() const
{
	OTString strPublicKey;
	bool bGotPublicKey = GetPublicKey().GetPublicKey(strPublicKey);
	
	if (!bGotPublicKey)
	{
		OTLog::Error("Error getting public key in OTPseudonym::VerifyPseudonym.\n");
		return false;	
	}
	
	
	OTIdentifier newID;
	bool bSuccessCalculateDigest = newID.CalculateDigest(strPublicKey);
	
	if (!bSuccessCalculateDigest)
	{
		OTLog::Error("Error calculating Certificate digest.\n");
		return false;	
	}
	
	
	// newID now contains the Hash aka Message Digest aka Fingerprint aka "IDENTIFIER" 
	// of the public key (in its text form, with escaped bookends.)
	// 
	// Now let's compare that identifier to the one already loaded by the wallet
	// and make sure they MATCH.
	
	if (!(m_nymID == newID))
	{
		OTString str1(m_nymID), str2(newID);
		OTLog::vError("\nHashes do NOT match in OTPseudonym::VerifyPseudonym!\n%s\n%s\n",
				str1.Get(), str2.Get());
		return false;
	}
	else {
//		OTString str2(newID);
//		OTLog::Output(1, "\nNymID from wallet *SUCCESSFUL* match to hash of Nym\'s public key:\n%s\n"
//				"---------------------------------------------------------------\n", str2.Get());
		return true;
	}
}





void OTPseudonym::DisplayStatistics(OTString & strOutput)
{	
	strOutput.Concatenate("==> Name: %s\n", m_strName.Get());
	strOutput.Concatenate(" Version: %s\n", m_strVersion.Get());
	
	OTString theStringID;
	GetIdentifier(theStringID);
	strOutput.Concatenate("Nym (aka User) ID: %s\n", theStringID.Get());
	
	for (mapOfRequestNums::iterator ii = m_mapRequestNum.begin();  ii != m_mapRequestNum.end(); ++ii)
	{
		std::string strServerID	= ii->first;
		long lRequestNumber		= ii->second;
		
		// Now we can log BOTH, before and after...
		strOutput.Concatenate("Request Number is %ld for server ID: %s\n", 
					   lRequestNumber, strServerID.c_str());
	}
	
	for (mapOfTransNums::iterator iii = m_mapTransNum.begin(); iii != m_mapTransNum.end(); ++iii)
	{	
		std::string strServerID		= (*iii).first;
		dequeOfTransNums * pDeque	= (iii->second);
		
		OT_ASSERT(NULL != pDeque);
		
		if (!(pDeque->empty()))
		{
			for (unsigned i = 0; i < pDeque->size(); i++)
			{
				long lTransactionNumber = pDeque->at(i);
				
				strOutput.Concatenate("Transaction Number available (%ld) for server ID: %s\n", 
							   lTransactionNumber, strServerID.c_str());
			}
		}
	} // for
}




bool OTPseudonym::SavePseudonymWallet(OTString & strOutput) const
{
	OTString nymID;
	GetIdentifier(nymID);
	
	OTASCIIArmor ascName;
	
	if (m_strName.Exists()) // name is in the clear in memory, and base64 in storage.
	{
		ascName.SetString(m_strName, false); // linebreaks == false
	}

	strOutput.Concatenate("<pseudonym name=\"%s\"\n"
			" nymID=\"%s\" />\n\n",
			ascName.Get(),
			nymID.Get());
	
	return true;
}


bool OTPseudonym::SavePseudonymWallet(std::ofstream & ofs) const
{
	OTString strOutput;
	
	if (SavePseudonymWallet(strOutput))
		ofs << strOutput.Get();
	else
		return false;
	
	return true;
}



/*
bool OTPseudonym::SavePseudonymWallet(FILE * fl) const
{
	if (NULL != fl)
	{
		OTString nymID;
		GetIdentifier(nymID);
		
		fprintf(fl, "<pseudonym name=\"%s\"\n"
				" nymID=\"%s\"\n"
				" file=\"%s\""
				">\n\n",
				m_strName.Get(), nymID.Get(), m_strNymfile.Get());
	}
	else {
		return false;
	}
	
	return true;
}
*/

// -----------------------------------------------------


//
// This function saves the public key to a file.
//
bool OTPseudonym::SavePublicKey(const OTString & strPath) const
{
	/* // old version uses fopen.
#ifdef _WIN32
	FILE * fl = NULL;
	errno_t err = fopen_s(&fl, strPath.Get(), "wb");
#else
	FILE * fl  = fopen(strPath.Get(), "w");
#endif
	bool bSave = false;
	*/

	std::ofstream ofs(strPath.Get(), std::ios::binary);
	
	if (ofs.fail())
	{
		OTLog::vError("Failed saving public key for nym: %s\n", strPath.Get());
		return false;
	}
	
	ofs.clear();

	bool bSave = SavePublicKey(ofs);
	ofs.close();
	
	return bSave;
}


bool OTPseudonym::SavePublicKey(std::ofstream & ofs) const
{
	// By passing in an OTString instead of OTASCIIArmor, it knows to add the bookends
	// ----- BEGIN PUBLIC KEY  etc.  These bookends are necessary for OTASCIIArmor to later
	// read the thing back up into memory again.
	OTString strKey;
	
	if (GetPublicKey().GetPublicKey(strKey, false)) // false means "do not ESCAPE the bookends"
		// Ie we'll get ----------- instead of - ---------
	{
		strKey.WriteToFile(ofs);
	}
	else 
	{
		OTLog::Error("Error in OTPseudonym::SavePublicKey: unable to GetPublicKey from Nym\n");
		return false;
	}
	
	return true;
}

/*
bool OTPseudonym::SavePublicKey(FILE * fl) const
{
	if (NULL != fl)
	{
		// By passing in an OTString instead of OTASCIIArmor, it knows to add the bookends
		// ----- BEGIN PUBLIC KEY  etc.  These bookends are necessary for OTASCIIArmor to later
		// read the thing back up into memory again.
		OTString strKey;
		
		if (GetPublicKey().GetPublicKey(strKey, false)) // false means "do not ESCAPE the bookends"
			// Ie we'll get ----------- instead of - ---------
		{
			strKey.WriteToFile(fl);
		}
		else {
			OTLog::Error("Error in OTPseudonym::SavePublicKey: unable to GetPublicKey from Nym\n");
			return false;
		}
	}
	else {
		return false;
	}
	
	return true;
}
*/




// This version is run on the server side, and assumes only a Public Key.
// This code reads up the file, discards the bookends, and saves only the gibberish itself.
bool OTPseudonym::LoadPublicKey()
{
	OTString strID, strPubKeyFile;
	
	GetIdentifier(strID);
	
	strPubKeyFile.Format("%s%s%s%s%s", OTLog::Path(), OTLog::PathSeparator(),
						 OTLog::PubkeyFolder(),
						 OTLog::PathSeparator(), strID.Get());
	
	// This loads up the ascii-armored Public Key.
	// On the client side, the entire x509 is stored.
	// On the server side, it's just the public key. 
	bool bLoadKeyFile = m_ascCert.LoadFromFile(strPubKeyFile);

	// If successful, I load the same file again, but this time using OpenSSL
	if (bLoadKeyFile)
	{
		// Unlike above, where I'm merely reading a text file into a memory buffer,
		// this time we are actually trying to use OpenSSL to really extract the
		// public key from that same file.
		OTAsymmetricKey & pubKey = (OTAsymmetricKey &)GetPublicKey();
		
		bool bLoadPublicKey = pubKey.LoadPublicKey(strPubKeyFile);
		
		if (!bLoadPublicKey)
		{
			OTLog::vError("Although the ascii-armored file (%s) was read, LoadPublicKey "
					"returned false.\n", strPubKeyFile.Get());
			return false;
		}
		else
		{
			OTLog::vOutput(4, "Successfully loaded public key from file: %s\n", strPubKeyFile.Get());
		}		
		return true;	
	}
	else
	{
		OTLog::Output(2, "Failure in OTPseudonym::LoadPublicKey.\n");
		return false;
	}
}




bool OTPseudonym::SavePseudonym() 
{
	if (!m_strNymfile.GetLength())
	{
		OTString nymID;
		GetIdentifier(nymID);
		m_strNymfile.Format("%s%s%s%s%s", OTLog::Path(), OTLog::PathSeparator(),
							OTLog::NymFolder(),
							OTLog::PathSeparator(), nymID.Get());
	}
	
		OTLog::vOutput(2, "Saving nym to: %s\n", m_strNymfile.Get());
	
	return SavePseudonym(m_strNymfile.Get());
}



bool OTPseudonym::SavePseudonym(const char * strPath)
{	
	OT_ASSERT(NULL != strPath);
	
	std::ofstream ofs(strPath, std::ios::binary);
	
	if (ofs.fail())
	{
		OTLog::vError("Failed opening file to save Nym: %s\n", strPath);
		return false;
	}
	
	ofs.clear();

	bool bSave = SavePseudonym(ofs);

	ofs.close();
	
	return bSave;	
}




/*
bool OTPseudonym::SavePseudonym(const char * strPath)
{	
	if (NULL == strPath)
		return false;
	
#ifdef _WIN32
	FILE * fl = NULL;
	errno_t err = fopen_s(&fl, strPath, "wb");
#else
	FILE * fl  = fopen(strPath, "w");
#endif
	bool bSave = false;
	
	if (NULL != fl)
	{
		bSave = SavePseudonym(fl);
		fclose(fl);
	}
	else {
		OTLog::vError("Error saving nym to: %s\n", strPath);
		bSave = false;
	}
	
	return bSave;	
}
*/


bool OTPseudonym::SavePseudonym(std::ofstream & ofs)
{
	OTString strNym;
	SavePseudonym(strNym);
		
	ofs << strNym.Get();
	
	return true;
}

/*
bool OTPseudonym::SavePseudonym(FILE * fl)
{
	OT_ASSERT_MSG(NULL != fl, "Null file pointer sent to OTPseudonym::SavePseudonym. (Why?)\n");
	
	OTString strNym;
	SavePseudonym(strNym);
	
	fprintf(fl, "%s", strNym.Get());	
	
	return true;
}
*/

// Save the Pseudonym to a string...
bool OTPseudonym::SavePseudonym(OTString & strNym)
{
	OTString nymID;
	GetIdentifier(nymID);
	
	strNym.Concatenate("<?xml version=\"%s\"?>\n\n", "1.0");	
	
	strNym.Concatenate("<OTuser version=\"%s\"\n"
			" nymID=\"%s\""
			">\n\n", 
			m_strVersion.Get(), 
			nymID.Get()
			);
	
	// -------------------------------------

	std::string	strServerID;
	long		lRequestNum;
	
	for (mapOfRequestNums::iterator ii = m_mapRequestNum.begin(); ii != m_mapRequestNum.end(); ++ii)
	{	
		strServerID = (*ii).first;
		lRequestNum = (*ii).second;
		
		strNym.Concatenate("<requestNum\n"
				" serverID=\"%s\"\n"
				" currentRequestNum=\"%ld\""
				"/>\n\n", 
				strServerID.c_str(),
				lRequestNum
				);
	}
	
	// -------------------------------------
	
	long lTransactionNumber = 0;
	
	for (mapOfTransNums::iterator iii = m_mapTransNum.begin(); iii != m_mapTransNum.end(); ++iii)
	{	
		strServerID					= (*iii).first;
		dequeOfTransNums * pDeque	= (iii->second);
		
		OT_ASSERT(NULL != pDeque);
		
		if (!(pDeque->empty()))
		{
			for (unsigned i = 0; i < pDeque->size(); i++)
			{
				lTransactionNumber = pDeque->at(i);
				
				strNym.Concatenate("<transactionNum\n"
								   " serverID=\"%s\"\n"
								   " transactionNum=\"%ld\""
								   "/>\n\n", 
								   strServerID.c_str(),
								   lTransactionNumber
								   );
			}
		}
	} // for
	
	// -------------------------------------
	
	lTransactionNumber = 0;
	
	for (mapOfTransNums::iterator iii = m_mapIssuedNum.begin(); iii != m_mapIssuedNum.end(); ++iii)
	{	
		strServerID					= (*iii).first;
		dequeOfTransNums * pDeque	= (iii->second);
		
		OT_ASSERT(NULL != pDeque);
		
		if (!(pDeque->empty()))
		{
			for (unsigned i = 0; i < pDeque->size(); i++)
			{
				lTransactionNumber = pDeque->at(i);
				
				strNym.Concatenate("<issuedNum\n"
								   " serverID=\"%s\"\n"
								   " transactionNum=\"%ld\""
								   "/>\n\n", 
								   strServerID.c_str(),
								   lTransactionNumber
								   );
			}
		}
	} // for
	
	// -------------------------------------
	
	strNym.Concatenate("</OTuser>\n");	
	
	return true;
	
}



/*
 
 Enumeration for all xml nodes which are parsed by IrrXMLReader.
 
 Enumeration values:
 
 EXN_NONE			No xml node. This is usually the node if you did not read anything yet.
 EXN_ELEMENT		A xml element, like <foo>.
 EXN_ELEMENT_END	End of an xml element, like </foo>.
 EXN_TEXT			Text within a xml element: <foo> this is the text. </foo>.
 EXN_COMMENT		An xml comment like <!-- I am a comment --> or a DTD definition.
 EXN_CDATA			An xml cdata section like <![CDATA[ this is some CDATA ]]>.
 EXN_UNKNOWN		Unknown element.
 
 Definition at line 180 of file irrXML.h.
 
 */
bool OTPseudonym::LoadFromString(const OTString & strNym)
{
	bool bSuccess = false;

	OTStringXML strNymXML(strNym);
	IrrXMLReader* xml = createIrrXMLReader(&strNymXML);
	OT_ASSERT(NULL != xml);
	
	// parse the file until end reached
	while(xml && xml->read())
	{
		// strings for storing the data that we want to read out of the file
		OTString UserNymID;
		
		OTString ReqNumServerID;
		OTString ReqNumCurrent;
		
		OTString TransNumServerID;
		OTString TransNumAvailable;
		
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
				if (!strcmp("OTuser", xml->getNodeName()))
				{
					m_strVersion	= xml->getAttributeValue("version");					
					UserNymID		= xml->getAttributeValue("nymID");	
					
					//TODO: no need to set the ID again here. We already know the ID
					// at this point. Better to check and compare they are the same here.
					//m_nymID.SetString(UserNymID);
					//
					
					if (UserNymID.GetLength())
						OTLog::vOutput(0, "\nLoading user, version: %s NymID:\n%s\n", m_strVersion.Get(), UserNymID.Get());
					bSuccess = true;
				}
				else if (!strcmp("requestNum", xml->getNodeName()))
				{
					ReqNumServerID = xml->getAttributeValue("serverID");				
					ReqNumCurrent = xml->getAttributeValue("currentRequestNum");
					
					OTLog::vOutput(1, "\nCurrent Request Number is %s for ServerID: %s\n",
							ReqNumCurrent.Get(), ReqNumServerID.Get());
					
					// Make sure now that I've loaded this request number, to add it to my
					// internal map so that it is available for future lookups.
					m_mapRequestNum[ReqNumServerID.Get()] = atol(ReqNumCurrent.Get());
				}
				else if (!strcmp("transactionNum", xml->getNodeName()))
				{
					TransNumServerID	= xml->getAttributeValue("serverID");				
					TransNumAvailable	= xml->getAttributeValue("transactionNum");
					
					OTLog::vOutput(1, "Transaction Number %s available for ServerID: %s\n",
								   TransNumAvailable.Get(), TransNumServerID.Get());
					
					AddTransactionNum(TransNumServerID, atol(TransNumAvailable.Get())); // This version doesn't save to disk. (Why save to disk AS WE'RE LOADING?)
				}
				else if (!strcmp("issuedNum", xml->getNodeName()))
				{
					TransNumServerID	= xml->getAttributeValue("serverID");				
					TransNumAvailable	= xml->getAttributeValue("transactionNum");
					
					OTLog::vOutput(1, "Currently liable for Transaction Number %s, for ServerID: %s\n",
								   TransNumAvailable.Get(), TransNumServerID.Get());
					
					AddIssuedNum(TransNumServerID, atol(TransNumAvailable.Get())); // This version doesn't save to disk. (Why save to disk AS WE'RE LOADING?)
				}
				else
				{
					// unknown element type
					OTLog::vError("unknown element type in OTPseudonym::LoadFromString: %s\n", xml->getNodeName());
					bSuccess = false;
				}
				break;
			}
			default:
			{
				OTLog::vOutput(5, "Unknown XML type in OTPseudonym::LoadFromString: %s\n", xml->getNodeName());
				break;	
			}
		} // switch
	} // while
		
	
	if (NULL != xml)
	{
		delete xml;
		xml = NULL;
	}
	
	return bSuccess;
}




bool OTPseudonym::LoadSignedNymfile(OTPseudonym & SIGNER_NYM)
{
	// Get the Nym's ID in string form
	OTString nymID;
	GetIdentifier(nymID);
	
	// Create an OTSignedFile object, giving it the filename (the ID) and the local directory ("nyms")
	OTSignedFile	theNymfile("nyms", nymID);
	
	// We verify:
	//
	// 1. That the file even exists and loads.
	// 2. That the local subdir and filename match the versions inside the file.
	// 3. That the signature matches for the signer nym who was passed in.
	//
	if (theNymfile.LoadFile()  
		&& theNymfile.VerifyFile() 
		&& theNymfile.VerifySignature(SIGNER_NYM) 
		)
	{
		OTLog::Output(4, "Loaded and verified signed nymfile. Reading from string...\n");
		
		if (theNymfile.GetFilePayload().GetLength() > 0)
			return LoadFromString(theNymfile.GetFilePayload());
		else 
		{
			const long lLength = static_cast<long> (theNymfile.GetFilePayload().GetLength());
			
			OTLog::vError("Bad length (%ld) while loading nymfile:\n%s\n", lLength, nymID.Get());
		}
	}
	else 
	{
		OTLog::vError("Error Loading or verifying signed nymfile:\n%s\n\n", nymID.Get());
	}

	return false;
}

bool OTPseudonym::SaveSignedNymfile(OTPseudonym & SIGNER_NYM)
{
	// Get the Nym's ID in string form
	OTString nymID;
	GetIdentifier(nymID);

	// Create an OTSignedFile object, giving it the filename (the ID) and the local directory ("nyms")
	OTSignedFile	theNymfile("nyms", nymID);
	theNymfile.GetFilename(m_strNymfile);
	
	OTLog::vOutput(2, "Saving nym to: %s\n", m_strNymfile.Get());
	
	// First we save this nym to a string...
	// Specifically, the file payload string on the OTSignedFile object.
	SavePseudonym(theNymfile.GetFilePayload());

	// Now the OTSignedFile contains the path, the filename, AND the
	// contents of the Nym itself, saved to a string inside the OTSignedFile object.
	
	if (theNymfile.SignContract(SIGNER_NYM) && 
		theNymfile.SaveContract())
	{
		return theNymfile.SaveFile();
	}
	
	return false;
}





// Each Nym has a public key file, as well as a nym file. Why two separate files?
// Because they are often used for different purposes and are being loaded/saved 
// for their own reasons. The Nymfile contains the user ID, which is a hash of the
// public key, so the it knows how to find the right pubkey file (filename is the
// hash) and it knows how to validate the contents (by hashing them.) The Nymfile
// also contains the transaction numbers that have been issued to that nym, so 
// the server might later load it up in order to verify that a specific transaction
// number is indeed on that list (and then remove it from the list.)
bool OTPseudonym::LoadNymfile(const char * szFilename/*=NULL*/)
{
	// If no filename was passed in (user might have designated one) then we create
	// the filename by appending the Nym's ID to the path.
	if (NULL == szFilename)
	{
		OTString strID;
		GetIdentifier(strID);
		m_strNymfile.Format((char *)"%s%s%s%s%s", OTLog::Path(), OTLog::PathSeparator(),
							OTLog::NymFolder(), OTLog::PathSeparator(), strID.Get());
	}
	else {
		m_strNymfile = szFilename;
	}

	
	std::ifstream in(m_strNymfile.Get(), std::ios::binary);
	
	if (in.fail())
	{
		OTLog::vError("Error opening file in OTPseudonym::LoadNymfile: %s\n",
					  m_strNymfile.Get());
		return false;
	}
	
	std::stringstream buffer;
	buffer << in.rdbuf();
	
	std::string contents(buffer.str());
	
	OTString strRawFile = contents.c_str();
	
	if (strRawFile.GetLength())
		return LoadFromString(strRawFile);
		
	return false;
}


bool OTPseudonym::Loadx509CertAndPrivateKey()
{
	OTString strID(m_nymID);

	m_strCertfile.Format((char *)"%s%s%s%s%s", OTLog::Path(), OTLog::PathSeparator(),
						 OTLog::CertFolder(),
						 OTLog::PathSeparator(), strID.Get());
	
	// This loads up the ascii-armored Cert from the certfile, minus the ------ bookends.
	// Later we will use this to create a hash and verify against the NymID that was in the wallet.
	bool bRetVal = m_ascCert.LoadFromFile(m_strCertfile);
	
	// I load the same file again, but this time using OpenSSL functions to read the public
	// key and private key (if necessary) from the same file.
	if (bRetVal)
	{
		bool bPublic  = false;
		bool bPrivate = false;
		
		bPublic  = m_pkeyPublic->LoadPublicKeyFromCertFile(m_strCertfile);
		bPrivate = m_pkeyPrivate->LoadPrivateKey(m_strCertfile);
		//		bPrivate = true;
		
		if (!bPublic)
		{
			OTLog::vError("Although the ascii-armored file (%s) was read, LoadPublicKeyFromCert "
					"returned false.\n", m_strCertfile.Get());
			return false;
		}
		else
		{
			OTLog::vOutput(2, "Successfully loaded public key from Certfile: %s\n", m_strCertfile.Get());
		}
		
		
		if (!bPrivate)
		{
			OTLog::vError("Although the ascii-armored file (%s) was read, LoadPrivateKey returned false.\n",
					m_strCertfile.Get());
			return false;
		}
		else
		{
			OTLog::vOutput(2, "Successfully loaded private key from: %s\n", m_strCertfile.Get());
		}
		
		return true;	
	}
	else
	{
		OTLog::vError("Failure in OTPseudonym::Loadx509CertAndPrivateKey, filename:\n%s\n", m_strCertfile.Get());
		return false;
	}
}





// This version WILL handle the bookends: -----BEGIN CERTIFICATE------ 
// It will also handle the escaped version: - -----BEGIN CERTIFICATE-----
bool OTPseudonym::SetCertificate(const OTString & strCert, bool bEscaped/*=true*/)
{
	return m_pkeyPublic->LoadPublicKeyFromCertString(strCert, bEscaped);
}


// This version WILL handle the bookends -----BEGIN PUBLIC KEY------ 
// It will also handle the escaped version: - -----BEGIN PUBLIC KEY------
bool OTPseudonym::SetPublicKey(const OTString & strKey, bool bEscaped/*=true*/)
{	
	if (strKey.Contains("PGP PUBLIC KEY"))
	{
		OTASCIIArmor theArmor;
		
		if (theArmor.LoadFromString((OTString &)strKey, bEscaped))
		{
			// This function expects that the bookends are already removed.
			// The ascii-armor loading code removes them and handles the escapes also.
			return m_pkeyPublic->LoadPublicKeyFromPGPKey(theArmor);
		}
		else {
			OTLog::Output(2, "Failed extracting PGP public key from ascii-armored text.\n");
			return false;
		}
	}
	else // the below function SetPublicKey (in the return call) expects the
		 // bookends to still be there, and it will handle removing them. (Unlike PGP code above.)
		return m_pkeyPublic->SetPublicKey(strKey, bEscaped);
}




// This version handles the ascii-armored text WITHOUT the bookends
bool OTPseudonym::SetPublicKey(const OTASCIIArmor & strKey)
{
	return m_pkeyPublic->SetPublicKey(strKey);
}


// sets internal member based in ID passed in
void OTPseudonym::SetIdentifier(const OTIdentifier & theIdentifier)
{
	m_nymID = theIdentifier;
}

// sets argument based on internal member
void OTPseudonym::GetIdentifier(OTIdentifier & theIdentifier) const
{
	theIdentifier = m_nymID;
}

// sets internal member based in ID passed in
void OTPseudonym::SetIdentifier(const OTString & theIdentifier)
{
	m_nymID.SetString(theIdentifier);
}

// sets argument based on internal member
void OTPseudonym::GetIdentifier(OTString & theIdentifier) const
{	
	m_nymID.GetString(theIdentifier);
}


const OTAsymmetricKey & OTPseudonym::GetPublicKey() const
{
	return (*m_pkeyPublic);
}

const OTAsymmetricKey & OTPseudonym::GetPrivateKey() const
{
	return (*m_pkeyPrivate);
}



OTPseudonym::OTPseudonym()
{
	m_pkeyPublic = new OTAsymmetricKey;
	m_pkeyPrivate = new OTAsymmetricKey;
	Initialize();
}

void OTPseudonym::Initialize()
{
	m_strVersion = "1.0";
}

OTPseudonym::OTPseudonym(const OTString & name, const OTString & filename, const OTString & nymID)
{
	m_pkeyPublic = new OTAsymmetricKey;
	m_pkeyPrivate = new OTAsymmetricKey;

	Initialize();
	
	m_strName		= name;
	m_strNymfile	= filename;
	
	m_nymID.SetString(nymID);
}

OTPseudonym::OTPseudonym(const OTIdentifier & nymID)
{
	m_pkeyPublic = new OTAsymmetricKey;
	m_pkeyPrivate = new OTAsymmetricKey;

	Initialize();
	
	m_nymID = nymID;
}

OTPseudonym::OTPseudonym(const OTString & strNymID)
{
	m_pkeyPublic = new OTAsymmetricKey;
	m_pkeyPrivate = new OTAsymmetricKey;

	Initialize();
	
	m_nymID.SetString(strNymID);
}

OTPseudonym::~OTPseudonym()
{
	delete m_pkeyPublic;
	delete m_pkeyPrivate;
	m_pkeyPublic	= NULL;
	m_pkeyPrivate	= NULL;
	
	ReleaseTransactionNumbers();
}




















