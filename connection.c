#include "connection.h"
#include "funcs.h"

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

FILE * open_connection(char * hostname, char * username, char * password)
{
    char * command = (char *) malloc(COMMAND_BUFFER_SIZE);
    sprintf(command, "ssh -T %s@%s > /dev/null\n", username, hostname);
    FILE * pipe = popen(command, "w");

    if (!strcmp(password, EMPTY_STRING))
    {
        sleep(1);
        fputs(password, pipe);
    }

    free(command);
    return pipe;
}

void close_connection(FILE * pipe)
{
    fputs("exit\n", pipe);
    pclose(pipe);
}

char * execute_command(FILE * pipe, const char * command)
{
    char * com = (char *) malloc(COMMAND_BUFFER_SIZE);
    fputs(command, pipe);
    fputs("&\n", pipe);

    fgets(com, COMMAND_BUFFER_SIZE, pipe);

    return com;
}

