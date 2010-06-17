#include <QDateTime>

#include "workday.h"
#include "watta.h"

cWorkDay::cWorkDay()
{
    cTracer obTracer( "cWorkDay::cWorkDay" );

    QString qsDate = QDateTime::currentDateTime().toString( "yyyy-MM-dd" );

    load( qsDate );

    m_poCurrSession = new cSession();

    calculateEndTimes();
}

cWorkDay::cWorkDay( QString &p_qsDate )
{
    cTracer obTracer( "cWorkDay::cWorkDay", p_qsDate.toStdString() );

    load( p_qsDate );

    m_poCurrSession = NULL;

    calculateEndTimes();
}

cWorkDay::~cWorkDay()
{
    cTracer obTracer( "cWorkDay::~cWorkDay" );

    if( m_poCurrSession ) delete m_poCurrSession;
}

QString cWorkDay::endTime() const
{
    return m_qsEndTime;
}

long cWorkDay::balance() const
{
    QString qsCurrDate = QDateTime::currentDateTime().toString( "hh:mm:ss" );
    long loBalance = cPreferences::timeStrToSeconds( qsCurrDate ) - m_loEndSeconds;

    return loBalance;
}

void cWorkDay::load( QString &p_qsDate )
{
    cTracer obTracer( "cWorkDay::load", p_qsDate.toStdString() );

    m_qsDate = "";
    m_loFixEndSeconds = 0;
    m_loLenEndSeconds = 0;

    QSqlQuery *poQuery = NULL;

    try
    {
        QString qsEndTime;
        QString qsLength;

        poQuery = g_poDB->executeQTQuery( QString( "SELECT `date`, `endTime`, `length` FROM `workdays` WHERE `date`='%1'").arg( p_qsDate ) );
        if( poQuery->size() == 0 )
        {
            qsEndTime = g_poPrefs->getWorkDayEnd();
            qsLength  = g_poPrefs->getWorkDayLength();
            g_poDB->executeQuery( QString( "INSERT INTO `workdays` (`date`, `endTime`, `length`) VALUES ('%1', '%2', '%3')" ).arg( p_qsDate ).arg( qsEndTime ).arg( qsLength ).toStdString(), true );
        }
        else
        {
            poQuery->first();
            qsEndTime = poQuery->value( 1 ).toString();
            qsLength  =  poQuery->value( 2 ).toString();
        }

        m_qsDate = p_qsDate;
        m_loFixEndSeconds = cPreferences::timeStrToSeconds( qsEndTime );
        m_loLenEndSeconds = cPreferences::timeStrToSeconds( qsLength );
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

    m_loSecondsAlreadySpent = 0;
    m_loLastSessionEnd = 0;

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
                long  loStartSeconds = cPreferences::timeStrToSeconds( qsStartTime );
                m_loLastSessionEnd   = cPreferences::timeStrToSeconds( qsEndTime );
                m_loSecondsAlreadySpent += m_loLastSessionEnd - loStartSeconds;
            }
        }
    }
    catch( cSevException &e )
    {
        g_obLogger << e.severity() << e.what() << cQTLogger::EOM;
    }

    if( poQuery ) delete poQuery;

    obTracer << "time already spent: " << cPreferences::secondsToTimeStr( (long)m_loSecondsAlreadySpent ).toStdString();
}

void cWorkDay::calculateEndTimes()
{
    if( m_poCurrSession ) m_loLenEndSeconds += m_poCurrSession->start();
    else m_loLenEndSeconds += m_loLastSessionEnd;
    m_loLenEndSeconds -= m_loSecondsAlreadySpent;

    m_loEndSeconds = max( m_loLenEndSeconds, m_loFixEndSeconds );
    m_qsEndTime = cPreferences::secondsToTimeStr( m_loEndSeconds );
}
