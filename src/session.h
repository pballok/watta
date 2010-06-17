#ifndef SESSION_H
#define SESSION_H

#include <QString>

class cSession
{
public:
    cSession();
    ~cSession();

    long           length() const;
    long           start() const;

private:
    QString        m_qsStartDate;
    QString        m_qsStartTime;
    long           m_loStartSeconds;
};

#endif // SESSION_H
