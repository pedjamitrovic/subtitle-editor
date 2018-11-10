#-------------------------------------------------
#
# Project created by QtCreator 2017-04-16T00:18:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qqqqqqq
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
    FileInfo.cpp \
    MicroDVD.cpp \
    MPSub.cpp \
    SRT.cpp \
    Subtitle.cpp \
    SubtitleApp.cpp \
    SubtitleIO.cpp \
    Subtitles.cpp \
    TimeStamp.cpp \
    dialogopen.cpp \
    dialoggreske.cpp \
    dialogexit.cpp \
    dialogsave.cpp \
    dialoginsert.cpp \
    SubtitleProcessing.cpp \
    dialogfps.cpp \
    dialogprocess.cpp \
    dialogmove.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    FileInfo.h \
    MicroDVD.h \
    MPSub.h \
    SRT.h \
    Subtitle.h \
    SubtitleApp.h \
    SubtitleIO.h \
    SubtitleProcessing.h \
    Subtitles.h \
    TimeStamp.h \
    dialogopen.h \
    dialoggreske.h \
    dialogexit.h \
    dialogsave.h \
    dialoginsert.h \
    dialogfps.h \
    dialogprocess.h \
    dialogmove.h \
    dialog.h

FORMS    += mainwindow.ui \
    dialogopen.ui \
    dialoggreske.ui \
    dialogexit.ui \
    dialogsave.ui \
    dialoginsert.ui \
    dialogfps.ui \
    dialogprocess.ui \
    dialogmove.ui \
    dialog.ui

RESOURCES += \
    myresources.qrc
