#include <QSqlQuery>

#include "session.h"
#include "watta.h"

cSession::cSession()
{
    cTracer obTrace( &g_obLogger, "cSession::cSession" );

    QDateTime  obCurrDateTime = QDateTime::currentDateTime();
    m_qsStartDate = obCurrDateTime.toString( "yyyy-MM-dd" );
    m_qsStartTime = obCurrDateTime.toString( "hh:mm:ss" );
    m_loStartSeconds = cPreferences::timeStrToSeconds( m_qsStartTime );

    try
    {
        g_poDB->executeQuery( QString( "INSERT INTO `sessions` (`date`, `startTime`) VALUES ('%1', '%2')" ).arg( m_qsStartDate ).arg( m_qsStartTime ) );
    }
    catch( cSevException &e )
    {
        g_obLogger << e;
    }
}

cSession::~cSession()
{
    cTracer obTrace( &g_obLogger, "cSession::~cSession" );

    QString qsEndTime = QDateTime::currentDateTime().toString( "hh:mm:ss" );
    try
    {
        g_poDB->executeQuery( QString( "UPDATE `sessions` SET `endTime`='%1' WHERE `date`='%2' AND `startTime`='%3'" ).arg( qsEndTime ).arg( m_qsStartDate ).arg( m_qsStartTime ) );
    }
    catch( cSevException &e )
    {
        g_obLogger << e;
    }
}

long cSession::length() const
{
    QString qsCurrTime = QDateTime::currentDateTime().toString( "hh:mm:ss" );
    return cPreferences::timeStrToSeconds( qsCurrTime ) - m_loStartSeconds;
}

long cSession::start() const
{
    return m_loStartSeconds;
}
