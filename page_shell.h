#ifndef PAGE_SHELL_H_INCLUDED
#define PAGE_SHELL_H_INCLUDED

#include <gtk/gtk.h>

#define LABEL_ACCESS_NAME                       "l_Access"
#define ENTRY_COMMAND_NAME                      "e_Shell"
#define TEXT_BUFFER_SHELL_NAME                  "text_buffer_Shell"
#define TEXT_VIEW_SHELL_NAME                    "text_Shell"

void page_shell_bind( GtkBuilder* builder );
void b_Execute_clicked( GtkWidget* widget, gpointer data );
void on_page_select( GtkNotebook* notebook, gpointer data );

#endif // PAGE_SHELL_H_INCLUDED

