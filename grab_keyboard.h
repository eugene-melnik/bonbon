#ifndef GRAB_KEYBOARD_H_INCLUDED
#define GRAB_KEYBOARD_H_INCLUDED

#include <gtk/gtk.h>

#define GRAB_WINDOW_NAME                        "grab_window"
#define GRAB_LABEL_NAME                         "label_grab"

typedef struct {
    int  key_code;
    char key_name[16];
} buttons;

void grab_window_bind( GtkBuilder* builder );
gboolean press_event( GtkWidget* widget, GdkEventKey* event, GtkLabel *label );

#endif // GRAB_KEYBOARD_H_INCLUDED

