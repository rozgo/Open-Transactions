<?php

require_once "otapi.php";

$wallet_path = "data_folder";
$ot_init = OT_API_Init($wallet_path);
$switch_wallet = OT_API_SwitchWallet($wallet_path, "wallet.xml");
echo "OT_API_Init => " . var_dump($ot_init);
echo "OT_SwitchWallet => " . var_dump($switch_wallet);

?>
