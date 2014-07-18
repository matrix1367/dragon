/*
 * CDAMenagerPlugin.cpp
 *
 *  Created on: 5 lip 2014
 *      Author: dev
 */
#include <list>
#include <dlfcn.h>
#include <string>
#include <stdio.h>

#include <boost/filesystem.hpp>
#include "CDAMenagerPlugin.h"
#include "CDASetting.h"


CDAMenagerPlugin::CDAMenagerPlugin() {
	printf("[CDAMenagerPlugin::%s] : (%d)\n" , __FUNCTION__ , __LINE__);
}

CDAMenagerPlugin::~CDAMenagerPlugin()
{
	printf("[CDAMenagerPlugin::%s] : (%d)\n" , __FUNCTION__ , __LINE__);
	std::list<IPlugin*>::iterator it_plugins;
	for(it_plugins=m_plugins.begin(); it_plugins!=m_plugins.end(); ++it_plugins)
	{
		delete *it_plugins;
	}
}
//
//void CDAMenagerPlugin::openPlugin(const std::string& fileName, IPlugin * plugin)
//{
//	void* handle = dlopen(fileName.c_str(), RTLD_LAZY);
//	IPlugin* (*create)();
//	create = (IPlugin* (*)())dlsym(handle, "create_object");
//
//	 plugin = ((IPlugin*)create());
//
//
//}

void CDAMenagerPlugin::load()
{
	printf("[CDAMenagerPlugin::%s] : (%d)\n" , __FUNCTION__ , __LINE__);
	boost::filesystem::directory_iterator iterator(CDASetting::getInstance().pathPlugins);
	for(; iterator != boost::filesystem::directory_iterator(); ++iterator)
	{
		std::string filename = CDASetting::getInstance().pathPlugins.append((iterator->path().filename()).c_str());
		printf("[CDAMenagerPlugin::%s] : (%d) Load plugin : %s\n" , __FUNCTION__ , __LINE__, filename.c_str());
		void* handle = dlopen(filename.c_str(), RTLD_LAZY);
		IPlugin* (*create)();
		create = (IPlugin* (*)())dlsym(handle, "create_object");
		IPlugin* plugin;
		plugin = (IPlugin*)create();

		if (plugin != NULL)
		{
			m_plugins.push_back(plugin);
		}
	}

}

void CDAMenagerPlugin::load(const std::string& fileName)
{
	printf("[CDAMenagerPlugin::%s] : (%d)\n" , __FUNCTION__ , __LINE__);
	void* handle = dlopen(fileName.c_str(), RTLD_LAZY);
	IPlugin* (*create)();

	create = (IPlugin* (*)())dlsym(handle, "create_object");

	IPlugin* plugin = (IPlugin*)create();
	if (plugin != NULL)
	{
		m_plugins.push_back(plugin);
	}
}

void CDAMenagerPlugin::remove(const std::string& namePlugin)
{
	printf("[CDAMenagerPlugin::%s] : (%d)\n" , __FUNCTION__ , __LINE__);
	std::string name;
	std::list<IPlugin*>::iterator it_plugins;
	for(it_plugins=m_plugins.begin(); it_plugins!=m_plugins.end(); ++it_plugins)
	{
		(*it_plugins)->getName(name);
		if (name == namePlugin)
		{
			m_plugins.remove(*it_plugins);
		}
	}
}

void CDAMenagerPlugin::modulesMain(int argc, char **argv)
{
	printf("[CDAMenagerPlugin::%s] : (%d)\n" , __FUNCTION__ , __LINE__);
	std::list<IPlugin*>::iterator it_plugins;
	for(it_plugins=m_plugins.begin(); it_plugins!=m_plugins.end(); ++it_plugins)
	{
		(*it_plugins)->moduleMain(argc, argv);
	}
}
