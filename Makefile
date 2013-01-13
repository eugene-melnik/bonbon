VERSION = 0.4

CC = gcc
RM = rm -f
CFLAGS = -Wall -Ofast -m64 -flto
LDFLAGS = -s $(shell pkg-config gtk+-3.0 --libs)
GTKCFLAGS = $(shell pkg-config gtk+-3.0 --cflags)

SOURCES = bonbon.c funcs.c connection.c page_connection.c page_keyboard.c page_shell.c
OBJS = bonbon.o funcs.o connection.o page_connection.o page_keyboard.o page_shell.o

EXECUTABLE = bonbon-$(VERSION)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(EXECUTABLE)

bonbon.o: bonbon.c bonbon.h funcs.h connection.h page_connection.h page_keyboard.h page_shell.h
	$(CC) $(CFLAGS) $(GTKCFLAGS) -c bonbon.c

funcs.o: funcs.c funcs.h
	$(CC) $(CFLAGS) $(GTKCFLAGS) -c funcs.c

connection.o: connection.c connection.h
	$(CC) $(CFLAGS) -c connection.c

page_connection.o: page_connection.c page_connection.h
	$(CC) $(CFLAGS) $(GTKCFLAGS) -c page_connection.c

page_keyboard.o: page_keyboard.c page_keyboard.h
	$(CC) $(CFLAGS) $(GTKCFLAGS) -c page_keyboard.c

page_shell.o: page_shell.c page_shell.h
	$(CC) $(CFLAGS) $(GTKCFLAGS) -c page_shell.c

clean:
	$(RM) $(OBJS) $(EXECUTABLE)
