#include "preferences.h"
#include "funcs.h"

#include <stdlib.h>

extern global_t global;

void preferences_window_bind( GtkBuilder* builder )
{
    /* Objects */
    GtkWidget* check_Save_login_data = GTK_WIDGET( gtk_builder_get_object( builder, CHECK_SAVE_DATA ) );
    GtkWidget* check_Auto_login = GTK_WIDGET( gtk_builder_get_object( builder, CHECK_AUTO_LOGIN ) );

    /* Signals */
    g_signal_connect( check_Save_login_data, "toggled", G_CALLBACK( check_button_activate ), &global.save_login_data );
    g_signal_connect( check_Auto_login, "toggled", G_CALLBACK( check_button_activate ), &global.auto_connect );

    /* Actions */
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( check_Save_login_data ), global.save_login_data );
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( check_Auto_login ), global.auto_connect );
}

