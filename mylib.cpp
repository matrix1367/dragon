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
  x = 20;
  m_name = "test";
}

void MyLib::getName(string& name)
{
	name = m_name;
}

void MyLib::DoSomething()
{
  cout<<x<<endl;
}

MyLib::~MyLib()
{

}
