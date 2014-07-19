#include <execinfo.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include "Plugins/IPlugin.h"
#include "CDAControler.h"
#include "WindowGUI.h"


using namespace std;

void printCallstack( int callstackSize = 20 ){
    void * buffer[ callstackSize ];
    char ** backtraceStrings;

    int const traceCount = backtrace( buffer, callstackSize );
    if( traceCount == 0 ){
        return;
    }

    backtraceStrings = backtrace_symbols( buffer, traceCount );

    if( ! backtraceStrings ){
        return;
    }

    for( size_t i = 0 ; i < traceCount ; ++ i ){
        std::cout << backtraceStrings[ i ] << std::endl;
    }

    delete [] backtraceStrings;
}

int main(int argc, char **argv)
{
	//printCallstack();
	printf("[%s] : (%d)\n" , __FUNCTION__ , __LINE__);
	CDAControler::getInstance().menagerPlugin.load();
	if (CDASetting::getInstance().autoRun)
	{
		CDAControler::getInstance().menagerPlugin.modulesMain(argc, argv);
	}

	WindowGUI gui;
	gui.WindowMain(argc, argv);
}
