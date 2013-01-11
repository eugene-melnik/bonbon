VERSION = 0.1

CC = gcc
RM = rm -f
CFLAGS = -Wall -Ofast -m64 -flto $(shell pkg-config gtk+-3.0 --cflags)
LDFLAGS = -s $(shell pkg-config gtk+-3.0 --libs)

SOURCES = bonbon.c

OBJS = bonbon.o

EXECUTABLE = bonbon-$(VERSION)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(EXECUTABLE)

bonbon.o: bonbon.c bonbon.h
	$(CC) $(CFLAGS) -c bonbon.c

clean:
	$(RM) $(OBJS) $(EXECUTABLE)
