#include "mainapplication.h"

MainApplication::MainApplication(QObject *parent)
    : QObject(parent)
{
    m_pLoginForm = new LoginForm;
    m_pLoginForm->show();

    connect(m_pLoginForm, SIGNAL(logged(QString)), SLOT(logIn(QString)));
}


void MainApplication::createMainWindow()
{
    m_pMainWindow = new MainWindow;
    m_pMainWindow->show();
    connect(m_pMainWindow, SIGNAL(logout()), SLOT(logOut()));
    connect(m_pMainWindow, SIGNAL(destroyed(QObject*)), SLOT(logOut()));
}


void MainApplication::deleteMainWindow()
{
    m_pMainWindow->close();
}


void MainApplication::logIn(QString userName)
{
    createMainWindow();
    m_pMainWindow->setWindowTitle(userName);
    m_pLoginForm->hide();
}


void MainApplication::logOut()
{
    m_pLoginForm->show();
    deleteMainWindow();
}


MainApplication::~MainApplication()
{
    delete m_pLoginForm;
}
