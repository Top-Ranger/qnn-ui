#-------------------------------------------------
#
# Project created by QtCreator 2015-07-10T17:56:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qnn-ui
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += src/main.cpp\
        src/qnnui.cpp \
    src/gaprogress.cpp \
    src/gathread.cpp \
    src/runproperties.cpp

HEADERS  += src/qnnui.h \
    src/gaprogress.h \
    src/gathread.h \
    src/runproperties.h \
    src/additionalsimulationfunctions.hpp

FORMS    += src/qnnui.ui \
    src/gaprogress.ui \
    src/runproperties.ui

unix: LIBS += -L$$PWD/../qnn/ -lqnn
win32: LIBS += -L$$PWD/../qnn/ -lqnn0

INCLUDEPATH += $$PWD/../qnn/src
DEPENDPATH += $$PWD/../qnn/src

OTHER_FILES += \
    LICENSE.GPL3

DISTFILES += \
    README
