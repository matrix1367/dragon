/*
 * CDAMenagerPlugin.h
 *
 *  Created on: 5 lip 2014
 *      Author: dev
 */

#ifndef CDAMENAGERPLUGIN_H_
#define CDAMENAGERPLUGIN_H_
#include <list>
#include "Plugins/IPlugin.h"

class CDAMenagerPlugin {
public:
	CDAMenagerPlugin();
	virtual ~CDAMenagerPlugin();
	void load(const std::string& fileName);
	void load();
	void remove(const std::string& namePlugin);
	void modulesMain(int argc, char **argv);
protected:
private:
	std::list<IPlugin*> m_plugins;
};

#endif /* CDAMENAGERPLUGIN_H_ */
