#ifndef PAGE_KEYBOARD_H_INCLUDED
#define PAGE_KEYBOARD_H_INCLUDED

#include <gtk/gtk.h>

/* Objects (in XML) */

#define COMBO_KEY1              "combo_Key1"
#define COMBO_KEY2              "combo_Key2"

/* Statusbar messages */

/* Handlers */

int page_keyboard_bind(GtkBuilder *);

void combo_changed(GtkComboBoxText * combobox, gpointer user_data);

#endif // PAGE_KEYBOARD_H_INCLUDED

