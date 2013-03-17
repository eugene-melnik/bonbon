CC = gcc
RM = rm -rf
CFLAGS = -Wall -g $(shell pkg-config gtk+-3.0 --cflags)
LDFLAGS = $(shell pkg-config gtk+-3.0 --libs)

SOURCES = bonbon.c funcs.c connection.c page_connection.c page_keyboard.c \
          page_shell.c preferences.c

OBJS = bonbon.o funcs.o connection.o page_connection.o page_keyboard.o \
       page_shell.o preferences.o

EXECUTABLE = bonbon

all: $(LANGS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(EXECUTABLE)

bonbon.o: bonbon.c bonbon.h funcs.h connection.h page_connection.h \
          page_keyboard.h page_shell.h preferences.h
	$(CC) $(CFLAGS) -c bonbon.c

funcs.o: funcs.c funcs.h
	$(CC) $(CFLAGS) -c funcs.c

connection.o: connection.c connection.h funcs.h
	$(CC) $(CFLAGS) -c connection.c

page_connection.o: page_connection.c page_connection.h funcs.h
	$(CC) $(CFLAGS) -c page_connection.c

page_keyboard.o: page_keyboard.c page_keyboard.h funcs.h
	$(CC) $(CFLAGS) -c page_keyboard.c

page_shell.o: page_shell.c page_shell.h funcs.h
	$(CC) $(CFLAGS) -c page_shell.c

preferences.o: preferences.c preferences.h funcs.h
	$(CC) $(CFLAGS) -c preferences.c

clean:
	$(RM) $(OBJS) $(EXECUTABLE)
