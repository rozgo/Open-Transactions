/************************************************************************************
 *    
 *  OTString.h
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


#ifndef  __STRING_H__
#define  __STRING_H__

// #include "whatever.h" -- all necessary #includes go here.
// Be sure to use 'extern "C" {   }' as a wrapper for straight 'C' headers.

#include <cstdio>
#include <cstdarg>
#include <cstring>

extern "C" {
#include <stdint.h>
}

#include <fstream>

//#ifdef _WIN32
//#define MAX_STRING_LENGTH   631072
//#else
#define MAX_STRING_LENGTH   1262144
//#endif // _WIN32


// If you've already strlen'd the string,
// you can pass the length to str_hsh or str_dup
// and save it the trouble.
char *str_dup1(const char *str);
char *str_dup2(const char *str, uint32_t length);
int len_cmp(char *s1, char *s2);




// =======================================================================
/*
 * strlcpy and strlcat
 *
 * Copyright (c) 1998 Todd C. Miller <Todd.Miller@courtesan.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * Copy src to string dst of size siz.  At most siz-1 characters
 * will be copied.  Always NUL terminates (unless siz == 0).
 * Returns strlen(src); if retval >= siz, truncation occurred.
 */
inline size_t strlcpy(char *dst, const char *src, size_t siz)
{
    char *d = dst;
    const char *s = src;
    size_t n = siz;
	
    /* Copy as many bytes as will fit */
    if (n != 0)
    {
        while (--n != 0)
        {
            if ((*d++ = *s++) == '\0')
                break;
        }
    }
	
    /* Not enough room in dst, add NUL and traverse rest of src */
    if (n == 0)
    {
        if (siz != 0)
            *d = '\0';  /* NUL-terminate dst */
        while (*s++)
            ;
    }
	
    return(s - src - 1); /* count does not include NUL */
}
/*
 * Appends src to string dst of size siz (unlike strncat, siz is the
 * full size of dst, not space left).  At most siz-1 characters
 * will be copied.  Always NUL terminates (unless siz <= strlen(dst)).
 * Returns strlen(src) + MIN(siz, strlen(initial dst)).
 * If retval >= siz, truncation occurred.
 */
inline size_t strlcat(char *dst, const char *src, size_t siz)
{
    char *d = dst;
    const char *s = src;
    size_t n = siz;
    size_t dlen;
	
    /* Find the end of dst and adjust bytes left but don't go past end */
    while (n-- != 0 && *d != '\0')
        d++;
    dlen = d - dst;
    n = siz - dlen;
	
    if (n == 0)
        return(dlen + strlen(s));
    while (*s != '\0')
    {
        if (n != 1)
        {
            *d++ = *s;
            n--;
        }
        s++;
    }
    *d = '\0';
	
    return(dlen + (s - src)); /* count does not include NUL */
}
// (End of the Todd Miller code.)
// =======================================================================




class OTIdentifier;
class OTContract;
class OTASCIIArmor;
class OTSignature;
class OTPseudonym;
class OTPayload;

class OTString
{
   // Construction -- Destruction
public:
	OTString();
	OTString(const OTString & strValue);
	OTString(const OTASCIIArmor & strValue);
	OTString(const OTSignature & strValue);
	OTString(const OTContract & theValue);
	OTString(const OTIdentifier & theValue);
	OTString(OTPseudonym & theValue);
	OTString(const char * new_string);
   
	virtual ~OTString();

   void Initialize();

	OTString& operator=(const OTString& rhs);
	OTString& operator=(const char * new_string);

   bool operator >(const OTString &s2) const;
   bool operator <(const OTString &s2) const;
   bool operator <=(const OTString &s2) const;
   bool operator >=(const OTString &s2) const;
   bool operator ==(const OTString &s2) const;

   // Attributes
public:

   // Operations
public:	
	inline bool At(uint32_t lIndex, char &c) { if (lIndex < m_lLength) { c = m_strBuffer[lIndex]; return true;} 
		else return false; }
   bool Exists(void) const;
   uint32_t GetLength(void) const;

	bool Compare(const char * strCompare) const;
	bool Compare(const OTString& strCompare) const;
	
	bool Contains(const char * strCompare) const;
	bool Contains(const OTString& strCompare) const;
	
	const char * Get(void) const;
	
	void   Set(const char * new_string, uint32_t nEnforcedMaxLength=0);
	void   Set(const OTString & strBuf);
	
//	void   Concatenate(const char *arg);
	void   Concatenate(const char *arg, ...);
	void   Concatenate(const OTString & strBuf);
	
	void   Truncate(uint32_t lAt);
	
	void   Format(const char *arg, ...);
   
	void ConvertToLowerCase();
	void ConvertToUpperCase();
	
	void OTfgets(std::istream & ofs);
//	void OTfgets(FILE * fl);

	// true  == there are more lines to read.
	// false == this is the last line. Like EOF.
	bool sgets(char * szBuffer, unsigned nBufSize);
	
   char sgetc(void);
   void sungetc(void);
   void reset(void);

	void WriteToFile(std::ofstream & ofs) const;
//	void WriteToFile(FILE * fl = NULL) const;

   virtual void Release(void);

   // Implementation
private:

   // Internal properties
private:
   uint32_t  m_lLength;
   uint32_t  m_lPosition;
   char * m_strBuffer;
};

bool operator >(const OTString& s1, const OTString& s2);
bool operator <(const OTString& s1, const OTString& s2);
bool operator >=(const OTString &s1, const OTString& s2);
bool operator <=(const OTString &s1, const OTString& s2);

#endif    // __STRING_H__
