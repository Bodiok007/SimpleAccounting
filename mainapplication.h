#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include <QObject>

#include "loginform.h"
#include "mainwindow.h"

class MainApplication : public QObject
{
    Q_OBJECT
public:
    explicit MainApplication(QObject *parent = 0);
    ~MainApplication();

signals:

public slots:
    void createMainWindow();
    void deleteMainWindow();
    void logIn(QString userName);
    void logOut();

private:
    LoginForm *m_pLoginForm;
    MainWindow *m_pMainWindow;
};

#endif // MAINAPPLICATION_H
