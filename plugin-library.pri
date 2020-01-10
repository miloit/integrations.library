# Project Include file for plugins only!
# May NOT be included by remote-software

# Add all common header files
include(yio-interfaces.pri)

INCLUDEPATH += $$PWD/sources

# Additional files
HEADERS += \
    $$PWD/include/yio-plugin/integration.h

# FIXME(zehnm) integrate & adapt enhancements
#HEADERS += $$PWD/sources/yio-plugin/plugin.h \
#    $$PWD/sources/yio-plugin/integrationproxy.h

#SOURCES += $$PWD/sources/yio-plugin/plugin.cpp \
#    $$PWD/sources/yio-plugin/integration.cpp \
#    $$PWD/sources/yio-plugin/integrationproxy.cpp

