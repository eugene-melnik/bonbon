#include "bonbon.h"
#include "connection.h"

#include <gtk/gtk.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

/*****************************************************************************
 *  Global variables                                                          *
  *****************************************************************************/

static GtkWidget * statusbar;
static char * hostname = NULL;
static char * username = NULL;
static char * password = NULL;
static int is_connected = FALSE;

/*****************************************************************************
 *  Global handlers, functions and threads                                    *
  *****************************************************************************/

static void b_Connect_clicked(GtkButton *, GtkBox *);
static void entry_edited(GtkEntry *, char *);

int remove_children(GtkContainer *);

void * connect_thread(void *);

/*****************************************************************************
 *  Entry point                                                               *
  *****************************************************************************/

int main(int argc, char * argv[])
{
    /* GTK initialization */

    gdk_threads_init();
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

    GtkWidget * e_Hostname = GTK_WIDGET(gtk_builder_get_object(builder, "e_Hostname"));
    GtkWidget * e_Username = GTK_WIDGET(gtk_builder_get_object(builder, "e_Username"));
    GtkWidget * e_Password = GTK_WIDGET(gtk_builder_get_object(builder, "e_Password"));

    statusbar = GTK_WIDGET(gtk_builder_get_object(builder, STATUSBAR_NAME));

    /* Signals */

    gtk_builder_connect_signals(builder, NULL);

    g_signal_connect(b_Connect, "clicked", G_CALLBACK(b_Connect_clicked), box_Result);

    g_signal_connect(e_Hostname, "changed", G_CALLBACK(entry_edited), hostname);
    g_signal_connect(e_Username, "changed", G_CALLBACK(entry_edited), username);
    g_signal_connect(e_Password, "changed", G_CALLBACK(entry_edited), password);

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

    /* Adding spinner on screen */

    GtkWidget * spinner = gtk_spinner_new();
    gtk_box_pack_start(box_Result, spinner, TRUE, TRUE, 5);
    gtk_spinner_start(GTK_SPINNER(spinner));
    gtk_widget_show(spinner);

    gtk_widget_set_sensitive(GTK_WIDGET(button), FALSE);

    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, THREAD_STACK_SIZE);
    pthread_create(&tid, &attr, connect_thread, (void *) button);
}

/*****************************************************************************
 *  Entries handler ("Hostame", "Username", "Password")                       *
  *****************************************************************************/

static void entry_edited(GtkEntry * entry, char * string)
{
    GtkEntryBuffer * entry_buffer = gtk_entry_get_buffer(entry);
    string = strdup(gtk_entry_buffer_get_text(entry_buffer));
}

/*****************************************************************************
 *  Remove all child widgets in GtkContainer                                  *
  *****************************************************************************/

int remove_children(GtkContainer * container)
{
    GList * children = gtk_container_get_children(GTK_CONTAINER(container));
    GList * iterator;

    for(iterator = children; iterator != NULL; iterator = g_list_next(iterator))
    {
        gtk_widget_destroy(GTK_WIDGET(iterator->data));
    }

    g_list_free(children);
    return EXIT_SUCCESS;
}

/*****************************************************************************
 *  thread                                                                    *
  *****************************************************************************/

void * connect_thread(void * button)
{
    if (!is_connected)
    {
        /* Connecting */

        if (open_connection(hostname, username, password))
        {
            is_connected = TRUE;

            gdk_threads_enter();
            gtk_widget_set_sensitive(GTK_WIDGET(button), TRUE);
            gtk_button_set_label(GTK_BUTTON(button), "gtk-disconnect");
            gtk_statusbar_push(GTK_STATUSBAR(statusbar), INFO_MESSAGE_ID, CONNECTED_MESSAGE);
            gdk_threads_leave();
        }
        else
        {
            gdk_threads_enter();
            gtk_statusbar_push(GTK_STATUSBAR(statusbar), ERROR_MESSAGE_ID, SOME_ERROR_MESSAGE);
            gdk_threads_leave();
        }
    }
    else
    {
        /* Disconnecting */

        if (close_connection())
        {
            is_connected = FALSE;

            gdk_threads_enter();
            gtk_widget_set_sensitive(GTK_WIDGET(button), TRUE);
            gtk_button_set_label(GTK_BUTTON(button), "gtk-connect");
            gtk_statusbar_push(GTK_STATUSBAR(statusbar), INFO_MESSAGE_ID, DISCONNECTED_MESSAGE);
            gdk_threads_leave();
        }
        else
        {
            gdk_threads_enter();
            gtk_statusbar_push(GTK_STATUSBAR(statusbar), ERROR_MESSAGE_ID, SOME_ERROR_MESSAGE);
            gdk_threads_leave();
        }
    }

    return 0;
}

