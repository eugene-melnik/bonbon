#include "page_connection.h"
#include "connection.h"
#include "strings.h"
#include "errors.h"
#include "funcs.h"

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

extern global_t global;

GtkWidget* e_Username;
GtkWidget* e_Hostname;
GtkWidget* e_Password;
GtkWidget* b_Connect;
GtkBox* resultbox;

void page_connection_bind( GtkBuilder* builder )
{
    /* Objects */
    GtkWindow* main_window = GTK_WINDOW( gtk_builder_get_object( builder, MAIN_WINDOW_NAME ) );
    b_Connect = GTK_WIDGET( gtk_builder_get_object( builder, CONNECT_BUTTON_NAME ) );
    e_Username = GTK_WIDGET( gtk_builder_get_object( builder, ENTRY_USERNAME_NAME ) );
    e_Hostname = GTK_WIDGET( gtk_builder_get_object( builder, ENTRY_HOSTNAME_NAME ) );
    e_Password = GTK_WIDGET( gtk_builder_get_object( builder, ENTRY_PASSWORD_NAME ) );
    GtkToggleButton* check_Save_pass = GTK_TOGGLE_BUTTON( gtk_builder_get_object( builder, CHECK_SAVE_PASS ) );
    global.statusbar = GTK_STATUSBAR( gtk_builder_get_object( builder, STATUSBAR_NAME ) );
    resultbox = GTK_BOX( gtk_builder_get_object( builder, BOX_RESULT_NAME ) );

    /* Signals */
    g_signal_connect( main_window, "show", G_CALLBACK( on_create ), b_Connect );
    g_signal_connect( e_Hostname, "changed", G_CALLBACK( entry_edited ), &global.hostname );
    g_signal_connect( e_Username, "changed", G_CALLBACK( entry_edited ), &global.username );
    g_signal_connect( e_Password, "changed", G_CALLBACK( entry_edited ), &global.password );
    g_signal_connect( check_Save_pass, "toggled", G_CALLBACK( check_button_activate ), &global.save_pass );

    /* Actions */
    gtk_widget_grab_focus( e_Username );
    gtk_toggle_button_set_active( check_Save_pass, global.save_pass );
    gtk_widget_show_all( GTK_WIDGET( main_window ) );
}

/*****************************************************************************
 * On Create                                                                  *
  *****************************************************************************/

G_MODULE_EXPORT void on_create( GtkWindow* window, GtkButton* b_Connect )
{
    global.save_login_data = FALSE;
    global.save_pass = FALSE;
    global.auto_connect = FALSE;
    global.is_connected = FALSE;
    global.hostname = EMPTY_STRING;
    global.username = EMPTY_STRING;
    global.password = EMPTY_STRING;

    GKeyFile* config_keyfile = g_key_file_new();

    if( g_key_file_load_from_file( config_keyfile, CONFIG_FILE_NAME, G_KEY_FILE_NONE, &global.error_msg ) ) {
        global.x_display = g_key_file_get_string( config_keyfile, GROUP_PREFS, X_DISPLAY_CFG, &global.error_msg );
        global.send_delay = g_key_file_get_integer( config_keyfile, GROUP_PREFS, SEND_DELAY_CFG, &global.error_msg );
        global.save_login_data = g_key_file_get_boolean( config_keyfile, GROUP_PREFS, SAVE_LOGIN_CFG, &global.error_msg );
        global.save_pass = g_key_file_get_boolean( config_keyfile, GROUP_PREFS, SAVE_PASS_CFG, &global.error_msg );
        global.auto_connect = g_key_file_get_boolean( config_keyfile, GROUP_PREFS, AUTO_CONNECT_CFG, &global.error_msg );

        global.hostname = g_key_file_get_string( config_keyfile, GROUP_LOGIN, HOSTNAME_CFG, &global.error_msg );
        global.username = g_key_file_get_string( config_keyfile, GROUP_LOGIN, USERNAME_CFG, &global.error_msg );
        global.password = g_key_file_get_string( config_keyfile, GROUP_LOGIN, PASSWORD_CFG, &global.error_msg );
    }

    gtk_entry_set_text( GTK_ENTRY( e_Hostname ), global.hostname );
    gtk_entry_set_text( GTK_ENTRY( e_Username ), global.username );
    gtk_entry_set_text( GTK_ENTRY( e_Password ), global.password );

    if( global.auto_connect ) {
        b_Connect_clicked( b_Connect, resultbox );
    }
}

/*****************************************************************************
 * On Destroy                                                                 *
  *****************************************************************************/

G_MODULE_EXPORT void on_destroy( GtkWindow* window, GtkButton* b_Connect )
{
    /* Disconnecting */
    if( global.is_connected) {
        close_connection();
    }

    /* Saving config */
    GKeyFile* config_keyfile = g_key_file_new();
    g_key_file_set_string( config_keyfile, GROUP_PREFS, X_DISPLAY_CFG, global.x_display );
    g_key_file_set_integer( config_keyfile, GROUP_PREFS, SEND_DELAY_CFG, global.send_delay );
    g_key_file_set_boolean( config_keyfile, GROUP_PREFS, SAVE_LOGIN_CFG, global.save_login_data );
    g_key_file_set_boolean( config_keyfile, GROUP_PREFS, SAVE_PASS_CFG, global.save_pass );
    g_key_file_set_boolean( config_keyfile, GROUP_PREFS, AUTO_CONNECT_CFG, global.auto_connect );

    if( global.save_login_data ) {
        g_key_file_set_string( config_keyfile, GROUP_LOGIN, HOSTNAME_CFG, global.hostname );
        g_key_file_set_string( config_keyfile, GROUP_LOGIN, USERNAME_CFG, global.username );
    } else {
        g_key_file_set_string( config_keyfile, GROUP_LOGIN, HOSTNAME_CFG, "" );
        g_key_file_set_string( config_keyfile, GROUP_LOGIN, USERNAME_CFG, "" );
    }

    if( global.save_pass ) {
        g_key_file_set_string( config_keyfile, GROUP_LOGIN, PASSWORD_CFG, global.password );
    } else {
        g_key_file_set_string( config_keyfile, GROUP_LOGIN, PASSWORD_CFG, "" );
    }

    char* config = g_key_file_to_data( config_keyfile, NULL, &global.error_msg );
    FILE* f = fopen( CONFIG_FILE_NAME, "w" );
    fwrite( config, 1, strlen(config), f );
    free(config);
    fclose( f );

    /* Exit */
    gtk_main_quit();
}

/*****************************************************************************
 *  Button "Connect/Disconnect" handler                                       *
  *****************************************************************************/

G_MODULE_EXPORT void b_Connect_clicked( GtkButton* button, GtkBox* box_Result )
{
    gtk_widget_set_sensitive( b_Connect, FALSE );
    remove_children( GTK_CONTAINER( box_Result ) );

    /* Adding spinner on screen */
    GtkWidget * spinner = gtk_spinner_new();
    gtk_box_pack_start( box_Result, spinner, TRUE, TRUE, 5 );
    gtk_spinner_start( GTK_SPINNER( spinner ) );
    gtk_widget_show( spinner );

    /* Connecting in new thread */
    g_thread_new( "connect_thread", connect_thread, (gpointer) b_Connect );
}

/*****************************************************************************
 *  Connecting/disconnecting                                                  *
  *****************************************************************************/

gpointer connect_thread( gpointer button )
{
    GtkWidget* label = NULL;

    if( !strcmp( global.hostname, EMPTY_STRING ) || !strcmp( global.username, EMPTY_STRING ) ) {
        gdk_threads_enter();
        show_in_statusbar( INCORRECT_DATA_MESSAGE );
        label = gtk_label_new( STATUS_EMPTY_FIELDS );
    }
    else if( !global.is_connected )
    {
        /* Connecting */
        int result = open_connection( global.hostname, global.username, global.password );

        if( result == SUCCESS )
        {
            global.is_connected = TRUE;

            gdk_threads_enter();

            gtk_widget_set_sensitive( e_Username, FALSE );
            gtk_widget_set_sensitive( e_Hostname, FALSE );
            gtk_widget_set_sensitive( e_Password, FALSE );

            show_in_statusbar( CONNECTED_MESSAGE );
            label = gtk_label_new( STATUS_CONNECTED );
            gtk_button_set_label( GTK_BUTTON( button ), "gtk-disconnect" );
        } else {
            gdk_threads_enter();
            label = gtk_label_new( STATUS_ERROR );

            char* text = SOME_ERROR_MESSAGE;

            switch( result ) {
                case CONNECTION_SESSION_CREATE_ERROR:
                    text = STR_ERROR_CREATING_SESSION; break;
                case CONNECTION_SESSION_CONNECT_ERROR:
                    text = STR_ERROR_CONNECTION; break;
                case CONNECTION_SESSION_AUTH_ERROR:
                    text = STR_ERROR_AUTHENTICATE_PASS; break;
            }

            show_in_statusbar( text );
        }
    } else {
        /* Disconnecting */
        close_connection( global.session );
        global.is_connected = FALSE;

        gdk_threads_enter();

        gtk_widget_set_sensitive( e_Username, TRUE );
        gtk_widget_set_sensitive( e_Hostname, TRUE );
        gtk_widget_set_sensitive( e_Password, TRUE );

        show_in_statusbar( DISCONNECTED_MESSAGE );
        label = gtk_label_new( STATUS_DISCONNECTED );
        gtk_button_set_label( GTK_BUTTON( button ), "gtk-connect" );
    }

    remove_children( GTK_CONTAINER( resultbox ) );
    gtk_box_pack_start( resultbox, GTK_WIDGET( label ), TRUE, TRUE, 1 );
    gtk_widget_show_all( GTK_WIDGET( resultbox ) );
    gtk_widget_set_sensitive( GTK_WIDGET( button ), TRUE );
    gdk_threads_leave();

    return( NULL );
}

