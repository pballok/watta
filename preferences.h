#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QString>

#include <guiwriter.h>
#include <filewriter.h>
#include <sevexception.h>

class cPreferences
{
public:
    cPreferences( const QString &p_qsAppName, const QString &p_qsVersion,
                  cGUIWriter *p_poGUIWriter, cFileWriter *p_poFileWriter );
    ~cPreferences();

    QString                    appName() const;
    QString                    version() const;
    void                       setGUILogLevel( const cSeverity::teSeverity p_enLevel );
    cSeverity::teSeverity      GUILogLevel() const;
    void                       setFileLogLevel( const cSeverity::teSeverity p_enLevel );
    cSeverity::teSeverity      fileLogLevel() const;
    QString                    dbHost() const;
    QString                    dbSchema() const;
    QString                    dbUser() const;
    QString                    dbPassword() const;

    void                       setWorkDayEnd( const QString &p_qsTime );
    QString                    workDayEnd() const;
    unsigned long              workDayEndSeconds() const;
    void                       setWorkDayLength( const QString &p_qsTime );
    QString                    workDayLength() const;
    unsigned long              workDayLengthSeconds() const;

    void                       load() throw(cSevException);
    void                       save() const throw(cSevException);

    static long                timeStrToSeconds( const QString &p_qsTime );
    static QString             secondsToTimeStr( const long p_loSeconds );

private:
    QString                    m_qsAppName;
    QString                    m_qsVersion;
    QString                    m_qsFileName;
    QString                    m_qsDBHost;
    QString                    m_qsDBSchema;
    QString                    m_qsDBUser;
    QString                    m_qsDBPwd;
    cGUIWriter*                m_poGUIWriter;
    cFileWriter*               m_poFileWriter;

    QString                    m_qsWorkDayEnd;
    QString                    m_qsWorkDayLength;
    unsigned long              m_ulWorkDayEndSeconds;
    unsigned long              m_ulWorkDayLengthSeconds;
};

#endif
