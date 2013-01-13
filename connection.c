#include "connection.h"

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

FILE * open_connection(char * hostname, char * username, char * password)
{
    char * command = (char *) malloc(COMMAND_BUFFER_SIZE);
    sprintf(command, "ssh -T eugene@pentagon-3 > /dev/null\n");
    FILE * pipe = popen(command, "w");
    sleep(2);

    fputs("DISPLAY=:0.0 xterm &\n", pipe);
    fflush(pipe);
    sleep(2);

    fputs("killall xterm\n", pipe);
    fflush(pipe);

    //fgets(command, COMMAND_BUFFER_SIZE, pipe);
    //printf("%s\n", command);

    //fputs("DISPLAY=:0.0 xdotool key ctrl+alt+Delete\n", pipe);

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

