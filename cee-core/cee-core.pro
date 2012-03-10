#-------------------------------------------------
#
# Project created by QtCreator 2012-02-28T19:22:53
#
#-------------------------------------------------

QT       -= gui

TARGET = cee-core
TEMPLATE = lib
CONFIG += staticlib

DEFINES += QT

SOURCES += \
    valuetable.cpp \
    valuenode.cpp \
    valueexception.cpp \
    valueassignmentnode.cpp \
    treenode.cpp \
    syntaxtree.cpp \
    scanner.c \
    parser.c \
    numbers.c \
    numbernode.cpp \
    functiontable.cpp \
    functionnode.cpp \
    functionassignmentnode.cpp \
    exception.cpp \
    commandnode.cpp \
    calcexception.cpp \
    calc.cpp

HEADERS += \
    valuetable.h \
    valuenode.h \
    valueexception.h \
    valueassignmentnode.h \
    treenode.h \
    syntaxtree.h \
    syntax_tree_wrapper.h \
    scanner.h \
    parser.h \
    numbers.h \
    numbernode.h \
    functiontable.h \
    functionnode.h \
    functionassignmentnode.h \
    exception.h \
    commandnode.h \
    calcexception.h \
    calc.h
