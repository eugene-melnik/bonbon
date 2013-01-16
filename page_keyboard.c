#include "page_keyboard.h"
#include "connection.h"
#include "funcs.h"

#include <stdlib.h>

extern global_t global;

char * key1;
char * key2;
char * key3;
char * key_seq;

int page_keyboard_bind(GtkBuilder * builder)
{
    /* Objects */

    GtkWidget * combo_Key1 = GTK_WIDGET(gtk_builder_get_object(builder, COMBO_KEY1));
    GtkWidget * combo_Key2 = GTK_WIDGET(gtk_builder_get_object(builder, COMBO_KEY2));
    GtkWidget * entry_Key3 = GTK_WIDGET(gtk_builder_get_object(builder, ENTRY_KEY3));
    GtkWidget * b_Send1 = GTK_WIDGET(gtk_builder_get_object(builder, BUTTON_SEND1));
    GtkWidget * entry_Key_sequence = GTK_WIDGET(gtk_builder_get_object(builder, ENTRY_KEY_SEQ));
    GtkWidget * b_Send2 = GTK_WIDGET(gtk_builder_get_object(builder, BUTTON_SEND2));
    GtkWidget * toggle_Grab_keyboard = GTK_WIDGET(gtk_builder_get_object(builder, TOGGLE_GRAB_KEYBOARD));
    GtkWidget * b_K_Up = GTK_WIDGET(gtk_builder_get_object(builder, BUTTON_K_UP));
    GtkWidget * b_K_Down = GTK_WIDGET(gtk_builder_get_object(builder, BUTTON_K_DOWN));
    GtkWidget * b_K_Left = GTK_WIDGET(gtk_builder_get_object(builder, BUTTON_K_LEFT));
    GtkWidget * b_K_Right = GTK_WIDGET(gtk_builder_get_object(builder, BUTTON_K_RIGHT));
    GtkWidget * b_K_Esc = GTK_WIDGET(gtk_builder_get_object(builder, BUTTON_K_ESC));
    GtkWidget * b_K_Tab = GTK_WIDGET(gtk_builder_get_object(builder, BUTTON_K_TAB));
    GtkWidget * b_K_Super = GTK_WIDGET(gtk_builder_get_object(builder, BUTTON_K_SUPER));
    GtkWidget * b_K_Space = GTK_WIDGET(gtk_builder_get_object(builder, BUTTON_K_SPACE));
    GtkWidget * b_K_BS = GTK_WIDGET(gtk_builder_get_object(builder, BUTTON_K_BS));
    GtkWidget * b_K_Del = GTK_WIDGET(gtk_builder_get_object(builder, BUTTON_K_DEL));
    GtkWidget * b_K_Return = GTK_WIDGET(gtk_builder_get_object(builder, BUTTON_K_RETURN));
    GtkWidget * b_K_Home = GTK_WIDGET(gtk_builder_get_object(builder, BUTTON_K_HOME));
    GtkWidget * b_K_End = GTK_WIDGET(gtk_builder_get_object(builder, BUTTON_K_END));

    /* Signals */

    g_signal_connect(combo_Key1, "changed", G_CALLBACK(combo_changed), &key1);
    g_signal_connect(combo_Key2, "changed", G_CALLBACK(combo_changed), &key2);
    g_signal_connect(entry_Key3, "changed", G_CALLBACK(entry_edited), &key3);
    g_signal_connect(entry_Key_sequence, "changed", G_CALLBACK(entry_edited), &key_seq);

    g_signal_connect(b_K_Up, "clicked", G_CALLBACK(arrow_pressed), "Up");
    g_signal_connect(b_K_Down, "clicked", G_CALLBACK(arrow_pressed), "Down");
    g_signal_connect(b_K_Left, "clicked", G_CALLBACK(arrow_pressed), "Left");
    g_signal_connect(b_K_Right, "clicked", G_CALLBACK(arrow_pressed), "Right");
    g_signal_connect(b_K_Esc, "clicked", G_CALLBACK(arrow_pressed), "Escape");
    g_signal_connect(b_K_Tab, "clicked", G_CALLBACK(arrow_pressed), "Tab");
    g_signal_connect(b_K_Super, "clicked", G_CALLBACK(arrow_pressed), "super");
    g_signal_connect(b_K_Space, "clicked", G_CALLBACK(arrow_pressed), "space");
    g_signal_connect(b_K_BS, "clicked", G_CALLBACK(arrow_pressed), "BackSpace");
    g_signal_connect(b_K_Del, "clicked", G_CALLBACK(arrow_pressed), "Delete");
    g_signal_connect(b_K_Return, "clicked", G_CALLBACK(arrow_pressed), "Return");
    g_signal_connect(b_K_Home, "clicked", G_CALLBACK(arrow_pressed), "Home");
    g_signal_connect(b_K_End, "clicked", G_CALLBACK(arrow_pressed), "End");

    return EXIT_SUCCESS;
}

void arrow_pressed(GtkButton * button, const char * type)
{
    if (global.is_connected)
    {
        send_key(global.main_pipe, type);
        show_in_statusbar(type);
    }
    else
    {
        show_in_statusbar(OFFLINE_MESSAGE);
    }
}

