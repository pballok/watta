#include "workday.h"
#include "watta.h"

cWorkDay::cWorkDay()
{
    QString qsDate = QDateTime::currentDateTime().toString( "yyyy-MM-dd" );

    load( qsDate );

    m_poCurrSession = new cSession();
}

cWorkDay::cWorkDay( QString &p_qsDate )
{
    load( p_qsDate );

    m_poCurrSession = NULL;
}

cWorkDay::~cWorkDay()
{
    if( m_poCurrSession ) delete m_poCurrSession;
}

void cWorkDay::load( QString &p_qsDate )
{
    m_qsDate = "";
    m_uiSeconds = 0;

    QSqlQuery *poQuery = NULL;

    try
    {
        poQuery = g_poDB->executeQTQuery( QString( "SELECT * FROM `workdays` WHERE `date`='%1'").arg( p_qsDate ) );
        if( poQuery->size() == 0 )
        {
            g_poDB->executeQuery( QString( "INSERT INTO `workdays` (`date`, `endTime`, `length`) VALUES ('%1')" ).arg( p_qsDate ).arg( g_poPrefs->getWorkDayEnd() ).arg( g_poPrefs->getWorkDayLength() ).toStdString(), true );
        }

        m_qsDate = p_qsDate;
    }
    catch( cSevException &e )
    {
        g_obLogger << e.severity() << e.what() << cQTLogger::EOM;
    }

    if( poQuery ) delete poQuery;

    loadSessions();
}

void cWorkDay::loadSessions()
{
    cTracer obTracer( "cWorkDay::loadSessions" );

    QSqlQuery *poQuery = NULL;

    try
    {
        poQuery = g_poDB->executeQTQuery( QString( "SELECT `startTime`, `endTime` FROM `sessions` WHERE `date`='%1'").arg( m_qsDate ) );
        while( poQuery->next() )
        {
            QString qsStartTime = poQuery->value( 0 ).toString();
            QString qsEndTime = poQuery->value( 1 ).toString();

            if( qsStartTime == "" || qsEndTime == "" )
            {
                g_obLogger << cSeverity::WARNING << "Corrupt Session Data:";
                g_obLogger << " Date: " << m_qsDate.toStdString();
                g_obLogger << " StarTime: " << qsStartTime.toStdString();
                g_obLogger << " EndTime: " << qsEndTime.toStdString();
                g_obLogger << cQTLogger::EOM;
            }
            else
            {
                unsigned int  uiStartSeconds = cPreferences::timeStrToSeconds( qsStartTime );
                unsigned int  uiEndSeconds   = cPreferences::timeStrToSeconds( qsEndTime );
                m_uiSeconds += uiEndSeconds - uiStartSeconds;
            }
        }
    }
    catch( cSevException &e )
    {
        g_obLogger << e.severity() << e.what() << cQTLogger::EOM;
    }

    if( poQuery ) delete poQuery;

    obTracer << "seconds: " << m_uiSeconds;
}
