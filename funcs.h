#ifndef FUNCS_H_INCLUDED
#define FUNCS_H_INCLUDED

#include <gtk/gtk.h>

/* Gettext */

#include <libintl.h>
#define _(str)                          gettext(str)
#define gettext_noop(str)               str
#define N_(str)                         gettext_noop(str)
#define GETTEXT_PACKAGE                 "bonbon"
#define LOCALEDIR                       "locale"

/* Files */

#define CONFIG_FILE_NAME                "data/bonbon.conf"

/* Statusbar messages */

#define SOME_ERROR_MESSAGE              _("Oops! There is some error here! :)")
#define OFFLINE_MESSAGE                 _("You are offline!")

/* Strings */

#define EMPTY_STRING                    ""
#define NOTHING_STRING                  "-"
#define END_OF_LINE                     "\n"
#define PLUS_S                          "+"

#define END_OF_STRING                   '\0'

/* Global constants */

#define COMMAND_BUFFER_SIZE             2 * 1024 * sizeof(char)  // 2KiB
#define THREAD_STACK_SIZE               64 * 1024  // 64KiB

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

