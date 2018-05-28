#=======================================================
#
#  = LIBRARY
#    GI
# 
#  = FILENAME
#    Makefile
#
#  = AUTHOR(S)
#    Alexandre Dupuis
#    Stefan Marconi
#
#  = VERSION
#    $Revision: 1.13 $
#
#  = DATE RELEASED
#    $Date: 2001/11/13 10:56:31 $
#
#  = COPYRIGHT
#    CUI, University of Geneva, Switzerland.
#
#=======================================================

include ../Makefile.def 

LIBS	=	-lMisc -lGI -lX11 -lm

PROGRAM_TEST 	= TestGI
LIBRARY      	= libGI.a

all:  $(LIBRARY) $(PROGRAM_TEST)

# ----------------------------------------
# Program test compilation
# ----------------------------------------

$(PROGRAM_TEST): testGI.o
	$(CC) -o $(PROGRAM_TEST) testGI.o -L../Lib $(LFLAGS) $(LIBS)

testGI.o: testGI.cc $(LIBRARY)
	$(CC) $(CFLAGS) $(INCS) testGI.cc

# ----------------------------------------
# Library compilation
# ----------------------------------------

#	ar -r $(LIBRARY) GraphicsInterface.o Polygon.o Line.o; \
# /usr/local/KAI/KCC.flex-3.4d-1/KCC_BASE/bin/KCC -o $(LIBRARY) 

$(LIBRARY): GraphicsInterface.o	Polygon.o PlotGI.o
	$(MAKELIB) $(LIBRARY) GraphicsInterface.o Polygon.o PlotGI.o; 

GraphicsInterface.o: GraphicsInterface.cc GraphicsInterface.hh
	$(CC) $(CFLAGS) $(INCS) GraphicsInterface.cc

Polygon.o: Polygon.cc Polygon.hh Point.hh
	$(CC) $(CFLAGS) $(INCS) Polygon.cc

PlotGI.o: PlotGI.cc Line.hh Point.hh
	$(CC) $(CFLAGS) $(INCS) PlotGI.cc

Line.o: Line.cc Line.hh Point.hh
	$(CC) $(CFLAGS) $(INCS) Line.cc

Point.o: Point.cc Point.hh
	$(CC) $(CFLAGS) $(INCS) Point.cc

# ----------------------------------------
# Cleaning order
# ----------------------------------------

clean: 
	rm -f *.o $(LIBRARY) $(PROGRAM_TEST)

# ----------------------------------------
# Dependencies
# ----------------------------------------

depend:
	makedepend $(CFLAGS) $(INCS) GraphicsInterface.cc Polygon.cc Line.cc Point.cc testGI.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.

