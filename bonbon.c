#include "bonbon.h"

#include <gtk/gtk.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
    /* GTK initialization */

    gtk_init(&argc, &argv);

    /* Loading widows forms from XML (Glade) file */

    GtkBuilder * builder = gtk_builder_new();
    GError * error_msg = NULL;

    if (!gtk_builder_add_from_file(builder, GLADE_FILE, &error_msg))
    {
        g_warning("%s\n", error_msg->message);
        return EXIT_FAILURE;
    }

    GtkWidget * main_window = GTK_WIDGET(gtk_builder_get_object(builder, MAIN_WINDOW_NAME));

    /* Starting */

    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(G_OBJECT(builder));
    gtk_widget_show_all(main_window);
    gtk_main();

    return EXIT_SUCCESS;
}

