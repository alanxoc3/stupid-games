######################################################################
# makefile - MISTERSSS
# Since the final program will not be available until months from now
# (16 OCT 2015), this file will simply compile the many tests
# performed on the created classes.
# for the windows compilations, be sure to precede the file name by:
# $W. And Linux is $L.
######################################################################

# B = bin
# W = windows
# L = linux
# S = source
# T = test
# C = standard command (compile object file)
# G = unstandard command (compile executable)

B=bin/
W=bin/windows/
L=bin/linux/
S=src/
T=src/tst/
C=g++ -c -g -Wall -std=c++11 -lGL -lGLEW -lSDL2 -lSOIL -o
G=g++ -g -Wall -std=c++11 -lGL -lGLEW -lSDL2 -lSOIL -o


# Test - 11 Evil Test.
$BevilTest.out : $TevilTest.cpp $Sconstants.h $Lgraphics.o $Linput.o $Ltimer.o $LthingHandler.o $LhelperGL.o $Lview.o $Lrectangle.o $Lgrid.o $LimageHandler.o $Limage.o $Lbackground.o $Lthing.o $Lliving.o $Lplayer.o $Lenemy.o $Lwall.o
	$G $BevilTest.out $TevilTest.cpp $Lgraphics.o $Linput.o $Ltimer.o $LthingHandler.o $LhelperGL.o $Lview.o $Lrectangle.o $Lgrid.o $LimageHandler.o $Limage.o $Lbackground.o $Lthing.o $Lliving.o $Lplayer.o $Lenemy.o $Lwall.o

# Test - 10 New Player Test/Update.
$BnewPlayerTest.out : $Sconstants.h $TnewPlayerTest.cpp $Lgraphics.o $Linput.o $Ltimer.o $LthingHandler.o $LhelperGL.o $Lview.o $Lrectangle.o $Lgrid.o $LimageHandler.o $Limage.o $Lbackground.o $Lthing.o $Lliving.o $Lplayer.o
	$G $BnewPlayerTest.out $TnewPlayerTest.cpp $Lgraphics.o $Linput.o $Ltimer.o $LthingHandler.o $LhelperGL.o $Lview.o $Lrectangle.o $Lgrid.o $LimageHandler.o $Limage.o $Lbackground.o $Lthing.o $Lliving.o $Lplayer.o

# Other Tests deleted. Find them in previous branches.

# Wall Object
$Lwall.o : $Swall.cpp $Swall.h
	$C $Lwall.o $Swall.cpp

# Enemy Object
$Lenemy.o : $Senemy.cpp $Senemy.h $Sconstants.h
	$C $Lenemy.o $Senemy.cpp

# Player Object
$Lplayer.o : $Splayer.cpp $Splayer.h $Sconstants.h
	$C $Lplayer.o $Splayer.cpp

# Living Thing Object
$Lliving.o : $Sliving.cpp $Sliving.h
	$C $Lliving.o $Sliving.cpp

# Thing Object
$Lthing.o : $Sthing.cpp $Sthing.h
	$C $Lthing.o $Sthing.cpp

# Background Object
$Lbackground.o : $Sbackground.cpp $Sbackground.h
	$C $Lbackground.o $Sbackground.cpp

# Image Engine
$Limage.o : $Simage.cpp $Simage.h
	$C $Limage.o $Simage.cpp

# Image Handler
$LimageHandler.o : $SimageHandler.cpp $SimageHandler.h
	$C $LimageHandler.o $SimageHandler.cpp

# Helper Functions for Open GL
$LhelperGL.o : $ShelperGL.cpp $ShelperGL.h
	$C $LhelperGL.o $ShelperGL.cpp

# Thing Handler
$LthingHandler.o : $SthingHandler.cpp $SthingHandler.h
	$C $LthingHandler.o $SthingHandler.cpp

# Graphics Engine
$Lgraphics.o : $Sgraphics.cpp $Sgraphics.h
	$C $Lgraphics.o $Sgraphics.cpp

# View Engine
$Lview.o : $Sview.cpp $Sview.h
	$C $Lview.o $Sview.cpp

# Input Engine
$Linput.o : $Sinput.cpp $Sinput.h
	$C $Linput.o $Sinput.cpp

# Rectangles Engine
$Lrectangle.o : $Srectangle.cpp $Srectangle.h
	$C $Lrectangle.o $Srectangle.cpp

# Grid Engine
$Lgrid.o : $Sgrid.cpp $Sgrid.h
	$C $Lgrid.o $Sgrid.cpp

# Timer Engine
$Ltimer.o : $Stimer.cpp $Stimer.h
	$C $Ltimer.o $Stimer.cpp

clean:
	rm $B*.o $B*.out $L*.o $L*.out
