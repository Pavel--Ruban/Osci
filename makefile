CC = g++ -g -Wall
MANAGERCFLAGS = $(shell pkg-config --cflags --libs  gtkmm-3.0 sqlite3 libnotify) 
#LIBNOTIFYFLAGS = -I/usr/lib/libnotifymm-1.0/include -I/usr/include/libnotifymm-1.0 -I/usr/include/atkmm-1.6 -I/usr/include/gtk-unix-print-2.0  -lnotifymm-1.0 -lfontconfig -lfreetype -lnotify
#LIBNOTIFYFLAGS = -I/usr/lib/libnotifymm-1.0/include -I/usr/include/libnotifymm-1.0 -lnotifymm-1.0 -lnotify
#MANAGERCFLAGS = $(shell pkg-config --cflags --libs  gtkmm-3.0 sqlite3)

MANAGER = main.o window.o
SERVER = server.o

default : $(MANAGER) $(SERVER)
	$(CC) $(MANAGER) $(SERVER) -o osci_manager $(MANAGERCFLAGS) #$(LIBNOTIFYFLAGS)

main.o : manager/main.cpp manager/window.hpp
	$(CC) manager/main.cpp -c $(MANAGERCFLAGS)

window.o : manager/window.cpp manager/window.hpp
	$(CC) manager/window.cpp -c $(MANAGERCFLAGS) #$(LIBNOTIFYFLAGS)

server.o : server/server.cpp server/server.h
	$(CC) server/server.cpp -c

clean:
	rm -f *.o 
