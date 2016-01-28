#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "addsale.h"
#include "loginform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Ui::MainWindow *getForm();

    virtual void exit();

public slots:
    void showAddSaleForm();
    void logOut();
    void logIn(QString userName);
    void setModels();
    void updateSalesModel();
    void updateServicesModel();

private:
    Ui::MainWindow *ui;
    LoginForm *m_pLoginForm;
    AddSale *m_pAddSaleForm;

};

#endif // MAINWINDOW_H
