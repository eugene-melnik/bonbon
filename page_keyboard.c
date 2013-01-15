#include "page_keyboard.h"
#include "funcs.h"

#include <stdlib.h>

char * key3 = NOTHING_STRING;

int page_keyboard_bind(GtkBuilder * builder)
{
    /* Objects */

    GtkWidget * combo_Key1 = GTK_WIDGET(gtk_builder_get_object(builder, COMBO_KEY1));
    GtkWidget * combo_Key2 = GTK_WIDGET(gtk_builder_get_object(builder, COMBO_KEY2));
    GtkWidget * entry_Key3 = GTK_WIDGET(gtk_builder_get_object(builder, ENTRY_KEY3));

    /* Signals */

    //g_signal_connect(combo_Key1, "changed", G_CALLBACK(combo_changed), NULL);
    //g_signal_connect(combo_Key2, "changed", G_CALLBACK(combo_changed), NULL);
    //g_signal_connect(entry_Key3, "changed", G_CALLBACK(entry_edited), &key3);

    return EXIT_SUCCESS;
}

