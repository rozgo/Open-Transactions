# This file was automatically generated by SWIG (http://www.swig.org).
# Version 1.3.31
#
# Don't modify this file, modify the SWIG interface instead.
# This file is compatible with both classic and new-style classes.

import _otapi
import new
new_instancemethod = new.instancemethod
try:
    _swig_property = property
except NameError:
    pass # Python < 2.2 doesn't have 'property'.
def _swig_setattr_nondynamic(self,class_type,name,value,static=1):
    if (name == "thisown"): return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'PySwigObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    if (not static) or hasattr(self,name):
        self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)

def _swig_setattr(self,class_type,name,value):
    return _swig_setattr_nondynamic(self,class_type,name,value,0)

def _swig_getattr(self,class_type,name):
    if (name == "thisown"): return self.this.own()
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError,name

def _swig_repr(self):
    try: strthis = "proxy of " + self.this.__repr__()
    except: strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

import types
try:
    _object = types.ObjectType
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0
del types


OT_API_Init = _otapi.OT_API_Init
OT_API_LoadWallet = _otapi.OT_API_LoadWallet
OT_API_SwitchWallet = _otapi.OT_API_SwitchWallet
OT_API_GetMemlogSize = _otapi.OT_API_GetMemlogSize
OT_API_GetMemlogAtIndex = _otapi.OT_API_GetMemlogAtIndex
OT_API_PeekMemlogFront = _otapi.OT_API_PeekMemlogFront
OT_API_PeekMemlogBack = _otapi.OT_API_PeekMemlogBack
OT_API_PopMemlogFront = _otapi.OT_API_PopMemlogFront
OT_API_PopMemlogBack = _otapi.OT_API_PopMemlogBack
OT_API_CreateNym = _otapi.OT_API_CreateNym
OT_API_AddServerContract = _otapi.OT_API_AddServerContract
OT_API_AddAssetContract = _otapi.OT_API_AddAssetContract
OT_API_GetServerCount = _otapi.OT_API_GetServerCount
OT_API_GetAssetTypeCount = _otapi.OT_API_GetAssetTypeCount
OT_API_GetAccountCount = _otapi.OT_API_GetAccountCount
OT_API_GetNymCount = _otapi.OT_API_GetNymCount
OT_API_GetServer_ID = _otapi.OT_API_GetServer_ID
OT_API_GetServer_Name = _otapi.OT_API_GetServer_Name
OT_API_GetAssetType_ID = _otapi.OT_API_GetAssetType_ID
OT_API_GetAssetType_Name = _otapi.OT_API_GetAssetType_Name
OT_API_GetAccountWallet_ID = _otapi.OT_API_GetAccountWallet_ID
OT_API_GetAccountWallet_Name = _otapi.OT_API_GetAccountWallet_Name
OT_API_GetAccountWallet_Balance = _otapi.OT_API_GetAccountWallet_Balance
OT_API_GetAccountWallet_Type = _otapi.OT_API_GetAccountWallet_Type
OT_API_GetAccountWallet_AssetTypeID = _otapi.OT_API_GetAccountWallet_AssetTypeID
OT_API_GetAccountWallet_ServerID = _otapi.OT_API_GetAccountWallet_ServerID
OT_API_GetAccountWallet_NymID = _otapi.OT_API_GetAccountWallet_NymID
OT_API_GetNym_TransactionNumCount = _otapi.OT_API_GetNym_TransactionNumCount
OT_API_GetNym_ID = _otapi.OT_API_GetNym_ID
OT_API_GetNym_Name = _otapi.OT_API_GetNym_Name
OT_API_GetNym_Stats = _otapi.OT_API_GetNym_Stats
OT_API_IsNym_RegisteredAtServer = _otapi.OT_API_IsNym_RegisteredAtServer
OT_API_GetNym_MailCount = _otapi.OT_API_GetNym_MailCount
OT_API_GetNym_MailContentsByIndex = _otapi.OT_API_GetNym_MailContentsByIndex
OT_API_GetNym_MailSenderIDByIndex = _otapi.OT_API_GetNym_MailSenderIDByIndex
OT_API_GetNym_MailServerIDByIndex = _otapi.OT_API_GetNym_MailServerIDByIndex
OT_API_Nym_RemoveMailByIndex = _otapi.OT_API_Nym_RemoveMailByIndex
OT_API_Nym_VerifyMailByIndex = _otapi.OT_API_Nym_VerifyMailByIndex
OT_API_GetNym_OutmailCount = _otapi.OT_API_GetNym_OutmailCount
OT_API_GetNym_OutmailContentsByIndex = _otapi.OT_API_GetNym_OutmailContentsByIndex
OT_API_GetNym_OutmailRecipientIDByIndex = _otapi.OT_API_GetNym_OutmailRecipientIDByIndex
OT_API_GetNym_OutmailServerIDByIndex = _otapi.OT_API_GetNym_OutmailServerIDByIndex
OT_API_Nym_RemoveOutmailByIndex = _otapi.OT_API_Nym_RemoveOutmailByIndex
OT_API_Nym_VerifyOutmailByIndex = _otapi.OT_API_Nym_VerifyOutmailByIndex
OT_API_Wallet_CanRemoveServer = _otapi.OT_API_Wallet_CanRemoveServer
OT_API_Wallet_RemoveServer = _otapi.OT_API_Wallet_RemoveServer
OT_API_Wallet_CanRemoveAssetType = _otapi.OT_API_Wallet_CanRemoveAssetType
OT_API_Wallet_RemoveAssetType = _otapi.OT_API_Wallet_RemoveAssetType
OT_API_Wallet_CanRemoveNym = _otapi.OT_API_Wallet_CanRemoveNym
OT_API_Wallet_RemoveNym = _otapi.OT_API_Wallet_RemoveNym
OT_API_Wallet_CanRemoveAccount = _otapi.OT_API_Wallet_CanRemoveAccount
OT_API_Wallet_RemoveAccount = _otapi.OT_API_Wallet_RemoveAccount
OT_API_SetNym_Name = _otapi.OT_API_SetNym_Name
OT_API_SetAccountWallet_Name = _otapi.OT_API_SetAccountWallet_Name
OT_API_SetAssetType_Name = _otapi.OT_API_SetAssetType_Name
OT_API_SetServer_Name = _otapi.OT_API_SetServer_Name
OT_API_VerifyAndRetrieveXMLContents = _otapi.OT_API_VerifyAndRetrieveXMLContents
OT_API_WriteCheque = _otapi.OT_API_WriteCheque
OT_API_WritePaymentPlan = _otapi.OT_API_WritePaymentPlan
OT_API_LoadUserPubkey = _otapi.OT_API_LoadUserPubkey
OT_API_LoadPubkey = _otapi.OT_API_LoadPubkey
OT_API_VerifyUserPrivateKey = _otapi.OT_API_VerifyUserPrivateKey
OT_API_LoadPurse = _otapi.OT_API_LoadPurse
OT_API_LoadMint = _otapi.OT_API_LoadMint
OT_API_LoadAssetContract = _otapi.OT_API_LoadAssetContract
OT_API_LoadServerContract = _otapi.OT_API_LoadServerContract
OT_API_IsBasketCurrency = _otapi.OT_API_IsBasketCurrency
OT_API_Basket_GetMemberCount = _otapi.OT_API_Basket_GetMemberCount
OT_API_Basket_GetMemberType = _otapi.OT_API_Basket_GetMemberType
OT_API_Basket_GetMinimumTransferAmount = _otapi.OT_API_Basket_GetMinimumTransferAmount
OT_API_Basket_GetMemberMinimumTransferAmount = _otapi.OT_API_Basket_GetMemberMinimumTransferAmount
OT_API_LoadAssetAccount = _otapi.OT_API_LoadAssetAccount
OT_API_LoadInbox = _otapi.OT_API_LoadInbox
OT_API_LoadOutbox = _otapi.OT_API_LoadOutbox
OT_API_Ledger_GetCount = _otapi.OT_API_Ledger_GetCount
OT_API_Ledger_CreateResponse = _otapi.OT_API_Ledger_CreateResponse
OT_API_Ledger_GetTransactionByIndex = _otapi.OT_API_Ledger_GetTransactionByIndex
OT_API_Ledger_GetTransactionByID = _otapi.OT_API_Ledger_GetTransactionByID
OT_API_Ledger_GetTransactionIDByIndex = _otapi.OT_API_Ledger_GetTransactionIDByIndex
OT_API_Ledger_AddTransaction = _otapi.OT_API_Ledger_AddTransaction
OT_API_Transaction_CreateResponse = _otapi.OT_API_Transaction_CreateResponse
OT_API_Ledger_FinalizeResponse = _otapi.OT_API_Ledger_FinalizeResponse
OT_API_Transaction_GetType = _otapi.OT_API_Transaction_GetType
OT_API_Transaction_GetVoucher = _otapi.OT_API_Transaction_GetVoucher
OT_API_Transaction_GetSuccess = _otapi.OT_API_Transaction_GetSuccess
OT_API_Transaction_GetDateSigned = _otapi.OT_API_Transaction_GetDateSigned
OT_API_Transaction_GetAmount = _otapi.OT_API_Transaction_GetAmount
OT_API_Pending_GetNote = _otapi.OT_API_Pending_GetNote
OT_API_Transaction_GetSenderUserID = _otapi.OT_API_Transaction_GetSenderUserID
OT_API_Transaction_GetSenderAcctID = _otapi.OT_API_Transaction_GetSenderAcctID
OT_API_Transaction_GetRecipientUserID = _otapi.OT_API_Transaction_GetRecipientUserID
OT_API_Transaction_GetRecipientAcctID = _otapi.OT_API_Transaction_GetRecipientAcctID
OT_API_Transaction_GetDisplayReferenceToNum = _otapi.OT_API_Transaction_GetDisplayReferenceToNum
OT_API_CreatePurse = _otapi.OT_API_CreatePurse
OT_API_SavePurse = _otapi.OT_API_SavePurse
OT_API_Purse_GetTotalValue = _otapi.OT_API_Purse_GetTotalValue
OT_API_Purse_Count = _otapi.OT_API_Purse_Count
OT_API_Purse_Peek = _otapi.OT_API_Purse_Peek
OT_API_Purse_Pop = _otapi.OT_API_Purse_Pop
OT_API_Purse_Push = _otapi.OT_API_Purse_Push
OT_API_Wallet_ImportPurse = _otapi.OT_API_Wallet_ImportPurse
OT_API_exchangePurse = _otapi.OT_API_exchangePurse
OT_API_Token_GetID = _otapi.OT_API_Token_GetID
OT_API_Token_GetDenomination = _otapi.OT_API_Token_GetDenomination
OT_API_Token_GetSeries = _otapi.OT_API_Token_GetSeries
OT_API_Token_GetValidFrom = _otapi.OT_API_Token_GetValidFrom
OT_API_Token_GetValidTo = _otapi.OT_API_Token_GetValidTo
OT_API_Token_GetAssetID = _otapi.OT_API_Token_GetAssetID
OT_API_Token_GetServerID = _otapi.OT_API_Token_GetServerID
OT_API_checkServerID = _otapi.OT_API_checkServerID
OT_API_createUserAccount = _otapi.OT_API_createUserAccount
OT_API_checkUser = _otapi.OT_API_checkUser
OT_API_sendUserMessage = _otapi.OT_API_sendUserMessage
OT_API_getRequest = _otapi.OT_API_getRequest
OT_API_getTransactionNumber = _otapi.OT_API_getTransactionNumber
OT_API_issueAssetType = _otapi.OT_API_issueAssetType
OT_API_getContract = _otapi.OT_API_getContract
OT_API_getMint = _otapi.OT_API_getMint
OT_API_createAssetAccount = _otapi.OT_API_createAssetAccount
OT_API_getAccount = _otapi.OT_API_getAccount
OT_API_GenerateBasketCreation = _otapi.OT_API_GenerateBasketCreation
OT_API_AddBasketCreationItem = _otapi.OT_API_AddBasketCreationItem
OT_API_issueBasket = _otapi.OT_API_issueBasket
OT_API_GenerateBasketExchange = _otapi.OT_API_GenerateBasketExchange
OT_API_AddBasketExchangeItem = _otapi.OT_API_AddBasketExchangeItem
OT_API_exchangeBasket = _otapi.OT_API_exchangeBasket
OT_API_notarizeWithdrawal = _otapi.OT_API_notarizeWithdrawal
OT_API_notarizeDeposit = _otapi.OT_API_notarizeDeposit
OT_API_notarizeTransfer = _otapi.OT_API_notarizeTransfer
OT_API_getInbox = _otapi.OT_API_getInbox
OT_API_getOutbox = _otapi.OT_API_getOutbox
OT_API_getNymbox = _otapi.OT_API_getNymbox
OT_API_LoadNymbox = _otapi.OT_API_LoadNymbox
OT_API_processInbox = _otapi.OT_API_processInbox
OT_API_processNymbox = _otapi.OT_API_processNymbox
OT_API_withdrawVoucher = _otapi.OT_API_withdrawVoucher
OT_API_depositCheque = _otapi.OT_API_depositCheque
OT_API_depositPaymentPlan = _otapi.OT_API_depositPaymentPlan
OT_API_issueMarketOffer = _otapi.OT_API_issueMarketOffer
OT_API_PopMessageBuffer = _otapi.OT_API_PopMessageBuffer
OT_API_FlushMessageBuffer = _otapi.OT_API_FlushMessageBuffer
OT_API_Message_GetCommand = _otapi.OT_API_Message_GetCommand
OT_API_Message_GetSuccess = _otapi.OT_API_Message_GetSuccess
OT_API_Message_GetTransactionSuccess = _otapi.OT_API_Message_GetTransactionSuccess
OT_API_Message_GetLedger = _otapi.OT_API_Message_GetLedger
OT_API_Message_GetNewAssetTypeID = _otapi.OT_API_Message_GetNewAssetTypeID
OT_API_Message_GetNewIssuerAcctID = _otapi.OT_API_Message_GetNewIssuerAcctID
OT_API_Message_GetNewAcctID = _otapi.OT_API_Message_GetNewAcctID
OT_API_ConnectServer = _otapi.OT_API_ConnectServer
OT_API_ProcessSockets = _otapi.OT_API_ProcessSockets


