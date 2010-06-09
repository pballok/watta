#include <QtGui>
#include <QApplication>
#include <QString>
#include <QMessageBox>

#include "qtlogger.h"
#include "qtmysqlconnection.h"
#include "preferences.h"
#include "dlgpreferences.h"
#include "wattamainapp.h"

cQTLogger             g_obLogger;
cQTMySQLConnection   *g_poDB;
cPreferences         *g_poPrefs;

int main( int argc, char *argv[] )
{
    int  inRetVal = 1;

    g_poDB = NULL;
    g_poPrefs = NULL;

    try
    {
        cWattaMainApp  apMainApp( argc, argv );

        bool          boSysTrayFound = false;
        unsigned int  uiCheckCounter = 0;
        while( !boSysTrayFound && uiCheckCounter++ < 20 )
        {
            boSysTrayFound = QSystemTrayIcon::isSystemTrayAvailable();
            if( !boSysTrayFound ) sleep( 5 );
        }
        if( !boSysTrayFound )
        {
            throw cSevException( cSeverity::ERROR, "Couldn't detect any system tray on this system." );
        }

        g_poDB     = new cQTMySQLConnection;

        g_poPrefs  = new cPreferences( QString::fromAscii( "watta" ) );
        g_poPrefs->setVersion( "0.2.0" );
        g_poPrefs->setDBAccess( "localhost", "watta", "watta", "watta" );

        g_poDB->open();
        g_obLogger.setDBConnection( g_poDB );

        g_obLogger << cSeverity::INFO;
        g_obLogger << g_poPrefs->getAppName().toStdString() << " Version " << g_poPrefs->getVersion().toStdString() << " started.";
        g_obLogger << cQTLogger::EOM;

        cWattaMainApp::setQuitOnLastWindowClosed( false );

        cDlgPreferences  obMainWindow;

        apMainApp.startSession( &obMainWindow );
        inRetVal = apMainApp.exec();
    }
    catch( cSevException &e )
    {
        g_obLogger << e.severity() << e.what() << cQTLogger::EOM;
    }

    if( g_poDB ) delete g_poDB;
    if( g_poPrefs ) delete g_poPrefs;

    return inRetVal;
}
