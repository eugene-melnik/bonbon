#include "page_connection.h"
#include "connection.h"
#include "strings.h"
#include "config.h"
#include "errors.h"
#include "funcs.h"

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

extern global_t global;

static GtkWindow* main_window = NULL;
static GtkEntry* e_Username = NULL;
static GtkEntry* e_Hostname = NULL;
static GtkEntry* e_Password = NULL;
static GtkToggleButton* c_Save_password = NULL;
static GtkButton* b_Connect = NULL;
static GtkBox* resultbox = NULL;

/*************************************************************************************************
 * Retrieving widgets and connections signals.                                                    *
  *************************************************************************************************/

void page_connection_bind( GtkBuilder* builder )
{
    /* Objects */
    main_window = GTK_WINDOW( gtk_builder_get_object( builder, MAIN_WINDOW_NAME ) );
    e_Username = GTK_ENTRY( gtk_builder_get_object( builder, ENTRY_USERNAME_NAME ) );
    e_Hostname = GTK_ENTRY( gtk_builder_get_object( builder, ENTRY_HOSTNAME_NAME ) );
    e_Password = GTK_ENTRY( gtk_builder_get_object( builder, ENTRY_PASSWORD_NAME ) );
    c_Save_password = GTK_TOGGLE_BUTTON( gtk_builder_get_object( builder, CHECK_SAVE_PASS ) );
    b_Connect = GTK_BUTTON( gtk_builder_get_object( builder, CONNECT_BUTTON_NAME ) );
    resultbox = GTK_BOX( gtk_builder_get_object( builder, BOX_RESULT_NAME ) );
    global.statusbar = GTK_STATUSBAR( gtk_builder_get_object( builder, STATUSBAR_NAME ) );

    /* Signals */
    g_signal_connect( main_window, "show", G_CALLBACK( on_create ), b_Connect );
    g_signal_connect( e_Hostname, "changed", G_CALLBACK( entry_edited ), &global.hostname );
    g_signal_connect( e_Username, "changed", G_CALLBACK( entry_edited ), &global.username );
    g_signal_connect( e_Password, "changed", G_CALLBACK( entry_edited ), &global.password );
    g_signal_connect( c_Save_password, "toggled", G_CALLBACK( check_button_activate ), &global.save_pass );

    /* Actions */
    gtk_widget_grab_focus( GTK_WIDGET( e_Username ) );
    gtk_widget_show_all( GTK_WIDGET( main_window ) );
}

/*************************************************************************************************
 * Loading config and setting global variables.                                                   *
  *************************************************************************************************/

void on_create( GtkWindow* window, GtkButton* b_Connect )
{
    if( load_config( CONFIG_FILE_NAME ) == SUCCESS ) {
        gtk_entry_set_text( e_Hostname, global.hostname );
        gtk_entry_set_text( e_Username, global.username );
        gtk_entry_set_text( e_Password, global.password );
        gtk_toggle_button_set_active( c_Save_password, global.save_pass );
    }

    if( global.auto_connect ) {
        b_Connect_clicked( b_Connect, resultbox );
    }
}

/*************************************************************************************************
 * Disconnecting, saving config and quit.                                                         *
  *************************************************************************************************/

void on_destroy( GtkWindow* window, GtkButton* b_Connect )
{
    if( global.is_connected ) close_connection();
    save_config( CONFIG_FILE_NAME );
    gtk_main_quit();
}

/*************************************************************************************************
 *  Button "Connect/Disconnect" handler                                                           *
  *************************************************************************************************/

void b_Connect_clicked( GtkButton* button, GtkBox* box_Result )
{
    /* Adding spinner on screen */
    gtk_widget_set_sensitive( GTK_WIDGET( b_Connect ), FALSE );
    remove_children( GTK_CONTAINER( box_Result ) );
    GtkWidget* spinner = gtk_spinner_new();
    gtk_box_pack_start( box_Result, spinner, TRUE, TRUE, 5 );
    gtk_spinner_start( GTK_SPINNER( spinner ) );
    gtk_widget_show( spinner );

    /* Connecting in new thread */
    g_thread_new( "connect_thread", connect_thread, (gpointer) b_Connect );
}

/*************************************************************************************************
 *  Connecting/disconnecting                                                                      *
  *************************************************************************************************/

gpointer connect_thread( gpointer button )
{
    GtkWidget* label = NULL;

    if( isempty( global.hostname ) || isempty( global.username ) ) {
        gdk_threads_enter();
        show_in_statusbar( INCORRECT_DATA_MESSAGE );
        label = gtk_label_new( STATUS_EMPTY_FIELDS );
    }
    else if( !global.is_connected ) {
        /* Connecting */
        int result = open_connection( global.hostname, global.username, global.password );
        if( result == SUCCESS ) {
            global.is_connected = TRUE;

            gdk_threads_enter();
            gtk_widget_set_sensitive( GTK_WIDGET( e_Username ), FALSE );
            gtk_widget_set_sensitive( GTK_WIDGET( e_Hostname ), FALSE );
            gtk_widget_set_sensitive( GTK_WIDGET( e_Password ), FALSE );
            gtk_widget_set_sensitive( GTK_WIDGET( c_Save_password ), FALSE );

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
        gtk_widget_set_sensitive( GTK_WIDGET( e_Username ), TRUE );
        gtk_widget_set_sensitive( GTK_WIDGET( e_Hostname ), TRUE );
        gtk_widget_set_sensitive( GTK_WIDGET( e_Password ), TRUE );
        gtk_widget_set_sensitive( GTK_WIDGET( c_Save_password ), TRUE );

        show_in_statusbar( DISCONNECTED_MESSAGE );
        label = gtk_label_new( STATUS_DISCONNECTED );
        gtk_button_set_label( GTK_BUTTON( button ), "gtk-connect" );
    }

    remove_children( GTK_CONTAINER( resultbox ) );
    gtk_box_pack_start( resultbox, label, TRUE, TRUE, 1 );
    gtk_widget_set_sensitive( GTK_WIDGET( button ), TRUE );
    gtk_widget_show_all( GTK_WIDGET( resultbox ) );
    gdk_threads_leave();

    return( NULL );
}

