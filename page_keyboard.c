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

static GtkComboBoxText* combo_Key1 = NULL;
static GtkComboBoxText* combo_Key2 = NULL;
static GtkEntry* e_Key3 = NULL;
static GtkEntry* e_Key_sequence = NULL;

void page_keyboard_bind( GtkBuilder* builder )
{
    combo_Key1 = GTK_COMBO_BOX_TEXT( gtk_builder_get_object( builder, COMBO_KEY1 ) );
    combo_Key2 = GTK_COMBO_BOX_TEXT( gtk_builder_get_object( builder, COMBO_KEY2 ) );
    e_Key3 = GTK_ENTRY( gtk_builder_get_object( builder, ENTRY_KEY3 ) );
    e_Key_sequence = GTK_ENTRY( gtk_builder_get_object( builder, ENTRY_KEY_SEQ ) );

    g_signal_connect( combo_Key1, "changed", G_CALLBACK( combo_changed ), &key1 );
    g_signal_connect( combo_Key2, "changed", G_CALLBACK( combo_changed ), &key2 );
    g_signal_connect( e_Key3, "changed", G_CALLBACK( entry_edited ), &key3 );
    g_signal_connect( e_Key_sequence, "changed", G_CALLBACK( entry_edited ), &key_seq);
}

void multiply_keys( GtkButton* button, gpointer data )
{
    if( !global.is_connected )
    {
        show_in_statusbar( OFFLINE_MESSAGE );
        return;
    }

    char keys[ COMMAND_BUFFER_SIZE ] = "";

    if( key1 != NULL ) { sprintf( keys, "%s+", key1 ); }
    if( key2 != NULL ) { strcat( keys, key2 ); strcat( keys, "+" ); }
    if( key3 != NULL ) { strcat( keys, key3 ); }
    else if( strlen( keys ) != 0 ) pop_char( keys );

    show_in_statusbar_ext( "Sending keys: \"%s\".", keys );
    send_key( keys );
}

void key_sequence( GtkButton* button, gpointer data )
{
    if( !global.is_connected )
    {
        show_in_statusbar( OFFLINE_MESSAGE );
        return;
    }

    if( key_seq == NULL )
    {
        show_in_statusbar( ENTER_DATA_MESSAGE );
        return;
    }

    show_in_statusbar_ext( "Sending sequence: \"%s\".", key_seq );
    char* key_name = strtok( key_seq, " " );

    while( key_name != NULL )
    {
        send_key( key_name );
        key_name = strtok( NULL, " " );
        usleep( global.send_delay );
    }

    GtkEntryBuffer* buffer = gtk_entry_get_buffer( GTK_ENTRY( e_Key_sequence ) );
    gtk_entry_buffer_delete_text( buffer, 0, -1 );
    key_seq = NULL;
}

void key_pressed( GtkButton* button, gpointer data )
{
    if( !global.is_connected )
    {
        show_in_statusbar( OFFLINE_MESSAGE );
        return;
    }

    const char* type = gtk_button_get_label( button );
    show_in_statusbar_ext( "Sending key: \"%s\".", type );
    send_key( type );
}

