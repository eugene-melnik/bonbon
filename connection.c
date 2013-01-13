#include "connection.h"

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

FILE * open_connection(char * hostname, char * username, char * password)
{
    char * command = (char *) malloc(COMMAND_BUFFER_SIZE);
    sprintf(command, "ssh -T %s@%s\n", username, hostname);
    FILE * pipe = popen(command, "w");

    sleep(1);

    fread(command, sizeof(char), COMMAND_BUFFER_SIZE, pipe);
    printf("%s\n", command);

    sleep(1);

    if (password != NULL)
    {
        fwrite(password, 1, strlen(password), pipe);
    }

    free(command);
    return pipe;
}

void close_connection(FILE * pipe)
{
    const char * command = "exit";
    fwrite(command, sizeof(char), strlen(command), pipe);
    printf("\n");
    pclose(pipe);
}

char * execute_command(const char * command)
{
    return NULL;
}

