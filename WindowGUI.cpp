/*
 * WindowGUI.cpp
 *
 *  Created on: 13 lip 2014
 *      Author: dev
 */
#include <list>
#include <string>

#include "CDAControler.h"
#include "WindowGUI.h"
#include "Plugins/IPlugin.h"


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

	 gtk_init (&argc, &argv);
	 m_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	 gtk_window_set_default_size( GTK_WINDOW( m_window ), width, height );
	 gtk_window_set_position( GTK_WINDOW( m_window ), GTK_WIN_POS_CENTER );
	 gtk_window_set_title( GTK_WINDOW( m_window ), titleName.c_str() );
	 g_signal_connect( G_OBJECT( m_window ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );

	 initTextView();

	 //gtk_widget_show (m_window);
	 gtk_widget_show_all( m_window );
	 gtk_main();
	return 0;
}

void WindowGUI::initTextView()
{
	GtkListStore * store;
	GtkTreeIter iter;
	store = gtk_list_store_new( 2, G_TYPE_STRING, G_TYPE_STRING );

	std::list<IPlugin*> plugins;
	CDAControler::getInstance().menagerPlugin.getPlugins(plugins);
	std::list<IPlugin*>::iterator it_plugins;

	for (it_plugins=plugins.begin();it_plugins!=plugins.end();++it_plugins)
	{
		std::string name= "";
		(*it_plugins)->getName(name);
		gtk_list_store_append( store, & iter );
		gtk_list_store_set( store, & iter, 0 , name.c_str() , 1, "1979s",  -1 );
	}



    GtkWidget * treeview;
    GtkTreeViewColumn * column_first;
    GtkCellRenderer * call_first;

    GtkTreeViewColumn * column_secend;
    GtkCellRenderer * call_second;

	treeview = gtk_tree_view_new();
	gtk_container_add( GTK_CONTAINER( m_window ), treeview );

	gtk_tree_view_set_model( GTK_TREE_VIEW( treeview ), GTK_TREE_MODEL( store ) );
	g_object_unref( G_OBJECT( store ) );


	column_first = gtk_tree_view_column_new();
	call_first = gtk_cell_renderer_text_new();

	gtk_tree_view_column_set_title( column_first, "Nazwa Pluginu" );
	gtk_tree_view_column_pack_start( column_first, call_first, TRUE );
	gtk_tree_view_column_add_attribute( column_first, GTK_CELL_RENDERER( call_first ), "text", 0 );
	gtk_tree_view_append_column( GTK_TREE_VIEW( treeview ), column_first );

	column_secend = gtk_tree_view_column_new();
	call_second = gtk_cell_renderer_text_new();

	gtk_tree_view_column_set_title( column_secend, "Ścieżka" );
	gtk_tree_view_column_pack_start( column_secend, call_second, TRUE );
	gtk_tree_view_column_add_attribute( column_secend, GTK_CELL_RENDERER( call_second ), "text", 1 );
	gtk_tree_view_append_column( GTK_TREE_VIEW( treeview ), column_secend );
}
