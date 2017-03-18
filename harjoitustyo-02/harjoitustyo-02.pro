TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    splitter.cpp \
    tiedoston_luku.cpp \
    apufunktiot.cpp \
    hakufunktiot.cpp

HEADERS += \
    splitter.hh \
    tiedoston_luku.hh \
    apufunktiot.hh \
    hakufunktiot.hh

OTHER_FILES += \
    tuotetiedot.txt

DISTFILES += \
    tuotetiedot.txt

