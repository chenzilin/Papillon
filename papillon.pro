# QT Modules
QT += core gui widgets

# Target
TARGET = Papillon
TEMPLATE = app

# Headers and sources
SOURCE_FOLDER = src
HEADER_FOLDER = src/include

INCLUDEPATH += $$HEADER_FOLDER
HEADERS += $$HEADER_FOLDER/mainwindow.h \
	$$HEADER_FOLDER/aboutdlg.h \
	$$HEADER_FOLDER/resultwidget.h \
	$$HEADER_FOLDER/codeeditorwidget.h \
	$$HEADER_FOLDER/dirsviewwidget.h \
	$$HEADER_FOLDER/helpdlg.h \
	$$HEADER_FOLDER/openedfilesviewwidget.h \
	$$HEADER_FOLDER/taglistwidget.h \
	$$HEADER_FOLDER/codeeditor.h \
	$$HEADER_FOLDER/syntaxhighlighter.h

SOURCES += $$SOURCE_FOLDER/main.cpp \
	$$SOURCE_FOLDER/mainwindow.cpp \
	$$SOURCE_FOLDER/aboutdlg.cpp \
	$$SOURCE_FOLDER/resultwidget.cpp \
	$$SOURCE_FOLDER/codeeditorwidget.cpp \
	$$SOURCE_FOLDER/dirsviewwidget.cpp \
	$$SOURCE_FOLDER/helpdlg.cpp \
	$$SOURCE_FOLDER/openedfilesviewwidget.cpp \
	$$SOURCE_FOLDER/taglistwidget.cpp \
	$$SOURCE_FOLDER/codeeditor.cpp \
	$$SOURCE_FOLDER/syntaxhighlighter.cpp

# Forms
FORMS_FOLDER = src
FORMS += $$FORMS_FOLDER/mainwindow.ui \
	$$FORMS_FOLDER/helpdlg.ui \
	$$FORMS_FOLDER/aboutdlg.ui

# Resources
RESOURCES += papillon.qrc

# Objects Pathes
DESTDIR = bin
UI_DIR = build
MOC_DIR = build
RCC_DIR = build
OBJECTS_DIR = build
