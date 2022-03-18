#-------------------------------------------------
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = yuv-viewer
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    yuvimage.cpp

HEADERS  += mainwindow.h \
    yuvimage.h \
    util.h

QMAKE_CXXFLAGS += -std=c++20

