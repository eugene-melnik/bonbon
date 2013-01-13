#ifndef FUNCS_H_INCLUDED
#define FUNCS_H_INCLUDED

#include <gtk/gtk.h>

/* Files */

#define CONFIG_FILE_NAME        "data/bonbon.conf"

/* Statusbar messages */

#define SOME_ERROR_MESSAGE      "Oops! There is some error here! :)"

/* Global constants */

#define THREAD_STACK_SIZE       64 * 1024 // 64KiB

/* Global variables */

typedef struct global_t {
    char * hostname;
    char * username;
    char * password;
    FILE * main_pipe;
    int auto_connect;
    int is_connected;
    int save_login_data;
    GtkWindow * main_window;
    GtkStatusbar * statusbar;
    GtkBox * resultbox;
    GError * error_msg;
} global_t;

global_t global;

/* Functions */

void show_in_statusbar(const char *);
void entry_edited(GtkEntry *, char **);
int remove_children(GtkContainer *);

#endif // FUNCS_H_INCLUDED

