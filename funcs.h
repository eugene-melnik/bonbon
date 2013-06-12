#ifndef FUNCS_H_INCLUDED
#define FUNCS_H_INCLUDED

#include <libssh/libssh.h>
#include <gtk/gtk.h>

/* Global */
#define COMMAND_BUFFER_SIZE                     1024 * sizeof(char)
#define RESULT_BUFFER_SIZE                      4096 * sizeof(char)

typedef struct {
    char*         hostname;
    char*         username;
    char*         password;

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

void show_in_statusbar( const char* message );
void show_in_statusbar_ext( const char* format, const char* value );
void entry_edited( GtkEntry* entry, char** destination );
void entry_edited_dig( GtkEntry* entry, int* destination );
void combo_changed( GtkComboBoxText* combobox, char** destination );
void check_button_activate( GtkCheckButton* button, int* destination );
void remove_children( GtkContainer* container );
int isempty( const char* string );
void pop_char( char* string );

#endif // FUNCS_H_INCLUDED

