COMP = g++
EDL = g++
RM = rm 
ANALOG = analog
CLEAN = efface
CPPFLAGS = g++ -std=c++1 -c
RMFLAGS = -f

analog : Log.o Graph.o main.o
	g++ -std=c++11 -o analog main.o Graph.o Log.o

main.o : main.cpp Log.h Graph.h
	g++ -std=c++11 -c main.cpp

Graph.o : Graph.cpp Graph.h Log.h
	g++ -std=c++11 -c Graph.cpp


Log.o : Log.h Log.cpp
	g++ -std=c++11 -c Log.cpp

efface :
	rm -f *.o analog core