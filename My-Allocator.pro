TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    my-allocator.c

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    my-allocator.h

