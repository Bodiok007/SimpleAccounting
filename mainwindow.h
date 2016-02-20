#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "addsale.h"
#include "addserviceform.h"
#include "editsalesform.h"
#include "editservicesform.h"


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
    void showAddServiceForm();
    void showEditSaleForm();
    void showEditServiceForm();
    void logOut();
    void logIn(QString userName);
    void setModels();
    void updateSalesModel();
    void updateServicesModel();

signals:
    void logout();

private:
    Ui::MainWindow *ui;
    AddSale *m_pAddSaleForm;
    AddServiceForm *m_pAddServiceForm;
    EditSalesForm *m_pEditSaleForm;
    EditServicesForm *m_pEditServiceForm;

    void bindSignalsAndSlotsForSales();
    void bindSignalsAndSlotsForServices();

};

#endif // MAINWINDOW_H
