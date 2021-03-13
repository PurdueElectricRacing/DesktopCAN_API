log("including" $$PWD/inc)

INCLUDEPATH += $$PWD/inc

SOURCES += $$PWD/src/canframe.cpp

HEADERS += $$PWD/inc/can_api.h \
    $$PWD/inc/can_exceptions.h \
    $$PWD/inc/can_interface.h \
    $$PWD/inc/can_parsing.h \
    $$PWD/inc/canframe.h

win32: LIBS += -lSetupApi
win32: LIBS += -lOle32
win32: LIBS += -lwinusb

win32:SOURCES += \
    $$PWD/candle/gsusb.c \
    $$PWD/candle/candle.c \
    $$PWD/candle/candle_ctrl_req.c \
    $$PWD/candle/WinCan.cpp \

win32:HEADERS += \
    $$PWD/candle/ch_9.h \
    $$PWD/candle/gsusb_def.h \
    $$PWD/candle/gsusb.h \
    $$PWD/candle/candle.h \
    $$PWD/candle/candle_defs.h \
    $$PWD/candle/candle_ctrl_req.h \
    $$PWD/candle/WinCan.h \
    $$PWD/inc/canframe.h \
    $$PWD/inc/can_api.h  \


win32:INCLUDEPATH += $$PWD/candle/inc

unix:INCLUDEPATH += $$PWD/socketcan

unix:HEADERS += $$PWD/socketcan/socketcan_if.h


unix:SOURCES += $$PWD/socketcan/socketcan_if.cpp
