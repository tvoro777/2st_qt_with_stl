QT += core gui widgets

CONFIG += c++17

SOURCES += \
    src/reader_filter/reader_filter.cpp \
    src/gui/mainwindow.cpp \
    src/main.cpp

HEADERS += \
    src/reader_filter/reader_filter.h \
    src/gui/mainwindow.h

FORMS += \
    src/gui/mainwindow.ui
