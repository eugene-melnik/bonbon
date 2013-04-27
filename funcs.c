#include "funcs.h"
#include "strings.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern global_t global;

/*************************************************************************************************
 *  Show text in statusbar.                                                                       *
  *************************************************************************************************/

void show_in_statusbar( const char* message )
{
    gtk_statusbar_pop( global.statusbar, 0 );
    gtk_statusbar_push( global.statusbar, 0, message );
}

/*************************************************************************************************
 *  Show text in statusbar. Extended version.                                                     *
  *************************************************************************************************/

void show_in_statusbar_ext( const char* format, const char* value )
{
    char message[ COMMAND_BUFFER_SIZE ];
    snprintf( message, COMMAND_BUFFER_SIZE, format, value );
    show_in_statusbar( message );
}

/*************************************************************************************************
 *  Entry handler (for text).                                                                     *
  *************************************************************************************************/

void entry_edited( GtkEntry* entry, char** destination )
{
    if( *destination != NULL ) free( *destination );
    GtkEntryBuffer* entry_buffer = gtk_entry_get_buffer( entry );
    *destination = strdup( gtk_entry_buffer_get_text( entry_buffer ) );
}

/*************************************************************************************************
 *  Entry handler (for numbers).                                                                  *
  *************************************************************************************************/

void entry_edited_dig( GtkEntry* entry, int* destination )
{
    GtkEntryBuffer* entry_buffer = gtk_entry_get_buffer( entry );
    *destination = atoi( gtk_entry_buffer_get_text( entry_buffer ) );
}

/*************************************************************************************************
 *  Comboes handler.                                                                              *
  *************************************************************************************************/

void combo_changed( GtkComboBoxText* combobox, char** destination )
{
    if( *destination != NULL ) free( *destination );
    *destination = strdup( gtk_combo_box_text_get_active_text( combobox ) );
    if( !strcmp( *destination, NOTHING_STRING ) ) *destination = NULL;
}

/*************************************************************************************************
 *  Check button handler.                                                                         *
  *************************************************************************************************/

void check_button_activate( GtkCheckButton* button, int* destination )
{
    *destination = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( button ) );
}

/*************************************************************************************************
 *  Remove all child widgets in GtkContainer.                                                     *
  *************************************************************************************************/

void remove_children( GtkContainer* container )
{
    GList* children = gtk_container_get_children( GTK_CONTAINER( container ) );

    if( children != NULL ) {
        for( GList* iter = children; iter != NULL; iter = g_list_next( iter ) ) {
            gtk_widget_destroy( GTK_WIDGET( iter->data ) );
        }

        g_list_free( children );
    }
}

/*************************************************************************************************
 *  Remove last char from the string.                                                             *
  *************************************************************************************************/

void pop_char( char* string )
{
    if( strlen(string) != 0 ) {
        string[ strlen(string) - 1 ] = END_OF_STRING;
    }
}

