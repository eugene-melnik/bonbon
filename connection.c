#include "connection.h"

#include <stdlib.h>

FILE * open_connection(char * hostname, char * username, char * password)
{
    char * command = (char *) malloc(COMMAND_BUFFER_SIZE);
    sprintf(command, "ssh %s@%s", username, hostname);

    FILE * pipe = popen(command, "rw");

    free(command);
    return pipe;
}

void close_connection(FILE * pipe)
{
    pclose(pipe);
}

