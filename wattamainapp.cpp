#include "wattamainapp.h"
#include "watta.h"

cWattaMainApp::cWattaMainApp( int &argc, char **argv ) : QApplication( argc, argv )
{
    cTracer obTrace( &g_obLogger, "cWattaMainApp::cWattaMainApp" );
    m_poCurrWorkDay = NULL;
    m_poMainDlg     = NULL;
    m_inTimerId     = 0;

    connect( this, SIGNAL( aboutToQuit() ), this, SLOT( endSession() ) );
}

cWattaMainApp::~cWattaMainApp()
{
}

void cWattaMainApp::startSession( cDlgPreferences *p_poMainDlg ) throw()
{
    cTracer obTrace( &g_obLogger, "cWattaMainApp::startSession" );

    m_poCurrWorkDay = new cWorkDay();
    m_poMainDlg = p_poMainDlg;

    m_inTimerId = startTimer( 1000 );
}

void cWattaMainApp::endSession() throw()
{
    cTracer obTrace( &g_obLogger, "cWattaMainApp::endSession" );

    killTimer( m_inTimerId );

    if( m_poCurrWorkDay ) delete m_poCurrWorkDay;
}

void cWattaMainApp::timerEvent ( QTimerEvent * )
{
    QString  qsToolTip = "End: ";
    qsToolTip.append( m_poCurrWorkDay->endTime() );
    qsToolTip.append( "\nBalance: " );
    qsToolTip.append( cPreferences::secondsToTimeStr( m_poCurrWorkDay->balance() ) );
    m_poMainDlg->setIconToolTip( qsToolTip );
}
