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

    QString        endTime() const;
    long           balance() const;

private:
    QString        m_qsDate;
    cSession      *m_poCurrSession;
    long           m_loFixEndSeconds;
    long           m_loLenEndSeconds;
    long           m_loEndSeconds;
    long           m_loSecondsAlreadySpent;
    long           m_loLastSessionEnd;
    QString        m_qsEndTime;

    void           load( QString &p_qsDate );
    void           loadSessions();
    void           calculateEndTimes();
};

#endif // WORKDAY_H
