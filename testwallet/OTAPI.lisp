

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

(cffi:defcfun ("OT_API_connectServer" OT_API_connectServer) :int
  (SERVER_ID :string)
  (USER_ID :string)
  (szCA_FILE :string)
  (szKEY_FILE :string)
  (szKEY_PASSWORD :string))

(cffi:defcfun ("OT_API_processSockets" OT_API_processSockets) :int)

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

(cffi:defcfun ("OT_API_issueBasket" OT_API_issueBasket) :void
  (SERVER_ID :string)
  (USER_ID :string)
  (BASKET_INFO :string))

(cffi:defcfun ("OT_API_exchangeBasket" OT_API_exchangeBasket) :void
  (SERVER_ID :string)
  (USER_ID :string)
  (BASKET_ASSET_ID :string)
  (BASKET_INFO :string))

(cffi:defcfun ("OT_API_getTransactionNumber" OT_API_getTransactionNumber) :void
  (SERVER_ID :string)
  (USER_ID :string))

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


