
To build the test client (it runs on the command-line):   

MAC OR LINUX:  make
FREEBSD:       gmake


You probably prefer to build in XmlRpc mode:

               make TRANSPORT=XmlRpc
               gmake TRANSPORT=XmlRpc

WINDOWS: inside the Open-Transactions\testwallet\testwallet folder
is an MS Visual C++ 2010 Express project that will build this project
for Windows.

The output will be an executable called "testwallet.exe".
Run it from this directory like so: ./testwallet.exe 

On Windows you may have to copy it to this directory first, as it may
be in a Debug or Release folder.

------------------------------------------




USING THE OTAPI (Makefile.API)

Open Transactions now supports native interfaces to the
following languages:

C, Obj-C, C++, C#, Java, Ruby, Python, Perl, Php, Tcl, Lisp

(Instructions for each language are below.)

You likely wish to add TRANSPORT=XmlRpc to the below commands, as well.

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

This builds the shared lib libOTAPI.so. Use OTAPI.cs in your C-Sharp
project.

--------------------------------

Java

make -f Makefile.API [TRANSPORT=XmlRpc] LANGUAGE=java

This builds the shared lib libOTAPI.jnilib. Use OTAPI.java in your Java 
project.

--------------------------------

Ruby

make -f Makefile.API [TRANSPORT=XmlRpc] LANGUAGE=ruby

This builds OTAPI.bundle which you can use in your Ruby project like any 
other native library.

On Linux I installed Ruby and Ruby-Dev:
apt-get install ruby
apt-get install ruby-dev

--------------------------------

Python

make -f Makefile.API [TRANSPORT=XmlRpc] LANGUAGE=python

This builds _OTAPI.so, a shared library that you can call from your Python
project using the OTAPI.py file.

To do this on linux, I had to install Python-dev:
apt-get install python-dev

--------------------------------

Perl5

make -f Makefile.API [TRANSPORT=XmlRpc] LANGUAGE=perl5

This builds OTAPI.bundle, which you can use in your Perl project via
 the file OTAPI.pm

Problems BUILDING?  Check the version of Perl being included / linked
in the Makefile, and make sure it matches the location on your system.
You might have 5.10.1 instead of 5.10.0

Problems RUNNING?  One user reported a segmentation fault on his Mac.
It was later determined that the user was building with version 5.10.1,
but running perl version 5.8.8, which was segfaulting. Try EXPLICITLY
running the correct version of perl at the command line, by typing 
perl5.10.0 or perl5.10.1, instead of just typing perl, when you run the
software. (This fixed the problem for me on my Mac.)


$ 
$ 
$ perl -e "use OTAPI;"
Segmentation fault
$ 
$ 
$ perl5.10.0 -e "use OTAPI;"
$ 
$ 
$  

(Notice, no segfault when I do it the second way -- because I am
running the correct version of perl that time.)

--------------------------------

PHP

make -f Makefile.API [TRANSPORT=XmlRpc] LANGUAGE=php5

This builds OTAPI.so, which you can use in your PHP project via the file OTAPI.php

On linux, make sure you have done this first:
apt-get install php5-dev

--------------------------------

Tcl

make -f Makefile.API [TRANSPORT=XmlRpc] LANGUAGE=tcl

This builds OTAPI.so, which you can use in your Tcl project like so:
load ./OTAPI.so OTAPI

On Linux, I had to install Tcl and Tcl-Dev:
apt-get install tcl
apt-get install tcl-dev

--------------------------------

LISP

make -f Makefile.API [TRANSPORT=XmlRpc] LANGUAGE=lisp

This builds OTAPI.so, which you can use in your LISP project via OTAPI.lisp


