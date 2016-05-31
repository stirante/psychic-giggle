#-------------------------------------------------
#
# Project created by QtCreator 2016-05-17T08:19:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = psychic-giggle
TEMPLATE = app


SOURCES += main.cpp\
        game.cpp \
    basicdatafile.cpp \
    state.cpp \
    renderable.cpp \
    renderablegroup.cpp \
    simplebutton.cpp

HEADERS  += game.h \
    basicdatafile.h \
    state.h \
    renderable.h \
    renderablegroup.h \
    simplebutton.h

RESOURCES = resources.qrc