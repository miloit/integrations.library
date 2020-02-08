# Project Include file for weather model
# MUST be included by remote-software
# May be included by integration plugins with weather functionality

INCLUDEPATH += $$PWD/src

# Model files
HEADERS += \
    $$PWD/src/yio-model/weather/weathermodel.h

SOURCES += \
    $$PWD/src/yio-model/weather/weathermodel.cpp
