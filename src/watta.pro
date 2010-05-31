TEMPLATE = app
FORMS = dlglogs.ui \
    dlgpreferences.ui
HEADERS = watta.h \
    sevexception.h \
    tracer.h \
    dbconnection.h \
    qtmysqlconnection.h \
    qtmysqlquerymodel.h \
    qtlogger.h \
    preferences.h \
    dlglogs.h \
    dlgpreferences.h \
    session.h \
    wattamainapp.h
SOURCES = tracer.cpp \
    dbconnection.cpp \
    qtmysqlconnection.cpp \
    qtmysqlquerymodel.cpp \
    qtlogger.cpp \
    preferences.cpp \
    main.cpp \
    dlglogs.cpp \
    dlgpreferences.cpp \
    session.cpp \
    wattamainapp.cpp
DESTDIR = ..
QT += sql
CONFIG += qt
CONFIG += console
RESOURCES += watta.qrc
