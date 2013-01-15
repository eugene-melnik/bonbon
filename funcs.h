#ifndef FUNCS_H_INCLUDED
#define FUNCS_H_INCLUDED

#include <gtk/gtk.h>

/* Files */

#define CONFIG_FILE_NAME        "data/bonbon.conf"

/* Statusbar messages */

#define SOME_ERROR_MESSAGE      "Oops! There is some error here! :)"

/* Strings */

#define EMPTY_STRING            ""
#define NOTHING_STRING          "-"

/* Global constants */

#define COMMAND_BUFFER_SIZE     2 * 1024 * sizeof(char)  // 2KiB
#define THREAD_STACK_SIZE       64 * 1024  // 64KiB

/* Global variables */

typedef struct global_t {
    char * hostname;
    char * username;
    char * password;
    FILE * main_pipe;
    int auto_connect;
    int is_connected;
    int save_login_data;
    GtkStatusbar * statusbar;
    GError * error_msg;
} global_t;

global_t global;

/* Global functions */

void show_in_statusbar(const char *);
void entry_edited(GtkEntry *, char **);
void combo_changed(GtkComboBoxText *, char **);
void check_button_activate(GtkCheckButton *, int *);
int remove_children(GtkContainer *);

#endif // FUNCS_H_INCLUDED

