###############################################################################
 #
 # Copyright (C) 2019-2020 Markus Zehnder <business@markuszehnder.ch>
 #
 # This file is part of the YIO-Remote software project.
 #
 # YIO-Remote software is free software: you can redistribute it and/or modify
 # it under the terms of the GNU General Public License as published by
 # the Free Software Foundation, either version 3 of the License, or
 # (at your option) any later version.
 #
 # YIO-Remote software is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 # GNU General Public License for more details.
 #
 # You should have received a copy of the GNU General Public License
 # along with YIO-Remote software. If not, see <https://www.gnu.org/licenses/>.
 #
 # SPDX-License-Identifier: GPL-3.0-or-later
 #############################################################################/

#
# Common helper project include to set output path based on platform & compiler
#

# -----------------------------------------------------------------------------
# Qt Linguist tools
# -----------------------------------------------------------------------------
# lupdate & lrelease integration in qmake is a major pain to get working on Linux, macOS, Windows PLUS Linux arm cross compile PLUS qmake / make cmd line!
# There are so many different ways and each one works great on SOME platform(s) only :-(
# So this here might look excessive but I found no other reliable way to make it work on as many environments as possible...
# 1.) Check if we get the linguist cmd line tools from the QT installation (works in Qt Creator on Linux, macOS and Win but not with Buildroot / Linux crosscompile)
exists($$[QT_INSTALL_BINS]/lupdate):QMAKE_LUPDATE = $$[QT_INSTALL_BINS]/lupdate
exists($$[QT_INSTALL_BINS]/lrelease):QMAKE_LRELEASE = $$[QT_INSTALL_BINS]/lrelease
  # think about our Windows friends
exists($$[QT_INSTALL_BINS]/lupdate.exe):QMAKE_LUPDATE = $$[QT_INSTALL_BINS]/lupdate.exe
exists($$[QT_INSTALL_BINS]/lrelease.exe):QMAKE_LRELEASE = $$[QT_INSTALL_BINS]/lrelease.exe
# 2.) Check if it's available from $HOST_DIR env var which is set during Buildroot. Only use it if it's not already defined (*=).
exists($$(HOST_DIR)/bin/lupdate):QMAKE_LUPDATE *= $$(HOST_DIR)/bin/lupdate
exists($$(HOST_DIR)/bin/lrelease):QMAKE_LRELEASE *= $$(HOST_DIR)/bin/lrelease
# 3.) Linux Qt Creator arm cross compile: QT_INSTALL_BINS is NOT available, but host tools should be available in QTDIR
exists($$(QTDIR)/bin/lupdate):QMAKE_LUPDATE *= $$(QTDIR)/bin/lupdate
exists($$(QTDIR)/bin/lrelease):QMAKE_LRELEASE *= $$(QTDIR)/bin/lrelease
# 4.) Fallback: custom env var QT_LINGUIST_DIR (which can also be used to override the tools found in the path)
exists($$(QT_LINGUIST_DIR)/lupdate):QMAKE_LUPDATE *= $$(QT_LINGUIST_DIR)/lupdate
exists($$(QT_LINGUIST_DIR)/lrelease):QMAKE_LRELEASE *= $$(QT_LINGUIST_DIR)/lrelease
# 5.) Last option: check path, plain and simple. (Would most likely be enough on most systems...)
if(isEmpty(QMAKE_LUPDATE)) {
    win32:QMAKE_LUPDATE    = $$system(where lupdate)
    unix|mac:QMAKE_LUPDATE = $$system(which lupdate)
}
if(isEmpty(QMAKE_LRELEASE)) {
    win32:QMAKE_LRELEASE    = $$system(where lrelease)
    unix|mac:QMAKE_LRELEASE = $$system(which lrelease)
}

# -----------------------------------------------------------------------------
# TARGET PLATFORM
# -----------------------------------------------------------------------------

win32 {
    CONFIG += PLATFORM_WIN
    message(PLATFORM_WIN)
    win32-g++ {
        CONFIG += COMPILER_GCC
        message(COMPILER_GCC)
    }
    win32-msvc* {
        # looks like they changed the config values with Qt 5.9: https://stackoverflow.com/a/46050538
        # Where's the damn documentation of available environment variables? Try and error with non-working Stackoverflow solutions ain't funny!
        #message($$CONFIG)
        # last resort: print everything to find the magic variable name...
        # WARNING: ONLY FOR DEBUGGING! This is slow and prints a LONG list
        #for(var, $$list($$enumerate_vars())) {
        #    message($$var)
        #    message($$eval($$var))
        #}
        MSVC_VER = $$(VisualStudioVersion)
        equals(MSVC_VER, 14.0){
            message("Visual Studio version: $$(VisualStudioVersion): MSVC 2015")
            CONFIG += COMPILER_MSVC2015
            message(COMPILER_MSVC2015)
        }
        equals(MSVC_VER, 15.0){
            message("Visual Studio version: $$(VisualStudioVersion): MSVC 2017")
            CONFIG += COMPILER_MSVC2017
            message(COMPILER_MSVC2017)
        }
        # untested!
        equals(MSVC_VER, 16.0){
            message("Visual Studio version: $$(VisualStudioVersion): MSVC 2019")
            CONFIG += COMPILER_MSVC2019
            message(COMPILER_MSVC2019)
        }

       # Probably no longer required. Initially taken from a Qt5 book which used no longer valid win32-msvc2017 directives
        #win32-msvc:QMAKE_TARGET.arch = x86_64
    }

}

linux {
    CONFIG += PLATFORM_LINUX
    message(PLATFORM_LINUX)
    # Make QMAKE_TARGET arch available for Linux
    !contains(QT_ARCH, x86_64){
        QMAKE_TARGET.arch = x86
    } else {
        QMAKE_TARGET.arch = x86_64
    }
    linux-g++{
        CONFIG += COMPILER_GCC
        message(COMPILER_GCC)
    }
}

macx {
    CONFIG += PLATFORM_OSX
    message(PLATFORM_OSX)
    macx-clang {
        CONFIG += COMPILER_CLANG
        message(COMPILER_CLANG)
        QMAKE_TARGET.arch = x86_64
    }
    macx-clang-32{
        CONFIG += COMPILER_CLANG
        message(COMPILER_CLANG)
        QMAKE_TARGET.arch = x86
    }
}

contains(QMAKE_TARGET.arch, x86_64) {
    CONFIG += PROCESSOR_x64
    message(PROCESSOR_x64)
} else {
    # TODO also test for arm?
    CONFIG += PROCESSOR_x86
    message(PROCESSOR_x86)
}

CONFIG(debug, release|debug) {
    CONFIG += BUILD_DEBUG
    message(BUILD_DEBUG)
} else {
    CONFIG += BUILD_RELEASE
    message(BUILD_RELEASE)
}

# -----------------------------------------------------------------------------
# DESTINATION PATH
# -----------------------------------------------------------------------------

platform_path = unknown-platform
compiler_path = unknown-compiler
processor_path = unknown-processor
build_path = unknown-build

PLATFORM_WIN {
    platform_path = windows
}
PLATFORM_OSX {
    platform_path = osx
}
PLATFORM_LINUX {
    platform_path = linux
}

COMPILER_GCC {
    compiler_path = gcc
}
COMPILER_MSVC2017 {
    compiler_path = msvc2017
}
COMPILER_CLANG {
    compiler_path = clang
}

PROCESSOR_x64 {
    processor_path = x64
}
PROCESSOR_x86 {
    processor_path = x86
}

# Special treatment for cross compiling!
equals(QT_ARCH, arm): {
    platform_path = linux
    compiler_path = gcc
    processor_path = arm
}

BUILD_DEBUG {
    build_path = debug
} else {
    build_path = release
}

DESTINATION_PATH = $${platform_path}-$${compiler_path}-$${processor_path}/$$build_path
message(Dest path: $${DESTINATION_PATH})

# Configure destination path by "Operating System/Compiler/Processor Architecture/Build Configuration"
DESTDIR = $$(YIO_BIN)
DESTDIR_BIN = $$(YIO_BIN)
isEmpty(DESTDIR) {
    DESTDIR = $$(YIO_SRC)
    isEmpty(DESTDIR) {
        DESTDIR_BIN = $$clean_path($$PWD/../binaries)
        DESTDIR = $$DESTDIR_BIN/$$DESTINATION_PATH
        message(Environment variables YIO_BIN and YIO_SRC not defined! Using '$$DESTDIR' as binary output directory.)
    } else {
        DESTDIR_BIN = $$clean_path($$(YIO_SRC)/binaries)
        DESTDIR = $$DESTDIR_BIN/$$DESTINATION_PATH
        message(YIO_SRC is set: using '$$DESTDIR' as binary output directory.)
    }
} else {
    message(YIO_BIN defined '$$DESTDIR' as binary output directory.)
}
