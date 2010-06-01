#ifndef WATTAMAINAPP_H
#define WATTAMAINAPP_H

#include <QApplication>

#include "workday.h"

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
    cWorkDay  *m_poCurrWorkDay;
};

#endif // WATTAMAINAPP_H
