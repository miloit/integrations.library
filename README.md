
# YIO Integration Library Repository

For details about the YIO Remote projectes and the integration library, please visit our documentation repository which can be found under
<https://github.com/YIO-Remote/documentation/wiki>.

## Integration Library

This integration library contains all required header files to develop YIO integration plugins with Qt C++.  
Furthermore, there are shared model classes included to simplify media player integrations and common skeleton classes for plugin development.

This integration library is not a static linked library, but organized as plain Qt Project Include files (.pri). The main reason for this approach is to simplify the build processes and project organization since there are already four platforms which need to be supported (ARM, Linux, macOS, Windows). In the future this might be changed, for the moment we valued the simple setup higher than having static libraries for all platforms.

### Project Includes

#### yio-interface.pri

This include contains all plugin header files required to develop integration plugins. It is the minimal requirement for plugins.

#### yio-plugin-lib.pri

This includes additional skeleton classes to simplify plugin development.  
The `yio-interface.pri` project is included and doesn't need to be specified anymore.

#### yio-model-mediaplayer.pri

Shared media player model classes. This is only required for media player integrations.

#### yio-model-weather.pri

Shared weather model classes. This is only required for weather integrations.

## Plugin Project Setup

### Environment Setup

To develop a YIO Remote integration plugin this `integrations.library` project needs to be checked out and made accessible for the plugin project.  
We recommend to check out `integrations.library` on the same level as the plugin project. I.e. the library can be referenced with the default path `../integrations.library`.  
The only dependency of an integration project is this library. It is the mandatory dependency for plugins as well as the remote-software project.

Example for an imaginary FooBar plugin:

    ~/projects
    └── yio
        ├── integration.foobar
        ├── integrations.library
        └── remote-software

For other non-standard project setups there's the `YIO_SRC` environment variable. It needs to be initialized to the base directory of the integrations.library project.

### Plugin Project File

Blueprint to include one or more integration Qt project includes into the plugin project:

    INTG_LIB_PATH = $$(YIO_SRC)
    isEmpty(INTG_LIB_PATH) {
        INTG_LIB_PATH = $$clean_path($$PWD/../integrations.library)
        message("Environment variables YIO_SRC not defined! Using '$$INTG_LIB_PATH' for integrations.library project.")
    } else {
        INTG_LIB_PATH = $$(YIO_SRC)/integrations.library
        message("YIO_SRC is set: using '$$INTG_LIB_PATH' for integrations.library project.")
    }

    ! include($$INTG_LIB_PATH/yio-plugin-lib.pri) {
        error( "Cannot find the yio-plugin-lib.pri file!" )
    }
