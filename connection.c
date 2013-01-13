#include "connection.h"

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

FILE * open_connection(char * hostname, char * username, char * password)
{
    char * command = (char *) malloc(COMMAND_BUFFER_SIZE);
    sprintf(command, "ssh -TX %s@%s\n", username, hostname);
    FILE * pipe = popen(command, "w");

    //fputs(password, pipe);

    sleep(1);

    fgets(command, COMMAND_BUFFER_SIZE, pipe);
    printf("%s\n", command);

    //fputs("DISPLAY=:0.0 xdotool key ctrl+alt+Delete\n", pipe);
    fputs("cheese\n", pipe);

    sleep(1);

    fgets(command, COMMAND_BUFFER_SIZE, pipe);
    printf("%s\n", command);

    free(command);
    return pipe;
}

void close_connection(FILE * pipe)
{
    const char * command = "exit";
    fputs(command, pipe);

    char * com = (char *) malloc(COMMAND_BUFFER_SIZE);
    fgets(com, COMMAND_BUFFER_SIZE, pipe);
    printf("%s\n", com);
    free(com);

    pclose(pipe);
}

char * execute_command(FILE * pipe, const char * command)
{
    char * com = (char *) malloc(COMMAND_BUFFER_SIZE);
    fputs(command, pipe);
    fgets(com, COMMAND_BUFFER_SIZE, pipe);

    return com;
}

