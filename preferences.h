#ifndef PREFERENCES_H_INCLUDED
#define PREFERENCES_H_INCLUDED

#include <gtk/gtk.h>

#define CHECK_SAVE_DATA                         "check_Save_login_data"
#define CHECK_AUTO_LOGIN                        "check_Auto_login"
#define ENTRY_DELAY                             "entry_Delay"
#define ENTRY_X                                 "entry_X"

void preferences_window_bind( GtkBuilder* builder );

#endif // PREFERENCES_H_INCLUDED

