CC = gcc
RM = rm -rf
CFLAGS = -Wall -g -std=gnu11
CFLAGS += $(shell pkg-config gtk+-3.0 --cflags)
LDFLAGS = -lssh -lGL -lX11
LDFLAGS += $(shell pkg-config gtk+-3.0 gmodule-2.0 --libs)

SOURCES = bonbon.c funcs.c connection.c page_connection.c page_keyboard.c \
          page_shell.c preferences.c grab_keyboard.h

OBJS = bonbon.o funcs.o connection.o page_connection.o page_keyboard.o \
       page_shell.o preferences.o grab_keyboard.o

EXECUTABLE = bonbon

all: $(LANGS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(EXECUTABLE)

bonbon.o: bonbon.c bonbon.h funcs.h connection.h page_connection.h \
          page_keyboard.h page_shell.h preferences.h errors.h
	$(CC) $(CFLAGS) -c bonbon.c

funcs.o: funcs.c funcs.h strings.h
	$(CC) $(CFLAGS) -c funcs.c

connection.o: connection.c connection.h funcs.h errors.h strings.h
	$(CC) $(CFLAGS) -c connection.c

page_connection.o: page_connection.c page_connection.h funcs.h strings.h
	$(CC) $(CFLAGS) -c page_connection.c

page_keyboard.o: page_keyboard.c page_keyboard.h funcs.h strings.h
	$(CC) $(CFLAGS) -c page_keyboard.c

page_shell.o: page_shell.c page_shell.h funcs.h strings.h
	$(CC) $(CFLAGS) -c page_shell.c

preferences.o: preferences.c preferences.h funcs.h
	$(CC) $(CFLAGS) -c preferences.c

grab_keyboard.o: grab_keyboard.c grab_keyboard.h errors.h
	$(CC) $(CFLAGS) -c grab_keyboard.c

clean:
	$(RM) $(OBJS) $(EXECUTABLE)
