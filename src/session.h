#ifndef SESSION_H
#define SESSION_H

#include <QString>

class cSession
{
public:
    cSession();
    ~cSession();

private:
    QString m_qsStartDate;
    QString m_qsStartTime;
};

#endif // SESSION_H
