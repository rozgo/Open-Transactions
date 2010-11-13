#
# The PROGRAM macro defines the name of the program or project.  It
# allows the program name to be changed by editing in only one
# location
#

PROGRAM = transaction.exe  

DEBUG_PROGRAM = transaction.debug



# Find out what platform we're on.
UNAME := $(shell uname -s)

OT_PLATFORM := ___OT_PLATFORM_UNKNOWN___

# I allow the user the option to force-override the build platform.
# Using make PLATFORM=darwin, for example, you will build in darwin mode
# even if you are on a linux box.
#

ifeq ($(PLATFORM), darwin)
UNAME := Darwin
endif
ifeq ($(PLATFORM), linux)
UNAME := Linux
endif
ifeq ($(PLATFORM), freebsd)
UNAME := FreeBSD
endif

ifeq ($(UNAME), Darwin)
OT_PLATFORM := darwin
endif
ifeq ($(UNAME), Linux)
OT_PLATFORM := linux
endif
ifeq ($(UNAME), FreeBSD)
OT_PLATFORM := freebsd
endif


PLATFORM = $(OT_PLATFORM)


LINUX_LIBDIR = lib
LBITS := $(shell getconf LONG_BIT)
ifeq ($(LBITS),64)
LINUX_LIBDIR = lib64
endif

# SSL Folders!

# For Darwin I use /opt instead of /usr, since OpenSSL 1.0.0a is
# installed to that location by MacPorts.
#
ifeq ($(PLATFORM), darwin)
SSL_INCLUDEDIRS = -I/opt/local/include
SSL_LIBDIRS = -L/opt/local/lib
endif

ifeq ($(PLATFORM), linux)
SSL_INCLUDEDIRS = -I/usr/local/ssl/include
SSL_LIBDIRS = -L/usr/local/ssl/$(LINUX_LIBDIR)
endif

ifeq ($(PLATFORM), freebsd)
SSL_INCLUDEDIRS = -I/usr/local/include
SSL_LIBDIRS = -L/usr/local/lib
#SSL_LIBDIRS = -L/usr/ports/security/openssl/work/openssl-1.0.0a
endif


PLATFORM_INCLUDEDIRS = \
	$(SSL_INCLUDEDIRS) \
	-I../OTLib/irrxml \
	-I../OTLib \
	-I./SSL-Example \
	-I./

PLATFORM_LIBDIRS = \
	$(SSL_LIBDIRS) \
	-L../OTLib



XMLRPCPP_INCLUDEDIR = -I../xmlrpcpp/src
XMLRPCPP_LIBDIR = -L../xmlrpcpp/



TRANSPORT_CFLAG = # empty
TRANSPORT_LDFLAG = # empty

ifeq ($(TRANSPORT), XmlRpc)
TRANSPORT_CFLAG += -DOT_XMLRPC_MODE
TRANSPORT_LDFLAG += -lXmlRpc
PLATFORM_INCLUDEDIRS += $(XMLRPCPP_INCLUDEDIR)
PLATFORM_LIBDIRS += $(XMLRPCPP_LIBDIR)
endif

INCLUDEDIRS = $(PLATFORM_INCLUDEDIRS)
LIBDIRS = $(PLATFORM_LIBDIRS)

# I know it seems strange to see the libraries repeated here multiple times. 
# But I found a tip online to do this, and there are definitely build issues
# on linux with at least one of these Makefiles, if you remove the repeats.
# Weird.
ifeq ($(PLATFORM), linux)
LIBS = -ldl $(TRANSPORT_LDFLAG) $(LIBDIRS) -lssl $(LIBDIRS) -lcrypto $(LIBDIRS) -lOTLib $(LIBDIRS) -lssl $(LIBDIRS) -lcrypto $(LIBDIRS) -lOTLib $(LIBDIRS) -lssl $(LIBDIRS) -lcrypto $(LIBDIRS) -lOTLib $(LIBDIRS) -lssl $(LIBDIRS) -lcrypto $(LIBDIRS) -lOTLib

DEBUG_LIBS = -ldl $(TRANSPORT_LDFLAG) $(LIBDIRS) -lssl $(LIBDIRS) -lcrypto $(LIBDIRS) -lOTLibd $(LIBDIRS) -lssl $(LIBDIRS) -lcrypto $(LIBDIRS) -lOTLibd $(LIBDIRS) -lssl $(LIBDIRS) -lcrypto $(LIBDIRS) -lOTLibd $(LIBDIRS) -lssl $(LIBDIRS) -lcrypto $(LIBDIRS) -lOTLibd
else
LIBS = $(TRANSPORT_LDFLAG) $(LIBDIRS) -lssl $(LIBDIRS) -lcrypto $(LIBDIRS) -lOTLib $(LIBDIRS) -lssl $(LIBDIRS) -lcrypto $(LIBDIRS) -lOTLib $(LIBDIRS) -lssl $(LIBDIRS) -lcrypto $(LIBDIRS) -lOTLib $(LIBDIRS) -lssl $(LIBDIRS) -lcrypto $(LIBDIRS) -lOTLib

DEBUG_LIBS = $(TRANSPORT_LDFLAG) $(LIBDIRS) -lssl $(LIBDIRS) -lcrypto $(LIBDIRS) -lOTLibd $(LIBDIRS) -lssl $(LIBDIRS) -lcrypto $(LIBDIRS) -lOTLibd $(LIBDIRS) -lssl $(LIBDIRS) -lcrypto $(LIBDIRS) -lOTLibd $(LIBDIRS) -lssl $(LIBDIRS) -lcrypto $(LIBDIRS) -lOTLibd
endif

#LIBS = $(LIBDIRS) -lOTLib ../OTLib/libssl.a \
#	../OTLib/libcrypto.a
# LIBS = $(LIBDIRS) -lOTLib /home/ben/work/openssl-1.0.0/libssl.a \
#         /home/ben/work/openssl-1.0.0/libcrypto.a

#
# The CXXSOURCES macro contains a list of source files.
#
# The CXXOBJECTS macro converts the CXXSOURCES macro into a list
# of object files.
#
# The CXXFLAGS macro contains a list of options to be passed to
# the compiler.  Adding "-g" to this line will cause the compiler
# to add debugging information to the executable.
#
# The CXX macro defines the C++ compiler.
#
# The LDFLAGS macro contains all of the library and library
# directory information to be passed to the linker.
#

CSOURCES = SSL-Example/SFSocket.c

SERVER_CXXSOURCES = \
	OTClientConnection.cpp \
	OTServer.cpp

ifeq ($(TRANSPORT), XmlRpc)
CXXSOURCES = \
	$(SERVER_CXXSOURCES) \
	xmlrpcxx_server.cpp
else
CXXSOURCES = \
	$(SERVER_CXXSOURCES) \
	testserver.cpp
endif

CXXOBJECTS = $(CXXSOURCES:.cpp=.o)  # expands to list of object files
COBJECTS   = $(CSOURCES:.c=.o)
CXXFLAGS   = $(TRANSPORT_CFLAG) $(INCLUDEDIRS)
CFLAGS     = $(TRANSPORT_CFLAG) $(INCLUDEDIRS)
DEBUG_FLAGS = -g
CXX = g++
CC = gcc


PLATFORM_LDFLAGS = $(LIBDIRS) $(LIBS)
PLATFORM_DEBUG_LDFLAGS = $(LIBDIRS) $(DEBUG_LIBS)

LDFLAGS = $(PLATFORM_LDFLAGS)
DEBUG_LDFLAGS = $(PLATFORM_DEBUG_LDFLAGS) 



#
# Default target: the first target is the default target.
# Just type "make -f Makefile.Linux" to build it.
#

all: $(PROGRAM)

debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: LIBS = $(DEBUG_LIBS)
debug: LDFLAGS = $(DEBUG_LDFLAGS)
debug: $(DEBUG_PROGRAM)


#
# Link target: automatically builds its object dependencies before
# executing its link command.
#

$(DEBUG_PROGRAM): $(CXXOBJECTS) $(COBJECTS) 
	$(CXX) $(CXXOBJECTS) $(COBJECTS) $(DEBUG_LIBS) -o $@

$(PROGRAM): $(CXXOBJECTS) $(COBJECTS) 
	$(CXX) $(CXXOBJECTS) $(COBJECTS) $(LIBS) -o $@

#
# Object targets: rules that define objects, their dependencies, and
# a list of commands for compilation.
#

SSL-Example/SFSocket.o: ./SSL-Example/SFSocket.c ./SSL-Example/SFSocket.h
	$(CC) $(CFLAGS) -c -o ./SSL-Example/SFSocket.o ./SSL-Example/SFSocket.c

OTServer.o: OTServer.cpp OTServer.h
	$(CXX) $(CXXFLAGS) -c -o OTServer.o OTServer.cpp
OTClientConnection.o: OTClientConnection.cpp OTClientConnection.h
	$(CXX) $(CXXFLAGS) -c -o OTClientConnection.o OTClientConnection.cpp

testserver.o: testserver.cpp
	$(CXX) $(CXXFLAGS) -c -o testserver.o testserver.cpp
xmlrpcxx_server.o: xmlrpcxx_server.cpp
	$(CXX) $(CXXFLAGS) -c -o xmlrpcxx_server.o xmlrpcxx_server.cpp


#
# Clean target: "make -f Makefile.Linux clean" to remove unwanted objects and executables.
#

RM=rm

clean:
	$(RM) -f $(CXXOBJECTS) $(COBJECTS) $(PROGRAM) $(DEBUG_PROGRAM)

#
# Run target: "make -f Makefile.Linux run" to execute the application
#             You will need to add $(VARIABLE_NAME) for any command line parameters 
#             that you defined earlier in this file.
# 

run:
	./$(PROGRAM) 


