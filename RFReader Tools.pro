#-------------------------------------------------
#
# Project created by QtCreator 2019-06-13T10:20:34
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = RFMXXX_TEST
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
CONFIG += qwt


SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

#INCLUDEPATH += H:/QWT/include
#LIBS += -LH:/QWT/lib–lqwt

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -LC:/qwt-6.1.6/QWT_LIB/lib/ -lqwt
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/qwt-6.1.6/QWT_LIB/lib/ -lqwtd
else:unix: LIBS += -L$$PWD/../../../qwt-6.1.6/QWT_LIB/lib/ -lqwt

INCLUDEPATH += C:/qwt-6.1.6/QWT_LIB/include
DEPENDPATH += C:/qwt-6.1.6/QWT_LIB/include

#INCLUDEPATH += H:/fftw/
#LIBS += -L H:\fftw -lfftw3-3

