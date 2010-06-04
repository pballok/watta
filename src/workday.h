#ifndef WORKDAY_H
#define WORKDAY_H

#include "session.h"

#include <QString>

class cWorkDay
{
public:
    cWorkDay();
    cWorkDay( QString &p_stDate );
    ~cWorkDay();

private:
    QString        m_qsDate;
    unsigned int   m_uiSeconds;
    cSession      *m_poCurrSession;

    void           load( QString &p_qsDate );
    void           loadSessions();
    unsigned int   timeStrToSeconds( QString &p_qsTime );
};

#endif // WORKDAY_H
