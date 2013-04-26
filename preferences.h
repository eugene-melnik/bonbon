#ifndef PREFERENCES_H_INCLUDED
#define PREFERENCES_H_INCLUDED

/* Headers */
#include <gtk/gtk.h>

/* Objects (in XML) */
#define CHECK_SAVE_DATA                 "check_Save_login_data"
#define CHECK_SAVE_PASS                 "check_Save_pass"
#define CHECK_AUTO_LOGIN                "check_Auto_login"
#define ENTRY_DELAY                     "entry_Delay"
#define ENTRY_X                         "entry_X"

/* Handlers */
void preferences_window_bind( GtkBuilder* builder );

#endif // PREFERENCES_H_INCLUDED

