#include "funcs.h"

#include <stdlib.h>
#include <string.h>

/*****************************************************************************
 *  Entries handler                                                           *
  *****************************************************************************/

void entry_edited(GtkEntry * entry, char ** string)
{
    if (*string != NULL)
    {
        free(*string);
    }

    GtkEntryBuffer * entry_buffer = gtk_entry_get_buffer(entry);
    *string = strdup(gtk_entry_buffer_get_text(entry_buffer));
}

/*****************************************************************************
 *  Remove all child widgets in GtkContainer                                  *
  *****************************************************************************/

int remove_children(GtkContainer * container)
{
    GList * children = gtk_container_get_children(GTK_CONTAINER(container));

    if (children != NULL)
    {
        GList * iterator;

        for (iterator = children; iterator != NULL; iterator = g_list_next(iterator))
        {
            gtk_widget_destroy(GTK_WIDGET(iterator->data));
        }

        g_list_free(children);
    }

    return EXIT_SUCCESS;
}

