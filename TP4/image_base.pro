#-------------------------------------------------
#
# Project created by QtCreator 2015-01-07T21:40:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = triangle
TEMPLATE = app

CONFIG(debug, debug|release) {
    DESTDIR = build/debug
} else {
    DESTDIR = build/release
}

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.rcc
UI_DIR = $$DESTDIR/.ui


SOURCES += main.cpp\
    fractalimage.cpp \
    interpolator.cpp \
    mainwindow.cpp \
    pixel2rect.cpp


HEADERS  += mainwindow.h \
    Commify.h \
    fractalimage.h \
    interpolator.h \
    pixel2rect.h

QMAKE_CXXFLAGS += -std=c++17

