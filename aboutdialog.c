#include "aboutdialog.h"
#include "bonbon.h"

static GtkAboutDialog* aboutdialog = NULL;

void aboutdialog_bind( GtkBuilder* builder )
{
    aboutdialog = GTK_ABOUT_DIALOG( gtk_builder_get_object( builder, "about_window" ) );

    gtk_about_dialog_set_program_name( aboutdialog, PROGRAM_NAME );
    gtk_about_dialog_set_version( aboutdialog, PROGRAM_VERSION );
}

