#include <QApplication>
#include <QString>
#include <QSettings>
#include <QMessageBox>
#include <QTranslator>

#include "qtlogger.h"
#include "qtmysqlconnection.h"
#include "preferences.h"
#include "wndmain.h"

cQTLogger             g_obLogger;
cQTMySQLConnection   *g_poDB;
cPreferences         *g_poPrefs;

int main( int argc, char *argv[] )
{
    QApplication  apMainApp( argc, argv );

    g_poDB     = new cQTMySQLConnection;

    g_poPrefs  = new cPreferences( QString::fromAscii( "watta" ) );
    g_poPrefs->setVersion( "0.1.0" );
    g_poPrefs->setDBAccess( "localhost", "watta", "watta", "watta" );

    try
    {
        g_poDB->open();
        g_obLogger.setDBConnection( g_poDB );
    }
    catch( cSevException &e )
    {
        g_obLogger << e.severity();
        g_obLogger << e.what();
        g_obLogger << cQTLogger::EOM;
    }

    g_obLogger << cSeverity::INFO;
    g_obLogger << g_poPrefs->getAppName().toStdString() << " Version " << g_poPrefs->getVersion().toStdString() << " started.";
    g_obLogger << cQTLogger::EOM;

    cWndMain  obMainWindow;
    obMainWindow.show();

    int r = apMainApp.exec();

    g_obLogger << cSeverity::INFO;
    g_obLogger << g_poPrefs->getAppName().toStdString() << " Version " << g_poPrefs->getVersion().toStdString() << " ended.";
    g_obLogger << cQTLogger::EOM;

    delete g_poDB;

    return r;
}
