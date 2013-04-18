#include "connection.h"
#include "errors.h"
#include "funcs.h"

#include <libssh/libssh.h>
#include <stdlib.h>
#include <string.h>

extern global_t global;
ssh_channel channel;

int open_connection( char* hostname, char* username, char* password )
{
    /* Creating session */
    global.session = ssh_new();
    if( global.session == NULL ) {
        g_warning( "Error while creating session..." );
        return( CONNECTION_SESSION_CREATE_ERROR );
    }

    /* Set session properties and try to connect */
    ssh_options_set( global.session, SSH_OPTIONS_HOST, hostname );
    ssh_options_set( global.session, SSH_OPTIONS_USER, username );
    if( ssh_connect( global.session ) != SSH_OK ) {
        g_warning( "Error while connecting..." );
        ssh_free( global.session );
        return( CONNECTION_SESSION_CONNECT_ERROR );
    }

    /* Authenticate with keys */
    if( !strcmp( password, EMPTY_STRING ) ) {
        if( ssh_userauth_password( global.session, NULL, NULL ) != SSH_OK ) {
            g_warning( "Authentication error (without password)..." );
            ssh_disconnect( global.session );
            ssh_free( global.session );
            return( CONNECTION_SESSION_AUTH_ERROR );
        }
    } else
    /* Authenticate with password */
    if( ssh_userauth_password( global.session, NULL, password ) != SSH_OK ) {
        g_warning( "Authentication error..." );
        ssh_disconnect( global.session );
        ssh_free( global.session );
        return( CONNECTION_SESSION_AUTH_ERROR );
    }

    return( SUCCESS );
}

void close_connection()
{
    /* Closing connection */
    ssh_disconnect( global.session );
    ssh_free( global.session );
}

int execute_command( const char* command, char** result )
{
    /* Opening channel and session in it */
    channel = ssh_channel_new( global.session );
    if( channel == NULL ) {
        g_warning( "Opening channel error..." );
        ssh_disconnect( global.session );
        ssh_free( global.session );
        return( EXECUTE_CHANNEL_OPEN_ERROR );
    }

    if( ssh_channel_open_session( channel ) != SSH_OK ) {
        g_warning( "Open session error..." );
        ssh_channel_free( channel );
        ssh_disconnect( global.session );
        ssh_free( global.session );
        return( EXECUTE_CHANNEL_OPEN_SESSION_ERROR );
    }

    /* Run command */
    if( ssh_channel_request_exec( channel, command ) != SSH_OK ) {
        g_warning( "Execute command error! (command = \"%s\")", command );
        return( EXECUTE_ERROR );
    }

    /* Reading results */
    char* buffer = (char*) malloc( 2048 );
    ssh_channel_read( channel, buffer, 2048, 0 );
    if( result != NULL ) *result = buffer;

    /* Closing channel */
    ssh_channel_send_eof( channel );
    ssh_channel_close( channel );
    ssh_channel_free( channel );
    return( SUCCESS );
}

int send_key( const char* key )
{
    char command[ 128 ];
    sprintf( command, "DISPLAY=%s xdotool key %s", global.x_display, key );
    return( execute_command( command, NULL ) );
}

