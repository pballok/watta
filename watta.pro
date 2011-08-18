TEMPLATE = app
INCLUDEPATH += ../../qtframework
FORMS = dlgpreferences.ui
HEADERS = ../../qtframework/severity.h \
    ../../qtframework/sevexception.h \
    ../../qtframework/logger.h \
    ../../qtframework/logwriter.h \
    ../../qtframework/guiwriter.h \
    ../../qtframework/filewriter.h \
    ../../qtframework/logmessage.h \
    ../../qtframework/tracer.h \
    ../../qtframework/qtmysqlconnection.h \
    watta.h \
    preferences.h \
    dlgpreferences.h \
    session.h \
    wattamainapp.h \
    workday.h
SOURCES = ../../qtframework/logger.cpp \
    ../../qtframework/guiwriter.cpp \
    ../../qtframework/filewriter.cpp \
    ../../qtframework/logmessage.cpp \
    ../../qtframework/tracer.cpp \
    ../../qtframework/qtmysqlconnection.cpp \
    preferences.cpp \
    main.cpp \
    dlgpreferences.cpp \
    session.cpp \
    wattamainapp.cpp \
    workday.cpp
DESTDIR = ..
QT += sql
CONFIG += qt
RESOURCES += watta.qrc
