/*
 * DAGridView.cpp
 *
 *  Created on: 20 lip 2014
 *      Author: dev
 */

#include "DAGridView.h"

DAGridView::DAGridView(GtkWidget *m_window)
{
	m_sizeColumn = -1;
	m_treeview = gtk_tree_view_new();
	gtk_container_add( GTK_CONTAINER( m_window ), treeview );
}

DAGridView::~DAGridView()
{
	// TODO Auto-generated destructor stub
}

void DAGridView::AddColum(const gchar* title)
{
    GtkTreeViewColumn * colum = gtk_tree_view_column_new();
    GtkCellRenderer * cell = gtk_cell_renderer_text_new();

	gtk_tree_view_column_set_title( colum, title);
	gtk_tree_view_column_pack_start( colum, cell, TRUE );
	gtk_tree_view_column_add_attribute( colum, GTK_CELL_RENDERER( cell ), "text", m_sizeColumn++ );
	gtk_tree_view_append_column( GTK_TREE_VIEW( m_treeview ), colum );
}

void DAGridView::Init()
{
	GtkTreeIter iter;
	m_store = gtk_list_store_new( 2, G_TYPE_STRING, G_TYPE_STRING );


	gtk_list_store_append( m_store, & iter );
	gtk_list_store_set( m_store, & iter, 0 , "Michał", 1, "dddddd",  -1 );

}
