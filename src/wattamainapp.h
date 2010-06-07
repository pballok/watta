#ifndef WATTAMAINAPP_H
#define WATTAMAINAPP_H

#include <QApplication>
#include <QDialog>

#include "workday.h"

class cWattaMainApp : public QApplication
{
    Q_OBJECT

public:
    cWattaMainApp( int &argc, char **argv );
    ~cWattaMainApp();

    void startSession( QDialog *p_poMainDlg )   throw();

public slots:
    void endSession()     throw();

private:
    cWorkDay  *m_poCurrWorkDay;
    QDialog   *m_poMainDlg;
};

#endif // WATTAMAINAPP_H
