#include "page_keyboard.h"
#include "funcs.h"

int page_keyboard_bind(GtkBuilder * builder)
{
    /* Objects */

    GtkWidget * combo_Key1 = GTK_WIDGET(gtk_builder_get_object(builder, COMBO_KEY1));
    GtkWidget * combo_Key2 = GTK_WIDGET(gtk_builder_get_object(builder, COMBO_KEY2));

    /* Signals */

    g_signal_connect(combo_Key1, "changed", G_CALLBACK(combo_changed), NULL);
    g_signal_connect(combo_Key2, "changed", G_CALLBACK(combo_changed), NULL);

    return 0;
}

void combo_changed(GtkComboBoxText * combobox, gpointer user_data)
{
    return;
}

