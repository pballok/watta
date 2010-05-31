#ifndef WATTAMAINAPP_H
#define WATTAMAINAPP_H

#include <QApplication>

#include "session.h"

class cWattaMainApp : public QApplication
{
    Q_OBJECT

public:
    cWattaMainApp( int &argc, char **argv );
    ~cWattaMainApp();

    void startSession()   throw();

public slots:
    void endSession()     throw();

private:
    cSession  *m_poSession;
};

#endif // WATTAMAINAPP_H
