TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    reppu.cpp \
    tuotantoketju.cpp \
    tiedostonluku.cpp \
    apufunktiot.cpp \
    kayttoliittyma.cpp

HEADERS += \
    reppu.hh \
    tuotantoketju.hh \
    tiedostonluku.hh \
    apufunktiot.hh \
    kayttoliittyma.hh

OTHER_FILES += \
    reseptit.txt \
    reseptit-complex.txt

DISTFILES += \
    reseptit.txt

