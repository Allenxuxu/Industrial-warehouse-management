#-------------------------------------------------
#
# Project created by QtCreator 2017-06-05T17:41:27
#
#-------------------------------------------------

QT       += core gui  sql

TARGET = AGV_Calling
TEMPLATE = app

CONFIG += extserialport

SOURCES += main.cpp\
        widget.cpp \
    ConfigDialog.cpp \
    Workstation.cpp \
    SerialPort.cpp

HEADERS  += widget.h \
    ConnectSQL.h \
    ConfigDialog.h \
    Workstation.h \
    LRCcheck.h \
    SerialPort.h

RESOURCES += \
    rc.qrc
