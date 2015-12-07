#-------------------------------------------------
#
# Project created by QtCreator 2015-11-08T22:27:24
#
#-------------------------------------------------

QT       += core gui
QT       += widgets
QT       += serialport
TARGET = Pi
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    serialport.cpp \
    celldialog.cpp \
    mazecell.cpp

HEADERS  += widget.h \
    serialport.h \
    celldialog.h \
    mazecell.h

FORMS    += widget.ui
