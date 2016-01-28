#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "db.h"
#include "ui_addsaleform.h"

#include "dbsettings.h"

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

    m_pAddServiceForm = new AddServiceForm;
    connect(ui->addServiceButton,
            SIGNAL(clicked(bool)),
            SLOT(showAddServiceForm())
           );

    m_pLoginForm = new LoginForm(0);
    m_pLoginForm->show();

    //this->hide();

    setModels();

    connect(DB::instance(),
            SIGNAL(updateSalesData()),
            SLOT(updateSalesModel())
           );

    connect(DB::instance(),
            SIGNAL(updateServicesData()),
            SLOT(updateServicesModel())
           );

    connect(ui->tableSales,
            SIGNAL(addSale()),
            SLOT(showAddSaleForm())
           );

    connect(ui->tableServices,
            SIGNAL(addService()),
            SLOT(showAddServiceForm())
           );

    ui->tabWidget->setStyleSheet("QTabBar::tab { height: 35px; }");

    ui->toolBar->addAction(QPixmap(":/logOut.png"), "Вихід", this, SLOT(logOut()) );

    connect(m_pLoginForm, SIGNAL(logged(QString)), SLOT(logIn(QString)) );
}


void MainWindow::setModels()
{
    updateSalesModel();
    updateServicesModel();
    ui->tableSales->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableServices->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


void MainWindow::updateSalesModel()
{
    ui->tableSales->setModel(DB::instance()->getAllSales());
}

void MainWindow::updateServicesModel()
{
    ui->tableServices->setModel(DB::instance()->getAllServices());
}


Ui::MainWindow *MainWindow::getForm()
{
    return ui;
}


void MainWindow::exit()
{
    this->hide();
    m_pLoginForm->show();
}


void MainWindow::showAddSaleForm()
{
    m_pAddSaleForm->setEmployeeName(windowTitle());
    m_pAddSaleForm->show();
}

void MainWindow::showAddServiceForm()
{
    m_pAddServiceForm->setEmployeeName(windowTitle());
    m_pAddServiceForm->show();
}


void MainWindow::logOut()
{
    this->hide();
    m_pLoginForm->show();
}


void MainWindow::logIn(QString userName)
{
    this->setWindowTitle(userName);
    this->show();
    qDebug() << "userLogged!" + userName;
}


MainWindow::~MainWindow()
{
    delete ui;
    delete m_pAddSaleForm;
    delete m_pLoginForm;
}


