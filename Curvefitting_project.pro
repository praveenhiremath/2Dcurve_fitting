#-------------------------------------------------
#
# Project created by QtCreator 2014-03-29T13:52:37
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Curvefitting_project
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    qcustomplot.cpp \
    dialog.cpp

HEADERS  += widget.h \
    qcustomplot.h \
    dialog.h

FORMS    += widget.ui \
    dialog.ui

RESOURCES += \
    user.qrc
