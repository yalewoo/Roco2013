#-------------------------------------------------
#
# Project created by QtCreator 2017-04-14T13:46:41
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtRoco
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pokemon.cpp \
    skill.cpp \
    selectpet.cpp \
    pk.cpp \
    pok.cpp \
    team.cpp \
    globalvar.cpp \
    client.cpp

HEADERS  += mainwindow.h \
    pokemon.h \
    skill.h \
    selectpet.h \
    pk.h \
    pok.h \
    team.h \
    globalvar.h \
    client.h

FORMS    += \
    selectpet.ui \
    pk.ui \
    client.ui
