TEMPLATE = lib
TARGET = LibraryUtils
CONFIG += staticlib c++17 warn_on
QT += core
DEFINES += LIBRARYUTILS_LIBRARY

# This library lives under the main app folder; parent dir has book.h, magazine.h, etc.
INCLUDEPATH += $$PWD/..
INCLUDEPATH += $$PWD/include

# Put the built .lib/.a in a known place for the app to link against
DESTDIR = $$PWD/build/lib

HEADERS += \
    include/LibraryUtils/LibraryUtils_global.h \
    include/LibraryUtils/Persistence/FileStorage.h \
    include/LibraryUtils/Sorting/ItemSorter.h \
    include/LibraryUtils/Searching/BookSearch.h \
    include/LibraryUtils/Storage/Storage.h

SOURCES += \
    src/FileStorage.cpp \
    src/ItemSorter.cpp \
    src/BookSearch.cpp