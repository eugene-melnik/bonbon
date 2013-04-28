#ifndef PAGE_SHELL_H_INCLUDED
#define PAGE_SHELL_H_INCLUDED

/* Headers */
#include <gtk/gtk.h>

/* Objects (in XML) */
#define LABEL_ACCESS_NAME                       "l_Access"
#define ENTRY_COMMAND_NAME                      "e_Shell"
#define TEXT_BUFFER_SHELL_NAME                  "text_buffer_Shell"
#define TEXT_VIEW_SHELL_NAME                    "text_Shell"

/* Handlers */
void page_shell_bind( GtkBuilder* builder );
void b_Execute_clicked( GtkWidget* widget, gpointer data );

#endif // PAGE_SHELL_H_INCLUDED

