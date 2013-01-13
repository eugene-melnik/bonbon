#ifndef CONNECTION_H_INCLUDED
#define CONNECTION_H_INCLUDED

#include <stdio.h>

#define CONNECTION_ERROR   0
#define CONNECTION_SUCCESS 1

#define COMMAND_BUFFER_SIZE     1024 * sizeof(char)

FILE * open_connection(char *, char *, char *);
void close_connection(FILE *);

char * execute_command(FILE *, const char *);

#endif // CONNECTION_H_INCLUDED

