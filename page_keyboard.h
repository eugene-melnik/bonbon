#ifndef PAGE_KEYBOARD_H_INCLUDED
#define PAGE_KEYBOARD_H_INCLUDED

/* Headers */
#include <gtk/gtk.h>

/* Objects (in XML) */
#define COMBO_KEY1              "combo_Key1"
#define COMBO_KEY2              "combo_Key2"
#define ENTRY_KEY3              "entry_Key3"
#define ENTRY_KEY_SEQ           "entry_Key_sequence"
#define TOGGLE_GRAB_KEYBOARD    "toggle_Grab_keyboard"

/* Handlers */
void page_keyboard_bind( GtkBuilder* builder );
void multiply_keys( GtkButton* button, gpointer data );
void key_sequence( GtkButton* button, gpointer data );
void key_pressed( GtkButton* button, gpointer data );

#endif // PAGE_KEYBOARD_H_INCLUDED

