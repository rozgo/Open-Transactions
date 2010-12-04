/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 * 
 * This file is not intended to be easily readable and contains a number of 
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG 
 * interface file instead. 
 * ----------------------------------------------------------------------------- */

/*
  +----------------------------------------------------------------------+
  | PHP version 4.0                                                      |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997, 1998, 1999, 2000, 2001 The PHP Group             |
  +----------------------------------------------------------------------+
  | This source file is subject to version 2.02 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available at through the world-wide-web at                           |
  | http://www.php.net/license/2_02.txt.                                 |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Authors:                                                             |
  |                                                                      |
  +----------------------------------------------------------------------+
 */


#ifndef PHP_OTAPI_H
#define PHP_OTAPI_H

extern zend_module_entry otapi_module_entry;
#define phpext_otapi_ptr &otapi_module_entry

#ifdef PHP_WIN32
# define PHP_OTAPI_API __declspec(dllexport)
#else
# define PHP_OTAPI_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(otapi);
PHP_MSHUTDOWN_FUNCTION(otapi);
PHP_RINIT_FUNCTION(otapi);
PHP_RSHUTDOWN_FUNCTION(otapi);
PHP_MINFO_FUNCTION(otapi);

ZEND_NAMED_FUNCTION(_wrap_OT_API_Init);
ZEND_NAMED_FUNCTION(_wrap_OT_API_LoadWallet);
ZEND_NAMED_FUNCTION(_wrap_OT_API_GetServerCount);
ZEND_NAMED_FUNCTION(_wrap_OT_API_GetAssetTypeCount);
ZEND_NAMED_FUNCTION(_wrap_OT_API_GetAccountCount);
ZEND_NAMED_FUNCTION(_wrap_OT_API_GetNymCount);
ZEND_NAMED_FUNCTION(_wrap_OT_API_GetServer_ID);
ZEND_NAMED_FUNCTION(_wrap_OT_API_GetServer_Name);
ZEND_NAMED_FUNCTION(_wrap_OT_API_GetAssetType_ID);
ZEND_NAMED_FUNCTION(_wrap_OT_API_GetAssetType_Name);
ZEND_NAMED_FUNCTION(_wrap_OT_API_GetAccountWallet_ID);
ZEND_NAMED_FUNCTION(_wrap_OT_API_GetAccountWallet_Name);
ZEND_NAMED_FUNCTION(_wrap_OT_API_GetAccountWallet_Balance);
ZEND_NAMED_FUNCTION(_wrap_OT_API_GetAccountWallet_Type);
ZEND_NAMED_FUNCTION(_wrap_OT_API_GetAccountWallet_AssetTypeID);
ZEND_NAMED_FUNCTION(_wrap_OT_API_SetAccountWallet_Name);
ZEND_NAMED_FUNCTION(_wrap_OT_API_GetNym_TransactionNumCount);
ZEND_NAMED_FUNCTION(_wrap_OT_API_GetNym_ID);
ZEND_NAMED_FUNCTION(_wrap_OT_API_GetNym_Name);
ZEND_NAMED_FUNCTION(_wrap_OT_API_SetNym_Name);
ZEND_NAMED_FUNCTION(_wrap_OT_API_VerifyAndRetrieveXMLContents);
ZEND_NAMED_FUNCTION(_wrap_OT_API_WriteCheque);
ZEND_NAMED_FUNCTION(_wrap_OT_API_WritePaymentPlan);
ZEND_NAMED_FUNCTION(_wrap_OT_API_LoadUserPubkey);
ZEND_NAMED_FUNCTION(_wrap_OT_API_LoadPubkey);
ZEND_NAMED_FUNCTION(_wrap_OT_API_VerifyUserPrivateKey);
ZEND_NAMED_FUNCTION(_wrap_OT_API_LoadPurse);
ZEND_NAMED_FUNCTION(_wrap_OT_API_LoadMint);
ZEND_NAMED_FUNCTION(_wrap_OT_API_LoadAssetContract);
ZEND_NAMED_FUNCTION(_wrap_OT_API_IsBasketCurrency);
ZEND_NAMED_FUNCTION(_wrap_OT_API_Basket_GetMemberCount);
ZEND_NAMED_FUNCTION(_wrap_OT_API_Basket_GetMemberType);
ZEND_NAMED_FUNCTION(_wrap_OT_API_Basket_GetMinimumTransferAmount);
ZEND_NAMED_FUNCTION(_wrap_OT_API_Basket_GetMemberMinimumTransferAmount);
ZEND_NAMED_FUNCTION(_wrap_OT_API_LoadAssetAccount);
ZEND_NAMED_FUNCTION(_wrap_OT_API_LoadInbox);
ZEND_NAMED_FUNCTION(_wrap_OT_API_LoadOutbox);
ZEND_NAMED_FUNCTION(_wrap_OT_API_Ledger_GetCount);
ZEND_NAMED_FUNCTION(_wrap_OT_API_Ledger_CreateResponse);
ZEND_NAMED_FUNCTION(_wrap_OT_API_Ledger_GetTransactionByIndex);
ZEND_NAMED_FUNCTION(_wrap_OT_API_Ledger_GetTransactionByID);
ZEND_NAMED_FUNCTION(_wrap_OT_API_Ledger_GetTransactionIDByIndex);
ZEND_NAMED_FUNCTION(_wrap_OT_API_Ledger_AddTransaction);
ZEND_NAMED_FUNCTION(_wrap_OT_API_Transaction_CreateResponse);
ZEND_NAMED_FUNCTION(_wrap_OT_API_Transaction_GetType);
ZEND_NAMED_FUNCTION(_wrap_OT_API_Transaction_GetVoucher);
ZEND_NAMED_FUNCTION(_wrap_OT_API_Transaction_GetSuccess);
ZEND_NAMED_FUNCTION(_wrap_OT_API_Purse_GetTotalValue);
ZEND_NAMED_FUNCTION(_wrap_OT_API_checkServerID);
ZEND_NAMED_FUNCTION(_wrap_OT_API_createUserAccount);
ZEND_NAMED_FUNCTION(_wrap_OT_API_checkUser);
ZEND_NAMED_FUNCTION(_wrap_OT_API_getRequest);
ZEND_NAMED_FUNCTION(_wrap_OT_API_getTransactionNumber);
ZEND_NAMED_FUNCTION(_wrap_OT_API_issueAssetType);
ZEND_NAMED_FUNCTION(_wrap_OT_API_getContract);
ZEND_NAMED_FUNCTION(_wrap_OT_API_getMint);
ZEND_NAMED_FUNCTION(_wrap_OT_API_createAssetAccount);
ZEND_NAMED_FUNCTION(_wrap_OT_API_getAccount);
ZEND_NAMED_FUNCTION(_wrap_OT_API_GenerateBasketCreation);
ZEND_NAMED_FUNCTION(_wrap_OT_API_AddBasketCreationItem);
ZEND_NAMED_FUNCTION(_wrap_OT_API_issueBasket);
ZEND_NAMED_FUNCTION(_wrap_OT_API_GenerateBasketExchange);
ZEND_NAMED_FUNCTION(_wrap_OT_API_AddBasketExchangeItem);
ZEND_NAMED_FUNCTION(_wrap_OT_API_exchangeBasket);
ZEND_NAMED_FUNCTION(_wrap_OT_API_notarizeWithdrawal);
ZEND_NAMED_FUNCTION(_wrap_OT_API_notarizeDeposit);
ZEND_NAMED_FUNCTION(_wrap_OT_API_notarizeTransfer);
ZEND_NAMED_FUNCTION(_wrap_OT_API_getInbox);
ZEND_NAMED_FUNCTION(_wrap_OT_API_processInbox);
ZEND_NAMED_FUNCTION(_wrap_OT_API_withdrawVoucher);
ZEND_NAMED_FUNCTION(_wrap_OT_API_depositCheque);
ZEND_NAMED_FUNCTION(_wrap_OT_API_depositPaymentPlan);
ZEND_NAMED_FUNCTION(_wrap_OT_API_issueMarketOffer);
ZEND_NAMED_FUNCTION(_wrap_OT_API_PopMessageBuffer);
ZEND_NAMED_FUNCTION(_wrap_OT_API_FlushMessageBuffer);
ZEND_NAMED_FUNCTION(_wrap_OT_API_Message_GetCommand);
ZEND_NAMED_FUNCTION(_wrap_OT_API_Message_GetSuccess);
ZEND_NAMED_FUNCTION(_wrap_OT_API_Message_GetLedger);
ZEND_NAMED_FUNCTION(_wrap_OT_API_Message_GetNewAssetTypeID);
ZEND_NAMED_FUNCTION(_wrap_OT_API_ConnectServer);
ZEND_NAMED_FUNCTION(_wrap_OT_API_ProcessSockets);
#endif /* PHP_OTAPI_H */
