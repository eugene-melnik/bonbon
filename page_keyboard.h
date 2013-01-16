#ifndef PAGE_KEYBOARD_H_INCLUDED
#define PAGE_KEYBOARD_H_INCLUDED

#include <gtk/gtk.h>

/* Objects (in XML) */

#define COMBO_KEY1              "combo_Key1"
#define COMBO_KEY2              "combo_Key2"
#define ENTRY_KEY3              "entry_key3"
#define BUTTON_SEND1            "b_Send1"
#define BUTTON_SEND2            "b_Send2"
#define ENTRY_KEY_SEQ           "entry_Key_sequence"
#define TOGGLE_GRAB_KEYBOARD    "toggle_Grab_keyboard"
#define BUTTON_K_UP             "b_K_Up"
#define BUTTON_K_DOWN           "b_K_Down"
#define BUTTON_K_LEFT           "b_K_Left"
#define BUTTON_K_RIGHT          "b_K_Right"

/* Statusbar messages */

/* Handlers */

int page_keyboard_bind(GtkBuilder *);

void arrow_pressed(GtkButton *, const char *);

#endif // PAGE_KEYBOARD_H_INCLUDED

