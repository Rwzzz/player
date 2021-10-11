#-------------------------------------------------
#
# Project created by QtCreator 2020-07-27T22:06:45
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
QT       += sql
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project
TEMPLATE = app


SOURCES += main.cpp\
        mywidget.cpp \
    music.cpp \
    musiclist.cpp \
    lyricwidget.cpp \
    speech.cpp \
    http.cpp \
    audio.cpp

HEADERS  += mywidget.h \
    music.h \
    musiclist.h \
    lyricwidget.h \
    speech.h \
    http.h \
    audio.h

FORMS    += mywidget.ui \
    lyricwidget.ui

RESOURCES += \
    res.qrc
