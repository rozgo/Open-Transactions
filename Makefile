all:
	cd OTLib && make
	cd transaction && make
	cd testwallet && make -f Makefile.CPP_API
	cd testwallet && make -f Makefile.testwallet
	cd util/otcreatemint && make
	cd util/signcontract && make

clean:
	cd OTLib && make clean
	cd transaction && make clean
	cd testwallet && make -f Makefile.CPP_API clean
	cd testwallet && make -f Makefile.testwallet clean
	cd util/otcreatemint && make clean
	cd util/signcontract && make clean
