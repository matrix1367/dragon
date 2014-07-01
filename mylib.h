#ifndef __MYCLASS_H__
#define __MYCLASS_H__

#include "IPluhin.h"

#include <string>

class MyLib : public IPlugin
{
public:
	MyLib();
	~MyLib();

	void getName(std::string & name);
	void moduleMain();
protected:
private:
	std::string m_name;
};

#endif
