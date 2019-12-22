TEMPLATE       = lib
CONFIG         += staticlib

REMOTE_SRC = $$(YIO_SRC)
isEmpty(REMOTE_SRC) {
    REMOTE_SRC = $$clean_path($$PWD/../remote-software)
    warning("Environment variables YIO_SR not defined! Using '$$REMOTE_SRC' for remote-software project.")
} else {
    REMOTE_SRC = $$(YIO_SRC)/remote-software
    message("YIO_SRC is set: using '$$REMOTE_SRC' for remote-software project.")
}

include($$REMOTE_SRC/qmake-target-platform.pri)
include($$REMOTE_SRC/qmake-destination-path.pri)

HEADERS         = plugin.h integration.h integrationproxy.h \
                  media_player/albummodel_mediaplayer.h media_player/searchmodel_mediaplayer.h \
                  weather\weathermodel.h \
                  $$REMOTE_SRC/sources/integrations/integrationinterface.h \
                  $$REMOTE_SRC/sources/integrations/plugininterface.h

SOURCES         = plugin.cpp integration.cpp integrationproxy.cpp \
                  media_player/albummodel_mediaplayer.cpp media_player/searchmodel_mediaplayer.cpp \
                  weather\weathermodel.cpp

TARGET          = integrationslibrary

# Configure destination path. DESTDIR is set in qmake-destination-path.pri
OBJECTS_DIR = $$PWD/build/$$DESTINATION_PATH/obj
MOC_DIR = $$PWD/build/$$DESTINATION_PATH/moc
RCC_DIR = $$PWD/build/$$DESTINATION_PATH/qrc
UI_DIR = $$PWD/build/$$DESTINATION_PATH/ui

# install
unix {
    target.path = /usr/lib
    INSTALLS += target
}
