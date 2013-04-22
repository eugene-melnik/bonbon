#include "grab_keyboard.h"
#include "connection.h"
#include "strings.h"
#include "funcs.h"

#include <gdk/gdkkeysyms.h>
#include <string.h>

GtkLabel* label_grab;

void grab_window_bind( GtkBuilder* builder )
{
    /* Objects */
    //GtkWindow* grab_window = GTK_WINDOW( gtk_builder_get_object( builder, GRAB_WINDOW_NAME ) );
    label_grab = GTK_LABEL( gtk_builder_get_object( builder, GRAB_LABEL_NAME ) );
}

G_MODULE_EXPORT gboolean press_event( GtkWidget* widget, GdkEventKey* event, GtkLabel *label )
{
    char command[ 30 ] = "";

    /* Modificators */
    if( event->state & GDK_SHIFT_MASK ) {
        strcat( command, "shift+" );
    }
    if( event->state & GDK_CONTROL_MASK ) {
        strcat( command, "ctrl+" );
    }

    /* Main buttons */
    buttons b[] = { { GDK_KEY_Return,    "Return"    }, { GDK_KEY_Home,      "Home"      },
                    { GDK_KEY_Left,      "Left"      }, { GDK_KEY_End,       "End"       },
                    { GDK_KEY_Up,        "Up"        }, { GDK_KEY_Delete,    "Delete"    },
                    { GDK_KEY_Right,     "Right"     }, { GDK_KEY_Insert,    "Insert"    },
                    { GDK_KEY_Down,      "Down"      }, { GDK_KEY_Page_Up,   "Page_Up"   },
                    { GDK_KEY_Escape,    "Escape"    }, { GDK_KEY_Page_Down, "Page_Down" },
                    { GDK_KEY_BackSpace, "BackSpace" }, { GDK_KEY_Menu,      "Menu"      },
                    { GDK_KEY_space,     "space"     }, { GDK_KEY_Tab,       "Tab"       },
                    { GDK_KEY_Alt_L,     "alt"       }, { GDK_KEY_Super_L,   "super"     } };

    const int b_count = sizeof(b) / sizeof(buttons);
    for( int i = 0; i < b_count; i++ ) {
        if( event->keyval == b[i].key_code ) {
            strcat( command, b[i].key_name );
        }
    }

    /* Chars and digits */
    for( int i = GDK_KEY_a; i <= GDK_KEY_z; i++ ) {
        if( ( event->keyval == i ) || ( event->keyval == (i - 0x20) ) ) {
            sprintf( command, "%s%c", command, (char) i );
        }
    }
    for( int i = GDK_KEY_0; i <= GDK_KEY_9; i++ ) {
        if( event->keyval == i ) {
            sprintf( command, "%s%c", command, (char) i );
        }
    }
    for( int i = GDK_KEY_F1; i <= GDK_KEY_F12; i++ ) {
        if( event->keyval == i ) {
            sprintf( command, "%sF%i", command, (i - GDK_KEY_F1 + 1) );
        }
    }

    /* Send keys */
    if( strlen( command ) != 0 ) {
        if( command[ strlen(command) - 1] == '+' ) {
            command[ strlen(command) - 1] = END_OF_STRING;
        }

        gtk_label_set_text( label_grab, command );
        show_in_statusbar( command );
        send_key( command );
    }

    return FALSE;
}

