#include "connection.h"
#include "strings.h"
#include "errors.h"
#include "funcs.h"

#include <libssh/libssh.h>
#include <stdlib.h>
#include <string.h>

extern global_t global;

int open_connection( char* hostname, char* username, char* password )
{
    /* Creating session */
    if( ( global.session = ssh_new() ) == NULL )
    {
        g_warning( STR_ERROR_CREATING_SESSION );
        return( CONNECTION_SESSION_CREATE_ERROR );
    }

    /* Set session properties and try to connect */
    ssh_options_set( global.session, SSH_OPTIONS_HOST, hostname );
    ssh_options_set( global.session, SSH_OPTIONS_USER, username );

    if( ssh_connect( global.session ) != SSH_OK )
    {
        g_warning( STR_ERROR_CONNECTION );
        ssh_free( global.session );
        return( CONNECTION_SESSION_CONNECT_ERROR );
    }

    /// TODO: Authenticate with keys

    /* Authenticate with password */
    if( ssh_userauth_password( global.session, NULL, password ) != SSH_OK )
    {
        g_warning( STR_ERROR_AUTHENTICATE_PASS );
        ssh_disconnect( global.session );
        ssh_free( global.session );
        return( CONNECTION_SESSION_AUTH_ERROR );
    }

    return( SUCCESS );
}

void close_connection()
{
    ssh_disconnect( global.session );
    ssh_free( global.session );
}

int execute_command( const char* command, char** result )
{
    /* Creating channel and opening session */
    ssh_channel channel = ssh_channel_new( global.session );

    if( channel == NULL )
    {
        g_warning( "Opening channel error..." );
        ssh_disconnect( global.session );
        ssh_free( global.session );
        return( EXECUTE_CHANNEL_OPEN_ERROR );
    }

    if( ssh_channel_open_session( channel ) != SSH_OK )
    {
        g_warning( "Open session error..." );
        ssh_channel_free( channel );
        ssh_disconnect( global.session );
        ssh_free( global.session );
        return( EXECUTE_CHANNEL_OPEN_SESSION_ERROR );
    }

    /* Run command */
    if( ssh_channel_request_exec( channel, command ) != SSH_OK )
    {
        g_warning( "Execute command error! (command = \"%s\")", command );
        return( EXECUTE_ERROR );
    }

    /* Reading results */
    char* buffer = (char*) malloc( RESULT_BUFFER_SIZE );
    ssh_channel_read( channel, buffer, RESULT_BUFFER_SIZE, 0 );
    if( result != NULL ) *result = buffer;

    /* Closing channel */
    ssh_channel_send_eof( channel );
    ssh_channel_close( channel );
    ssh_channel_free( channel );
    return( SUCCESS );
}

int send_key( const char* key )
{
    char command[ COMMAND_BUFFER_SIZE ];
    sprintf( command, "DISPLAY=%s xdotool key %s", global.x_display, key );
    return( execute_command( command, NULL ) );
}

