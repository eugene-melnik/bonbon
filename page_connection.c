#include "page_connection.h"
#include "connection.h"
#include "funcs.h"

extern global_t global;

int page_connection_bind(GtkBuilder * builder)
{
    GtkWidget * b_Connect = GTK_WIDGET(gtk_builder_get_object(builder, CONNECT_BUTTON_NAME));
    GtkWidget * e_Hostname = GTK_WIDGET(gtk_builder_get_object(builder, ENTRY_HOSTNAME_NAME));
    GtkWidget * e_Username = GTK_WIDGET(gtk_builder_get_object(builder, ENTRY_USERNAME_NAME));
    GtkWidget * e_Password = GTK_WIDGET(gtk_builder_get_object(builder, ENTRY_PASSWORD_NAME));
    global.main_window = GTK_WINDOW(gtk_builder_get_object(builder, MAIN_WINDOW_NAME));
    global.statusbar = GTK_STATUSBAR(gtk_builder_get_object(builder, STATUSBAR_NAME));
    global.resultbox = GTK_BOX(gtk_builder_get_object(builder, BOX_RESULT_NAME));

    g_signal_connect(global.main_window, "show", G_CALLBACK(on_create), NULL);
    g_signal_connect(global.main_window, "destroy", G_CALLBACK(on_destroy), NULL);
    g_signal_connect(b_Connect, "clicked", G_CALLBACK(b_Connect_clicked), global.resultbox);
    g_signal_connect(e_Hostname, "changed", G_CALLBACK(entry_edited), &global.hostname);
    g_signal_connect(e_Username, "changed", G_CALLBACK(entry_edited), &global.username);
    g_signal_connect(e_Password, "changed", G_CALLBACK(entry_edited), &global.password);

    return 0;
}

/*****************************************************************************
 * On Create                                                                  *
  *****************************************************************************/

void on_create(GtkWindow * window, gpointer user_data)
{
    GKeyFile * config_keyfile = g_key_file_new();

    if (g_key_file_load_from_file(config_keyfile, CONFIG_FILE_NAME,
                                  G_KEY_FILE_NONE, &global.error_msg))
    {
        //
    }
    else
    {
        global.hostname = NULL;
        global.username = NULL;
        global.password = NULL;
    }

    global.is_connected = FALSE;
}

/*****************************************************************************
 * On Destroy                                                                 *
  *****************************************************************************/

void on_destroy(GtkWindow * window, gpointer user_data)
{
    gtk_main_quit();
}

/*****************************************************************************
 *  Button "Connect/Disconnect" handler                                       *
  *****************************************************************************/

void b_Connect_clicked(GtkButton * button, GtkBox * box_Result)
{
    gtk_widget_set_sensitive(GTK_WIDGET(button), FALSE);
    remove_children(GTK_CONTAINER(box_Result));

    /* Adding spinner on screen */

    GtkWidget * spinner = gtk_spinner_new();
    gtk_box_pack_start(box_Result, spinner, TRUE, TRUE, 5);
    gtk_spinner_start(GTK_SPINNER(spinner));
    gtk_widget_show(spinner);

    /* Connectin in new thread */

    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, THREAD_STACK_SIZE);
    pthread_create(&tid, &attr, connect_thread, (void *) button);
}

/*****************************************************************************
 *  Connecting/disconnecting thread                                           *
  *****************************************************************************/

void * connect_thread(void * button)
{
    GtkWidget * label = NULL;

    if ((global.hostname == NULL) || (global.username == NULL))
    {
        gdk_threads_enter();
        show_in_statusbar(INCORRECT_DATA_MESSAGE);
        label = gtk_label_new("Status:\nEmpty field(s)!");
    }
    else if (!global.is_connected)
    {
        /* Connecting */

        if ((global.main_pipe = open_connection(global.hostname, global.username, global.password)) != NULL)
        {
            global.is_connected = TRUE;

            gdk_threads_enter();
            show_in_statusbar(CONNECTED_MESSAGE);
            label = gtk_label_new("Status:\nConnected");
            gtk_button_set_label(GTK_BUTTON(button), "gtk-disconnect");
        }
        else
        {
            gdk_threads_enter();
            label = gtk_label_new("Status:\nError!!!");
            show_in_statusbar(SOME_ERROR_MESSAGE);
        }
    }
    else
    {
        /* Disconnecting */

        close_connection(global.main_pipe);
        global.is_connected = FALSE;

        gdk_threads_enter();
        show_in_statusbar(DISCONNECTED_MESSAGE);
        label = gtk_label_new("Status:\nDisconnected");
        gtk_button_set_label(GTK_BUTTON(button), "gtk-connect");
    }

    remove_children(GTK_CONTAINER(global.resultbox));
    gtk_box_pack_start(global.resultbox, GTK_WIDGET(label), TRUE, TRUE, 1);
    gtk_widget_show_all(GTK_WIDGET(global.resultbox));
    gtk_widget_set_sensitive(GTK_WIDGET(button), TRUE);
    gdk_threads_leave();

    return NULL;
}

