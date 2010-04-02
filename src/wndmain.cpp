#include <QMessageBox>

#include "wndmain.h"
#include "dlgpreferences.h"
#include "dlglogs.h"
#include "watta.h"

cWndMain::cWndMain( QWidget *parent )
    : QMainWindow( parent )
{
    cTracer obTrace( "cWndMain::cWndMain" );

    setupUi( this );
}

cWndMain::~cWndMain()
{
    cTracer obTrace( "cWndMain::~cWndMain" );
}

void cWndMain::on_action_Preferences_triggered()
{
    cTracer obTrace( "cWndMain::on_action_Preferences_triggered" );

    cDlgPreferences  obDlgPrefs( this );

    obDlgPrefs.exec();
}

void cWndMain::on_action_Logs_triggered()
{
    cTracer obTrace( "cWndMain::on_action_Logs_triggered" );

    cDlgLogs  obDlgLogs( this );

    obDlgLogs.exec();
}
