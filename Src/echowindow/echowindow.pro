QT += widgets

HEADERS    = echowindow.h \
             pluginsloader.h \
             iplugin.h

SOURCES    = echowindow.cpp \
             pluginsloader.cpp \
             main.cpp


TARGET     = dragon
QMAKE_PROJECT_NAME = echopluginwindow
win32 {
    CONFIG(debug, release|debug):DESTDIR = ../debug/
    CONFIG(release, release|debug):DESTDIR = ../release/
} else {
    DESTDIR    = ../
}

# install
target.path = C:\workspace\dragon\install
INSTALLS += target
