TEMPLATE = app
FORMS = wndmain.ui \
    dlglogs.ui \
    dlgpreferences.ui
HEADERS = watta.h \
    sevexception.h \
    tracer.h \
    dbconnection.h \
    qtmysqlconnection.h \
    qtmysqlquerymodel.h \
    qtlogger.h \
    preferences.h \
    wndmain.h \
    dlglogs.h \
    dlgpreferences.h
SOURCES = tracer.cpp \
    dbconnection.cpp \
    qtmysqlconnection.cpp \
    qtmysqlquerymodel.cpp \
    qtlogger.cpp \
    preferences.cpp \
    main.cpp \
    wndmain.cpp \
    dlglogs.cpp \
    dlgpreferences.cpp
DESTDIR = ..
QT += sql
CONFIG += qt
CONFIG += console
