#ifndef DLGPREFERENCES_H
#define DLGPREFERENCES_H

#include "ui_dlgpreferences.h"

class cDlgPreferences : public QDialog, private Ui::dlgPreferences
{
    Q_OBJECT

public:
    cDlgPreferences( QWidget *p_poParent = 0 );

public slots:
    virtual void accept();

private slots:
    void on_sliConsoleLogLevel_valueChanged( int p_inValue );
    void on_sliDBLogLevel_valueChanged( int p_inValue );
    void on_sliGUILogLevel_valueChanged( int p_inValue );
};

#endif
