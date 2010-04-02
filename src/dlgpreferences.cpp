#include <QMessageBox>
#include <QPushButton>
#include "dlgpreferences.h"
#include "watta.h"

cDlgPreferences::cDlgPreferences( QWidget *p_poParent )
    : QDialog( p_poParent )
{
    cTracer obTrace( "cDlgPreferences::cDlgPreferences" );

    setupUi( this );

    unsigned int  uiConLevel, uiDBLevel, uiGUILevel;
    g_poPrefs->getLogLevels( &uiConLevel, &uiDBLevel, &uiGUILevel );
    sliConsoleLogLevel->setValue( uiConLevel );
    sliDBLogLevel->setValue( uiDBLevel );
    sliGUILogLevel->setValue( uiGUILevel );
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

    g_poPrefs->save();

    QDialog::accept();
}
