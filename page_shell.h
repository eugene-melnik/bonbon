#ifndef PAGE_SHELL_H_INCLUDED
#define PAGE_SHELL_H_INCLUDED

#include <gtk/gtk.h>

/* Objects (in XML) */

#define LABEL_ACCESS_NAME               "l_Access"
#define ENTRY_COMMAND_NAME              "e_Shell"
#define BUTTON_EXECUTE_NAME             "b_Execute"
#define TEXT_BUFFER_SHELL_NAME          "text_buffer_Shell"
#define TEXT_VIEW_SHELL_NAME            "text_Shell"

/* Statusbar messages */

#define DONE_MESSAGE                    "Done!"
#define OFFLINE_MESSAGE                 "You are offline!"
#define ENTER_COMMAND_MESSAGE           "Enter command first!"

/* Handlers */

int page_shell_bind(GtkBuilder *);
void b_Execute_clicked(GtkButton *, gpointer);

#endif // PAGE_SHELL_H_INCLUDED

