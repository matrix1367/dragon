#include <dlfcn.h>
#include <iostream>
#include <string>
#include "IPluhin.h"
#include "mylib.h"

using namespace std;

int main(int argc, char **argv)
{
  void* handle = dlopen("./mylib.so", RTLD_LAZY);

  IPlugin* (*create)();
  void (*destroy)(IPlugin*);

  create = (IPlugin* (*)())dlsym(handle, "create_object");
  destroy = (void (*)(IPlugin*))dlsym(handle, "destroy_object");

  IPlugin* myClass = (IPlugin*)create();

  string nazwa = "";

  myClass->getName(nazwa);
  cout << "name :" << nazwa << endl;
  destroy( myClass );
}
