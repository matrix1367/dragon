/*
 * WindowGUI.h
 *
 *  Created on: 13 lip 2014
 *      Author: dev
 */

#ifndef WINDOWGUI_H_
#define WINDOWGUI_H_
#include <string>
#include <gtk/gtk.h>

#include "IGUI.h"

class WindowGUI: public IGUI {
public:
	WindowGUI();
	virtual ~WindowGUI();
	int WindowMain(int argc, char **argv);

protected:
private:
	int width;
	int height;
	std::string titleName;
	 GtkWidget *m_window;
	void initTextView();
};

#endif /* WINDOWGUI_H_ */
