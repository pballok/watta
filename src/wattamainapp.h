#ifndef WATTAMAINAPP_H
#define WATTAMAINAPP_H

#include <QApplication>

#include "dlgpreferences.h"
#include "workday.h"

class cWattaMainApp : public QApplication
{
    Q_OBJECT

public:
    cWattaMainApp( int &argc, char **argv );
    ~cWattaMainApp();

    void startSession( cDlgPreferences *p_poMainDlg )   throw();

public slots:
    void endSession()     throw();

protected:
    void timerEvent ( QTimerEvent *p_poEvent );

private:
    cWorkDay         *m_poCurrWorkDay;
    cDlgPreferences  *m_poMainDlg;
    int               m_inTimerId;

};

#endif // WATTAMAINAPP_H
