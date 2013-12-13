COMP = g++
EDL = g++
RM = rm 
EXE = analog
CLEAN = efface
CPPFLAGS = -std=c++11 -c -Wall
RMFLAGS = -f
INTERFACE = Log.h Commande.h Graph.h 
REAL = $(INTERFACE:.h=.cpp) main.cpp
OBJ = $(INTERFACE:.h=.o) main.o

.PHONY : $(CLEAN)

$(EXE) : $(OBJ)
	$(EDL) -std=c++11 -o $(EXE) $(OBJ)

%.o : %.cpp
	$(COMP) $(CPPFLAGS) $<

$(CLEAN) :
	$(RM) $(RMFLAGS) *.o $(EXE) core
