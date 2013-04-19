#include "connection.h"
#include "strings.h"
#include "errors.h"
#include "funcs.h"

#include <libssh/libssh.h>
#include <stdlib.h>
#include <string.h>

extern global_t global;

/*****************************************************************************
 *  Creating session and authenticate user.                                   *
  *****************************************************************************/

int open_connection( char* hostname, char* username, char* password )
{
    /* Creating session */
    global.session = ssh_new();
    if( global.session == NULL ) {
        g_warning( STR_ERROR_CREATING_SESSION );
        return( CONNECTION_SESSION_CREATE_ERROR );
    }

    /* Set session properties and try to connect */
    ssh_options_set( global.session, SSH_OPTIONS_HOST, hostname );
    ssh_options_set( global.session, SSH_OPTIONS_USER, username );
    if( ssh_connect( global.session ) != SSH_OK ) {
        g_warning( STR_ERROR_CONNECTION );
        ssh_free( global.session );
        return( CONNECTION_SESSION_CONNECT_ERROR );
    }

    /* Authenticate with keys */
    if( !strcmp( password, EMPTY_STRING ) ) {
        /* FIXME: Don't works. */
        if( ssh_userauth_password( global.session, NULL, NULL ) != SSH_OK ) {
            g_warning( STR_ERROR_AUTHENTICATE );
            ssh_disconnect( global.session );
            ssh_free( global.session );
            return( CONNECTION_SESSION_AUTH_ERROR );
        }
    } else
    /* Authenticate with password */
    if( ssh_userauth_password( global.session, NULL, password ) != SSH_OK ) {
        g_warning( STR_ERROR_AUTHENTICATE_PASS );
        ssh_disconnect( global.session );
        ssh_free( global.session );
        return( CONNECTION_SESSION_AUTH_ERROR );
    }

    return( SUCCESS );
}

/*****************************************************************************
 *  Disconnecting from the remote host.                                       *
  *****************************************************************************/

void close_connection()
{
    ssh_disconnect( global.session );
    ssh_free( global.session );
}

/*****************************************************************************
 *  Opening channel and sending command to the remote host.                   *
  *****************************************************************************/

int execute_command( const char* command, char** result )
{
    /* Creating channel and opening session */
    ssh_channel channel = ssh_channel_new( global.session );
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

/*****************************************************************************
 *  Formatting command and sending it to the remote host.                     *
  *****************************************************************************/

int send_key( const char* key )
{
    char command[ 128 ];
    sprintf( command, "DISPLAY=%s xdotool key %s", global.x_display, key );
    return( execute_command( command, NULL ) );
}

