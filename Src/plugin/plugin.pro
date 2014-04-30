#! [0]
TEMPLATE        = lib
CONFIG         += plugin
QT             += widgets
INCLUDEPATH    += ../echowindow
HEADERS         = echoplugin.h
SOURCES         = echoplugin.cpp
TARGET          = $$qtLibraryTarget(dragon)
DESTDIR         = ../plugins
#! [0]

EXAMPLE_FILES = dragonplugin.json

# install
target.path = C:\workspace\dragon\install\plugin
INSTALLS += target
