#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "db.h"
//#include "salestableview.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableSales->setModel(DB::instance()->getAllSales());
    ui->tableSales->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableServices->setModel(DB::instance()->getAllServices());
    ui->tableServices->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
    delete ui;
}
