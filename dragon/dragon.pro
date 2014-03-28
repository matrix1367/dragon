#-------------------------------------------------
#
# Project created by QtCreator 2014-03-24T15:36:17
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dragon
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    bankdb.cpp

HEADERS  += mainwindow.h \
    database.h \
    bankdb.h

FORMS    += mainwindow.ui
