#include "page_keyboard.h"
#include "grab_keyboard.h"
#include "connection.h"
#include "strings.h"
#include "funcs.h"

#include <string.h>
#include <unistd.h>

extern global_t global;

char* key1 = NULL;
char* key2 = NULL;
char* key3 = NULL;
char* key_seq = NULL;

GtkWidget* entry_Key_sequence;

void page_keyboard_bind( GtkBuilder* builder )
{
    /* Objects */
    GtkWidget* combo_Key1 = GTK_WIDGET( gtk_builder_get_object( builder, COMBO_KEY1 ) );
    GtkWidget* combo_Key2 = GTK_WIDGET( gtk_builder_get_object( builder, COMBO_KEY2 ) );
    GtkWidget* entry_Key3 = GTK_WIDGET( gtk_builder_get_object( builder, ENTRY_KEY3 ) );
    entry_Key_sequence = GTK_WIDGET( gtk_builder_get_object( builder, ENTRY_KEY_SEQ ) );

    /* Signals */
    g_signal_connect( combo_Key1, "changed", G_CALLBACK( combo_changed ), &key1 );
    g_signal_connect( combo_Key2, "changed", G_CALLBACK( combo_changed ), &key2 );
    g_signal_connect( entry_Key3, "changed", G_CALLBACK( entry_edited ), &key3 );
    g_signal_connect( entry_Key_sequence, "changed", G_CALLBACK( entry_edited ), &key_seq);
}

G_MODULE_EXPORT void multiply_keys( GtkButton* button, gpointer data )
{
    if( global.is_connected ) {
        char keys[100];// = EMPTY_STRING;

        if( key1 != NULL ) { sprintf( keys, "%s+", key1 ); }
        if( key2 != NULL ) { strcat( keys, key2 ); strcat( keys, "+" ); }
        if( key3 != NULL ) { strcat( keys, key3 ); }
        else if( strlen( keys ) != 0 ) {
            keys[ strlen( keys ) - 1 ] = END_OF_STRING;
        }

        show_in_statusbar( keys );
        send_key( keys );
    } else {
        show_in_statusbar( OFFLINE_MESSAGE );
    }
}

G_MODULE_EXPORT void key_sequence( GtkButton* button, gpointer data )
{
    if( global.is_connected ) {
        if( key_seq != NULL ) {
            char* key_name = strtok( key_seq, " " );

            while( key_name != NULL ) {
                send_key( key_name );
                key_name = strtok( NULL, " " );
                usleep( global.send_delay );
            }

            gtk_entry_buffer_delete_text( gtk_entry_get_buffer( GTK_ENTRY( entry_Key_sequence ) ), 0, -1 );
            show_in_statusbar( DONE_MESSAGE );
            key_seq = NULL;
        } else {
            show_in_statusbar( "Enter sequence first!" );
        }
    } else {
        show_in_statusbar( OFFLINE_MESSAGE );
    }
}

G_MODULE_EXPORT void key_pressed( GtkButton* button, gpointer data )
{
    if( global.is_connected ) {
        const char* type = gtk_button_get_label( button );
        show_in_statusbar( type );
        send_key( type );
    } else {
        show_in_statusbar( OFFLINE_MESSAGE );
    }
}

