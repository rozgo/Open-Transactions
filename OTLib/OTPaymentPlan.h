/************************************************************************************
 *    
 *  OTPaymentPlan.h
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


#ifndef __OT_PAYMENT_PLAN__
#define __OT_PAYMENT_PLAN__



#include "OTAgreement.h"


/*
 OTPaymentPlan
  
 This instrument is signed by two parties or more (the first one, I think...)
 
 While processing payment, BOTH parties to a payment plan will be loaded up and
 their signatures will be checked against the original plan, which is saved as a
 cron receipt.
 
 There is also a "current version" of the payment plan, which contains updated info
 from processing, and is signed by the server.
 
 BOTH the original version, and the updated version, are sent to EACH user whenever
 a payment is processed, as his receipt. This way you have the user's signature on 
 the terms, and the server's signature whenever it carries out the terms. A receipt
 with both is placed in the inbox of both users after any action.
 
 As with cheques, the server can use the receipts in the inboxes, plus the last agreed
 balance, to prove the current balance of any account. The user removes the receipt from
 his inbox by accepting it and, in the process, performing a new balance agreement.
 
 THIS MEANS that the OT server can carry out the terms of contracts!  So far, at least,
 cheques, trades, payment plans... as long as everything is signed off, we're free and
 clear under the same triple-signed system that account transfer uses. (The Users cannot
 repudiate their own signatures later, and the server can prove all balances with the
 user's own signature.)
 
 Of course, either side is free to CANCEL a payment plan, or to leave their account bereft
 of funds and prone to failed payments. But if they cancel, their signature will appear
 on the cancellation request, and the recipient gets a copy of it in his inbox. And if
 the funds are insufficient, the plan will keep trying to charge, leaving failure notices
 in both inboxes when such things occur.
 
 You could even have the server manage an issuer account, backed in payment plan revenue,
 that would form a new asset type that can then be traded on markets. (The same as you can
 have the server manage the issuer account for a basket currency now, which is backed with
 reserve accounts managed by the server, and you can then trade the basket currency on markets.)
 
 ———————————————————————————————
 */





class OTPaymentPlan : public OTAgreement
{
	// *************************** Methods for generating a payment plan: ***************************
	
public: 
	// From parent:  (This must be called first, before the other two methods below can be called.)	
	//
	//	bool		SetAgreement(const long & lTransactionNum,	const OTString & strConsideration,
	//							 const time_t & VALID_FROM=0,	const time_t & VALID_TO=0);
	
	// From this:
	bool		SetInitialPayment(const long & lAmount, time_t tTimeUntilInitialPayment=0); // default: now.
	
	// These two can be called independent of each other. You can 
	// have an initial payment, AND/OR a payment plan.
	
	bool		SetPaymentPlan(const long & lPaymentAmount, time_t tTimeUntilPlanStart=2592000, // Default: 1st payment in 30 days
							   time_t tBetweenPayments=2592000, // Default: 30 days.
							   time_t tPlanLength=0, int nMaxPayments=0);
	
	
	
	
	// ********************* "INITIAL PAYMENT" public GET METHODS	*********************
public:
	inline bool				HasInitialPayment()		const	{ return m_bInitialPayment; }	
	inline const time_t &	GetInitialPaymentDate()	const	{ return m_tInitialPaymentDate; }
	inline const long &		GetInitialPaymentAmount()const	{ return m_lInitialPaymentAmount; }
	inline bool				IsInitialPaymentDone()	const	{ return m_bInitialPaymentDone; }
	
	inline const time_t &	GetInitialPaymentCompletedDate() const	{ return m_tInitialPaymentCompletedDate; }
	inline const time_t &	GetLastFailedInitialPaymentDate() const	{ return m_tFailedInitialPaymentDate; }
	inline int				GetNoInitialFailures()	 const	{ return m_nNumberInitialFailures; }

	
	// "INITIAL PAYMENT" private MEMBERS
private:
	bool	m_bInitialPayment;				// Will there be an initial payment?
	time_t	m_tInitialPaymentDate;			// Date of the initial payment, measured seconds after creation.
	time_t	m_tInitialPaymentCompletedDate;	// Date the initial payment was finally transacted.
	time_t	m_tFailedInitialPaymentDate;	// Date of the last failed payment, measured seconds after creation.
	long	m_lInitialPaymentAmount;		// Amount of the initial payment.
	bool	m_bInitialPaymentDone;			// Has the initial payment been made?
	int		m_nNumberInitialFailures;		// If we've tried to process this multiple times, we'll know.
	
	// --------------------------------------------------------------------------
	// "INITIAL PAYMENT" protected SET METHODS
protected:
	inline void SetInitialPaymentDate(const time_t & tInitialPaymentDate) { m_tInitialPaymentDate = tInitialPaymentDate; }
	inline void SetInitialPaymentAmount(const long & lAmount)	{ m_lInitialPaymentAmount = lAmount; }
	
	// Sets the bool that officially the initial payment has been done. (Checks first to make sure not already done.)
	bool SetInitialPaymentDone();

	inline void SetInitialPaymentCompletedDate(const time_t & tInitialPaymentDate) 
	{ m_tInitialPaymentCompletedDate = tInitialPaymentDate; }
	inline void SetLastFailedInitialPaymentDate(const time_t & tFailedInitialPaymentDate) 
	{ m_tFailedInitialPaymentDate = tFailedInitialPaymentDate; }

	inline void	SetNoInitialFailures(const int & nNoFailures)	{ m_nNumberInitialFailures = nNoFailures; }
	inline void	IncrementNoInitialFailures()					{ m_nNumberInitialFailures++; }
	
	
// --------------------------------------------------------------------------
	
	
	
	// ********************* "PAYMENT PLAN" public GET METHODS *********************
public:	
	inline bool				HasPaymentPlan()		 const	{ return m_bPaymentPlan; }
	inline const long &		GetPaymentPlanAmount()	 const	{ return m_lPaymentPlanAmount; }
	inline const time_t &	GetTimeBetweenPayments() const	{ return m_tTimeBetweenPayments; }
	inline const time_t &	GetPaymentPlanStartDate()const	{ return m_tPaymentPlanStartDate; }
	inline const time_t &	GetPaymentPlanLength()	 const	{ return m_tPaymentPlanLength; }
	inline int				GetMaximumNoPayments()	 const	{ return m_nMaximumNoPayments; }
	
	inline const time_t &	GetDateOfLastPayment()	 const	{ return m_tDateOfLastPayment; }
	inline const time_t &	GetDateOfLastFailedPayment() const { return m_tDateOfLastFailedPayment; }
	
	inline int				GetNoPaymentsDone()		 const	{ return m_nNoPaymentsDone; }
	inline int				GetNoFailedPayments()	 const	{ return m_nNoFailedPayments; }
	
	// --------------------------------------------------------------------------
	// "PAYMENT PLAN" private MEMBERS
private:
	bool	m_bPaymentPlan;			// Will there be a payment plan?
	long	m_lPaymentPlanAmount;	// Amount of each payment.
	time_t	m_tTimeBetweenPayments;	// How long between each payment?
	time_t	m_tPaymentPlanStartDate;// Date for the first payment plan payment.
	time_t	m_tPaymentPlanLength;	// Optional. Plan length measured in seconds since plan start.
	int		m_nMaximumNoPayments;	// Optional. The most number of payments that are authorized.
	
	time_t	m_tDateOfLastPayment;	// Recording of date of the last payment.
	time_t	m_tDateOfLastFailedPayment;	// Recording of date of the last failed payment.
	int		m_nNoPaymentsDone;		// Recording of the number of payments already processed.
	int		m_nNoFailedPayments;	// Every time a payment fails, we record that here.
	
	// --------------------------------------------------------------------------
	// "PAYMENT PLAN" protected SET METHODS	
protected:
	inline void SetPaymentPlanAmount(const		 long &	lAmount)		{ m_lPaymentPlanAmount		= lAmount; }
	inline void SetTimeBetweenPayments(const	 time_t&tTimeBetween)	{ m_tTimeBetweenPayments	= tTimeBetween; }
	inline void SetPaymentPlanStartDate(const	 time_t&tPlanStartDate)	{ m_tPaymentPlanStartDate	= tPlanStartDate; }
	inline void SetPaymentPlanLength(const		 time_t&tPlanLength)	{ m_tPaymentPlanLength		= tPlanLength; }
	inline void SetMaximumNoPayments(			 int	nMaxNoPayments)	{ m_nMaximumNoPayments		= nMaxNoPayments; }
	
	inline void SetDateOfLastPayment(const		 time_t&tDateOfLast)	{ m_tDateOfLastPayment		= tDateOfLast; }
	inline void SetDateOfLastFailedPayment(const time_t&tDateOfLast)	{ m_tDateOfLastFailedPayment= tDateOfLast; }
	
	inline void SetNoPaymentsDone(				 int	nNoPaymentsDone){ m_nNoPaymentsDone			= nNoPaymentsDone; }
	inline void SetNoFailedPayments(			 int	nNoFailed)		{ m_nNoFailedPayments		= nNoFailed; }

	inline void IncrementNoPaymentsDone()								{ m_nNoPaymentsDone++; }
	inline void IncrementNoFailedPayments()								{ m_nNoFailedPayments++; }
	
// --------------------------------------------------------------------------------------------------
	
	inline bool IsFlaggedForRemoval() const { return m_bFlagForRemoval; }
	inline void SetFlagForRemoval() { m_bFlagForRemoval = true; }
	
private:	// These are NOT stored as part of the payment plan. They are merely used during execution.
	bool	m_bProcessingInitialPayment;
	bool	m_bProcessingPaymentPlan;
	bool	m_bFlagForRemoval;
	
public: 
	// --------------------------------------------------------------------------
	
	// From OTAgreement (parent class of this)
	/*
	 inline OTIdentifier &	GetRecipientAcctID()		{ return m_RECIPIENT_ACCT_ID; }
	 inline OTIdentifier &	GetRecipientUserID()		{ return m_RECIPIENT_USER_ID; }
	 inline void			SetRecipientAcctID(OTIdentifier & ACCT_ID)	{ m_RECIPIENT_ACCT_ID = ACCT_ID; }
	 inline void			SetRecipientUserID(OTIdentifier & USER_ID)	{ m_RECIPIENT_USER_ID = USER_ID; }

	 OTString		m_strConsideration;	// Presumably an agreement is in return for some consideration. Memo here.
	 */
	// Return True if should stay on OTCron's list for more processing.
	// Return False if expired or otherwise should be removed.
	virtual bool ProcessCron(); // OTCron calls this regularly, which is my chance to expire, etc.
	
	// --------------------------------------------------------------------------
	
	// From OTCronItem (parent class of OTAgreement, parent class of this)
	/*
	 inline void SetCronPointer(OTCron & theCron) { m_pCron = &theCron; }	 

	 inline void SetCreationDate(const time_t & CREATION_DATE) { m_CREATION_DATE = CREATION_DATE; }
	 inline const time_t & GetCreationDate() const { return m_CREATION_DATE; }
	 */
	
	// --------------------------------------------------------------------------
	
	// From OTTrackable (parent class of OTCronItem, parent class of OTAgreement, parent of this)
	/*
	 inline long GetTransactionNum() const { return m_lTransactionNum; }
	 inline void SetTransactionNum(long lTransactionNum) { m_lTransactionNum = lTransactionNum; }
	 
	 inline const OTIdentifier &	GetSenderAcctID()		{ return m_SENDER_ACCT_ID; }
	 inline const OTIdentifier &	GetSenderUserID()		{ return m_SENDER_USER_ID; }
	 inline void	SetSenderAcctID(const OTIdentifier & ACCT_ID)	{ m_SENDER_ACCT_ID = ACCT_ID; }
	 inline void	SetSenderUserID(const OTIdentifier & USER_ID)	{ m_SENDER_USER_ID = USER_ID; }
	 */
	
	// --------------------------------------------------------------------------
	
	// From OTInstrument (parent of OTTrackable, parent of OTCronItem, parent of OTAgreement, parent of this)
	/*
	 OTInstrument(const OTIdentifier & SERVER_ID, const OTIdentifier & ASSET_ID) : OTContract()
	 
	 inline const OTIdentifier & GetAssetID() const { return m_AssetTypeID; }
	 inline const OTIdentifier & GetServerID() const { return m_ServerID; }
	 
	 inline void SetAssetID(const OTIdentifier & ASSET_ID)  { m_AssetTypeID	= ASSET_ID; }
	 inline void SetServerID(const OTIdentifier & SERVER_ID) { m_ServerID	= SERVER_ID; }
	 
	 inline time_t GetValidFrom()	const { return m_VALID_FROM; }
	 inline time_t GetValidTo()		const { return m_VALID_TO; }
	 
	 inline void SetValidFrom(time_t TIME_FROM)	{ m_VALID_FROM	= TIME_FROM; }
	 inline void SetValidTo(time_t TIME_TO)		{ m_VALID_TO	= TIME_TO; }
	 
	 bool VerifyCurrentDate(); // Verify the current date against the VALID FROM / TO dates.
	 bool IsExpired()
	 */
	
protected:
	bool ProcessPayment(const long & lAmount);
	void ProcessInitialPayment();
	void ProcessPaymentPlan();

public:	
	OTPaymentPlan();
	OTPaymentPlan(const OTIdentifier & SERVER_ID,			const OTIdentifier & ASSET_ID);
	OTPaymentPlan(const OTIdentifier & SERVER_ID,			const OTIdentifier & ASSET_ID,
				  const OTIdentifier & SENDER_ACCT_ID,		const OTIdentifier & SENDER_USER_ID,
				  const OTIdentifier & RECIPIENT_ACCT_ID,	const OTIdentifier & RECIPIENT_USER_ID);
	virtual ~OTPaymentPlan();
	
	void InitPaymentPlan();
	
	virtual void Release();
	
	
	// return -1 if error, 0 if nothing, and 1 if the node was processed.
	virtual int ProcessXMLNode(irr::io::IrrXMLReader*& xml);
	
	virtual void UpdateContents(); // Before transmission or serialization, this is where the ledger saves its contents 
	
	virtual bool SaveContractWallet(std::ofstream & ofs);
	
};








#endif // __OT_PAYMENT_PLAN__
