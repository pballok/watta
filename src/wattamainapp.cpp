#include "wattamainapp.h"
#include "watta.h"

cWattaMainApp::cWattaMainApp( int &argc, char **argv ) : QApplication( argc, argv )
{
    m_poSession = NULL;

    connect( this, SIGNAL( aboutToQuit() ), this, SLOT( endSession() ) );
}

cWattaMainApp::~cWattaMainApp()
{
    endSession();
}

void cWattaMainApp::startSession() throw()
{
    m_poSession = new cSession();
}

void cWattaMainApp::endSession() throw()
{
    if( m_poSession ) delete m_poSession;
    m_poSession = NULL;

    g_obLogger << cSeverity::INFO;
    g_obLogger << g_poPrefs->getAppName().toStdString() << " Version " << g_poPrefs->getVersion().toStdString() << " ended.";
    g_obLogger << cQTLogger::EOM;
}
