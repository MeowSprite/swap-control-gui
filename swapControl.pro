#-------------------------------------------------
#
# Project created by QtCreator 2016-12-26T17:47:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = swap-control
TEMPLATE = app

CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    zswapconfig.cpp \
    zramconfig.cpp \
    zswaptab.cpp \
    zramtab.cpp \
    fileswapconfig.cpp \
    fileswaptab.cpp

HEADERS  += mainwindow.h \
    zswapconfig.h \
    common.h \
    zramconfig.h \
    fileswapconfig.h

FORMS    += mainwindow.ui
