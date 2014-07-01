#include "mylib.h"
#include <iostream>

using namespace std;

extern "C" MyLib* create_object()
{
  return new MyLib;
}

extern "C" void destroy_object( MyLib* object )
{
  delete object;
}

MyLib::MyLib()
{
  m_name = "te	sss";
}

void MyLib::getName(string& name)
{
	name = m_name;
}

void MyLib::moduleMain()
{
	std::cout << "start plugin" << std::endl;
}

MyLib::~MyLib()
{

}
