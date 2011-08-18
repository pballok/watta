#include <QtGui>
#include <QApplication>
#include <QString>
#include <QMessageBox>

#include <iostream>
#include <logger.h>
#include <guiwriter.h>
#include <filewriter.h>
#include <qtmysqlconnection.h>

#include "preferences.h"
#include "dlgpreferences.h"
#include "wattamainapp.h"

cLogger             g_obLogger;
cQTMySQLConnection *g_poDB;
cPreferences       *g_poPrefs;

using namespace std;

int main( int argc, char *argv[] )
{
    int  inRetVal = 1;

    g_poDB = NULL;
    g_poPrefs = NULL;

    cWattaMainApp  apMainApp( argc, argv );

    cGUIWriter  obGUIWriter;
    g_obLogger.registerWriter( &obGUIWriter );

    cFileWriter obFileWriter( cSeverity::NONE, "watta.log", cFileWriter::APPEND );
    g_obLogger.registerWriter( &obFileWriter );

    try
    {
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

        g_poDB     = new cQTMySQLConnection( &g_obLogger );

        g_poPrefs  = new cPreferences( "watta", "0.3.0", &obGUIWriter, &obFileWriter );

        g_poDB->setHostName( g_poPrefs->dbHost() );
        g_poDB->setDatabaseName( g_poPrefs->dbSchema() );
        g_poDB->setUserName( g_poPrefs->dbUser() );
        g_poDB->setPassword( g_poPrefs->dbPassword() );
        g_poDB->open();

        g_obLogger << cSeverity::INFO
                   << g_poPrefs->appName().toStdString() << " Version " << g_poPrefs->version().toStdString() << " started."
                   << cLogMessage::EOM;

        cWattaMainApp::setQuitOnLastWindowClosed( false );

        cDlgPreferences  obMainWindow;

        apMainApp.startSession( &obMainWindow );
        inRetVal = apMainApp.exec();
    }
    catch( cSevException &e )
    {
        g_obLogger << cSeverity::ERROR << "WHOA... Just caught an unhandled exception!" << cLogMessage::EOM;
        g_obLogger << e;

        inRetVal = 1;
    }

    g_obLogger << cSeverity::INFO
               << g_poPrefs->appName().toStdString() << " Version " << g_poPrefs->version().toStdString() << " ended."
               << cLogMessage::EOM;

    cerr << "Point1" << endl;
    if( g_poDB ) delete g_poDB;
    cerr << "Point2" << endl;
    if( g_poPrefs ) delete g_poPrefs;
    cerr << "Point3" << endl;

    return inRetVal;
}
