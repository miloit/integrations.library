# Project Include file for plugins only!
# May NOT be included by remote-software

# Add all common header files
include(yio-interfaces.pri)

INCLUDEPATH += $$PWD/src

# Additional plugin files
HEADERS += \
    $$PWD/src/yio-plugin/integration.h

# FIXME(zehnm) integrate & adapt enhancements
#HEADERS += $$PWD/src/yio-plugin/plugin.h \
#    $$PWD/src/yio-plugin/integrationproxy.h

#SOURCES += $$PWD/src/yio-plugin/plugin.cpp \
#    $$PWD/src/yio-plugin/integration.cpp \
#    $$PWD/src/yio-plugin/integrationproxy.cpp
