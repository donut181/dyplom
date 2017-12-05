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
    ParseDialog.cpp \
    OptionsTab.cpp \
    Config.cpp \
    extrasTab.cpp \
    OutputParser.cpp \
    ConfigureCommandDialog.cpp \
    simulationsobserver.cpp

HEADERS  += mainwindow.h \
    createsimulatordialog.h \
    Simulator.h \
    netlist.h \
    ParseDialog.h \
    OptionsTab.h \
    Config.h \
    extrasTab.h \
    OutputParser.h \
    ConfigureCommandDialog.h \
    simulationsobserver.h

FORMS    += mainwindow.ui \
    createsimulatordialog.ui \
    parsedialog.ui \
    configurecommanddialog.ui
