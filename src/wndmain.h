#ifndef WNDMAIN_H
#define WNDMAIN_H

#include <QString>

#include "ui_wndmain.h"
#include "session.h"

class cWndMain : public QMainWindow, private Ui::wndMain
{
    Q_OBJECT

public:
    cWndMain( QWidget *parent = 0 );
    ~cWndMain();

private slots:
    void on_action_Preferences_triggered();
    void on_action_Logs_triggered();
};

#endif
