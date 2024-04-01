TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L"../SFML-2.5.1/lib"
LIBS += -L"../SFML-2.5.1/bin"
INCLUDEPATH += "../SFML-2.5.1/include"
DEPENDPATH += "../SFML-2.5.1/include"

CONFIG(release, debug | release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window
CONFIG(debug, debug | release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window

SOURCES += \
        main.cpp
