#include <QMessageBox>
#include <QPushButton>
#include "dlgpreferences.h"
#include "watta.h"

cDlgPreferences::cDlgPreferences( QWidget *p_poParent )
    : QDialog( p_poParent )
{
    cTracer obTrace( &g_obLogger, "cDlgPreferences::cDlgPreferences" );

    setupUi( this );

    QString qsTitle( g_poPrefs->appName() + " Version " + g_poPrefs->version() );
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

    sliGUILogLevel->setValue( g_poPrefs->GUILogLevel() );
    sliFileLogLevel->setValue( g_poPrefs->fileLogLevel() );

    ledWorkDayEnd->setText( g_poPrefs->workDayEnd() );
    ledWorkDayLen->setText( g_poPrefs->workDayLength() );
}

void cDlgPreferences::setIconToolTip( const QString &p_qsToolTip )
{
    m_poTrayIcon->setToolTip( p_qsToolTip );
}

void cDlgPreferences::on_sliFileLogLevel_valueChanged( int p_inValue )
{
    lblFileLogLevelValue->setText( cSeverity::toStr( (cSeverity::teSeverity)p_inValue ) );
}

void cDlgPreferences::on_sliGUILogLevel_valueChanged( int p_inValue )
{
    lblGUILogLevelValue->setText( cSeverity::toStr( (cSeverity::teSeverity)p_inValue ) );
}

void cDlgPreferences::accept()
{
    g_poPrefs->setGUILogLevel( (cSeverity::teSeverity)sliGUILogLevel->value() );
    g_poPrefs->setFileLogLevel( (cSeverity::teSeverity)sliFileLogLevel->value() );

    g_poPrefs->setWorkDayEnd( ledWorkDayEnd->text() );
    g_poPrefs->setWorkDayLength( ledWorkDayLen->text() );

    g_poPrefs->save();

    QDialog::accept();
}
