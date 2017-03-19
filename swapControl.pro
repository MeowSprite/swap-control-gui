#-------------------------------------------------
#
# Project created by QtCreator 2016-12-26T17:47:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = swap-control
CONFIG(debug, debug|release) {
    DESTDIR = ./
    OBJECTS_DIR = build/debug/
    MOC_DIR = build/debug/
    RCC_DIR = build/debug/
    UI_DIR = build/debug/
} else {
    DESTDIR = ./
    OBJECTS_DIR = build/release/
    MOC_DIR = build/release/
    RCC_DIR = build/release/
    UI_DIR = build/release/
}
TEMPLATE = app

QMAKE_CXXFLAGS += -Wno-unused-function
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
TRANSLATIONS += translations/zh_CN.ts \
    translations/en_US.ts

