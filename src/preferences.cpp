#include "preferences.h"
#include "watta.h"

#include <QSettings>

cPreferences::cPreferences( const QString &p_qsAppName, const QString &p_qsVersion,
                            cGUIWriter *p_poGUIWriter, cFileWriter *p_poFileWriter  )
    : m_qsAppName( p_qsAppName ),
      m_qsVersion( p_qsVersion ),
      m_poGUIWriter( p_poGUIWriter ),
      m_poFileWriter( p_poFileWriter )
{
    m_qsFileName  = QString( "./%1.ini" ).arg( p_qsAppName );
    m_qsDBHost    = "";
    m_qsDBSchema  = "";
    m_qsDBUser    = "";
    m_qsDBPwd     = "";

    m_qsWorkDayEnd    = "";
    m_qsWorkDayLength = "";
    m_ulWorkDayEndSeconds    = 0;
    m_ulWorkDayLengthSeconds = 0;

    try
    {
        load();
    } catch( cSevException &e )
    {
        g_obLogger << e;
    }
}

cPreferences::~cPreferences()
{
}

QString cPreferences::appName() const
{
    return m_qsAppName;
}

QString cPreferences::version() const
{
    return m_qsVersion;
}

void cPreferences::setGUILogLevel( const cSeverity::teSeverity p_enLevel )
{
    m_poGUIWriter->setMinSeverity( p_enLevel );
}

cSeverity::teSeverity cPreferences::GUILogLevel() const
{
    return m_poGUIWriter->minSeverity();
}

void cPreferences::setFileLogLevel( const cSeverity::teSeverity p_enLevel )
{
    m_poFileWriter->setMinSeverity( p_enLevel );
}

cSeverity::teSeverity cPreferences::fileLogLevel() const
{
    return m_poFileWriter->minSeverity();
}

QString cPreferences::dbHost() const
{
    return m_qsDBHost;
}

QString cPreferences::dbSchema() const
{
    return m_qsDBSchema;
}

QString cPreferences::dbUser() const
{
    return m_qsDBUser;
}

QString cPreferences::dbPassword() const
{
    return m_qsDBPwd;
}

void cPreferences::setWorkDayEnd( const QString &p_qsTime )
{
    m_qsWorkDayEnd = p_qsTime;
    m_ulWorkDayEndSeconds = timeStrToSeconds( m_qsWorkDayEnd );
}

QString cPreferences::workDayEnd() const
{
    return m_qsWorkDayEnd;
}

unsigned long cPreferences::workDayEndSeconds() const
{
    return m_ulWorkDayEndSeconds;
}

void cPreferences::setWorkDayLength( const QString &p_qsTime )
{
    m_qsWorkDayLength = p_qsTime;
    m_ulWorkDayLengthSeconds = timeStrToSeconds( m_qsWorkDayLength );
}

QString cPreferences::workDayLength() const
{
    return m_qsWorkDayLength;
}

unsigned long cPreferences::workDayLengthSeconds() const
{
    return m_ulWorkDayLengthSeconds;
}

void cPreferences::load() throw(cSevException)
{
    QSettings obPrefFile( m_qsFileName, QSettings::IniFormat );
    if( obPrefFile.status() != QSettings::NoError )
    {
        throw cSevException( cSeverity::WARNING, QString( "Failed to open preferences file: %1" ).arg( m_qsFileName ).toStdString() );
    }

    unsigned int uiGUILevel = obPrefFile.value( "LogLevels/GUILogLevel", cSeverity::ERROR ).toUInt();
    if( (uiGUILevel >= cSeverity::MAX) ||
        (uiGUILevel <= cSeverity::MIN) )
    {
        uiGUILevel = cSeverity::NONE;
        throw cSevException( cSeverity::WARNING, QString( "Invalid GUILogLevel in preferences file: %1" ).arg( m_qsFileName ).toStdString() );
    }
    setGUILogLevel( (cSeverity::teSeverity)uiGUILevel );

    unsigned int uiFileLevel = obPrefFile.value( "LogLevels/FileLogLevel", cSeverity::ERROR ).toUInt();
    if( (uiFileLevel >= cSeverity::MAX) ||
        (uiFileLevel <= cSeverity::MIN) )
    {
        uiFileLevel = cSeverity::NONE;
        throw cSevException( cSeverity::WARNING, QString( "Invalid FileLogLevel in preferences file: %1" ).arg( m_qsFileName ).toStdString() );
    }
    setFileLogLevel( (cSeverity::teSeverity)uiFileLevel );

    m_qsDBHost    = obPrefFile.value( "DataBase/Host", "" ).toString();
    m_qsDBSchema  = obPrefFile.value( "DataBase/Schema", "" ).toString();
    m_qsDBUser    = obPrefFile.value( "DataBase/User", "" ).toString();
    m_qsDBPwd     = obPrefFile.value( "DataBase/Password", "" ).toString();

    setWorkDayEnd( obPrefFile.value( "WorkDay/EndTime", "00:00:00" ).toString() );
    setWorkDayLength( obPrefFile.value( "WorkDay/Length", "08:30:00" ).toString() );
}

void cPreferences::save() const throw(cSevException)
{
    QSettings  obPrefFile( m_qsFileName, QSettings::IniFormat );
    if( obPrefFile.status() != QSettings::NoError )
    {
        throw cSevException( cSeverity::WARNING, QString( "Failed to write to preferences file: %1" ).arg( m_qsFileName ).toStdString() );
    }

    obPrefFile.setValue( "LogLevels/GUILogLevel", m_poGUIWriter->minSeverity() );
    obPrefFile.setValue( "LogLevels/FileLogLevel", m_poFileWriter->minSeverity() );

    obPrefFile.setValue( "WorkDay/EndTime", m_qsWorkDayEnd );
    obPrefFile.setValue( "WorkDay/Length", m_qsWorkDayLength );
}

long cPreferences::timeStrToSeconds( const QString &p_qsTime )
{
    long loSeconds = 0;

    if( p_qsTime != "" )
    {
        bool boConversionOk = true;
        loSeconds = p_qsTime.section( ':', 2, 2 ).toInt( &boConversionOk, 10 );

        if( boConversionOk ) loSeconds += p_qsTime.section( ':', 1, 1 ).toInt( &boConversionOk, 10 ) * 60;
        else loSeconds = 0;

        if( boConversionOk ) loSeconds += p_qsTime.section( ':', 0, 0 ).toInt( &boConversionOk, 10 ) * 3600;
        else loSeconds = 0;
    }

    return loSeconds;
}

QString cPreferences::secondsToTimeStr( const long p_loSeconds )
{
    QString  qsTime = "";
    unsigned long ulSeconds = p_loSeconds;
    if( p_loSeconds < 0 )
    {
        qsTime = "-";
        ulSeconds = -1 * p_loSeconds;
    }
    unsigned long ulHours = ulSeconds / 3600;
    ulSeconds -= ulHours * 3600;
    unsigned long ulMinutes = ulSeconds / 60;
    ulSeconds -= ulMinutes * 60;

    qsTime += QString( "%1:%2:%3" ).arg( ulHours, 2, 10, QChar( '0' ) ).arg( ulMinutes, 2, 10, QChar( '0' ) ).arg( ulSeconds, 2, 10, QChar( '0' ) );
    return qsTime;
}
