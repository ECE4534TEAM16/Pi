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
    mazesolve.cpp \
    serialport.cpp \
<<<<<<< HEAD
    celldialog.cpp
=======
    celldialog.cpp \
    mazecell.cpp
>>>>>>> temp

HEADERS  += widget.h \
    mazesolve.h \
    serialport.h \
<<<<<<< HEAD
    celldialog.h
=======
    celldialog.h \
    mazecell.h
>>>>>>> temp

FORMS    += widget.ui
