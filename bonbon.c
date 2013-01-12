#include "bonbon.h"
#include "connection.h"

#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

/*****************************************************************************
 *  Global variables                                                          *
  *****************************************************************************/

int is_connected = 0;
GtkWidget * statusbar;
char * hostname = NULL;
char * username = NULL;
char * password = NULL;

/*****************************************************************************
 *  Global handlers                                                           *
  *****************************************************************************/

static void b_Connect_clicked(GtkButton *, GtkBox *);

/*****************************************************************************
 *  Entry point                                                               *
  *****************************************************************************/

int main(int argc, char * argv[])
{
    /* GTK initialization */

    gtk_init(&argc, &argv);

    /* Loading widows forms from XML (Glade) file */

    GtkBuilder * builder = gtk_builder_new();
    GError * error_msg = NULL;

    if (!gtk_builder_add_from_file(builder, GLADE_FILE_NAME, &error_msg))
    {
        g_warning("%s\n", error_msg->message);
        return EXIT_FAILURE;
    }

    /* Bindings objects */

    GtkWidget * main_window = GTK_WIDGET(gtk_builder_get_object(builder, MAIN_WINDOW_NAME));
    GtkWidget * b_Connect = GTK_WIDGET(gtk_builder_get_object(builder, CONNECT_BUTTON_NAME));
    GtkWidget * box_Result = GTK_WIDGET(gtk_builder_get_object(builder, BOX_RESULT_NAME));

    statusbar = GTK_WIDGET(gtk_builder_get_object(builder, STATUSBAR_NAME));

    /* Signals */

    gtk_builder_connect_signals(builder, NULL);
    g_signal_connect(b_Connect, "clicked", G_CALLBACK(b_Connect_clicked), box_Result);

    /* Starting */

    gtk_statusbar_push(GTK_STATUSBAR(statusbar), INFO_MESSAGE_ID, READY_MESSAGE);
    g_object_unref(G_OBJECT(builder));
    gtk_widget_show_all(main_window);
    gtk_main();

    return EXIT_SUCCESS;
}

/*****************************************************************************
 *  Button "Connect/Disconnect" handler                                       *
  *****************************************************************************/

static void b_Connect_clicked(GtkButton * button, GtkBox * box_Result)
{
    remove_children(GTK_CONTAINER(box_Result));

    GtkWidget * spinner = gtk_spinner_new();
    gtk_box_pack_start(box_Result, spinner, TRUE, TRUE, 5);
    gtk_spinner_start(GTK_SPINNER(spinner));
    gtk_widget_show(spinner);

    if (!is_connected)
    {
        /* Connecting */

        if (open_connection(hostname, username, password))
        {
            is_connected = TRUE;
            gtk_button_set_label(button, "gtk-disconnect");
            gtk_statusbar_push(GTK_STATUSBAR(statusbar), INFO_MESSAGE_ID, CONNECTED_MESSAGE);
        }
        else
        {
            gtk_statusbar_push(GTK_STATUSBAR(statusbar), ERROR_MESSAGE_ID, SOME_ERROR_MESSAGE);
        }
    }
    else
    {
        /* Disconnecting */

        if (close_connection())
        {
            is_connected = FALSE;
            gtk_button_set_label(button, "gtk-connect");
            gtk_statusbar_push(GTK_STATUSBAR(statusbar), INFO_MESSAGE_ID, DISCONNECTED_MESSAGE);
        }
        else
        {
            gtk_statusbar_push(GTK_STATUSBAR(statusbar), ERROR_MESSAGE_ID, SOME_ERROR_MESSAGE);
        }
    }
}

void remove_children(GtkContainer * container)
{
    GList * children = gtk_container_get_children(GTK_CONTAINER(container));
    GList * iterator;

    for(iterator = children; iterator != NULL; iterator = g_list_next(iterator))
    {
        gtk_widget_destroy(GTK_WIDGET(iterator->data));
    }

    g_list_free(children);
}

