#include <stdlib.h>
#include <string.h>
#include "page_shell.h"
#include "connection.h"
#include "funcs.h"

extern global_t global;
char* string;

GtkEntry* e_Shell;
GtkButton* b_Execute;
GtkTextView* text_Shell;
GtkTextBuffer* text_buffer_Shell;

int page_shell_bind( GtkBuilder* builder )
{
    /* Objects */
    e_Shell = GTK_ENTRY( gtk_builder_get_object( builder, ENTRY_COMMAND_NAME ) );
    b_Execute = GTK_BUTTON( gtk_builder_get_object( builder, BUTTON_EXECUTE_NAME ) );
    text_Shell = GTK_TEXT_VIEW( gtk_builder_get_object( builder, TEXT_VIEW_SHELL_NAME ) );
    text_buffer_Shell = GTK_TEXT_BUFFER( gtk_builder_get_object( builder, TEXT_BUFFER_SHELL_NAME ) );

    /* Signals */
    g_signal_connect( e_Shell, "changed", G_CALLBACK( entry_edited ), &string );
    g_signal_connect( e_Shell, "activate", G_CALLBACK( b_Execute_clicked ), NULL );
    g_signal_connect( b_Execute, "clicked", G_CALLBACK( b_Execute_clicked ), NULL );

    return( EXIT_SUCCESS );
}

void b_Execute_clicked( GtkButton* button, gpointer userdata )
{
    GtkTextIter iter;
    gtk_text_buffer_get_end_iter( text_buffer_Shell, &iter );

    if ( strcmp( string, EMPTY_STRING ) )
    {
        if ( global.is_connected )
        {
            gtk_text_buffer_insert( text_buffer_Shell, &iter, string, -1 );
            gtk_text_buffer_insert( text_buffer_Shell, &iter, END_OF_LINE, -1 );
            show_in_statusbar( DONE_MESSAGE );

            char* str = execute_command( global.main_pipe, string );
            //gtk_text_buffer_insert( text_buffer_Shell, &iter, str, -1 );
            free( str );
        }
        else
        {
            gtk_text_buffer_insert( text_buffer_Shell, &iter, OFFLINE_MESSAGE, -1 );
            gtk_text_buffer_insert( text_buffer_Shell, &iter, END_OF_LINE, -1 );
            show_in_statusbar( OFFLINE_MESSAGE );
        }

        gtk_entry_set_text( GTK_ENTRY( e_Shell ), EMPTY_STRING );
    }
    else
    {
        show_in_statusbar( ENTER_COMMAND_MESSAGE );
    }

    gtk_text_view_scroll_to_iter( GTK_TEXT_VIEW( text_Shell ), &iter, 0.0, FALSE, 0, 0 );
}

