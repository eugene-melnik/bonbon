#ifndef CONNECTION_H_INCLUDED
#define CONNECTION_H_INCLUDED

#include <stdio.h>

#define COMMAND_BUFFER_SIZE         1024 * sizeof(char)

FILE * open_connection(char *, char *, char *);
void close_connection(FILE *);

char * execute_command(FILE *, const char *);

#endif // CONNECTION_H_INCLUDED

