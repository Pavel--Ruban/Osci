CC = g++ -g -Wall
MANAGERCFLAGS = $(shell pkg-config --cflags --libs  gtkmm-3.0 sqlite3 libnotify) 
BOOSTLIBRATIES = -lboost_system -lboost_thread
MANAGER = main.o window.o
SERVER = asyncServer.o

default : $(MANAGER) $(SERVER)
	$(CC) $(MANAGER) $(SERVER) -o osci_manager $(MANAGERCFLAGS) $(BOOSTLIBRATIES)

main.o : manager/main.cpp manager/window.hpp server/asyncServer.hpp
	$(CC) manager/main.cpp -c $(MANAGERCFLAGS)

window.o : manager/window.cpp manager/window.hpp server/asyncServer.hpp
	$(CC) manager/window.cpp -c $(MANAGERCFLAGS)

asyncServer.o : server/asyncServer.cpp server/asyncServer.hpp
	$(CC) server/asyncServer.cpp -c $(MANAGERCFLAGS)

clean:
	rm -f *.o 
