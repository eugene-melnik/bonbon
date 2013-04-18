#ifndef PAGE_CONNECTION_H_INCLUDED
#define PAGE_CONNECTION_H_INCLUDED

/* Headers */
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
#define X_DISPLAY_CFG           "x_display"
#define SEND_DELAY_CFG          "send_delay"

#define GROUP_LOGIN             "Login"
#define SAVE_LOGIN_CFG          "save_login_data"
#define AUTO_CONNECT_CFG        "auto_connect"
#define USERNAME_CFG            "username"
#define HOSTNAME_CFG            "hostname"
#define PASSWORD_CFG            "password"

/* Statusbar messages */
#define READY_MESSAGE           "Ready to party!"
#define INCORRECT_DATA_MESSAGE  "Incorrect data!"
#define CONNECTED_MESSAGE       "Connected."
#define DISCONNECTED_MESSAGE    "Disconnected."

#define STATUS_EMPTY_FIELDS     "Status:\nEmpty field(s)!"
#define STATUS_CONNECTED        "Status:\nConnected"
#define STATUS_DISCONNECTED     "Status:\nDisconnected"
#define STATUS_ERROR            "Status:\nError!!!"

/* Handlers */
void page_connection_bind( GtkBuilder* builder );
G_MODULE_EXPORT void on_create( GtkWindow* window, GtkButton* b_Connect );
G_MODULE_EXPORT void on_destroy( GtkWindow* windwow, GtkButton* b_Connect );
G_MODULE_EXPORT void b_Connect_clicked( GtkButton* button, GtkBox* box_Result );
gpointer connect_thread( gpointer button );

#endif // PAGE_CONNECTION_H_INCLUDED

