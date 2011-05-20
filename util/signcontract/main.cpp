extern "C"
{
#include <stdio.h>
	
#include <openssl/ssl.h>
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


#include "OTString.h"
#include "OTIdentifier.h"
#include "OTPseudonym.h"
#include "OTAssetContract.h"
#include "OTServerContract.h"
#include "OTSignedFile.h"
#include "OTLog.h"
//#include "OTStorage.h"


// Run this program from inside the testwallet directory.

int main (int argc, char * const argv[])
{
	
	if (argc < 3)
	{
		printf("Usage:  signcontract  s|a  nym_id  contract_file\n"
			   "Current path: %s\n"
			   "Use 's' when signing a server contract, and 'a' for an asset contract.\n\n",
			   OTLog::Path());
		exit(1);
	}
	
	SSL_library_init();
	SSL_load_error_strings();
	
	bool bIsServerContract = (*(argv[1]) == 's') ? true : false;
	
	OTString strNymID(argv[2]), strContractFile(argv[3]);
	OTString NymName(strNymID), NymFile;
	
	NymFile.Format("%s%snyms%s%s", OTLog::Path(), OTLog::PathSeparator(),
				   OTLog::PathSeparator(), strNymID.Get());
	
	OTPseudonym theNym(NymName, NymFile, strNymID);
	
	OTSignedFile theFile("nyms", strNymID.Get());
	
	if (theFile.LoadFile())
	{
		OTString strFileContents(theFile.GetFilePayload());
		
		if (theNym.Loadx509CertAndPrivateKey() && theNym.VerifyPseudonym()) 
		{							
			// LoadFile() loads the OTSignedFile that contains the nym.
			// VerifyFile() insures that the name I thought it would have, and
			//              where it was found, matches the name inside the file.
			// VerifySignature() makes sure that the Nym signed it. 
			//				(Won't work on server sign where Nyms don't sign themselves.)
			// LoadFromString() loads the Nym object out of the string from the OTSignedFile.
			//
			if (
				//theFile.VerifyFile() && 
				//theFile.VerifySignature(theNym) && 
				theNym.LoadFromString(strFileContents)) 
			{
				std::ifstream in(strContractFile.Get());
				
				std::stringstream buffer;
				buffer << in.rdbuf();
				
				std::string contents(buffer.str());
				
				OTString strContract(contents.c_str());				
				
				if (strContract.GetLength())
				{
					OTAssetContract theAssetContract;
					OTServerContract theServerContract;
					
					if (bIsServerContract)
						theServerContract.CreateContract(strContract, theNym);
					else
						theAssetContract.CreateContract(strContract, theNym);

					OTString strOutput, strDigest;
					
					if (bIsServerContract)
					{
						theServerContract.GetIdentifier(strDigest);
						theServerContract.SaveContract(strOutput);
					}
					else
					{
						theAssetContract.GetIdentifier(strDigest);
						theAssetContract.SaveContract(strOutput);
					}
					
					fprintf(stdout, "\n\n Contract ID:\n%s\n\nContract:\n%s\n", 
							strDigest.Get(), strOutput.Get());
				}
			}
		}
	}
	
	return 0;
}
