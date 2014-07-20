/*
 * DAGridView.h
 *
 *  Created on: 20 lip 2014
 *      Author: dev
 */

#ifndef DAGRIDVIEW_H_
#define DAGRIDVIEW_H_
#include <gtk/gtk.h>


class DAGridView {
public:
	DAGridView();
	virtual ~DAGridView();
	void Init();
	void AddColum(const gchar *title);
protected:
private:
	GtkWidget * m_treeview;
	GtkListStore * m_store;
	int m_sizeColumn;
};

#endif /* DAGRIDVIEW_H_ */
