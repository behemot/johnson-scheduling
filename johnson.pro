CONFIG += debug_and_release

HEADERS += headers/gui.h
HEADERS += headers/choose.h
HEADERS += headers/tasks.h
HEADERS += headers/gant.h
HEADERS += headers/johnson.h

SOURCES += src/main.cpp
SOURCES += src/gui.cpp
SOURCES += src/choose.cpp
SOURCES += src/tasks.cpp
SOURCES += src/gant.cpp
SOURCES += src/johnson.cpp

INCLUDEPATH = headers

OBJECTS_DIR = tmp
OBJMOC = $$OBJECTS_DIR
MOC_DIR = generated

DESTDIR = build
TARGET = johnson

