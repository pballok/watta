#ifndef DLGPREFERENCES_H
#define DLGPREFERENCES_H

#include <QAction>
#include <QSystemTrayIcon>
#include <QMenu>

#include "ui_dlgpreferences.h"

class cDlgPreferences : public QDialog, private Ui::dlgPreferences
{
    Q_OBJECT

public:
    cDlgPreferences( QWidget *p_poParent = 0 );

    void setIconToolTip( const QString &p_qsToolTip );

public slots:
    virtual void accept();

private:
    QAction                   *m_poPreferencesAction;
    QAction                   *m_poTasksAction;
    QAction                   *m_poQuitAction;

    QSystemTrayIcon           *m_poTrayIcon;
    QMenu                     *m_poTrayIconMenu;

private slots:
    void on_sliConsoleLogLevel_valueChanged( int p_inValue );
    void on_sliDBLogLevel_valueChanged( int p_inValue );
    void on_sliGUILogLevel_valueChanged( int p_inValue );
};

#endif
