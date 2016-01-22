#-------------------------------------------------
#
# Project created by QtCreator 2016-01-18T16:09:50
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = accounting
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    db.cpp \
    salestableview.cpp

HEADERS  += mainwindow.h \
    db.h \
    salestableview.h

FORMS    += \
    mainwindow.ui
