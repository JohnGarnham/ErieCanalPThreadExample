#
# Created by gmakemake (Sparc Aug  2 2007) on Sun Oct 28 12:52:53 2007
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c

########## Flags from header.mak

########## flags settings for multi-threading (from header.mak file)
#
# C++ pthreads multithreading with g++ compiler on Solaris (10)
#
# $Id: header.mak,v 1.2 2006/10/18 18:03:04 bks Exp $
#
# $Log: header.mak,v $
# Revision 1.2  2006/10/18 18:03:04  bks
# added -lrt switch
#
# Revision 1.1  2006/10/06 23:13:07  bks
# Initial revision
#
#
# @author bks
#
CXXFLAGS =	-ggdb
CFLAGS =	-ggdb
CLIBFLAGS =	-lm 
CCLIBFLAGS =	-lrt -lpthread
#
########## end flags settings (from header.mak file)


########## End of flags from header.mak


CPP_FILES =	Car.cpp ErieCanalMonitor.cpp simulation.cpp
C_FILES =	
S_FILES =	
H_FILES =	Car.h ErieCanalMonitor.h diagnostics.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	Car.o ErieCanalMonitor.o 

#
# Main targets
#

all:	simulation 

simulation:	simulation.o $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o simulation simulation.o $(OBJFILES) $(CCLIBFLAGS)

#
# Dependencies
#

Car.o:	Car.h ErieCanalMonitor.h
ErieCanalMonitor.o:	ErieCanalMonitor.h
simulation.o:	Car.h ErieCanalMonitor.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm $(OBJFILES) simulation.o core 2> /dev/null

realclean:        clean
	-/bin/rm -rf simulation 
