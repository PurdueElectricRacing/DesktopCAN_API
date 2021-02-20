QT += core
QT -= gui

CONFIG += c++17 debug
QMAKE_CFLAGS += -std=c99
QMAKE_LFLAGS += -static-libgcc -static-libstdc++

TARGET = example
CONFIG += console
CONFIG -= app_bundle

SUBDIRS += ../inc ../src ../socketcan ../candle

OBJECTS_DIR = obj/
DESTDIR = build/

TEMPLATE = app

INCLUDEPATH += ../inc

SOURCES += ../src/canframe.cpp

HEADERS += ../inc/can_api.h \
    ../inc/can_exceptions.h \
    ../inc/can_interface.h \
    ../inc/can_parsing.h \
    ../inc/canframe.h

win32: LIBS += -lSetupApi
win32: LIBS += -lOle32
win32: LIBS += -lwinusb

win32:SOURCES += main_win.cpp \
    ../candle/gsusb.c \
    ../candle/candle.c \
    ../candle/candle_ctrl_req.c \
    ../candle/WinCan.cpp \

win32:HEADERS += \
    ../candle/ch_9.h \
    ../candle/gsusb_def.h \
    ../candle/gsusb.h \
    ../candle/candle.h \
    ../candle/candle_defs.h \
    ../candle/candle_ctrl_req.h \
    ../candle/WinCan.h \
    ../inc/canframe.h \
    ../inc/can_api.h


win32:INCLUDEPATH += ../candle

unix:INCLUDEPATH += ../socketcan

unix:HEADERS += socketcan_if.h


unix:SOURCES += main_sc.cpp ../socketcan/socketcan_if.cpp
