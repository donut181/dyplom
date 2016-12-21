#-------------------------------------------------
#
# Project created by QtCreator 2016-12-07T22:38:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SymControl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    createsimulatordialog.cpp \
    Simulator.cpp \
    netlist.cpp \
    extrastab.cpp \
    ParseDialog.cpp \
    OptionsTab.cpp \
    Config.cpp

HEADERS  += mainwindow.h \
    createsimulatordialog.h \
    Simulator.h \
    netlist.h \
    extrastab.h \
    ParseDialog.h \
    OptionsTab.h \
    Config.h

FORMS    += mainwindow.ui \
    createsimulatordialog.ui \
    parsedialog.ui
