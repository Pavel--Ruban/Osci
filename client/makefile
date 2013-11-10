GTK_INCLUDE = -I/usr/local/include
GTK_LIB = -L/usr/local/lib
X11_LIB = -L/usr/X11R6/lib
CC = gcc -g -Wall
CFLAGS = $(GTK_INCLUDE)
LDFLAGS = $(GTK_LIB) $(X11_LIB) -lgtk -lgdk -lglib -lX11 -lXext -lm

OBJS = gtk.o

helloworld: gtk.o
	$(CC) $(GTK_LIB) $(X11_LIB) $(OBJS) -o gtk $(LDFLAGS)

clean:
	rm -f *.o *~ gtk
