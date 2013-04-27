#ifndef FUNCS_H_INCLUDED
#define FUNCS_H_INCLUDED

/* Headers */
#include <libssh/libssh.h>
#include <gtk/gtk.h>

/* Global constants */
#define COMMAND_BUFFER_SIZE             1024 * sizeof(char)
#define RESULT_BUFFER_SIZE              4096 * sizeof(char)

/* Global variable */
typedef struct {
    char*         hostname;         /* host name or computer's IP */
    char*         username;         /* user's name on remote computer */
    char*         password;         /* user's password */

    char*         x_display;
    int           send_delay;
    int           auto_connect;
    int           is_connected;
    int           save_login_data;
    int           save_pass;

    GError*       error_msg;
    GtkStatusbar* statusbar;
    ssh_session   session;
} global_t;

global_t global;

/* Global functions */
void show_in_statusbar( const char* message );
void show_in_statusbar_ext( const char* format, const char* value );
void entry_edited( GtkEntry* entry, char** destination );
void entry_edited_dig( GtkEntry* entry, int* destination );
void combo_changed( GtkComboBoxText* combobox, char** destination );
void check_button_activate( GtkCheckButton* button, int* destination );
void remove_children( GtkContainer* container );
void pop_char( char* string );

#endif // FUNCS_H_INCLUDED

