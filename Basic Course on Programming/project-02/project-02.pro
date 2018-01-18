TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cc \
    tiedostonluku.cc \
    tietokanta.cc \
    paloittelija.cc

HEADERS += \
    tiedostonluku.hh \
    tietokanta.hh \
    paloittelija.hh
