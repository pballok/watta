#include "wattamainapp.h"
#include "watta.h"

cWattaMainApp::cWattaMainApp( int &argc, char **argv ) : QApplication( argc, argv )
{
    cTracer obTrace( "cWattaMainApp::cWattaMainApp" );
    m_poCurrWorkDay = NULL;
    m_poMainDlg     = NULL;

    connect( this, SIGNAL( aboutToQuit() ), this, SLOT( endSession() ) );
}

cWattaMainApp::~cWattaMainApp()
{
    cTracer obTrace( "cWattaMainApp::~cWattaMainApp" );
}

void cWattaMainApp::startSession( QDialog *p_poMainDlg ) throw()
{
    cTracer obTrace( "cWattaMainApp::startSession" );

    m_poCurrWorkDay = new cWorkDay();
    m_poMainDlg = p_poMainDlg;
}

void cWattaMainApp::endSession() throw()
{
    cTracer obTrace( "cWattaMainApp::endSession" );

    if( m_poCurrWorkDay ) delete m_poCurrWorkDay;

    g_obLogger << cSeverity::INFO;
    g_obLogger << g_poPrefs->getAppName().toStdString() << " Version " << g_poPrefs->getVersion().toStdString() << " ended.";
    g_obLogger << cQTLogger::EOM;
}
