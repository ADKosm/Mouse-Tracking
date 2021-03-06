#-------------------------------------------------
#
# Project created by QtCreator 2016-04-03T10:45:40
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mouseTracking
TEMPLATE = app
DESTDIR = ../Mouse-Tracking-build

SOURCES += main.cpp\
        base.cpp \
    test1.cpp \
    graphicsbuttons.cpp \
    serializator.cpp \
    test2.cpp

HEADERS  += base.h \
    test1.h \
    ITest.h \
    tests.h \
    graphicsbuttons.h \
    serializator.h \
    test2.h

FORMS    += base.ui
