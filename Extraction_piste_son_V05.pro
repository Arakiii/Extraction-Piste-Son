#-------------------------------------------------
#
# Project created by QtCreator 2019-04-10T11:22:53
#
#-------------------------------------------------
QT       += gui widgets
QT       += core gui
QT += multimedia
QT += printsupport
QT += svg
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Extraction_piste_son_V05
TEMPLATE = app

INCLUDEPATH += "../../include"
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
    aboutdialog.cpp \
    playerfinishedcallback.cpp \
    playerheartbeatcallback.cpp \
    modifnote.cpp \
    application.cpp

HEADERS  += mainwindow.h \
    aboutdialog.h \
    playerfinishedcallback.h \
    playerheartbeatcallback.h \
    modifnote.h \
    application.h

FORMS    += mainwindow.ui \
    modifnote.ui
LIBS += -lwinmm

DISTFILES += \
    Extraction_piste_son_V05.pro.user \
    Icon/Portee.PNG \
    Icon/play.png \
    Icon/pause.png \
    Icon/noireDO.png \
    Icon/noire.png \
    Icon/icone.png \
    Icon/gray_background.png \
    Icon/croche.png \
    Icon/cledesol.png \
    Icon/cledefa.png \
    Icon/blanche.png

win32 {
    LIBS += winmm.lib
}

RESOURCES += \
    ressource.qrc
