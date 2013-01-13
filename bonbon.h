#ifndef BONBON_H_INCLUDED
#define BONBON_H_INCLUDED

/* Files */

#define GLADE_FILE_NAME         "./data/bonbon.glade"
#define CONFIG_FILE_NAME        "./data/bonbon.conf"

/* Objects (in XML) */

#define MAIN_WINDOW_NAME        "main_window"
#define CONNECT_BUTTON_NAME     "b_Connect"
#define BOX_RESULT_NAME         "box_Result"
#define STATUSBAR_NAME          "statusbar"
#define ENTRY_HOSTNAME_NAME     "e_Hostname"
#define ENTRY_USERNAME_NAME     "e_Username"
#define ENTRY_PASSWORD_NAME     "e_Password"

/* Statusbar messages */

#define INFO_MESSAGE_ID         0
#define WARNING_MESSAGE_ID      1
#define ERROR_MESSAGE_ID        2

#define READY_MESSAGE           "Ready to party!"
#define INCORRECT_DATA_MESSAGE  "Incorrect data!"
#define CONNECTED_MESSAGE       "Connected."
#define DISCONNECTED_MESSAGE    "Disconnected."
#define SOME_ERROR_MESSAGE      "Oops! There is some error here! :)"

#define THREAD_STACK_SIZE       128 * 1024 // 128KiB

#endif // BONBON_H_INCLUDED

