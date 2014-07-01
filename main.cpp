#include <dlfcn.h>
#include <iostream>
#include <string>
#include "mylib.h"

using namespace std;

int main(int argc, char **argv)
{
  void* handle = dlopen("./mylib.so", RTLD_LAZY);

  MyLib* (*create)();
  void (*destroy)(MyLib*);

  create = (MyLib* (*)())dlsym(handle, "create_object");
  destroy = (void (*)(MyLib*))dlsym(handle, "destroy_object");

  MyLib* myClass = (MyLib*)create();
  myClass->DoSomething();
  string nazwa = "";

  myClass->getName(nazwa);
  cout << "name :" << nazwa << endl;
  destroy( myClass );
}
