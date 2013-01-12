#include "connection.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int open_connection(char * hostname, char * username, char * password)
{
    printf("opening connection...\n");
    sleep(3);
    printf("ok!\n");

    return CONNECTION_SUCCESS;
}

int close_connection()
{
    printf("closing connection...\n");
    sleep(3);
    printf("ok!\n");

    return CONNECTION_SUCCESS;
}

