#ifndef PAGE_CONNECTION_H_INCLUDED
#define PAGE_CONNECTION_H_INCLUDED

#include <gtk/gtk.h>

/* Objects (in XML) */
#define MAIN_WINDOW_NAME        "main_window"
#define CONNECT_BUTTON_NAME     "b_Connect"
#define BOX_RESULT_NAME         "box_Result"
#define STATUSBAR_NAME          "statusbar"
#define ENTRY_HOSTNAME_NAME     "e_Hostname"
#define ENTRY_USERNAME_NAME     "e_Username"
#define ENTRY_PASSWORD_NAME     "e_Password"

#define GROUP_PREFS             "Preferences"
#define GROUP_LOGIN             "Login"
#define SAVE_LOGIN_CFG          "save_login_data"
#define AUTO_CONNECT_CFG        "auto_connect"
#define USERNAME_CFG            "username"
#define HOSTNAME_CFG            "hostname"
#define PASSWORD_CFG            "password"

/* Statusbar messages */
#define READY_MESSAGE           _("Ready to party!")
#define INCORRECT_DATA_MESSAGE  _("Incorrect data!")
#define CONNECTED_MESSAGE       _("Connected.")
#define DISCONNECTED_MESSAGE    _("Disconnected.")

#define STATUS_EMPTY_FIELDS     _("Status:\nEmpty field(s)!")
#define STATUS_CONNECTED        _("Status:\nConnected")
#define STATUS_DISCONNECTED     _("Status:\nDisconnected")
#define STATUS_ERROR            _("Status:\nError!!!")

/* Handlers */
int page_connection_bind(GtkBuilder *);
void on_create(GtkWindow *, GtkButton *);
void on_destroy(GtkWindow *, GtkButton *);
void b_Connect_clicked(GtkButton *, GtkBox *);
void * connect_thread(void *);

#endif // PAGE_CONNECTION_H_INCLUDED

