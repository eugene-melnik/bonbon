#include "funcs.h"
#include "strings.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern global_t global;

void show_in_statusbar( const char* message )
{
    gtk_statusbar_pop( global.statusbar, 0 );
    gtk_statusbar_push( global.statusbar, 0, message );
}

void show_in_statusbar_ext( const char* format, const char* value )
{
    char message[ COMMAND_BUFFER_SIZE ];
    snprintf( message, COMMAND_BUFFER_SIZE, format, value );
    show_in_statusbar( message );
}

void entry_edited( GtkEntry* entry, char** destination )
{
    if( *destination != NULL ) free( *destination );
    GtkEntryBuffer* entry_buffer = gtk_entry_get_buffer( entry );
    *destination = strdup( gtk_entry_buffer_get_text( entry_buffer ) );
}

void entry_edited_dig( GtkEntry* entry, int* destination )
{
    GtkEntryBuffer* entry_buffer = gtk_entry_get_buffer( entry );
    *destination = atoi( gtk_entry_buffer_get_text( entry_buffer ) );
}

void combo_changed( GtkComboBoxText* combobox, char** destination )
{
    if( *destination != NULL ) free( *destination );
    *destination = strdup( gtk_combo_box_text_get_active_text( combobox ) );
    if( strcmp( *destination, "-" ) == 0 ) *destination = NULL;
}

void check_button_activate( GtkCheckButton* button, int* destination )
{
    *destination = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( button ) );
}

void remove_children( GtkContainer* container )
{
    GList* children = gtk_container_get_children( GTK_CONTAINER( container ) );

    if( children != NULL )
    {
        for( GList* iter = children; iter != NULL; iter = g_list_next( iter ) )
        {
            gtk_widget_destroy( GTK_WIDGET( iter->data ) );
        }

        g_list_free( children );
    }
}

int isempty( const char* string )
{
    if( string[0] == '\0' )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void pop_char( char* string )
{
    if( strlen(string) != 0 )
    {
        string[ strlen(string) - 1 ] = '\0';
    }
}

