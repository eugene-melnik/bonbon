#ifndef ERRORS_H_INCLUDED
#define ERRORS_H_INCLUDED

/** Global codes **/
#define SUCCESS                                 0
#define FAILURE                                -1

/** bonbon.c : main() **/
#define BUILDER_LOAD_FAIL                       1

/** connection.c : open_connection() **/
#define CONNECTION_SESSION_CREATE_ERROR         2
#define CONNECTION_SESSION_CONNECT_ERROR        3
#define CONNECTION_SESSION_AUTH_ERROR           4

/** connection.c : execute_command() **/
#define EXECUTE_CHANNEL_OPEN_ERROR              5
#define EXECUTE_CHANNEL_OPEN_SESSION_ERROR      6
#define EXECUTE_ERROR                           7

#endif // ERRORS_H_INCLUDED
