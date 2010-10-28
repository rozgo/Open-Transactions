
# COMMENT: This is set up for Mac OS X.   If you are using Linux, then you
# need to uncomment the LINUX line, and comment out the MAC line. Capiche?
# For each target.
#
# There is also a Makefile.linux, so if you want to run that one, type:
# make -f Makefile.linux
#
# This makefile will build the entire project and all the assorted tools.
#
# RPC is the PREFERRED mode to run the software, since it uses xmlrpc over
# http. BUT you need to have the XmlRpc++ library installed on your system.
# (It doesn't come with Open Transactions by default.)
# AND you need to make sure the Makefiles reference the same folder it's
# installed in, which may not be the same location that it is on MY system
# (and the Makefiles are set up for my system.)
#
# If that sounds daunting, trust me, it's not. But in the meantime, the
# default mode provides its own transport code via OTMessage -> TCP -> SSL, 
# built in.  So you can use it like that in the meantime.
# 
# But trust me, it's worth it to install XmlRpc++ and run OpenTransactions
# in that mode, since then it's fully-enabled as a web service, and it's
# just the preferred mode for running the software.
#
# Good luck!



all:
	cd OTLib && make
	cd transaction && make
	cd testwallet && make -f Makefile.CPP_API
	cd testwallet && make -f Makefile.JNI_API_MAC_OSX
	cd testwallet && make -f Makefile.testwallet
	cd util/otcreatemint && make && cp ./createmint.exe ../../transaction/data_folder/createmint.exe
	cd util/signcontract && make && cp ./signcontract.exe ../../testwallet/data_folder/signcontract.exe

debug:
	cd OTLib && make debug
	cd transaction && make debug
	cd testwallet && make -f Makefile.CPP_API debug
	cd testwallet && make -f Makefile.JNI_API_MAC_OSX debug
	cd testwallet && make -f Makefile.testwallet debug
	cd util/otcreatemint && make debug && cp ./createmint.debug ../../transaction/data_folder/createmint.debug
	cd util/signcontract && make debug && cp ./signcontract.debug ../../testwallet/data_folder/signcontract.debug

rpc:
	cd OTLib && make
	cd transaction && make -f Makefile.rpc
	cd testwallet && make -f Makefile.CPP_API rpc
	cd testwallet && make -f Makefile.JNI_API_MAC_OSX rpc
	cd testwallet && make -f Makefile.rpc
	cd util/otcreatemint && make && cp ./createmint.exe ../../transaction/data_folder/createmint.exe
	cd util/signcontract && make && cp ./signcontract.exe ../../testwallet/data_folder/signcontract.exe

debugrpc:
	cd OTLib && make debug
	cd transaction && make -f Makefile.rpc debug
	cd testwallet && make -f Makefile.CPP_API debugrpc
	cd testwallet && make -f Makefile.JNI_API_MAC_OSX debugrpc
	cd testwallet && make -f Makefile.rpc debug
	cd util/otcreatemint && make debug && cp ./createmint.debug ../../transaction/data_folder/createmint.debug
	cd util/signcontract && make debug && cp ./signcontract.debug ../../testwallet/data_folder/signcontract.debug

clean:
	cd OTLib && make clean
	cd transaction && make clean
	cd transaction && make -f Makefile.rpc clean
	cd testwallet && make -f Makefile.CPP_API clean
	cd testwallet && make -f Makefile.JNI_API_MAC_OSX clean
	cd testwallet && make -f Makefile.testwallet clean
	cd testwallet && make -f Makefile.rpc clean
	cd util/otcreatemint && make clean && touch ../../transaction/data_folder/createmint.tmp && rm ../../transaction/data_folder/createmint.*
	cd util/signcontract && make clean && touch ../../testwallet/data_folder/signcontract.tmp && rm ../../testwallet/data_folder/signcontract.*


 
