CC=g++
PATH_PLUGINS=Plugins
SOURCES=main.cpp CDAMenagerPlugin.cpp CDASetting.cpp WindowGUI.cpp

all: clear mylib main

main: $(SOURCES)
	$(CC) -g -rdynamic $(SOURCES) -ldl -lboost_system -lboost_filesystem -o Debug/dragon `pkg-config --cflags --libs gtk+-2.0`
	
mylib: $(PATH_PLUGINS)/mylib/mylib.cpp
	$(CC) -fPIC -shared $(PATH_PLUGINS)/mylib/mylib.cpp -o Debug/Plugins/mylib.so
	
clear:
	rm -fv Debug/*.o
	rm -fv Debug/Plugins/*.o	
