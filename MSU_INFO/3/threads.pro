QT += core
QT -= gui

CONFIG += c++11

TARGET = threads
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    Philosophers.h
