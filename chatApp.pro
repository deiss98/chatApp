#-------------------------------------------------
#
# Project created by QtCreator 2022-01-19T18:06:02
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chatApp
TEMPLATE = app


SOURCES += main.cpp\
    inscription.cpp \
    connexion.cpp \
    db.cpp \
    invitation.cpp \
    chat.cpp

HEADERS  += \
    inscription.h \
    connexion.h \
    db.h \
    invitation.h \
    chat.h

FORMS    += \
    inscription.ui \
    connexion.ui \
    invitation.ui \
    chat.ui
