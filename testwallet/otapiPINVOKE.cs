/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


using System;
using System.Runtime.InteropServices;

class otapiPINVOKE {

  protected class SWIGExceptionHelper {

    public delegate void ExceptionDelegate(string message);
    public delegate void ExceptionArgumentDelegate(string message, string paramName);

    static ExceptionDelegate applicationDelegate = new ExceptionDelegate(SetPendingApplicationException);
    static ExceptionDelegate arithmeticDelegate = new ExceptionDelegate(SetPendingArithmeticException);
    static ExceptionDelegate divideByZeroDelegate = new ExceptionDelegate(SetPendingDivideByZeroException);
    static ExceptionDelegate indexOutOfRangeDelegate = new ExceptionDelegate(SetPendingIndexOutOfRangeException);
    static ExceptionDelegate invalidCastDelegate = new ExceptionDelegate(SetPendingInvalidCastException);
    static ExceptionDelegate invalidOperationDelegate = new ExceptionDelegate(SetPendingInvalidOperationException);
    static ExceptionDelegate ioDelegate = new ExceptionDelegate(SetPendingIOException);
    static ExceptionDelegate nullReferenceDelegate = new ExceptionDelegate(SetPendingNullReferenceException);
    static ExceptionDelegate outOfMemoryDelegate = new ExceptionDelegate(SetPendingOutOfMemoryException);
    static ExceptionDelegate overflowDelegate = new ExceptionDelegate(SetPendingOverflowException);
    static ExceptionDelegate systemDelegate = new ExceptionDelegate(SetPendingSystemException);

    static ExceptionArgumentDelegate argumentDelegate = new ExceptionArgumentDelegate(SetPendingArgumentException);
    static ExceptionArgumentDelegate argumentNullDelegate = new ExceptionArgumentDelegate(SetPendingArgumentNullException);
    static ExceptionArgumentDelegate argumentOutOfRangeDelegate = new ExceptionArgumentDelegate(SetPendingArgumentOutOfRangeException);

    [DllImport("otapi", EntryPoint="SWIGRegisterExceptionCallbacks_otapi")]
    public static extern void SWIGRegisterExceptionCallbacks_otapi(
                                ExceptionDelegate applicationDelegate,
                                ExceptionDelegate arithmeticDelegate,
                                ExceptionDelegate divideByZeroDelegate, 
                                ExceptionDelegate indexOutOfRangeDelegate, 
                                ExceptionDelegate invalidCastDelegate,
                                ExceptionDelegate invalidOperationDelegate,
                                ExceptionDelegate ioDelegate,
                                ExceptionDelegate nullReferenceDelegate,
                                ExceptionDelegate outOfMemoryDelegate, 
                                ExceptionDelegate overflowDelegate, 
                                ExceptionDelegate systemExceptionDelegate);

    [DllImport("otapi", EntryPoint="SWIGRegisterExceptionArgumentCallbacks_otapi")]
    public static extern void SWIGRegisterExceptionCallbacksArgument_otapi(
                                ExceptionArgumentDelegate argumentDelegate,
                                ExceptionArgumentDelegate argumentNullDelegate,
                                ExceptionArgumentDelegate argumentOutOfRangeDelegate);

    static void SetPendingApplicationException(string message) {
      SWIGPendingException.Set(new System.ApplicationException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingArithmeticException(string message) {
      SWIGPendingException.Set(new System.ArithmeticException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingDivideByZeroException(string message) {
      SWIGPendingException.Set(new System.DivideByZeroException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingIndexOutOfRangeException(string message) {
      SWIGPendingException.Set(new System.IndexOutOfRangeException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingInvalidCastException(string message) {
      SWIGPendingException.Set(new System.InvalidCastException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingInvalidOperationException(string message) {
      SWIGPendingException.Set(new System.InvalidOperationException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingIOException(string message) {
      SWIGPendingException.Set(new System.IO.IOException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingNullReferenceException(string message) {
      SWIGPendingException.Set(new System.NullReferenceException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingOutOfMemoryException(string message) {
      SWIGPendingException.Set(new System.OutOfMemoryException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingOverflowException(string message) {
      SWIGPendingException.Set(new System.OverflowException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingSystemException(string message) {
      SWIGPendingException.Set(new System.SystemException(message, SWIGPendingException.Retrieve()));
    }

    static void SetPendingArgumentException(string message, string paramName) {
      SWIGPendingException.Set(new System.ArgumentException(message, paramName, SWIGPendingException.Retrieve()));
    }
    static void SetPendingArgumentNullException(string message, string paramName) {
      Exception e = SWIGPendingException.Retrieve();
      if (e != null) message = message + " Inner Exception: " + e.Message;
      SWIGPendingException.Set(new System.ArgumentNullException(paramName, message));
    }
    static void SetPendingArgumentOutOfRangeException(string message, string paramName) {
      Exception e = SWIGPendingException.Retrieve();
      if (e != null) message = message + " Inner Exception: " + e.Message;
      SWIGPendingException.Set(new System.ArgumentOutOfRangeException(paramName, message));
    }

    static SWIGExceptionHelper() {
      SWIGRegisterExceptionCallbacks_otapi(
                                applicationDelegate,
                                arithmeticDelegate,
                                divideByZeroDelegate,
                                indexOutOfRangeDelegate,
                                invalidCastDelegate,
                                invalidOperationDelegate,
                                ioDelegate,
                                nullReferenceDelegate,
                                outOfMemoryDelegate,
                                overflowDelegate,
                                systemDelegate);

      SWIGRegisterExceptionCallbacksArgument_otapi(
                                argumentDelegate,
                                argumentNullDelegate,
                                argumentOutOfRangeDelegate);
    }
  }

  protected static SWIGExceptionHelper swigExceptionHelper = new SWIGExceptionHelper();

  public class SWIGPendingException {
    [ThreadStatic]
    private static Exception pendingException = null;
    private static int numExceptionsPending = 0;

    public static bool Pending {
      get {
        bool pending = false;
        if (numExceptionsPending > 0)
          if (pendingException != null)
            pending = true;
        return pending;
      } 
    }

    public static void Set(Exception e) {
      if (pendingException != null)
        throw new ApplicationException("FATAL: An earlier pending exception from unmanaged code was missed and thus not thrown (" + pendingException.ToString() + ")", e);
      pendingException = e;
      lock(typeof(otapiPINVOKE)) {
        numExceptionsPending++;
      }
    }

    public static Exception Retrieve() {
      Exception e = null;
      if (numExceptionsPending > 0) {
        if (pendingException != null) {
          e = pendingException;
          pendingException = null;
          lock(typeof(otapiPINVOKE)) {
            numExceptionsPending--;
          }
        }
      }
      return e;
    }
  }


  protected class SWIGStringHelper {

    public delegate string SWIGStringDelegate(string message);
    static SWIGStringDelegate stringDelegate = new SWIGStringDelegate(CreateString);

    [DllImport("otapi", EntryPoint="SWIGRegisterStringCallback_otapi")]
    public static extern void SWIGRegisterStringCallback_otapi(SWIGStringDelegate stringDelegate);

    static string CreateString(string cString) {
      return cString;
    }

    static SWIGStringHelper() {
      SWIGRegisterStringCallback_otapi(stringDelegate);
    }
  }

  static protected SWIGStringHelper swigStringHelper = new SWIGStringHelper();


  [DllImport("otapi", EntryPoint="CSharp_OT_API_Init")]
  public static extern int OT_API_Init(string jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_LoadWallet")]
  public static extern int OT_API_LoadWallet(string jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_CreateNym")]
  public static extern string OT_API_CreateNym();

  [DllImport("otapi", EntryPoint="CSharp_OT_API_AddServerContract")]
  public static extern int OT_API_AddServerContract(string jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_AddAssetContract")]
  public static extern int OT_API_AddAssetContract(string jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_GetServerCount")]
  public static extern int OT_API_GetServerCount();

  [DllImport("otapi", EntryPoint="CSharp_OT_API_GetAssetTypeCount")]
  public static extern int OT_API_GetAssetTypeCount();

  [DllImport("otapi", EntryPoint="CSharp_OT_API_GetAccountCount")]
  public static extern int OT_API_GetAccountCount();

  [DllImport("otapi", EntryPoint="CSharp_OT_API_GetNymCount")]
  public static extern int OT_API_GetNymCount();

  [DllImport("otapi", EntryPoint="CSharp_OT_API_GetServer_ID")]
  public static extern string OT_API_GetServer_ID(int jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_GetServer_Name")]
  public static extern string OT_API_GetServer_Name(string jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_GetAssetType_ID")]
  public static extern string OT_API_GetAssetType_ID(int jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_GetAssetType_Name")]
  public static extern string OT_API_GetAssetType_Name(string jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_GetAccountWallet_ID")]
  public static extern string OT_API_GetAccountWallet_ID(int jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_GetAccountWallet_Name")]
  public static extern string OT_API_GetAccountWallet_Name(string jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_GetAccountWallet_Balance")]
  public static extern string OT_API_GetAccountWallet_Balance(string jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_GetAccountWallet_Type")]
  public static extern string OT_API_GetAccountWallet_Type(string jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_GetAccountWallet_AssetTypeID")]
  public static extern string OT_API_GetAccountWallet_AssetTypeID(string jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_GetAccountWallet_ServerID")]
  public static extern string OT_API_GetAccountWallet_ServerID(string jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_GetAccountWallet_NymID")]
  public static extern string OT_API_GetAccountWallet_NymID(string jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_GetNym_TransactionNumCount")]
  public static extern int OT_API_GetNym_TransactionNumCount(string jarg1, string jarg2);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_GetNym_ID")]
  public static extern string OT_API_GetNym_ID(int jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_GetNym_Name")]
  public static extern string OT_API_GetNym_Name(string jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_GetNym_Stats")]
  public static extern string OT_API_GetNym_Stats(string jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_IsNym_RegisteredAtServer")]
  public static extern int OT_API_IsNym_RegisteredAtServer(string jarg1, string jarg2);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_GetNym_MailCount")]
  public static extern int OT_API_GetNym_MailCount(string jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_GetNym_MailContentsByIndex")]
  public static extern string OT_API_GetNym_MailContentsByIndex(string jarg1, int jarg2);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_GetNym_MailSenderIDByIndex")]
  public static extern string OT_API_GetNym_MailSenderIDByIndex(string jarg1, int jarg2);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_GetNym_MailServerIDByIndex")]
  public static extern string OT_API_GetNym_MailServerIDByIndex(string jarg1, int jarg2);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Nym_RemoveMailByIndex")]
  public static extern int OT_API_Nym_RemoveMailByIndex(string jarg1, int jarg2);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Nym_VerifyMailByIndex")]
  public static extern int OT_API_Nym_VerifyMailByIndex(string jarg1, int jarg2);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_SetNym_Name")]
  public static extern int OT_API_SetNym_Name(string jarg1, string jarg2, string jarg3);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_SetAccountWallet_Name")]
  public static extern int OT_API_SetAccountWallet_Name(string jarg1, string jarg2, string jarg3);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_SetAssetType_Name")]
  public static extern int OT_API_SetAssetType_Name(string jarg1, string jarg2);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_SetServer_Name")]
  public static extern int OT_API_SetServer_Name(string jarg1, string jarg2);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_VerifyAndRetrieveXMLContents")]
  public static extern string OT_API_VerifyAndRetrieveXMLContents(string jarg1, string jarg2);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_WriteCheque")]
  public static extern string OT_API_WriteCheque(string jarg1, string jarg2, string jarg3, string jarg4, string jarg5, string jarg6, string jarg7, string jarg8);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_WritePaymentPlan")]
  public static extern string OT_API_WritePaymentPlan(string jarg1, string jarg2, string jarg3, string jarg4, string jarg5, string jarg6, string jarg7, string jarg8, string jarg9, string jarg10, string jarg11, string jarg12, string jarg13, string jarg14, string jarg15);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_LoadUserPubkey")]
  public static extern string OT_API_LoadUserPubkey(string jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_LoadPubkey")]
  public static extern string OT_API_LoadPubkey(string jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_VerifyUserPrivateKey")]
  public static extern int OT_API_VerifyUserPrivateKey(string jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_LoadPurse")]
  public static extern string OT_API_LoadPurse(string jarg1, string jarg2, string jarg3);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_LoadMint")]
  public static extern string OT_API_LoadMint(string jarg1, string jarg2);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_LoadAssetContract")]
  public static extern string OT_API_LoadAssetContract(string jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_LoadServerContract")]
  public static extern string OT_API_LoadServerContract(string jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_IsBasketCurrency")]
  public static extern int OT_API_IsBasketCurrency(string jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Basket_GetMemberCount")]
  public static extern int OT_API_Basket_GetMemberCount(string jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Basket_GetMemberType")]
  public static extern string OT_API_Basket_GetMemberType(string jarg1, int jarg2);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Basket_GetMinimumTransferAmount")]
  public static extern string OT_API_Basket_GetMinimumTransferAmount(string jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Basket_GetMemberMinimumTransferAmount")]
  public static extern string OT_API_Basket_GetMemberMinimumTransferAmount(string jarg1, int jarg2);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_LoadAssetAccount")]
  public static extern string OT_API_LoadAssetAccount(string jarg1, string jarg2, string jarg3);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_LoadInbox")]
  public static extern string OT_API_LoadInbox(string jarg1, string jarg2, string jarg3);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_LoadOutbox")]
  public static extern string OT_API_LoadOutbox(string jarg1, string jarg2, string jarg3);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Ledger_GetCount")]
  public static extern int OT_API_Ledger_GetCount(string jarg1, string jarg2, string jarg3, string jarg4);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Ledger_CreateResponse")]
  public static extern string OT_API_Ledger_CreateResponse(string jarg1, string jarg2, string jarg3, string jarg4);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Ledger_GetTransactionByIndex")]
  public static extern string OT_API_Ledger_GetTransactionByIndex(string jarg1, string jarg2, string jarg3, string jarg4, int jarg5);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Ledger_GetTransactionByID")]
  public static extern string OT_API_Ledger_GetTransactionByID(string jarg1, string jarg2, string jarg3, string jarg4, string jarg5);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Ledger_GetTransactionIDByIndex")]
  public static extern string OT_API_Ledger_GetTransactionIDByIndex(string jarg1, string jarg2, string jarg3, string jarg4, int jarg5);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Ledger_AddTransaction")]
  public static extern string OT_API_Ledger_AddTransaction(string jarg1, string jarg2, string jarg3, string jarg4, string jarg5);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Transaction_CreateResponse")]
  public static extern string OT_API_Transaction_CreateResponse(string jarg1, string jarg2, string jarg3, string jarg4, string jarg5, int jarg6);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Ledger_FinalizeResponse")]
  public static extern string OT_API_Ledger_FinalizeResponse(string jarg1, string jarg2, string jarg3, string jarg4, int jarg5);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Transaction_GetType")]
  public static extern string OT_API_Transaction_GetType(string jarg1, string jarg2, string jarg3, string jarg4);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Transaction_GetVoucher")]
  public static extern string OT_API_Transaction_GetVoucher(string jarg1, string jarg2, string jarg3, string jarg4);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Transaction_GetSuccess")]
  public static extern int OT_API_Transaction_GetSuccess(string jarg1, string jarg2, string jarg3, string jarg4);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Transaction_GetDateSigned")]
  public static extern string OT_API_Transaction_GetDateSigned(string jarg1, string jarg2, string jarg3, string jarg4);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Transaction_GetAmount")]
  public static extern string OT_API_Transaction_GetAmount(string jarg1, string jarg2, string jarg3, string jarg4);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Pending_GetNote")]
  public static extern string OT_API_Pending_GetNote(string jarg1, string jarg2, string jarg3, string jarg4);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Transaction_GetSenderUserID")]
  public static extern string OT_API_Transaction_GetSenderUserID(string jarg1, string jarg2, string jarg3, string jarg4);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Transaction_GetSenderAcctID")]
  public static extern string OT_API_Transaction_GetSenderAcctID(string jarg1, string jarg2, string jarg3, string jarg4);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Transaction_GetRecipientUserID")]
  public static extern string OT_API_Transaction_GetRecipientUserID(string jarg1, string jarg2, string jarg3, string jarg4);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Transaction_GetRecipientAcctID")]
  public static extern string OT_API_Transaction_GetRecipientAcctID(string jarg1, string jarg2, string jarg3, string jarg4);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Transaction_GetDisplayReferenceToNum")]
  public static extern string OT_API_Transaction_GetDisplayReferenceToNum(string jarg1, string jarg2, string jarg3, string jarg4);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Purse_GetTotalValue")]
  public static extern string OT_API_Purse_GetTotalValue(string jarg1, string jarg2, string jarg3);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_checkServerID")]
  public static extern void OT_API_checkServerID(string jarg1, string jarg2);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_createUserAccount")]
  public static extern void OT_API_createUserAccount(string jarg1, string jarg2);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_checkUser")]
  public static extern void OT_API_checkUser(string jarg1, string jarg2, string jarg3);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_sendUserMessage")]
  public static extern void OT_API_sendUserMessage(string jarg1, string jarg2, string jarg3, string jarg4, string jarg5);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_getRequest")]
  public static extern void OT_API_getRequest(string jarg1, string jarg2);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_getTransactionNumber")]
  public static extern void OT_API_getTransactionNumber(string jarg1, string jarg2);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_issueAssetType")]
  public static extern void OT_API_issueAssetType(string jarg1, string jarg2, string jarg3);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_getContract")]
  public static extern void OT_API_getContract(string jarg1, string jarg2, string jarg3);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_getMint")]
  public static extern void OT_API_getMint(string jarg1, string jarg2, string jarg3);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_createAssetAccount")]
  public static extern void OT_API_createAssetAccount(string jarg1, string jarg2, string jarg3);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_getAccount")]
  public static extern void OT_API_getAccount(string jarg1, string jarg2, string jarg3);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_GenerateBasketCreation")]
  public static extern string OT_API_GenerateBasketCreation(string jarg1, string jarg2);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_AddBasketCreationItem")]
  public static extern string OT_API_AddBasketCreationItem(string jarg1, string jarg2, string jarg3, string jarg4);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_issueBasket")]
  public static extern void OT_API_issueBasket(string jarg1, string jarg2, string jarg3);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_GenerateBasketExchange")]
  public static extern string OT_API_GenerateBasketExchange(string jarg1, string jarg2, string jarg3, string jarg4, int jarg5);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_AddBasketExchangeItem")]
  public static extern string OT_API_AddBasketExchangeItem(string jarg1, string jarg2, string jarg3, string jarg4, string jarg5);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_exchangeBasket")]
  public static extern void OT_API_exchangeBasket(string jarg1, string jarg2, string jarg3, string jarg4, int jarg5);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_notarizeWithdrawal")]
  public static extern void OT_API_notarizeWithdrawal(string jarg1, string jarg2, string jarg3, string jarg4);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_notarizeDeposit")]
  public static extern void OT_API_notarizeDeposit(string jarg1, string jarg2, string jarg3, string jarg4);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_notarizeTransfer")]
  public static extern void OT_API_notarizeTransfer(string jarg1, string jarg2, string jarg3, string jarg4, string jarg5, string jarg6);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_getInbox")]
  public static extern void OT_API_getInbox(string jarg1, string jarg2, string jarg3);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_getOutbox")]
  public static extern void OT_API_getOutbox(string jarg1, string jarg2, string jarg3);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_getNymbox")]
  public static extern void OT_API_getNymbox(string jarg1, string jarg2);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_LoadNymbox")]
  public static extern string OT_API_LoadNymbox(string jarg1, string jarg2);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_processInbox")]
  public static extern void OT_API_processInbox(string jarg1, string jarg2, string jarg3, string jarg4);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_processNymbox")]
  public static extern void OT_API_processNymbox(string jarg1, string jarg2, string jarg3);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_withdrawVoucher")]
  public static extern void OT_API_withdrawVoucher(string jarg1, string jarg2, string jarg3, string jarg4, string jarg5, string jarg6);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_depositCheque")]
  public static extern void OT_API_depositCheque(string jarg1, string jarg2, string jarg3, string jarg4);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_depositPaymentPlan")]
  public static extern void OT_API_depositPaymentPlan(string jarg1, string jarg2, string jarg3);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_issueMarketOffer")]
  public static extern void OT_API_issueMarketOffer(string jarg1, string jarg2, string jarg3, string jarg4, string jarg5, string jarg6, string jarg7, string jarg8, string jarg9, string jarg10, int jarg11);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_PopMessageBuffer")]
  public static extern string OT_API_PopMessageBuffer();

  [DllImport("otapi", EntryPoint="CSharp_OT_API_FlushMessageBuffer")]
  public static extern void OT_API_FlushMessageBuffer();

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Message_GetCommand")]
  public static extern string OT_API_Message_GetCommand(string jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Message_GetSuccess")]
  public static extern int OT_API_Message_GetSuccess(string jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Message_GetLedger")]
  public static extern string OT_API_Message_GetLedger(string jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Message_GetNewAssetTypeID")]
  public static extern string OT_API_Message_GetNewAssetTypeID(string jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_Message_GetNewIssuerAcctID")]
  public static extern string OT_API_Message_GetNewIssuerAcctID(string jarg1);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_ConnectServer")]
  public static extern int OT_API_ConnectServer(string jarg1, string jarg2, string jarg3, string jarg4, string jarg5);

  [DllImport("otapi", EntryPoint="CSharp_OT_API_ProcessSockets")]
  public static extern int OT_API_ProcessSockets();
}
