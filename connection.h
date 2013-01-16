#ifndef CONNECTION_H_INCLUDED
#define CONNECTION_H_INCLUDED

#include <stdio.h>

#define LOGIN_SCRIPT "#!/usr/bin/expect"
                     "spawn ssh %s@%s"
                     "expect \"password:\""
                     "send %s"
                     "sh"
                     "exit 0"

FILE * open_connection(char *, char *, char *);
void close_connection(FILE *);

char * execute_command(FILE *, const char *);

#endif // CONNECTION_H_INCLUDED

