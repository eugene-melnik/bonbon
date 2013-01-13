#include "page_shell.h"
#include "funcs.h"

char string[100];

int page_shell_bind(GtkBuilder * builder)
{
    //GtkWidget * l_Access = GTK_WIDGET(gtk_builder_get_object(builder, LABEL_ACCESS_NAME));
    GtkWidget * e_Shell = GTK_WIDGET(gtk_builder_get_object(builder, ENTRY_COMMAND_NAME));
    GtkWidget * b_Execute = GTK_WIDGET(gtk_builder_get_object(builder, BUTTON_EXECUTE_NAME));

    g_signal_connect(e_Shell, "changed", G_CALLBACK(entry_edited), &string);
    g_signal_connect(b_Execute, "clicked", G_CALLBACK(b_Execute_clicked), string);

    return 0;
}

void b_Execute_clicked(GtkButton * button, char * string)
{
    //
}

