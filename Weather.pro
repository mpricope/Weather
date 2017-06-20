#-------------------------------------------------
#
# Project created by QtCreator 2017-06-03T16:23:50
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Weather
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


INCLUDEPATH += /home/apps/boost/include/

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        noaa/noaaparser.cpp \
    db/db.cpp

HEADERS += \
        mainwindow.h \
    csv.h \
    noaa/noaaparser.h \
    db/db.h \
    globals.h \
    db/station.h

FORMS += \
        mainwindow.ui

QMAKE_CXXFLAGS += -DBOOST_NO_CXX11_SCOPED_ENUMS -DBOOST_ALL_DYN_LINK

LIBS += -L/home/apps/boost/lib -lboost_system -lboost_filesystem
