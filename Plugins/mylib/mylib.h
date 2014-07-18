#ifndef __MYCLASS_H__
#define __MYCLASS_H__

#include "../IPlugin.h"

#include <string>

class MyLib : public IPlugin
{
public:
	MyLib();
	~MyLib();

	void getName(std::string & name);
	void moduleMain(int argc, char **argv);
protected:
private:
	std::string m_name;
};

#endif
