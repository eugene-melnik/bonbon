#include "funcs.h"

#include <stdlib.h>
#include <string.h>

extern global_t global;

/*****************************************************************************
 *  Show text in statusbar                                                    *
  *****************************************************************************/

void show_in_statusbar( const char* message )
{
    gtk_statusbar_pop( global.statusbar, 0 );
    gtk_statusbar_push( global.statusbar, 0, message );
}

/*****************************************************************************
 *  Entries handler                                                           *
  *****************************************************************************/

void entry_edited( GtkEntry* entry, char** destination )
{
    if( *destination != NULL ) {
        free( *destination );
    }

    GtkEntryBuffer* entry_buffer = gtk_entry_get_buffer( entry );
    *destination = strdup( gtk_entry_buffer_get_text( entry_buffer ) );
}

/*****************************************************************************
 *  Combos handler                                                            *
  *****************************************************************************/

void combo_changed( GtkComboBoxText* combobox, char** destination )
{
    if( *destination != NULL ){
        free( *destination );
    }

    *destination = strdup( gtk_combo_box_text_get_active_text( combobox ) );

    if( !strcmp( *destination, NOTHING_STRING ) ) {
        *destination = NULL;
    }
}

/*****************************************************************************
 *  Check button handler                                                      *
  *****************************************************************************/

void check_button_activate( GtkCheckButton* button, int* destination )
{
    *destination = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( button ) );
}

/*****************************************************************************
 *  Remove all child widgets in GtkContainer                                  *
  *****************************************************************************/

void remove_children( GtkContainer* container )
{
    GList* children = gtk_container_get_children( GTK_CONTAINER( container ) );

    if( children != NULL ) {
        for( GList* iterator = children; iterator != NULL; iterator = g_list_next( iterator ) ){
            gtk_widget_destroy( GTK_WIDGET( iterator->data ) );
        }

        g_list_free( children );
    }
}

