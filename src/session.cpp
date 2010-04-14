#include <QSqlQuery>

#include "session.h"
#include "watta.h"

cSession::cSession()
{
    cTracer obTrace( "cSession::cSession" );

    QDateTime  obCurrDateTime = QDateTime::currentDateTime();
    m_qsStartDate = obCurrDateTime.toString( "yyyy-MM-dd" );
    m_qsStartTime = obCurrDateTime.toString( "hh:mm:ss" );

    QSqlQuery *poQuery = g_poDB->executeQTQuery( QString( "SELECT * FROM `workdays` WHERE `date`='%1'").arg( m_qsStartDate ) );
    if( poQuery->size() == 0 )
    {
        g_poDB->executeQuery( QString( "INSERT INTO `workdays` (`date`) VALUES ('%1')" ).arg( m_qsStartDate ).toStdString(), true );
    }

    g_poDB->executeQuery( QString( "INSERT INTO `sessions` (`date`, `startTime`) VALUES ('%1', '%2')" ).arg( m_qsStartDate ).arg( m_qsStartTime ).toStdString(), true );
}

cSession::~cSession()
{
    cTracer obTrace( "cSession::~cSession" );

    QString qsEndTime = QDateTime::currentDateTime().toString( "hh:mm:ss" );
    g_poDB->executeQuery( QString( "UPDATE `sessions` SET `endTime`='%1' WHERE `date`='%2' AND `startTime`='%3'" ).arg( qsEndTime ).arg( m_qsStartDate ).arg( m_qsStartTime ).toStdString(), true );
}
