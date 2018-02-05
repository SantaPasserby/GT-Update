#-------------------------------------------------
#
# Project created by QtCreator 2018-01-15T09:04:22
#
#-------------------------------------------------

QT       += core gui serialport

RC_ICONS = update.ico
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GT-Update
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    qextserialport-1.2win-alpha/qextserialbase.cpp \
    qextserialport-1.2win-alpha/win_qextserialport.cpp \
    serialdialog.cpp \
    serialparameter.cpp

HEADERS  += mainwindow.h \
    qextserialport-1.2win-alpha/qextserialbase.h \
    qextserialport-1.2win-alpha/win_qextserialport.h \
    serialdialog.h \
    serialparameter.h

FORMS    += mainwindow.ui \
    serialdialog.ui
