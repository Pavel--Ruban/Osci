CC = g++ -g -Wall

# Headers & libraries.
BOOSTLIBS = -lboost_system -lboost_thread

MANAGERCFLAGS = $(shell pkg-config --cflags  gtkmm-3.0 sqlite3)
MANAGERLIBS = $(shell pkg-config --libs  gtkmm-3.0 sqlite3)

LIBNOTIFYFLAGS = $(shell pkg-config --cflags libnotify)
LIBNOTIFYLIBS = $(shell pkg-config --libs libnotify)

DEFAULTLIBS = $(MANAGERLIBS) $(LIBNOTIFYLIBS) $(BOOSTLIBS)

# Used object files.
MANAGER = main.o window.o window_tools.o window_events.o
SERVER = asyncServer.o

# Default rule to built whole application.
default : $(MANAGER) $(SERVER)
	$(CC) $(MANAGER) $(SERVER) -o osci_manager $(DEFAULTLIBS)

main.o : manager/main.cpp manager/window.hpp server/asyncServer.hpp
	$(CC) manager/main.cpp -c $(MANAGERCFLAGS)

window_tools.o : manager/window_tools.cpp manager/window.hpp
	$(CC) manager/window_tools.cpp -c $(MANAGERCFLAGS)

window_events.o : manager/window_events.cpp manager/window.hpp
	$(CC) manager/window_events.cpp -c $(MANAGERCFLAGS) $(LIBNOTIFYFLAGS)

window.o : manager/window.cpp manager/window.hpp
	$(CC) manager/window.cpp -c $(MANAGERCFLAGS)

asyncServer.o : server/asyncServer.cpp server/asyncServer.hpp
	$(CC) server/asyncServer.cpp -c $(MANAGERCFLAGS)

clean:
	rm -f *.o
