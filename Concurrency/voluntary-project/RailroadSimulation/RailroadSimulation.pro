TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
LIBS += -pthread
CONFIG -= qt

SOURCES += \
        main.cpp \
    railroadjunction.cc \
    train.cc \
    location.cc \
    trafficstatus.cc \
    connection.cc

HEADERS += \
    railroadjunction.hh \
    train.hh \
    constants.h \
    location.hh \
    trafficstatus.hh \
    connection.hh
