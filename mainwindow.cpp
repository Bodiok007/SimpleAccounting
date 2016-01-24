#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "db.h"
#include "ui_addsaleform.h"
//#include "salestableview.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pAddSaleForm = new AddSale(0);

    connect(ui->addSaleButton,
            SIGNAL(clicked(bool)),
            SLOT(showAddSaleForm())
           );

    ui->tableSales->setModel(DB::instance()->getAllSales());
    ui->tableSales->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableServices->setModel(DB::instance()->getAllServices());
    ui->tableServices->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tabWidget->setStyleSheet("QTabBar::tab { height: 35px; }");

    ui->toolBar->addAction(QPixmap(":/logOut.png"), "Вихід", this, SLOT(slotNoImpl()));


    //connect(ui->addSaleButton, SIGNAL(clicked(bool), ),
}

MainWindow::~MainWindow()
{
    delete ui;
}

Ui::MainWindow *MainWindow::getForm()
{
    return ui;
}

void MainWindow::showAddSaleForm()
{
    m_pAddSaleForm->show();
}
