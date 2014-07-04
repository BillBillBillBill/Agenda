Agenda : Agenda.o AgendaUI.o AgendaService.o Storage.o Meeting.o User.o Date.o Log.o
	g++ -std=c++0x -o Agenda Agenda.o AgendaUI.o AgendaService.o Storage.o Meeting.o User.o Date.o Log.o

Agenda.o : Agenda.cpp
	g++ -std=c++0x -c Agenda.cpp

AgendaUI.o : AgendaUI.h AgendaUI.cpp
	g++ -std=c++0x -c AgendaUI.cpp

AgendaService.o : AgendaService.h AgendaService.cpp 
	g++ -std=c++0x -c AgendaService.cpp

Log.o : Log.cpp
	g++ -std=c++0x -c Log.cpp

Storage.o : Storage.h Storage.cpp 
	g++ -std=c++0x -c Storage.cpp

Meeting.o : Meeting.h Meeting.cpp 
	g++ -std=c++0x -c Meeting.cpp


User.o : User.h User.cpp
	g++ -std=c++0x -c User.cpp

Date.o : Date.h Date.cpp
	g++ -std=c++0x -c Date.cpp

clean:
	rm -f *.o
