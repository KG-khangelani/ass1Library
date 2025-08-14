TEMPLATE = subdirs

SUBDIRS += lib app

lib.file = LibraryUtils/LibraryUtils.pro
lib.target = LibraryUtils

app.file = ass1Library.pro
app.target = ass1Library
app.depends = lib
