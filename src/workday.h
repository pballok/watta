#ifndef WORKDAY_H
#define WORKDAY_H

#include "session.h"

#include <QString>

class cWorkDay
{
public:
    cWorkDay( QString &p_stDate );
    ~cWorkDay();

private:
    QString        m_qsDate;
    unsigned int   m_uiSeconds;
    cSession      *m_poCurrSession;

    void           loadSessions();
    unsigned int   timeStrToSeconds( QString &p_qsTime );
};

#endif // WORKDAY_H
