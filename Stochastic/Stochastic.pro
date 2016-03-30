QT += widgets
SOURCES += \
    main.cpp \
    mafenetre.cpp

HEADERS += \
    mafenetre.h \
    DLL1.h \

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-DLL1-Desktop_Qt_5_5_1_MSVC2013_64bit-Debug/release/ -lDLL1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-DLL1-Desktop_Qt_5_5_1_MSVC2013_64bit-Debug/debug/ -lDLL1
else:unix: LIBS += -L$$PWD/../build-DLL1-Desktop_Qt_5_5_1_MSVC2013_64bit-Debug/ -lDLL1

INCLUDEPATH += $$PWD/../DLL1
DEPENDPATH += $$PWD/../DLL1
