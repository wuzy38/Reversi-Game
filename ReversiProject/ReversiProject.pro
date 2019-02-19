#-------------------------------------------------
#
# Project created by QtCreator 2018-11-16T17:46:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ReversiProject
TEMPLATE = app


SOURCES += main.cpp\
        reversimainwindow.cpp \
    reversi.cpp \
    reversiai.cpp \
    selectdialog.cpp

HEADERS  += reversimainwindow.h \
    reversi.h \
    reversiai.h \
    selectdialog.h

FORMS    += reversimainwindow.ui \
    selectdialog.ui
