#ifndef PAGE_KEYBOARD_H_INCLUDED
#define PAGE_KEYBOARD_H_INCLUDED

#include <gtk/gtk.h>

/* Objects (in XML) */

#define COMBO_KEY1              "combo_Key1"
#define COMBO_KEY2              "combo_Key2"
#define ENTRY_KEY3              "entry_key3"

/* Statusbar messages */

/* Handlers */

int page_keyboard_bind(GtkBuilder *);

#endif // PAGE_KEYBOARD_H_INCLUDED

