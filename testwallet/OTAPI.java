/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


public class OTAPI {
  public static int OT_API_Init(String szClientPath) {
    return OTAPIJNI.OT_API_Init(szClientPath);
  }

  public static int OT_API_LoadWallet(String szPath) {
    return OTAPIJNI.OT_API_LoadWallet(szPath);
  }

  public static int OT_API_ConnectServer(String SERVER_ID, String USER_ID, String szCA_FILE, String szKEY_FILE, String szKEY_PASSWORD) {
    return OTAPIJNI.OT_API_ConnectServer(SERVER_ID, USER_ID, szCA_FILE, szKEY_FILE, szKEY_PASSWORD);
  }

  public static int OT_API_ProcessSockets() {
    return OTAPIJNI.OT_API_ProcessSockets();
  }

  public static int OT_API_GetNymCount() {
    return OTAPIJNI.OT_API_GetNymCount();
  }

  public static int OT_API_GetServerCount() {
    return OTAPIJNI.OT_API_GetServerCount();
  }

  public static int OT_API_GetAssetTypeCount() {
    return OTAPIJNI.OT_API_GetAssetTypeCount();
  }

  public static int OT_API_GetAccountCount() {
    return OTAPIJNI.OT_API_GetAccountCount();
  }

  public static String OT_API_GetNym_ID(int nIndex) {
    return OTAPIJNI.OT_API_GetNym_ID(nIndex);
  }

  public static String OT_API_GetNym_Name(String NYM_ID) {
    return OTAPIJNI.OT_API_GetNym_Name(NYM_ID);
  }

  public static String OT_API_GetServer_ID(int nIndex) {
    return OTAPIJNI.OT_API_GetServer_ID(nIndex);
  }

  public static String OT_API_GetServer_Name(String SERVER_ID) {
    return OTAPIJNI.OT_API_GetServer_Name(SERVER_ID);
  }

  public static String OT_API_GetAssetType_ID(int nIndex) {
    return OTAPIJNI.OT_API_GetAssetType_ID(nIndex);
  }

  public static String OT_API_GetAssetType_Name(String ASSET_TYPE_ID) {
    return OTAPIJNI.OT_API_GetAssetType_Name(ASSET_TYPE_ID);
  }

  public static String OT_API_GetAccountWallet_ID(int nIndex) {
    return OTAPIJNI.OT_API_GetAccountWallet_ID(nIndex);
  }

  public static String OT_API_GetAccountWallet_Name(String ACCOUNT_ID) {
    return OTAPIJNI.OT_API_GetAccountWallet_Name(ACCOUNT_ID);
  }

  public static String OT_API_GetAccountWallet_Balance(String ACCOUNT_ID) {
    return OTAPIJNI.OT_API_GetAccountWallet_Balance(ACCOUNT_ID);
  }

  public static String OT_API_GetAccountWallet_Type(String ACCOUNT_ID) {
    return OTAPIJNI.OT_API_GetAccountWallet_Type(ACCOUNT_ID);
  }

  public static String OT_API_GetAccountWallet_AssetTypeID(String ACCOUNT_ID) {
    return OTAPIJNI.OT_API_GetAccountWallet_AssetTypeID(ACCOUNT_ID);
  }

  public static String OT_API_WriteCheque(String SERVER_ID, String CHEQUE_AMOUNT, String VALID_FROM, String VALID_TO, String SENDER_ACCT_ID, String SENDER_USER_ID, String CHEQUE_MEMO, String RECIPIENT_USER_ID) {
    return OTAPIJNI.OT_API_WriteCheque(SERVER_ID, CHEQUE_AMOUNT, VALID_FROM, VALID_TO, SENDER_ACCT_ID, SENDER_USER_ID, CHEQUE_MEMO, RECIPIENT_USER_ID);
  }

  public static String OT_API_LoadUserPubkey(String USER_ID) {
    return OTAPIJNI.OT_API_LoadUserPubkey(USER_ID);
  }

  public static int OT_API_VerifyUserPrivateKey(String USER_ID) {
    return OTAPIJNI.OT_API_VerifyUserPrivateKey(USER_ID);
  }

  public static String OT_API_LoadPurse(String SERVER_ID, String ASSET_TYPE_ID) {
    return OTAPIJNI.OT_API_LoadPurse(SERVER_ID, ASSET_TYPE_ID);
  }

  public static String OT_API_LoadMint(String SERVER_ID, String ASSET_TYPE_ID) {
    return OTAPIJNI.OT_API_LoadMint(SERVER_ID, ASSET_TYPE_ID);
  }

  public static String OT_API_LoadAssetContract(String ASSET_TYPE_ID) {
    return OTAPIJNI.OT_API_LoadAssetContract(ASSET_TYPE_ID);
  }

  public static String OT_API_LoadAssetAccount(String SERVER_ID, String USER_ID, String ACCOUNT_ID) {
    return OTAPIJNI.OT_API_LoadAssetAccount(SERVER_ID, USER_ID, ACCOUNT_ID);
  }

  public static String OT_API_LoadInbox(String SERVER_ID, String USER_ID, String ACCOUNT_ID) {
    return OTAPIJNI.OT_API_LoadInbox(SERVER_ID, USER_ID, ACCOUNT_ID);
  }

  public static String OT_API_LoadOutbox(String SERVER_ID, String USER_ID, String ACCOUNT_ID) {
    return OTAPIJNI.OT_API_LoadOutbox(SERVER_ID, USER_ID, ACCOUNT_ID);
  }

  public static int OT_API_Ledger_GetCount(String SERVER_ID, String USER_ID, String ACCOUNT_ID, String THE_LEDGER) {
    return OTAPIJNI.OT_API_Ledger_GetCount(SERVER_ID, USER_ID, ACCOUNT_ID, THE_LEDGER);
  }

  public static String OT_API_Ledger_CreateResponse(String SERVER_ID, String USER_ID, String ACCOUNT_ID, String ORIGINAL_LEDGER) {
    return OTAPIJNI.OT_API_Ledger_CreateResponse(SERVER_ID, USER_ID, ACCOUNT_ID, ORIGINAL_LEDGER);
  }

  public static String OT_API_Ledger_GetTransactionByIndex(String SERVER_ID, String USER_ID, String ACCOUNT_ID, String THE_LEDGER, int nIndex) {
    return OTAPIJNI.OT_API_Ledger_GetTransactionByIndex(SERVER_ID, USER_ID, ACCOUNT_ID, THE_LEDGER, nIndex);
  }

  public static String OT_API_Ledger_GetTransactionByID(String SERVER_ID, String USER_ID, String ACCOUNT_ID, String THE_LEDGER, String TRANSACTION_NUMBER) {
    return OTAPIJNI.OT_API_Ledger_GetTransactionByID(SERVER_ID, USER_ID, ACCOUNT_ID, THE_LEDGER, TRANSACTION_NUMBER);
  }

  public static String OT_API_Ledger_GetTransactionIDByIndex(String SERVER_ID, String USER_ID, String ACCOUNT_ID, String THE_LEDGER, int nIndex) {
    return OTAPIJNI.OT_API_Ledger_GetTransactionIDByIndex(SERVER_ID, USER_ID, ACCOUNT_ID, THE_LEDGER, nIndex);
  }

  public static String OT_API_Ledger_AddTransaction(String SERVER_ID, String USER_ID, String ACCOUNT_ID, String THE_LEDGER, String THE_TRANSACTION) {
    return OTAPIJNI.OT_API_Ledger_AddTransaction(SERVER_ID, USER_ID, ACCOUNT_ID, THE_LEDGER, THE_TRANSACTION);
  }

  public static String OT_API_Transaction_CreateResponse(String SERVER_ID, String USER_ID, String ACCOUNT_ID, String RESPONSE_LEDGER, String ORIGINAL_TRANSACTION, int BOOL_DO_I_ACCEPT) {
    return OTAPIJNI.OT_API_Transaction_CreateResponse(SERVER_ID, USER_ID, ACCOUNT_ID, RESPONSE_LEDGER, ORIGINAL_TRANSACTION, BOOL_DO_I_ACCEPT);
  }

  public static String OT_API_Transaction_GetType(String SERVER_ID, String USER_ID, String ACCOUNT_ID, String THE_TRANSACTION) {
    return OTAPIJNI.OT_API_Transaction_GetType(SERVER_ID, USER_ID, ACCOUNT_ID, THE_TRANSACTION);
  }

  public static void OT_API_checkServerID(String SERVER_ID, String USER_ID) {
    OTAPIJNI.OT_API_checkServerID(SERVER_ID, USER_ID);
  }

  public static void OT_API_createUserAccount(String SERVER_ID, String USER_ID) {
    OTAPIJNI.OT_API_createUserAccount(SERVER_ID, USER_ID);
  }

  public static void OT_API_checkUser(String SERVER_ID, String USER_ID, String USER_ID_CHECK) {
    OTAPIJNI.OT_API_checkUser(SERVER_ID, USER_ID, USER_ID_CHECK);
  }

  public static void OT_API_getRequest(String SERVER_ID, String USER_ID) {
    OTAPIJNI.OT_API_getRequest(SERVER_ID, USER_ID);
  }

  public static void OT_API_getTransactionNumber(String SERVER_ID, String USER_ID) {
    OTAPIJNI.OT_API_getTransactionNumber(SERVER_ID, USER_ID);
  }

  public static void OT_API_issueAssetType(String SERVER_ID, String USER_ID, String THE_CONTRACT) {
    OTAPIJNI.OT_API_issueAssetType(SERVER_ID, USER_ID, THE_CONTRACT);
  }

  public static void OT_API_getContract(String SERVER_ID, String USER_ID, String ASSET_ID) {
    OTAPIJNI.OT_API_getContract(SERVER_ID, USER_ID, ASSET_ID);
  }

  public static void OT_API_getMint(String SERVER_ID, String USER_ID, String ASSET_ID) {
    OTAPIJNI.OT_API_getMint(SERVER_ID, USER_ID, ASSET_ID);
  }

  public static void OT_API_createAssetAccount(String SERVER_ID, String USER_ID, String ASSET_ID) {
    OTAPIJNI.OT_API_createAssetAccount(SERVER_ID, USER_ID, ASSET_ID);
  }

  public static void OT_API_getAccount(String SERVER_ID, String USER_ID, String ACCT_ID) {
    OTAPIJNI.OT_API_getAccount(SERVER_ID, USER_ID, ACCT_ID);
  }

  public static void OT_API_issueBasket(String SERVER_ID, String USER_ID, String BASKET_INFO) {
    OTAPIJNI.OT_API_issueBasket(SERVER_ID, USER_ID, BASKET_INFO);
  }

  public static void OT_API_exchangeBasket(String SERVER_ID, String USER_ID, String BASKET_ASSET_ID, String BASKET_INFO) {
    OTAPIJNI.OT_API_exchangeBasket(SERVER_ID, USER_ID, BASKET_ASSET_ID, BASKET_INFO);
  }

  public static void OT_API_notarizeWithdrawal(String SERVER_ID, String USER_ID, String ACCT_ID, String AMOUNT) {
    OTAPIJNI.OT_API_notarizeWithdrawal(SERVER_ID, USER_ID, ACCT_ID, AMOUNT);
  }

  public static void OT_API_notarizeDeposit(String SERVER_ID, String USER_ID, String ACCT_ID, String THE_PURSE) {
    OTAPIJNI.OT_API_notarizeDeposit(SERVER_ID, USER_ID, ACCT_ID, THE_PURSE);
  }

  public static void OT_API_notarizeTransfer(String SERVER_ID, String USER_ID, String ACCT_FROM, String ACCT_TO, String AMOUNT, String NOTE) {
    OTAPIJNI.OT_API_notarizeTransfer(SERVER_ID, USER_ID, ACCT_FROM, ACCT_TO, AMOUNT, NOTE);
  }

  public static void OT_API_getInbox(String SERVER_ID, String USER_ID, String ACCT_ID) {
    OTAPIJNI.OT_API_getInbox(SERVER_ID, USER_ID, ACCT_ID);
  }

  public static void OT_API_processInbox(String SERVER_ID, String USER_ID, String ACCT_ID, String ACCT_LEDGER) {
    OTAPIJNI.OT_API_processInbox(SERVER_ID, USER_ID, ACCT_ID, ACCT_LEDGER);
  }

  public static void OT_API_withdrawVoucher(String SERVER_ID, String USER_ID, String ACCT_ID, String RECIPIENT_USER_ID, String CHEQUE_MEMO, String AMOUNT) {
    OTAPIJNI.OT_API_withdrawVoucher(SERVER_ID, USER_ID, ACCT_ID, RECIPIENT_USER_ID, CHEQUE_MEMO, AMOUNT);
  }

  public static void OT_API_depositCheque(String SERVER_ID, String USER_ID, String ACCT_ID, String THE_CHEQUE) {
    OTAPIJNI.OT_API_depositCheque(SERVER_ID, USER_ID, ACCT_ID, THE_CHEQUE);
  }

}
