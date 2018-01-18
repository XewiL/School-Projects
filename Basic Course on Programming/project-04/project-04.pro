TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cc \
    paloittelija.cc \
    syotteenluku.cc \
    tietokanta.cc

HEADERS += \
    paloittelija.hh \
    syotteenluku.hh \
    tietokanta.hh
