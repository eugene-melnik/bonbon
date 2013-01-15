#include "page_shell.h"
#include "connection.h"
#include "funcs.h"

#include <stdlib.h>

extern global_t global;
char * string;

int page_shell_bind(GtkBuilder * builder)
{
    /* Objects */

    GtkWidget * e_Shell = GTK_WIDGET(gtk_builder_get_object(builder, ENTRY_COMMAND_NAME));
    GtkWidget * b_Execute = GTK_WIDGET(gtk_builder_get_object(builder, BUTTON_EXECUTE_NAME));
    GtkTextBuffer * text_buffer_Shell = GTK_TEXT_BUFFER(gtk_builder_get_object(builder, TEXT_BUFFER_SHELL_NAME));

    /* Signals */

    g_signal_connect(e_Shell, "changed", G_CALLBACK(entry_edited), &string);
    g_signal_connect(e_Shell, "activate", G_CALLBACK(b_Execute_clicked), text_buffer_Shell);
    g_signal_connect(b_Execute, "clicked", G_CALLBACK(b_Execute_clicked), text_buffer_Shell);

    return 0;
}

void b_Execute_clicked(GtkButton * button, GtkTextBuffer * buffer)
{
    GtkTextIter iter;
    gtk_text_buffer_get_end_iter(buffer, &iter);

    if (global.is_connected)
    {
        gtk_text_buffer_insert(buffer, &iter, string, -1);

        char * str = execute_command(global.main_pipe, string);
        gtk_text_buffer_get_end_iter(buffer, &iter);
        gtk_text_buffer_insert(buffer, &iter, str, -1);
        free(str);
        gtk_text_buffer_get_end_iter(buffer, &iter);
        gtk_text_buffer_insert(buffer, &iter, "\n", -1);
    }
    else
    {
        gtk_text_buffer_insert(buffer, &iter, OFFLINE_MESSAGE, -1);
        show_in_statusbar(OFFLINE_MESSAGE);
    }
}

