#=======================================================
#
#  = LIBRARY
#    Misc
# 
#  = FILENAME
#    Makefile
#
#  = AUTHOR(S)
#    Alexandre Dupuis
#    Stefan Marconi
#
#  = VERSION
#    $Revision: 1.10 $
#
#  = DATE RELEASED
#    $Date: 2001/11/13 10:00:23 $
#
#  = COPYRIGHT
#    University of Geneva, Switzerland.
#
#=======================================================

include ../Makefile.def

LIBS	=	-lMisc -lm


PROGRAM_TEST = TestMisc
LIBRARY      = libMisc.a

all:  $(LIBRARY) $(PROGRAM_TEST)

# ----------------------------------------
# Program test compilation
# ----------------------------------------

$(PROGRAM_TEST): testMisc.o $(LIBRARY)
	$(CC) -o $(PROGRAM_TEST) testMisc.o $(LFLAGS) -L./ $(LIBS) 

testMisc.o: testMisc.cc
	$(CC) $(CFLAGS) $(INCS) testMisc.cc	

# ----------------------------------------
# Library compilation
# ----------------------------------------

#

$(LIBRARY): String.o  Random.o IntPow.o RandomS.o
	$(MAKELIB) $(LIBRARY) String.o  \
	Random.o IntPow.o RandomS.o ; \

String.o: String.cc String.hh
	$(CC) $(CFLAGS) $(INCS) String.cc

Matrix.o: Matrix.cc Matrix.hh Vector.hh
	$(CC) $(CFLAGS) $(INCS) Matrix.cc

Vector.o: Vector.cc Vector.hh
	$(CC) $(CFLAGS) $(INCS) Vector.cc

List.o: List.cc List.hh
	$(CC) $(CFLAGS) $(INCS) List.cc

Cell.o: Cell.cc Cell.hh
	$(CC) $(CFLAGS) $(INCS) Cell.cc

Random.o: Random.cc Random.hh
	$(CC) $(CFLAGS) $(INCS) Random.cc

RandomS.o: RandomS.cc RandomS.hh
	$(CC) $(CFLAGS) $(INCS) RandomS.cc

IntPow.o: IntPow.cc IntPow.hh
	$(CC) $(CFLAGS) $(INCS) IntPow.cc

# ----------------------------------------
# Cleaning order
# ----------------------------------------

clean: 
	rm -f *.o $(LIBRARY) $(PROGRAM_TEST)

# ----------------------------------------
# Dependencies
# ----------------------------------------

depend:
	makedepend $(CFLAGS) $(INCS) String.cc TString.cc Random.cc IntPow.cc RandomS.cc testMisc.cc


# DO NOT DELETE THIS LINE -- make depend depends on it.

