#ifndef PAGE_SHELL_H_INCLUDED
#define PAGE_SHELL_H_INCLUDED

#include <gtk/gtk.h>

#define LABEL_ACCESS_NAME               "l_Access"
#define ENTRY_COMMAND_NAME              "e_Shell"
#define BUTTON_EXECUTE_NAME             "b_Execute"
#define TEXT_BUFFER_SHELL_NAME          "text_buffer_Shell"

int page_shell_bind(GtkBuilder *);
void b_Execute_clicked(GtkButton *, GtkTextBuffer *);

#endif // PAGE_SHELL_H_INCLUDED

