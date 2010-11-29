

;;;SWIG wrapper code starts here

(cl:defmacro defanonenum (&body enums)
   "Converts anonymous enums to defconstants."
  `(cl:progn ,@(cl:loop for value in enums
                        for index = 0 then (cl:1+ index)
                        when (cl:listp value) do (cl:setf index (cl:second value)
                                                          value (cl:first value))
                        collect `(cl:defconstant ,value ,index))))

(cl:eval-when (:compile-toplevel :load-toplevel)
  (cl:unless (cl:fboundp 'swig-lispify)
    (cl:defun swig-lispify (name flag cl:&optional (package cl:*package*))
      (cl:labels ((helper (lst last rest cl:&aux (c (cl:car lst)))
                    (cl:cond
                      ((cl:null lst)
                       rest)
                      ((cl:upper-case-p c)
                       (helper (cl:cdr lst) 'upper
                               (cl:case last
                                 ((lower digit) (cl:list* c #\- rest))
                                 (cl:t (cl:cons c rest)))))
                      ((cl:lower-case-p c)
                       (helper (cl:cdr lst) 'lower (cl:cons (cl:char-upcase c) rest)))
                      ((cl:digit-char-p c)
                       (helper (cl:cdr lst) 'digit 
                               (cl:case last
                                 ((upper lower) (cl:list* c #\- rest))
                                 (cl:t (cl:cons c rest)))))
                      ((cl:char-equal c #\_)
                       (helper (cl:cdr lst) '_ (cl:cons #\- rest)))
                      (cl:t
                       (cl:error "Invalid character: ~A" c)))))
        (cl:let ((fix (cl:case flag
                        ((constant enumvalue) "+")
                        (variable "*")
                        (cl:t ""))))
          (cl:intern
           (cl:concatenate
            'cl:string
            fix
            (cl:nreverse (helper (cl:concatenate 'cl:list name) cl:nil cl:nil))
            fix)
           package))))))

;;;SWIG wrapper code ends here


(cffi:defcfun ("OT_API_Init" OT_API_Init) :int
  (szClientPath :string))

(cffi:defcfun ("OT_API_LoadWallet" OT_API_LoadWallet) :int
  (szPath :string))

(cffi:defcfun ("OT_API_ConnectServer" OT_API_ConnectServer) :int
  (SERVER_ID :string)
  (USER_ID :string)
  (szCA_FILE :string)
  (szKEY_FILE :string)
  (szKEY_PASSWORD :string))

(cffi:defcfun ("OT_API_ProcessSockets" OT_API_ProcessSockets) :int)

(cffi:defcfun ("OT_API_GetNymCount" OT_API_GetNymCount) :int)

(cffi:defcfun ("OT_API_GetServerCount" OT_API_GetServerCount) :int)

(cffi:defcfun ("OT_API_GetAssetTypeCount" OT_API_GetAssetTypeCount) :int)

(cffi:defcfun ("OT_API_GetAccountCount" OT_API_GetAccountCount) :int)

(cffi:defcfun ("OT_API_GetNym_ID" OT_API_GetNym_ID) :string
  (nIndex :int))

(cffi:defcfun ("OT_API_GetNym_Name" OT_API_GetNym_Name) :string
  (NYM_ID :string))

(cffi:defcfun ("OT_API_GetServer_ID" OT_API_GetServer_ID) :string
  (nIndex :int))

(cffi:defcfun ("OT_API_GetServer_Name" OT_API_GetServer_Name) :string
  (SERVER_ID :string))

(cffi:defcfun ("OT_API_GetAssetType_ID" OT_API_GetAssetType_ID) :string
  (nIndex :int))

(cffi:defcfun ("OT_API_GetAssetType_Name" OT_API_GetAssetType_Name) :string
  (ASSET_TYPE_ID :string))

(cffi:defcfun ("OT_API_GetAccountWallet_ID" OT_API_GetAccountWallet_ID) :string
  (nIndex :int))

(cffi:defcfun ("OT_API_GetAccountWallet_Name" OT_API_GetAccountWallet_Name) :string
  (ACCOUNT_ID :string))

(cffi:defcfun ("OT_API_GetAccountWallet_Balance" OT_API_GetAccountWallet_Balance) :string
  (ACCOUNT_ID :string))

(cffi:defcfun ("OT_API_GetAccountWallet_Type" OT_API_GetAccountWallet_Type) :string
  (ACCOUNT_ID :string))

(cffi:defcfun ("OT_API_GetAccountWallet_AssetTypeID" OT_API_GetAccountWallet_AssetTypeID) :string
  (ACCOUNT_ID :string))

(cffi:defcfun ("OT_API_WriteCheque" OT_API_WriteCheque) :string
  (SERVER_ID :string)
  (CHEQUE_AMOUNT :string)
  (VALID_FROM :string)
  (VALID_TO :string)
  (SENDER_ACCT_ID :string)
  (SENDER_USER_ID :string)
  (CHEQUE_MEMO :string)
  (RECIPIENT_USER_ID :string))

(cffi:defcfun ("OT_API_WritePaymentPlan" OT_API_WritePaymentPlan) :string
  (SERVER_ID :string)
  (VALID_FROM :string)
  (VALID_TO :string)
  (SENDER_ACCT_ID :string)
  (SENDER_USER_ID :string)
  (PLAN_CONSIDERATION :string)
  (RECIPIENT_ACCT_ID :string)
  (RECIPIENT_USER_ID :string)
  (INITIAL_PAYMENT_AMOUNT :string)
  (INITIAL_PAYMENT_DELAY :string)
  (PAYMENT_PLAN_AMOUNT :string)
  (PAYMENT_PLAN_DELAY :string)
  (PAYMENT_PLAN_PERIOD :string)
  (PAYMENT_PLAN_LENGTH :string)
  (PAYMENT_PLAN_MAX_PAYMENTS :string))

(cffi:defcfun ("OT_API_LoadUserPubkey" OT_API_LoadUserPubkey) :string
  (USER_ID :string))

(cffi:defcfun ("OT_API_LoadPubkey" OT_API_LoadPubkey) :string
  (USER_ID :string))

(cffi:defcfun ("OT_API_VerifyUserPrivateKey" OT_API_VerifyUserPrivateKey) :int
  (USER_ID :string))

(cffi:defcfun ("OT_API_LoadPurse" OT_API_LoadPurse) :string
  (SERVER_ID :string)
  (ASSET_TYPE_ID :string))

(cffi:defcfun ("OT_API_LoadMint" OT_API_LoadMint) :string
  (SERVER_ID :string)
  (ASSET_TYPE_ID :string))

(cffi:defcfun ("OT_API_LoadAssetContract" OT_API_LoadAssetContract) :string
  (ASSET_TYPE_ID :string))

(cffi:defcfun ("OT_API_IsBasketCurrency" OT_API_IsBasketCurrency) :int
  (ASSET_TYPE_ID :string))

(cffi:defcfun ("OT_API_Basket_GetMemberCount" OT_API_Basket_GetMemberCount) :int
  (BASKET_ASSET_TYPE_ID :string))

(cffi:defcfun ("OT_API_Basket_GetMemberType" OT_API_Basket_GetMemberType) :string
  (BASKET_ASSET_TYPE_ID :string)
  (nIndex :int))

(cffi:defcfun ("OT_API_Basket_GetMinimumTransferAmount" OT_API_Basket_GetMinimumTransferAmount) :string
  (BASKET_ASSET_TYPE_ID :string))

(cffi:defcfun ("OT_API_Basket_GetMemberMinimumTransferAmount" OT_API_Basket_GetMemberMinimumTransferAmount) :string
  (BASKET_ASSET_TYPE_ID :string)
  (nIndex :int))

(cffi:defcfun ("OT_API_LoadAssetAccount" OT_API_LoadAssetAccount) :string
  (SERVER_ID :string)
  (USER_ID :string)
  (ACCOUNT_ID :string))

(cffi:defcfun ("OT_API_LoadInbox" OT_API_LoadInbox) :string
  (SERVER_ID :string)
  (USER_ID :string)
  (ACCOUNT_ID :string))

(cffi:defcfun ("OT_API_LoadOutbox" OT_API_LoadOutbox) :string
  (SERVER_ID :string)
  (USER_ID :string)
  (ACCOUNT_ID :string))

(cffi:defcfun ("OT_API_Ledger_GetCount" OT_API_Ledger_GetCount) :int
  (SERVER_ID :string)
  (USER_ID :string)
  (ACCOUNT_ID :string)
  (THE_LEDGER :string))

(cffi:defcfun ("OT_API_Ledger_CreateResponse" OT_API_Ledger_CreateResponse) :string
  (SERVER_ID :string)
  (USER_ID :string)
  (ACCOUNT_ID :string)
  (ORIGINAL_LEDGER :string))

(cffi:defcfun ("OT_API_Ledger_GetTransactionByIndex" OT_API_Ledger_GetTransactionByIndex) :string
  (SERVER_ID :string)
  (USER_ID :string)
  (ACCOUNT_ID :string)
  (THE_LEDGER :string)
  (nIndex :int))

(cffi:defcfun ("OT_API_Ledger_GetTransactionByID" OT_API_Ledger_GetTransactionByID) :string
  (SERVER_ID :string)
  (USER_ID :string)
  (ACCOUNT_ID :string)
  (THE_LEDGER :string)
  (TRANSACTION_NUMBER :string))

(cffi:defcfun ("OT_API_Ledger_GetTransactionIDByIndex" OT_API_Ledger_GetTransactionIDByIndex) :string
  (SERVER_ID :string)
  (USER_ID :string)
  (ACCOUNT_ID :string)
  (THE_LEDGER :string)
  (nIndex :int))

(cffi:defcfun ("OT_API_Ledger_AddTransaction" OT_API_Ledger_AddTransaction) :string
  (SERVER_ID :string)
  (USER_ID :string)
  (ACCOUNT_ID :string)
  (THE_LEDGER :string)
  (THE_TRANSACTION :string))

(cffi:defcfun ("OT_API_Transaction_CreateResponse" OT_API_Transaction_CreateResponse) :string
  (SERVER_ID :string)
  (USER_ID :string)
  (ACCOUNT_ID :string)
  (RESPONSE_LEDGER :string)
  (ORIGINAL_TRANSACTION :string)
  (BOOL_DO_I_ACCEPT :int))

(cffi:defcfun ("OT_API_Transaction_GetType" OT_API_Transaction_GetType) :string
  (SERVER_ID :string)
  (USER_ID :string)
  (ACCOUNT_ID :string)
  (THE_TRANSACTION :string))

(cffi:defcfun ("OT_API_Transaction_GetSuccess" OT_API_Transaction_GetSuccess) :int
  (SERVER_ID :string)
  (USER_ID :string)
  (ACCOUNT_ID :string)
  (THE_TRANSACTION :string))

(cffi:defcfun ("OT_API_Purse_GetTotalValue" OT_API_Purse_GetTotalValue) :string
  (SERVER_ID :string)
  (ASSET_TYPE_ID :string)
  (THE_PURSE :string))

(cffi:defcfun ("OT_API_checkServerID" OT_API_checkServerID) :void
  (SERVER_ID :string)
  (USER_ID :string))

(cffi:defcfun ("OT_API_createUserAccount" OT_API_createUserAccount) :void
  (SERVER_ID :string)
  (USER_ID :string))

(cffi:defcfun ("OT_API_checkUser" OT_API_checkUser) :void
  (SERVER_ID :string)
  (USER_ID :string)
  (USER_ID_CHECK :string))

(cffi:defcfun ("OT_API_getRequest" OT_API_getRequest) :void
  (SERVER_ID :string)
  (USER_ID :string))

(cffi:defcfun ("OT_API_getTransactionNumber" OT_API_getTransactionNumber) :void
  (SERVER_ID :string)
  (USER_ID :string))

(cffi:defcfun ("OT_API_issueAssetType" OT_API_issueAssetType) :void
  (SERVER_ID :string)
  (USER_ID :string)
  (THE_CONTRACT :string))

(cffi:defcfun ("OT_API_getContract" OT_API_getContract) :void
  (SERVER_ID :string)
  (USER_ID :string)
  (ASSET_ID :string))

(cffi:defcfun ("OT_API_getMint" OT_API_getMint) :void
  (SERVER_ID :string)
  (USER_ID :string)
  (ASSET_ID :string))

(cffi:defcfun ("OT_API_createAssetAccount" OT_API_createAssetAccount) :void
  (SERVER_ID :string)
  (USER_ID :string)
  (ASSET_ID :string))

(cffi:defcfun ("OT_API_getAccount" OT_API_getAccount) :void
  (SERVER_ID :string)
  (USER_ID :string)
  (ACCT_ID :string))

(cffi:defcfun ("OT_API_GenerateBasketCreation" OT_API_GenerateBasketCreation) :string
  (USER_ID :string)
  (MINIMUM_TRANSFER :string))

(cffi:defcfun ("OT_API_AddBasketCreationItem" OT_API_AddBasketCreationItem) :string
  (USER_ID :string)
  (THE_BASKET :string)
  (ASSET_TYPE_ID :string)
  (MINIMUM_TRANSFER :string))

(cffi:defcfun ("OT_API_issueBasket" OT_API_issueBasket) :void
  (SERVER_ID :string)
  (USER_ID :string)
  (THE_BASKET :string))

(cffi:defcfun ("OT_API_GenerateBasketExchange" OT_API_GenerateBasketExchange) :string
  (SERVER_ID :string)
  (USER_ID :string)
  (BASKET_ASSET_TYPE_ID :string)
  (BASKET_ASSET_ACCT_ID :string)
  (TRANSFER_MULTIPLE :int))

(cffi:defcfun ("OT_API_AddBasketExchangeItem" OT_API_AddBasketExchangeItem) :string
  (SERVER_ID :string)
  (USER_ID :string)
  (THE_BASKET :string)
  (ASSET_TYPE_ID :string)
  (ASSET_ACCT_ID :string))

(cffi:defcfun ("OT_API_exchangeBasket" OT_API_exchangeBasket) :void
  (SERVER_ID :string)
  (USER_ID :string)
  (BASKET_ASSET_ID :string)
  (THE_BASKET :string)
  (BOOL_EXCHANGE_IN_OR_OUT :int))

(cffi:defcfun ("OT_API_notarizeWithdrawal" OT_API_notarizeWithdrawal) :void
  (SERVER_ID :string)
  (USER_ID :string)
  (ACCT_ID :string)
  (AMOUNT :string))

(cffi:defcfun ("OT_API_notarizeDeposit" OT_API_notarizeDeposit) :void
  (SERVER_ID :string)
  (USER_ID :string)
  (ACCT_ID :string)
  (THE_PURSE :string))

(cffi:defcfun ("OT_API_notarizeTransfer" OT_API_notarizeTransfer) :void
  (SERVER_ID :string)
  (USER_ID :string)
  (ACCT_FROM :string)
  (ACCT_TO :string)
  (AMOUNT :string)
  (NOTE :string))

(cffi:defcfun ("OT_API_getInbox" OT_API_getInbox) :void
  (SERVER_ID :string)
  (USER_ID :string)
  (ACCT_ID :string))

(cffi:defcfun ("OT_API_processInbox" OT_API_processInbox) :void
  (SERVER_ID :string)
  (USER_ID :string)
  (ACCT_ID :string)
  (ACCT_LEDGER :string))

(cffi:defcfun ("OT_API_withdrawVoucher" OT_API_withdrawVoucher) :void
  (SERVER_ID :string)
  (USER_ID :string)
  (ACCT_ID :string)
  (RECIPIENT_USER_ID :string)
  (CHEQUE_MEMO :string)
  (AMOUNT :string))

(cffi:defcfun ("OT_API_depositCheque" OT_API_depositCheque) :void
  (SERVER_ID :string)
  (USER_ID :string)
  (ACCT_ID :string)
  (THE_CHEQUE :string))

(cffi:defcfun ("OT_API_depositPaymentPlan" OT_API_depositPaymentPlan) :void
  (SERVER_ID :string)
  (USER_ID :string)
  (THE_PAYMENT_PLAN :string))

(cffi:defcfun ("OT_API_issueMarketOffer" OT_API_issueMarketOffer) :void
  (SERVER_ID :string)
  (USER_ID :string)
  (ASSET_TYPE_ID :string)
  (ASSET_ACCT_ID :string)
  (CURRENCY_TYPE_ID :string)
  (CURRENCY_ACCT_ID :string)
  (MARKET_SCALE :string)
  (MINIMUM_INCREMENT :string)
  (TOTAL_ASSETS_ON_OFFER :string)
  (PRICE_LIMIT :string)
  (bBuyingOrSelling :int))

(cffi:defcfun ("OT_API_PopMessageBuffer" OT_API_PopMessageBuffer) :string)

(cffi:defcfun ("OT_API_FlushMessageBuffer" OT_API_FlushMessageBuffer) :void)

(cffi:defcfun ("OT_API_Message_GetCommand" OT_API_Message_GetCommand) :string
  (THE_MESSAGE :string))

(cffi:defcfun ("OT_API_Message_GetSuccess" OT_API_Message_GetSuccess) :int
  (THE_MESSAGE :string))

(cffi:defcfun ("OT_API_Message_GetLedger" OT_API_Message_GetLedger) :string
  (THE_MESSAGE :string))


