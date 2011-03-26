/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


public class otapi {
  public static int OT_API_Init(String szClientPath) {
    return otapiJNI.OT_API_Init(szClientPath);
  }

  public static int OT_API_LoadWallet(String szPath) {
    return otapiJNI.OT_API_LoadWallet(szPath);
  }

  public static String OT_API_CreateNym() {
    return otapiJNI.OT_API_CreateNym();
  }

  public static int OT_API_AddServerContract(String szContract) {
    return otapiJNI.OT_API_AddServerContract(szContract);
  }

  public static int OT_API_AddAssetContract(String szContract) {
    return otapiJNI.OT_API_AddAssetContract(szContract);
  }

  public static int OT_API_GetServerCount() {
    return otapiJNI.OT_API_GetServerCount();
  }

  public static int OT_API_GetAssetTypeCount() {
    return otapiJNI.OT_API_GetAssetTypeCount();
  }

  public static int OT_API_GetAccountCount() {
    return otapiJNI.OT_API_GetAccountCount();
  }

  public static int OT_API_GetNymCount() {
    return otapiJNI.OT_API_GetNymCount();
  }

  public static String OT_API_GetServer_ID(int nIndex) {
    return otapiJNI.OT_API_GetServer_ID(nIndex);
  }

  public static String OT_API_GetServer_Name(String SERVER_ID) {
    return otapiJNI.OT_API_GetServer_Name(SERVER_ID);
  }

  public static String OT_API_GetAssetType_ID(int nIndex) {
    return otapiJNI.OT_API_GetAssetType_ID(nIndex);
  }

  public static String OT_API_GetAssetType_Name(String ASSET_TYPE_ID) {
    return otapiJNI.OT_API_GetAssetType_Name(ASSET_TYPE_ID);
  }

  public static String OT_API_GetAccountWallet_ID(int nIndex) {
    return otapiJNI.OT_API_GetAccountWallet_ID(nIndex);
  }

  public static String OT_API_GetAccountWallet_Name(String ACCOUNT_ID) {
    return otapiJNI.OT_API_GetAccountWallet_Name(ACCOUNT_ID);
  }

  public static String OT_API_GetAccountWallet_Balance(String ACCOUNT_ID) {
    return otapiJNI.OT_API_GetAccountWallet_Balance(ACCOUNT_ID);
  }

  public static String OT_API_GetAccountWallet_Type(String ACCOUNT_ID) {
    return otapiJNI.OT_API_GetAccountWallet_Type(ACCOUNT_ID);
  }

  public static String OT_API_GetAccountWallet_AssetTypeID(String ACCOUNT_ID) {
    return otapiJNI.OT_API_GetAccountWallet_AssetTypeID(ACCOUNT_ID);
  }

  public static String OT_API_GetAccountWallet_ServerID(String ACCOUNT_ID) {
    return otapiJNI.OT_API_GetAccountWallet_ServerID(ACCOUNT_ID);
  }

  public static String OT_API_GetAccountWallet_NymID(String ACCOUNT_ID) {
    return otapiJNI.OT_API_GetAccountWallet_NymID(ACCOUNT_ID);
  }

  public static int OT_API_GetNym_TransactionNumCount(String SERVER_ID, String NYM_ID) {
    return otapiJNI.OT_API_GetNym_TransactionNumCount(SERVER_ID, NYM_ID);
  }

  public static String OT_API_GetNym_ID(int nIndex) {
    return otapiJNI.OT_API_GetNym_ID(nIndex);
  }

  public static String OT_API_GetNym_Name(String NYM_ID) {
    return otapiJNI.OT_API_GetNym_Name(NYM_ID);
  }

  public static String OT_API_GetNym_Stats(String NYM_ID) {
    return otapiJNI.OT_API_GetNym_Stats(NYM_ID);
  }

  public static int OT_API_IsNym_RegisteredAtServer(String NYM_ID, String SERVER_ID) {
    return otapiJNI.OT_API_IsNym_RegisteredAtServer(NYM_ID, SERVER_ID);
  }

  public static int OT_API_GetNym_MailCount(String NYM_ID) {
    return otapiJNI.OT_API_GetNym_MailCount(NYM_ID);
  }

  public static String OT_API_GetNym_MailContentsByIndex(String NYM_ID, int nIndex) {
    return otapiJNI.OT_API_GetNym_MailContentsByIndex(NYM_ID, nIndex);
  }

  public static String OT_API_GetNym_MailSenderIDByIndex(String NYM_ID, int nIndex) {
    return otapiJNI.OT_API_GetNym_MailSenderIDByIndex(NYM_ID, nIndex);
  }

  public static String OT_API_GetNym_MailServerIDByIndex(String NYM_ID, int nIndex) {
    return otapiJNI.OT_API_GetNym_MailServerIDByIndex(NYM_ID, nIndex);
  }

  public static int OT_API_Nym_RemoveMailByIndex(String NYM_ID, int nIndex) {
    return otapiJNI.OT_API_Nym_RemoveMailByIndex(NYM_ID, nIndex);
  }

  public static int OT_API_Nym_VerifyMailByIndex(String NYM_ID, int nIndex) {
    return otapiJNI.OT_API_Nym_VerifyMailByIndex(NYM_ID, nIndex);
  }

  public static int OT_API_SetNym_Name(String NYM_ID, String SIGNER_NYM_ID, String NYM_NEW_NAME) {
    return otapiJNI.OT_API_SetNym_Name(NYM_ID, SIGNER_NYM_ID, NYM_NEW_NAME);
  }

  public static int OT_API_SetAccountWallet_Name(String ACCT_ID, String SIGNER_NYM_ID, String ACCT_NEW_NAME) {
    return otapiJNI.OT_API_SetAccountWallet_Name(ACCT_ID, SIGNER_NYM_ID, ACCT_NEW_NAME);
  }

  public static int OT_API_SetAssetType_Name(String ASSET_ID, String STR_NEW_NAME) {
    return otapiJNI.OT_API_SetAssetType_Name(ASSET_ID, STR_NEW_NAME);
  }

  public static int OT_API_SetServer_Name(String SERVER_ID, String STR_NEW_NAME) {
    return otapiJNI.OT_API_SetServer_Name(SERVER_ID, STR_NEW_NAME);
  }

  public static String OT_API_VerifyAndRetrieveXMLContents(String THE_CONTRACT, String USER_ID) {
    return otapiJNI.OT_API_VerifyAndRetrieveXMLContents(THE_CONTRACT, USER_ID);
  }

  public static String OT_API_WriteCheque(String SERVER_ID, String CHEQUE_AMOUNT, String VALID_FROM, String VALID_TO, String SENDER_ACCT_ID, String SENDER_USER_ID, String CHEQUE_MEMO, String RECIPIENT_USER_ID) {
    return otapiJNI.OT_API_WriteCheque(SERVER_ID, CHEQUE_AMOUNT, VALID_FROM, VALID_TO, SENDER_ACCT_ID, SENDER_USER_ID, CHEQUE_MEMO, RECIPIENT_USER_ID);
  }

  public static String OT_API_WritePaymentPlan(String SERVER_ID, String VALID_FROM, String VALID_TO, String SENDER_ACCT_ID, String SENDER_USER_ID, String PLAN_CONSIDERATION, String RECIPIENT_ACCT_ID, String RECIPIENT_USER_ID, String INITIAL_PAYMENT_AMOUNT, String INITIAL_PAYMENT_DELAY, String PAYMENT_PLAN_AMOUNT, String PAYMENT_PLAN_DELAY, String PAYMENT_PLAN_PERIOD, String PAYMENT_PLAN_LENGTH, String PAYMENT_PLAN_MAX_PAYMENTS) {
    return otapiJNI.OT_API_WritePaymentPlan(SERVER_ID, VALID_FROM, VALID_TO, SENDER_ACCT_ID, SENDER_USER_ID, PLAN_CONSIDERATION, RECIPIENT_ACCT_ID, RECIPIENT_USER_ID, INITIAL_PAYMENT_AMOUNT, INITIAL_PAYMENT_DELAY, PAYMENT_PLAN_AMOUNT, PAYMENT_PLAN_DELAY, PAYMENT_PLAN_PERIOD, PAYMENT_PLAN_LENGTH, PAYMENT_PLAN_MAX_PAYMENTS);
  }

  public static String OT_API_LoadUserPubkey(String USER_ID) {
    return otapiJNI.OT_API_LoadUserPubkey(USER_ID);
  }

  public static String OT_API_LoadPubkey(String USER_ID) {
    return otapiJNI.OT_API_LoadPubkey(USER_ID);
  }

  public static int OT_API_VerifyUserPrivateKey(String USER_ID) {
    return otapiJNI.OT_API_VerifyUserPrivateKey(USER_ID);
  }

  public static String OT_API_LoadPurse(String SERVER_ID, String ASSET_TYPE_ID, String USER_ID) {
    return otapiJNI.OT_API_LoadPurse(SERVER_ID, ASSET_TYPE_ID, USER_ID);
  }

  public static String OT_API_LoadMint(String SERVER_ID, String ASSET_TYPE_ID) {
    return otapiJNI.OT_API_LoadMint(SERVER_ID, ASSET_TYPE_ID);
  }

  public static String OT_API_LoadAssetContract(String ASSET_TYPE_ID) {
    return otapiJNI.OT_API_LoadAssetContract(ASSET_TYPE_ID);
  }

  public static String OT_API_LoadServerContract(String SERVER_ID) {
    return otapiJNI.OT_API_LoadServerContract(SERVER_ID);
  }

  public static int OT_API_IsBasketCurrency(String ASSET_TYPE_ID) {
    return otapiJNI.OT_API_IsBasketCurrency(ASSET_TYPE_ID);
  }

  public static int OT_API_Basket_GetMemberCount(String BASKET_ASSET_TYPE_ID) {
    return otapiJNI.OT_API_Basket_GetMemberCount(BASKET_ASSET_TYPE_ID);
  }

  public static String OT_API_Basket_GetMemberType(String BASKET_ASSET_TYPE_ID, int nIndex) {
    return otapiJNI.OT_API_Basket_GetMemberType(BASKET_ASSET_TYPE_ID, nIndex);
  }

  public static String OT_API_Basket_GetMinimumTransferAmount(String BASKET_ASSET_TYPE_ID) {
    return otapiJNI.OT_API_Basket_GetMinimumTransferAmount(BASKET_ASSET_TYPE_ID);
  }

  public static String OT_API_Basket_GetMemberMinimumTransferAmount(String BASKET_ASSET_TYPE_ID, int nIndex) {
    return otapiJNI.OT_API_Basket_GetMemberMinimumTransferAmount(BASKET_ASSET_TYPE_ID, nIndex);
  }

  public static String OT_API_LoadAssetAccount(String SERVER_ID, String USER_ID, String ACCOUNT_ID) {
    return otapiJNI.OT_API_LoadAssetAccount(SERVER_ID, USER_ID, ACCOUNT_ID);
  }

  public static String OT_API_LoadInbox(String SERVER_ID, String USER_ID, String ACCOUNT_ID) {
    return otapiJNI.OT_API_LoadInbox(SERVER_ID, USER_ID, ACCOUNT_ID);
  }

  public static String OT_API_LoadOutbox(String SERVER_ID, String USER_ID, String ACCOUNT_ID) {
    return otapiJNI.OT_API_LoadOutbox(SERVER_ID, USER_ID, ACCOUNT_ID);
  }

  public static int OT_API_Ledger_GetCount(String SERVER_ID, String USER_ID, String ACCOUNT_ID, String THE_LEDGER) {
    return otapiJNI.OT_API_Ledger_GetCount(SERVER_ID, USER_ID, ACCOUNT_ID, THE_LEDGER);
  }

  public static String OT_API_Ledger_CreateResponse(String SERVER_ID, String USER_ID, String ACCOUNT_ID, String ORIGINAL_LEDGER) {
    return otapiJNI.OT_API_Ledger_CreateResponse(SERVER_ID, USER_ID, ACCOUNT_ID, ORIGINAL_LEDGER);
  }

  public static String OT_API_Ledger_GetTransactionByIndex(String SERVER_ID, String USER_ID, String ACCOUNT_ID, String THE_LEDGER, int nIndex) {
    return otapiJNI.OT_API_Ledger_GetTransactionByIndex(SERVER_ID, USER_ID, ACCOUNT_ID, THE_LEDGER, nIndex);
  }

  public static String OT_API_Ledger_GetTransactionByID(String SERVER_ID, String USER_ID, String ACCOUNT_ID, String THE_LEDGER, String TRANSACTION_NUMBER) {
    return otapiJNI.OT_API_Ledger_GetTransactionByID(SERVER_ID, USER_ID, ACCOUNT_ID, THE_LEDGER, TRANSACTION_NUMBER);
  }

  public static String OT_API_Ledger_GetTransactionIDByIndex(String SERVER_ID, String USER_ID, String ACCOUNT_ID, String THE_LEDGER, int nIndex) {
    return otapiJNI.OT_API_Ledger_GetTransactionIDByIndex(SERVER_ID, USER_ID, ACCOUNT_ID, THE_LEDGER, nIndex);
  }

  public static String OT_API_Ledger_AddTransaction(String SERVER_ID, String USER_ID, String ACCOUNT_ID, String THE_LEDGER, String THE_TRANSACTION) {
    return otapiJNI.OT_API_Ledger_AddTransaction(SERVER_ID, USER_ID, ACCOUNT_ID, THE_LEDGER, THE_TRANSACTION);
  }

  public static String OT_API_Transaction_CreateResponse(String SERVER_ID, String USER_ID, String ACCOUNT_ID, String RESPONSE_LEDGER, String ORIGINAL_TRANSACTION, int BOOL_DO_I_ACCEPT) {
    return otapiJNI.OT_API_Transaction_CreateResponse(SERVER_ID, USER_ID, ACCOUNT_ID, RESPONSE_LEDGER, ORIGINAL_TRANSACTION, BOOL_DO_I_ACCEPT);
  }

  public static String OT_API_Ledger_FinalizeResponse(String SERVER_ID, String USER_ID, String ACCOUNT_ID, String THE_LEDGER, int BOOL_DO_I_ACCEPT) {
    return otapiJNI.OT_API_Ledger_FinalizeResponse(SERVER_ID, USER_ID, ACCOUNT_ID, THE_LEDGER, BOOL_DO_I_ACCEPT);
  }

  public static String OT_API_Transaction_GetType(String SERVER_ID, String USER_ID, String ACCOUNT_ID, String THE_TRANSACTION) {
    return otapiJNI.OT_API_Transaction_GetType(SERVER_ID, USER_ID, ACCOUNT_ID, THE_TRANSACTION);
  }

  public static String OT_API_Transaction_GetVoucher(String SERVER_ID, String USER_ID, String ACCOUNT_ID, String THE_TRANSACTION) {
    return otapiJNI.OT_API_Transaction_GetVoucher(SERVER_ID, USER_ID, ACCOUNT_ID, THE_TRANSACTION);
  }

  public static int OT_API_Transaction_GetSuccess(String SERVER_ID, String USER_ID, String ACCOUNT_ID, String THE_TRANSACTION) {
    return otapiJNI.OT_API_Transaction_GetSuccess(SERVER_ID, USER_ID, ACCOUNT_ID, THE_TRANSACTION);
  }

  public static String OT_API_Transaction_GetDateSigned(String SERVER_ID, String USER_ID, String ACCOUNT_ID, String THE_TRANSACTION) {
    return otapiJNI.OT_API_Transaction_GetDateSigned(SERVER_ID, USER_ID, ACCOUNT_ID, THE_TRANSACTION);
  }

  public static String OT_API_Transaction_GetAmount(String SERVER_ID, String USER_ID, String ACCOUNT_ID, String THE_TRANSACTION) {
    return otapiJNI.OT_API_Transaction_GetAmount(SERVER_ID, USER_ID, ACCOUNT_ID, THE_TRANSACTION);
  }

  public static String OT_API_Pending_GetNote(String SERVER_ID, String USER_ID, String ACCOUNT_ID, String THE_TRANSACTION) {
    return otapiJNI.OT_API_Pending_GetNote(SERVER_ID, USER_ID, ACCOUNT_ID, THE_TRANSACTION);
  }

  public static String OT_API_Transaction_GetSenderUserID(String SERVER_ID, String USER_ID, String ACCOUNT_ID, String THE_TRANSACTION) {
    return otapiJNI.OT_API_Transaction_GetSenderUserID(SERVER_ID, USER_ID, ACCOUNT_ID, THE_TRANSACTION);
  }

  public static String OT_API_Transaction_GetSenderAcctID(String SERVER_ID, String USER_ID, String ACCOUNT_ID, String THE_TRANSACTION) {
    return otapiJNI.OT_API_Transaction_GetSenderAcctID(SERVER_ID, USER_ID, ACCOUNT_ID, THE_TRANSACTION);
  }

  public static String OT_API_Transaction_GetRecipientUserID(String SERVER_ID, String USER_ID, String ACCOUNT_ID, String THE_TRANSACTION) {
    return otapiJNI.OT_API_Transaction_GetRecipientUserID(SERVER_ID, USER_ID, ACCOUNT_ID, THE_TRANSACTION);
  }

  public static String OT_API_Transaction_GetRecipientAcctID(String SERVER_ID, String USER_ID, String ACCOUNT_ID, String THE_TRANSACTION) {
    return otapiJNI.OT_API_Transaction_GetRecipientAcctID(SERVER_ID, USER_ID, ACCOUNT_ID, THE_TRANSACTION);
  }

  public static String OT_API_Transaction_GetDisplayReferenceToNum(String SERVER_ID, String USER_ID, String ACCOUNT_ID, String THE_TRANSACTION) {
    return otapiJNI.OT_API_Transaction_GetDisplayReferenceToNum(SERVER_ID, USER_ID, ACCOUNT_ID, THE_TRANSACTION);
  }

  public static String OT_API_Purse_GetTotalValue(String SERVER_ID, String ASSET_TYPE_ID, String THE_PURSE) {
    return otapiJNI.OT_API_Purse_GetTotalValue(SERVER_ID, ASSET_TYPE_ID, THE_PURSE);
  }

  public static void OT_API_checkServerID(String SERVER_ID, String USER_ID) {
    otapiJNI.OT_API_checkServerID(SERVER_ID, USER_ID);
  }

  public static void OT_API_createUserAccount(String SERVER_ID, String USER_ID) {
    otapiJNI.OT_API_createUserAccount(SERVER_ID, USER_ID);
  }

  public static void OT_API_checkUser(String SERVER_ID, String USER_ID, String USER_ID_CHECK) {
    otapiJNI.OT_API_checkUser(SERVER_ID, USER_ID, USER_ID_CHECK);
  }

  public static void OT_API_sendUserMessage(String SERVER_ID, String USER_ID, String USER_ID_RECIPIENT, String RECIPIENT_PUBKEY, String THE_MESSAGE) {
    otapiJNI.OT_API_sendUserMessage(SERVER_ID, USER_ID, USER_ID_RECIPIENT, RECIPIENT_PUBKEY, THE_MESSAGE);
  }

  public static void OT_API_getRequest(String SERVER_ID, String USER_ID) {
    otapiJNI.OT_API_getRequest(SERVER_ID, USER_ID);
  }

  public static void OT_API_getTransactionNumber(String SERVER_ID, String USER_ID) {
    otapiJNI.OT_API_getTransactionNumber(SERVER_ID, USER_ID);
  }

  public static void OT_API_issueAssetType(String SERVER_ID, String USER_ID, String THE_CONTRACT) {
    otapiJNI.OT_API_issueAssetType(SERVER_ID, USER_ID, THE_CONTRACT);
  }

  public static void OT_API_getContract(String SERVER_ID, String USER_ID, String ASSET_ID) {
    otapiJNI.OT_API_getContract(SERVER_ID, USER_ID, ASSET_ID);
  }

  public static void OT_API_getMint(String SERVER_ID, String USER_ID, String ASSET_ID) {
    otapiJNI.OT_API_getMint(SERVER_ID, USER_ID, ASSET_ID);
  }

  public static void OT_API_createAssetAccount(String SERVER_ID, String USER_ID, String ASSET_ID) {
    otapiJNI.OT_API_createAssetAccount(SERVER_ID, USER_ID, ASSET_ID);
  }

  public static void OT_API_getAccount(String SERVER_ID, String USER_ID, String ACCT_ID) {
    otapiJNI.OT_API_getAccount(SERVER_ID, USER_ID, ACCT_ID);
  }

  public static String OT_API_GenerateBasketCreation(String USER_ID, String MINIMUM_TRANSFER) {
    return otapiJNI.OT_API_GenerateBasketCreation(USER_ID, MINIMUM_TRANSFER);
  }

  public static String OT_API_AddBasketCreationItem(String USER_ID, String THE_BASKET, String ASSET_TYPE_ID, String MINIMUM_TRANSFER) {
    return otapiJNI.OT_API_AddBasketCreationItem(USER_ID, THE_BASKET, ASSET_TYPE_ID, MINIMUM_TRANSFER);
  }

  public static void OT_API_issueBasket(String SERVER_ID, String USER_ID, String THE_BASKET) {
    otapiJNI.OT_API_issueBasket(SERVER_ID, USER_ID, THE_BASKET);
  }

  public static String OT_API_GenerateBasketExchange(String SERVER_ID, String USER_ID, String BASKET_ASSET_TYPE_ID, String BASKET_ASSET_ACCT_ID, int TRANSFER_MULTIPLE) {
    return otapiJNI.OT_API_GenerateBasketExchange(SERVER_ID, USER_ID, BASKET_ASSET_TYPE_ID, BASKET_ASSET_ACCT_ID, TRANSFER_MULTIPLE);
  }

  public static String OT_API_AddBasketExchangeItem(String SERVER_ID, String USER_ID, String THE_BASKET, String ASSET_TYPE_ID, String ASSET_ACCT_ID) {
    return otapiJNI.OT_API_AddBasketExchangeItem(SERVER_ID, USER_ID, THE_BASKET, ASSET_TYPE_ID, ASSET_ACCT_ID);
  }

  public static void OT_API_exchangeBasket(String SERVER_ID, String USER_ID, String BASKET_ASSET_ID, String THE_BASKET, int BOOL_EXCHANGE_IN_OR_OUT) {
    otapiJNI.OT_API_exchangeBasket(SERVER_ID, USER_ID, BASKET_ASSET_ID, THE_BASKET, BOOL_EXCHANGE_IN_OR_OUT);
  }

  public static void OT_API_notarizeWithdrawal(String SERVER_ID, String USER_ID, String ACCT_ID, String AMOUNT) {
    otapiJNI.OT_API_notarizeWithdrawal(SERVER_ID, USER_ID, ACCT_ID, AMOUNT);
  }

  public static void OT_API_notarizeDeposit(String SERVER_ID, String USER_ID, String ACCT_ID, String THE_PURSE) {
    otapiJNI.OT_API_notarizeDeposit(SERVER_ID, USER_ID, ACCT_ID, THE_PURSE);
  }

  public static void OT_API_notarizeTransfer(String SERVER_ID, String USER_ID, String ACCT_FROM, String ACCT_TO, String AMOUNT, String NOTE) {
    otapiJNI.OT_API_notarizeTransfer(SERVER_ID, USER_ID, ACCT_FROM, ACCT_TO, AMOUNT, NOTE);
  }

  public static void OT_API_getInbox(String SERVER_ID, String USER_ID, String ACCT_ID) {
    otapiJNI.OT_API_getInbox(SERVER_ID, USER_ID, ACCT_ID);
  }

  public static void OT_API_getOutbox(String SERVER_ID, String USER_ID, String ACCT_ID) {
    otapiJNI.OT_API_getOutbox(SERVER_ID, USER_ID, ACCT_ID);
  }

  public static void OT_API_getNymbox(String SERVER_ID, String USER_ID) {
    otapiJNI.OT_API_getNymbox(SERVER_ID, USER_ID);
  }

  public static String OT_API_LoadNymbox(String SERVER_ID, String USER_ID) {
    return otapiJNI.OT_API_LoadNymbox(SERVER_ID, USER_ID);
  }

  public static void OT_API_processInbox(String SERVER_ID, String USER_ID, String ACCT_ID, String ACCT_LEDGER) {
    otapiJNI.OT_API_processInbox(SERVER_ID, USER_ID, ACCT_ID, ACCT_LEDGER);
  }

  public static void OT_API_processNymbox(String SERVER_ID, String USER_ID, String ACCT_LEDGER) {
    otapiJNI.OT_API_processNymbox(SERVER_ID, USER_ID, ACCT_LEDGER);
  }

  public static void OT_API_withdrawVoucher(String SERVER_ID, String USER_ID, String ACCT_ID, String RECIPIENT_USER_ID, String CHEQUE_MEMO, String AMOUNT) {
    otapiJNI.OT_API_withdrawVoucher(SERVER_ID, USER_ID, ACCT_ID, RECIPIENT_USER_ID, CHEQUE_MEMO, AMOUNT);
  }

  public static void OT_API_depositCheque(String SERVER_ID, String USER_ID, String ACCT_ID, String THE_CHEQUE) {
    otapiJNI.OT_API_depositCheque(SERVER_ID, USER_ID, ACCT_ID, THE_CHEQUE);
  }

  public static void OT_API_depositPaymentPlan(String SERVER_ID, String USER_ID, String THE_PAYMENT_PLAN) {
    otapiJNI.OT_API_depositPaymentPlan(SERVER_ID, USER_ID, THE_PAYMENT_PLAN);
  }

  public static void OT_API_issueMarketOffer(String SERVER_ID, String USER_ID, String ASSET_TYPE_ID, String ASSET_ACCT_ID, String CURRENCY_TYPE_ID, String CURRENCY_ACCT_ID, String MARKET_SCALE, String MINIMUM_INCREMENT, String TOTAL_ASSETS_ON_OFFER, String PRICE_LIMIT, int bBuyingOrSelling) {
    otapiJNI.OT_API_issueMarketOffer(SERVER_ID, USER_ID, ASSET_TYPE_ID, ASSET_ACCT_ID, CURRENCY_TYPE_ID, CURRENCY_ACCT_ID, MARKET_SCALE, MINIMUM_INCREMENT, TOTAL_ASSETS_ON_OFFER, PRICE_LIMIT, bBuyingOrSelling);
  }

  public static String OT_API_PopMessageBuffer() {
    return otapiJNI.OT_API_PopMessageBuffer();
  }

  public static void OT_API_FlushMessageBuffer() {
    otapiJNI.OT_API_FlushMessageBuffer();
  }

  public static String OT_API_Message_GetCommand(String THE_MESSAGE) {
    return otapiJNI.OT_API_Message_GetCommand(THE_MESSAGE);
  }

  public static int OT_API_Message_GetSuccess(String THE_MESSAGE) {
    return otapiJNI.OT_API_Message_GetSuccess(THE_MESSAGE);
  }

  public static String OT_API_Message_GetLedger(String THE_MESSAGE) {
    return otapiJNI.OT_API_Message_GetLedger(THE_MESSAGE);
  }

  public static String OT_API_Message_GetNewAssetTypeID(String THE_MESSAGE) {
    return otapiJNI.OT_API_Message_GetNewAssetTypeID(THE_MESSAGE);
  }

  public static String OT_API_Message_GetNewIssuerAcctID(String THE_MESSAGE) {
    return otapiJNI.OT_API_Message_GetNewIssuerAcctID(THE_MESSAGE);
  }

  public static int OT_API_ConnectServer(String SERVER_ID, String USER_ID, String szCA_FILE, String szKEY_FILE, String szKEY_PASSWORD) {
    return otapiJNI.OT_API_ConnectServer(SERVER_ID, USER_ID, szCA_FILE, szKEY_FILE, szKEY_PASSWORD);
  }

  public static int OT_API_ProcessSockets() {
    return otapiJNI.OT_API_ProcessSockets();
  }

}
