#-------------------------------------------------
#
# Project created by QtCreator 2015-04-02T22:09:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chinput
TEMPLATE = app
CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    inputmanager.cpp \
    hzimg.cpp \
    flowlayout.cpp \
    InputHandler.cpp

HEADERS  += mainwindow.h \
    inputmanager.h \
    hzImg.h \
    flowlayout.h \
    InputHandler.h

FORMS    += mainwindow.ui

DISTFILES += \
    mhzk16 \
    input_set
