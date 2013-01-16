#ifndef CONNECTION_H_INCLUDED
#define CONNECTION_H_INCLUDED

#include <stdio.h>

#define LOGIN_SCRIPT                    "ssh -T %s@%s > /dev/null\n" // "#!/usr/bin/expect\nspawn ssh %s@%s\nexpect \"password:\"\nsend %s\nsh\nexit 0"

FILE * open_connection(char *, char *, char *);
void close_connection(FILE *);

char * execute_command(FILE *, const char *);

#endif // CONNECTION_H_INCLUDED

