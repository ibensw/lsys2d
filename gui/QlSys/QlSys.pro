# -------------------------------------------------
# Project created by QtCreator 2010-02-13T13:46:59
# -------------------------------------------------
TARGET = QlSys
TEMPLATE = app
SOURCES += main.cpp \
    qlsys.cpp
HEADERS += qlsys.h
FORMS += qlsys.ui
QT += opengl
LIBS += ../../src/*.o ../../src/engine/*.o ../../src/tinyxml/*.o -L/usr/lib -lpthread -lSDL -lGL -lglut -lpng -lpngwriter -lz -lfreetype
