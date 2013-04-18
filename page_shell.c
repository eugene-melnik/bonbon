#include "page_shell.h"
#include "connection.h"
#include "funcs.h"

#include <stdlib.h>
#include <string.h>

extern global_t global;

char* command = NULL;
GtkEntry* e_Shell = NULL;
GtkTextView* text_Shell = NULL;
GtkTextBuffer* text_buffer_Shell = NULL;

void page_shell_bind( GtkBuilder* builder )
{
    /* Objects */
    e_Shell = GTK_ENTRY( gtk_builder_get_object( builder, ENTRY_COMMAND_NAME ) );
    text_Shell = GTK_TEXT_VIEW( gtk_builder_get_object( builder, TEXT_VIEW_SHELL_NAME ) );
    text_buffer_Shell = GTK_TEXT_BUFFER( gtk_builder_get_object( builder, TEXT_BUFFER_SHELL_NAME ) );

    /* Signals */
    g_signal_connect( e_Shell, "changed", G_CALLBACK( entry_edited ), &command );
}

G_MODULE_EXPORT void b_Execute_clicked( GtkWidget* widget, gpointer data )
{
    if( global.is_connected ) {
        GtkTextIter iter;
        gtk_text_buffer_get_end_iter( text_buffer_Shell, &iter );

        if ( strcmp( command, EMPTY_STRING ) ) {
            if ( global.is_connected ) {
                gtk_text_buffer_insert( text_buffer_Shell, &iter, command, -1 );
                gtk_text_buffer_insert( text_buffer_Shell, &iter, END_OF_LINE, -1 );
                show_in_statusbar( DONE_MESSAGE );

                char* result;
                execute_command( command, &result );
                /** FIXME: There is a little bug here */
                gtk_text_buffer_insert( text_buffer_Shell, &iter, result, -1 );
                free( result );
            } else {
                gtk_text_buffer_insert( text_buffer_Shell, &iter, OFFLINE_MESSAGE, -1 );
                gtk_text_buffer_insert( text_buffer_Shell, &iter, END_OF_LINE, -1 );
                show_in_statusbar( OFFLINE_MESSAGE );
            }

            gtk_entry_set_text( GTK_ENTRY( e_Shell ), EMPTY_STRING );
        } else {
            show_in_statusbar( ENTER_COMMAND_MESSAGE );
        }

        gtk_text_view_scroll_to_iter( GTK_TEXT_VIEW( text_Shell ), &iter, 0.0, FALSE, 0.0, 0.0 );
    } else {
        show_in_statusbar( OFFLINE_MESSAGE );
    }
}

