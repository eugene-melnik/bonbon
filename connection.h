#ifndef CONNECTION_H_INCLUDED
#define CONNECTION_H_INCLUDED

#define CONNECTION_ERROR   0
#define CONNECTION_SUCCESS 1

int open_connection(char *, char *, char *);
int close_connection();

#endif // CONNECTION_H_INCLUDED

