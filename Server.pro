#-------------------------------------------------
#
# Project created by QtCreator 2014-07-10T20:17:43
#
#-------------------------------------------------

QT       += core

QT       -= gui

QT 	    += network

TARGET = Server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    metadatareader.cpp \
    metadata.cpp \
    metadatamaker.cpp \
    server.cpp \
    basedata.cpp \
    xrfdata.cpp \
    emsdata.cpp \
    libsdata.cpp \
    basedatamaker.cpp

HEADERS += \
    metadatareader.h \
    metadata.h \
    metadatamaker.h \
    server.h \
    basedata.h \
    xrfdata.h \
    emsdata.h \
    libsdata.h \
    basedatamaker.h
