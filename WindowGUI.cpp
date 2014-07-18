/*
 * WindowGUI.cpp
 *
 *  Created on: 13 lip 2014
 *      Author: dev
 */

#include "WindowGUI.h"
#include <gtk/gtk.h>

WindowGUI::WindowGUI() {
	printf("[WindowGUI::%s] : (%d)\n" , __FUNCTION__ , __LINE__);
	width = 800;
	height = 600;
	titleName = "Dragon";
}

WindowGUI::~WindowGUI() {
	printf("[WindowGUI::%s] : (%d)\n" , __FUNCTION__ , __LINE__);
}

int WindowGUI::WindowMain(int argc, char **argv)
{
	printf("[WindowGUI::%s] : (%d)\n" , __FUNCTION__ , __LINE__);
	 GtkWidget *window;
	 gtk_init (&argc, &argv);
	 window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	 gtk_window_set_default_size( GTK_WINDOW( window ), width, height );
	 gtk_window_set_position( GTK_WINDOW( window ), GTK_WIN_POS_CENTER );
	 gtk_window_set_title( GTK_WINDOW( window ), titleName.c_str() );
	 g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );
	 gtk_widget_show (window);
	 gtk_main();
	return 0;
}
