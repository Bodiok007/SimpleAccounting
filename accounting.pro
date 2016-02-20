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
    DB/db.cpp \
    salestableview.cpp \
    servicestableview.cpp \
    addsaleform.cpp \
    addsale.cpp \
    loginform.cpp \
    DB/dbsettings.cpp \
    addserviceform.cpp \
    editsalesform.cpp \
    editservicesform.cpp \
    salesmodel.cpp \
    servicecategories.cpp \
    servicesmodel.cpp \
    salecategories.cpp \
    mainapplication.cpp

HEADERS  += mainwindow.h \
    DB/db.h \
    salestableview.h \
    servicestableview.h \
    addsaleform.h \
    addsale.h \
    loginform.h \
    DB/dbsettings.h \
    addserviceform.h \
    editsalesform.h \
    editservicesform.h \
    salesmodel.h \
    servicecategories.h \
    servicesmodel.h \
    salecategories.h \
    mainapplication.h

FORMS    += \
    mainwindow.ui \
    addsaleform.ui \
    loginform.ui \
    addserviceform.ui \
    editsalesform.ui \
    editservicesform.ui

RESOURCES += \
    resource.qrc
