#include <stdlib.h>
#include <string.h>
#include "funcs.h"

extern global_t global;

void show_in_statusbar( const char* str )
{
    gtk_statusbar_push( global.statusbar, 0, str );
}

/*****************************************************************************
 *  Entries handler                                                           *
  *****************************************************************************/

void entry_edited( GtkEntry* entry, char** string )
{
    if( *string != NULL )
    {
        free( *string );
    }

    GtkEntryBuffer* entry_buffer = gtk_entry_get_buffer( entry );
    *string = strdup( gtk_entry_buffer_get_text( entry_buffer ) );
}

/*****************************************************************************
 *  Combos handler                                                            *
  *****************************************************************************/

void combo_changed( GtkComboBoxText* combobox, char** string )
{
    if( *string != NULL )
    {
        free( *string );
    }

    *string = strdup( gtk_combo_box_text_get_active_text( combobox ) );

    if( !strcmp( *string, NOTHING_STRING ) )
    {
        *string = NULL;
    }
}

/*****************************************************************************
 *  Check button handler                                                      *
  *****************************************************************************/

void check_button_activate( GtkCheckButton* button, int* res )
{
    *res = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( button ) );
}

/*****************************************************************************
 *  Remove all child widgets in GtkContainer                                  *
  *****************************************************************************/

int remove_children( GtkContainer* container )
{
    GList* children = gtk_container_get_children( GTK_CONTAINER( container ) );

    if( children != NULL )
    {
        GList* iterator;

        for( iterator = children; iterator != NULL; iterator = g_list_next( iterator ) )
        {
            gtk_widget_destroy( GTK_WIDGET( iterator->data ) );
        }

        g_list_free( children );
    }

    return( EXIT_SUCCESS );
}

