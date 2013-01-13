VERSION = 0.3

CC = gcc
RM = rm -f
CFLAGS = -Wall -Ofast -m64 -flto
LDFLAGS = -s $(shell pkg-config gtk+-3.0 --libs)
GTKCFLAGS = $(shell pkg-config gtk+-3.0 --cflags)

SOURCES = bonbon.c connection.c page_shell.c
OBJS = bonbon.o connection.o page_shell.o

EXECUTABLE = bonbon-$(VERSION)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(EXECUTABLE)

bonbon.o: bonbon.c bonbon.h connection.h page_shell.h
	$(CC) $(CFLAGS) $(GTKCFLAGS) -c bonbon.c

connection.o: connection.c connection.h
	$(CC) $(CFLAGS) -c connection.c

page_shell.o: page_shell.c page_shell.h
	$(CC) $(CFLAGS) -c page_shell.c

clean:
	$(RM) $(OBJS) $(EXECUTABLE)
