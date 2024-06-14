TEMPLATE = app
INCLUDEPATH += include
HEADERS = include/resume.h
SOURCES = src/resume.cpp src/main.cpp
TARGET = resume
QT = core gui widgets printsupport
LIBS += -lpoppler-qt5

MOC_DIR = objs
OBJECTS_DIR = objs

