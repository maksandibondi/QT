#-------------------------------------------------
#
# Project created by QtCreator 2016-03-30T02:29:18
#
#-------------------------------------------------

QT       -= gui

TARGET = DLL1
TEMPLATE = lib

DEFINES += DLL1_LIBRARY

SOURCES += DLL1.cpp

HEADERS += DLL1.h\
        dll1_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
