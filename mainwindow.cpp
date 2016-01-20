#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "db.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(DB::instance()->getAllSales());
    ui->tableServices->setModel(DB::instance()->getAllServices());
}

MainWindow::~MainWindow()
{
    delete ui;
}
