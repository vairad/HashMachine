#############################################################################
# Makefile for building: Mastermind
#############################################################################

####### Compiler, tools and options

CXX           = g++
CXXFLAGS      = -O2 -std=c++0x -Wall -W $(DEFINES)
INCPATH       = -I../Mastermind -I. 
LINK          = g++
LFLAGS        = -Wl,-O3 -Wl,-rpath,
DEL           = rm

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = ../HashMachine/main.cpp \
		../HashMachine/sha512.cpp \
		../HashMachine/localcfile.cpp \
		../HashMachine/noalgorithm.cpp \
		../HashMachine/localstdin.cpp 
OBJECTS       = main.o \
		sha512.o \
		localcfile.o \
		noalgorithm.o \
		localstdin.o

DIST          = ifile.h \
		ihashstandard.h \
		localcfile.h \
		sha512.h \
		noalgorithm.h \
		localstdin.h ../HashMachine/main.cpp \
		../HashMachine/sha512.cpp \
		../HashMachine/localcfile.cpp \
		../HashMachine/noalgorithm.cpp \
		../HashMachine/localstdin.cpp

TARGET        = HashMachine


first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

all: $(TARGET)

clean:	
	rm -f *.o

cleanAll:	
	rm -f *.o $(TARGET) *.log
####### Compile

main.o: ../HashMachine/main.cpp ../HashMachine/ifile.h \
		../HashMachine/ihashstandard.h \
		../HashMachine/localcfile.h \
		../HashMachine/sha512.h \
		../HashMachine/noalgorithm.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o ../HashMachine/main.cpp

sha512.o: ../HashMachine/sha512.cpp ../HashMachine/sha512.h \
		../HashMachine/ifile.h \
		../HashMachine/ihashstandard.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o sha512.o ../HashMachine/sha512.cpp

localcfile.o: ../HashMachine/localcfile.cpp ../HashMachine/localcfile.h \
		../HashMachine/ifile.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o localcfile.o ../HashMachine/localcfile.cpp

noalgorithm.o: ../HashMachine/noalgorithm.cpp ../HashMachine/noalgorithm.h \
		../HashMachine/ihashstandard.h \
		../HashMachine/ifile.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o noalgorithm.o ../HashMachine/noalgorithm.cpp

localstdin.o: ../HashMachine/localstdin.cpp ../HashMachine/localstdin.h \
		../HashMachine/ifile.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o localstdin.o ../HashMachine/localstdin.cpp


