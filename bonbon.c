#include "page_connection.h"
#include "page_keyboard.h"
#include "grab_keyboard.h"
#include "preferences.h"
#include "aboutdialog.h"
#include "page_shell.h"
#include "connection.h"
#include "errors.h"
#include "funcs.h"
#include "bonbon.h"
#include "ui.h"

#include <gtk/gtk.h>
#include <string.h>

global_t global;

void show_version()
{
    g_print( "Program: %s\n"
             "Version: %s\n", PROGRAM_NAME, PROGRAM_VERSION );
}

void show_using()
{
    g_print( "Using: bonbon [-v||--version]\n"
             "\t-v || --version\tshow bonbon version and exit\n" );
}

int main( int argc, char** argv )
{
    if( argc == 2 )
    {
        if( strcmp( argv[1], "-v" ) == 0 || strcmp( argv[1], "--version" ) == 0 )
        {
            show_version();
            return( SUCCESS );
        }
    }
    else if( argc != 1 )
    {
        g_print( "Error! Unknown argument: \"%s\"\n", argv[1] );
        show_using();
        return( SUCCESS );
    }

    gdk_threads_init();
    gtk_init( &argc, &argv );
    GtkBuilder* builder = gtk_builder_new();

    if( !gtk_builder_add_from_string( builder, ui, -1, &global.error_msg ) ) {
        g_warning( "%s\n", global.error_msg->message );
        global.error_msg = NULL;
        return( BUILDER_LOAD_FAIL );
    }

    page_connection_bind( builder );
    page_keyboard_bind( builder );
    page_shell_bind( builder );
    grab_window_bind( builder );
    preferences_window_bind( builder );
    aboutdialog_bind( builder );

    gtk_builder_connect_signals( builder, NULL );
    show_in_statusbar( READY_MESSAGE );
    g_object_unref( builder );
    gtk_main();

    return( SUCCESS );
}

