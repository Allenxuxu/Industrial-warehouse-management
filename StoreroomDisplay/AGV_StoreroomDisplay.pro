#-------------------------------------------------
#
# Project created by QtCreator 2017-06-06T08:56:07
#
#-------------------------------------------------

QT       += core gui sql

TARGET = AGV_StoreroomDisplay
TEMPLATE = app
CONFIG += extserialport

SOURCES += main.cpp\
        widget.cpp \
    ModifyDataDialog.cpp \
    SerialPort.cpp \
    WorkstationBox.cpp

HEADERS  += widget.h \
    ConnectSQl.h \
    ModifyDataDialog.h \
    SerialPort.h \
    WorkstationBox.h

RESOURCES += \
    icon.qrc
