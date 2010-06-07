#include <QMessageBox>
#include <QPushButton>
#include "dlgpreferences.h"
#include "watta.h"

cDlgPreferences::cDlgPreferences( QWidget *p_poParent )
    : QDialog( p_poParent )
{
    cTracer obTrace( "cDlgPreferences::cDlgPreferences" );

    setupUi( this );

    QString qsTitle( g_poPrefs->getAppName() + " Version " + g_poPrefs->getVersion() );
    setWindowTitle( qsTitle );

    m_poPreferencesAction = new QAction( QString::fromStdString( "&Preferences" ), this );
    connect( m_poPreferencesAction, SIGNAL( triggered() ), this, SLOT( show() ) );

    m_poTasksAction = new QAction( QString::fromStdString( "&Tasks" ), this );

    m_poQuitAction = new QAction( QString::fromStdString( "&Quit" ), this );
    connect( m_poQuitAction, SIGNAL( triggered() ), qApp, SLOT( quit() ) );

    m_poTrayIconMenu = new QMenu( this );
    m_poTrayIconMenu->addAction( m_poPreferencesAction );
    m_poTrayIconMenu->addAction( m_poTasksAction );
    m_poTrayIconMenu->addSeparator();
    m_poTrayIconMenu->addAction( m_poQuitAction );

    m_poTrayIcon = new QSystemTrayIcon( this );
    m_poTrayIcon->setContextMenu( m_poTrayIconMenu );
    m_poTrayIcon->setIcon( QIcon( ":/images/green.jpeg" ) );
    m_poTrayIcon->setVisible( true );
    m_poTrayIcon->setToolTip( qsTitle );

    unsigned int  uiConLevel, uiDBLevel, uiGUILevel;
    g_poPrefs->getLogLevels( &uiConLevel, &uiDBLevel, &uiGUILevel );
    sliConsoleLogLevel->setValue( uiConLevel );
    sliDBLogLevel->setValue( uiDBLevel );
    sliGUILogLevel->setValue( uiGUILevel );

    ledWorkDayEnd->setText( g_poPrefs->getWorkDayEnd() );
    ledWorkDayLen->setText( g_poPrefs->getWorkDayLength() );
}

void cDlgPreferences::on_sliConsoleLogLevel_valueChanged( int p_inValue )
{
    lblConsoleLogLevelValue->setText( cSeverity::toStr( (cSeverity::teSeverity)p_inValue ) );
}

void cDlgPreferences::on_sliDBLogLevel_valueChanged( int p_inValue )
{
    lblDBLogLevelValue->setText( cSeverity::toStr( (cSeverity::teSeverity)p_inValue ) );
}

void cDlgPreferences::on_sliGUILogLevel_valueChanged( int p_inValue )
{
    lblGUILogLevelValue->setText( cSeverity::toStr( (cSeverity::teSeverity)p_inValue ) );
}

void cDlgPreferences::accept()
{
    g_poPrefs->setLogLevels( sliConsoleLogLevel->value(),
                             sliDBLogLevel->value(),
                             sliGUILogLevel->value() );

    g_poPrefs->setWorkDayEnd( ledWorkDayEnd->text() );
    g_poPrefs->setWorkDayLength( ledWorkDayLen->text() );

    g_poPrefs->save();

    QDialog::accept();
}
