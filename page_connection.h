#ifndef PAGE_CONNECTION_H_INCLUDED
#define PAGE_CONNECTION_H_INCLUDED

/* Headers */
#include <gtk/gtk.h>

/* Files */
#define CONFIG_FILE_NAME                "data/bonbon.conf"

/* Objects (in XML) */
#define MAIN_WINDOW_NAME        "main_window"
#define CONNECT_BUTTON_NAME     "b_Connect"
#define BOX_RESULT_NAME         "box_Result"
#define STATUSBAR_NAME          "statusbar"
#define ENTRY_HOSTNAME_NAME     "e_Hostname"
#define ENTRY_USERNAME_NAME     "e_Username"
#define ENTRY_PASSWORD_NAME     "e_Password"
#define CHECK_SAVE_PASS         "check_Save_pass"

#define STOCK_BUTTON_CONNECT    "gtk-connect"
#define STOCK_BUTTON_DISCONNECT "gtk-disconnect"

/* Statusbar messages */
#define READY_MESSAGE           "Ready to party!"
#define INCORRECT_DATA_MESSAGE  "Incorrect data!"
#define CONNECTED_MESSAGE       "Connected."
#define DISCONNECTED_MESSAGE    "Disconnected."

/* Status messages */

#define STATUS_EMPTY_FIELDS     "Status:\nEmpty field(s)!"
#define STATUS_CONNECTED        "Status:\nConnected"
#define STATUS_DISCONNECTED     "Status:\nDisconnected"
#define STATUS_ERROR            "Status:\nError!!!"

/* Handlers */
void page_connection_bind( GtkBuilder* builder );
void on_create( GtkWindow* window, GtkButton* b_Connect );
void on_destroy( GtkWindow* windwow, GtkButton* b_Connect );
void b_Connect_clicked( GtkButton* button, GtkBox* box_Result );
gpointer connect_thread( gpointer button );

#endif // PAGE_CONNECTION_H_INCLUDED

