#-------------------------------------------------
#
# Project created by QtCreator 2015-07-10T17:56:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qnn-ui
TEMPLATE = app


SOURCES += src/main.cpp\
        src/qnnui.cpp \
    src/gaprogress.cpp \
    src/gathread.cpp

HEADERS  += src/qnnui.h \
    src/gaprogress.h \
    src/gathread.h

FORMS    += src/qnnui.ui \
    src/gaprogress.ui

unix|win32: LIBS += -L$$PWD/../qnn/ -lqnn

INCLUDEPATH += $$PWD/../qnn/src
DEPENDPATH += $$PWD/../qnn/src
