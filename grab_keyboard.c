#include "grab_keyboard.h"
#include "connection.h"

#include <gdk/gdkkeysyms.h>

void grab_window_bind( GtkBuilder* builder )
{
    /* Objects */
    //GtkWindow* grab_window = GTK_WINDOW( gtk_builder_get_object( builder, GRAB_WINDOW_NAME ) );
}

G_MODULE_EXPORT gboolean press_event( GtkWidget* widget, GdkEventKey* event, gpointer data )
{
    buttons b[] = { { GDK_KEY_Return,    "Return"    },
                    { GDK_KEY_Left,      "Left"      },
                    { GDK_KEY_Up,        "Up"        },
                    { GDK_KEY_Right,     "Right"     },
                    { GDK_KEY_Down,      "Down"      },
                    { GDK_KEY_Escape,    "Escape"    },
                    { GDK_KEY_BackSpace, "BackSpace" },
                    { GDK_KEY_Shift_L,   "shift"     } };

    const int b_count = sizeof(b) / sizeof(buttons);

    for( int i = 0; i < b_count; i++ ) {
        if( event->keyval == b[i].key_code ) {
            send_key( b[i].key_name );
        }
    }

    return FALSE;
}

