#ifndef __MYCLASS_H__
#define __MYCLASS_H__

#include <string>

class MyLib
{
public:
	MyLib();
	virtual ~MyLib();

	virtual void getName(std::string & name);
	virtual void DoSomething();

protected:
private:
	std::string m_name;
  int x;
};

#endif
