CC = g++ -g -Wall
CFLAGS = $(shell pkg-config --cflags --libs  gtkmm-3.0)

OBJS = main.o window.o

default : $(OBJS)
	$(CC) $(OBJS) -o manager $(CFLAGS)

main.o : main.cpp window.hpp
	$(CC) main.cpp -c $(CFLAGS)

window.o : window.cpp window.hpp
	$(CC) window.cpp -c $(CFLAGS)

clean:
	rm -f *.o
