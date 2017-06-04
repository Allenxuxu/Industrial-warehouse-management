#-------------------------------------------------
#
# Project created by QtCreator 2017-05-24T21:25:15
#
#-------------------------------------------------

QT       += core gui sql

TARGET = StoreroomDisplay
TEMPLATE = app
CONFIG += extserialport


SOURCES += main.cpp\
    WorkstationBox.cpp \
    Widget.cpp \
    DataDialog.cpp \
    qextserial.cpp

HEADERS  += \
    WorkstationBox.h \
    Widget.h \
    DataDialog.h \
    ConnectSQl.h \
    qextserial.h

OTHER_FILES += \
    readme.txt

RESOURCES += \
    icon.qrc
