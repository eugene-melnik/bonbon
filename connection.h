#ifndef CONNECTION_H_INCLUDED
#define CONNECTION_H_INCLUDED

#include <stdio.h>

#define LOGIN_SCRIPT                    "ssh -TX %s@%s > /dev/null\n"

FILE * open_connection(char *, char *, char *);
void close_connection(FILE *);

char * execute_command(FILE *, const char *);
int send_key(FILE *, const char *);

#endif // CONNECTION_H_INCLUDED

