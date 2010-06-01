#include <QSqlQuery>

#include "session.h"
#include "watta.h"

cSession::cSession()
{
    cTracer obTrace( "cSession::cSession" );

    QDateTime  obCurrDateTime = QDateTime::currentDateTime();
    m_qsStartDate = obCurrDateTime.toString( "yyyy-MM-dd" );
    m_qsStartTime = obCurrDateTime.toString( "hh:mm:ss" );

    try
    {
        g_poDB->executeQuery( QString( "INSERT INTO `sessions` (`date`, `startTime`) VALUES ('%1', '%2')" ).arg( m_qsStartDate ).arg( m_qsStartTime ).toStdString(), true );
    }
    catch( cSevException &e )
    {
        g_obLogger << e.severity() << e.what() << cQTLogger::EOM;
    }
}

cSession::~cSession()
{
    cTracer obTrace( "cSession::~cSession" );

    QString qsEndTime = QDateTime::currentDateTime().toString( "hh:mm:ss" );
    g_poDB->executeQuery( QString( "UPDATE `sessions` SET `endTime`='%1' WHERE `date`='%2' AND `startTime`='%3'" ).arg( qsEndTime ).arg( m_qsStartDate ).arg( m_qsStartTime ).toStdString(), true );
}
