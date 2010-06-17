#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QString>

class cPreferences
{
public:
    cPreferences();
    cPreferences( const QString &p_qsAppName );
    ~cPreferences();

    void                       setAppName( const QString &p_qsAppName );
    QString                    getAppName() const;
    void                       setVersion( const QString &p_qsVersion );
    QString                    getVersion() const;
    void                       setWorkDayEnd( const QString &p_qsTime );
    QString                    getWorkDayEnd() const;
    unsigned long              getWorkDayEndSeconds() const;
    void                       setWorkDayLength( const QString &p_qsTime );
    QString                    getWorkDayLength() const;
    unsigned long              getWorkDayLengthSeconds() const;
    void                       setLogLevels( const unsigned int p_uiConLevel,
                                             const unsigned int p_uiDBLevel,
                                             const unsigned int p_uiGUILevel,
                                             bool p_boSaveNow = false );
    void                       getLogLevels( unsigned int *p_poConLevel = NULL,
                                             unsigned int *p_poDBLevel = NULL,
                                             unsigned int *p_poGUILevel = NULL ) const;
    void                       setDBAccess( const QString &p_qsHost, const QString &p_qsDB,
                                            const QString &p_qsUser, const QString &p_qsPwd );
    void                       getDBAccess( QString *p_poHost = NULL, QString *p_poDB = NULL,
                                            QString *p_poUser = NULL, QString *p_poPwd = NULL) const;

    void                       load();
    void                       save() const;

    static long                timeStrToSeconds( const QString &p_qsTime );
    static QString             secondsToTimeStr( const long p_loSeconds );

private:
    QString                    m_qsAppName;
    QString                    m_qsFileName;
    QString                    m_qsVersion;
    QString                    m_qsWorkDayEnd;
    QString                    m_qsWorkDayLength;

    unsigned long              m_ulWorkDayEndSeconds;
    unsigned long              m_ulWorkDayLengthSeconds;

    void init();
};

#endif
