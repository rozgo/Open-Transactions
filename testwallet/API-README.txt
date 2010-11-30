These instructions cover: BUILDING the API.

If you were looking for instructions for USING the API,
here they are:
https://github.com/FellowTraveler/Open-Transactions/wiki/API



First, to build the test client (it runs on the command-line):   

MAC OR LINUX:  make
FREEBSD:       gmake


You probably prefer to build in XmlRpc mode:

               make TRANSPORT=XmlRpc
               gmake TRANSPORT=XmlRpc




-----------------------------------------

WINDOWS: inside the Open-Transactions\testwallet\testwallet folder
is an MS Visual C++ 2010 Express project that will build this project
for Windows.

The output will be an executable called "testwallet.exe".
Run it from this directory like so: ./testwallet.exe 

On Windows you may have to copy it to this directory first, as it may
be in a Debug or Release folder.

------------------------------------------




BUILDING THE OTAPI (Makefile.API)

Open Transactions now supports native interfaces to the
following languages:

C, Obj-C, C++, C#, Java, Ruby, Python, Perl, Php, Tcl, Lisp

(Instructions for each language are below.)

You likely wish to add TRANSPORT=XmlRpc to the below commands, as well.
And: MAKE SURE you do a make clean when switching languages, since they
can interfere with each other. 

----------------
LINUX WARNING: On Linux, you must rebuild OTLib with the proper flags,
before you can build the OTAPI, or you'll get errors. If you are using
linux, do this now:

cd ../OTLib; make clean; make DYNAMIC_OTLIB=1; cd ../testwallet

Now you may continue with the rest of these instructions...
----------------
ADDITIONAL WARNING: I had python working on darwin, but then on linux
I had issues loading the .so. But then I realized I was on 64-bit linux,
and some pieces were linking with 64-bit, while others weren't, so that
was the problem.

My point?

In EVERY CASE, issues are possible. If you can work through them, please
let me know the details so I can add them to these notes. And if you need
my help, contact me, since I want to support people who are using the API.
----------------



C, Obj-C, C++

make -f Makefile.API [TRANSPORT=XmlRpc] LANGUAGE=c

To use OT in C, C++, or Obj-C, link to libOTAPI.a, and...

...to use the OTAPI C functions in C, Obj-C, or C++, include OTAPI.h

...or to use the OTAPI C++ class in C++, include OpenTransactions.h

--------------------------------

C#

make -f Makefile.API [TRANSPORT=XmlRpc] LANGUAGE=csharp

This builds the shared lib libotapi.so. Use otapi.cs in your C-Sharp
project.

--------------------------------

Java

make -f Makefile.API [TRANSPORT=XmlRpc] LANGUAGE=java

This builds the shared lib libotapi.jnilib. Use otapi.java in your Java 
project.

--------------------------------

Ruby

make -f Makefile.API [TRANSPORT=XmlRpc] LANGUAGE=ruby

This builds otapi.bundle on Mac, and otapi.so on Linux, which you can use
in your Ruby project like any other native library.

On Linux I installed Ruby and Ruby-Dev:
apt-get install ruby
apt-get install ruby-dev



NOTE: The Ruby API now features a top-level build target! Especially on Linux,
this is the easiest way to build the Ruby API. To build for ruby, do it from
the MAIN folder:

	cd Open-Transactions; make clean; make ruby;


To test the Ruby API, follow these tests from there:

1)	cd testwallet; ruby

2) After you hit enter, paste the below ruby code, followed by a Ctrl-D as
depicted below:

require 'otapi'

Otapi.OT_API_Init "/full-path-goes-here/Open-Transactions/testwallet/data_folder"

Otapi.OT_API_LoadWallet "wallet.xml"

^D

NOTE: Use an actual Ctrl-D, and do not simply paste the one that appears above.
ADDITIONAL NOTE: Make sure you use the correct path, above where it says "full-
path-goes-here" you should substitute that for the appropriate path on your own
system. (On the command line, use the pwd command to see what the path is on your 
own system.)

If everything is successful, you will see the wallet loaded on the screen!


--------------------------------


Python

make -f Makefile.API [TRANSPORT=XmlRpc] LANGUAGE=python

This builds _otapi.so, a shared library that you can call from your Python
project using the otapi.py file.

To do this on linux, I had to install Python-dev:
apt-get install python-dev

From the testwallet folder, you can verify the Python API like this:

$
$
$
$ python
>>> import otapi
>>> otapi.OT_API_Init("/full-path-goes-here/Open-Transactions/testwallet/data_folder")
>>> otapi.OT_API_LoadWallet("wallet.xml")


Let me know if it works for you!

--------------------------------

Perl5

make -f Makefile.API [TRANSPORT=XmlRpc] LANGUAGE=perl5

This builds otapi.bundle, which you can use in your Perl project via
 the file otapi.pm

Problems BUILDING?  Check the version of Perl being included / linked
in the Makefile, and make sure it matches the location on your system.
You might have 5.10.1 instead of 5.10.0

Problems RUNNING?  One user reported a segmentation fault on his MAC OS X.
It was later determined that the user was building with perl 5.10.1,
but running perl version 5.8.8, which was segfaulting. So, try EXPLICITLY
running the correct version of perl at the command line, by typing 
perl5.10.0 or perl5.10.1, instead of just typing perl, when you run the
software. (This fixed the problem for me on my Mac.)
Example:
$ 
$ perl -e "use otapi;"
Segmentation fault
$ 
$ 
$ perl5.10.0 -e "use otapi;"
$ 
$ 
$  


Notice: no segfault when I do it the second way -- because I am
running the correct version of perl that time. Try it both ways
to test on your own computer which one is right.


PERL NOTE!!! There is now a TOP LEVEL option for building perl5!
Since some platforms require XmlRpc and OTLib to be rebuilt with
certain flags, I made it easy by adding a top-level target, since
we have a client developer who is actively targeting perl.

TO USE IT:

	cd Open-Transactions; make clean; make perl5;


It's that easy! To test it on the command line:

$ cd testwallet
$
$ perl5.10.0
use otapi;
otapi::OT_API_Init("/full-path-goes-here/Open-Transactions/testwallet/data_folder");
otapi::OT_API_LoadWallet("wallet.xml");

^D

Loading wallet: Fellow Traveler's test wallet, version: 1.0

(Etc. The entire wallet loaded.)

--------------------------------

PHP

make -f Makefile.API [TRANSPORT=XmlRpc] LANGUAGE=php5

This builds otapi.so, which you can use in your PHP project via the file otapi.php

On linux, make sure you have done this first:
apt-get install php5-dev

--------------------------------

Tcl

make -f Makefile.API [TRANSPORT=XmlRpc] LANGUAGE=tcl

This builds otapi.so, which you can use in your Tcl project like so:
load ./otapi.so otapi

On Linux, I had to install Tcl and Tcl-Dev:
apt-get install tcl
apt-get install tcl-dev

--------------------------------

LISP

make -f Makefile.API [TRANSPORT=XmlRpc] LANGUAGE=lisp

This builds otapi.so, which you can use in your LISP project via otapi.lisp


