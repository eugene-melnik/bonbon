#include "preferences.h"
#include "funcs.h"

#include <stdlib.h>
#include <string.h>

extern global_t global;

void preferences_window_bind( GtkBuilder* builder )
{
    /* Objects */
    GtkToggleButton* check_Save_login_data = GTK_TOGGLE_BUTTON( gtk_builder_get_object( builder, CHECK_SAVE_DATA ) );
    GtkToggleButton* check_Save_pass = GTK_TOGGLE_BUTTON( gtk_builder_get_object( builder, CHECK_SAVE_PASS ) );
    GtkToggleButton* check_Auto_login = GTK_TOGGLE_BUTTON( gtk_builder_get_object( builder, CHECK_AUTO_LOGIN ) );
    GtkEntry* entry_Delay = GTK_ENTRY( gtk_builder_get_object( builder, ENTRY_DELAY ) );
    GtkEntry* entry_X = GTK_ENTRY( gtk_builder_get_object( builder, ENTRY_X ) );

    /* Signals */
    g_signal_connect( check_Save_login_data, "toggled", G_CALLBACK( check_button_activate ), &global.save_login_data );
    g_signal_connect( check_Save_pass, "toggled", G_CALLBACK( check_button_activate ), &global.save_pass );
    g_signal_connect( check_Auto_login, "toggled", G_CALLBACK( check_button_activate ), &global.auto_connect );
    g_signal_connect( entry_Delay, "changed", G_CALLBACK( entry_edited_dig ), &global.send_delay );
    g_signal_connect( entry_X, "changed", G_CALLBACK( entry_edited ), &global.x_display );

    /* Actions */
    gtk_toggle_button_set_active( check_Save_login_data, global.save_login_data );
    gtk_toggle_button_set_active( check_Save_pass, global.save_pass );
    gtk_toggle_button_set_active( check_Auto_login, global.auto_connect );
    gtk_entry_set_text( entry_X, global.x_display );
    char delay[16]; sprintf( delay, "%d", global.send_delay );
    gtk_entry_set_text( entry_Delay, delay );
}

