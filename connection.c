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

    if (password != NULL)
    {
        sleep(2);
        fputs(password, pipe);
        fflush(pipe);
    }

    free(command);
    return pipe;
}

void close_connection(FILE * pipe)
{
    const char * command = "exit\n";
    fputs(command, pipe);
    pclose(pipe);
}

char * execute_command(FILE * pipe, const char * command)
{
    char * com = (char *) malloc(COMMAND_BUFFER_SIZE);
    fputs(command, pipe);
    fgets(com, COMMAND_BUFFER_SIZE, pipe);

    return com;
}

