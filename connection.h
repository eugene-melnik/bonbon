#ifndef CONNECTION_H_INCLUDED
#define CONNECTION_H_INCLUDED

/* Headers */
#include <stdio.h>

/* Handlers */
int open_connection( char* hostname, char* username, char* password );
void close_connection();

int execute_command( const char* command, char** result );
int send_key( const char* key );

#endif // CONNECTION_H_INCLUDED

