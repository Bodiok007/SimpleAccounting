#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "addsale.h"

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

public slots:
    void showAddSaleForm();


private:
    Ui::MainWindow *ui;
    AddSale *m_pAddSaleForm;
};

#endif // MAINWINDOW_H
