# -------------------------------------------------
# Project created by QtCreator 2009-08-25T20:35:54
# -------------------------------------------------
QT -= core \
    gui
TARGET = LSys2D
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    point2d.cpp \
    parser.cpp \
    calc.cpp \
    engine/engine.cpp \
    point3d.cpp \
    direction.cpp \
    alphabet.cpp \
    memcache.cpp \
    iterator.cpp \
    stringstat.cpp
HEADERS += point2d.h \
    parser.h \
    calc.h \
    engine/engine.h \
    point3d.h \
    direction.h \
    alphabet.h \
    memcache.h \
    iterator.h \
    stringstat.h
