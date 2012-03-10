#-------------------------------------------------
#
# Project created by QtCreator 2012-02-28T19:38:11
#
#-------------------------------------------------

QT       += core gui

TARGET = cee
TEMPLATE = app

#mac {
#  CONFIG -= app_bundle
#}

INCLUDEPATH += ../cee-core
LIBS += -L../cee-core
LIBS += -lcee-core
LIBS += -lreadline

SOURCES += \
    settingswindow.cpp \
    settings.cpp \
    miniconsole.cpp \
    mainwindow.cpp \
    main.cpp \
    commandline.cpp

HEADERS  += \
    settingswindow.h \
    settings.h \
    miniconsole.h \
    mainwindow.h \
    commandline.h

FORMS    += \
    settingswindow.ui \
    mainwindow.ui

//DEFINES += GUI_ONLY



