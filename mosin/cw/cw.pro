QT += core gui

greaterThan(QT_MAJOR_VERSION, 4) : QT += widgets

CONFIG += c++17

HEADERS += \
    programgen.h \
    scene.h \
    statistic.h \
    tree.h \
    usergen.h \
    window.h

SOURCES += \
    main.cpp \
    programgen.cpp \
    scene.cpp \
    statistic.cpp \
    tree.cpp \
    usergen.cpp \
    window.cpp

DISTFILES += \
    input_file.txt
