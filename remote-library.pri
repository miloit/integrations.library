# Project Include file for remote-software only!
# May NOT be included by integration plugins.

# Add all common header files
include(yio-interfaces.pri)

INCLUDEPATH += $$PWD/sources

# Additional files
HEADERS += \
    $$PWD/sources/shared/mediaplayer/albummodel_mediaplayer.h \
    $$PWD/sources/shared/mediaplayer/searchmodel_mediaplayer.h \
    $$PWD/sources/shared/weather/weathermodel.h

SOURCES += \
    $$PWD/sources/shared/mediaplayer/albummodel_mediaplayer.cpp \
    $$PWD/sources/shared/mediaplayer/searchmodel_mediaplayer.cpp \
    $$PWD/sources/shared/weather/weathermodel.cpp
