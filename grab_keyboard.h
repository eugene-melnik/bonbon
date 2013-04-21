#ifndef GRAB_KEYBOARD_H_INCLUDED
#define GRAB_KEYBOARD_H_INCLUDED

/* Headers */
#include <gtk/gtk.h>

/* Objects (in XML) */
#define GRAB_WINDOW_NAME        "grab_window"
#define GRAB_LABEL_NAME         "label_grab"

typedef struct {
    int  key_code;
    char key_name[16];
} buttons;

/* Handlers */
void grab_window_bind( GtkBuilder* builder );
G_MODULE_EXPORT gboolean press_event( GtkWidget* widget, GdkEventKey* event, GtkLabel *label );

#endif // GRAB_KEYBOARD_H_INCLUDED

