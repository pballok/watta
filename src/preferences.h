#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QString>

class cPreferences
{
public:
    cPreferences();
    cPreferences( const QString &p_qsFileName );
    ~cPreferences();

    void                       setAppName( const QString &p_qsFileName );
    QString                    getAppName() const;
    void                       setVersion( const QString &p_qsVersion );
    QString                    getVersion() const;
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

private:
    QString                    m_qsAppName;
    QString                    m_qsFileName;
    QString                    m_qsVersion;

    void init();
};

#endif
