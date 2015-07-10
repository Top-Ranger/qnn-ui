#-------------------------------------------------
#
# Project created by QtCreator 2015-07-10T17:56:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qnn-ui
TEMPLATE = app


SOURCES += main.cpp\
        qnnui.cpp \
    gaprogress.cpp \
    gathread.cpp

HEADERS  += qnnui.h \
    gaprogress.h \
    gathread.h

FORMS    += qnnui.ui \
    gaprogress.ui

unix|win32: LIBS += -L$$PWD/../qnn/ -lqnn

INCLUDEPATH += $$PWD/../qnn/src
DEPENDPATH += $$PWD/../qnn/src
