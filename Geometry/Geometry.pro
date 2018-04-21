TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    polygon.cpp \
    field.cpp \
    visibilitygraph.cpp

HEADERS += \
    model.h \
    polygon.h \
    field.h \
    visibilitygraph.h
