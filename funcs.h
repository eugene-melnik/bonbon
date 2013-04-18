#ifndef FUNCS_H_INCLUDED
#define FUNCS_H_INCLUDED

/* Headers */
#include <libssh/libssh.h>
#include <gtk/gtk.h>

/* Files */
#define CONFIG_FILE_NAME                "data/bonbon.conf"

/* Statusbar messages */
#define SOME_ERROR_MESSAGE              "Oops! There is some error here! :)"
#define OFFLINE_MESSAGE                 "You are offline!"

/* Strings */
#define EMPTY_STRING                    ""
#define NOTHING_STRING                  "-"
#define END_OF_LINE                     "\n"
#define END_OF_STRING                   '\0'

/* Global constants */
#define COMMAND_BUFFER_SIZE             1024 * sizeof(char)  // 1KiB

/* Global variables */
typedef struct {
    char*         hostname;         /* host name or computer's IP */
    char*         username;         /* user's name on remote computer */
    char*         password;         /* user's password */

    char*         x_display;
    int           send_delay;
    int           auto_connect;
    int           is_connected;
    int           save_login_data;
    GError*       error_msg;
    GtkStatusbar* statusbar;
    ssh_session   session;
} global_t;

global_t global;

/* Global functions */
void show_in_statusbar( const char* message );
void entry_edited( GtkEntry* entry, char** destination );
void combo_changed( GtkComboBoxText* combobox, char** destination );
void check_button_activate( GtkCheckButton* button, int* destination );
void remove_children( GtkContainer* container );

#endif // FUNCS_H_INCLUDED

