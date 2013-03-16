#ifndef PREFERENCES_H_INCLUDED
#define PREFERENCES_H_INCLUDED

#include <gtk/gtk.h>

/* Objects (in XML) */
#define CHECK_SAVE_DATA                 "check_Save_login_data"
#define CHECK_AUTO_LOGIN                "check_Auto_login"

/* Handlers */
int preferences_window_bind(GtkBuilder *);

#endif // PREFERENCES_H_INCLUDED

