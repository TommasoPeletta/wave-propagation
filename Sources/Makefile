ac1d: ac1d.cc
	g++ -O3  -o ac1d -I$(HOME)/SpcTools/Include ac1d.cc -L$(HOME)/SpcTools/Lib -L/usr/X11R6/lib -lMisc -lGI -lX11

spin: spin.cc
	g++ -O3  -o spin -I$(HOME)/SpcTools/Include spin.cc -L$(HOME)/SpcTools/Lib -L/usr/X11R6/lib -lMisc -lGI -lX11

parity: parity.cc
	g++ -O3  -o parity -I$(HOME)/SpcTools/Include parity.cc -L$(HOME)/SpcTools/Lib -L/usr/X11R6/lib -lMisc -lGI -lX11

plotExple: plotExple.cc
	g++ -O3  -o plotExple -I$(HOME)/SpcTools/Include plotExple.cc -L$(HOME)/SpcTools/Lib -L/usr/X11R6/lib  -lGI -lMisc -lX11

wave: 2d_wave_Graphic.cpp
	g++ -O3  -o wave -I$(HOME)/SpcTools/Include 2d_wave_Graphic.cpp -L$(HOME)/SpcTools/Lib -L/usr/X11R6/lib  -lGI -lMisc -lX11

multilayers: tests_multicouches.cc
	g++ -O3  -o multilayers -I$(HOME)/SpcTools/Include  tests_multicouches.cc -L$(HOME)/SpcTools/Lib -L/usr/X11R6/lib  -lGI -lMisc -lX11

clean:
	rm ac1d parity  plotExple spin wave multicouches
