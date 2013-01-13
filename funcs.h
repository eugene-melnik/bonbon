#ifndef FUNCS_H_INCLUDED
#define FUNCS_H_INCLUDED

#include <gtk/gtk.h>

typedef struct global_t {
    char * hostname;
    char * username;
    char * password;
    FILE * main_pipe;
    int auto_connect;
    int is_connected;
    int save_login_data;
    GtkStatusbar * statusbar;
    GtkBox * resultbox;
    GError * error_msg;
} global_t;

void entry_edited(GtkEntry *, char **);
int remove_children(GtkContainer *);

#endif // FUNCS_H_INCLUDED

