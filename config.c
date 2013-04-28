#include "config.h"
#include "funcs.h"
#include "errors.h"
#include "strings.h"

#include <stdlib.h>
#include <string.h>

extern global_t global;

/*************************************************************************************************
 * Loading global variables from configuration file.                                              *
  *************************************************************************************************/

int load_config( const char* filename )
{
    /// TODO: Optimize this shit!
    global.hostname = "";
    global.username = "";
    global.password = "";
    global.save_pass = FALSE;
    global.save_login_data = FALSE;
    global.auto_connect = FALSE;
    global.is_connected = FALSE;
    global.x_display = DEFAULT_X_DISPLAY;
    global.send_delay = DEFAULT_SEND_DELAY;

    GKeyFile* keyfile = g_key_file_new();

    if( g_key_file_load_from_file( keyfile, filename, G_KEY_FILE_NONE, &global.error_msg ) ) {
        global.hostname = g_key_file_get_string( keyfile, GROUP_LOGIN, HOSTNAME_CFG, NULL );
        global.username = g_key_file_get_string( keyfile, GROUP_LOGIN, USERNAME_CFG, NULL );
        global.password = g_key_file_get_string( keyfile, GROUP_LOGIN, PASSWORD_CFG, NULL );
        global.x_display = g_key_file_get_string( keyfile, GROUP_PREFS, X_DISPLAY_CFG, NULL );
        global.send_delay = g_key_file_get_integer( keyfile, GROUP_PREFS, SEND_DELAY_CFG, NULL );
        global.save_pass = g_key_file_get_boolean( keyfile, GROUP_PREFS, SAVE_PASS_CFG, NULL );
        global.save_login_data = g_key_file_get_boolean( keyfile, GROUP_PREFS, SAVE_LOGIN_CFG, NULL );
        global.auto_connect = g_key_file_get_boolean( keyfile, GROUP_PREFS, AUTO_CONNECT_CFG, NULL );
    } else {
        g_warning( "%s\n", global.error_msg->message );
        global.error_msg = NULL;
        return( FAILURE );
    }

    return( SUCCESS );
}

/*************************************************************************************************
 * Save variables to the config file.                                                             *
  *************************************************************************************************/

int save_config( const char* filename )
{
    /// TODO: And this one to!
    GKeyFile* keyfile = g_key_file_new();
    g_key_file_set_string( keyfile, GROUP_PREFS, X_DISPLAY_CFG, global.x_display );
    g_key_file_set_integer( keyfile, GROUP_PREFS, SEND_DELAY_CFG, global.send_delay );
    g_key_file_set_boolean( keyfile, GROUP_PREFS, SAVE_LOGIN_CFG, global.save_login_data );
    g_key_file_set_boolean( keyfile, GROUP_PREFS, SAVE_PASS_CFG, global.save_pass );
    g_key_file_set_boolean( keyfile, GROUP_PREFS, AUTO_CONNECT_CFG, global.auto_connect );

    if( global.save_login_data ) {
        g_key_file_set_string( keyfile, GROUP_LOGIN, HOSTNAME_CFG, global.hostname );
        g_key_file_set_string( keyfile, GROUP_LOGIN, USERNAME_CFG, global.username );
    } else {
        g_key_file_set_string( keyfile, GROUP_LOGIN, HOSTNAME_CFG, "" );
        g_key_file_set_string( keyfile, GROUP_LOGIN, USERNAME_CFG, "" );
    }

    if( global.save_pass ) {
        g_key_file_set_string( keyfile, GROUP_LOGIN, PASSWORD_CFG, global.password );
    } else {
        g_key_file_set_string( keyfile, GROUP_LOGIN, PASSWORD_CFG, "" );
    }

    char* config = g_key_file_to_data( keyfile, NULL, &global.error_msg );
    if( config != NULL ) {
        FILE* file = fopen( filename, "w" );
        fwrite( config, sizeof(char), strlen(config), file );
        free( config );
        fclose( file );
    }

    return( SUCCESS );
}

