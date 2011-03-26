// runme.java

public class runme {
  static {
    System.loadLibrary("otapi");
  }

  public static void main(String argv[]) {
	otapi.OT_API_Init("/Users/REDACTED/Projects/Open-Transactions/testwallet/data_folder");
	otapi.OT_API_LoadWallet("wallet.xml");
  }
}
