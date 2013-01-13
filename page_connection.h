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

int page_connection_bind(GtkBuilder *);

void on_create(GtkWindow *, gpointer);
void on_destroy(GtkWindow *, gpointer);
void b_Connect_clicked(GtkButton *, GtkBox *);

void * connect_thread(void *);

#endif // PAGE_CONNECTION_H_INCLUDED

