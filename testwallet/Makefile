#
# IMPORTANT:  WHEN USING THIS MAKEFILE, YOU *MUST* USE THE OPTIONS.
# EXAMPLE:
#
# make PLATFORM=linux  TRANSPORT=XmlRpc
# make PLATFORM=darwin TRANSPORT=ssltcp debug
# Etc...
#
# Transport and platform are mandatory.
#
# Platform options are darwin, linux and freebsd (untested)
#
# Language options are c, csharp, java, ruby, python, perl5, php5, 
# tcl, and lisp. 
#

PROGRAM = testwallet.exe
DEBUG_PROGRAM = testwallet.debug


OT_INCLUDEDIRS = \
	-I../OTLib/irrxml \
	-I../OTLib \
	-I./SSL-Example \
	-I.


# The LIBDIRS macro contains a list of library directories
# to pass to the linker so it can find necessary libraries.
#
OT_LIBDIRS = \
	-L../OTLib

PLATFORM_LIBDIRS = #empty
PLATFORM_INCLUDEDIRS = #empty

API_CSOURCES = SSL-Example/SFSocket.c
API_CXXSOURCES = # empty
API_CFLAGS = # empty
API_LDFLAGS = # empty


C_COMPILER = cc

# The LIBS macro contains a list of libraries that the the
# executable must be linked against.
API_LIBS =  -lssl -lcrypto  -lOTLib -lssl -lcrypto  -lOTLib  -lssl -lcrypto -lOTLib  -lssl -lcrypto -lOTLib
API_DEBUG_LIBS = -lssl -lcrypto -lOTLibd -lssl -lcrypto -lOTLibd  -lssl -lcrypto -lOTLibd -lssl -lcrypto -lOTLibd
#
# FT: I tested this. The above version worked on Linux, and the below version did not.
#
#API_LIBS = -lssl  -lcrypto -lOTLib
#API_DEBUG_LIBS =  -lssl -lcrypto  -lOTLibd



# ---------------------------------------------------------------------

# --- DARWIN
#
ifeq ($(PLATFORM), darwin)

PLATFORM_INCLUDEDIRS = -I/usr/local/ssl/include

endif
# End DARWIN -------------------------------------------------------------




ifeq ($(PLATFORM), linux)

PLATFORM_INCLUDEDIRS = -I/usr/local/ssl/include
#PLATFORM_LIBDIRS += -L/usr/local/lib

API_LDFLAGS += -ldl

C_COMPILER = gcc

endif
# End LINUX -------------------------------------------------------------





# --- FreeBSD ----

ifeq ($(PLATFORM), freebsd)

PLATFORM_INCLUDEDIRS = -I/usr/local/include
PLATFORM_LIBDIRS += -L/usr/local/lib
#PLATFORM_LIBDIRS += /usr/ports/security/openssl/work/openssl-1.0.0a
# This one's for you, Ben.
endif
# End FreeBSD -------------------------------------------------------------





# ---------------------------------------------------------------------

# --- TRANSPORT

# This is not a target, but a command-line option.
#
# So you have to do: make PLATFORM=linux TRANSPORT=XmlRpc
#                OR: make PLATFORM=darwin TRANSPORT=XmlRpc debug
#                OR: make PLATFORM=freebsd TRANSPORT=XmlRpc
# 		Etc...
#

XMLRPCPP_INCLUDEDIR = -I../xmlrpcpp/src
XMLRPCPP_LIBDIR = -L../xmlrpcpp/

ifeq ($(TRANSPORT), XmlRpc)
API_CFLAGS += -DOT_XMLRPC_MODE
API_LDFLAGS += -lXmlRpc
PLATFORM_INCLUDEDIRS += $(XMLRPCPP_INCLUDEDIR)
PLATFORM_LIBDIRS += $(XMLRPCPP_LIBDIR)
API_CXXSOURCES += xmlrpcxx_client.cpp
else
API_CXXSOURCES += testclient.cpp
endif



# ---------------------------------------------------------------------
#
# The CSOURCES macro contains a list of source files.
#
# The COBJECTS macro converts the CSOURCES macro into a list
# of object files.
#
# The CFLAGS macro contains a list of options to be passed to
# the compiler.  Adding "-g" to this line will cause the compiler
# to add debugging information to the executable.
#
# The CC macro defines the C compiler.
#
# The LDFLAGS macro contains all of the library and library
# directory information to be passed to the linker.
#

INCLUDEDIRS = $(PLATFORM_INCLUDEDIRS) $(OT_INCLUDEDIRS)


LIBDIRS = $(PLATFORM_LIBDIRS) $(OT_LIBDIRS)

CSOURCES = $(API_CSOURCES)

CXXSOURCES = \
                         OpenTransactions.cpp \
                         OTServerConnection.cpp \
                         OTClient.cpp \
                         $(API_CXXSOURCES)

CXXOBJECTS = $(CXXSOURCES:.cpp=.o)  # expands to list of object files
COBJECTS   = $(CSOURCES:.c=.o)
CFLAGS     = $(INCLUDEDIRS) $(API_CFLAGS) -c
DEBUG_FLAGS = -g
CXX = g++
CC = $(C_COMPILER)

LIBS = $(API_LIBS)
DEBUG_LIBS = $(API_DEBUG_LIBS)


# --- LDFLAGS
#
LDFLAGS = $(API_LDFLAGS) $(LIBDIRS) $(LIBS)
DEBUG_LDFLAGS =  $(API_LDFLAGS) $(LIBDIRS) $(DEBUG_LIBS)





# ---------------------------------------------------------------------

# --- DARWIN
#
ifeq ($(PLATFORM), darwin)
LINK_COMMAND = $(CXX) $(LDFLAGS) -o $(PROGRAM) $(CXXOBJECTS) $(COBJECTS)
DEBUG_LINK_COMMAND = $(CXX) $(DEBUG_LDFLAGS) -o $(DEBUG_PROGRAM) $(CXXOBJECTS) $(COBJECTS)
endif
# End DARWIN -------------------------------------------------------------

ifeq ($(PLATFORM), linux)
LINK_COMMAND = $(CXX) $(CXXOBJECTS) $(COBJECTS) $(LDFLAGS) -o $(PROGRAM)
DEBUG_LINK_COMMAND = $(CXX)  $(CXXOBJECTS) $(COBJECTS) $(DEBUG_LDFLAGS) -o $(DEBUG_PROGRAM)
endif
# End LINUX -------------------------------------------------------------

# --- FreeBSD ----
ifeq ($(PLATFORM), freebsd)
LINK_COMMAND = $(CXX) $(CXXOBJECTS) $(COBJECTS) $(LDFLAGS) -o $(PROGRAM)
DEBUG_LINK_COMMAND = $(CXX)  $(CXXOBJECTS) $(COBJECTS) $(DEBUG_LDFLAGS) -o $(DEBUG_PROGRAM)
endif
# End FreeBSD -------------------------------------------------------------




# ---------------------------------------------------------------------

# --- TARGETS

#
# Default target: the first target is the default target.
# Just type "make PLATFORM=darwin" to build it.
#

$(PROGRAM): $(CXXOBJECTS) $(COBJECTS)
	$(LINK_COMMAND)

all: $(PROGRAM)

debug: CFLAGS += $(DEBUG_FLAGS)
debug: LIBS = $(DEBUG_LIBS)
debug: LDFLAGS = $(DEBUG_LDFLAGS)
debug: $(CXXOBJECTS) $(COBJECTS) 
	$(DEBUG_LINK_COMMAND)


# ---------------------------------------------------------------------


#
# Object targets: rules that define objects, their dependencies, and
# a list of commands for compilation.
#

SFSocket.o: ./SSL-Example/SFSocket.c ./SSL-Example/SFSocket.h
	$(CC) $(CFLAGS) -o ./SSL-Example/SFSocket.o ./SSL-Example/SFSocket.c

OTServerConnection.o: OTServerConnection.cpp OTServerConnection.h
	$(CXX) $(CFLAGS) -o OTServerConnection.o OTServerConnection.cpp
OTClient.o: OTClient.cpp OTClient.h
	$(CXX) $(CFLAGS) -o OTClient.o OTClient.cpp
OpenTransactions.o: OpenTransactions.cpp OpenTransactions.h
	$(CXX) $(CFLAGS) -o OpenTransactions.o OpenTransactions.cpp

xmlrpcxx_client.o: xmlrpcxx_client.cpp
	$(CXX) $(CFLAGS) -o xmlrpcxx_client.o xmlrpcxx_client.cpp

testclient.o: testclient.cpp
	$(CXX) $(CFLAGS) -o testclient.o testclient.cpp

#
# Clean target: "make -f Makefile.API clean" to remove unwanted objects and executables.
#
RM=rm

clean:
	$(RM) -f $(COBJECTS) $(CXXOBJECTS) $(PROGRAM) $(DEBUG_PROGRAM)


# Run target: "make run" to execute the application
#             You will need to add $(VARIABLE_NAME) for any command line parameters 
#             that you defined earlier in this file.
# 

run:
	./$(PROGRAM) 


